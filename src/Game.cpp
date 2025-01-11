#include "Game.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include <string>
#include <iostream>
#include <stdexcept>

#include "game/Settings.h"

#include "core/time/Clock.h"
#include "core/input/Input.h"
#include "core/ResourceManager.h"

#include "core/audio/Audio.h"

Game::Game(int width, int height) 
	: _width(WINDOW_WIDTH), _height(WINDOW_HEIGHT), _direction(Direction::Right)
{
	// Initialization rand()
	srand(time(nullptr));

	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error("Failed to initialize GLFW library");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, "Tetris game by dryerem19", nullptr, nullptr);
	if (_window == nullptr) {
		throw std::runtime_error("Failed to create GLFW window");
	}
	
	glfwMakeContextCurrent(_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glfwSwapInterval(1);

	glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));
	glfwSetFramebufferSizeCallback(_window, Game::OnFramebufferSizeCallback);

	glViewport(0, 0, _width, _height);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	// Инициализация подсистемы рендеринга
	Renderer::GetInstance();

	// Инициализация подсистемы звука
	AudioDevice::GetInstance();

	Input::Init(_window);
}

Game::~Game()
{
	glfwTerminate();
}

void Game::Beep()
{
	// Выводит звук
	std::cout << "\a";
}

// Игровой цикл
int Game::Exec()
{
	Clock clock;
	double targetFPS = 16.0;
	double targetFrameTime = 1.0 / targetFPS;

	double timer = 0;
	double delay = 0.3;

	while (!glfwWindowShouldClose(_window))
	{
		/* Poll and handle events (inputs, window resize, etc.) */
		glfwPollEvents();

		/* Start the Dear ImGui frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		double elapsedTime = clock.GetElapsedTime();
		if (elapsedTime < targetFrameTime) {
			std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameTime - elapsedTime));
		}

		AudioDevice::GetInstance().Update();
		Input::Update();

		Update();

		// Gui stuff
		RenderMenu();
		ImGui::Render();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		if (_newGame) {
			NewGame();
			_newGame = false;
		}

		// Render the game
		Render();

		// Render the ImGui frame
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(_window);
		glfwSwapBuffers(_window);
		clock.Restart();
	}

	/* Cleanup */
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return EXIT_SUCCESS;
}

void Game::NewGame()
{
	_gameManager = std::make_unique<GameManager>();
	_gameManager->InitGame();

	_camera.SetViewport(0, 0, _width, _height);

	Renderer::GetInstance().SetCamera(&_camera);
}

// Обновление состояния игры
void Game::Update()
{
	if (Input::GetKey(KeyCode::Escape)) {
		_state = GameState::GamePause;
	}

	if (_state == GameState::GameActive) {
		_gameManager->Update();
		if (_gameManager->IsGameOver()) {
			_state = GameState::GameOver;
		}
	}
}

// Вывод на экран
void Game::Render()
{
	if (_state == GameState::GameActive) {
		_gameManager->Draw(Renderer::GetInstance());
	}
}

void Game::RenderMenu()
{
	ImGuiIO& io = ImGui::GetIO();

	if (_state == GameState::GameOver)
	{
		ImGui::SetNextWindowPos({ io.DisplaySize.x * 0.5f, 100 }, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		if (ImGui::Begin("FakeWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize | 
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground))
		{
			static const std::string text = "Gameover!";

			auto windowWidth = ImGui::GetWindowSize().x;
			auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
			
			// Текст по центру
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
			ImGui::Text(text.c_str());
			ImGui::End();
		}
	}

	if (_state == GameState::GameMenu || _state == GameState::GamePause || _state == GameState::GameOver) 
	{
		// Выравнивание окна по центру
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

		// Применяем стиль к окну для выравнивания заголовка по центру окна
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));

		if (ImGui::Begin("Main menu", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse))
		{
			static const float buttonWidth = 75.0f;
			static const float buttonHeight = 20.0f;

			// Выравниваем кнопку по центру
			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
			if (ImGui::Button("New game", ImVec2(buttonWidth, buttonHeight))) {
				_newGame = true;
				_state = GameState::GameActive;
			}

			if (_state == GameState::GamePause)
			{
				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
				if (ImGui::Button("Continue", ImVec2(buttonWidth, buttonHeight))) {
					_state = GameState::GameActive;
				}
			}

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
			if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight))) {
				glfwSetWindowShouldClose(_window, true); // Закрываем окно
			}

			ImGui::PopStyleVar(); // Отменяем стиль
			ImGui::End();
		}
	}
}

void Game::OnFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Game* handle = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
	if (!handle) {
		return;
	}

	handle->_width = width;
	handle->_height = height;
	handle->_camera.SetViewport(0, 0, width, height);
}
