#include <IPEngine/Window/GLFW.hpp>

void GLFW::setErrorCallback()
{
    glfwSetErrorCallback(GLFW::error_callback);
}

void GLFW::setInitAndHints(int majorVersion, int minorVersion)
{
    if (!glfwInit()) {
        throw GLFWInitException("Failed to initialized glfw");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if defined(__APPLE__) || defined(Macintosh)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

void GLFW::error_callback(int error, const char *description)
{
    std::cout << "Error Code: " << error << std::endl;
    std::cerr << "[Error] " << description << std::endl;
}

void GLFW::init(int majorVersion, int minorVersion)
{
    if (majorVersion < 0 || minorVersion < 0) {
        throw std::runtime_error("Version should be a positive number");
    }
    setErrorCallback();
    setInitAndHints(majorVersion, minorVersion);

}
