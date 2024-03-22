#include <iostream>

class Vector
{
public:
    Vector(int s) : elem{
                        new double[s]},
                    sz{s} {}
    double &operator[](int i) { return elem[i]; }
    int size() { return sz; }

private:
    double *elem;
    int sz;
};

int main()
{
    Vector v {3};
    std::cin >> v[2];
    std::cout << v[2] << " " << v.size() << std::endl;
}