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

Window::Window(const int width, const int height, const std::string &title) : data_ {{width, height}, {0, 0}, title} {
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfw_init_) {
        if (!glfwInit()) {
            throw WindowError {"Could not initialize GLFW"};
        }
        glfw_init_ = true;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    handle_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (handle_ == nullptr) {
        glfwTerminate();
        throw WindowError {"Could not create window handle"};
    }

    glfwSetWindowUserPointer(handle_, &data_);

    glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow *handle, int width, int height) {
        auto *const data         = static_cast<Data *>(glfwGetWindowUserPointer(handle));
        data->framebuffer_size.x = width;
        data->framebuffer_size.y = height;
        glViewport(0, 0, width, height);
    });

    glfwSetWindowSizeCallback(handle_, [](GLFWwindow *handle, int width, int height) {
        auto *const data    = static_cast<Data *>(glfwGetWindowUserPointer(handle));
        data->window_size.x = width;
        data->window_size.y = height;
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

    Dimensions framebuffer_size;
    glfwGetFramebufferSize(handle_, &framebuffer_size.x, &framebuffer_size.y);
    glViewport(0, 0, framebuffer_size.x, framebuffer_size.y);
    data_.framebuffer_size = framebuffer_size;
}

Window::~Window() {
    if (handle_ != nullptr) {
        glfwDestroyWindow(handle_);
    }

    if (glfw_init_) {
        glfwTerminate();
    }
}

bool Window::IsOpen() const {
    if (handle_ == nullptr) {
        throw WindowHandleIsNullptr {};
    }
    return glfwWindowShouldClose(handle_) == 0;
}

Dimensions Window::GetSize() const {
    if (handle_ == nullptr) {
        throw WindowHandleIsNullptr {};
    }
    return data_.window_size;
}

Dimensions Window::GetFramebufferSize() const {
    if (handle_ == nullptr) {
        throw WindowHandleIsNullptr {};
    }
    return data_.framebuffer_size;
}

void Window::SwapBuffers() const {
    if (handle_ == nullptr) {
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
