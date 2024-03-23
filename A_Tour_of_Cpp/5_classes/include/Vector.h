class Vector
{
public:
    Vector(int s) : elem{new double[s]}, sz(s) {}
    double &operator[](int i) { return elem[i]; }
    int size() const { return sz; }

private:
    double *elem;
    int sz;
};

class Container
{
public:
    virtual double &operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};

class Vector_container : public Container
{
public:
    Vector_container(int s) : v(s) {}
    ~Vector_container() {}

    double &operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }

private:
    Vector v;
};