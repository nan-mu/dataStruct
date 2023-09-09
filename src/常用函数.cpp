#include <cmath>
#include <iostream>
#include <random>
#include <regex>
#include <vector>

using namespace std;

/// @brief 交换两变量
template <class T>
void tSwap(T* p1, T* p2) {
    T temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/// @brief
/// 封装一下正则，不知道为啥我的regex_match用不了，c++特性的真的很友好呀！！！！需要<regex>和<vector>两个头文件
/// @param target 目标字符串
/// @param sreg 正则表达式，使用ECMAScript模式
/// @param res 存放结果
void regSimple(string target, const char* sreg, vector<string>& res) {
    smatch sm;
    regex reg(sreg, regex::ECMAScript);
    string::const_iterator citer = target.cbegin();
    while (regex_search(citer, target.cend(), sm, reg)) {  //循环匹配
        citer = sm[0].second;
        // for (int i = 0; i < sm.size(); i++)
        res.push_back(sm.str());
    }
}

/// @brief 根据字符串输出double类型数字，有错误抛出，支持小数点和百分号
/// @param str 输入字符串
/// @return 目标数
double strToDob(string str) {
    double
        res = 0,
        digit = 0,
        is正 =
            1;  //一个存放结果，一个存放由符号带来的进位问题，一个存放正负信息
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] <= '9') && (str[i] >= '0')) {
            res += (double)(str[i] - '0') * pow(10, str.length() - i - 1);
        } else if (str[i] == '%') {
            digit += 2;
        } else if (str[i] == '.') {
            digit += str.length() - i - 1;
        } else if (str[i] == '-') {
            is正 = -1;
        } else {
            throw "Unknown signal：" + str;
        }
    }
    res = is正 * res * pow(0.1, digit);
    return res;
    //我的妈，写完我才想起来可以用sscanf()，但不知道能不能识别%
}

/// @brief 冒泡排序，将目标数组从小到大重排，优点是复杂度为O(n)到O(n^2)
/// @param arr 目标数组
void bubbleSort(vector<int>& arr) {
    int i = 0;
    for (bool j = true; j;) {
        j = false;
        for (i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) {  //两变量交换
                arr[i] += arr[i - 1];
                arr[i - 1] = arr[i] - arr[i - 1];
                arr[i] -= arr[i - 1];
                j = true;
            }
        }
    }
}

/// @brief
/// 封装迭代器，c++真的好麻烦🤢，auto其实没typescript的any好使；
/// @param call_back 迭代函数
/// @param seq
/// 由bubbleSortRank(_target)生产的排序数组（感觉这里可以写一个seq不存在的重载，forEachBySort内部进行排序，但编写排序标志就比较困难了，没思路了！）
/// @param target 被排序数组，操作数组
template <class Callback, class Item>
void forEachBySort(Callback call_back, const vector<int>& seq,
                   const Item target) {
    for (int i = 0; i < target.size(); i++) call_back(target[seq[i]], i);
}

/// @brief
/// 冒泡排序，将目标数组的下标存入另一个数组，该数组按照目标数组元素的大小从大到小重排，优点是复杂度为O(n)到O(n^2)
/// @param arr 目标数组
template <class T>
void bubbleSortRank(const vector<T>& _arr, vector<int>& res) {
    int i;
    vector<int> arr(_arr);
    for (int ii = 0; ii < arr.size(); ii++) res.push_back(ii);  //初始化rank
    for (bool j = true; j;) {
        j = false;
        for (i = 1; i < arr.size(); i++) {
            if (arr[i] > arr[i - 1]) {  //两变量交换并交换排序
                tSwap(&arr[i], &arr[i - 1]);
                tSwap(&res[i], &res[i - 1]);
                j = true;
            }
        }
    }
    vector<int>().swap(arr);  //释放临时数组
}

/// @brief !num 通过尾调用实现阶乘，坏处是可能会造成引用栈溢出
double 阶乘(double i) {
    if (i == 1) {
        return 1;
    } else {
        return i * 阶乘(i - 1);
    }
}

/// @brief 递归法生成二项式系数 $ c^k_n $
/// @param n
/// @param k
int 二项式(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    else
        return 二项式(n - 1, k - 1) + 二项式(n - 1, k);
}

/// @brief 判断字母，不区分大小写，无依赖
bool isABC(char a) { return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'); }

/// @brief 随机生成数组元素
void randomInitArr(vector<int>& arr, int size) {
    int _size = 10, min = 0, max = 100,
        temp;  //设定随机生成数组的大小，随机数上下限
    random_device seed;       //硬件生成随机数种子
    ranlux48 engine(seed());  //利用种子生成随机数引擎
    uniform_int_distribution<> distrib(min,
                                       max);  //设置随机数范围，并为均匀分布
    for (int i = 0; i < size; i++) arr.push_back(distrib(engine));
}