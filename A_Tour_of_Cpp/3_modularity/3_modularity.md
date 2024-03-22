# Modularity

## Introduction
- A _declaration_ specifies all that's needed to use a function or a type
    - The corresponding _definition_ can reside elsewhere
- There can be _many_ declarations for an entity but _only_ one definition

## Separate Compilation
- C++ supports a notion of separate compilation (where user code sees only declarations of the types and functions used) in two ways
    - Header Files
        - Place declarations in separate files, and textually `#include` a header file where its declarations are needed
    - Modules
        - Define modules files, compile them, and `import` them where needed
        - Only `export`ed declarations are seen
- Header Files
    - Place declarations that specify the interface to a piece of code we consider a module in a file
    ```cpp
    // Vector.h
    class Vector {
        public:
            Vector(int s);
            double& operator[](int i);
            int size();
        private:
            double* elem;
            int sz;
    }
    ```
    - You will need a corresponding .cpp (i.e., Vector.cpp) file providing the definitions
    - To use, simply `#include "Vector.h"`
    - __Translation Unit__
        - A .cpp file that is compiled by itself (including the h files it includes)
        - A program can consist of thousands of these
    - Disadvantages
        - _Time_
            - If Vector.h is included in 101 TUs, then compiler will have to process it 101 times.
        - _Order Dependencies_
            - If you include h1 before h2, the declarations and macros in h1 might affect h2!
        - _Transitivity_
            - All code that needs to express a declaration in a header file MUST be present in that header file, leading to header file including more header files!
- Modules
    - Advantages
        - A module is compiled once only!
            - Rather than in each translation unit
        - Two modules can be imported in either order without changing their meaning
        - If you import/include something into a module, the user of your module does not gain access to them
    ```cpp
    export module Vector; // defining module called Vector
    export class Vector {...}
    export bool operator==(const Vector& v1, const Vector& v2) {...}
    ``` 
    - Compiler will take care of generating the interface for Vector module!

## Namespaces
    - A mechanism for expressing that some declarations belong together and that their names shouldn't clash with other names.
    ```cpp
    namespace My_code {
        class complex {...}

        int main();
    }

    int My_code::main() {
        complex z{1,2}; // use my version of complex
    }

    int main() {
        return My_code::main();
    }
    ```
    - Using-Declaration
        - A way to bring the name into a scope without repeatedly qualifying it. Makes a name from a namespace usable as if it were declared in the scope in which it appears.
        ```cpp
        using std::swap;
        swap(x, y);
        ```
    - Using-Directive
        - A way to gain access to all names in a namespace. Makes _unqualified_ names from the named namespace accessible from the scope in which we placed the directive.
        ```cpp
        using namespace std;
        ```
## Function Arguments and Return Values
- The default for argument passing and value return is _make a copy_.
- Argument Passing
    - Pass small (size of two or three pointers or less) values __by-value__ and larger ones __by-reference__.
    - If we are passing by reference and not modifying it, do __pass-by-const-reference__.
    - Default function argument can be achieved like this
    ```cpp
    void print(int value, int base=10);
    print(2, 16); //ok
    print(2); //ok
    ```
- Value Return 
    - Small objects can be return __by-value__.
    - Return __by-reference__ when we want to grant a caller access to something that is not local to the function (i.e., element of a Vector).
    - What if the object to return is not small?
        - Use __move constructor__ (to be visited later).
        - Even if we don't provide one, compiler is smart enough to perform __copy elision__.
- Suffix Return Type
    - Instead of putting return type at the very front, put it at the very end.
    - Use `auto` to mean "the return type will be mentioned later or be deduced".
    ```cpp
    auto mul(int i, double d) -> double {return i * d;}
    ```
- Structured Binding
    - A function can return only a single value, but that value can be a class object with many members.
    - Structured Binding
        - The mechanism for giving local names to members of a class object
        ```cpp
        auto [n, v] = read_entry(); 
        ```
        - There must be the _same number_ of names defined for the binding as there are data members in the class object
## Advice
- Avoid non-inline function definitions in headers
- Don't put a  using-directive in a header file
- Don't overuse return-type deduction
- Don't overuse structured binding