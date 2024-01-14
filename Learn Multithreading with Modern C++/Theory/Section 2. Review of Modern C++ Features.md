dates:: 2024-01-12 18:32

---

Context:
- [nullptr](#nullptr)
- [Universal Initialization](#Universal%20Initialization)
- [std chrono](#std%20chrono)
- [auto keyword](#auto%20keyword)
- [auto with qualifiers](#auto%20with%20qualifiers)
- [range-based for loop](#range-based%20for%20loop)
- [Lambda Expression](#Lambda%20Expression)
- [lvalue and rvalue](#lvalue%20and%20rvalue)
- [std move](#std%20move)
- [Rvalue references and overloading](#Rvalue%20references%20and%20overloading)
- [Move-Only Types](#Move-Only%20Types)
- [Move operators](#Move%20operators)
- [Deleted and Defaulted Operators](#Deleted%20and%20Defaulted%20Operators)
- [Random Number Classes](#Random%20Number%20Classes)
- [std unique_ptr](#std%20unique_ptr)

---
### nullptr

`nullptr` is a keyword introduced in the C++11 standard to represent a null pointer. It is a constant of type `std::nullptr_t`, and it is used to indicate that a pointer doesn't point to any memory location.

Before the introduction of `nullptr`, programmers commonly used the integer constant `0` or the macro `NULL` to represent null pointers. However, this could lead to ambiguity in certain situations, as `0` or `NULL` could also be used as integer values.

With `nullptr`, C++ provides a clear and unambiguous way to represent null pointers. It is often preferred over using `0` or `NULL` for better type safety and to avoid potential issues with overloaded functions or templates.

### Universal Initialization

Universal initialization refers to the ability to initialize variables using curly braces `{}` syntax. This syntax provides a consistent and flexible way to initialize variables, regardless of their type. Universal initialization is also known as uniform or brace initialization.

```cpp
int x{10};
float pi{3.14};
char ch{'A'};
```

### std::chrono

In C++, the `<chrono>` header provides a set of facilities for performing operations involving time, such as measuring durations and representing points in time. The `<chrono>` library is part of the C++ Standard Library and was introduced in C++11.

Here's a brief overview of key components in `std::chrono`:

1. **Durations (`std::chrono::duration`):**
   - Represents a time span or duration. Examples include seconds, milliseconds, microseconds, etc.
   - Allows arithmetic operations such as addition, subtraction, and multiplication with scalar values.

2. **Time Points (`std::chrono::time_point`):**
   - Represents a point in time.
   - Combines a duration and an epoch (a reference point in time, like the system clock's start).

3. **Clocks (`std::chrono::system_clock`, `std::chrono::steady_clock`, `std::chrono::high_resolution_clock`):**
   - Provides access to the current time.
   - `system_clock`: Represents the system-wide real-time clock.
   - `steady_clock`: Represents a monotonic clock, often used for measuring durations.
   - `high_resolution_clock`: An alias for either `system_clock` or `steady_clock` with higher precision, if available.

4. **Time Utilities:**
   - `std::chrono::time_point_cast`: Converts between time points with different durations.
   - `std::chrono::duration_cast`: Converts between durations with different units.
   - `std::chrono::duration` and `std::chrono::time_point` have specialized templates for common durations and time points.

5. **Clock Conversions:**
   - `std::chrono::utc_clock` and `std::chrono::tai_clock` for representing time in Coordinated Universal Time (UTC) and International Atomic Time (TAI), respectively.

### auto keyword

The `auto` keyword is used for automatic type inference, allowing the compiler to deduce the type of a variable based on its initializer. It is part of C++11 and later standards and is particularly useful in situations where the type is either complex or verbose, making code more concise and readable.

Here's a brief description of the `auto` keyword:

1. **Automatic Type Inference:**
   - `auto` allows the compiler to automatically deduce the type of a variable based on its initializer.

2. **Saves Typing and Enhances Readability:**
   - Particularly beneficial when dealing with complex or verbose type names, saving developers from explicitly specifying the type.

3. **Usage Examples:**
   - Used with variable declarations: `auto variable_name = initializer;`
   - Used in range-based for loops: `for (auto element : container) { /* ... */ }`
   - Used with lambda expressions: `auto lambda_function = [](int x) { return x * 2; };`

4. **Compiler-Generated Type:**
   - The compiler generates the appropriate type during compilation, ensuring type safety.

### auto with qualifiers

When using `auto` with qualifiers, the deduced type includes the qualifiers present in the initialization expression. Qualifiers such as `const` and reference (`&`) are preserved in the deduced type. This allows you to declare variables with the same qualifiers as the initialized expression without explicitly specifying the type.

**Example:**
```cpp
#include <iostream>

int main() {
    int x = 42;
    const auto& y = x; // 'y' is deduced as 'const int&'
    
    auto z = y;        // 'z' is deduced as 'int', not 'const int'

    std::cout << x << " " << y << " " << z << std::endl;

    return 0;
}
```

In this example, `y` is deduced as a reference to a constant integer (`const int&`), and `z` is deduced as a non-constant integer (`int`). The `auto` keyword retains the qualifiers present in the initializer.

Remember that using `auto` with qualifiers can be useful for code brevity, but it's crucial to be aware of the implications on the deduced type, especially in scenarios where qualifiers are significant.

### range-based for loop

A range-based for loop is a convenient and expressive way to iterate over the elements of a container, such as an array, vector, or any other type that supports iteration. It simplifies the syntax and makes the code more readable compared to traditional loops with iterators or indices.

The syntax of a range-based for loop is as follows:

```cpp
for (auto element : container) {
    // Code to be executed for each element
}
```

Here, `auto` is used to automatically deduce the type of the elements in the container, and `element` represents the individual elements during each iteration. The loop will iterate over all elements in the `container`.

Range-based for loops are concise and can improve code readability, especially when the index or iterator values are not needed, and you simply want to iterate over the elements of a container.

### Lambda Expression

A lambda expression is an anonymous function or a function without a name. It allows you to create functions on the fly, typically for short, one-time use. Lambda expressions were introduced in C++11 and provide a concise way to define functions within the body of another function or code block.

Here's a short description of the basic syntax and features of lambda expressions in C++:

**Syntax:**

```cpp
[capture](parameters) -> return_type {
    // function body
}
```

- **`capture`:** Specifies which variables from the surrounding scope should be accessible inside the lambda function.
- **`parameters`:** Similar to function parameters, specifies the input parameters of the lambda function.
- **`return_type`:** Specifies the return type of the lambda function.
- **`function body`:** Contains the actual code of the lambda function.

**Capture Clauses:**

Lambda expressions can capture variables from their surrounding scope. There are different ways to capture variables:

- **`[ ]`:** No capture, lambda can't use variables from the surrounding scope.
- **`[variable]`:** Capture a specific variable by value.
- **`[&variable]`:** Capture a specific variable by reference.
- **`[=]`:** Capture all variables by value.
- **`[&]`:** Capture all variables by reference.

Lambda expressions are commonly used in algorithms, event handling, and wherever a short, inline function is needed. They enhance the expressive power of C++ and provide a more concise syntax for defining functions on the spot.

### lvalue and rvalue

lvalue and rvalue are concepts related to the categorization of expressions based on their properties. These concepts play a crucial role in understanding and working with modern C++ features, such as move semantics and perfect forwarding.

1. **Lvalue (Left Value):**
   - An lvalue is an expression that refers to an object with identifiable memory location (a variable). It is called "left value" because historically, it appeared on the left-hand side of an assignment expression.
   - Examples of lvalues include variables, array elements, and dereferenced pointers.

   ```cpp
   int x = 10; // 'x' is an lvalue
   int arr[5];  // 'arr' is an lvalue
   int* ptr = &x; // '*ptr' is an lvalue
   ```

2. **Rvalue (Right Value):**
   - An rvalue is an expression that represents a temporary or a value that doesn't have a persistent memory location. It is called "right value" because historically, it appeared on the right-hand side of an assignment expression.
   - Examples of rvalues include literals, temporary objects, and the result of expressions.

   ```cpp
   int y = 20;          // '20' is an rvalue
   int result = x + y;  // 'x + y' is an rvalue
   ```

3. **Lvalue Reference (`&`):**
   - An lvalue reference is a reference to an lvalue. It is declared using the `&` symbol.
   - Lvalue references are typically used for aliasing, allowing multiple names to refer to the same object.

   ```cpp
   int a = 30;
   int& refA = a;  // 'refA' is an lvalue reference to 'a'
   ```

4. **Rvalue Reference (`&&`):**
   - An rvalue reference is a reference to an rvalue. It is declared using the `&&` symbol.
   - Rvalue references are introduced for efficient resource management, especially in the context of move semantics.

   ```cpp
   int&& rvalueRef = 42;  // 'rvalueRef' is an rvalue reference
   ```

   Rvalue references are commonly used in move semantics to transfer ownership of resources from one object to another without unnecessary copying.

### std::move

`std::move` is a utility function provided by the Standard Template Library (STL) that is used for enabling the move semantics feature introduced in C++11. Move semantics allow efficient transfer of resources (such as ownership of dynamically allocated memory) from one object to another without unnecessary copying.

The `std::move` function is declared in the `<utility>` header and is typically used to explicitly cast an object to an rvalue reference, indicating that it can be moved from. It doesn't perform any actual moving but rather transforms an object into an rvalue, which allows move constructors or move assignment operators to be invoked.

Here's a brief description of how `std::move` is commonly used:

```cpp
#include <utility>

class MyClass {
public:
    // Move constructor
    MyClass(MyClass&& other) {
        // Move resources from 'other' to 'this'
    }

    // Move assignment operator
    MyClass& operator=(MyClass&& other) {
        // Move resources from 'other' to 'this'
        return *this;
    }
};

int main() {
    MyClass obj1;
    MyClass obj2 = std::move(obj1); // std::move signals that ownership can be transferred

    return 0;
}
```

In the example, `std::move` is used to indicate that the ownership of resources in `obj1` can be efficiently transferred to `obj2`. This is particularly useful in scenarios where copying is expensive, and moving the resources is a more efficient option. Keep in mind that after using `std::move`, the source object should be considered in a valid but unspecified state, and further use might have unexpected results.

### Rvalue references and overloading

Rvalue references, combined with function overloading, contribute to the implementation of efficient and flexible code by allowing developers to handle both temporary and non-temporary objects in a customized way. They are particularly powerful in scenarios involving resource management, such as dynamic memory allocation, where avoiding unnecessary copies can significantly improve performance.

- **Purpose:** Overloading functions or constructors with both lvalue and rvalue reference parameters allows the code to handle both temporary and non-temporary objects differently.

- **Example:**
  ```cpp
  class MyClass {
  public:
      // Constructor with lvalue reference
      MyClass(const int& value) {
          // Handle lvalue (const reference) case
      }

      // Constructor with rvalue reference
      MyClass(int&& value) {
          // Handle rvalue (move) case
      }
  };
  ```

- **Use Case:** Overloading with rvalue references is commonly used in move constructors, move assignment operators, and other scenarios where you want to provide different behavior for temporary and non-temporary objects.

### Move-Only Types


In C++, move-only types refer to objects that can be efficiently moved but not copied. This concept is closely associated with move semantics, introduced in C++11, which enables the efficient transfer of resources from one object to another without unnecessary copying.

Some objects are designed to be movable but not copyable. This is often the case for resources that are expensive to copy but can be efficiently transferred.
Examples of move-only types include unique pointers (`std::unique_ptr`), file handles, network connections, etc.
Move-only types typically have a move constructor and a move assignment operator but may delete or disable their copy constructor and copy assignment operator.

Example of a move-only type (using `std::unique_ptr`):

```cpp
#include <iostream>
#include <memory>

class MoveOnlyType {
public:
    MoveOnlyType() = default;

    // Move constructor
    MoveOnlyType(MoveOnlyType&& other) noexcept {
        // Move resources from 'other' to 'this'
    }

    // Move assignment operator
    MoveOnlyType& operator=(MoveOnlyType&& other) noexcept {
        if (this != &other) {
            // Move resources from 'other' to 'this'
        }
        return *this;
    }

    // Deleting copy constructor and copy assignment operator
    MoveOnlyType(const MoveOnlyType&) = delete;
    MoveOnlyType& operator=(const MoveOnlyType&) = delete;
};

int main() {
    std::unique_ptr<MoveOnlyType> ptr1 = std::make_unique<MoveOnlyType>();
    std::unique_ptr<MoveOnlyType> ptr2 = std::move(ptr1); // Move ownership from ptr1 to ptr2

    return 0;
}
```

In this example, `MoveOnlyType` is a move-only type, and ownership of its resources can be efficiently transferred using move semantics.

### Move operators

Move operators are a set of special member functions that allow efficient transfer of resources (such as memory ownership) from one object to another. These operators, typically called move constructors and move assignment operators, leverage the concept of rvalue references to facilitate the transfer of resources without unnecessary copying.

1. **Move Constructor (`T::T(T&& other) noexcept`):**
   - A move constructor is a special constructor that takes an rvalue reference (`T&&`) as its parameter.
   - It is used to efficiently transfer resources (e.g., dynamic memory) from one object (`other`) to the newly constructed object.
   - The move constructor is called automatically in certain situations, such as when returning a local object from a function by value or when using the `std::move` function.

   ```cpp
   // Example move constructor
   MyClass(MyClass&& other) noexcept {
       // Transfer resources from 'other' to 'this'
   }
   ```

2. **Move Assignment Operator (`T& operator=(T&& other) noexcept`):**
   - The move assignment operator is a special assignment operator that takes an rvalue reference (`T&&`) as its parameter.
   - It allows the efficient transfer of resources from the right-hand side (`other`) to the left-hand side (`*this`).
   - Like the move constructor, the move assignment operator is invoked automatically in certain scenarios.

   ```cpp
   // Example move assignment operator
   MyClass& operator=(MyClass&& other) noexcept {
       // Transfer resources from 'other' to 'this'
       if (this != &other) {
           // Release existing resources if any
           // ...
           // Transfer ownership
           // ...
       }
       return *this;
   }
   ```

The use of move semantics can significantly improve performance by avoiding unnecessary deep copying of resources. Move operations are particularly beneficial when dealing with large data structures, such as dynamic containers like `std::vector` or objects managing resources like file handles.

To take full advantage of move semantics, it's essential to implement move constructors and move assignment operators for user-defined types, particularly when dealing with resource management. The `noexcept` specifier indicates that the operation is not expected to throw exceptions, which is a good practice for move operations to be as efficient as possible.

### Deleted and Defaulted Operators

The terms "deleted" and "defaulted" are associated with special member functions, which include constructors, destructors, copy/move constructors, copy/move assignment operators, and others.

1. **Deleted Operators:**
   - A deleted operator is a way to explicitly disallow the usage of a particular special member function or operator.
   - When an operator or function is marked as deleted using `= delete;`, attempting to use it will result in a compilation error.
   - It is commonly used to prevent unintended behavior or to enforce certain design decisions.
   - Example:
     ```cpp
     class MyClass {
     public:
         // Deleting the copy constructor
         MyClass(const MyClass&) = delete;
     };
     ```

2. **Defaulted Operators:**
   - A defaulted operator is a way to instruct the compiler to generate the default implementation for a special member function or operator.
   - The `= default;` syntax is used to explicitly request the compiler to provide the default implementation.
   - It is particularly useful when you want the compiler-generated default behavior for certain functions.
   - Example:
     ```cpp
     class MyClass {
     public:
         // Using the default constructor
         MyClass() = default;
     };
     ```

   - For copy/move constructors and assignment operators, the defaulted versions perform a member-wise copy or move of the class members.
   - Example:
     ```cpp
     class MyCopyableClass {
     public:
         MyCopyableClass() = default;
         MyCopyableClass(const MyCopyableClass&) = default; // Compiler-generated copy constructor
         MyCopyableClass& operator=(const MyCopyableClass&) = default; // Compiler-generated copy assignment operator
     };
     ```

   - The defaulted functions are implicitly generated by the compiler if they are not explicitly declared or defined.

In summary, deleted operators are used to prevent certain operations explicitly, while defaulted operators instruct the compiler to generate default implementations for certain operations. Both concepts contribute to controlling the behavior of the class and enforcing design decisions.

### Random Number Classes

Random number generation is facilitated by various classes and functions provided in the `<random>` header. 

1. **std::random_device:**
   - This class provides access to a non-deterministic source of randomness (e.g., hardware entropy). It is often used to seed other random number generators.

2. **std::mt19937, std::mt19937_64:**
   - These are implementations of the Mersenne Twister pseudo-random number generator algorithms with 32-bit and 64-bit output, respectively. They are commonly used for generating high-quality pseudo-random numbers.

3. **std::uniform_int_distribution, std::uniform_real_distribution:**
   - These classes represent distributions for generating random integers and random floating-point numbers, respectively, within a specified range.

4. **std::normal_distribution:**
   - This class represents a normal (Gaussian) distribution, allowing the generation of random numbers with a mean and standard deviation.

5. **std::bernoulli_distribution:**
   - This class represents a Bernoulli distribution, useful for generating random boolean values with a given probability.

6. **std::shuffle:**
   - This algorithm shuffles the elements in a range, providing a way to randomize the order of a collection.

7. **std::default_random_engine:**
   - This is a type alias that represents the default random number engine used by various random distribution classes. It is often a typedef for `std::mt19937`.

Usage typically involves creating an instance of a random number distribution class, initializing it with a random device or engine, and then invoking it to generate random numbers within the specified range.

Example:

```cpp
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    int random_number = distribution(gen);
    std::cout << "Random number between 1 and 10: " << random_number << std::endl;

    return 0;
}
```

### std::unique_ptr

`std::unique_ptr` is a C++ Standard Library smart pointer that manages the ownership and lifetime of dynamically allocated objects. It is part of the C++11 standard and provides a way to handle memory management automatically while adhering to the principle of unique ownership.

Here are some key features and characteristics of `std::unique_ptr`:

1. **Unique Ownership:**
   - A `std::unique_ptr` owns the dynamically allocated object exclusively. It ensures that at any given time, only one `std::unique_ptr` instance owns the object.

2. **Automatic Resource Management:**
   - `std::unique_ptr` automatically takes care of deallocating the memory when the pointer goes out of scope. This helps in preventing memory leaks by tying the object's lifetime to the lifetime of the `std::unique_ptr`.

3. **No Overhead of Reference Counting:**
   - Unlike `std::shared_ptr`, `std::unique_ptr` does not incur the overhead of reference counting because it doesn't support shared ownership. This makes it more lightweight and efficient in scenarios where shared ownership is not needed.

4. **Move Semantics:**
   - `std::unique_ptr` is designed to support move semantics. Ownership can be transferred from one `std::unique_ptr` to another efficiently using move operations, which can be particularly useful in resource management scenarios.

5. **Nullptr Handling:**
   - `std::unique_ptr` can be in a state of not owning any object, which is represented by a null pointer. It provides member functions like `get()` and `reset()` for managing the pointer and `operator bool()` for easy null checks.

6. **Custom Deleter:**
   - It allows specifying a custom deleter function or callable object to handle the deallocation of the object. This can be useful when dealing with resources other than memory.

Here's a basic example of using `std::unique_ptr`:

```cpp
#include <memory>
#include <iostream>

class MyClass {
public:
    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

int main() {
    // Creating a unique_ptr with a dynamically allocated object
    std::unique_ptr<MyClass> myUniquePtr = std::make_unique<MyClass>();

    // Using the unique_ptr
    myUniquePtr->doSomething();

    // No need to manually delete, as unique_ptr handles it automatically
    return 0;
}
```



--- 

## Links

<- Back to [Main](../README.md)