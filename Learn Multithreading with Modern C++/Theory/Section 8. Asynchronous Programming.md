dates:: 2024-01-13 17:06

---

Context:
- [Synchronous and Asynchronous Programming](#Synchronous%20and%20Asynchronous%20Programming)
- [std packaged_task](#std%20packaged_task)
- [std async](#std%20async)
- [Choosing a Thread Object](#Choosing%20a%20Thread%20Object)

---
### Synchronous and Asynchronous Programming

Synchronous and asynchronous programming refer to two different approaches to managing the flow of execution in a program, particularly when dealing with operations that may take some time to complete, such as I/O operations, network requests, or computations.

Synchronous Programming:

1. **Sequential Execution:**
   - In synchronous programming, tasks are executed in a sequential order, one after another.
   - Each task must complete before the program moves on to the next one.

2. **Blocking:**
   - Synchronous operations are blocking, meaning that the program is paused while waiting for an operation to finish.
   - This can lead to inefficiency, especially when dealing with I/O-bound tasks where waiting for data can consume valuable processing time.

3. **Easy to Understand:**
   - Synchronous code is often simpler and easier to reason about since the flow of control is straightforward.

4. **Example (C++ with Blocking I/O):**
   ```cpp
   #include <iostream>
   #include <fstream>

   int main() {
       std::ifstream file("example.txt");
       std::string content;

       // Blocking operation
       file >> content;

       // Process content after reading
       std::cout << content << std::endl;

       return 0;
   }
   ```

Asynchronous Programming:

1. **Concurrent Execution:**
   - Asynchronous programming allows tasks to run concurrently, without waiting for the completion of each task before starting the next one.

2. **Non-Blocking:**
   - Asynchronous operations are non-blocking, allowing the program to continue its execution while waiting for certain tasks to complete.

3. **Callbacks or Promises:**
   - Callbacks or promises are often used to handle the result of asynchronous operations.
   - Callback functions are executed when the asynchronous operation completes.

4. **Complexity and Callback Hell:**
   - Asynchronous code can become more complex, especially when dealing with multiple asynchronous operations. This can lead to callback hell or the "pyramid of doom" if not managed properly.

5. **Example (JavaScript with Asynchronous I/O using Promises):**
   ```javascript
   const fs = require('fs').promises;

   async function readFileAsync() {
       try {
           // Non-blocking operation
           const content = await fs.readFile('example.txt', 'utf-8');
           console.log(content);
       } catch (error) {
           console.error('Error reading file:', error);
       }
   }

   readFileAsync();
   ```

Choosing Between Synchronous and Asynchronous:

- **Use Synchronous When:**
  - The program's simplicity and readability are a priority.
  - The operations are not I/O-bound or time-consuming.
  - Blocking is acceptable without impacting overall performance.

- **Use Asynchronous When:**
  - Efficiency and responsiveness are critical.
  - Dealing with I/O-bound tasks or tasks that may take a significant amount of time.
  - Concurrent execution is necessary to achieve better performance.

Both synchronous and asynchronous programming have their places in different scenarios, and the choice between them depends on the requirements and goals of the specific application or system. Modern systems often use a combination of both approaches to balance simplicity and efficiency.

### std::packaged_task

`std::packaged_task` is a template class in C++ that provides a convenient way to package a function or callable object for asynchronous execution. It is part of the `<future>` header and is often used in combination with `std::thread`, `std::async`, or other mechanisms that involve running code in a separate thread.

Here's a basic overview of `std::packaged_task`:

1. Declaration:
   - Include the `<future>` header to use `std::packaged_task`.

   ```cpp
   #include <future>
   ```

2. Creating a `std::packaged_task`:
   - Declare a `std::packaged_task` by providing a callable object (function or functor) as a template parameter.

   ```cpp
   std::packaged_task<int()> task([]() { return 42; });
   ```

3. Executing the Task:
   - To execute the packaged task, create a `std::future` using the `get_future` member function and then call the `operator()` on the task.

   ```cpp
   std::future<int> resultFuture = task.get_future();
   task();  // Executes the packaged task
   ```

4. Using with `std::thread`:
   - `std::packaged_task` can be used with `std::thread` to run the task asynchronously.

   ```cpp
   std::packaged_task<int()> task([]() { return 42; });
   std::thread workerThread(std::move(task));
   workerThread.join();
   ```

Example:

Here's a simple example demonstrating the use of `std::packaged_task`:

```cpp
#include <iostream>
#include <future>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    // Create a packaged task for the 'add' function
    std::packaged_task<int(int, int)> task(add);

    // Get a future associated with the packaged task
    std::future<int> resultFuture = task.get_future();

    // Execute the packaged task in a separate thread
    std::thread workerThread(std::move(task), 10, 20);
    workerThread.join();

    // Retrieve the result from the future
    int result = resultFuture.get();

    // Print the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
```

In this example, a packaged task is created for the `add` function, which takes two integers and returns their sum. The packaged task is then executed in a separate thread using `std::thread`, and the result is obtained from the associated `std::future`. The flexibility of `std::packaged_task` allows you to encapsulate callable objects and run them asynchronously, providing a more flexible alternative to `std::async`.

### std::async

`std::async` is a function template in C++ that provides a high-level interface for launching asynchronous tasks. It is part of the `<future>` header and is designed to simplify the use of asynchronous programming by encapsulating the creation of `std::thread`, `std::packaged_task`, and `std::promise` behind a single, easy-to-use interface.

Here's a basic overview of `std::async`:

1. Declaration:
   - Include the `<future>` header to use `std::async`.

   ```cpp
   #include <future>
   ```

2. Creating an Asynchronous Task:
   - Use `std::async` to create an asynchronous task by providing a callable object (function or functor) and optional arguments.

   ```cpp
   std::future<int> resultFuture = std::async(add, 10, 20);
   ```

   - In this example, `add` is a function that takes two integers and returns their sum.

3. Launch Policies:
   - `std::async` supports launch policies that control how the asynchronous task is executed. The default policy is `std::launch::async | std::launch::deferred`.

   ```cpp
   std::future<int> resultFuture = std::async(std::launch::async, add, 10, 20);
   ```

   - The `std::launch::async` policy forces the task to be executed asynchronously in a separate thread. The `std::launch::deferred` policy allows the system to decide whether to execute the task immediately or wait until the `get` function is called.

Example:

Here's a simple example demonstrating the use of `std::async`:

```cpp
#include <iostream>
#include <future>

int add(int a, int b) {
    return a + b;
}

int main() {
    // Launch an asynchronous task using std::async
    std::future<int> resultFuture = std::async(add, 10, 20);

    // Do other work while the asynchronous task is running

    // Wait for the result and retrieve it
    int result = resultFuture.get();

    // Print the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
```

In this example, `std::async` is used to launch an asynchronous task that adds two numbers. The program can continue with other work while the asynchronous task is running, and the result is obtained using the `get` function when needed. The default launch policy is used, allowing the system to decide whether to execute the task immediately or defer its execution.

### Choosing a Thread Object

﻿We now have three different ways to execute a task:
- Create an std::thread object
- Create an std::packaged_task object
- Call std::async()

**Advantages of std::async()**
- The simplest way to execute a task
	- Easy to obtain the return value from a task
	- Or to catch any exception thrown in the task
	- Choice of running the task synchronously or asynchronously
- Higher-level abstraction than std::thread
	- The library manages the threads for the programmer
	- And the inter-thread communication
	- No need to use shared data

﻿**Disadvantages of async()**
﻿- Cannot detach tasks
﻿- A task executed with std::launch::async is "implicitly joined"
﻿  ```cpp
﻿  {
	auto fut = std::async(std::launch::async, hello);
  } // Calls "fut()
  ```

- The returned future's destructor will block
	- Until the task completes

﻿**Advantages of std::packaged_task**
﻿- The best choice if we want to represent tasks as objects
	﻿- e.g. to create a container of tasks
- A lower-level abstraction than std::async()
	- Can control when a task is executed
	- Can control on which thread it is executed

 **Advantages of std::thread**
- The most flexible
	- Allows access to the underlying software thread
	- Useful for features not supported by standard C++ 
	- Can be detached

**Recommendations**
﻿- Use std::async()
	﻿- For starting a new thread in general
 - Use std::packaged_task
	- For containers of thread objects
- Use std::thread
	 - For starting a detachable thread
	 - For more specialized requirements

--- 

## Links

<- Back to [Main](../README.md)