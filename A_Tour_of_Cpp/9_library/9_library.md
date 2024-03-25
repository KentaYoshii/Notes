# Library

## STD organization
- Every standard-library facility is provided through some standard header, such as `#include<string>`
- The standard library is defined in a namespace called `std`.
    - To use standard-library facilities, the `std::` prefix can be used
- Sub-namespaces
    - Literals are often offered in sub-namespaces to std.
        - `std::chrono`, `std::literals::string_literals`, etc.
    - To use them, we need to introduce it into the namespace in which we want to use it
    ```cpp
    using namespace std::literals::string_literals;
    ```
- `ranges`-namespace
    - std offers algorithms in two versions
        - A _traditional_ version taking a pair of iteraotrs
            - sort(v.begin(), v.end())
        - A _range_ version taking a single range
            - sort(v)
    - These two don't overload well
        - We should explictly introduce the raneg version of a std into scope if we decide to go with it
        ```cpp
        ...
        sort(v.begin(), v.end()); // ok
        sort(v); // error!
        ranges::sort(v) // ok
        using ranges::sort;
        sort(v); // ok!
        ```
- Headers
    - std headers such as `<algorithm>` and `<array>` all supply declarations in namespace `std`
    - stdlib.h (headers from the C standard library) are provided
        - (preferred) cstdlib is C++ header and places its declarations in both the `std` and global namespace
        - stdlib.h is C header and places its declarations only in global namespace