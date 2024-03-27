# Pointers and Containers

## Pointers
- Pointer
    - Something that allows us to refer to an object and to access it according to its type
- Types
    - `T*`
        - A built-in pointer type that points to an object of type T
        - Or to a contiguously-allocated sequence of elements of type T
    - `T&`
        - A built-in reference type that refers to an object of type T
        - a pointer with implicit dereference
    - `unique_ptr<T>`
        - An owning pointer to a T
    - `shared_ptr<T>`
        - A pointer to an object of type T and ownership is shared among all shared_ptrs to that T
    - `weak_ptr<T>`
        - A pointer to an object owned by a `shared_ptr<T>`
        - Must be converted to a `shared_ptr<T>` to access its object
    - `span<T>`
        - A pointer to a contiguous sequence of Ts
    - `string_view<T>`
        - A pointer to a const sub-string
- Owning vs non-owning pointer
    - Owning pointer is one that that is responsible for eventually deleting the object it refers to
    - Non-owning pointer (T* or a span) can _dangle_.
        - Point to an invalid location where object used to be
- Guides
    - Containers should be your first choice for resource handles
    - Do not retain a pointer to a local object
        - Returning a pointer from a function, etc.
    - Use owning pointers to objects allocated on the free store
    - Whenevrer you can, use local variables instead
- __unique_ptr__ and __shared_ptr__
    - these two "smart pointers" help manage objects on the free store
    - `unique_ptr` represents unique ownership 
        - its destructor destroys its object
        ```cpp
        std::unique_ptr<X> make_X(int i)
        {
            return std::unique_ptr<X>{new X{i}};
        }
        ```
        - when passing unique_ptrs around, they are _moved_ rather than copied
    - `shared_ptr` represents shared ownership
        - the last shared_ptr's destructor destroys the object
        - shared_ptrs are _copied_ rather than moved.
        - use this only when you have to (i.e., share ownership)
    - use the `make_unique()` and `make_shared()` functions to construct the smart pointers!
    ```cpp
    struct S {
        int i; 
        std::string s;
    }

    auto p1 = std::make_shared<S>{1, "Hello"};
    auto p2 = std::make_unique<S>{2, "World"};
    ```
    - When to use smart pointers
        - When we share an object, we need pointers to refer to the shared object
        - When we refer to a polymorphic object, we need a pointer because we do not always know the concrete type
        - A shared polymorphic object
- __span__
    - A span is basically a (pointer, length) pair denoting a sequence of elements
        - Gives access to a contiguous sequence of elements
        - Elements can be stored in many ways (vectors, built-in arrays, etc.)
        - Non-ownership pointer
        - When `span` is used for subscripting, range-checking is not done
    ```cpp
    void fpn(int *p, int n)
    {
        // assuming that p points to n integers
        // this is just a convention
        // - we cannot write range-for loop
        // - compiler cannot do cheap range-check etc.
        for (int i = 0; i < n; ++i)
        {
            p[i] = 0;
        }
    }

    void fs(std::span<int> p)
    {
        for (int& x: p)
        {
            x = 0;
        }
    }

    int a[100];
    fs(a); // creates a span {a, 100}
    fs(a, 100); // error
    fs({a, 100});
    ```
## Containers
- STL provides several containers that do not fit perfectly well with the ones we discussed before (vector, list, etc.)
    - These serve rather specialized services needed by large community of programmers
- `T[N]`
    - built-in array
    - fixed-size contiguously allocated sequence of N elements of type T
    - implicitly converts to a `T*`
- `basic_string<C>`
    - a sequence of characters of type C
- `valarray`
    - an array of numeric values of type T
- `array<T,N>`
    - a fixed-size sequence of elements of type T where the number of elements is N (N must be _constant expression_)
    - array can be allocated on the stack, in an object, or static storage
        - because the size is _known_!
    - elements are _allocated_ in the scope where the array is defined
    - must be initialized by an initializer list
        - number of elements in the initializer must be equal to or less than N
    ```cpp
    std::array<int, 3> a1 = {1, 2, 3};
    ```
    - using array saves you from nasty implicit pointer conversions
        - need to call `data()` to get the C-style pointer
- `bitset<N>`
    - Provide operations on a sequence of N bits where N is known at compile-time
    - if N is larger than 64 bits, this can be really convenient
        - bitset is optimized for smaller N values too
    ```cpp
    std::bitset<9> bs1 {"111111111"};  // from string
    std::bitset<9> bs2 {0b111111111};  // from int

    std::bitset<9> bs3 = ~bs1;
    ```
    - all the bit operations work on bitsets
- `pair<T, U>`
    - Used for "pair of values" use cases
        - sure you can use struct for returning "pair of values" but this easily can go unmaintainable
    - `first` and `second` lets you access the first and second element respectively
    - structured binding also works with pairs
    ```cpp
    auto [a, b] = fct(); // fct returns a pair object
    ```
    - use `make_pair()` to avoid redundant type specification
- `tuple<T..>`
    - Generalization of `pair` with zero or more elements
    ```cpp
    std::tuple t0 {};
    auto t1 = std::make_tuple(1, 1.1, "heel"); // std::tuple<int, double, string>
    ```
    - use `make_tuple()` to avoid redundant type specification
    - the elements of tuple are numbered
    - members are accessed through `get` function template
        - get by index
        ```cpp
        std::string s = std::get<2>(t1);
        ```
        - get by type
            - only if that type is _unique_ in the tuple
        ```cpp
        std::string s = std::get<string>(t1);
        ```
        - get for writing
        ```cpp
        std::get<string>(t1) = "heel2";
        ```
    - tuple really shines when you have to store or pass around an unknown number of elements of unknown types as an object
## Alternatives
- `union`
    - built-in type that holds one of a set of alternatives
- `variant<T...>`
    - safer and more convenient alternative to using raw `union`s
    - when you assign or init a variant with a value, it remembers the type of that value
        - later we can inquire the type
    ```cpp
    //
    auto m = fct(); // returns std::variant<string, int>
    if (std::holds_alternative<std::string>(m))
        std::cout << std::get<string>(m) << '\n';
    ...
    ```
    - you can easily perform different actions based on checking alternatives
        - using `visit`
    ```cpp
    using Node = std::variant<A, B, C, D>
    void check(Node* p)
    {
        // visitor visit then applies () to the overload object
        // - which in turn selects the most appropriate lambda to call 
        visit(overloaded {
            [](A& e) {},
            [](B& b) {},
            ...
        }, *p)
    }
    ```
- `optional<A>`
    - A* either pointing to an object or `nullptr`
        - put it another way, `variant<A, nothing>`
    - Useful for functions that may or may not return an object
    - An optional is treated as a pointer to its object 
        - not object itself
    - it is not type safe, make sure to check
    ```cpp
    std::optional<std::string> compose_m(std::ifstream& s)
    {
        std::string mess;
        if (ok) { return mess; }
        return {}; // empty optional
    }
    if (auto m = compose_m(std::cin)) // optional points to an object
        std::cout << *m << std::endl;
    else {
        ...
    }
    ```
- `any`
    - An `any` can hold arbitrary type and know which type (if any) it holds.
        - unconstrained version of `variant`
    ```cpp
    std::any compose_m(std::ifstream& s)
    {
        std::string mess;
        if (ok) { return mess; }
        return {}; 
    }
    auto m = compose_m(std::cin);
    std::string& s = std::any_cast<std::string&>(m);
    // exception is thrown if not string reference
    ```
    - We can extract the value held by the any by asserting the expected type