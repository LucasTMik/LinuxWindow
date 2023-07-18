#include "./LinuxWindow.h"
#include "../../Core.h"

namespace MWin {
    LinuxWindow::LinuxWindow(unsigned int width, unsigned int height, const char* name)
    {
        m_Display = XOpenDisplay(nullptr);
        ASSERT(m_Display != nullptr);

        int screen = DefaultScreen(m_Display);
        m_Window = XCreateSimpleWindow(m_Display, RootWindow(m_Display, screen), 0, 0, 800, 600, 1, BlackPixel(m_Display, screen), WhitePixel(m_Display, screen));
        XStoreName(m_Display, m_Window, name);

        std::cout << "Window Created" << std::endl;

        // Map the window to the screen
        XMapWindow(m_Display, m_Window);

        // Enable all input masks for the window
        long eventMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                     EnterWindowMask | LeaveWindowMask | PointerMotionMask | ExposureMask |
                     StructureNotifyMask | SubstructureNotifyMask | FocusChangeMask |
                     PropertyChangeMask;

        XSelectInput(m_Display, m_Window, eventMask);
    }

    LinuxWindow::~LinuxWindow()
    {
        XDestroyWindow(m_Display, m_Window);
        XCloseDisplay(m_Display);
    }

    void LinuxWindow::Update()
    {
        XNextEvent(m_Display, &m_Event);

        switch(m_Event.type)
        {
            case KeyPress:
            {
                AWindow::m_KeyPressCallback(m_Event.xkey.keycode);
                break;
            }
            case KeyRelease:
            {
                AWindow::m_KeyReleasedCallback(m_Event.xkey.keycode);
                break;
            }
            case ButtonPress:
            {
                AWindow::m_KeyPressCallback(m_Event.xkey.keycode);
                break;
            }
            case ButtonRelease:
            {
                AWindow::m_KeyReleasedCallback(m_Event.xkey.keycode);
                break;
            }
            case VisibilityNotify:
            {
                break;
            }
            case FocusIn:
            {
                break;
            }
            case FocusOut:
            {
                break;
            }
            case MotionNotify:
            {
                AWindow::m_MouseMoveCallback(m_Event.xmotion.x, m_Event.xmotion.y);
                break;
            }
            case NoExpose:
            case GraphicsExpose:
            case Expose:
            {
                break;
            }
            case DestroyNotify:
            {
                break;
            }
        }
    }
}