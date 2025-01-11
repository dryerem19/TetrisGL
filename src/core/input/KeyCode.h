#pragma once
#include <GLFW/glfw3.h>

/**
* @brief ���� ������.
*
* ���� ������ ����� ������������ ��� ����������� ������� ������� � ���������� ������ � ������� \ref Input::GetKeyDown � /ref Input::GetKeyUp.
*/
enum class KeyCode
{
	/**
	* @brief ������� Backspace.
	*/
	Backspace = GLFW_KEY_BACKSPACE,

	/**
	* @brief ������� �������� ������.
	*/
	Delete = GLFW_KEY_DELETE,

	/**
	* @brief ������� Tab.
	*/
	Tab = GLFW_KEY_TAB,

	/**
	* @brief ������� Return.
	*/
	Return = GLFW_KEY_ENTER,

	/**
	* @brief ������� Pause.
	*/
	Pause = GLFW_KEY_PAUSE,

	/**
	* @brief ������� Escape.
	*/
	Escape = GLFW_KEY_ESCAPE,

	/**
	* @brief ������� Space (������).
	*/
	Space = GLFW_KEY_SPACE,

	/**
	* @brief ������� '0' �� �������� ����������.
	*/
	Keypad0 = GLFW_KEY_KP_0,

	/**
	* @brief ������� '1' �� �������� ����������.
	*/
	Keypad1 = GLFW_KEY_KP_1,

	/**
	* @brief ������� '2' �� �������� ����������.
	*/
	Keypad2 = GLFW_KEY_KP_2,

	/**
	* @brief ������� '3' �� �������� ����������
	*/
	Keypad3 = GLFW_KEY_KP_3,

	/**
	* @brief ������� '4' �� �������� ����������.
	*/
	Keypad4 = GLFW_KEY_KP_4,

	/**
	* @brief ������� '5' �� �������� ����������.
	*/
	Keypad5 = GLFW_KEY_KP_5,

	/**
	* @brief ������� '6' �� �������� ����������.
	*/
	Keypad6 = GLFW_KEY_KP_6,

	/**
	* @brief ������� '7' �� �������� ����������.
	*/
	Keypad7 = GLFW_KEY_KP_7,

	/**
	* @brief ������� '8' �� �������� ����������.
	*/
	Keypad8 = GLFW_KEY_KP_8,

	/**
	* @brief ������� '9' �� �������� ����������.
	*/
	Keypad9 = GLFW_KEY_KP_9,

	/**
	* @brief ������� '.' �� �������� ����������.
	*/
	KeypadPeriod = GLFW_KEY_KP_DECIMAL,

	/**
	* @brief ������� '/' �� �������� ����������.
	*/
	KeypadDivide = GLFW_KEY_KP_DIVIDE,

	/**
	* @brief ������� '*' �� �������� ����������.
	*/
	KeypadMultiply = GLFW_KEY_KP_MULTIPLY,

	/**
	* @brief ������� '-' �� �������� ����������.
	*/
	KeypadMinus = GLFW_KEY_KP_SUBTRACT,

	/**
	* @brief ������� '+' �� �������� ����������.
	*/
	KeypadPlus = GLFW_KEY_KP_ADD,

	/**
	* @brief ������� 'Enter' �� �������� ����������.
	*/
	KeypadEnter = GLFW_KEY_KP_ENTER,

	/**
	* @brief ������� '=' �� �������� ����������.
	*/
	KeypadEqual = GLFW_KEY_KP_EQUAL,

	/**
	* @brief ������� '������� �����'.
	*/
	UpArrow = GLFW_KEY_UP,

	/**
	* @brief ������� '������� ����'.
	*/
	DownArrow = GLFW_KEY_DOWN,

	/**
	* @brief ������� '������� �������'.
	*/
	RightArrow = GLFW_KEY_RIGHT,

	/**
	* @brief ������� '������� �����'.
	*/
	LeftArrow = GLFW_KEY_LEFT,

	/**
	* @brief ������� Insert.
	*/
	Insert = GLFW_KEY_INSERT,

	/**
	* @brief ������� Home.
	*/
	Home = GLFW_KEY_HOME,

	/**
	* @brief ������� End.
	*/
	End = GLFW_KEY_END,

	/**
	* @brief ������� Page Up.
	*/
	PageUp = GLFW_KEY_PAGE_UP,

	/**
	* @brief ������� Page Down.
	*/
	PageDown = GLFW_KEY_PAGE_DOWN,

	/**
	* @brief �������������� ������� F1.
	*/
	F1 = GLFW_KEY_F1,

	/**
	* @brief �������������� ������� F2.
	*/
	F2 = GLFW_KEY_F2,

	/**
	* @brief �������������� ������� F3.
	*/
	F3 = GLFW_KEY_F3,

	/**
	* @brief �������������� ������� F4.
	*/
	F4 = GLFW_KEY_F4,

	/**
	* @brief �������������� ������� F5.
	*/
	F5 = GLFW_KEY_F5,

	/**
	* @brief �������������� ������� F6.
	*/
	F6 = GLFW_KEY_F6,

	/**
	* @brief �������������� ������� F7.
	*/
	F7 = GLFW_KEY_F7,

	/**
	* @brief �������������� ������� F8.
	*/
	F8 = GLFW_KEY_F8,

	/**
	* @brief �������������� ������� F9.
	*/
	F9 = GLFW_KEY_F9,

	/**
	* @brief �������������� ������� F10.
	*/
	F10 = GLFW_KEY_F10,

	/**
	* @brief �������������� ������� F11.
	*/
	F11 = GLFW_KEY_F11,

	/**
	* @brief �������������� ������� F12.
	*/
	F12 = GLFW_KEY_F12,

	/**
	* @brief �������������� ������� F13.
	*/
	F13 = GLFW_KEY_F13,

	/**
	* @brief �������������� ������� F14.
	*/
	F14 = GLFW_KEY_F14,

	/**
	* @brief �������������� ������� F15.
	*/
	F15 = GLFW_KEY_F15,

	/**
	* @brief ������� '0' � ������� ���� ����������.
	*/
	Alpha0 = GLFW_KEY_0,

	/**
	* @brief ������� '1' � ������� ���� ����������.
	*/
	Alpha1 = GLFW_KEY_1,

	/**
	* @brief ������� '2' � ������� ���� ����������.
	*/
	Alpha2 = GLFW_KEY_2,

	/**
	* @brief ������� '3' � ������� ���� ����������.
	*/
	Alpha3 = GLFW_KEY_3,

	/**
	* @brief ������� '4' � ������� ���� ����������.
	*/
	Alpha4 = GLFW_KEY_4,

	/**
	* @brief ������� '5' � ������� ���� ����������.
	*/
	Alpha5 = GLFW_KEY_5,

	/**
	* @brief ������� '6' � ������� ���� ����������.
	*/
	Alpha6 = GLFW_KEY_6,

	/**
	* @brief ������� '7' � ������� ���� ����������.
	*/
	Alpha7 = GLFW_KEY_7,

	/**
	* @brief ������� '8' � ������� ���� ����������.
	*/
	Alpha8 = GLFW_KEY_8,

	/**
	* @brief ������� '9' � ������� ���� ����������.
	*/
	Alpha9 = GLFW_KEY_9,
	/**
	* @brief ������� ',' (�������).
	*/
	Comma = GLFW_KEY_COMMA,

	/**
	* @brief ������� '-' (�����).
	*/
	Minus = GLFW_KEY_MINUS,

	/**
	* @brief ������� '.' (�����).
	*/
	Period = GLFW_KEY_PERIOD,

	/**
	* @brief ������� '/' (����).
	*/
	Slash = GLFW_KEY_SLASH,

	/**
	* @brief ������� ';' (����� � �������).
	*/
	Semicolon = GLFW_KEY_SEMICOLON,

	/**
	* @brief ������� '=' (�����).
	*/
	Equal = GLFW_KEY_EQUAL,

	/**
	* @brief ������� '[' (����� ���������� ������).
	*/
	LeftBracket = GLFW_KEY_LEFT_BRACKET,

	/**
	* @brief ������� '\' (�������� ����).
	*/
	Backslash = GLFW_KEY_BACKSLASH,

	/**
	* @brief ������� ']' (������ ���������� ������).
	*/
	RightBracket = GLFW_KEY_RIGHT_BRACKET,

	/**
	* @brief ������� 'A'.
	*/
	A = GLFW_KEY_A,

	/**
	* @brief ������� 'B'.
	*/
	B = GLFW_KEY_B,

	/**
	* @brief ������� 'C'.
	*/
	C = GLFW_KEY_C,

	/**
	* @brief ������� 'D'.
	*/
	D = GLFW_KEY_D,

	/**
	* @brief ������� 'E'.
	*/
	E = GLFW_KEY_E,

	/**
	* @brief ������� 'F'.
	*/
	F = GLFW_KEY_F,

	/**
	* @brief ������� 'G'.
	*/
	G = GLFW_KEY_G,

	/**
	* @brief ������� 'H'.
	*/
	H = GLFW_KEY_H,

	/**
	* @brief ������� 'I'.
	*/
	I = GLFW_KEY_I,

	/**
	* @brief ������� 'J'.
	*/
	J = GLFW_KEY_J,

	/**
	* @brief ������� 'K'.
	*/
	K = GLFW_KEY_K,

	/**
	* @brief ������� 'L'.
	*/
	L = GLFW_KEY_L,

	/**
	* @brief ������� 'M'.
	*/
	M = GLFW_KEY_M,

	/**
	* @brief ������� 'N'.
	*/
	N = GLFW_KEY_N,

	/**
	* @brief ������� 'O'.
	*/
	O = GLFW_KEY_O,

	/**
	* @brief ������� 'P'.
	*/
	P = GLFW_KEY_P,

	/**
	* @brief ������� 'Q'.
	*/
	Q = GLFW_KEY_Q,

	/**
	* @brief ������� 'R'.
	*/
	R = GLFW_KEY_R,

	/**
	* @brief ������� 'S'.
	*/
	S = GLFW_KEY_S,

	/**
	* @brief ������� 'T'.
	*/
	T = GLFW_KEY_T,

	/**
	* @brief ������� 'U'.
	*/
	U = GLFW_KEY_U,

	/**
	* @brief ������� 'V'.
	*/
	V = GLFW_KEY_V,

	/**
	* @brief ������� 'W'.
	*/
	W = GLFW_KEY_W,

	/**
	* @brief ������� 'X'.
	*/
	X = GLFW_KEY_X,

	/**
	* @brief ������� 'Y'.
	*/
	Y = GLFW_KEY_Y,

	/**
	* @brief ������� 'Z'.
	*/
	Z = GLFW_KEY_Z,

	/**
	* @brief ������� NumLock.
	*/
	NumLock = GLFW_KEY_NUM_LOCK,

	/**
	* @brief ������� CapsLock.
	*/
	CapsLock = GLFW_KEY_CAPS_LOCK,

	/**
	* @brief ������� ScrollLock.
	*/
	ScrollLock = GLFW_KEY_SCROLL_LOCK,

	/**
	* @brief ������� RightShift.
	*/
	RightShift = GLFW_KEY_RIGHT_SHIFT,

	/**
	* @brief ������� LeftShift.
	*/
	LeftShift = GLFW_KEY_LEFT_SHIFT,

	/**
	* @brief ������� RightControl.
	*/
	RightControl = GLFW_KEY_RIGHT_CONTROL,

	/**
	* @brief ������� LeftControl.
	*/
	LeftControl = GLFW_KEY_LEFT_CONTROL,

	/**
	* @brief ������� RightAlt.
	*/
	RightAlt = GLFW_KEY_RIGHT_ALT,

	/**
	* @brief ������� LeftAlt.
	*/
	LeftAlt = GLFW_KEY_LEFT_ALT,

	/**
	* @brief ����� ������� Command ��� Windows.
	*/
	LeftCommand = GLFW_KEY_LEFT_SUPER,

	/**
	* @brief ������ ������� Command ��� Windows.
	*/
	RightCommand = GLFW_KEY_RIGHT_SUPER,

	/**
	* ������� Menu.
	*/
	Menu = GLFW_KEY_MENU,

	/**
	* ����� (��� ��������) ������ ����.
	*/
	Mouse0 = GLFW_MOUSE_BUTTON_LEFT,

	/**
	* ������ ������ ���� (��� �������������� ������ ����).
	*/
	Mouse1 = GLFW_MOUSE_BUTTON_RIGHT,

	/**
	* ������� ������ ���� (��� ������ ������ ����).
	*/
	Mouse2 = GLFW_MOUSE_BUTTON_MIDDLE,

	/**
	* �������������� (���������) ������ ����.
	*/
	Mouse3 = GLFW_MOUSE_BUTTON_4,

	/**
	* �������������� (�����) ������ ����.
	*/
	Mouse4 = GLFW_MOUSE_BUTTON_5,

	/**
	* �������������� (��� ������) ������ ����.
	*/
	Mouse5 = GLFW_MOUSE_BUTTON_6,

	/**
	* �������������� (��� �������) ������ ����.
	*/
	Mouse6 = GLFW_MOUSE_BUTTON_7,

	/**
	* �������������� (��� �������) ������ ����.
	*/
	Mouse7 = GLFW_MOUSE_BUTTON_8
};