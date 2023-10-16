#include "Utilities.h"

void PlayerUtils::CheckError(FMOD_RESULT result, const char* file, int line)
{
	if (result != FMOD_OK)
	{
		printf("FMOD Error [%d]: %s at %d\n", static_cast<int>(result), file, line);
	}
}
