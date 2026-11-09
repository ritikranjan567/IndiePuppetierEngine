#include <IPEngine/Window/Window.hpp>
#include <utility>

bool Window::gladLoaded = false;

Window::Window(int width, int height, const std::string& title) :
    title(title), window(nullptr), width(width), height(height) {
    setUp();
}

Window::~Window()
{
    destroy();
}

Window::Window(Window&& other) noexcept :
    title(std::move(other.title)),
    window(std::exchange(other.window, nullptr)),
    width(other.width),
    height(other.height) {
}

Window& Window::operator=(Window&& other) noexcept
{
    if (this != &other) {
        destroy();
        title = std::move(other.title);
        window = std::exchange(other.window, nullptr);
        width = other.width;
        height = other.height;
    }
    return *this;
}

void Window::render()
{
    glfwMakeContextCurrent(window);
    glfwSwapBuffers(window);
}

GLFWwindow *Window::getGLFWwindow() const noexcept
{
    return window;
}

void Window::setShouldClose(bool flag)
{
    glfwSetWindowShouldClose(window, flag);
}

bool Window::shouldClose() const noexcept
{
    return glfwWindowShouldClose(window);
}

void Window::destroy() noexcept
{
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

void Window::setUp()
{
    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

    if (!window) {
        throw std::runtime_error("Failed to create GLFW window " + title);
    }

    glfwMakeContextCurrent(window);

    if (!Window::gladLoaded && !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        destroy();
        throw std::runtime_error("Failded to load glad for window " + title);
    }

    Window::gladLoaded = true;

    int tempWidth, tempHeight;
    glfwGetFramebufferSize(window, &tempWidth, &tempHeight);
    glViewport(0, 0, tempWidth, tempHeight);

    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
}

void Window::framebuffer_size_callback([[maybe_unused]]GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
