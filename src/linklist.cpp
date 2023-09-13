#include <assert.h>

#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct Node {  // 数据节点类
	Node *next;
	char data;
} Node;

class NodeLink {
  private:
	Node *head;	 //指向链表开头
	// 本来这里有一个opt用来当作中间变量，但第二题略有负责，所以使用中间变量可能会导致作用域污染，所以删掉了
	Node *tail;	 //指向链表结尾
	Node *now;	 //用于表示迭代器操作对象
	int length;
	void first_push(char data) {
		head = (Node *)malloc(sizeof(Node));
		tail = head;
		now = head;
	}

  public:
	NodeLink() {  //初始化链表
		head = nullptr;
		tail = nullptr;
	}
	~NodeLink() { now = nullptr; }
	bool push(char data) {	//向末尾插入
		if (head == nullptr)
			first_push(data);
		else {
			Node *opt = (Node *)malloc(sizeof(Node));
			opt->data = data;
			opt->next = nullptr;
			tail->next = opt;
			tail = opt;
			opt = nullptr;
		}
		return true;
	};
	bool push(char data, int index) {  //通过引索插入
		Node *opt;
		get_length();
		if (index > length) return false;  //或许，这里应该用断言？
		for (int index = length - index; index > 0; index--) {
			opt = (Node *)malloc(sizeof(Node));
			opt->data = tail->data;
			tail->next = opt;
			tail = opt;
		};
		return true;
	};
	int get_length() {
		Node *opt;
		int len = 0;
		for (opt = head; opt != nullptr; opt = opt->next) len++;
		opt = nullptr;
		length = len;
		return len;
	}
};

int main() {
	printf("d");
	return 0;
}