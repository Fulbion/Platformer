#include "Game.hpp"

#ifndef NDEBUG
int main()
#else
#include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
#endif // NDEBUG
{
	Game game;
	game.run();
	return 0;
}
