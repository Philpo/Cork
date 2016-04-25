#pragma once
#include "Utils.h"
#include <string>
#include "Window.h"

#include <map>

using namespace std;

class KeyMap
{
public:
	KeyMap();
	~KeyMap();

	map <string, USHORT> inputMap;


	//const map<string, string> testMap =
	//{
	//	{"x", "y" }
	//};


	//keyMap["MOVE_RIGHT"] = USHORT;
};

