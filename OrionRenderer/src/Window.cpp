#include "Window.h"
#include <iostream>

Window::Window(std::string_view Title, Size2i windowSize, Size2i resolution, int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cerr << "GLFW CAN NOT INITIALIZE!!!";
		exit(-1);
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE); 
	this->mWindow = glfwCreateWindow(windowSize.width, windowSize.height, Title.data(), nullptr, nullptr);
	glfwMakeContextCurrent(mWindow);
	glfwSwapInterval(0);
	glfwSetWindowShouldClose(mWindow, 0);
}
Window::~Window()
{
	glfwDestroyWindow(mWindow);
}

void Window::Begin()
{
	glfwPollEvents();
}

void Window::Loop()
{
	/*sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::EventType::MouseMoved:
			(*this->onMouseMove)(mDT, event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::EventType::KeyPressed:
			(*this->onKeyboard)(event.key.code , event.mouseMove.x,event.mouseMove.y);
			break;
		case sf::Event::EventType::Resized:
			(*this->onWindowResize)(event.size.width, event.size.height);
		case sf::Event::EventType::Closed:
			this->mWindow.close();
		}
	}

	(*this->onRender)(mDT);*/
}

void Window::End()
{
}

void Window::OnRender(void(*function)(Timestep& dt))
{
}

void Window::OnMouseMove(void(*function)(GLFWwindow* window, double xpos, double ypos))
{
	glfwSetCursorPosCallback(this->mWindow, *function);
}

void Window::OnKeyboard(void(*function)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
	glfwSetKeyCallback(this->mWindow, function);
}

void Window::OnWindowResize(void(*function)(GLFWwindow* window, int width, int height))
{
	glfwSetWindowSizeCallback(this->mWindow, function);
}

void Window::OnWindowClose(void(*function)(GLFWwindow* window))
{
	glfwSetWindowCloseCallback(this->mWindow, function);
}

Size2i Window::GetWindowExtent()
{
	int sizeX,sizeY;
	glfwGetWindowSize(mWindow,&sizeX,&sizeY);
	return { (uint32_t)sizeX,(uint32_t)sizeY };
}

