#pragma once
#include <GLFW/glfw3.h>

/**
* @brief Коды клавиш.
*
* Коды клавиш можно использовать для обнаружения событий нажатия и отпускания клавиш с помощью \ref Input::GetKeyDown и /ref Input::GetKeyUp.
*/
enum class KeyCode
{
	/**
	* @brief Клавиша Backspace.
	*/
	Backspace = GLFW_KEY_BACKSPACE,

	/**
	* @brief Клавиша удаления вперед.
	*/
	Delete = GLFW_KEY_DELETE,

	/**
	* @brief Клавиша Tab.
	*/
	Tab = GLFW_KEY_TAB,

	/**
	* @brief Клавиша Return.
	*/
	Return = GLFW_KEY_ENTER,

	/**
	* @brief Клавиша Pause.
	*/
	Pause = GLFW_KEY_PAUSE,

	/**
	* @brief Клавиша Escape.
	*/
	Escape = GLFW_KEY_ESCAPE,

	/**
	* @brief Клавиша Space (пробел).
	*/
	Space = GLFW_KEY_SPACE,

	/**
	* @brief Клавиша '0' на цифровой клавиатуре.
	*/
	Keypad0 = GLFW_KEY_KP_0,

	/**
	* @brief Клавиша '1' на цифровой клавиатуре.
	*/
	Keypad1 = GLFW_KEY_KP_1,

	/**
	* @brief Клавиша '2' на цифровой клавиатуре.
	*/
	Keypad2 = GLFW_KEY_KP_2,

	/**
	* @brief Клавиша '3' на цифровой клавиатуре
	*/
	Keypad3 = GLFW_KEY_KP_3,

	/**
	* @brief Клавиша '4' на цифровой клавиатуре.
	*/
	Keypad4 = GLFW_KEY_KP_4,

	/**
	* @brief Клавиша '5' на цифровой клавиатуре.
	*/
	Keypad5 = GLFW_KEY_KP_5,

	/**
	* @brief Клавиша '6' на цифровой клавиатуре.
	*/
	Keypad6 = GLFW_KEY_KP_6,

	/**
	* @brief Клавиша '7' на цифровой клавиатуре.
	*/
	Keypad7 = GLFW_KEY_KP_7,

	/**
	* @brief Клавиша '8' на цифровой клавиатуре.
	*/
	Keypad8 = GLFW_KEY_KP_8,

	/**
	* @brief Клавиша '9' на цифровой клавиатуре.
	*/
	Keypad9 = GLFW_KEY_KP_9,

	/**
	* @brief Клавиша '.' на цифровой клавиатуре.
	*/
	KeypadPeriod = GLFW_KEY_KP_DECIMAL,

	/**
	* @brief Клавиша '/' на цифровой клавиатуре.
	*/
	KeypadDivide = GLFW_KEY_KP_DIVIDE,

	/**
	* @brief Клавиша '*' на цифровой клавиатуре.
	*/
	KeypadMultiply = GLFW_KEY_KP_MULTIPLY,

	/**
	* @brief Клавиша '-' на цифровой клавиатуре.
	*/
	KeypadMinus = GLFW_KEY_KP_SUBTRACT,

	/**
	* @brief Клавиша '+' на цифровой клавиатуре.
	*/
	KeypadPlus = GLFW_KEY_KP_ADD,

	/**
	* @brief Клавиша 'Enter' на цифровой клавиатуре.
	*/
	KeypadEnter = GLFW_KEY_KP_ENTER,

	/**
	* @brief Клавиша '=' на цифровой клавиатуре.
	*/
	KeypadEqual = GLFW_KEY_KP_EQUAL,

	/**
	* @brief Клавиша 'стрелка вверх'.
	*/
	UpArrow = GLFW_KEY_UP,

	/**
	* @brief Клавиша 'стрелка вниз'.
	*/
	DownArrow = GLFW_KEY_DOWN,

	/**
	* @brief Клавиша 'стрелка направо'.
	*/
	RightArrow = GLFW_KEY_RIGHT,

	/**
	* @brief Клавиша 'стрелка влево'.
	*/
	LeftArrow = GLFW_KEY_LEFT,

	/**
	* @brief Клавиша Insert.
	*/
	Insert = GLFW_KEY_INSERT,

	/**
	* @brief Клавиша Home.
	*/
	Home = GLFW_KEY_HOME,

	/**
	* @brief Клавиша End.
	*/
	End = GLFW_KEY_END,

	/**
	* @brief Клавиша Page Up.
	*/
	PageUp = GLFW_KEY_PAGE_UP,

	/**
	* @brief Клавиша Page Down.
	*/
	PageDown = GLFW_KEY_PAGE_DOWN,

	/**
	* @brief Функциональная клавиша F1.
	*/
	F1 = GLFW_KEY_F1,

	/**
	* @brief Функциональная клавиша F2.
	*/
	F2 = GLFW_KEY_F2,

	/**
	* @brief Функциональная клавиша F3.
	*/
	F3 = GLFW_KEY_F3,

	/**
	* @brief Функциональная клавиша F4.
	*/
	F4 = GLFW_KEY_F4,

	/**
	* @brief Функциональная клавиша F5.
	*/
	F5 = GLFW_KEY_F5,

	/**
	* @brief Функциональная клавиша F6.
	*/
	F6 = GLFW_KEY_F6,

	/**
	* @brief Функциональная клавиша F7.
	*/
	F7 = GLFW_KEY_F7,

	/**
	* @brief Функциональная клавиша F8.
	*/
	F8 = GLFW_KEY_F8,

	/**
	* @brief Функциональная клавиша F9.
	*/
	F9 = GLFW_KEY_F9,

	/**
	* @brief Функциональная клавиша F10.
	*/
	F10 = GLFW_KEY_F10,

	/**
	* @brief Функциональная клавиша F11.
	*/
	F11 = GLFW_KEY_F11,

	/**
	* @brief Функциональная клавиша F12.
	*/
	F12 = GLFW_KEY_F12,

	/**
	* @brief Функциональная клавиша F13.
	*/
	F13 = GLFW_KEY_F13,

	/**
	* @brief Функциональная клавиша F14.
	*/
	F14 = GLFW_KEY_F14,

	/**
	* @brief Функциональная клавиша F15.
	*/
	F15 = GLFW_KEY_F15,

	/**
	* @brief Клавиша '0' в верхнем ряду клавиатуры.
	*/
	Alpha0 = GLFW_KEY_0,

	/**
	* @brief Клавиша '1' в верхнем ряду клавиатуры.
	*/
	Alpha1 = GLFW_KEY_1,

	/**
	* @brief Клавиша '2' в верхнем ряду клавиатуры.
	*/
	Alpha2 = GLFW_KEY_2,

	/**
	* @brief Клавиша '3' в верхнем ряду клавиатуры.
	*/
	Alpha3 = GLFW_KEY_3,

	/**
	* @brief Клавиша '4' в верхнем ряду клавиатуры.
	*/
	Alpha4 = GLFW_KEY_4,

	/**
	* @brief Клавиша '5' в верхнем ряду клавиатуры.
	*/
	Alpha5 = GLFW_KEY_5,

	/**
	* @brief Клавиша '6' в верхнем ряду клавиатуры.
	*/
	Alpha6 = GLFW_KEY_6,

	/**
	* @brief Клавиша '7' в верхнем ряду клавиатуры.
	*/
	Alpha7 = GLFW_KEY_7,

	/**
	* @brief Клавиша '8' в верхнем ряду клавиатуры.
	*/
	Alpha8 = GLFW_KEY_8,

	/**
	* @brief Клавиша '9' в верхнем ряду клавиатуры.
	*/
	Alpha9 = GLFW_KEY_9,
	/**
	* @brief Клавиша ',' (запятая).
	*/
	Comma = GLFW_KEY_COMMA,

	/**
	* @brief Клавиша '-' (минус).
	*/
	Minus = GLFW_KEY_MINUS,

	/**
	* @brief Клавиша '.' (точка).
	*/
	Period = GLFW_KEY_PERIOD,

	/**
	* @brief Клавиша '/' (слеш).
	*/
	Slash = GLFW_KEY_SLASH,

	/**
	* @brief Клавиша ';' (точка с запятой).
	*/
	Semicolon = GLFW_KEY_SEMICOLON,

	/**
	* @brief Клавиша '=' (равно).
	*/
	Equal = GLFW_KEY_EQUAL,

	/**
	* @brief Клавиша '[' (левая квадратная скобка).
	*/
	LeftBracket = GLFW_KEY_LEFT_BRACKET,

	/**
	* @brief Клавиша '\' (обратный слеш).
	*/
	Backslash = GLFW_KEY_BACKSLASH,

	/**
	* @brief Клавиша ']' (правая квадратная скобка).
	*/
	RightBracket = GLFW_KEY_RIGHT_BRACKET,

	/**
	* @brief Клавиша 'A'.
	*/
	A = GLFW_KEY_A,

	/**
	* @brief Клавиша 'B'.
	*/
	B = GLFW_KEY_B,

	/**
	* @brief Клавиша 'C'.
	*/
	C = GLFW_KEY_C,

	/**
	* @brief Клавиша 'D'.
	*/
	D = GLFW_KEY_D,

	/**
	* @brief Клавиша 'E'.
	*/
	E = GLFW_KEY_E,

	/**
	* @brief Клавиша 'F'.
	*/
	F = GLFW_KEY_F,

	/**
	* @brief Клавиша 'G'.
	*/
	G = GLFW_KEY_G,

	/**
	* @brief Клавиша 'H'.
	*/
	H = GLFW_KEY_H,

	/**
	* @brief Клавиша 'I'.
	*/
	I = GLFW_KEY_I,

	/**
	* @brief Клавиша 'J'.
	*/
	J = GLFW_KEY_J,

	/**
	* @brief Клавиша 'K'.
	*/
	K = GLFW_KEY_K,

	/**
	* @brief Клавиша 'L'.
	*/
	L = GLFW_KEY_L,

	/**
	* @brief Клавиша 'M'.
	*/
	M = GLFW_KEY_M,

	/**
	* @brief Клавиша 'N'.
	*/
	N = GLFW_KEY_N,

	/**
	* @brief Клавиша 'O'.
	*/
	O = GLFW_KEY_O,

	/**
	* @brief Клавиша 'P'.
	*/
	P = GLFW_KEY_P,

	/**
	* @brief Клавиша 'Q'.
	*/
	Q = GLFW_KEY_Q,

	/**
	* @brief Клавиша 'R'.
	*/
	R = GLFW_KEY_R,

	/**
	* @brief Клавиша 'S'.
	*/
	S = GLFW_KEY_S,

	/**
	* @brief Клавиша 'T'.
	*/
	T = GLFW_KEY_T,

	/**
	* @brief Клавиша 'U'.
	*/
	U = GLFW_KEY_U,

	/**
	* @brief Клавиша 'V'.
	*/
	V = GLFW_KEY_V,

	/**
	* @brief Клавиша 'W'.
	*/
	W = GLFW_KEY_W,

	/**
	* @brief Клавиша 'X'.
	*/
	X = GLFW_KEY_X,

	/**
	* @brief Клавиша 'Y'.
	*/
	Y = GLFW_KEY_Y,

	/**
	* @brief Клавиша 'Z'.
	*/
	Z = GLFW_KEY_Z,

	/**
	* @brief Клавиша NumLock.
	*/
	NumLock = GLFW_KEY_NUM_LOCK,

	/**
	* @brief Клавиша CapsLock.
	*/
	CapsLock = GLFW_KEY_CAPS_LOCK,

	/**
	* @brief Клавиша ScrollLock.
	*/
	ScrollLock = GLFW_KEY_SCROLL_LOCK,

	/**
	* @brief Клавиша RightShift.
	*/
	RightShift = GLFW_KEY_RIGHT_SHIFT,

	/**
	* @brief Клавиша LeftShift.
	*/
	LeftShift = GLFW_KEY_LEFT_SHIFT,

	/**
	* @brief Клавиша RightControl.
	*/
	RightControl = GLFW_KEY_RIGHT_CONTROL,

	/**
	* @brief Клавиша LeftControl.
	*/
	LeftControl = GLFW_KEY_LEFT_CONTROL,

	/**
	* @brief Клавиша RightAlt.
	*/
	RightAlt = GLFW_KEY_RIGHT_ALT,

	/**
	* @brief Клавиша LeftAlt.
	*/
	LeftAlt = GLFW_KEY_LEFT_ALT,

	/**
	* @brief Левая клавиша Command или Windows.
	*/
	LeftCommand = GLFW_KEY_LEFT_SUPER,

	/**
	* @brief Правая клавиша Command или Windows.
	*/
	RightCommand = GLFW_KEY_RIGHT_SUPER,

	/**
	* Клавиша Menu.
	*/
	Menu = GLFW_KEY_MENU,

	/**
	* Левая (или основная) кнопка мыши.
	*/
	Mouse0 = GLFW_MOUSE_BUTTON_LEFT,

	/**
	* Правая кнопка мыши (или дополнительная кнопка мыши).
	*/
	Mouse1 = GLFW_MOUSE_BUTTON_RIGHT,

	/**
	* Средняя кнопка мыши (или третья кнопка мыши).
	*/
	Mouse2 = GLFW_MOUSE_BUTTON_MIDDLE,

	/**
	* Дополнительная (четвертая) кнопка мыши.
	*/
	Mouse3 = GLFW_MOUSE_BUTTON_4,

	/**
	* Дополнительная (пятая) кнопка мыши.
	*/
	Mouse4 = GLFW_MOUSE_BUTTON_5,

	/**
	* Дополнительная (или шестая) кнопка мыши.
	*/
	Mouse5 = GLFW_MOUSE_BUTTON_6,

	/**
	* Дополнительная (или седьмая) кнопка мыши.
	*/
	Mouse6 = GLFW_MOUSE_BUTTON_7,

	/**
	* Дополнительная (или восьмая) кнопка мыши.
	*/
	Mouse7 = GLFW_MOUSE_BUTTON_8
};