dates:: 2024-01-13 14:19

---

Context:
- [Concurrency vs Parallelism](#Concurrency%20vs%20Parallelism)
- [Parallelism](#Parallelism)
- [Computer with Single Processor](#Computer%20with%20Single%20Processor)
- [Computer with Single Processor and Cache](#Computer%20with%20Single%20Processor%20and%20Cache)
- [Computer with Multiple Processors](#Computer%20with%20Multiple%20Processors)
- [Synchronization Issues](#Synchronization%20Issues)

---

Concurrency in C++ refers to the ability of a program to execute multiple tasks simultaneously, allowing for more efficient utilization of computing resources. It involves the concurrent execution of threads, which are independent sequences of instructions within a program.

Key concepts related to concurrency in C++ include:

1. **Thread:** A thread is the smallest unit of execution within a process. A process can have multiple threads, and each thread runs independently, performing its own set of tasks.

2. **Concurrency vs. Parallelism:** Concurrency is a broader concept that involves managing multiple tasks at the same time, while parallelism specifically refers to the simultaneous execution of multiple tasks on multiple processors or cores.

3. **std::thread:** C++ provides a standard library for managing threads, including features like thread creation, synchronization, and communication between threads.

4. **Mutex (std::mutex):** Mutex (mutual exclusion) is a synchronization primitive used to protect shared resources from being accessed simultaneously by multiple threads. It helps avoid data races and ensures thread safety.

5. **std::async and std::future:** These components are part of the C++ Standard Library and allow for asynchronous execution of tasks. `std::async` creates a new thread to execute a function asynchronously, and `std::future` is used to retrieve the result.

6. **Atomic Operations (std::atomic):** Atomic operations ensure that certain operations on variables are executed without interruption, preventing data races. C++ provides atomic types and operations in the `std::atomic` header.

Concurrency in C++ can lead to improved performance and responsiveness in applications, especially in scenarios where tasks can be executed independently. However, it also introduces challenges such as race conditions, deadlocks, and the need for proper synchronization mechanisms.

C++17 and later versions have introduced additional features and improvements to make working with concurrency safer and more convenient, such as the `<execution>` header, parallel algorithms, and a standard memory model for better-defined behavior in concurrent programs.

### Concurrency vs Parallelism

Concurrency and parallelism are related concepts in the context of computer science, but they refer to different ways of achieving multiple tasks in a program or system.

Concurrency:
Concurrency is a broader concept that deals with the execution of multiple tasks over a period of time. In a concurrent system, tasks can start, run, and complete in overlapping time intervals, even if they are not necessarily executed simultaneously. The focus is on managing multiple tasks and making progress on all of them, often using techniques like interleaved execution or time-slicing. Concurrency is particularly relevant in scenarios where tasks can be executed independently, such as in asynchronous programming.

**Key points about concurrency:**
- **Not necessarily simultaneous:** Tasks can overlap in time, but they might not be executed at the exact same moment.
- **Single-threaded or multi-threaded:** Concurrency can be achieved with a single thread of execution or multiple threads.
- **Cooperative multitasking:** Tasks yield control voluntarily, allowing the system to switch between them.

### Parallelism
Parallelism is the simultaneous execution of multiple tasks or processes to improve efficiency and performance. In a parallel system, tasks are executed at the same time, often leveraging multiple processors or cores. The primary goal of parallelism is to divide a larger task into smaller subtasks that can be executed concurrently for faster overall computation.

**Key points about parallelism:**
- **Simultaneous execution:** Multiple tasks are executed at the exact same time.
- **Multi-threaded or multi-process:** Parallelism can involve multiple threads within a process or multiple processes running independently.
- **Division of labor:** Tasks are divided into smaller units to be executed in parallel.

In summary, concurrency is about managing multiple tasks and making progress on all of them over time, whether they run simultaneously or not. Parallelism specifically involves the simultaneous execution of tasks to achieve faster computation. Concurrency is more about the structure of the program, while parallelism is more about the execution of the program on hardware with multiple resources. It's also worth noting that a system can be both concurrent and parallel, and the terms are often used in conjunction.

### Computer with Single Processor

![](./images/Pasted%20image%2020240113145219.png)

A computer with a single processor, often referred to as a single-core processor system, is a system that has only one central processing unit (CPU). In such a system, the CPU is responsible for executing all the tasks and processing instructions.

Here are some key characteristics of a computer with a single processor:

1. **Single Core:** The processor has only one processing core. A core is a physical processing unit on the CPU chip that can execute instructions independently.

2. **Sequential Execution:** Tasks and instructions are processed one at a time, in a sequential manner. The CPU executes instructions in the order they are received.

3. **Limited Parallelism:** Since there is only one core, the computer has limited ability to execute tasks in parallel. Even if the operating system is designed to manage multiple tasks concurrently, they share the same core and must take turns executing.

4. **Task Switching:** The operating system employs task switching to give the illusion of multitasking. It rapidly switches between different tasks, providing the appearance of concurrent execution.

5. **Resource Limitations:** In terms of processing power, a single-core system may have limitations compared to multi-core systems, especially when it comes to handling computationally intensive tasks.

6. **Power Efficiency:** Single-core systems are often power-efficient, as there is only one core consuming energy. This can be advantageous in scenarios where power consumption is a critical consideration.

7. **Less Complex:** Single-core systems are generally less complex than multi-core systems, making them cost-effective and suitable for less demanding computing needs.

While modern computers often feature multi-core processors for improved performance, single-core systems are still found in simpler devices, embedded systems, and some specialized applications where the computational demands are modest.

It's important to note that the shift to multi-core processors has become prevalent in modern computing due to the increased demand for parallel processing capabilities, which can lead to better performance in multitasking and parallelizable workloads.

### Computer with Single Processor and Cache

![](./images/Pasted%20image%2020240113145131.png)

A computer with a single processor and cache is a common configuration in many systems, especially in entry-level or low-power computing devices. Let's explore the key components and characteristics of such a system:

 1. Processor (CPU):
- **Single Processor:** The system is equipped with a single central processing unit (CPU). The CPU is responsible for executing instructions and performing calculations.

2. Cache Memory:
- **L1 Cache and L2 Cache:** The processor typically has multiple levels of cache memory. The L1 cache is the closest to the CPU cores and is usually divided into instruction cache (L1i) and data cache (L1d). The L2 cache is larger and provides additional storage for frequently accessed data.

3. Main Memory (RAM):
- **Main Memory:** The system has main memory (RAM), which is used for storing data and instructions that are actively being used by the CPU. While the cache provides fast and small-capacity memory close to the CPU, RAM offers larger but comparatively slower storage.

4. Bus Architecture:
- **Front-Side Bus (FSB):** The CPU communicates with other components, such as memory and peripheral devices, through a system bus. The Front-Side Bus is a common bus architecture that facilitates data transfer between the CPU and other parts of the system.

5. Motherboard:
- **Motherboard:** The motherboard provides the physical connections and interfaces for various components, including the CPU, memory modules, and peripheral devices. It serves as the central circuit board for the system.

6. Input/Output (I/O) Interfaces:
- **Peripheral Connectivity:** The computer includes interfaces for connecting external devices, such as USB ports, audio jacks, and network ports.

7. Graphics Processing (GPU):
- **Integrated or Dedicated GPU:** Graphics processing may be handled by an integrated graphics processor or a dedicated graphics card, depending on the specific configuration.

 8. Storage:
- **Storage Devices:** The computer includes storage devices (e.g., hard disk drives or solid-state drives) for long-term data storage.

9. Power Supply:
- **Power Supply Unit (PSU):** The PSU provides electrical power to the various components in the system.

10. Operating System:
- **Operating System (OS):** The computer runs an operating system that manages hardware resources, facilitates communication between software and hardware, and provides a user interface.

A computer with a single processor and cache is suitable for basic computing tasks such as web browsing, document editing, and light multimedia consumption. While it may not provide the same level of performance as systems with multiple processors or advanced parallel architectures, it can meet the needs of users with less demanding requirements.

### Computer with Multiple Processors

![](./images/Pasted%20image%2020240113145434.png)

A computer with multiple processors, often referred to as a multiprocessor or multi-CPU system, is designed to harness the power of multiple central processing units (CPUs) to enhance overall system performance. Here are the key components and characteristics of a computer with multiple processors:

1. Multiple Processors (CPUs):
- **Dual, Quad, or More:** The system is equipped with two or more processors, each having its own set of cores. Common configurations include dual-core, quad-core, hexa-core, octa-core, and even higher core counts.

2. Cache Hierarchy:
- **L1, L2, and Possibly L3 Caches:** Each processor may have its own levels of cache memory (L1, L2), and there might be a shared L3 cache that facilitates communication between different processors.

3. Main Memory (RAM):
- **Large RAM Capacity:** A multiprocessor system often includes a larger main memory capacity to accommodate the needs of multiple processors working concurrently.

4. Interconnects:
- **Processor Interconnects:** Specialized interconnects or buses facilitate communication between processors. These interconnects play a crucial role in enabling efficient data sharing and coordination between processors.

5. Symmetric Multiprocessing (SMP) Architecture:
- **Symmetric Access to Resources:** In an SMP system, all processors have equal access to system resources, including memory and I/O devices. This architecture allows any processor to perform any task.

6. Bus or Switch-Based Architecture:
- **System Bus or Switch Fabric:** Depending on the architecture, the system might use a traditional bus or a more advanced switch fabric to connect processors and other components.

7. Operating System Support:
- **Multithreading Support:** The operating system must support multithreading to effectively manage the concurrent execution of tasks across multiple processors.

8. Parallel Programming:
- **Parallel Software Development:** Applications need to be developed or optimized for parallel execution to take full advantage of multiple processors.

9. Scalability:
- **Scalable Performance:** The system can exhibit scalable performance, meaning that adding more processors can lead to a proportional increase in computational power for certain types of tasks.

10. High-Performance Computing (HPC):
- **Use in High-Performance Computing:** Multiprocessor systems are commonly used in scientific and engineering applications, simulations, rendering, and other computationally intensive tasks.

11. Redundancy and Reliability:
- **Fault Tolerance:** Some multiprocessor systems may incorporate redundancy and fault-tolerant features to ensure continued operation even in the presence of hardware failures.

12. Parallel Processing Paradigms:
- **Parallelization Techniques:** Applications may use parallel processing paradigms such as task parallelism, data parallelism, or a combination of both.

Multiprocessor systems are suitable for tasks that can be divided into smaller subtasks that can be executed concurrently. These systems provide enhanced performance, making them well-suited for tasks that require substantial computational power.

### Synchronization Issues

![](./images/Pasted%20image%2020240113145626.png)

Synchronization issues arise in concurrent programming when multiple threads or processes access shared resources concurrently, and there is a possibility of interference or inconsistent results due to the lack of proper coordination. These issues can lead to race conditions, deadlocks, and data inconsistency. Here are some common synchronization issues:

1. **Race Conditions:**
   - **Definition:** A race condition occurs when the behavior of a program depends on the relative timing of events, such as the order of execution of threads.
   - **Example:** Multiple threads accessing and modifying a shared variable without proper synchronization can result in unpredictable outcomes.

2. **Deadlocks:**
   - **Definition:** A deadlock is a situation where two or more threads are unable to proceed because each is waiting for the other to release a resource.
   - **Example:** Thread A holds resource X and waits for resource Y, while thread B holds resource Y and waits for resource X.

3. **Starvation:**
   - **Definition:** Starvation happens when a thread is unable to gain access to a resource it needs for an extended period because other threads are continuously acquiring and releasing the resource.
   - **Example:** A thread with lower priority continuously gets preempted by threads with higher priority, preventing it from accessing shared resources.

4. **Priority Inversion:**
   - **Definition:** Priority inversion occurs when a higher-priority task is forced to wait for a lower-priority task to release a resource.
   - **Example:** Thread A (high priority) is waiting for a resource held by Thread B (low priority), and Thread B is preempted by Thread C (medium priority).

5. **Data Inconsistency:**
   - **Definition:** Data inconsistency occurs when multiple threads access shared data concurrently, leading to unexpected or incorrect values.
   - **Example:** Two threads read and modify the same variable simultaneously without proper synchronization, resulting in unpredictable values.

6. **Atomicity Violation:**
   - **Definition:** Atomicity violation happens when an operation that should be executed as a single, indivisible unit is interrupted, leading to unexpected results.
   - **Example:** Incrementing a shared counter without proper atomic operations may result in partial updates if two threads attempt to increment the counter simultaneously.

7. **Ordering Issues:**
   - **Definition:** Ordering issues occur when the order of execution of instructions or events affects the program's behavior.
   - **Example:** The interleaved execution of instructions in different threads may lead to unexpected outcomes if the order is not properly managed.

To address synchronization issues, various synchronization mechanisms and techniques are used, including locks, mutexes, semaphores, condition variables, and atomic operations. Proper synchronization ensures that shared resources are accessed in a controlled and coordinated manner, minimizing the risk of issues related to concurrency.

--- 

## Links

<- Back to [Main](../README.md)