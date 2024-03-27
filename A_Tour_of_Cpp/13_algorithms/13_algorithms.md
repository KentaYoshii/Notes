# Algorithms
## Introduction
- A standard algorithm is expressed in terms of half-open sequences of elements
    - A sequence
        - represented by a pair of iterators specifying the first element and one-beyond-the-last tlement
- For writing, we only need to specify the initial element to be overwritten
- Some algorithms modify element values but NO algorithms add or subtracts elements of a container.
    - Sequence does not identify the container that holds the elements of the sequence
```cpp
std::unique_copy(vec.begin(), vec.end(), tar.begin());
```
- The STD does not offer a range-check when writing into a container
- `std::back_inserter(res)`
    - constructs an iterator for res that adds elements at the end of a container
        - extending the container if needed
- Most of the algorithms have `range` versions so we can do
    ```cpp
    std::sort(v.begin(), v.end()); // traditional
    ranges::sort(v); // using range
    ```
## Use of Iterators
- Iterators 
    - Any particular iterator is an object of some type
        - an iterator needs to hold the information needed for doing its job for a particular container type
            - for vector
                - it could simply be a pointer
                - or it could be a tuple where first points to the initial element and second is the offset
            - for list
                - it needs to point to a link that _knows_ about the next link!
    - Commonality among iterators
        - Semantics and Naming of their operations
            - ++ yields an iterator that refers to the next element
            - * yields the element to which the iterator refers
    - Iterators are general idea and concepts
        - std::forward_iterator, std::random_access_iterator, etc.
    - Each container knows its iterator type so we rarely need to interact with them directly
        - accessible via `iterator` or `const_iterator`
        ```cpp
        std::list<Entry>::iterator
        ```
- Use of Iterators
    - Many algorithms return iterators
        - `std::find()` returns an iterator to the element found
            - returns `end()` to indicate not found
    - Iterators are used to separate algorithms and containers
        - an algorithm operates on its data through iterators and knows nothing about the container in which the elements are stored
        - a container knows nothing about the algorithms operating on its elements
- Stream Iterators
    - The notion of iterators can be applied to I/O
    - `ostream_iterator`
        - We need to specify which stream will be used and the type of objects written to it
            - the effect of assigning to `*oo` is to write the assigned value to cout
        ```cpp
        std::ostream_iterator<std::string> oo {std::cout} // write strings to cout
        *oo = "hello, ";
        ++oo; // nop but provides the same intf with other iterators!
        *oo = "world!";
        
        vector<string> a {"hello", "world"};
        std::copy(a, oo);
        ```
    - `istream_iterator`
        - Input iterators are use in pairs so we need to define two istream_iterators
        ```cpp
        std::istream_iterator<std::string> ii {std::cin} // beginning
        std::istream_iterator<std::string> eos {}; // end-of-stream
        ```
    - Normally stream iterators are just passed directly to algorithms
    ```cpp
    int main()
    {
        std::string from, to;
        std::cin >> from >> to;

        std::ifstream is{from};
        std::ofstream os{to};
        
        // construct set from read-only input file stream
        std::set<std::string> b {std::istream_iterator{is}, std::istream_iterator<std::string>{}}
        // copy
        std::copy(b, std::ostream_iterator{os});
        return !is.eof() || !os;
    }
    ```
## Use of Predicates
- We can use predicates to give standard algorithms wide range of meanings
- Predicates should NOT modify the elements to which it is applied
```cpp
struct Greater_than {
    int val;
    Greater_than(int v): val{v}{}
    bool operator()(const pair<string, int>& r) const {return r.second>val;}
};
void f(std::map<string, int>& m)
{
    auto p = std::find_if(m, Greater_than{42}); // using function object
    auto p2 = std::find_if(m, [](const auto& r){return r.second>42;}) // using lambda expression
}
```