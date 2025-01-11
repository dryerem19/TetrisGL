#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "types/direction.h"

#include <memory>

#include "core/render/Renderer.h"
#include "game/GameManager.h"

enum class GameState
{
	GameActive,
	GamePause,
	GameMenu,
	GameOver,
	GameWin
};

class Game
{
private:
	bool _newGame = false;
	int _width, _height;
	GLFWwindow* _window;

	std::shared_ptr<Texture> _blueTexture;
	std::unique_ptr<Sprite> _blue;

	Camera _camera;
	
	std::unique_ptr<GameManager> _gameManager;

	int _score = 0;
	GameState _state = GameState::GameMenu;
	Direction _direction;
public:
	Game(int width = 640, int height = 480);
	~Game();

	void Beep();
	int Exec();
	void NewGame();

	void DoCollide();

private:
	void ProcessInput();
	void Update();
	void Render();
	void RenderMenu();

	static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void OnFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};