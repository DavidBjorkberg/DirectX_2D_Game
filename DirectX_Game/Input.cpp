#include "Input.h"
std::unique_ptr<DirectX::Keyboard> Input::keyboard;
DirectX::Keyboard::KeyboardStateTracker Input::Keys;
bool Input::KeyPressed(Keyboard::Keys key)
{
	bool pp = Keys.GetLastState().IsKeyDown(key);
	bool nn = Keys.IsKeyPressed(key);
	return nn;
}

bool Input::KeyDown(Keyboard::Keys key)
{
	return keyboard->GetState().IsKeyDown(key);
}

bool Input::KeyReleased(Keyboard::Keys key)
{
	return Keys.IsKeyReleased(key);
}

void Input::Update()
{
	Keys.Update(keyboard->GetState());
}

Input::Input()
{
	keyboard = std::make_unique<DirectX::Keyboard>();
	Keys.Reset();
}
