
# install yaml-cpp
wget https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz -O yaml-cpp-0.7.0.tar.gz
tar xf yaml-cpp-0.7.0.tar.gz
cd yaml-cpp-yaml-cpp-0.7.0  && mkdir build && cd build && cmake -DYAML_BUILD_SHARED_LIBS=ON .. && make -j8 && make install
cd ../../ && rm -rf yaml-cpp*


# install evpp
# 参考: https://note.youdao.com/s/BR9BvHGb