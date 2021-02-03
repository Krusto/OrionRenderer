#include <iostream>
#include <chrono>
#include "Orion.h"

using namespace Orion;

void OnWindowClose(GLFWwindow* window) {
	glfwSetWindowShouldClose(window, true);

}

int main() {

	Window window("Title", { 1280,720 }, { 1280,720 });
	glfwMakeContextCurrent(window);
	window.OnWindowClose(OnWindowClose);
	std::vector<Orion::Extension> extensionsToLoad{
		Extension::DEBUG_REPORT,
		Extension::DEBUG_UTILS,
		Extension::KHR_SURFACE,
		Extension::KHR_WIN32_SURFACE
	};

	Orion::Renderer::Init(&window, extensionsToLoad, VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);

	Orion::VertexLayout layout{ {"position",Orion::ShaderDataType::type::vec3},{"color",Orion::ShaderDataType::type::vec3} };

	std::vector<Orion::Vertex> vertices
	{
	{{0.0f, -0.5f,0.0f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f,0.0f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f,0.0f}, {0.0f, 0.0f, 1.0f}}
	};

	while (window.IsOpen()) {
		auto start = std::chrono::steady_clock::now();
		
		window.Begin();

		Renderer::DrawFrame();

		window.End();
		
		auto end = std::chrono::steady_clock::now();

		OrionLog("%dFPS",(1.0 / (double)std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count())*1000.0);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	Orion::Renderer::Destroy();
	return 0;
}
