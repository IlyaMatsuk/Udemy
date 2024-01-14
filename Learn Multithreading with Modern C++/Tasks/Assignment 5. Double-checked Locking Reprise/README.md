In the video in Section 4 on "Lazy Initialization", we discussed double-checked locking. This is a popular but error-prone way to implement the Singleton pattern, in which only one object of a class can be created.

The key part of the code looks like this (the full source code is in the attached ZIP file)

if (!ptr) {                                     // First check of ptr (1)
    std::lock_guard<std::mutex> lk(process_mutex);
 
    if (!ptr)                                   // Second check of ptr (2)
        ptr = new some_type;                    // Allocate and initialize (3)
}

The problem is that the initialization at (3) actually consists of three separate operations:

Allocate memory

Initialize memory

Set ptr to the address of the allocated memory

A thread can be interrupted between any one of these operations. Also, an optimizing compiler can reorder these operations, so that ptr is set before the memory is initialized.

Another thread B could interleave and perform the check at (1) while thread A is paused. It is possible that ptr is non-null,  even though the memory has not been initialized. Thread B will then by-pass the mutex lock, because ptr is not null, and it will then use uninitialized memory.

(If you are not clear about this, I suggest you review the "Lazy Initialization" video before proceeding.)

Questions for this assignment
Can we solve this problem by making ptr an atomic variable?

Write a program which implements double-checked locking and uses an atomic variable. Check that your program compiles and runs correctly.