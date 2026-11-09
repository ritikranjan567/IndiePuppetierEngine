#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE


/// @brief Contians onetime method to initialized glfw, throw error on unexpected values
class GLFW {
    static void setErrorCallback();
    static void setInitAndHints(int majorVersion, int minorVersion);

    static void error_callback(int error, const char* description);
public:
    static void init(int majorVersion, int minorVersion);
};

class GLFWInitException : public std::exception {
private:
    std::string message;
public:
    GLFWInitException(const char* msg) : message(msg) {}

    const char* what() const noexcept {
        return message.c_str();
    }
};