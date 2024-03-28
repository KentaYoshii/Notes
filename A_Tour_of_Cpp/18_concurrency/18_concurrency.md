# Concurrency

## Introduction
- Concurrency
    - The execution of several tasks simultaneously
- STL support for concurrency is primarily aimed at supporting _systems-level_ concurrency
    - rather than directly providing sophisticated higher-level concurrency models
- STL directly supports concurrent execution of multiple _threads_ in a __single address space__.
    - to do this, C++ provides a memory model and a set of atomic operations

## Tasks and Threads
- Task
    - a computation that can potentially be executed concurrently with other computations
- Thread
    - a system-level representation of a task in a program
- A task to be executed concurrently with other tasks is launched by constructing a `thread` with the task as its argument
```cpp
void f();
struct F {
    void operator()();
}

void user()
{
    thread t1 {F{}};
    thread t2 {f};

    t1.join(); // wait for t1
    t2.join(); // wait for t2
}
```
- `jthread`
    - you sometimes forget to call `join()` on a thread
    - "joining thread" will call join in its destructor
```cpp
void user()
{
    jthread t1{F{}};
    jthread t2{f}; // the order will be reversed! since join is done in destructor
}
```
- Threads share address space so they can communicate through shared objects
    - but this is really tricky to get it right!
- Goal of task definition
    - keep tasks completely separate except where they communicate in simple and obvious ways
- Arguments Passing
    - Task oftentimes need arguments to work with 
    ```cpp
    void f(int);
    struct F {
        F(int i): _i(i){}
        void operator()();
        private:
            int _i;
    }
    void user()
    {
        int i = 0;
        jthread t1{F{i}};
        jthread t2{f,i}; // the order will be reversed! since join is done in destructor
    }
    ```
    - `thread` has a variadic template constructor that can accept an arbitrary sequence of arguments
        - compiler checks that first argument, f, can be invokes using the passed-in arg(s)
            - if passes, it constructs a function object
        - use `ref()` to take the reference of an argument
- Returning results
    - pass args via non-const reference so that the task can modify it
    - pass args via const reference (using `cref`) and also pass another argument specifing the location of a place to deposit the result (aka. out argument)

## Sharing Data
- When tasks share data, access must be synchronized
- Mutexes and Locks
    - A thread acquires a mutex to enter critical sections
    - Define a mutex together with the data it is protecting
    ```cpp
    mutex m;
    int sh;

    void f()
    {
        scoped_lock lck{m};
        sh+=7;
    }
    ```
    - `scoped_lock<mutex>`
        - the constructor acquires the mutex (m.lock())
            - if another thread has already acquired the mutex, the thread blocks
        - the destructor releases the mutex
        - can acquire multiple locks
            ```cpp
            scoped_lock lck{m1,m2,m3};
            ```
            - the thread will only proceed once it acquires all 3 locks
                - it will _never_ go to sleep
        - if you only need one mutex, use `lock_guard` (one mutex version of `scoped_lock`)
        - scoped_lock canNOT be moved!
            - `unique_lock` can be!
        - `unique_lock` provides low level operations such as `lock()` and `unlock()`
    - `shared_mutex`
        - "reader-writer" lock
            - readers acquire lock in shared mode
            - writers acquire lock in exclusive mode
        ```cpp
        shared_mutex mx;

        void reader()
        {
            shared_lock lck{mx};
            ...
        }
        void writer()
        {
            unique_lock lck{mx};
            ...
        }
        ```
- atomics
    - A mutex is fairly expensive
    - If it is only tiny amount of work, prefer the use of an _atomic_ variable
    ```cpp
    mutex mx;
    atomic<bool> init_x;
    X x;

    if (!init_x) 
    {
        lock_guard lck {mx};
        if (!init_x)
        {
            // init x
            init_x = true;
        }
    }
    ```
## Waiting for Events
- A thread sometimes has to wait for something to complete
    - time passing, another task completing, etc.
- __Conditional Variables__
    - A mechanism allowing one thread to wait for another
    - A thread wait for some condition/event to occur
```cpp

queue<Message> mqueue;
condition_variable mcond;
mutex mmutex;

void C()
{
    while(true)
    {
        unique_lock lck {mmutex}; // acquire mx
        mcond.wait(lck, []{return !mqueue.empty();}); // release mx and wait
                                                      // don't wake up until cond is true
                                                      // re-acquire mx upon wakeup
        // pop from message queue 
    }
}
void P()
{
    while(true)
    {
        scoped_lock lck{mmutex};
        mqueue.push(/**/);
        mcond.notify_one();
    }
}
```

## Communicating Tasks
- `<future>` provides a few facilities to allow programmers to operate at the conceptual level of tasks rather than directly at the lower level of threads and locks
- `future` and `promise`
    - They enable a transfer of a value between two tasks without explicit use of a lock
    - When a task wants to pass a value to another, it puts the value into a `promise`
        - The value can be read from the corresponding `future`
            - if the value is not there yet, our thread blocks until it is ready 
            - if the value cannot be computed `get()` might thrown an exception
        ```cpp
        // assume we have future<X> fx
        X v = fx.get();
        ```
    ```cpp
    // example of sending a result of type X to a future
    void f(promise<X>& px)
    {
        try {
            X res;
            // do something 
            px.set_value(res);
        } catch (...) {
            // pass the exception to future's task
            px.set_exception(current_exception());
        }
    }
    // example of getting a result from a future
    void g(future<X>& fx)
    {
        try {
            X v = fx.get();
        } catch (...) {
            // if exception does not need to be handled by g, you can remove try-catch
            // exception will just propagate up as usual
        }
    }
    ```
- `packaged_task`
    - How can we get a `future` into the task that need a result and `promise` into the task that should produce that result?
        - `packaged_task` can handle that setup
        - `packaged_task` is a wapper code to put the return value or exception from the task into a `promise`
            - just like the above code
            - then you can call `get_future()` to get the corresponding future
    - packaged_task template takes the type of the task as its template argument and the task as its constructor argument
        - packaged_task cannot be copied
            - it is a resource handle
            - so use move
    ```cpp
    // define task
    double accum(vector<double>::iterator b, vector<double>::iterator e, double init)
    {
        return accumulate(&*b, &*e, init);
    }

    double comp2(vector<double>& v)
    {
        packaged_task pt0 {accum};
        packaged_task pt1 {accum};

        future<double> f0 {pt0.get_future()};
        future<double> f1 {pt1.get_future()};

        double *first = &v[0];
        thread t1 {move(pt0), first, first+v.size()/2, 0.0};
        thread t2 {move(pt1), first+v.size()/2, first+v.size(), 0.0};

        return f0.get() + f1.get();
    }
    ```
- `async`
    - Let's you separate the "call part" of a function call from the "get the result part"
    - Think in terms of tasks that potentially compute their results asynchronously
    - Don't even think to use this on tasks that might access the same resources
    - The number of threads that will actually be used is all up for async to decide
    ```cpp
    double comp2(vector<double>& v)
    {
        auto v0 = &v[0];
        auto sz = v.size();

        // async returns a future
        auto f0 = async(accum, v0, v0+sz/2, 0.0);
        auto f1 = async(accum, v0+sz/2, v0+sz, 0.0);

        return f0.get() + f1.get();
    }
    ```
- Stopping a thread
    - _stop\_token_
        - A mechanism for politely requesting a thread to clean up and go away
    ```cpp
    void find(stop_token tok, vector<string>::iterator b, vector<string>::iterator e, string& key)
    {
        // tests whether other threads requested me to stop
        for (string* p = b; p!=e && !tok.stop_requested(); ++p)
        {
            // return if match is found
        }
    }
    void find_all(vector<string>& vs, string& key)
    {
        int mid = vs.size()/2;
        string* pvs = &vs[0];

        stop_source ss1{}; // produce stop_token for communicating with threads
        jthread t1(find, ss1.get_token(), pvs, pvs+mid, key);
        stop_source ss2{};
        jthread t2(find, ss2.get_token(), pvs+mid, pvs+mid+mid, key);

        while(/*not found yet*/)
            this_thread::sleep_for(10ms);
        
        // found
        ss1.request_stop();
        ss2.request_stop();
    }
    ```
## Coroutines
- Coroutine
    - A function that maintains its state between calls
        - like a function object but the saving and restoring of its state between calls are implicit and complete
        - think of it like a function that saves its stack frame between calls
        - is a lot smaller than a thread
        - `co_await` asks the expression if it has a result to provide
            - if yes, then the execution controls as normal
            - if no, the current function suspends execution and returns control to the function
                - coroutine attaches itself to the expression object such that once it has the value, it resumes the coroutine's execution (on the same thread or some other thread)
        - `co_yield` returns a value and waits for the next call
        - `co_return` returns a value and terminates the coroutine
    ```cpp
    generator<long long>fib()
    {
        long long a = 0;
        long long b = 1;
        while (a < b)
        {
            auto next = a + b
            co_yield next; // save state, return value, and wait
            a = b;
            b = next;
        }
        co_return 0;
    }

    void user(int max)
    {
        for (int i = 0; i++<max;)
            std::cout << fib() << '';
    }
    ```