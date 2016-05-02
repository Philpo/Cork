#pragma once
#include <thread>
class ThreadWrapper
{
public:
	ThreadWrapper(std::thread* thread);
	~ThreadWrapper();

private:
	std::thread* _thread = new std::thread;
};

