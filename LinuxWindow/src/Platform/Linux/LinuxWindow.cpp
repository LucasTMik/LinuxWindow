#include "./LinuxWindow.h"
#include "../../Core.h"
#include "../../Events/KeyboardEvent.h"
#include "../../Events/MouseEvent.h"
#include "../../Events/ApplicationEvent.h"

namespace MWin {
    LinuxWindow::LinuxWindow(const AWindowProps props)
    {
      Init(props);
    }

    void LinuxWindow::Init(const AWindowProps props)
    {
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.Name = props.Name;

        m_Display = XOpenDisplay(nullptr);
        ASSERT(m_Display != nullptr);

        int screen = DefaultScreen(m_Display);
        m_Window = XCreateSimpleWindow(m_Display, RootWindow(m_Display, screen), 0, 0, m_Data.Width, m_Data.Height, 1, BlackPixel(m_Display, screen), WhitePixel(m_Display, screen));
        XStoreName(m_Display, m_Window, m_Data.Name.c_str());

        std::cout << "Window" << m_Data.Name.c_str() << "Created" << std::endl;

        // Map the window to the screen
        XMapWindow(m_Display, m_Window);

        // Enable all input masks for the window
        long eventMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                     EnterWindowMask | LeaveWindowMask | PointerMotionMask | ExposureMask |
                     StructureNotifyMask | SubstructureNotifyMask | FocusChangeMask |
                     PropertyChangeMask | VisibilityChangeMask;

        XSelectInput(m_Display, m_Window, eventMask);
    }

    AWindow* AWindow::Create(const AWindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        XDestroyWindow(m_Display, m_Window);
        XCloseDisplay(m_Display);
    }

    void LinuxWindow::SetEventCallback(const EventCallbackFn& func)
    {
        m_Data.Callback = func;
    }

    void LinuxWindow::HandleWindowEvents()
    {
        static XEvent w_Event;
        XNextEvent(m_Display, &w_Event);

        switch(w_Event.type)
        {
            case ButtonPress:
            case KeyPress:
            {
                KeyboardPress event(w_Event.xkey.keycode);
                m_Data.Callback(event);
                break;
            }
            case ButtonRelease:
            case KeyRelease:
            {
                KeyboardRelease event(w_Event.xkey.keycode);
                m_Data.Callback(event);
                break;
            }
            case MotionNotify:
            {
                MouseMoveEvent event(w_Event.xmotion.x, w_Event.xmotion.y);
                m_Data.Callback(event);
                break;
            }
            case ConfigureNotify:
            {
                ResizeEvent event(w_Event.xconfigure.width, w_Event.xconfigure.height);
                m_Data.Width = w_Event.xconfigure.width;
                m_Data.Height = w_Event.xconfigure.height;
                m_Data.Callback(event);
                break;
            }
        }        
    }

    void LinuxWindow::OnUpdate()
    {
        HandleWindowEvents();
    }

    unsigned int LinuxWindow::GetWidth() const 
    {
        return m_Data.Width;
    }

    unsigned int LinuxWindow::GetHeight() const
    {
        return m_Data.Height;
    }
}