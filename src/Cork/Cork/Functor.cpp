#include "Functor.h"


Functor::Functor()
{
}


Functor::~Functor()
{
}

void Functor::DetectCombos(vector<USHORT>* recentInput)
{

	/*
	*		Whenever the recentInput vector changes size a timer is meant to begin which
	*		then allows the key combos to be reset after a short period of time.
	*		There however is an issue with the iterator that is causing a crash.
	*		There is likely a better alturnaitve to using an iterator to get the vector size.
	*/

	mutex guardFunctor1, guardFunctor2;
	int previousVectorSize = 0;

	while (threadRunning)
	{
		int vectorSize = 0;
		guardFunctor1.lock();
		{
			//for (vector<USHORT>::iterator i = recentInput->begin(); i != recentInput->end(); i++)
			//{
			//	vectorSize++;
			//};
		}
		guardFunctor1.unlock();

		if (vectorSize != previousVectorSize);
		{
			SetLastInputTime(GetLastInputTime());
			SetCurrentInputTime(std::chrono::steady_clock::now());
			previousVectorSize = vectorSize;
		}

		if (_timeSinceLastInput > _comboTimeLimit)
		{
			guardFunctor2.lock();
			{
				recentInput->clear();
			}
			guardFunctor2.unlock();
		}
	}
}
