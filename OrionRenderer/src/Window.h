#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include <functional>
#include "Util/Timestep.h"
struct Size2i {
public:
	uint32_t width;
	uint32_t height;
};

class Window {
public:
	Window() = default;
	Window(std::string_view Title, Size2i windowSize, Size2i resolution, int argc = 0, char** argv = nullptr);
	
	~Window();

	void Begin();
	void Loop();
	void End();

	void OnRender(void (*function)(Timestep& dt));
	void OnMouseMove(void (*function)(GLFWwindow* window, double xpos, double ypos));
	void OnKeyboard(void (*function)(GLFWwindow* window, int key, int scancode, int action, int mods));
	void OnWindowResize(void (*function)(GLFWwindow* window,int width, int height));
	void OnWindowClose(void (*function)(GLFWwindow* window));
	auto& getDeltaTime() { return this->mDT; }
	const auto& getDeltaTime() const { return this->mDT; }

	void setDeltaTime(double value) {
		mDT.setTime(value);
	}

	auto& getHandle() { return mWindow; }
	const auto& getHandle() const{ return mWindow; }

	bool IsOpen() { return !glfwWindowShouldClose(mWindow); }

	Size2i GetWindowExtent();

	Size2i resolution{};

	operator GLFWwindow* () { return mWindow; }
private:
	GLFWwindow* mWindow;
	Timestep mDT;
};

typedef Window* WindowHandle;