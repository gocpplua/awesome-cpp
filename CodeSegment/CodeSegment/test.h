#pragma once
#include <string>
#include <stack>
#include <algorithm>
using namespace std;
class Test;
class Test1 {
public:
    Test1();
    int a = 0;
    //int aa(Test& a){}
    Test bb();
};
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Base {
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int) {};
    virtual void mf2() {};
    void mf3() {}
    void mf3(double){}
};

class Derived :public Base {
public:
    virtual void mf1() {}
    void mf3(){}
    void mf4() {}
};

class CompanyA {
    void sendCleartext(const std::string& msg) {}
    void sendEncrypted(const std::string& msg) {}
};


class CompanyB {
    void sendCleartext(const std::string& msg) {}
    void sendEncrypted(const std::string& msg) {}
};

class MsgInfo {

};

template<typename Company>
class MsgSender {
public:
    void sendClear(const MsgInfo& info) {
        std::string msg;
        Company c;
        c.sendCleartext(msg);
    }

    void sendSecret(const MsgInfo& info) {

    }
};

template<typename Company>
class LoggingMsgSender :public MsgSender<Company> {
public:
    void sendClearMsg(const std::string& info) {
        sendClear(info);
    }
};



class LeetCode7 {
public:
    // -2147483648 ~2147483647
    int reverse(int x) {
        int source = x;
        int target = 0;
        bool positive = source > 0 ? true : false;
        while (source != 0)
        {
            int remain = source % 10;
            source /= 10;
            if (positive)
            {
                if (target > 214748364)
                {
                    return 0;
                }
                else if (target == 214748364 && remain > 7)
                {
                    return 0;
                }
            }
            else
            {
                if (target < -214748364)
                {
                    return 0;
                }
                else if (target == -214748364 && remain < -8)
                {
                    return 0;
                }
            }
            target = target * 10 + remain;
        }
        return target;
    }

    bool isPalindrome(int x) {
        int source = x;
        int target = 0;
        if (x < 0 || (x % 10 == 0 && x != 0))
        {
            return false;
        }
        else if (x > 0)
        {
            while (target < source)
            {
                target = target * 10 + source % 10;
                if (target == source)
                {
                    return true;
                }

                source /= 10;
                if (target == source)
                {
                    return true;
                }
            }
        }
        else
        {
            return true;
        }
        return false;
    }


    int getValue(char pre, char cur) {
        switch (pre) {
        case 'I': return (cur == 'V' || cur == 'X') ? -1 : 1;
        case 'V': return 5;
        case 'X': return (cur == 'L' || cur == 'C') ? -10 : 10;
        case 'L': return 50;
        case 'C': return (cur == 'D' || cur == 'M') ? -100 : 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
        }
    }
    int romanToInt(std::string s) {
        int target = 0;
        int len = s.length();
        if (len <= 0) return 0;
        char pre = s[0];
        for (int i = 1; i < len; i++)
        {
            char current = s[i];
            target += getValue(pre, current);
            pre = current;
        }
        target += getValue(pre, ' '); // 特别注意最后一位的问题
        return target;
    }

    int romanToInt1(std::string s) {
        int target = 0;
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            char c = s[i];
            if (c == 'I')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'V')
                    {
                        target += 4;
                        i++;
                        continue;
                    }
                    else if (s[i+1]== 'X')
                    {
                        target += 9;
                        i++;
                        continue;
                    }
                }
                target += 1;
            }
            else if (c == 'X')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'L')
                    {
                        target += 40;
                        i++;
                        continue;
                    }
                    else if (s[i+1] == 'C')
                    {
                        target += 90;
                        i++;
                        continue;
                    }
                }
                target += 10;
            }
            else if (c == 'C')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'D')
                    {
                        target += 400;
                        i++;
                        continue;
                    }
                    else if (s[i+1] == 'M')
                    {
                        target += 900;
                        i++;
                        continue;
                    }
                }
                target += 100;
            }
            else if (c == 'V')
            {
                target += 5;
            }
            else if (c == 'L')
            {
                target += 50;
            }
            else if (c == 'D')
            {
                target += 500;
            }
            else if (c == 'M')
            {
                target += 1000;
            }
        }
        return target;
    }

    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size())return "";
        string commonPre = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            int j = 0;
            for (; j < commonPre.length() && j < strs[i].length(); j++) {
                if (commonPre[j] != strs[i][j]) {
                   break;
                }
            }
            if (j == 0) return "";
            commonPre[j] = '\0';
        }
        return commonPre;
    }


    bool isValid(string s) {
        int len = s.length();
        if (0 == len) return true;

        std::stack<char> mystack;
        for (int i = 0; i < len; i++)
        {
            char currChar = s[i];
            if (currChar == '(' || currChar == '{' || currChar == '[')
            {
                mystack.push(currChar);
            }
            else if(currChar == ')' || currChar == '}' || currChar == ']')
            {
                if (0 == mystack.size()) return false;
                char topChar = mystack.top();
                if ((topChar == '(' && currChar == ')')  || (topChar == '{' && currChar == '}') || (topChar == '[' && currChar == ']'))
                {
                    mystack.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        return 0 == mystack.size() ? true : false;
    }

    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (0 == len) return 0;
        int i = 0, j = 1;
        for (; j < len; j++)
        {
            if (nums[i] != nums[j])
            {
                nums[i + 1] = nums[j];
                i++;
            }
        }
        return i+1;
    }

    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        if (0 == len)
        {
            return 0;
        }

        int i = 0, j = 0;
        for (; i < len; i++)
        {
            if (nums[i] != val)
            {
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->val > l2->val)
        {
            // 保证11最小数字
            ListNode* temp = l1;
            l1 = l2;
            l2 = temp;
        }
        ListNode* head = l1;
        ListNode* next = nullptr;

        for (; l1 != nullptr || l2 != nullptr;)
        {
            if (l1->next == nullptr)
            {
                l1->next = l2;
                return head;
            }
            if (l2 == nullptr)
            {
                return head;
            }
            if (l1->val <= l2->val && l2->val <= l1->next->val)
            {
                next = l2;
                ListNode* temp1 = l1->next;
                ListNode* temp2 = l2->next;
                l1->next = l2;
                l2->next = temp1;
                l2 = temp2;
            }
            else
            {
                if (l1->val <= l2->val)
                {
                    if (next)
                    {
                        l1 = next;
                        next = nullptr;
                    }
                    else
                    {
                        l1 = l1->next;
                    }
                }
                else
                {
                    l2 = l2->next;
                }
            }
        }
        
        return head;
    }

    string generateSayStr(const string& originalStr) {
        string destinationStr;
        int len = originalStr.length();
        if (0 == len) return "";
        int count = 1;
        int currChar = originalStr[0];
        for (int i = 1; i < len; i++)
        {
            if (currChar != originalStr[i])
            {
                destinationStr += (48 + count);
                destinationStr += currChar;
                count = 1;
                currChar = originalStr[i];
            }
            else
            {
                count++;
            }
        }
        destinationStr += (48 + count);
        destinationStr += currChar;
        return destinationStr;
    }
    string countAndSay(int n) {
        return "";
    }

    int strStr(string haystack, string needle) {
        int len1 = haystack.length();
        int len2 = needle.length();
        if (0 == len2) return 0;

        for (int i = 0; i <= len1 - len2; i++)
        {
            bool bFind = true;
            for (int j = 0; j < len2; j++)
            {
                if (haystack[i + j] != needle[j])
                {
                    bFind = false;
                    break;
                }
            }
            if (bFind)
            {
                return i;
            }
        }
        return -1;
    }

    int maxSubArray(vector<int>& nums) {
        int nLen = nums.size();
        if (0 == nLen) return 0;
        if (1 == nLen) return nums[0];
        int pre = 0;
        int nMax = nums[0];
        for (int i = 0; i < nLen; i++)
        {
            pre = std::max(pre + nums[i], nums[i]);
            nMax = std::max(nMax, pre);
        }
        return nMax;
    }
    // 58. 最后一个单词的长度
    int lengthOfLastWord(string s) {
        int nLen = s.length();
        int end = nLen - 1;
        int start = 0;
        for (int i = nLen - 1; i >= 0; i--)
        {
            if (s[i] != ' ')
            {
                end = i;
                break;
            }
        }

        for (int i = end; i >= 0; i--)
        {
            if (s[i] == ' ')
            {
                return end - i;
            }
        }
        return end + 1;
    }

    // 66.加一
    vector<int> plusOne(vector<int>& digits) 
    {
        int len = digits.size();
        int up = 0;
        if (digits[len - 1] != 9)
        {
            digits[len - 1] = digits[len - 1] + 1;
            return digits;
        }
        else
        {
            digits[len - 1] = 0;
            up = 1;
        }
    
        for (int i = len - 2; i >= 0; i--)
        {
            if (digits[i] + up > 9)
            {
                digits[i] = 0;
                up = 1;
            }
            else
            {
                digits[i] = digits[i] + up;
                up = 0;
                return digits;
            }
        }

        if (up > 0)
        {
            digits.insert(digits.begin(), up);
        }
        return digits;
    }

    // 67. 二进制求和
    string addBinary(string a, string b) {
        int n = a.size();
        int m = b.size();
        string ans;

        n > m ? b.insert(0, n - m, '0') : a.insert(0, m - n, '0');
        int len = a.size();
        int sum = 0;
        for (int i = len - 1; i >= 0; i--) {
            sum = (a[i] - '0') + (b[i] - '0') + sum / 2; // 这个sum 表示前一次的和，如果是2就进位，很机智
            ans += char(sum % 2 + '0');
        }

        if (sum / 2 == 1)  ans += '1';
        std::reverse(ans.begin(), ans.end());
        return ans;
    }

    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size() - 1;
        int maxArea = (j - i - 1) * min(height[i], height[j]);
        while(i < j)
        {
            int area = (j - i) * min(height[i], height[j]);
            if (maxArea < area) maxArea = area;

            if (height[i] <= height[j]) {
                i++;
            }
            else {
                j--;
            }
        }
        return maxArea;
    }

    // 589. N叉树的前序遍历
    vector<int> preorder(Node* root) {
        std::vector<int> vec;
        recursive(root, vec);
        return vec;
    }

    void recursive(Node* node, vector<int>& vec) {
        if (!node) return;
        vec.push_back(node->val);
        int size = node->children.size();
        for (int i = 0; i < size; i++)
        {
            recursive(node->children[i], vec);
        }
    }
};