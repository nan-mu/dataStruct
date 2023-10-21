#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

/* 有点离谱，我希望用c++20的ranges，但似乎clang默认用libstdc++而不是libc++导致无法使用最新的标准库。
解决方法是在编译flag中启用-std=c++20和-stdlib=libc++*/

int main() {
    string s_target, t_temple;

    for (const auto letter :
         "abcdefghijklmnopqrstuvwxyz") // 生成一个弱随机的字符串
        if (rand() > RAND_MAX / 2)
            s_target += letter;
    for (auto iter = rand() / s_target.length(); iter < s_target.length();
         iter++)
        t_temple.push_back(s_target[iter]);

    cout << t_temple;
}