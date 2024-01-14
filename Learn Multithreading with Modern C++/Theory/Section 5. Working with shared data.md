dates:: 2024-01-13 15:06

---

Context:
- [Critical Section](#Critical%20Section)
- [C++ mutex](#C++%20mutex)
- [std mutex interfaces](#std%20mutex%20interfaces)
- [std timed_mutex](#std%20timed_mutex)
- [std shared_mutex](#std%20shared_mutex)
- [std recursive_mutex](#std%20recursive_mutex)
- [std lock_guard](#std%20lock_guard)
- [std unique_lock](#std%20unique_lock)
- [std unique_lock interfaces](#std%20unique_lock%20interfaces)
- [std scoped_lock](#std%20scoped_lock)
- [std shared_lock](#std%20shared_lock)
- [Static variables in a multithreading environment](#Static%20variables%20in%20a%20multithreading%20environment)
- [std thread_local](#std%20thread_local)
- [Lazy initialization](#Lazy%20initialization)
- [Deadlock](#Deadlock)
- [Livelock](#Livelock)

---
### Critical Section

A critical section is a region of code within a program that must be executed atomically. In other words, only one thread at a time is allowed to enter and execute the critical section. The purpose of a critical section is to protect shared resources or data structures from simultaneous access by multiple threads, which can lead to data corruption or race conditions.

Here are key concepts related to critical sections:

1. **Critical Section Entry:**
   - **Mutex (Mutual Exclusion):** A commonly used synchronization mechanism for implementing critical sections is a mutex. A thread must acquire the mutex before entering the critical section. If another thread holds the mutex, the requesting thread is blocked until the mutex is released.

   ```cpp
   #include <mutex>

   std::mutex myMutex;

   void criticalSection() {
       std::lock_guard<std::mutex> lock(myMutex);
       // Code inside the critical section
   }
   ```

2. **Ensuring Mutual Exclusion:**
   - The goal of a critical section is to ensure mutual exclusion, meaning that at any given time, only one thread can execute the critical section.

3. **Preventing Race Conditions:**
   - Critical sections prevent race conditions by ensuring that shared resources are accessed in a controlled manner, avoiding conflicts that can lead to unpredictable behavior.

4. **Deadlocks:**
   - Care must be taken to avoid deadlocks, which can occur when multiple threads are waiting for each other to release resources. Deadlocks can halt program execution.

5. **Atomic Operations:**
   - In some cases, critical sections may involve atomic operations that are inherently thread-safe, ensuring that certain operations are executed atomically without the need for locks.

6. **Performance Considerations:**
   - While critical sections provide safety, they can introduce performance overhead due to the need for synchronization. Fine-tuning is often required to balance safety and performance.

Example:

```cpp
#include <iostream>
#include <mutex>

std::mutex myMutex;

void criticalSection(int threadId) {
    std::lock_guard<std::mutex> lock(myMutex);
    std::cout << "Thread " << threadId << " entered the critical section.\n";
    // Code inside the critical section
    std::cout << "Thread " << threadId << " exited the critical section.\n";
}

int main() {
    // Multiple threads trying to access the critical section concurrently
    std::thread t1(criticalSection, 1);
    std::thread t2(criticalSection, 2);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
```

In this example, the `criticalSection` function represents the critical section. The `std::lock_guard` ensures that only one thread at a time can execute the critical section, preventing interference between threads.

### C++ mutex

﻿std::mutex - lock() • unlock() • try_lock()
﻿std::timed_mutex - try_lock_for() • try_lock_until()
﻿std::shared_mutex - Allows multiple ownerships of the mutex
﻿std::recursive_mutex - Allows recursive locks (lock(), lock(), unlock() unlock())
﻿
```
﻿std::mutex
|-- std::timed_mutex
|-- std::shared_mutex
|-- std::recursive_mutex
```
### std::mutex interfaces

The `std::mutex` class in C++ provides a standard interface for implementing mutual exclusion, allowing only one thread to enter a critical section at a time. Here is an overview of the `std::mutex` interface:

1. **Default Constructor:**
   - Creates an unlocked mutex.

   ```cpp
   std::mutex myMutex;
   ```

2. **`lock` Function:**
   - Locks the mutex, blocking if the mutex is already locked by another thread.

   ```cpp
   myMutex.lock();
   ```

3. **`try_lock` Function:**
   - Attempts to lock the mutex without blocking. Returns immediately with a boolean indicating success or failure.

   ```cpp
   if (myMutex.try_lock()) {
       // Mutex is locked
   } else {
       // Mutex is not locked
   }
   ```

4. **`unlock` Function:**
   - Unlocks the mutex, allowing other threads to lock it.

   ```cpp
   myMutex.unlock();
   ```

5. **`std::lock_guard` for Automatic Locking and Unlocking:**
   - `std::lock_guard` is a convenient class that automatically locks and unlocks a mutex using RAII (Resource Acquisition Is Initialization) principles.

   ```cpp
   #include <mutex>

   std::mutex myMutex;

   void criticalSection() {
       std::lock_guard<std::mutex> lock(myMutex);
       // Code inside the critical section
   }
   ```

6. **`std::unique_lock` for More Flexibility:**
   - `std::unique_lock` provides more flexibility than `std::lock_guard`. It allows deferred locking, timed locking, and manual locking and unlocking.

   ```cpp
   #include <mutex>

   std::mutex myMutex;

   void criticalSection() {
       std::unique_lock<std::mutex> lock(myMutex);
       // Code inside the critical section
   }
   ```

### std::timed_mutex

`std::timed_mutex` is another type of mutex provided by the C++ Standard Library, which extends the functionality of `std::mutex`. `std::timed_mutex` allows a thread to attempt to lock the mutex for a specified duration, and it supports operations for timed locking and unlocking.

Key Interfaces and Usage:

1. **Include Header:**
   - To use `std::timed_mutex`, include the `<mutex>` header.

   ```cpp
   #include <mutex>
   ```

2. **Declaration and Initialization:**
   - Declare and initialize a `std::timed_mutex` object.

   ```cpp
   std::timed_mutex myTimedMutex;
   ```

3. **Locking and Unlocking:**

a. `lock()`:
   - Locks the mutex. If the mutex is not available, the calling thread will be blocked until the mutex can be acquired.

   ```cpp
   myTimedMutex.lock();
   ```

b. `try_lock()`:
   - Attempts to lock the mutex without blocking. Returns `true` if the lock is acquired successfully, and `false` otherwise.

   ```cpp
   if (myTimedMutex.try_lock()) {
       // Lock acquired successfully
   } else {
       // Lock not acquired
   }
   ```

c. `try_lock_for()`:
   - Attempts to lock the mutex for a specified duration. Returns `true` if the lock is acquired within the specified duration, and `false` otherwise.

   ```cpp
   std::chrono::milliseconds duration(100);
   if (myTimedMutex.try_lock_for(duration)) {
       // Lock acquired within the specified duration
   } else {
       // Lock not acquired within the specified duration
   }
   ```

d. `try_lock_until()`:
   - Attempts to lock the mutex until a specified time point. Returns `true` if the lock is acquired before the specified time point, and `false` otherwise.

   ```cpp
   using namespace std::chrono;
   system_clock::time_point deadline = system_clock::now() + seconds(5);
   if (myTimedMutex.try_lock_until(deadline)) {
       // Lock acquired before the deadline
   } else {
       // Lock not acquired before the deadline
   }
   ```

e. `unlock()`:
   - Unlocks the mutex.

   ```cpp
   myTimedMutex.unlock();
   ```

4. **Example:**

```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::timed_mutex myTimedMutex;

void timedFunction() {
    std::unique_lock<std::timed_mutex> lock(myTimedMutex, std::defer_lock);

    if (lock.try_lock_for(std::chrono::seconds(3))) {
        std::cout << "Thread " << std::this_thread::get_id() << " acquired the timed mutex.\n";
        // Perform work within the critical section
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Thread " << std::this_thread::get_id() << " released the timed mutex.\n";
        lock.unlock();
    } else {
        std::cout << "Thread " << std::this_thread::get_id() << " failed to acquire the timed mutex.\n";
    }
}

int main() {
    std::thread t1(timedFunction);
    std::thread t2(timedFunction);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
```

In this example, `std::timed_mutex` is used to protect a critical section, and each thread attempts to lock the mutex for a specified duration using `try_lock_for`. The example demonstrates the use of timed locking to handle scenarios where waiting for the lock indefinitely may not be desirable.
### std::shared_mutex

`std::shared_mutex` is a C++ Standard Library class introduced in C++14 that provides a mechanism for shared ownership of a resource with multiple readers and exclusive ownership for a single writer. It is often used in scenarios where multiple threads need to read a shared resource concurrently, but exclusive access is required for writing. This type of mutex is also known as a "reader-writer lock."

Key Interfaces and Usage:

1. **Include Header:**
   - To use `std::shared_mutex`, include the `<mutex>` header.

   ```cpp
   #include <mutex>
   ```

2. **Declaration and Initialization:**
   - Declare and initialize a `std::shared_mutex` object.

   ```cpp
   std::shared_mutex mySharedMutex;
   ```

3. **Locking and Unlocking:**

a. `lock()`:
   - Locks the mutex exclusively for writing. If the mutex is not available, the calling thread will be blocked until it can obtain the exclusive lock.

   ```cpp
   mySharedMutex.lock();
   ```

b. `try_lock()`:
   - Attempts to lock the mutex exclusively for writing without blocking. Returns `true` if the lock is acquired successfully, and `false` otherwise.

   ```cpp
   if (mySharedMutex.try_lock()) {
       // Exclusive lock acquired successfully
   } else {
       // Exclusive lock not acquired
   }
   ```

c. `unlock()`:
   - Unlocks the mutex, releasing the exclusive lock.

   ```cpp
   mySharedMutex.unlock();
   ```

d. `lock_shared()`:
   - Locks the mutex for shared (read) access. Multiple threads can hold shared locks simultaneously.

   ```cpp
   mySharedMutex.lock_shared();
   ```

e. `try_lock_shared()`:
   - Attempts to lock the mutex for shared (read) access without blocking. Returns `true` if the shared lock is acquired successfully, and `false` otherwise.

   ```cpp
   if (mySharedMutex.try_lock_shared()) {
       // Shared lock acquired successfully
   } else {
       // Shared lock not acquired
   }
   ```

f. `unlock_shared()`:
   - Unlocks the mutex, releasing a shared lock.

   ```cpp
   mySharedMutex.unlock_shared();
   ```

4. **Example:**

```cpp
#include <iostream>
#include <mutex>
#include <thread>

std::shared_mutex mySharedMutex;

void readerFunction(int id) {
    std::shared_lock<std::shared_mutex> lock(mySharedMutex);
    std::cout << "Reader " << id << " enters the shared section.\n";
    // Read from the shared resource
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Reader " << id << " exits the shared section.\n";
}

void writerFunction(int id) {
    std::unique_lock<std::shared_mutex> lock(mySharedMutex);
    std::cout << "Writer " << id << " enters the exclusive section.\n";
    // Write to the shared resource
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Writer " << id << " exits the exclusive section.\n";
}

int main() {
    std::thread readers[3];
    std::thread writers[2];

    // Start reader threads
    for (int i = 0; i < 3; ++i) {
        readers[i] = std::thread(readerFunction, i);
    }

    // Start writer threads
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writerFunction, i);
    }

    // Wait for threads to finish
    for (int i = 0; i < 3; ++i) {
        readers[i].join();
    }

    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}
```

In this example, `std::shared_mutex` is used to protect a shared resource. Reader threads use `std::shared_lock` to acquire shared locks for reading, while writer threads use `std::unique_lock` to acquire an exclusive lock for writing. Multiple reader threads can access the shared resource concurrently, but only one writer thread can have exclusive access at a time.
### std::recursive_mutex

`std::recursive_mutex` is a type of mutex provided by the C++ Standard Library that extends the functionality of `std::mutex`. Unlike `std::mutex`, a `std::recursive_mutex` allows a thread to lock the mutex multiple times in a recursive manner. Each call to `lock` must be matched with a corresponding call to `unlock`, and the mutex is only fully released when the number of unlocks matches the number of locks.

Key Interfaces and Usage:

1. **Include Header:**
   - To use `std::recursive_mutex`, include the `<mutex>` header.

   ```cpp
   #include <mutex>
   ```

2. **Declaration and Initialization:**
   - Declare and initialize a `std::recursive_mutex` object.

   ```cpp
   std::recursive_mutex myRecursiveMutex;
   ```

3. **Locking and Unlocking:**

a. `lock()`:
   - Locks the mutex. If the calling thread already holds the lock, it can call `lock` again without blocking. Each call to `lock` must be matched with a corresponding call to `unlock`.

   ```cpp
   myRecursiveMutex.lock();
   ```

b. `try_lock()`:
   - Attempts to lock the mutex without blocking. Returns `true` if the lock is acquired successfully, and `false` otherwise.

   ```cpp
   if (myRecursiveMutex.try_lock()) {
       // Lock acquired successfully
   } else {
       // Lock not acquired
   }
   ```

c. `unlock()`:
   - Unlocks the mutex. If the calling thread has called `lock` multiple times, it needs to call `unlock` an equal number of times to fully release the lock.

   ```cpp
   myRecursiveMutex.unlock();
   ```


### std::lock_guard

`std::lock_guard` is a C++ Standard Library class template introduced to simplify the process of managing locks in a scoped manner. It provides a convenient RAII (Resource Acquisition Is Initialization) mechanism for acquiring and releasing a lock automatically. The primary purpose of `std::lock_guard` is to ensure that a lock is acquired during the lifetime of the `std::lock_guard` object and released when the object goes out of scope.

Key Features and Usage:

1. **Include Header:**
   - To use `std::lock_guard`, include the `<mutex>` header.

   ```cpp
   #include <mutex>
   ```

2. **Locking a Mutex:**
   - `std::lock_guard` is typically used with a `std::mutex` to ensure that the associated critical section is executed atomically.

   ```cpp
   std::mutex myMutex;

   void criticalSection() {
       std::lock_guard<std::mutex> lock(myMutex);
       // Code inside the critical section
   }
   ```

3. **Automated Locking and Unlocking:**
   - The constructor of `std::lock_guard` locks the associated mutex, and its destructor releases the lock when it goes out of scope.

4. **Scope of Locking:**
   - The critical section is guaranteed to be locked only for the duration of the scope in which the `std::lock_guard` object is defined.

5. **Exception Safety:**
   - `std::lock_guard` provides exception safety by ensuring that the mutex is properly released even if an exception is thrown within the critical section.


### std::unique_lock

`std::unique_lock` is another C++ Standard Library class template for managing locks, similar to `std::lock_guard`. `std::unique_lock` provides more flexibility and features than `std::lock_guard` and is often preferred in scenarios where additional control over locking and unlocking is needed.

Key Features and Usage:

1. **Include Header:**
   - To use `std::unique_lock`, include the `<mutex>` header.

   ```cpp
   #include <mutex>
   ```

2. **Locking a Mutex:**
   - `std::unique_lock` is used with a `std::mutex` or other lockable objects to provide locking and unlocking.

   ```cpp
   std::mutex myMutex;

   void criticalSection() {
       std::unique_lock<std::mutex> lock(myMutex);
       // Code inside the critical section
   }
   ```

3. **Manual Locking and Unlocking:**
   - Unlike `std::lock_guard`, `std::unique_lock` allows for manual locking and unlocking by calling its member functions `lock()` and `unlock()`.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex);
   lock.lock();   // Explicit lock
   // Critical section
   lock.unlock(); // Explicit unlock
   ```

4. **Deferred Locking:**
   - `std::unique_lock` can be constructed without immediately locking the associated mutex. Locking can be deferred until a later point in the code.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::defer_lock);
   // Code...
   lock.lock(); // Explicitly lock when needed
   ```

5. **Conditional Locking:**
   - `std::unique_lock` allows for conditionally locking or unlocking the mutex based on certain conditions.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex);
   if (condition) {
       lock.unlock();
       // Code without the lock
   }
   ```

6. **Custom Locking Strategies:**
   - `std::unique_lock` supports various locking strategies, including `std::adopt_lock` and `std::try_to_lock`, providing more control over the locking process.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::adopt_lock);
   ```


### std::unique_lock interfaces

1. **Constructor:**
   - The primary constructor initializes a `std::unique_lock` object and optionally locks the associated mutex.

   ```cpp
   std::mutex myMutex;
   std::unique_lock<std::mutex> lock(myMutex);
   ```

   - The `std::defer_lock` parameter can be used to construct a `std::unique_lock` without immediately locking the associated mutex.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::defer_lock);
   ```

2. **Member Functions:**
a. `lock()`:
   - Manually locks the associated mutex. If the mutex is already locked, the calling thread will be blocked until the lock can be obtained.

   ```cpp
   lock.lock();
   ```

b. `try_lock()`:
   - Attempts to lock the associated mutex without blocking. Returns `true` if the lock is acquired successfully, and `false` otherwise.

   ```cpp
   if (lock.try_lock()) {
       // Lock acquired successfully
   } else {
       // Lock not acquired
   }
   ```

c. `unlock()`:
   - Manually unlocks the associated mutex. It should be called only if the lock is held by the current thread.

   ```cpp
   lock.unlock();
   ```

4. **Locking Strategies:**

a. `std::defer_lock`:
   - Used in the constructor to create a `std::unique_lock` without immediately locking the associated mutex.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::defer_lock);
   ```

b. `std::try_to_lock`:
   - Used in the constructor to attempt to lock the associated mutex without blocking.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::try_to_lock);
   ```

c. `std::adopt_lock`:
   - Used in the constructor when the mutex is already locked by the calling thread. The `std::unique_lock` object adopts the ownership of the existing lock.

   ```cpp
   std::unique_lock<std::mutex> lock(myMutex, std::adopt_lock);
   ```


--- 



### std::scoped_lock

`std::scoped_lock` is a C++11 feature that provides a convenient way to lock multiple mutexes simultaneously, preventing potential deadlocks. It is part of the `<mutex>` header and simplifies the process of acquiring multiple locks in a deadlock-free manner.

Here's a brief overview of `std::scoped_lock`:

1. **Basic Usage:**
   - `std::scoped_lock` is a lock wrapper that takes multiple `std::mutex` or `std::unique_lock` objects as arguments.
   - When a `std::scoped_lock` is constructed, it locks all the associated mutexes at once.

   ```cpp
   #include <iostream>
   #include <mutex>
   #include <thread>

   std::mutex mutex1, mutex2;

   void example_function() {
       std::scoped_lock lock(mutex1, mutex2);
       // Both mutex1 and mutex2 are locked here

       // Critical section
       std::cout << "Thread ID: " << std::this_thread::get_id() << " is in the critical section.\n";
   }

   int main() {
       std::thread t1(example_function);
       std::thread t2(example_function);

       t1.join();
       t2.join();

       return 0;
   }
   ```

2. **Locking Order:**
   - `std::scoped_lock` follows a deadlock-avoidance algorithm. It locks the provided mutexes in a predefined order to prevent potential deadlocks.
   - The order of the mutexes passed as arguments is not relevant; the `std::scoped_lock` internally sorts them.

3. **Benefits:**
   - Easier to use than managing multiple `std::unique_lock` instances manually.
   - Automatic unlocking when the `std::scoped_lock` goes out of scope, making it exception-safe.

4. **Custom Locking Policies (C++14 and Later):**
   - In C++14 and later, `std::scoped_lock` allows you to use custom locking policies by providing a set of lockable objects.

   ```cpp
   #include <iostream>
   #include <mutex>

   struct CustomLockable {
       void lock() { std::cout << "Custom lock\n"; }
       void unlock() { std::cout << "Custom unlock\n"; }
   };

   int main() {
       CustomLockable lockable;
       std::scoped_lock lock(lockable);
       // Custom locking logic is applied

       return 0;
   }
   ```

5. **Avoiding Deadlocks:**
   - When using multiple mutexes, the order in which they are locked is crucial to avoid deadlocks. `std::scoped_lock` helps by automatically choosing a consistent locking order.

Important Considerations:
- **Locking Granularity:** Be mindful of the granularity of locks to avoid unnecessary contention and improve performance.
- **Locking Duration:** Locks should be held for the minimum required duration to reduce the chances of contention.

`std::scoped_lock` simplifies the acquisition of multiple locks in a safe and efficient manner, reducing the likelihood of deadlocks and making the code more readable. It is a valuable tool in multithreading scenarios where multiple mutexes need to be managed simultaneously.

### std::shared_lock

`std::shared_lock` is a C++ feature introduced in C++14 that provides shared ownership of multiple locks. It is part of the `<shared_mutex>` header and is commonly used with `std::shared_mutex` to enable multiple threads to share read access to a shared resource concurrently.

Here's a brief overview of `std::shared_lock`:
1. **Basic Usage with `std::shared_mutex`:**
   - `std::shared_lock` is a lock wrapper that is used to acquire shared ownership of one or more `std::shared_mutex` objects.

   ```cpp
   #include <iostream>
   #include <shared_mutex>
   #include <thread>

   std::shared_mutex sharedMutex;
   int sharedData = 0;

   void read_shared_data() {
       std::shared_lock lock(sharedMutex);
       // Multiple threads can concurrently read sharedData
       std::cout << "Thread ID: " << std::this_thread::get_id() << " reads: " << sharedData << std::endl;
   }

   void write_shared_data() {
       {
           std::unique_lock lock(sharedMutex);
           // Only one thread can write to sharedData at a time
           sharedData++;
       }
       // Other threads can read sharedData concurrently
   }

   int main() {
       std::thread t1(read_shared_data);
       std::thread t2(write_shared_data);
       std::thread t3(read_shared_data);

       t1.join();
       t2.join();
       t3.join();

       return 0;
   }
   ```

2. **Benefits:**
   - `std::shared_lock` enables multiple threads to acquire shared ownership of a lock simultaneously, allowing concurrent read access.
   - It provides a convenient and safe way to manage shared access to resources.

3. **Shared Ownership:**
   - Multiple `std::shared_lock` instances can be created at the same time, allowing multiple threads to share read access.
   - The lock is released automatically when all `std::shared_lock` instances are destroyed.

4. **Upgrade to Exclusive Lock:**
   - `std::shared_lock` can be upgraded to an exclusive lock (write lock) using `std::unique_lock`. This is useful when a thread initially acquires a shared lock but later needs exclusive access.

   ```cpp
   #include <iostream>
   #include <shared_mutex>
   #include <thread>

   std::shared_mutex sharedMutex;
   int sharedData = 0;

   void read_shared_data() {
       std::shared_lock lock(sharedMutex);
       std::cout << "Thread ID: " << std::this_thread::get_id() << " reads: " << sharedData << std::endl;

       // Upgrade to exclusive lock
       std::unique_lock uniqueLock(lock);
       sharedData++;
   }
   ```

Important Considerations:
- **Compatibility:** `std::shared_lock` can be used with any lockable object, but it is particularly useful with `std::shared_mutex`. If you are working with a simple `std::mutex`, using `std::unique_lock` might be more appropriate for exclusive access.

- **Granularity:** Shared locking is beneficial when the critical section allows concurrent read access. However, consider the granularity of the locking to ensure optimal performance.

- **Upgrade Carefully:** While `std::shared_lock` can be upgraded to an exclusive lock, care must be taken to avoid potential deadlocks or performance issues.

`std::shared_lock` is a powerful tool for managing shared access to resources in a multithreaded environment. It promotes efficient concurrent read access while still allowing for exclusive write access when needed.
### Static variables in a multithreading environment

In C++11, when working with static variables in a multithreading environment, it's important to consider thread safety. A static variable declared inside a function or a method has the potential to be accessed by multiple threads concurrently, leading to race conditions if not properly synchronized. Here are some considerations and strategies for ensuring thread safety with static variables in C++11:

1. **Initialization of Static Variables:**

   - Static variables inside a function or method are initialized only once, and their initialization is not guaranteed to be thread-safe.

   ```cpp
   #include <iostream>
   #include <thread>

   void functionWithStatic() {
       static int sharedStaticVariable = 0;
       // ...
   }

   int main() {
       // Multiple threads calling the function
       std::thread t1(functionWithStatic);
       std::thread t2(functionWithStatic);

       t1.join();
       t2.join();

       return 0;
   }
   ```

2. **Thread Safety with Initialization:**

   - Use the double-checked locking pattern to ensure thread safety during the initialization of a static variable. This pattern involves checking a condition before acquiring a lock to avoid the overhead of locking in the common case where the variable is already initialized.

   ```cpp
   #include <iostream>
   #include <mutex>

   void functionWithStatic() {
       static int sharedStaticVariable = 0;
       static std::once_flag flag;

       std::call_once(flag, [](){
           // Initialization code, executed only once
           sharedStaticVariable = 42;
       });

       // Access sharedStaticVariable
       // ...
   }

   int main() {
       // Multiple threads calling the function
       std::thread t1(functionWithStatic);
       std::thread t2(functionWithStatic);

       t1.join();
       t2.join();

       return 0;
   }
   ```

   - The `std::once_flag` and `std::call_once` are part of C++11 and provide a mechanism for performing one-time initialization in a thread-safe manner.

3. **Thread Safety During Access:**

   - If the static variable is read-only or doesn't require complex initialization, there might not be a need for the double-checked locking pattern. Ensure that the operations on the variable are thread-safe.

   ```cpp
   #include <iostream>
   #include <mutex>

   void functionWithStatic() {
       static int sharedStaticVariable = 0;

       // Access sharedStaticVariable in a thread-safe way
       {
           std::lock_guard<std::mutex> lock(mutexForSharedVariable);
           // Access sharedStaticVariable
           // ...
       }
   }

   int main() {
       // Multiple threads calling the function
       std::thread t1(functionWithStatic);
       std::thread t2(functionWithStatic);

       t1.join();
       t2.join();

       return 0;
   }
   ```

   - Use a `std::mutex` to protect the shared static variable during both initialization and access.

Remember that the appropriate strategy depends on the specific use case, and it's crucial to analyze the requirements of your application to choose the right approach for ensuring thread safety with static variables.

### std::thread_local

`std::thread_local` is a keyword introduced in C++11 that is used to declare thread-local variables. A thread-local variable is a variable whose storage duration is per-thread, meaning each thread has its own separate copy of the variable. This is particularly useful in multithreaded programming where different threads may need independent instances of the same variable.

Syntax:

```cpp
thread_local <data_type> variable_name;
```

Example:

```cpp
#include <iostream>
#include <thread>

thread_local int threadSpecificValue = 0;

void threadFunction() {
    // Each thread will have its own copy of threadSpecificValue
    threadSpecificValue++;
    std::cout << "Thread-specific value: " << threadSpecificValue << std::endl;
}

int main() {
    // Create two threads
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
```

In this example, `threadSpecificValue` is declared as `thread_local`. Each thread will have its own instance of `threadSpecificValue`, and modifications made by one thread won't affect the value seen by another thread.

Key Points:

1. **Thread-Specific Storage:**
   - `std::thread_local` allows you to create thread-specific instances of variables.

2. **Storage Duration:**
   - The storage duration of a `thread_local` variable is associated with the thread it is created in. The variable is automatically destroyed when the thread exits.

3. **Initialization:**
   - `thread_local` variables are initialized the first time a thread accesses them.

4. **Use Cases:**
   - Common use cases include maintaining state that is specific to each thread, such as thread-specific logging, caches, or other per-thread resources.

5. **Note:**
   - Be cautious with the use of `thread_local`, as excessive reliance on thread-local variables can lead to increased complexity and potential issues with sharing data between threads.

`std::thread_local` is a powerful tool in managing thread-specific state and can be especially useful in scenarios where each thread needs its own independent instance of a variable.

### Lazy initialization

Lazy initialization is a programming pattern where the initialization of an object or the computation of a value is delayed until the point at which it is needed. The idea is to defer the resource-intensive or time-consuming initialization until the last possible moment, typically when the object or value is first accessed. This can help in improving performance and resource usage by avoiding unnecessary initialization for objects or values that might not be used during the program's execution.

Here's an example of lazy initialization in C++ using a simple class:

```cpp
#include <iostream>
#include <mutex>

class LazyInitializedObject {
public:
    LazyInitializedObject() {
        // Initialization code, if needed
        std::cout << "Object is being initialized.\n";
    }

    void performOperation() {
        std::cout << "Performing operation on the object.\n";
    }
};

class LazyInitializer {
public:
    LazyInitializedObject& getObject() {
        // Double-checked locking for thread safety
        if (!objectInitialized) {
            std::lock_guard<std::mutex> lock(mutex);
            if (!objectInitialized) {
                lazyInitializedObject = std::make_unique<LazyInitializedObject>();
                objectInitialized = true;
            }
        }

        return *lazyInitializedObject;
    }

private:
    std::unique_ptr<LazyInitializedObject> lazyInitializedObject;
    bool objectInitialized = false;
    std::mutex mutex;
};

int main() {
    LazyInitializer lazyInitializer;

    // Object is not initialized until this point
    LazyInitializedObject& lazyObject = lazyInitializer.getObject();

    // Now the object is initialized and can be used
    lazyObject.performOperation();

    return 0;
}
```

In this example:

- The `LazyInitializer` class is responsible for managing the lazy initialization of the `LazyInitializedObject`.
- The `getObject` function uses double-checked locking to ensure that the object is initialized only once and is thread-safe.
- The `LazyInitializedObject` is created and initialized only when `getObject` is called for the first time.

Lazy initialization is especially beneficial when the initialization process is resource-intensive or time-consuming, and there's a possibility that the object might not be used during the program's execution. It helps in deferring the cost of initialization until it becomes necessary, improving the overall efficiency of the program.


### Deadlock

A deadlock is a situation in computer science where two or more processes or threads cannot proceed because each is waiting for the other to release a resource. In other words, each process holds a resource and is also waiting for another resource acquired by some other process. Deadlocks are a common issue in concurrent programming, and they can lead to a complete halt in the execution of a program.

There are four necessary conditions for a deadlock to occur, known as the Coffman conditions:

1. **Mutual Exclusion:** At least one resource must be held in a non-sharable mode (i.e., only one process can use the resource at a time).

2. **Hold and Wait:** A process must be holding at least one resource and waiting to acquire additional resources held by other processes.

3. **No Preemption:** Resources cannot be preemptively taken away from a process. They must be explicitly released by the process holding them.

4. **Circular Wait:** There must exist a set of waiting processes such that P1 is waiting for a resource held by P2, P2 is waiting for a resource held by P3, and so on, until Pn is waiting for a resource held by P1, thus forming a circular chain of waiting.

Example:

Consider two processes, P1 and P2, and two resources, R1 and R2. The following scenario illustrates a deadlock:

1. P1 acquires R1 and requests R2.
2. P2 acquires R2 and requests R1.

At this point, both processes are waiting for the resources held by the other, resulting in a circular wait. This is a classic example of a deadlock.

Prevention and Avoidance:

To prevent deadlocks, it's essential to eliminate at least one of the Coffman conditions. Common strategies include:

- **Lock Ordering:** Establish a global order on all resources and require that each process requests resources in that order.

- **Resource Allocation Graph:** Use a resource allocation graph to detect and prevent cycles.

- **Timeouts:** Introduce timeouts to resource requests, allowing processes to give up waiting after a certain period.

- **No Hold and Wait:** Require processes to request all needed resources at once, rather than acquiring them incrementally.

- **Resource Manager:** Use a centralized resource manager to allocate resources and ensure proper synchronization.

- **Preemption:** Allow resources to be preempted from one process and allocated to another when needed.

Detecting and handling deadlocks is an important aspect of concurrent programming to ensure the reliability and responsiveness of software systems.

### Livelock

A livelock is a situation in concurrent programming where two or more processes or threads continually change their state in response to the actions of the other, but none make progress. In other words, the processes are actively trying to resolve a conflict, but due to their interactions, they remain in a state where no progress is made, and they do not return to a stable state. Livelocks can be thought of as a form of "infinite loop" in a concurrent system.

Livelocks are similar to deadlocks in that they involve processes that are stuck and unable to make progress. However, in a livelock, the processes are not waiting for a resource like in a deadlock; instead, they are actively trying to resolve a conflict but end up in a situation where they cannot break out of the loop.

Example:

Consider two people walking towards each other in a narrow hallway. Each person tries to be polite and moves to the side to let the other pass. However, they both choose the same side, and when they try to correct their path, they end up blocking each other again. This cycle repeats, and neither person is able to make progress down the hallway.

Characteristics of Livelocks:

1. **Continuous Activity:** In a livelock, processes are continuously active, trying to resolve a conflict or avoid interference.

2. **No Forward Progress:** Despite their activity, the processes involved in a livelock do not make any forward progress towards reaching a stable state.

3. **Self-Perpetuating:** The livelock situation can be self-perpetuating, with the processes remaining stuck in a loop until some external intervention breaks the cycle.

Prevention and Mitigation:

Preventing livelocks can be challenging, but some strategies include:

- **Randomization:** Introduce randomness in decision-making processes to break deterministic patterns that lead to livelocks.

- **Timeouts:** Use timeouts to limit the duration of certain activities or waiting periods, after which the processes can take alternative actions.

- **Backoff Strategies:** Implement backoff strategies where processes temporarily cease their activities to allow the system to recover.

- **Conflict Resolution:** Improve conflict resolution mechanisms to reduce the likelihood of processes interfering with each other.

Livelocks are undesirable in concurrent systems as they can lead to performance degradation and unresponsiveness. Detecting and mitigating livelocks often requires careful design and analysis of the system's concurrency mechanisms.

## Links

<- Back to [Main](../README.md)