# Chapter 1: The Basics
- __CMake__
    - An open-source, cross-platform tool that uses compiler and platform independent config files to generate native build tool files specific to your complier and platform.
    - CMake tools need two things: __kit__ and __variant__.
    - A kit represents a toolchain (the compiler, linker, and other tools used to build your project)
    - A variant contains instructions for how to build your project. Defaults are
        - _Debug_ 
            - No optimizations + debug info
        - _Release_
            - Optimizations + no debug info
        - _MinRelSize_
            - Optimize for size + no debug info
        - _RelWithDebInfo_
            - Optimize for speed + debug info
- __Compiler__
    - Clang(++) for MAC
    - GCC for Linux
    - MSVC/MINGW for Windows
- __Declaration__ is a statement that introduces an entity into the program and specifies its type
    - _type_ defines a set of possible values and a set of operations for an object
    - _object_ is some memory that holds a value of a type
    - _value_ is a set of bits interpreted according to a type
    - _variable_ is a named object

- __Initialization__ can be done using `=` or `{}`
    - The former does a _narrowing conversions_ (i.e., double becomes int)
    - The latter will raise an error
    ```cpp
    int a = 0.0; // 0
    int a {0.0}; // error!
    ```
- __Scopes__
    - ___Local___ scope
        - Local name 
            - A name declared in a function or lambda + function args
        - Block 
            - Delimited by {} pair
        - Local names' scope extends from its point of declaration to the end of block 
    - ___Class___ scope
        - (Class) Member name
            - A name defined in a class, outside any function, lambda, or enum class.
        - Class names' scope extends from block for that class
    - ___Namespace___ scope
        - (Namespace) Member name
            - A name defined in a namespace outside any function, lambda, class or enum class.
        - Namespace names' scope extends from the point of declaration to end of name space
    - ___Global___ namespace
        - Global name
            - A name not defined in any other construct

- __Lifetime__
    - Point of Destruction
        - Namespace object -> end of the program
        - Member -> point of destruction of the object of which it is a member
        - `new` -> lives until destroyed by `delete`

- __Constants__
    - `const`
        - "I promise not to change this value."
        - The value of a this may be calculated at _run time_
    - `constexpr`
        - "to be evaluated at compile time"
        - performance + placement of data in read-only memory
        - The value of this MUST be calculated by the _compiler_      
    ```cpp
    constexpr int dmv = 17; // ok
    int var = 17;
    const double sqv = sqrt(var); // ok, run-time comp

    double sum(const vector<double>&);
    constexpr double s2 = sum(v); 
    // error: sum(v) is not constant expression
    ```
    - _Constant Expression_
        - Expression that will be evaluated by the _compiler_
        - For function to be this, it must be defined `constexpr` or `consteval`
            - `constexpr` function can be called with non-constant expression arguments
            - `consteval` function can only be called with constant expression arguments
- __Pointers, Arrays, and References__
    - In an expression,
        - prefix unary `*` means "contents of"
        - prefix unary `&` means "address of"
        ```cpp
        char *p = &v[3];
        char x = *p;
        ```
    - In a declaration, 
        - unary suffix `&` means "reference to"
            - Reference is similar to a pointer, except that you don't need to use a prefix `*` to access the value referred to by the reference
            - Reference CANNOT be made to refer to a different object _after_ its initialization
    - Null Pointer
        - Used when we don't have an object to point to or if we need to represent the notion of "no object available".
        - Only one `nullptr` shared by all pointer types
        ```cpp
        double *pd = nullptr; //ok
        int a = nullptr; //error: nullptr is a pointer
        ```
- __Mapping to HW__
    - Assignment
        - An assigment of a built-in type is a simple machine copy operation
        ```cpp
        int x = 2;
        int y = 3;
        x = y; // x is now 3
        ```
        - In the above, the two objects are independent.
    - A reference and a pointer both refer/point to an object and both are represented in memory as __machine address__.
        - Language rules differ tho!
            - Assignment to a reference does not change what the reference refers to but _assigns_ to the referenced object
            ```cpp
            int x = 2;
            int y = 3;
            int& r = x;
            int& r2 = y;
            r = r2; // write through r -> x = 3
            ```
    - Initialization
        - Make an uninitialized piece of memory into a valid object
        ```cpp
        int x = 7;
        int& r {x};
        ```
- __Advice__
    - Use {} for delcaring named types!
    - In if, prefer the implicit test against 0 or null