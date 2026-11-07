#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IPEngine/Window/Window.hpp>

int main() {

    int res = glfwInit();
    if (res != GLFW_TRUE) throw "Error in init";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if defined(__APPLE__) || defined(Macintosh)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    Window window1(800, 600, "First window");

    while(window1.isClosed()) {
        window1.update();
    }


    return 0;
}