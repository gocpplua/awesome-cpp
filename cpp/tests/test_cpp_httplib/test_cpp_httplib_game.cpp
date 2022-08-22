//
//  simplesvr.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//
// 编译运行：mkdir build && cd build && cmake ../ && make test_cpp-httplib && ./out/test_cpp-httplib
// 客户端请求发送： $ curl 127.0.0.1:8080/hi
//               Hello World!

#include <cstdio>
#include "../../3thParty/cpp-httplib/httplib.h"
#include "../../3thParty/json/json.hpp"
#include <iostream>
#include<string>

using namespace httplib;

std::string dump_headers(const Headers &headers) {
  std::string s;
  char buf[BUFSIZ];

  for (auto it = headers.begin(); it != headers.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

std::string log(const Request &req, const Response &res) {
  std::string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  std::string query;
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%c%s=%s",
             (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
             x.second.c_str());
    query += buf;
  }
  snprintf(buf, sizeof(buf), "%s\n", query.c_str());
  s += buf;

  s += dump_headers(req.headers);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
  s += buf;
  s += dump_headers(res.headers);
  s += "\n";

  if (!res.body.empty()) { s += res.body; }

  s += "\n";

  return s;
}


// https://json.nlohmann.me/features/arbitrary_types/#basic-usage
namespace ns {
  // 实例1
  struct commonret {
    int code;
    std::string msg;
  };

  //Those methods MUST be in your type's namespace
  void to_json(nlohmann::json& j, const commonret& p) {
      j = nlohmann::json{ {"code", p.code}, {"msg", p.msg} };
  }

  void from_json(const nlohmann::json& j, commonret& p) {
      j.at("code").get_to(p.code);
      j.at("msg").get_to(p.msg);
  }


  // C++ 使用nlohmann解析Json数据&数据对象建模： https://zhuanlan.zhihu.com/p/387380942
  // 实例2
  struct addr {
    std::string province;
    std::string city;
  };

  struct customret {
      int code;
      std::string msg;
      addr data;
  };

  void to_json(nlohmann::json& j, const addr& p) {
      j = nlohmann::json{ {"province", p.province}, {"city", p.city} };
  }

  void from_json(const nlohmann::json& j, addr& p) {
      j.at("province").get_to(p.province);
      j.at("city").get_to(p.city);
  }

  void to_json(nlohmann::json& j, const customret& p) {
      j = nlohmann::json{ {"msg", p.msg}, {"code", p.code} };
      nlohmann::json jaddr;
      to_json(jaddr, p.data);
      j["data"] = jaddr;
  }

  void from_json(const nlohmann::json& j, customret& p) {
      j.at("msg").get_to(p.msg);
      j.at("code").get_to(p.code);
      j.at("data").get_to(p.data);
  }

} // namespace ns

int main(void) {
  Server svr;

  if (!svr.is_valid()) {
    printf("server has an error...\n");
    return -1;
  }

  svr.Get("/", [=](const Request & /*req*/, Response &res) {
    res.set_redirect("/hi");
  });

  svr.Post("/api/largespacevr/v1/gameserver/startgame", [](const Request &req, Response &res) {
    auto bodyJson = nlohmann::json::parse(req.body);
    std::cout << "gameround:"<< bodyJson["gameround"] << std::endl;
    ns::commonret p = {0, "success"};
    nlohmann::json j = p;
    res.set_content(j.dump(), "appliation/json");
  });

  svr.Post("/api/largespacevr/v1/gameserver/stopgame", [](const Request &req, Response &res) {
    auto bodyJson = nlohmann::json::parse(req.body);
    std::cout << "gameround:"<< bodyJson["gameround"] << std::endl;

    ns::customret p {0, "success",  "province", "city"};
    nlohmann::json j = p;
    res.set_content(j.dump(), "appliation/json");
  });

  svr.Post("/api/largespacevr/v1/gameserver/control", [](const Request &req, Response &res) {
    auto bodyJson = nlohmann::json::parse(req.body);
    std::cout << "gameround:"<< bodyJson["gameround"] << std::endl;

    // 方法一
    auto jsonBody = nlohmann::json{
      {"code", 1},
      {"msg", "success"},
      {"data", {{"s1",1}}}
    };

    /* 方法二
    nlohmann::json jsonBody;
    jsonBody["code"] = 1;
    jsonBody["msg"] = "success";
    jsonBody["data"] = {{"s1",1}};
    */
    res.set_content(jsonBody.dump(), "appliation/json");
  });

  svr.set_error_handler([](const Request & /*req*/, Response &res) {
    const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
    char buf[BUFSIZ];
    snprintf(buf, sizeof(buf), fmt, res.status);
    res.set_content(buf, "text/html");
  });

  svr.set_logger([](const Request &req, const Response &res) {
    printf("%s", log(req, res).c_str());
  });

  svr.listen("localhost", 6838);

  return 0;
}
