#include "Clock.h"

// Dependency library
#include <GLFW/glfw3.h> // glfwGetTime()

Clock::Clock()
{
	this->Restart();
}

double Clock::GetElapsedTime() const
{
	return glfwGetTime() - _startTime;
}

void Clock::Restart()
{
	_startTime = glfwGetTime();
}
