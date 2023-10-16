#include <fmod.h>
#include <iostream>

namespace PlayerUtils
{
	void CheckError(FMOD_RESULT result, const char* file, int line);
#define FMODCheckERROR(result) CheckError(result, __FILE__, __LINE__);
}

