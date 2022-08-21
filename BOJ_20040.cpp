#include <cstdio>

typedef unsigned int u32;

template<typename T>
class Node
{
public:
    Node() : val((T)NULL) { parent = this; }
    Node(T _val) : val(_val) { parent = this; }
    T& at() { return val; }
    Node* find();
    void merge(Node& node);
private:
    T val;
    Node* parent;
};

template<typename T>
Node<T>* Node<T>::find()
{
    if(parent == this) return this;
    else               return parent = (*parent).find();
}

template<typename T>
void Node<T>::merge(Node& node)
{
    (*node.find()).parent = find();
    node.find();
}

int main()
{
    u32 n, m;
    u32 result = 0;
    bool flag = true;

    scanf(" %u %u", &n, &m);

    Node<u32>* arr = new Node<u32>[n];

    for(u32 i = 0; i < m; i++)
    {
        u32 u, v;
        
        scanf(" %u %u", &u, &v);

        if(flag && arr[u].find() != arr[v].find())
        {
            arr[u].merge(arr[v]);
        }
        else if(flag)
        {
            result = i + 1;
            flag = false;
        }
    }

    printf("%u\n", result);
}