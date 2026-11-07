#include <IPEngine/Window/Window.hpp>

Window::Window(int width, int height, const std::string& title) : 
    title(title), window(nullptr), width(width), height(height) {
    setUp();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow *Window::getGLFWwindow() const noexcept
{
    return window;
}

void Window::closeWindow()
{
    glfwSetWindowShouldClose(window, true);
}

bool Window::isClosed() const noexcept
{
    return !glfwWindowShouldClose(window);
}

void Window::setColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Window::setUp()
{

    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw "Failed to create glfw window";
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw "Failed to initialize GLAD";
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* _window, int width, int height)
{
    glViewport(0, 0, width, height);
}
