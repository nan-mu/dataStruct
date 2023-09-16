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
	Node *head;	 //指向链表开头
	// 本来这里有一个opt用来当作中间变量，但第二题略有负责，所以使用中间变量可能会导致作用域污染，所以删掉了
	Node *tail;	 //指向链表结尾
	Node *now;	 //用于表示迭代器操作对象
	int length;
	void first_push(char data) {
		head = (Node *)malloc(sizeof(Node));
		head->data = data;
		tail = head;
		now = head;
	}

  public:
	NodeLink() {  //初始化链表
		head = nullptr;
		tail = nullptr;
	}
	~NodeLink() {
		now = nullptr;
		while (pop())
			;
		head = nullptr;
		tail = nullptr;
	}
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
		Node *opt = head;
		get_length();
		if (index > length) return false;  //或许，这里应该用断言？
		for (int i = index - 1; i > 0; i--) opt = opt->next;  //找到操作位置
		char temp = data;

		for (int i = length - index + 1; i > 0; i--) {	//开始插入并移动
			tSwap(&temp, &(opt->data));
			opt = opt->next;
		}
		push(temp);	   //更新尾端并放置最后一个数据
		get_length();  //更新长度

		return true;
	};

	bool deleteE(int index) {  //通过引索插入
		Node *opt = head;
		get_length();
		if (index > length) return false;  //或许，这里应该用断言？
		for (int i = index - 1; i > 0; i--) opt = opt->next;  //找到操作位置
		char temp = opt->data;
		// for (; opt->next != nullptr; opt = opt->next) {	 //开始插入并移动
		// 	tSwap(&(opt->next->data), &(opt->data));
		// }
		while (opt->next != nullptr) {
			tSwap(&(opt->next->data), &(opt->data));
			opt = opt->next;
			if (opt->next == tail) {
				tSwap(&(opt->next->data), &(opt->data));
				free(tail);	 //删除
				tail = opt;	 //更新尾巴
				tail->next = nullptr;
			}
		}

		get_length();  //更新长度

		return true;
	};

	bool print() {	// 打印链表
		Node *opt;
		for (opt = head; opt != nullptr; opt = opt->next) {
			printf("%c ", opt->data);
		}
		printf("\n");
		opt = nullptr;
		return true;
	}

	int get_length() {	// 计算长度
		int len = 0;
		for (Node *opt = head; opt != nullptr; opt = opt->next) len++;
		length = len;
		return len;
	}

	bool is_empty() {  //判断是否为空
		get_length();
		return get_length() ? true : false;
	}

	Node *find(char element) {	//返回位置假设元素不重复
		for (Node *opt = head; opt != tail; opt = opt->next)
			if (opt->data == element) return opt;

		return nullptr;	 //找不到情况返回空指针
	}

	inline bool pop() {	 //从头开始删除
		if (head == tail) {
			tail = nullptr;
			free(head);
			head = nullptr;
			printf("clean");
			return 0;
		} else {
			if (head == now) now = head->next;
			Node *opt = head;
			head = opt->next;
			free(opt);
			opt = nullptr;
			return true;
		}
	}

	char print(int index) {	 //打印单个数据
		assert(index < length);
		Node *opt = head;
		for (int i = index - 1; i > 0; i--) opt = opt->next;  //找到操作位
		return opt->data;
	}
};

// int main() {
// 	NodeLink h;
// 	h.push('a');
// 	h.push('b');
// 	h.push('c');
// 	h.push('d');
// 	h.push('e');
// 	h.print();
// 	printf("h length: %d\n", h.get_length());
// 	printf(h.is_empty() ? "有的\n" : "空的\n");
// 	printf("%c\n", h.print(3));
// 	printf("%p\n", h.find('a'));
// 	h.push('/', 4);
// 	h.print();
// 	h.deleteE(3);
// 	h.print();
// 	return 0;
// }
