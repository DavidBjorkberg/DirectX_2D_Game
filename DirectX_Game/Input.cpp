#include "Input.h"
std::unique_ptr<DirectX::Keyboard> Input::keyboard;
DirectX::Keyboard::KeyboardStateTracker Input::Keys;

bool Input::KeyPressed(Keyboard::Keys key)
{
	Keys.Update(keyboard->GetState());
	return Keys.IsKeyPressed(key);
}

bool Input::KeyDown(Keyboard::Keys key)
{
	Keys.Update(keyboard->GetState());
	return keyboard->GetState().IsKeyDown(key);
}

bool Input::KeyReleased(Keyboard::Keys key)
{
	Keys.Update(keyboard->GetState());
	return Keys.IsKeyReleased(key);
}

Input::Input()
{
	keyboard = std::make_unique<DirectX::Keyboard>();
	Keys.Reset();
}
