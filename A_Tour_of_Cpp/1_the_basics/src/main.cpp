#include <iostream>
#include <string>

void x_3_6()
{
    std::cout << "Type in a bool" << std::endl;
    bool b;
    // std::boolalpha is an I/O manipulator
    std::cin >> std::boolalpha >> b; 
    std::cout << "Type in a char" << std::endl;
    char c;
    std::cin >> c;
    std::cout << "Type in a int" << std::endl;
    int i;
    std::cin >> i;
    std::cout << "Type in a string" << std::endl;
    std::string s;
    std::cin >> s;
    std::cout << b << " " << c << " " << i << " " << s << std::endl;
}

int main(int, char **)
{
    x_3_6();
}
