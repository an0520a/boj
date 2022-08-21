#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

inline void sqaure_star(char* arr, unsigned int length, unsigned int nl);

int main()
{
	unsigned int n;
	scanf(" %u", &n);
    char *arr = (char *)calloc((n + 1) * n, sizeof(char)); // 크기가 (n + 1) * n

    memset(arr, '*', n * (n + 1)); // 배열을 모두 '*'로 채운다.
	
	sqaure_star(arr, n, n + 1);

	for(unsigned int i = n; i < (n + 1) * n; i += n + 1) arr[i] = '\n';
	arr[n * (n + 1) - 1] = 0;
	printf("%s", arr);

    free(arr);
}

void sqaure_star(char* arr, unsigned int length, unsigned int nl)
{
	if(length == 1){ return; }

	else
	{
		unsigned int new_length = length / 3;

		sqaure_star(arr, new_length, nl);
		sqaure_star(arr + new_length, new_length, nl);
		sqaure_star(arr + new_length * 2, new_length, nl);
		sqaure_star(arr + nl * new_length, new_length, nl);
		for(unsigned int i = 0; i < new_length; i++) memset(arr + nl * (new_length + i) + new_length, ' ', new_length);
		sqaure_star(arr + nl * new_length + new_length * 2, new_length, nl);
		sqaure_star(arr + nl * new_length * 2, new_length, nl);
		sqaure_star(arr + nl * new_length * 2 + new_length, new_length, nl);
		sqaure_star(arr + nl * new_length * 2 + new_length * 2, new_length, nl);
	}
}