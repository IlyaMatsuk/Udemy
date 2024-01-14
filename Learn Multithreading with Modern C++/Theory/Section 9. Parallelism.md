dates:: 2024-01-13 17:28

---

Context:
- [Parallelism](#Parallelism)
- [Data Parallelism](#Data%20Parallelism)
- [Execution Policies](#Execution%20Policies)
- [Algorithms and Execution Policies](#Algorithms%20and%20Execution%20Policies)

---
### Parallelism

Parallelism in computing refers to the simultaneous execution of multiple tasks or processes to improve overall system throughput and performance. It is a fundamental concept in both hardware and software design and is commonly utilized to make better use of available resources, particularly in multi-core processors and distributed computing environments.

Here are key aspects of parallelism:

1. **Task Parallelism:**
   - **Definition:** Task parallelism involves breaking down a larger task into smaller, independent tasks that can be executed concurrently.
   - **Example:** In a parallelized sorting algorithm, different portions of the array can be sorted simultaneously.

2. **Data Parallelism:**
   - **Definition:** Data parallelism involves distributing data across multiple processing units and performing the same operation on each unit concurrently.
   - **Example:** Parallelizing a matrix multiplication where each element of the result matrix is computed independently.

3. **Parallel Hardware Architectures:**
   - **Multi-Core Processors:** Modern CPUs often have multiple cores, each capable of executing its own set of instructions independently.
   - **Graphics Processing Units (GPUs):** GPUs are designed for parallelism and are highly effective in handling parallelizable tasks, especially in graphics rendering and scientific computing.
   - **Parallel Computing Clusters:** Distributed systems or clusters of computers can be used to perform parallel computations on a larger scale.

4. **Parallel Programming Models:**
   - **Threads:** Threads are lightweight, independent units of execution within a process. Parallel programming using threads is common in multi-core systems.
   - **Message Passing:** In distributed computing, processes communicate by passing messages. MPI (Message Passing Interface) is a popular standard for this model.
   - **Task-Based Parallelism:** Parallelism is expressed in terms of tasks that can be executed independently. Examples include C++11's `std::async` and Intel TBB (Threading Building Blocks).

5. **Parallel Algorithms:**
   - Parallel algorithms are designed to exploit parallel processing capabilities and improve the efficiency of computations.
   - Examples include parallel sorting algorithms, parallel search algorithms, and parallel matrix operations.

Example (C++ with `std::async`):

```cpp
#include <iostream>
#include <future>

int add(int a, int b) {
    return a + b;
}

int main() {
    // Launch two asynchronous tasks in parallel
    std::future<int> resultFuture1 = std::async(add, 10, 20);
    std::future<int> resultFuture2 = std::async(add, 30, 40);

    // Do other work while the tasks are running

    // Wait for the results and retrieve them
    int result1 = resultFuture1.get();
    int result2 = resultFuture2.get();

    // Print the results
    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
```

In this example, two asynchronous tasks are launched in parallel using `std::async`. The program can continue with other work while the tasks are running, and the results are obtained using the `get` function when needed. This demonstrates a simple form of task parallelism in C++.

### Data Parallelism

Data parallelism is a parallel computing paradigm where the same operation is applied to multiple pieces of data simultaneously. The primary goal is to distribute data across multiple processing units, such as CPU cores or GPU threads, and perform parallel computations on each piece of data concurrently. This paradigm is particularly effective for tasks that can be parallelized by applying the same operation independently to different elements of a dataset.

Key characteristics and concepts related to data parallelism include:

1. **Independence of Data:**
   - In data parallelism, each piece of data is processed independently of others. The operations performed on one piece of data do not depend on the results of operations on other pieces.

2. **Vectorization:**
   - Vectorization is a technique used in data parallelism where operations are performed on entire vectors or arrays of data elements in a single instruction. SIMD (Single Instruction, Multiple Data) instructions in modern CPUs are an example of vectorization.

3. **SIMD Architectures:**
   - SIMD architectures support data parallelism by allowing the execution of a single instruction on multiple data elements simultaneously. This is commonly used in vector processors, GPUs, and modern CPU instruction sets like SSE (Streaming SIMD Extensions) and AVX (Advanced Vector Extensions).

4. **Parallel Algorithms for Data Parallelism:**
   - Data parallelism often involves parallelizing algorithms that operate on large datasets, such as parallel sorting, parallel searching, and parallel matrix operations.
   - The parallelization is achieved by dividing the dataset into chunks, and each chunk is processed independently.

Example (C++ with Parallel Accumulation):

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

int main() {
    // Create a vector of integers
    std::vector<int> numbers(1000000, 1);

    // Perform parallel accumulation using std::reduce and std::execution::par
    int sum = std::reduce(std::execution::par, numbers.begin(), numbers.end(), 0);

    // Print the result
    std::cout << "Parallel Sum: " << sum << std::endl;

    return 0;
}
```

In this example, `std::reduce` is used with `std::execution::par` to perform parallel accumulation of integers in a vector. The operation is applied concurrently to different segments of the vector, taking advantage of data parallelism.

Note: The availability of parallel execution policies and their efficiency may vary depending on the C++ compiler and library implementations.

### Execution Policies

Execution policies in C++ are a feature introduced in the C++ Standard Library to support parallelism and allow developers to express their intent regarding the execution strategy for certain algorithms. Execution policies are used with parallel algorithms to specify whether the algorithm should be executed sequentially, in parallel, or using vectorization.

C++17 introduced three execution policies for parallel algorithms:

1. **`std::execution::seq` (Sequential Execution):**
   - The algorithm is executed sequentially.
   - This is the default execution policy if none is specified explicitly.

   ```cpp
   #include <algorithm>
   #include <vector>

   int main() {
       std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

       // Sequential sort
       std::sort(std::execution::seq, numbers.begin(), numbers.end());

       return 0;
   }
   ```

2. **`std::execution::par` (Parallel Execution):**
   - The algorithm is executed in parallel, utilizing multiple threads if available.
   - It is up to the implementation to determine the degree of parallelism.

   ```cpp
   #include <algorithm>
   #include <vector>

   int main() {
       std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

       // Parallel sort
       std::sort(std::execution::par, numbers.begin(), numbers.end());

       return 0;
   }
   ```

3. **`std::execution::par_unseq` (Parallel and Unsequenced Execution):**
   - The algorithm is executed in parallel, and vectorization (SIMD) may be applied to enhance performance.
   - It combines parallel execution with vectorization when applicable.

   ```cpp
   #include <algorithm>
   #include <vector>

   int main() {
       std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

       // Parallel and unsequenced sort
       std::sort(std::execution::par_unseq, numbers.begin(), numbers.end());

       return 0;
   }
   ```

4. **`std::execution::unseq` (Unsequenced Execution):**
   - The algorithm is executed in unsequenced order, and vectorization (SIMD) may be applied.
   - It is primarily used with algorithms that operate on ranges of values without dependencies between elements.

   ```cpp
   #include <algorithm>
   #include <vector>

   int main() {
       std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

       // Unsequenced sort
       std::sort(std::execution::unseq, numbers.begin(), numbers.end());

       return 0;
   }
   ```

When using these execution policies, it's important to note that not all algorithms can be efficiently parallelized. Additionally, the actual parallelism achieved depends on the specific compiler and library implementation. Always check the documentation and benchmarks for your particular compiler and platform.

Starting with C++20, additional execution policies, such as `std::execution::par_unseq` and `std::execution::unseq`, were introduced to provide more fine-grained control over the execution strategy.

### Algorithms and Execution Policies

Certainly! Here's a list of commonly used algorithms in C++ that can be used with execution policies without specific examples:

1. **For-Each Algorithms:**
   - `std::for_each`
   - `std::for_each_n`
   - `std::for_each` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

2. **Transform Algorithms:**
   - `std::transform`
   - `std::transform_ex`
   - `std::transform_reduce`
   - `std::transform_reduce_ex`
   - `std::transform` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

3. **Sort Algorithms:**
   - `std::sort`
   - `std::partial_sort`
   - `std::partial_sort_copy`
   - `std::stable_sort`
   - `std::nth_element`
   - `std::sort` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

4. **Search Algorithms:**
   - `std::find`
   - `std::find_if`
   - `std::search`
   - `std::search_n`
   - `std::adjacent_find`
   - `std::find`, `std::find_if`, `std::search`, `std::search_n`, and `std::adjacent_find` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

5. **Copy Algorithms:**
   - `std::copy`
   - `std::copy_if`
   - `std::copy_n`
   - `std::copy_backward`
   - `std::copy`, `std::copy_if`, `std::copy_n`, and `std::copy_backward` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

6. **Reduce Algorithms:**
   - `std::accumulate`
   - `std::reduce`
   - `std::inclusive_scan`
   - `std::exclusive_scan`
   - `std::transform_reduce`
   - `std::inclusive_scan`, `std::exclusive_scan`, and `std::transform_reduce` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

7. **Partitioning Algorithms:**
   - `std::partition`
   - `std::stable_partition`
   - `std::partition_point`
   - `std::partition`, `std::stable_partition`, and `std::partition_point` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

8. **Min/Max Algorithms:**
   - `std::min_element`
   - `std::max_element`
   - `std::min`
   - `std::max`
   - `std::minmax_element`
   - `std::min_element`, `std::max_element`, `std::min`, `std::max`, and `std::minmax_element` with `std::execution::seq`, `std::execution::par`, `std::execution::par_unseq`, and `std::execution::unseq` options.

These algorithms cover a range of operations, and by using execution policies, you can specify the desired level of parallelism or vectorization for their execution. Keep in mind that not all algorithms are equally amenable to parallelization, and the effectiveness of parallelism depends on the specific algorithm and the characteristics of the data being processed.

--- 

## Links

<- Back to [Main](../README.md)