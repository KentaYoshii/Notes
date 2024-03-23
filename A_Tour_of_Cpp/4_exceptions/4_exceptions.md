# Exceptions

## Exceptions 
```cpp
double& Vector::operator[](int i)
{
    if (!(0<=i && i < size()))
        throw std::out_of_range("Vector::operator");
}
```
- The `throw` transfers control to a handler for exceptions of type `std::out_of_range` in some function that directly or indirectly called operator[].
    - The implementation will _unwind_ (exit scopes, functions, invoking destructors, etc.) the function call stack as needed to get back to the context of that caller
```cpp
void f()
// If f was not the suitable place to handle errors, we would not have used a try-block
// And instead let the exception percolate up the call stack
{
    try {
        compute1(v); // might throw an exception
    } 
    catch (const std::out_of_range& err) {
        // handle
    }
}
```
- We put code for which we are interested in handling exceptions into a `try`-block
- Don't overuse try-blocks!
    - Most functions should simply allow the exception to be propagated up the call stack.

## Invariants
- Whenever we define a function, we should consider what its preconditions are and consider whether to test them.
    - For the most part, it is good idea to test simple invariants.
- Class Invariants
    - A statement about what is true about a class
    - Constructor's job to establish the invariant for its class so that member functions can rely on it
    - Member functions then simply need to ensure that invariant still holds on exit
    ```cpp
    Vector::Vector(int s) 
    {
        if (s < 0) 
            throw length_error("...");
        elem = new double[s];
        sz = s;
    }
    ```

## Error-Handling Alternatives
- Return an error code when
    - A failure is normal and expected
    - An immediate caller can reasonably be expected to handle the failure
- Terminate the program when
    - An error is of a kind from which we cannot recover
    - To ensure this, you can add `noexcept` to a function so that a `throw` from anywhere in the function's implementation will turn into a `terminate()`.
    ```cpp
    void user(int sz) noexcept {...}
    ```
## Assertions
- There is currently no general and standard way of writing optional runtime tests of invariants.
- For now, you have to rely on ad hoc mechanisms
- `assert()`
    - Debug macro that terminates the program if assert fails in "debug mode"
    - In other modes, these are not checked.
- Static Assertions
    - We can also perform simple checks on most properties that are known at compile time and report failures to meet our expectations as compiler error messages!
    - Used to make assertions about types used as parameters in generic programming
    - `static_assert(A, S)`
        - A is some constant expression we want to check
        - S (optional) is compiler error message if A is not true
        ```cpp
        std::static_assert(4<=sizeof(int));
        ```
## Advice
- When in doubt, use exceptions
- Don't apply noexcept thoughtlessly