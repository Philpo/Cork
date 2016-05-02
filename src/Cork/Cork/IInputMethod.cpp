#include "IInputMethod.h"

/*
 *		The reason for the IInputMethod class is so that new input methods e.g. Xinput can be added
 *		using the singleton pattern. A commented out implimentation of a singleton pattern can be
 *		found in RawInput.
 */
IInputMethod::IInputMethod()
{
}


IInputMethod::~IInputMethod()
{
}
