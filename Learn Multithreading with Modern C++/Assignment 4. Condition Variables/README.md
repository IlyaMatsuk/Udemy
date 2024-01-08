Rewrite the first condition variable example from the video to use a boolean flag instead of a condition variable. Your program must not contain any data race, deadlock or livelock conditions.

The source code for the example is in the attached ZIP file.

Questions for this assignment:

- Check that your program compiles and runs correctly. If you need help, click on the Instructor Example to get some hints.

```cpp
  #include <iostream>
  #include <thread>
  #include <condition_variable>
  #include <string>

  using namespace std::chrono;

  // Global variables
  std::mutex mut;
  std::condition_variable cv;
  std::string sdata{ "Empty" };

  // Waiting thread
  void reader() {
    std::unique_lock<std::mutex> guard(mut);            // Acquire lock
    cv.wait(guard);                                // Wait for condition variable to be notified
    std::cout << "Data is " << sdata << std::endl;           // Wake up and use the new value
  }

  // Modyifing thread
  void writer() {
    std::cout << "Writing data..." << std::endl;
    {
      std::lock_guard<std::mutex> lg(mut);            // Acquire lock
      std::this_thread::sleep_for(2s);           // Pretend to be busy...
      sdata = "Populated";                       // Modify the data
    }
    cv.notify_one();                               // Notify the condition variable
  }

  int main() {
    std::cout << "Data is " << sdata << std::endl;
    std::thread read{ reader };
    std::thread write{ writer };
    /*
    // If the writer thread finishes before the reader thread starts, the notification is lost
    thread write{writer};
    std::this_thread::sleep_for(500ms);
    thread read{reader};
    */
    write.join();
    read.join();
  }
```
