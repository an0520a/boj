#include <cstdio>
#include <cstring>

typedef unsigned int u32;

int main()
{
    u32 T;
    scanf(" %u", &T);

    char f[100100];
    char arr_s[700100];

    while(T--)
    {
        char* fp = f;
        char * arr_s_p = arr_s;
        u32 n;
        char** arr;
        bool rev = false;
        bool err = false;

        int front, back;
        u32 s = 0, t = 0;

        scanf(" %s", f);
        scanf(" %u", &n);
        scanf(" %s", arr_s);

        arr = new char*[n];
        for(u32 i = 0; i < n; i++) { arr[i] = new char[5]{ 0 }; }

        while (*arr_s_p)
        {
            if (*arr_s_p >= '0' && *arr_s_p <= '9')
            {
                arr[s][t] = *arr_s_p;
                t++;
            }
            else if(*arr_s_p == ',')
            {
                s++;
                t = 0;
            }

            arr_s_p++;
        }

        front = 0; back = n - 1;

        while (*fp)
        {
            if (*fp == 'R')
            {
                rev = !rev;
            }
            else
            {
                if (rev) { back--; }
                else     { front++; }
            }

            if (front == back + 2) { err = true; break; }

            fp++;
        }

        if (err) printf("error\n");
        else
        {
            if (front == back + 1)
            {
                printf("[]\n");
            }
            else
            {
                printf("[");
                if(rev == false)
                {
                    for(int i = front; i < back; i++)
                    {
                        printf("%s,", arr[i]);
                    }
                    printf("%s", arr[back]);
                }
                else
                {
                    for(int i = back; i > front; i--)
                    {
                        printf("%s,", arr[i]);
                    }
                    printf("%s", arr[front]);
                }
                printf("]\n");
            }
        }

        for(u32 i = 0; i < n; i++) delete[] arr[i];
        delete[] arr;
    }
}