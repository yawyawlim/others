
#include <iostream>
#include <queue>
#include <limits.h>
//�Ӽ����� ��֧�޽�

using namespace std;
int N;//����Ԫ�ظ���
int t;//Ŀ��ֵ
int r;//ʣ��ֵ
int* a = new int[N + 1];//Ԫ������

class Node {
public:
    int remaining;//���黹���Լӵ�ֵ
    int value;//�ڵ㵱ǰ����ֵ
    int priority;//���ȼ�
    int level;//��ռ������ڲ�
    int picked;//�Ƿ�ѡ
    Node* parent;
};
Node* leaf = NULL;//Ҷ�ڵ�

Node initialize(int level, int value, Node* parent, int remaining) {
    Node newnode;
    newnode.value = value;
    newnode.priority = value;//�����ȼ���Ϊ��ǰ���õ���ֵ
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
            if (leaf->picked == 1) {//ѡ��
                result[i] = 1;
            }
            else result[i] = 0;//��ѡ
            leaf = leaf->parent;//���ظ��ڵ�
        }
        for (int i = 1; i <= N; i++) {
            cout << result[i] << " ";
        }
    }
    cout << endl;
}

bool operator<(Node a, Node b) {
    return a.priority > b.priority;//��ǰ��ֵ�ϴ�Ľ�����ȼ�Խ��
}

void bb() {
    Node start;
    start = initialize(0, 0, NULL, r);//��ʼ����ʼ�ڵ�
    priority_queue<Node>heap;//���ȶ���
    heap.push(start);

    while (!(heap.empty()))
    {
        Node* p = new Node(heap.top());//ȡͷ���
        heap.pop();
        if (p->level == N) {
            if (p->value == t) {
                leaf = p;//����Ҷ�ڵ�
            }
        }
        else {
            if (((p->value + a[p->level + 1]) <= t) && ((p->value + p->remaining) >= t))//��ڵ�
            {
                Node rightnode;
                rightnode = initialize(p->level + 1, p->value + a[p->level + 1], p, p->remaining - a[p->level + 1]);
                rightnode.picked = 1;//node is picked
                heap.push(rightnode);
            }
            if (p->value + p->remaining - a[p->level + 1] >= t) {//�ҽڵ�
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
        r += a[i];//ʣ��Ľڵ�ֵ
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
//��֧�޽�������Ӽ�������ʾ��һ����չ��Ҷ�ӽڵ�������ж��Ƿ�õ��⡣
//��չ��Ҷ�ӽڵ���ҪO(2^N)��ʱ��
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

