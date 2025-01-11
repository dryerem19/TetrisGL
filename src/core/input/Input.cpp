#include "Input.h"

// Инициализация статических переменных
bool Input::_initialized = false;
bool Input::_currentStateKeyboard[1024];
bool Input::_previousStateKeyboard[1024];

void Input::Init(GLFWwindow* window)
{
	if (!_initialized) {
		glfwSetKeyCallback(window, OnKeyCallback);

		for (int i = 0; i < 1024; ++i) {
			_currentStateKeyboard[i] = false;
			_previousStateKeyboard[i] = false;
		}

		_initialized = true;
	}
}

void Input::Update()
{
	for (int i = 0; i < 1024; ++i) {
		//_previousStateKeyboard[i] = _currentStateKeyboard[i];
	}
}

bool Input::GetKey(KeyCode key)
{
	return _currentStateKeyboard[static_cast<int>(key)];
}

bool Input::GetKeyUp(KeyCode key)
{
	int key_code = static_cast<int>(key);
	return _previousStateKeyboard[key_code] && !_currentStateKeyboard[key_code];
}

bool Input::GetKeyDown(KeyCode key)
{
	int key_code = static_cast<int>(key);
	return _currentStateKeyboard[key_code] && !_previousStateKeyboard[key_code];
}

void Input::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024) {
		_previousStateKeyboard[key] = _currentStateKeyboard[key];
		if (action == GLFW_PRESS) {
			_currentStateKeyboard[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			_currentStateKeyboard[key] = false;
		}
	}
}
