# Concepts and Generic Programming

## Concepts
- Consider the following example
```cpp
template<typename Sequence, typename Value>
Value sum(const Sequence&s, Value v)
{
    for (const auto&x : s)
        v+=x;
    return v;
}
```
- The sum() requires that 
    - first template arg is some kind of sequence of elements
        - that supports begin() and end() for range-for to work
    - second template arg is some kind of number
        - that supports +=
    - These requirements are called ___concepts___
- Use of Concepts
    - `typename` is the most lenient
        - only requires that argument is a type
    - most templates should be constrained template
        - compiler can reject bad calls by only looking at the interface!
    ```cpp
    template<Sequence Seq, Number Num>
        requires Arithmetic<std::range_value_t<Seq>, Num> // range_value_t gives us the element type of Seq
    Num sum(const Seq&s, Num v)
    {
        for (const auto&x : s)
            v+=x;
        return v;
    }
    ```
    - `requires Arithmetic...` is called __requirements__-clause.
        - template<Sequence Seq> is just a shorthand so we could have written
        ```cpp
        template<typename Seq, typename Num> requires Sequence<Seq> && Number<Num>...
        ```
- Concept-based Overloading
    - We can overload templates based on their properties.
    - Compiler will select the template with the strongest requirements met by the arguments.
- Valid Code
    - __requires__-expression 
        ```cpp
        template<forward_iterator iter>
            requires requires(Iter p, int i) { p[i]; p+i; } // first require starts the clause
        ```
        - lets us check if a set of expression is valid
        - it is a predicate that is true if the statements in it are valid code
        - this SHOULD be abstracted away in the definition of concepts!!!
- Definition of Concepts
    - Concept is a compile-time _predicate_ specifying how one or more types can be used
    ```cpp
    template<typename T, typename T2 = T>
    concept Equality_comparable = 
        requires (T a, T2 b) {
            // Give two values of the type, they must be comparable using == and !=
            // and result of those ops must be Boolean

            // The result of {...} after "->" must be a concept
            // There is no std boolean concept so Boolean is a UD-concept
            { a == b } -> Boolean;
            { a != b } -> Booelan;
        }
    ```
    - `typename T2 = T` means that if we don't specify a second template argument, T2 will be same as T
        - T is _default template argument_.
- Definition Checking
    - The concepts specified for a template are used to check arguments at the point of use of the template
        - Not used to check the use of the parameters in the DEFINITION of the template
        ```cpp
        template<equality_comparable T>
        bool cmp(T a, T b)
        {
            return a < b;
        }
        cmp(cout, cerr); // concept error: no support for ==
        cmp(1,2); // ok
        cmp(1+1i, 2+2i); // instantiation-time error! complex does not support <
        ```
- Concepts and auto
    - The keyword `auto` denotes the least constrained concept for a value
        - Simply requires that it must be a value of some type!
        - Taking an auto parameter makes a function into a _function template_
    - We can use concept to strengthen requirements of all such initialization
    ```cpp
    auto twice(Arithmetic auto x) { return x + x; } // numbers only
    auto thrice(auto x) { return x + x + x; } // any type with + defined
    ```
    - Also for variable initialization
    ```cpp
    Channel auto ch3 = open_channel("aa");
    ```
    - And for return type
    ```cpp
    Number auto fct()
    {
        return fct_2(x); // error unless fct_2 returns a Numbre
    }
    ```

## Generic Programming
- Lifting
    - The process of generalizing from a concrete piece of code while preserving performance.
- The best way to develop template is
    - Write a concrete version
    - Debug, test, and measure
    - Replace the concrete types with template arguments

## Variadic Templates
- Variadic Template
    - A template that is defined to accept an arbitrary number of arguments of arbitrary types.
```cpp
template<typename T>
concept Printable = requires(T t) { std::cout << t;}

void print(){} 

// Printable... means that Tail is a sequence of types
// Tail... means that tail is a sequence of values of types in Tail
template<Printable T, Printable... Tail>
void print(T head, Tail... tail)
{
    std::cout << head << ''; 
    print(tail...);
    // or if we want to remove empty print
    // if constexpr(sizeof...(tail)>0)
    //     print(tail...);
}

print("first", 1, 2, "hello"s);
```
- A parameter declared with a `...` is called a _parameter pack_
    - Tail is a template-argument parameter pack
    - tail is a function-argument parameter pack
- A call of print() separates the args into a head and a tail
    - the empty print() is for the final case when tail is empty
- Fold Expressions
    - C++ has a limited form of iteration over elements of a parameter pack
    ```cpp
    template<Number... T>
    int sum(T... v)
    {
        return (v + ... + 0); 
    }
    ```
    - `(v+...+0)` means add all the elements of v starting with the initial value 0 
        - the first element to be added is the one with the highest index (right-fold)
        - `(0+...+v)` will make it left-fold.
- Arguments Forwarding
    - Another way to use variadic templates is when you just want to pass arguments unchaged through an interface
        - Useful when you do not know what arguments are needed to construct an object
    ```cpp
    template<concepts::InputTransport Transport>
    class InputChannel {
        public:
        // std::forward moves the arguments unchanged!
            template<typename... TransportArgs>
            InputChannel(TransportArgs&&... transportArgs)
                : _transport(std::forward<TransportArgs>(transportArgs)...){}
        Transport _transport;
    }
    ```

## Template Compilation Model
- At the point of use, the args for a template are checked against its concepts.
    - Error reported immediately
- For unconstrained template parameters, all checks are postponed until code is generated for the template "at template instantiation time".
- Template Instantiation Time checking
    - Checks the use of arguments in the template definition
    - Kind of like a compile-time variant of _duck typing_.
    - It only operates on values!
- To use an unconstrained template, its definition must be in scope at its point of use.
    - If using header files, template definitions need to be in there too!

