#include "linkList.h"

#include <cstdio>
#include <cstdlib>

bool NodeList::push(int data) {
	opt = (Node *)malloc(sizeof(Node));
	opt->data = data;
	opt->next = nullptr;
	if (tail != nullptr) {	//创建首个节点的情况
		printf("创建了第一个节点");
		head = opt;
		tail = opt;
		opt = nullptr;
	} else {  //创建后续节点的情况
		printf("创建了一个节点");
		tail->next = opt;
		tail = opt;
		opt = nullptr;
	}
	return true;
}

bool NodeList::pop() {
	if (head == tail) {
		free(head);
		return CLEARD;
	} else {
		opt = head;
		head = opt->next;
		free(opt);
		opt = nullptr;
		return true;
	}
}

bool NodeList::sort() {
	Node *opt2 = nullptr;
	for (opt = head; opt != nullptr; opt = opt->next) {
		for (opt2 = opt; opt2 != nullptr; opt2 = opt2->next) {	//冒泡排序
			if (opt2->next->data < opt2->data) {
				opt2->data += opt2->next->data;
				opt2->next->data = opt2->data - opt2->next->data;
				opt2->data = opt2->next->data;
			}
		}
	}
	return true;
}

bool NodeList::print() {
	for (opt = head; opt != nullptr; opt = opt->next) {
		printf("%d ", opt->data);
	}
	printf("\n");
	return true;
}
