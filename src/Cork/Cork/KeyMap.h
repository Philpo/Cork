#pragma once
#include "Utils.h"
#include <string>
#include "Window.h"
#include <iostream>

#include <map>

/*		The map currently has it's data hardcoded in the constructor. A better solution
 *		would be to store the data in an XLM or text file which would allow the data to be easily
 *		accessed, edited, and saved.
 */

using namespace std;

class KeyMap
{
public:
	KeyMap(string inputType);
	~KeyMap();

	map <string, USHORT> inputMap;

	void ChangeMappedKey(string command, USHORT newKey);
};

