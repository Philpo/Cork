#include "Functor.h"


Functor::Functor()
{
}


Functor::~Functor()
{
}

void Functor::DetectCombos(vector<USHORT>* recentInput)
{
	while (threadRunning)
	{
		if (updateInput)
		{
			updateInput = false;

			recentInput->push_back(newInput);
			SetLastInputTime(GetLastInputTime());
			SetCurrentInputTime(std::chrono::steady_clock::now());
		}

		if (_timeSinceLastInput > _conboTimeLimit)
		{
			recentInput->clear();
		}
	}
}
