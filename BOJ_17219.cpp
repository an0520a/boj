#include <stdio.h>

typedef unsigned int u32;

size_t mystrlen(char* src);
void mystrcpy(char* dest, char* src);
int mystrcmp(char* dest, char* src);

size_t mystrlen(char* src)
{
    char* p = src;
    size_t len = 0;

    while(*p)
    {
        p++;
        len++;
    }
}

void mystrcpy(char* dest, char* src)
{
    char* dest_p = dest;
    char* src_p = src;

    while(*src_p)
    {
        *(dest_p++) = *(src_p++);
    }

    (*dest_p) = '\0';
}

int mystrcmp(char* dest, char* src)
{
    char* dest_p = dest;
    char* src_p = src;

    while(*dest_p && *src_p)
    {
        if      (*(dest_p) < *(src_p)) return -1;
        else if (*(dest_p) > *(src_p)) return 1;

        dest_p++, src_p++;
    }

    return ((*dest_p == *src_p) ? 0 : ((*dest_p > *src_p) ? 1 : -1));
}

class Node
{
public:
    Node() : next(nullptr) {}
    char str[21] = { 0 };
    char key[21] = { 0 };
    Node* next;
};

class HashTable
{
public:
    HashTable(size_t _prime = 100000);
    ~HashTable() { delete[] table; }
    size_t hashing(char * key);
    void insert(char * key, char * val);
    void erase(char * key);
    char* search(char* key);
private:
    size_t prime;
    Node* table;
};

HashTable::HashTable(size_t _prime) : prime(_prime), table(new Node[_prime]) {}

size_t HashTable::hashing(char * key)
{
    const static unsigned char Sbox[26] = 
    { 0x01, 0x78, 0x69, 0x10, 0x11, 0xB4, 0xE3, 0x23, 0x22, 0x82, 0xA3, 0x14, 0xA7, 0xB5, 0xE6, 0x12, 0x00, 0x21, 0x15, 0x19, 0x24, 0x07, 0xF6, 0x09, 0x20, 0x05 };
    char* p = key;
    size_t i = 0;
    size_t hash = 0;

    while(*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            hash ^= (Sbox[*p - 'A'] ^ Sbox[i]);
        }
        else if (*p >= 'a' && *p <= 'z')
        {
            hash ^= Sbox[*p - 'a'] ^ Sbox[i];
        }
        else if (*p == '-')
        {
            hash ^= 0x1B;
        }
        else
        {
            hash ^= 0x7F;
        }

        hash = (hash << 8) | (hash >> 24);

        p++;
    }

    return hash % prime;
    i = (i + *p) % 26;
}

void HashTable::insert(char * key, char * val)
{
    size_t hash = hashing(key);
    Node* node = &table[hash];

    while((*node).next != nullptr)
    {
        node = (*node).next;
    }

    mystrcpy((*node).key, key);
    mystrcpy((*node).str, val);
    (*node).next = new Node;
}

char* HashTable::search(char* key)
{
    size_t hash = hashing(key);
    Node* node = &table[hash];

    while(node != nullptr)
    {
        if (!mystrcmp((*node).key, key))
        {
            return (*node).str;
        }
        node = (*node).next;
    }

    return nullptr;
}

int main()
{
    HashTable hash_table;
    char web[25];
    char pw[25];

    u32 N, M;
    scanf(" %u %u", &N, &M);

    while(N--)
    {
        scanf(" %s %s", web, pw);
        hash_table.insert(web, pw);
    }

    while(M--)
    {
        scanf(" %s", web);
        printf("%s\n", hash_table.search(web));
    }
}
