# Templates

## Introduction
- Someone who wants a vector is unlikely always to want a vector of `double`s
    - Vector is a general concept; its element type should be represented independently!
- ___Template___
    - A class or a function that we parameterize with a set of types or values.

## Parameterized Types
- We can generalize like this:
```cpp
template <typename T>
class Vector {
    private:
        T* elem;
        int sz;
    public:
        ...
        T& operator[](int i);
        const T& operator[](int i) const;
}

Vector<char> vc(200);
Vector<std::string> vs(17);
```
- `template <typename T>` prefix makes __T__ a type parameter of the declaration it prefixes
    - "for all types T"
- Templates are _compile-time_ mechanism -- so there is no added run-time overhead!
- _Instantiation_ / _Specialization_
    - A template plus a set of template arguments
    - Late in compilation, at _instantiation time_, code is generated for each UNIQUE instantiation used in a program
- Constrained Templated Arguments
    - For our Vector, we just not want any __T__, but we want a copyable __T__!
    - __Concept__
        - `template<Element T>` below means "for all T such that Element(T)". 
        - Element is a _predicate_ that checks whether T has all the properties that a Vector requires!
            - compile-time error if it does not hold
    ```cpp
    template<Element T> // template-argument T is called "constrained argument"
    class Vector { // template for which its argument is constraned is called "constrained template"
        private:
            T* elem;
            ...
    }
    ```
- Value Template Arguments
    - A template can also take value arguments
    ```cpp
    template<typename T, int N>
    struct Buffer {
        constexpr int size() { return N; }
        T elem[N];
    }
    Buffer<char, 1024> glob;
    Buffer<int, 10> a;
    ```
- Template Argument Deduction
    - Template arguments can be often deduced from an initializer
    ```cpp
    pair p = {1, 5.2}; // std::pair<int, double>

    template<typename T>
    class Vector {
        ...
        Vector(std::initializer_list<T>);
    }
    Vector v = {1, 2, 3}; // v is Vector<int>
    Vector v2 = v; // v2 is Vector<int> deduced from v
    ```

## Parameterized Operations
- Three ways of expressing an operation parameterized by types or values
    - A function template
    - A function object
        - an object that can carry data and be called like a function
    - A lambda expression 
        - a shorthand for a function object
- Function Template
    - A function template can be a member function, but not a __virtual__ member
```cpp
template<typename S, typename V>
V sum(const S& s, V v)
{
    for (const auto& x : s)
        v+=x;
    return v;
}
```
- Function Objects
    - Function Object / Functor
        - Objects that can be called like functions
        - Function objects are widely used as arguments to algorithms
    - Advantage
        - The beauty of these is that they carry the value to be compared against with them (for this example).
        - Simple function object can be often times inlined too so a call of Less_than is far more efficient than an indirect function call.
    ```cpp
    template<typename T>
    class Less_than {
        const T val;
        public:
            ...
            // application operator
            bool operator()(const T& x) const { return x < val; }
    }

    template<typename C, typename P>
    int count(const C& c, P pred)
    {
        int cnt = 0;
        for (const auto& x : c)
            if (pred(x))
                ++cnt;
        return cnt;
    }
    ```
- Lambda Expressions
    - In above, we had to define a class Less_than separately from its use.
        - This can be very tedious!
    - Lambda Expression allows you to implicitly generate function objects
    ```cpp
    count(vec, [&](int a){ return a < x; })
    ```
    - `[]` is called _capture list_
        - `[&]` specifies that all local names used in the lambda body will be accessed through references
        - `[=]` captures all local names used by value
        - `[]` captures nothing
        - `[this]` captures current object by reference (if lambda is defined within a member func). `[*this]` copies current object
        - `[a, b, ...]` captures a and b specifically
    - We can make a _generic lambda_ too by having it take in an argument of type `auto` meaning value of any type is acceptable as initializer.
        - Can use concept to add constraints to this input type
    ```cpp
    [](auto& s){ s -> do_fct(); }
    ```
    - Lambda allows you to convert any statement into an expression. If you have a complicated switch statement with different cases, lambda lets you do it this way:
    ```cpp
    vector<int> v = [&] {
        switch(m) {
            case a: return 0;
            case b: return 1;
            ...
        }
    }();
    ```
    - Finally
        - What if we need to perform some cleanup that is not associated with a single object or with an object that does not have a destructor? We can define an action to be taken using lambda expression!
        ```cpp
        template<typename F>
        [nodiscard] auto finally(F f)
        {
            return Final_action(f);
        }
        auto act = finally([&]{ free_some_stuff(); })
        ```
        - When act goes out of scope, its ~Final_action() will invoke f!

## Template Mechanisms
- Variable Templates
    - Defines a family of variables or static data members
```cpp
template<typename T>
constexpr T pi = T(3.1415926535897932385L); // variable template
 
template<typename T>
T circular_area(T r) // function template
{
    return pi<T> * r * r; // pi<T> is a variable template instantiation
}
```
- Aliases
    - It is useful to introduce a synonym for a type or a template
    ```cpp
    using size_t = unsigned int
    ```
    - The actual type might be implementation dependent (it could be unsigned long!)
        - Helps you write portable code
    - It is common for a parameterized type to provide an alias for types related to their template arguments
    ```cpp
    template<typename T>
    class Vector {
        public: 
            using value_type = T; // every std container provides value_type as the name for the type of its elements!
    }
    ```
    - Then, we can write something like
    ```cpp
    template<typename C>
    using Value_type = C::value_type;

    template<typename Container>
    void algo(Container& c)
    {
        Vector<Value_type<Container>> vec;
        ...
    }
    ```
    - You can also use aliasing to do a partial specialization
    ```cpp
    template<typename Key, typename Value> 
    class Map {

    }

    template<typename Value>
    using String_map = Map<string, Value>;

    String_map<int> m; // Map<string, int>!
    ```
- Compile-Time if
    - Consider writing an operation that can be implemented using one of two functions.
    - `if constexpr`
        - only the selected branch of this expression is checked by the compiler
            - provides alternative implementations without run-time overhead
        ```cpp
        template<typename T>
        void a(T& target)
        {
            if constexpr(is_trivially_copyable_v<T>)
                do_a();
            else 
                do_b();
        }
        ```