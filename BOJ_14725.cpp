#include <cstdio>
#include <string>
#include <vector>
#include <map>

typedef unsigned int u32;

using namespace std;

class Node
{
public:
    Node(const string& _str, u32 _depth = 0) : str(_str), par(nullptr), depth(_depth) {}
    ~Node() { for (auto iter = childMap.begin(); iter != childMap.end(); iter++) delete (*iter).second; }
    void insert(const string& str);
    Node* find(const string& str) const;
    void rootInOrder() const;
    void inOrder() const;

    string str;
    u32 depth;
    map<string, Node*> childMap;
    Node* par;
};

void Node::insert(const string& str) { childMap.insert({str, new Node(str, depth + 1)}); }
Node* Node::find(const string& str) const { return (*childMap.find(str)).second; }
void Node::rootInOrder() const { for (auto iter = childMap.begin(); iter != childMap.end(); iter++) (*(*iter).second).inOrder(); }
void Node::inOrder() const
{
    for (u32 i = 1; i < depth; i++) printf("--");
    printf("%s\n", str.c_str());
    for (auto iter = childMap.begin(); iter != childMap.end(); iter++) (*(*iter).second).inOrder();
}

int main()
{
    u32 N;
    Node* root = new Node("root");

    scanf(" %u", &N);

    while(N--)
    {
        u32 K;
        char tmpStr[16];
        Node* pre = root;

        scanf(" %u", &K);

        while(K--)
        {
            string str;

            scanf(" %s", tmpStr);

            str = tmpStr;
            (*pre).insert(str);
            pre = (*pre).find(str);
        }
    }

    (*root).rootInOrder();
}