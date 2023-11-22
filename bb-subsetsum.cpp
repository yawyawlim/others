
#include <iostream>
#include <queue>
#include <limits.h>
//子集和数 分支限界

using namespace std;
int N;//集合元素个数
int t;//目标值
int r;//剩余值
int* a = new int[N + 1];//元素数组

class Node {
public:
    int remaining;//数组还可以加的值
    int value;//节点当前的数值
    int priority;//优先级
    int level;//解空间树所在层
    int picked;//是否被选
    Node* parent;
};
Node* leaf = NULL;//叶节点

Node initialize(int level, int value, Node* parent, int remaining) {
    Node newnode;
    newnode.value = value;
    newnode.priority = value;//设优先级数为当前所得到的值
    newnode.level = level;
    newnode.remaining = remaining;
    newnode.parent = parent;
    return newnode;
}

void output() {
    int* result = new int[N + 1];
    if (leaf == NULL) {
        cout << "No Solution Found!";
    }
    else {
        for (int i = N; i > 0; i--) {
            if (leaf->picked == 1) {//选中
                result[i] = 1;
            }
            else result[i] = 0;//不选
            leaf = leaf->parent;//返回父节点
        }
        for (int i = 1; i <= N; i++) {
            cout << result[i] << " ";
        }
    }
    cout << endl;
}

bool operator<(Node a, Node b) {
    return a.priority > b.priority;//当前数值较大的结点优先级越高
}

void bb() {
    Node start;
    start = initialize(0, 0, NULL, r);//初始化起始节点
    priority_queue<Node>heap;//优先队列
    heap.push(start);

    while (!(heap.empty()))
    {
        Node* p = new Node(heap.top());//取头结点
        heap.pop();
        if (p->level == N) {
            if (p->value == t) {
                leaf = p;//定义叶节点
            }
        }
        else {
            if (((p->value + a[p->level + 1]) <= t) && ((p->value + p->remaining) >= t))//左节点
            {
                Node rightnode;
                rightnode = initialize(p->level + 1, p->value + a[p->level + 1], p, p->remaining - a[p->level + 1]);
                rightnode.picked = 1;//node is picked
                heap.push(rightnode);
            }
            if (p->value + p->remaining - a[p->level + 1] >= t) {//右节点
                Node leftnode;
                leftnode = initialize(p->level + 1, p->value, p, p->remaining - a[p->level + 1]);
                leftnode.picked = 0;//node isn't picked
                heap.push(leftnode);
            }
        }
    }
}

void input() {
    r = 0;
    cout << "enter numbers and target: ";
    cin >> N >> t;
    cout << "enter main set: ";
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        r += a[i];//剩余的节点值
    }
}

int main() {
    while (true) {
        input();
        bb();
        output();
        cout << endl;
    }
    //return 0;
}
//分支限界可以用子集树来表示，一旦扩展到叶子节点则可以判定是否得到解。
//扩展到叶子节点需要O(2^N)的时间
/*
test cases:
    N=10 t=5842
    267 493 869 961 1000 1153 1246 1598 1766 1922
    result:0 0 1 1 1 0 1 0 1 0

    N=6 t=22
    1 2 4 8 16 32
    result:0 1 1 0 1 0

    N=10 t=50
    41 34 21 20 8 7 7 4 3 3
    result:0 0 1 0 1 1 1 1 0 1
*/

