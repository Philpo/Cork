#pragma once
#include "Utils.h"
#include <string>
#include "Window.h"
#include <iostream>

#include <map>

using namespace std;

class KeyMap
{
public:
	//KeyMap();
	KeyMap(string inputType);
	~KeyMap();

	map <string, USHORT> inputMap;

	void ChangeMappedKey(string command, USHORT newKey);
};

