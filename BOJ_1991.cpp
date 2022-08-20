#include <stdio.h>
#include <assert.h>
#include <vector>

template <typename T>
class BinaryTree;

template <typename T>
class Node
{
public:
    Node(const T& _val = (T)NULL);
private:
    T val;
    Node* par;
    Node* left;
    Node* right;
    friend class BinaryTree<T>;
};

template <typename T>
Node<T>::Node(const T& _val) : val(_val), par(nullptr), left(nullptr), right(nullptr) {}

template <typename T>
class BinaryTree
{
public:
    BinaryTree();
    
    class Position
    {
    public:
        Position(Node<T>* _node = nullptr) : node(_node) {}
        T& operator*() { return (*node).val; }
        Position left() const { return Position((*node).left); }
        Position right() const { return Position((*node).right); }
        Position par() const { return Position((*node).par); }
        bool isExistPar() const { return (*node).par != nullptr; }
        bool isExistLeft() const { return (*node).left != nullptr; }
        bool isExistRight() const { return (*node).right != nullptr; }
    private:
        Node<T>* node;
        friend class BinaryTree<T>;
    };
    
    void creatRoot(const T& val);
    void insertL(const Position& pos, const T& val);
    void insertR(const Position& pos, const T& val);
    Position root();
    bool empty() { return size == 0; }
    std::vector<T> preorder(Position& pos);
    std::vector<T> inorder(Position& pos);
    std::vector<T> postorder(Position& pos);
private:
    Node<T>* treeRoot;
    size_t size;
};

template <typename T>
BinaryTree<T>::BinaryTree() : treeRoot(nullptr), size(0) {}

template <typename T>
void BinaryTree<T>::insertL(const Position& pos, const T& val)
{
    if(pos.isExistLeft())
    {
        assert(true);
    }
    
    (*pos.node).left = new Node<T>(val);

    size++;
}

template <typename T>
void BinaryTree<T>::insertR(const Position& pos, const T& val)
{
    if(pos.isExistRight())
    {
        assert(true);
    }
    
    (*pos.node).right = new Node<T>(val);

    size++;
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::root()
{
    return Position(treeRoot);
}

template <typename T>
void BinaryTree<T>::creatRoot(const T& val)
{
    if(treeRoot != nullptr)
    {
        assert(true);
    }

    treeRoot = new Node<T>(val);
    
    size++;
}

template <typename T>
std::vector<T> BinaryTree<T>::preorder(Position& pos)
{
    std::vector<T> result;
    std::vector<T> tmp;

    result.push_back(*pos);

    if(pos.isExistLeft())
    {
        auto left = pos.left();
        tmp = preorder(left);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    if(pos.isExistRight())
    {
        auto right = pos.right();
        tmp = preorder(right);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    return result;
}

template <typename T>
std::vector<T> BinaryTree<T>::inorder(Position& pos)
{
    std::vector<T> result;
    std::vector<T> tmp;

    if(pos.isExistLeft())
    {
        auto left = pos.left();
        tmp = inorder(left);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    result.push_back(*pos);

    if(pos.isExistRight())
    {
        auto right = pos.right();
        tmp = inorder(right);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    return result;
}

template <typename T>
std::vector<T> BinaryTree<T>::postorder(Position& pos)
{
    std::vector<T> result;
    std::vector<T> tmp;

    if(pos.isExistLeft())
    {
        auto left = pos.left();
        tmp = postorder(left);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    if(pos.isExistRight())
    {
        auto right = pos.right();
        tmp = postorder(right);
        result.insert(result.end(), tmp.begin(), tmp.end());
    }

    result.push_back(*pos);

    return result;
}

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 N;
    BinaryTree<char>::Position pos_arr[26];
    BinaryTree<char> tree;
    tree.creatRoot('A');
    pos_arr[0] = tree.root();

    scanf(" %u", &N);

    for (u32 i = 0; i < N; i++)
    {
        char par, left, right;
        scanf(" %c %c %c", &par, &left, &right);

        BinaryTree<char>::Position pos = pos_arr[par - 'A'];

        if(left != '.') tree.insertL(pos, left), pos_arr[left - 'A'] = pos.left();
        if(right != '.') tree.insertR(pos, right), pos_arr[right - 'A'] = pos.right();
    }

    vector<char> pre = tree.preorder(pos_arr[0]);
    vector<char> in = tree.inorder(pos_arr[0]);
    vector<char> post = tree.postorder(pos_arr[0]);

    for (u32 i = 0; i < pre.size(); i++)
    {
        printf("%c", pre[i]);
    }

    printf("\n");

    for (u32 i = 0; i < pre.size(); i++)
    {
        printf("%c", in[i]);
    }

    printf("\n");

    for (u32 i = 0; i < pre.size(); i++)
    {
        printf("%c", post[i]);
    }

    printf("\n");
}