#include <cstdio>

#include "linkList.h"

using namespace std;

#define PROJECT_NAME "DAY1"

#include "comFunc.hpp"	//一些常用的函数

int main() {
	vector<int> rand_data;	// 准备一些随机数

	com_func::randomInitArr(rand_data, 100);

	//  往链表里放入数据
	NodeList line;
	for (vector<int>::iterator iter = rand_data.begin();
		 iter != rand_data.end(); ++iter)
		line.push(*iter);

	//排序
	line.sort();

	// 输出
	line.print();

	// 删除
	while (line.pop()) {
	}
	return 0;
}