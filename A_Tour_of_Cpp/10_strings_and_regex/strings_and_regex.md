# Strings and Regex
## Strings
- `std::string` 
    - saves users from C-stype manipulation of arrays of characters through pointers
    - it is a regular type for owning a sequence of characters of various character types
    - has a move constructor so returning a string is efficient
    - mutable
    - `c_str()` or `data()` will give you read-only view of C-style string representation
    - Literal
    ```cpp
    const char* a = "a"; // C-style (a zero-terminated array of chars)
    std::string b = "b"s; // std::string (note the s suffix)
    ```
- Implementing `std::string`
    - Done using _short-string optimization_
        - short string values (~14 characters) are kept in the string object itself
        - long string values are placed on the heap
    - Supporting other character sets
        - `std::string` is just an alias for a general template `std::basic_string` with a character type `char`
        ```cpp
        template<typename Char>
        class basic_string {

        }
        using string = basic_string<char>;

        // If we have Japanese character called Jchar
        using Jstring = basic_string<Jchar>;
        ```
- `std::string_view`
    - You can pass a whole string using references but passing only substring is hard
    - `std::string_view` 
        - Basically a (pointer, length) pair denoting a sequence of characters
        - Gives you access to contiguous sequence of characters that are stored in many ways (C-style, std::string, etc.)
        - It does NOT own the characters it points to 
        - Defines a range, so it is traversable
        - It only gives you a read-only view! so you cannot modify the characters that it points to
        - It needs to point to something! 
        - Use `sv` suffix to create a string_view
            ```cpp
            std::string_view a = "hello"; // length is computed at runtime
            std::string_view b = "hello"sv; // length is computed at COMPILE time
            ```
        - For range checking, use `at()` rather than iterator or `[]`
            - Other way round when you want to optimize for speed
    - Use `std::string_view` as an arg of functions that needs to read character sequences stored in various ways
    - Use `std::string_span<char>` as an arg of functions that needs to write character sequences stored in various ways

## Regex
- std provides `std::regex` 
- too niche to take notes...