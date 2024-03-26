# Containers
## Overview
- STL container defines a sequence and are _resource handles_.
- STL provides
    - vector<T>
        - a variable size vector
    - list<T>
        - a DLL
    - forward_list<T>
        - a SLL
    - deque<T>
        - a double-ended queue
    - map<K,V>
        - an associative array
    - multimap<K,V>
        - a map in which key can occur multiple times
    - unordered_map<K,V>
        - a map using hashed lookup
    - unordered_multimap<K,V>
        - a multimap using hashed lookup
    - set<T>
        - a map with just key
    - multiset<T>
        - a set in which value can occur multiple times
    - unordered_set<T>  
        - a set using hashed lookup
    - unorderd_multiset<T>
        - a multiset using hashed lookup
- Unordered containers are optimized for _lookup_ with a key.
- STL containers all have the same interface; some notable ones are
    - `value_type`
        - the type of an element
    - `p=c.begin()`
        - p points to the first element of c
    - `p=c.end()`
        - p points to one-past-the-last element of c
- Each container has its own strength and weaknesses
    - Vector
        - cheap and easy to subscript and loop over elements
        - need to move elements to different locations when inserting/removing elements
            - invalidating pointers to these elements!
    - forward_list
        - ideal for empty sequence 
            - because it only occupies 1 word (ptr to next element)!
            - it does not even container the size field!!!
- An emplace operation takes arguments for an element's constructor and builds the object in a newly allocated space in the container
    - Rather than copying an object into the container
    ```cpp
    v.push_back(pair{1, "cp and mv"}); // make a pair and move it into v
    v.emplace_back(1, "build in place"); // build a pair in v
    ```
- Pass a container _by reference_ and return it _by value_!
- When creating a container, use `{}`-initializer syntax for sequences of elements and `()`-initializer syntax for sizes!
- Unordered vs Ordered vs Associative
    - Use ordered containers (map, set, etc.) if you need to iterate over their elements in order
    - Use unordered containers for
        - element types with no natural order (no `<`)
        - fast lookup
    - Use associative (map, list) when you need pointer to elements to be stable as the size changes
        - no invalidation!
## Vectors
- The most useful STL container and should be your go-to default option
- A vector is a sequence of elements of a given type
    - stored contiguously in memory
- Typical vectors consist of a handle of vectors
    - `allocator`
        - allocator from which the vector can acquire memory for its elemens
        - the default uses `new` and `delete`
    - `elem`
        - pointer to the first element
    - `space`
        - pointer to the one-past-the-last element
    - `last`    
        - pointer to the one-past-the-last allocated space
- When initializing a vector with size, using `()` syntax, the elements are initialized to their type's default value.
    - If you want, you can specify the default as a second argument.
- `reserve()`
    - Used to make room for more elements
    - May have to allocate new memory and when it does, it moves the elements to the new allocation.
    - Use this in the beginning to avoid any unnecessary pointer invalidatoins
- Assignment
    - Involves copying its elements
    - Use, pointers, references, and move operations if this is undesirable
- Elements
    - When you insert a new element, its value is copied into the container
    - Element is not a reference or pointer! Just a copy!
    - If you have a class hierarchy, store a smart pointer to these object!
    ```cpp
    vector<unique_ptr<Shape>> vups;
    ```
- Range Checking
    - STL vector does NOT guarantee range checking
    - `at()` opertaion is a vector subscript operation that throws an exception if the argument is out of the vector's range
        - use this if you want to be safe
    - Use range-for to be safe!
## List
- Use a list for sequences where we want to insert and delete elements without moving other elements
- To search for an element
    - search from the beginning till the end
- To identify an element in a list, use an _iterator_.
    - a list iterator identifies a list element and can be used to iterate over a list
    ```cpp
    // given iterator p, *p is the element to which it refers
    // *p.m == p->m
    for (auto p=a.begin(); p!=a.end(); ++p)
        if(p->name=="Kenta") return 1;
    ```
## Map
- STL offers a balanced binary search tree called map
- Optimized for lookup(O(logN)) and insertion
- When subscripting
    - if key is found, the corresponding value is returned
    - if key is not found, it is entered into the map with a default value for its value
        - To avoid this, we can use `find()`
## Unordered Map
- Runtime for map is pretty good but we can do better by doing a _hashed lookup_.
    - Rather than comparison using operator `<`.
    - You need operator `==` though!
- STL provides a default hash function for built-in types
    - If necessary we can provide our own if we are using UDTs.

## Allocator
- Default STL containers allocate space using `new` and `delete`
- STL provies opportunities to install allocators with specific semantics where needed
```cpp
pmr::synchronized_pool_resource pool;
// use this allocator instead!
std::vector<int> data = std::vector<int>{512, &pool};
```