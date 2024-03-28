# Numerics
## Mathematical Function
- `<cmath>` defines the standard mathematical functions 
    - arguments are `float`, `double`, and `long double`
    - examples include
        - `abs(x)`
        - `floor(x)`
        - `log(x)`
    - return type is the _same_ as the argument type
- errors are reported by setting `errno` from `<cerrno>` 
    - to __EDOM__ if it is a domain error
    - to __ERANGE__ if it is a range error

## Numerical Algorithms
- `<numeric>` defines generalized numerical algorithms
    - There are sequentials ones and parallel ones
- Sequential Algorithms
    - `x=accumulate(b,e,i)`
        - x is the sum of i and the elements of [b:e)
        - can optionally take in a fourth argument f that replaces the default __+__
    - `x=inner_product(b,e,b2,i)`
    - `x=gcd(n,m)`
    ...
- Parallel Algorithms 
    - parallel ones take an execution policy argument (`par`, `par_unseq`, etc.)
    - `x=reduce(b,e,v)`
        - equivalent to `accumulate(b,e,v)` except it is out of order

## Random Numbers
- A random number generator consists of two parts
    - _Engine_ that produces a sequence of random or pseudo-random values
    - _Distribution_ that maps those values into a mathematical distribution in a range
        - `normal_distribution`
        - `uniform_int_distribution`
        ...
    ```cpp
    using mEng = std::default_random_engine;
    using mDist = std::uniform_int_distribution<>;

    mEng eng {};
    mDist dist {1,6};
    auto die = [&](){return dist(eng);};

    int x = die(); // x is value between 1:6
    ```
- To get a repeated or different sequence of values, we _seed_ the engine
    ```cpp
    eng.seed(999);
    ```
## Vector Arithematic
- STL vector does not support mathematical operations on vectors
- `valarray` provides a vector-like template that is less general but can perform numerical computations
    - the operations are applied to each element of the vectors
    ```cpp
    void f(valarray<double>& a1, valarray<double>& a2)
    {
        valarray<double> a = a1 + a2 * 4;
        ...
    }
    ```
## Type Aliases
- If you want to be specific about the sizes of integer types for example, use __type aliases__
- `<stdint>`
    - `int32_t`, `uint_least64_t`, etc.
- `<stddef>`
    - `size_t`
        - the type returned by sizeof()

## Mathematical Constants
- They come in two flavors
    - Template variable
        - `pi_v<T>`
    - Short name for most common use
        - `pi` which is `pi_v<double>`