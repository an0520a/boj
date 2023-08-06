#include <cstdio>

unsigned int MbtiToCode(const char* __str)
{
    unsigned int result = 0;

    if (__str[0] == 'E') result |= 0b1000;
    if (__str[1] == 'N') result |= 0b0100;
    if (__str[2] == 'F') result |= 0b0010;
    if (__str[3] == 'P') result |= 0b0001;

    return result;
}

unsigned int GetMbtiCodeDistance(unsigned int __code1, unsigned int __code2)
{
    unsigned int result = 0;
    unsigned int code_xor = __code1 ^ __code2;

    if (code_xor & 0b1)     result++;
    if (code_xor & 0b10)    result++;
    if (code_xor & 0b100)   result++;
    if (code_xor & 0b1000)  result++;

    return result;
}

int main()
{
    size_t T;

    scanf(" %lu", &T);

    for (size_t i = 0; i < T; i++)
    {
        size_t N;
        size_t available_mbti_arr_size = 0;
        size_t min_distance = __SIZE_MAX__;
        size_t mbti_exist_arr[16] = { 0 };
        char buf[6];
        bool end_flag = false;

        scanf(" %lu", &N);

        if (N > 32)
        {
            scanf("%*[^\n]");
            scanf("%*c");

            min_distance = 0;
            end_flag = true;
        }

        if (end_flag == false)
        {
            for (size_t i = 0; i < N; i++)
            {
                scanf(" %s", buf);

                unsigned int code = MbtiToCode(buf);

                mbti_exist_arr[code]++;

                if (mbti_exist_arr[code] >= 3)
                {
                    min_distance = 0;
                    end_flag = true;
                }
            }
        }

        if (end_flag == false)
        {
            unsigned int available_mbti_arr[32];

            for (size_t i = 0; i < 16; i++)
            {
                available_mbti_arr_size += mbti_exist_arr[i];            
            }

            for (size_t i = 0, k = 0; i < 16; i++)
            {
                for (size_t j = 0; j < mbti_exist_arr[i]; j++)
                {
                    available_mbti_arr[k] = i;
                    k++;
                }            
            }

            for (size_t i = 0; i < available_mbti_arr_size; i++)
            {
                for (size_t j = i + 1; j < available_mbti_arr_size; j++)
                {
                    for (size_t k = j + 1; k < available_mbti_arr_size; k++)
                    {
                        size_t pre_distance = 0;

                        pre_distance += GetMbtiCodeDistance(available_mbti_arr[i], available_mbti_arr[j]);
                        pre_distance += GetMbtiCodeDistance(available_mbti_arr[j], available_mbti_arr[k]);
                        pre_distance += GetMbtiCodeDistance(available_mbti_arr[k], available_mbti_arr[i]);

                        min_distance = (min_distance < pre_distance)? min_distance : pre_distance;
                    }
                }
            }
        }

        printf("%lu\n", min_distance);
    }
}