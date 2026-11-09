#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

/// @brief Class is responsible for creating windows for engine
class Window {
public:
    explicit Window(int width, int height, const std::string& title);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    void render();
    GLFWwindow* getGLFWwindow() const noexcept;
    void setShouldClose(bool flag);
    bool shouldClose() const noexcept;
    void destroy() noexcept;

private:
    std::string title;
    GLFWwindow* window;
    int width, height;
    static bool gladLoaded;
    void setUp();
    static void framebuffer_size_callback([[maybe_unused]]GLFWwindow* window, int width, int height);
};