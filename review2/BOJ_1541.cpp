#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string line;
    const std::regex kLineRegex(R"(([0-9]+)|([+-]))", std::regex::optimize);
    int sum = 0;
    bool sign_flag = true;

    std::cin >> line;

    std::sregex_iterator iter(line.begin(), line.end(), kLineRegex);
    std::sregex_iterator end;

    while(iter != end)
    {
        const std::smatch& line_match = *iter;
        int val = 0;

        if (line_match[1].matched)                                  val = std::stoi(line_match[1]); // number
        else if (sign_flag && line_match[2].str().front() == '-')   sign_flag = false; //sign

        if (sign_flag == true)  sum += val;
        else                    sum -= val;

        iter++;
    }
    
    std::cout << sum << std::endl;
}