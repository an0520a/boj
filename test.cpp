#include <stdio.h>
#include <stdlib.h>

// 상수
const int constval = 30;

// 초기화되지 않은 전역 변수
int uninitial;

// 초기화된 전역변수
int initial = 30;

// 정적변수
static int staticval = 70;

// 함수
int function()
{
    return 20;
}

int main(int argc, const char* argv[])
{
    int localval1 = 30; // 지역변수 1
    int localval2; // 지역변수 2
    char* arr = (char*)malloc(sizeof(char) * 10); // 동적 할당 변수
    
    /* 포인터 출력 영역 */
    printf("\n");
    printf("Constant Variable Memory Address : %p \n", &constval);
    printf("Uninitialized Variable Memory Address : %p \n", &uninitial);
    printf("Initialized Variable Memory Address : %p \n", &initial);
    printf("Static Variable Memory Address : %p \n", &staticval);
    printf("Function Memory Address : %p \n", function);
    printf("Local Variable 1 Memory Address : %p \n", &localval1);
    printf("Local Variable 2 Memory Address : %p \n", &localval2);
    printf("Dynamic Variable Memory Address : %p \n\n", arr);
    return 0;
}