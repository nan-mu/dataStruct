#include <assert.h>

#include <cstdio>
#include <cstdlib>

using namespace std;

/// @brief 交换两变量
template <class T>
void tSwap(T *p1, T *p2) {
	T temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

typedef struct Node {  // 数据节点类
	Node *next;
	char data;
} Node;

class NodeLink {
  private:
	Node *head;	 //指向队开头
	Node *tail;	 //操作对象（队尾）
	int length;

  public:
	NodeLink() {  //初始化链表
		head = nullptr;
		tail = nullptr;
	}
	~NodeLink() {
		while (pop())
			;
		head = nullptr;
		tail = nullptr;
	}
	bool pop() {
		if (head == tail) {	 //删除最后一项
			free(head);
			head = nullptr;
			tail = nullptr;
			length = 0;
			return false;
		} else {
			tail->next = head->next;
			free(head);
			head = tail->next;
			return true;
		}
	}
	bool push(char data) {
		if (head == nullptr) {
			head = (Node *)malloc(sizeof(Node));
			tail = head;
			head->data = data;
			head->next = head;
			return true;
		} else {
			Node *opt = (Node *)malloc(sizeof(Node));
			opt->data = data;
			tail->next = opt;
			tail = opt;
			opt->next = head;
			return true;
		}
	}
	int get_length() {	// 计算长度
		int len = length ? 1 : 0;
		for (Node *opt = head; opt != tail; opt = opt->next) len++;
		length = len;
		return len;
	}
	void print() {
		Node *opt = head;
		for (int i = get_length(); i > 0; i--) {
			printf("%c ", opt->data);
			opt = opt->next;
		}
		printf("\n");
	}
	void exchange() {}
};