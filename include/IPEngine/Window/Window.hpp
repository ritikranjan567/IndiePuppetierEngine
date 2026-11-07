#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

/// @brief Class is responsible for creating windows for engine
class Window {
public:
    Window() = default;
    Window(int width, int height, const std::string& title);
    ~Window();

    void update();
    GLFWwindow* getGLFWwindow() const noexcept;
    void closeWindow();
    bool isClosed() const noexcept;
    void setColor(float r, float g, float b, float a);

private:
    std::string title;
    GLFWwindow* window;
    int width, height;
    void setUp();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};