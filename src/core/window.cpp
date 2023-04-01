#include "core/window.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

static void GlfwErrorCallback(int error, const char *message) {
    std::cerr << "GLFW Error #" << error << ": " << message << '\n';
}

namespace core {

bool Window::glfw_init_ {};
bool Window::glad_loaded_ {};

Window::Window(const int width, const int height, const std::string &title) : data_ {width, height, title} {
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfw_init_) {
        if (!glfwInit()) {
            throw WindowError {"Could not initialize GLFW"};
        }
        glfw_init_ = true;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    handle_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (handle_ == nullptr) {
        glfwTerminate();
        throw WindowError {"Could not create window handle"};
    }

    glfwSetWindowUserPointer(handle_, &data_);

    glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow *handle, int width, int height) {
        auto *const data = static_cast<Data *>(glfwGetWindowUserPointer(handle));
        data->width      = width;
        data->height     = height;
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    if (!glad_loaded_) {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glfwDestroyWindow(handle_);
            glfwTerminate();
            throw WindowError {"Could not initialize GLAD"};
        }
        glad_loaded_ = true;
    }

    glViewport(0, 0, width, height);
}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
    }

    if (glfw_init_) {
        glfwTerminate();
    }
}

bool Window::IsOpen() const {
    if (!handle_) {
        throw WindowHandleIsNullptr {};
    }

    return glfwWindowShouldClose(handle_) == 0;
}

void Window::SwapBuffers() const {
    if (!handle_) {
        throw WindowHandleIsNullptr {};
    }
    glfwSwapBuffers(handle_);
}

void Window::PollEvents() noexcept {
    if (glfw_init_) {
        glfwPollEvents();
    }
}

}  // namespace core
