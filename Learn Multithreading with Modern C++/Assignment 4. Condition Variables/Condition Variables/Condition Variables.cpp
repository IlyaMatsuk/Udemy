#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::chrono;

// Global variables
std::mutex mut;
bool cv = false;
std::string sdata{ "Empty" };

// Waiting thread
void reader() {

	std::unique_lock<std::mutex> guard(mut);
	while (!cv)
	{
		guard.unlock();
		std::this_thread::sleep_for(100ms);
		guard.lock();
	}

	std::cout << "Data is " << sdata << std::endl;
}

// Modyifing thread
void writer() {
	std::cout << "Writing data..." << std::endl;
	std::lock_guard<std::mutex> lg(mut);
	std::this_thread::sleep_for(2s);
	sdata = "Populated";
	cv = true;
}

int main() {
	std::cout << "Data is " << sdata << std::endl;
	std::thread read{ reader };
	std::thread write{ writer };

	write.join();
	read.join();
}