# Ranges
## Range
- A __range__ is a generalization of the sequences defined by {begin(), end()} iterators; it specifies what it takes to be a sequence of elements. A range can be defined by:
    - A _{begin, end}_ pair of iterators
    - A _{begin, n}_ pair where begin is an iterator is n is the number of elements
    - A _{begin, pred}_ pair where begin is an iterator and pred is a predicate
        - if pred is true for the iterator p, we reach the end of the range
        - allows us to define infinite sequence!
- There are different kinds of ranges corresponding to the different kinds of iterators!
    - `forward_range`, `bidrectional_range`, etc.

- Generators
    - oftentimes, a range needs to be generated on the fly
        - std provides a few generators for that
    - `v=std::views::iota_view{x}`
        - v is a inifinite range of elements: x, x+1, x+2, etc.
        - `v=std::views::iota_view{x, y}` is the bounded version
    - `v=istream_view<T>{is}` 
        - v is the range obtained by calling `>>` for T on is.
    ```cpp
    auto cplx = std::views::istream_view<std::complex<double>>(std::cin);
    for (auto x : cplx)
        std::cout << x << '\n';
    // can compose too!
    for (auto x : std::transform_view(cplx, [](auto z){ return z * z; }))
        ...
    ```
- The range algorithms are almost identical to their counterparts that take two iterators pair
    - The difference is that they have _concept-enforced_ constraints
## Views
- A __view__ is a way of looking at a range (or you could say, lightweight range).
- View essential operations (mv, cp, etc.) all happen in _constant time_, irregardless of the number of elements in the view
- View is NOT responsible for deleting the elements of a range
    - It canNOT also outlive the underlying range
- Views are created by _range adaptors_.
     - Range adaptors take a range and produce a view.
        ```cpp
        std::views::filter_view v {r, [](int x) { return x % 2; }};
        ```
        - When reading from v, we read from _its_ range.
        - these views are evaluated _lazily_; that is you only pay the cost to process an element in the view when you _access_ that element
        ```cpp
        ints | std::views::filter([](int i) { return i % 3 == 0; }) 
             | std::views::transform([](int i) { return i * i; })
        // Here, filter range adaptor creates a view named "input"
        // transform range adaptor takes the view of elements divisible by three and 
        // creates a view of those elements squared
        ```
    - Range adaptors can be chained together using `|`
        - `a|f|g|t` == t(g(f(a)))
        - You need to use the corresponding function for std view type
            - so if view type is `filter_view` then function will be `filter`
            - `filter()` yields an `filter_view` object which you can pipe against a range
            - initial input to the pipeline has to be a _range_ or a _generator_.
                - `a` in the above example...
        ```cpp
        auto odd = [](int x) { return x % 2;};
        for (int x : r | std::views::filter(odd) | std::view::take(3)) 
            std::cout << x;
        ```
## Concepts
- STL provides many useful concepts such as
    - concepts defining properties of types
    - concepts defining iterators
    - concepts defining ranges
- Type Concepts
    - Type concepts help simplify templates
    - Some examples
        - `same_as<T,U>`
            - T is the same as U
        - `derived_from<T,U>`
            - T is derived from U
        - `common_with<T,U>`
            - T and U share a common type
    ```cpp
    template<typename T, typename U>
        requires std::common_with<T, U>
    bool ok(T t, U u)
    {
        std::common_type<T, U> t1 = fct(t);
        std::common_type<T, U> t2 = fct2(u);
        if (t1 < t2) {...}
    }
    ```
    - Some comparsion examples
        - `equality_comparable_with<T,U>`
            - T and U can be compared for equivalence using `==`
            - `equality_comparable<T>` (one arg version)
        - `totally_orderd_with<T,U>`
            - T and U can be totally ordered (<, >, <=, =>)
            - `totally_ordered<T>` (one arg version)
    - Some examples that lets you classify types
        - `regular<T>`
            - copyable<T>, default_constructable<T>, and equality_comparable<T>
            - the "ideal" for types!
        - `moveable<T>`
            - move_constructible<T>, assignable<T&, T>, and swappable<T>
    - Some examples that lets you specify how an operation can be called
        - `invocable<F, Args>`
            - An F can be invoked with an argument list of type `Args`
        - `regular_invocable`
            - invocable<F, Args> and is equality preserving
                - f == x then F(f) == F(x)
## Iterator / Range concepts
- STL algorithms access their data through iterators so we need concepts to classify properties of iterator types
    - The different kinds of iterators are used to select the BEST algorithm for a gvein set of arguments
- Some iterator concepts
    - `input_or_output_iterator<I>`
        - An I can be incremented and dereferenced
    - `forward_iterator<I>`
        - An I supports multi-pass and ==
    - `bidrectional_iterator<I>`
        - A forward_iterator<I> supporting --
    - `random_access_iterator<I>`
        - A bidrectional_iterator<I> supporting +, -, +=, -=, and []
    - `sentinel_for<S,I>`
        - An S is a sentinel for an Iterator type; S is a predicate on I's value type
        - Sentinel
            - We can iterate over a range starting at an iterator until the predicate becomes true
            ```cpp
            template<typename Iter>
            class Sentinel {
                public:
                    Sentinel(int ee): end(ee) {}
                    ...
                    // friend declarator allows us to define the functions "within" the scope of the class
                    friend bool operator==(const Iter& p, Sentinel s) { return (*p == s.end);}
                    friend bool operator!=(const Iter& p, Sentinel s) { return !(*p == s.end)}
                private:
                    iter_value_t<Iter> end;
            }
            std::static_assert(std::sentinel_for<Sentinel<const char*>, const char *>);
            ranges::for_each("Hello, World\n H", Sentinel<const char*>('\n'), [](const char x) { std::cout << x;});
            // Hello, World
            ```
- Some range concepts
    - Basically the range versions of iterator concepts
        - `random_access_raneg<R>`, `bidrectional_range<R>`, etc.