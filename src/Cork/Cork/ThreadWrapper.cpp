#include "ThreadWrapper.h"


ThreadWrapper::ThreadWrapper(std::thread* thread)
{
	_thread = thread;
}


ThreadWrapper::~ThreadWrapper()
{
	_thread->join();
}

