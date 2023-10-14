#include <iostream>
#include <queue>
using namespace std;

void reverseQueue(queue<int>& q) {
    if (q.empty()) {
        return;
    }
    int front = q.front();
    q.pop();
    reverseQueue(q);
    q.push(front);
}

int main() {
    int w = 10;
    queue<int> q;

    // 倒置前
    cout << "倒置前：";
    for (int i = 1; i <= w; i++) {
        q.push(i);
        cout << q.back() << " ";
    }
    cout << endl;

    // 倒置
    reverseQueue(q);

    // 倒置后
    cout << "倒置后：";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    return 0;
}
