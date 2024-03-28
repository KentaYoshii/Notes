# Utilities

## Time
- In `<chrono>`, STL provides facilities dealing with time
- Clocks
    ```cpp
    auto t0 = std::chrono::system_clock::now(); // returns a time_point
    do_work();
    auto t1 = std::chrono::system_clock::now();
    auto diff = t1-t0; // returns a duration

    // can cast duration to different time units
    std::cout << std::chrono::duration_cast<nanoseconds>(diff).count() << "ns\n";

    // std::chrono_literals defines time-unit suffixes
    auto a = 10ms;
    ```
- There are supports for Calendars and Time Zones too

## Function Adaption 
- When passing a function as an argument, the type of the argument must exactly match the expectations expressed in the called functions's declaration
- If a function almost matches it, we have three ways of adjusting it
    - Lambda Expressions
    ```cpp
    void draw_all(std::vector<Shape*>& v)
    {
        // for each invokes f(x) for each element x
        // but we want to call member function...
        // lambda to the rescue
        for_each(v.begin(), v.end(), [](Shape* p){ p->draw();})
    }
    ```
    - `mem_fn()`
        - Given a member function, the function adaptor mem_fn produces a _function object_ that can be called as non-member function
        - Mainstream way before lambda
        ```cpp
        void draw_all(std::vector<Shape*>& v)
        {
            // for each invokes f(x) for each element x
            // but we want to call member function...
            // lambda to the rescue
            for_each(v.begin(), v.end(), std::mem_fn(&Shape::draw))
        }
        ```
    - `std::function`
        - Type that can hold any object you can invoke using the call operator
        ```cpp
        int f2(string);
        std::function fct2{f2}; // std::function<int(string)>
        ```
        - Since function is an object, it does not participate in overloading
            - If you need to overload function objects, consider using `overloaded`

## Type Functions
- Type Function
    - A function that is evaluated at compile time given a type as its argument or returning a type
    ```cpp
    constexpr float min = std::numeric_limits<float>::min();
    constexpr int minI = std::numeric_limits<int>::min();

    constexpr int szi = sizeof(int);
    ```
    - In `<type_traits>`, the STL provides many functions for inquiring about properties of type
    ```cpp
    bool b = std::is_arithmetic_v<X>;
    ```
    - STL uses `_v` for type functions that return values and `_t` for those that return types
    - Concepts are type functions and often the best type functions
- Type Predicates
    - Type Predicates
        - Type functions offered by STL that answer fundamental questions about types
        - Often used to constrain template arguments
        ```cpp
        template<typename Scalar>
        class cplx {
            static_assert(std::is_arithmetic_v<Scalar>, "error message");
        };
        ```
        - This is easier and more elegantly done using concepts
        ```cpp
        template<Arithmetic Scalar>
        class cplx {
        };
        ```
        - Often times, type predicates can be used to define concepts
        ```cpp
        template<typename T>
        concept Arithmetic = is_arithmetic_v<T>;
        ```
        - type predicates only apply to the built-in types
            - concept can be defined in terms of the _operations_ required!
    - Conditional Properties
        - Using type functions or concepts we can define a conditional property
        ```cpp
        // type funciton way
        template<typename T>
        class Smart_Pointer {
            ...
            T* operator->() const requires is_class_v<T>; // only for class!
        }

        // template way
        template<typename T>
        concept Class = is_class_v<T> || is_union_v<T>;

        template<typename T>
        class Smart_Pointer {
            ...
            T* operator->() const requires Class<T>; // only for class!
        }
        ```
    - Type Generators
        - Many type functions return types, often new types they compute
        - `R=remove_const_t<T>`
            - R is T with the topmost `const` removed
        - `R=conditional_t<b, T, U>`
            - R is T if b is true; U otherwise
        - We can even define a conditional property (don't do this lol)
        ```cpp
        template<typename T>
        class Smart_Pointer {
            ...
           enable_if<is_class_v<T>, T&> operator->(); // only for class!
        }
        ```
- Metaprogramming
    - Use of type functions and concepts
    - Template Metaprogramming if it involves templates as well

## Bit Manipulation
- `<bit>` defines functions for low-level bit manipulation
    - `bit_cast` lets us convert a value of one type to another type of the same size
- `std::byte` exists to represent bytes
    - rather than bytes known to represent some types
- Use unsigned int or `std::byte` to perform bit operations

## Exiting a Program
- When encountering a serious problem from which you cannot recover, you need to exit the program
- `exit(x)`
    - call functions registered with `atexit` and exit the program with the return value x
- `abort()`
    - exit the program immediately and unconditionally with a return value indicating unsuccessful operation
- `quick_exit(x)`
    - call functions registered with `at_quick_exit()` then exit the program with return value x
- `terminate()`
    - call the terminate_handler
        - default is `abort()`