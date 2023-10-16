#include "MediaPlayer.h"

int main(int argc, char** argv)
{
	MediaPlayer player;

	player.InitializePlaylist();
	player.Play();
	player.Shutdown();

	return 0;		// [0 = Success, if not 0, Error]
}