#include <iostream>
#include <IPEngine/Window/Window.hpp>
#include <IPEngine/Window/GLFW.hpp>
#include<vector>
#include <fstream>

int main() {

    GLFW::init(3, 3);
    
    Window window(800, 600, "Puppetier");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glEnable(GL_DEPTH_TEST);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // read from glsl file
    std::ifstream vertexFile("assets/shaders/vertex_core.glsl");
    std::string vertexFileStr((std::istreambuf_iterator<char>(vertexFile)), 
        (std::istreambuf_iterator<char>()));

    const char* vertexShaderSource = vertexFileStr.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    if (!vertexFile.is_open()) {
        std::cout << "Unable to open the file" << std::endl;
        return -1;
    }

    while(!window.shouldClose()) {
        window.render();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}