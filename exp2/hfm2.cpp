#include <iostream>
#include <string>
using namespace std;
#define ElemType int

class HfmTree;

typedef struct hfmTNode {
    ElemType element;           //结点的数据域
    int w;                      //结点的权值
    struct hfmTNode* lChild;    //结点的左孩子指针
    struct hfmTNode* rChild;    //结点的右孩子指针
}HFMTNode;

class BTNode
{
public:
    BTNode()
    {
        lChild = rChild = parent = NULL;
    }
    BTNode(const ElemType& x, char& q)
    {
        element = x;
        lChild = rChild = parent = NULL;
        ch = q;
    }
    BTNode(const ElemType& x, char& q, BTNode* l, BTNode* r)
    {
        element = x;
        lChild = l;
        rChild = r;
        ch = q;
        parent = NULL;
    }
    ElemType element;
    BTNode* lChild, * rChild, * parent;
    string num;     // 储存路径编码，用string不用担心大小问题
    char ch;        // 储存字符
};

void Print(ElemType& x)
{
    cout << x << " ";
}

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    bool IsEmpty() const;
    void Clear() { }             // 移去所有结点，成为空二叉树
    bool Root(ElemType& x) const;      // 若二叉树不空，则x为根的值，并返回true，否则返回false
    void MakeTree(const ElemType& x, char c, BinaryTree& left, BinaryTree& right);                        // 建树
    void BreakTree(ElemType& x, BinaryTree& left, BinaryTree& right);
    void PreOrder(void (*Visit) (ElemType& x));
    void InOrder(void (*Visit) (ElemType& x));
    void PostOrder(void (*Visit) (ElemType& x));
    int CountNode();             // 计算二叉树的结点个数
    void PrintHfm();             // 输出二叉树的前序和中序遍历
protected:
    BTNode* root;
private:
    void PreOrder(void (*Visit) (ElemType& x), BTNode* t);
    void InOrder(void (*Visit) (ElemType& x), BTNode* t);
    void PostOrder(void (*Visit) (ElemType& x), BTNode* t);
    int CountNode(BTNode* t); // 计算结点数量
};

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::~BinaryTree()
{
    Clear();
}

bool BinaryTree::IsEmpty() const
{
    return root == NULL;
}

bool BinaryTree::Root(ElemType& x) const
{
    if (root) {
        x = root->element;
        return true;
    }
    else
        return false;
}

void BinaryTree::MakeTree(const ElemType& x, char c, BinaryTree& left, BinaryTree& right)
{
    if (root || &left == &right) {
        std::cout << "MakeTree fail!" << endl;
        return;
    }
    root = new BTNode(x, c, left.root, right.root);
    left.root = right.root = NULL;
}

void BinaryTree::BreakTree(ElemType& x, BinaryTree& left, BinaryTree& right)
{
    if (!root || &left == &right || left.root || right.root) {
        cout << "BreakTree failed!" << endl;
        return;
    }
    else {
        x = root->element;
        left.root = root->lChild;
        right.root = root->rChild;
        delete root;
        root = NULL;
        //this->parent = NULL;
    }
}

void BinaryTree::PreOrder(void (*Visit) (ElemType& x))
{
    PreOrder(Visit, root);
}

void BinaryTree::InOrder(void (*Visit) (ElemType& x))
{
    InOrder(Visit, root);
}

void BinaryTree::PostOrder(void (*Visit) (ElemType& x))
{
    PostOrder(Visit, root);
}

int BinaryTree::CountNode()
{
    return CountNode(root);
}

void BinaryTree::PreOrder(void (*Visit) (ElemType& x), BTNode* t)
{
    if (t) {
        Visit(t->element);
        PreOrder(Visit, t->lChild);
        PreOrder(Visit, t->rChild);
    }
}

void BinaryTree::InOrder(void (*Visit) (ElemType& x), BTNode* t)
{
    if (t) {
        InOrder(Visit, t->lChild);
        Visit(t->element);
        InOrder(Visit, t->rChild);
    }
}

void BinaryTree::PostOrder(void (*Visit) (ElemType& x), BTNode* t)
{
    if (t) {
        PostOrder(Visit, t->lChild);
        PostOrder(Visit, t->rChild);
        Visit(t->element);
    }
}

int BinaryTree::CountNode(BTNode* t)
{
    if (t) {
        return CountNode(t->lChild) + CountNode(t->rChild) + 1;
    }
    else
        return 0;
}

// 输出哈夫曼树的前序和中序遍历
void BinaryTree::PrintHfm()
{
    cout << "先序遍历哈夫曼树:" << endl;
    PreOrder(Print);
    cout << endl;
    cout << "中序遍历哈夫曼树:" << endl;
    InOrder(Print);
    cout << endl;
}


class HfmTree :public BinaryTree
{
public:
    operator ElemType () const
    {
        return weight;
    }
    ElemType GetWeight()
    {
        return weight;
    }
    void SetWeight(const ElemType& x)
    {
        weight = x;
    }
    void SetNull()
    {
        root = NULL;
    }
    void Code();                                    // 根据输入的字符输出编码
    void DeCode() { DeCode(root); cout << endl; }   // 根据输入的编码输出字符
    void Create_code() { Create_code(root); }       // 写入路径编码
    void Conn_parent() { Conn_parent(root); }       // 令parent指向上级结点
    void test() { testprint(root); }                // 测试，输出字符对应的编码
private:
    void Create_code(BTNode* t);
    void DeCode(BTNode* q);
    void Conn_parent(BTNode* t);
    ElemType weight;
    void Code(BTNode* t, char a);
    void testprint(BTNode* t);
};

class PriQueue
{
private:
    HfmTree* hfmQueue;
    int n, maxSize;
public:
    PriQueue(int mSize = 100);
    ~PriQueue() { delete[]hfmQueue; }
    bool IsEmpty() const { return n == 0; }
    bool IsFull() const { return n == maxSize; }
    void Append(const HfmTree& x);
    void Deal(HfmTree& x);
    void print();
    void AdjustDown(int r);
    void AdjustUp(int j);
};

PriQueue::PriQueue(int mSize)
{
    maxSize = mSize;
    n = 0;
    hfmQueue = new HfmTree[maxSize];
}

void PriQueue::Append(const HfmTree& x)
{
    if (IsFull()) {
        cout << "The PriQueue is full!" << endl;
    }
    hfmQueue[n++] = x;
    AdjustUp(n - 1);
}

void PriQueue::Deal(HfmTree& x)
{
    if (IsEmpty()) {
        cout << "The PriQueue is Empty!" << endl;
    }
    x = hfmQueue[0];
    hfmQueue[0] = hfmQueue[--n];
    AdjustDown(0);
}

void PriQueue::print()
{
    for (int i = 0; i < n; i++) {
        cout << hfmQueue[i] << " " << endl;
    }
}

void PriQueue::AdjustDown(int r)
{
    int Child = 2 * r + 1;
    HfmTree temp = hfmQueue[r];
    while (Child < n) {
        if (Child + 1 < n && hfmQueue[Child + 1] < hfmQueue[Child]) {
            Child++;
        }
        if (temp > hfmQueue[Child]) {
            hfmQueue[r] = hfmQueue[Child];
            r = Child;
            Child = 2 * Child + 1;
        }
        else {
            break;
        }

    }
    hfmQueue[r] = temp;
}

void PriQueue::AdjustUp(int j)
{
    HfmTree temp = hfmQueue[j];
    int i = j;
    while (i > 0 && temp < hfmQueue[(i - 1) / 2]) {
        hfmQueue[i] = hfmQueue[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    hfmQueue[i] = temp;
}



// 打印出所有的结点的权值以及对应的字符
void HfmTree::testprint(BTNode* t)
{
    static int u = 0;
    if (t)
    {
        cout << t->num << " " << t->ch << " " << u++ << endl;
        testprint(t->lChild);
        testprint(t->rChild);
    }
}

// 由输入的字符输出相应的编码
void HfmTree::Code()
{
    cout << "请输入要编码的字符串:" << endl;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        Code(root, s[i]);
    }
    cout << endl;
}

// 由输入的编码输出相应的字符
void HfmTree::DeCode(BTNode* q)
{
    cout << "请输入二进制编码(0和1的组合):" << endl;
    string n;
    cin >> n;
    BTNode* t = q;
    int count = n.length();
    for (int i = 0; i < count; i++) {
        if (n[i] == '0' && t->lChild->ch != '*') {
            cout << t->lChild->ch;
            t = q;
        }
        else if (n[i] == '1' && t->rChild->ch != '*') {
            cout << t->rChild->ch;
            t = q;
        }
        else if (n[i] == '0' && t->lChild != NULL) {
            t = t->lChild;
        }
        else if (n[i] == '1' && t->rChild != NULL) {
            t = t->rChild;
        }
        else {
            cout << "Decode fail!";
            return;
        }
    }
}

// 把空的parent指针指向每个节点的父级指针
void HfmTree::Conn_parent(BTNode* t)
{
    if (t) {
        if (t->lChild != NULL) {
            t->lChild->parent = t;
        }
        if (t->rChild != NULL) {
            t->rChild->parent = t;
        }
        Conn_parent(t->lChild);
        Conn_parent(t->rChild);
    }
}

void HfmTree::Code(BTNode* t, char a)
{
    if (t) {
        if (t->ch == a) {
            cout << t->num;
        }
        Code(t->lChild, a);
        Code(t->rChild, a);
    }
}
// 用遍历把路径保存在字符串num里
void HfmTree::Create_code(BTNode* t)
{
    if (t) {
        if (t->parent != NULL) {
            if (t == t->parent->lChild) {
                t->num = t->parent->num + '0';
            }
            else if (t == t->parent->rChild) {
                t->num = t->parent->num + '1';
            }
            else
                cout << "Creat_code Error!" << endl;
        }
        Create_code(t->lChild);
        Create_code(t->rChild);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="weight">权值数组</param>
/// <param name="charArr">名称数组</param>
/// <param name="size">节点数量</param>
/// <returns></returns>
HfmTree CreateHfmTree(ElemType weight[], char charArr[], int size)
{
    PriQueue pQ(size);
    HfmTree x, y, z;
    for (int i = 0; i < size; i++) {
        z.MakeTree(weight[i], charArr[i], x, y);
        z.SetWeight(weight[i]);
        pQ.Append(z);
        z.SetNull();
    }
    for (int i = 1; i < size; i++) {
        pQ.Deal(x);
        pQ.Deal(y);
        z.MakeTree(x.GetWeight() + y.GetWeight(), '*', x, y); // *用于区别叶子和普通结点
        z.SetWeight(x.GetWeight() + y.GetWeight());
        pQ.Append(z);
        z.SetNull();
    }
    pQ.Deal(z);
    return z;
}

// 6
// ABCDEFG
// 9 11 13 3 5 12
int main()
{
    cout << "请输入需要编码的字符数量:" << endl;
    int size;                          // 需要编码的字符数量
    cin >> size;

    cout << "请输入所要编码的字符:" << endl;
    char* charArr = new char[size + 1];      // 储存字符
    cin >> charArr;

    cout << "请输入对应字符的权值:" << endl;
    int* weightArr = new int[size + 1];        // 储存权值
    for (int i = 0; i < size; i++) {
        cin >> weightArr[i];
    }

    HfmTree hfmTree = CreateHfmTree(weightArr, charArr, size);
    hfmTree.Conn_parent();
    hfmTree.Create_code();
    //a.test();                     
    while (1) {
        cout << endl;
        cout << "请输入功能" << endl;
        cout << "1. 编码" << endl;
        cout << "2. 解码" << endl;
        cout << "3. 显示哈夫曼树(先序遍历+后序遍历)" << endl;
        cout << "4. 退出" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            hfmTree.Code();
            break;
        case 2:
            hfmTree.DeCode();
            break;
        case 3:
            hfmTree.PrintHfm();
        case 4:
            return 0;
        }
    }
    system("pause");   // 在vs上编译运行需要的暂停函数
    return 0;
}
