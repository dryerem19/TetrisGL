#include <memory>
#include "Game.h"

#include <Windows.h>

int main()
{
    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

	auto game = std::make_unique<Game>(640, 480);
	return game->Exec();
}
