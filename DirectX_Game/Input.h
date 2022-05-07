#pragma once
#include<Keyboard.h>

using namespace DirectX;
 class Input
{
public:
	static bool KeyPressed(Keyboard::Keys key);
	static bool KeyDown(Keyboard::Keys key);
	static bool KeyReleased(Keyboard::Keys key);
	static void Update();
	static std::unique_ptr<Keyboard> keyboard;
	Input();
private:
	static Keyboard::KeyboardStateTracker Keys;
};