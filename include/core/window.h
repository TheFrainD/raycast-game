#pragma once

#include <stdexcept>
#include <string>

struct GLFWwindow;

namespace core {

class WindowError : public std::runtime_error {
public:
    explicit WindowError(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class WindowHandleIsNullptr : public WindowError {
public:
    WindowHandleIsNullptr() : WindowError("Window handle is nullptr") {}
};

class Window {
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    Window(const Window &)            = delete;
    Window(Window &&)                 = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&)      = delete;

    [[nodiscard]] bool IsOpen() const;
    void SwapBuffers() const;

    static void PollEvents() noexcept;

private:
    static bool glfw_init_;
    static bool glad_loaded_;

    struct Data {
        int width;
        int height;
        std::string title;
    };

    GLFWwindow *handle_ {nullptr};
    Data data_;
};

}  // namespace core