# Input and Output
## Output
- `<ostream>` converts typed objects to a stream of characters (bytes)
    - Defines output for every built-in type
    - operator `<<` (put to) is used as an output operator on objects of type `ostream`
    - `cout` is the standard output stream and `cerr` is the stream for reporting errors
    - Avoid `std::endl` 
        - Flushing requires making a request to OS and is expensive
        - It automatically gets flushed anyways when the buffer is full
## Input
- `<istream>` converts a stream of characters (bytes) to typed objects
    - operaotr `>>` (get from) is used as an input operator on objects of type `istream`
        - the type of right hand operand determiens what input is accepted
        - skips initial whitespace!
        ```cpp
        int i;
        double d;
        std::cin >> i >> d; // the read is terminated by any character that is not an int
        ```
        - a space or a newline terminates the read!
        ```cpp
        std::string s;
        std::cin >> s;
        // type in Kenta Yoshii
        std::cout << "Hello, " << s << "\n"; // Hello, Kenta
        // do 
        // note: the newline is discarded at the end
        std::getline(cin, s);
        ```
    - `cin` is the standard input stream

## I/O state
- An `iostream` has a state that we can examine to determine whether an operation succeeded
    ```cpp
    void fct(istream& is)
    {
        for (int i; is>>i)
        {
            ...
        }
    }
    ```
    - Here, it reads from `is` until something that is not an integer is encountered (EOF, for instance)
    - `is>>i` returns a reference to `is`
        - testing an `istream` yields true if the stream is ready for another operation!
            - "did we succeed in reading an int from `is` to `i`?
    - We can set the state of the stream too!
    ```cpp
    if (is.eof()) 
        // do something
    if (is.fail())
        is.clear(); // reset the state to good
        // do something
        is.setstate(ios::base::failbit); // set the is's state to fail
    ```
## I/O for UDT
- We can define I/O for our own types too!
```cpp
struct Entry {
    std::string name;
    int number;
}

// output 
// - take output stream by REFERENCE and return IT
std::ostream& operator<<(ostream& os, const Entry& e)
{
    return os << "[" << e.name << "," << e.number << "]" << '\n';
}

// input
// - return istream by reference so that you can test if it succeeded or not
std::istream& operator>>(istream& is, Entry& e)
{
    // check if well-formatted etc.
    // populate e

    // if fail 
    // is.setstate(ios_base::failbit);

    return is;
}

for (Entry ee; std::cin>>ee;)
    std::cout << ee << '\n`;
```

## Output Formatting
- The `iostream` and `format` libraries provide operations for controlling the format of input and output
    - `iostream` is as old as C++
    - `format` provides printf style formatting!
- Stream Formatting
    - Manipulators
        - Simple formatting controls
        - Found in `ios`, `istream`, `ostream` and `iomanip`
    ```cpp
    std::cout << 1234 << hex << 1234 << oct << 1234; // 1234 4d2 2322
    std::cout.precision(4); // round floating point values more than 5
    std::cout << 1234.5678 << 1234.56789; // 1234.5678 1235
    ```
    - Floating-point manipulators such as `precision()` is sticky!
    - `<<` can also handle duraiton, time, etc.
- printf()-style formatting
    - printf() is part of C++ but it suffers from lack of type safety and extensibility to support UDT
    - `format` provides type-safe printf()-style formatting
    ```cpp
    string s = fromat("Hello, {}\n", val);
    ```
    - A format string delimitted by `{}` specify how arguments following the format string are to be inserted
        - `{}` takes the next argument, and insert it based on default `<<`
        - format directive is preceded by a colon 
            - i.e, `{:d}` for decimal
        - format() takes its arguments in order but we can change that too
            ```cpp
            std::cout << format("{2:} {1:x} {0:b}", 000, 111, 222);
            // first format directive uses the third arg following the format
            // ...
            // 222 6f 0
            ```
    - Constant formats are checked at compile time 
        - So if there is an error, an exception is thrown
    - `vformat()` takes a variable as a format
        - increases flexibility but gives chance to run-time errors
    - formatter can also write directly into a buffer
    ```cpp
    std::string buf;
    format_to(back_inserter(buf), "iterator: {} {}\n", "hi!", 2022);
    std::cout << buf; // iterator hi! 2022
    ```
## Streams
- STD supports
    - _Standard Streams_
        - streams attached to the system's standard I/O streams
    - _File Streams_
        - streams attached to files
        - `ifstream` for reading from a file, `ofstream` for writing to a file, `fstream` for r/w from/to a file
        ```cpp
        ofstream ofs {"path"};
        if (!ofs) {
            // error! cannot oepn!
        }
        // i/ofstream can be used just as cin/cout!
        ```
    - _String Streams_
        - streams attached to strings
        - `istringstream` for reading from a string, `ostringstream` for writing to a string,`stirngstream` for r/w from/to a string
        ```cpp
        ostringstream oss;
        oss << "hello world";
        cout << oss.view();
        ```
        - contents can be read either by `str()` (a string copy of contents) or `view()` (a `string_view` of contents)
    - _Memory Streams_
        - stream attached to specific areas of memory
        - `ispanstream` for reading, `ospanstream` for writing, and `spanstream` for r/w
        ```cpp
        array<char, 128> buf;
        ospanstream ss(buf); // takes a span as an argument
        ss << "write" << arg " to memory";
        ```
    - _Synchronized Streams_
        - streams that can be used from multiple threads in a safe manner
        - `osyncstream` guarantees that a sequence of output ops will complete and their results will be expected in the output buffer even if some other thread tries to write
        - Make sure to use `osyncstream` everywhere!
        ```cpp
        osyncstream oss(std::cout);
        oss << x;
        oss << y;
        ```
- Streams CANNOT be copied; always pass by reference
- All the std streams are templates with their character type as a paramter 
    - `ostream` is `basic_ostream<char>` 
## C-style I/O
- C-style I/O is not good 
    - not type-safe, bad for UDT...
- If you care about performance, you can use this command to make standard streams not compatible with C-style I/O
```cpp
ios_base::sync_with_stdio(false);
```