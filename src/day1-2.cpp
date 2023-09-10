#include "day1-2.h"

#include <cstdio>

using namespace std;

#define PROJECT_NAME "DAY1"

#include "comFunc.hpp"	// 一些常用的函数

// 思路：
//	首先排序，如果我把排序的代码写出来，也算做完了第一题！
// 	然后差集
// 	最后更新链表，也就是去除不需要的节点

int main() {
	vector<int> rand_data;	// 准备一些随机数

	com_func::randomInitArr(rand_data, 100);

	//  往链表里放入数据
	NodeList lineA, lineB;
	for (vector<int>::iterator iter = rand_data.begin();
		 iter != rand_data.end(); ++iter)
		lineA.push(*iter);
	rand_data.clear();
	com_func::randomInitArr(rand_data, 100);
	for (vector<int>::iterator iter = rand_data.begin();
		 iter != rand_data.end(); ++iter)
		lineB.push(*iter);

	//排序
	lineA.sort();
	lineA.print();
	printf("\n------------------------\n");
	lineB.sort();
	lineB.print();
	printf("\n------------------------\n");

	//做差集
	lineA.diff(lineB);	//显示地做差集，其实可以用重载
	lineA.print();

	return 0;
}