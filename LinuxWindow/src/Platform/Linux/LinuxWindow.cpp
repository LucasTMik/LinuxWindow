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
        m_Data.Running = true;

        m_Display = XOpenDisplay(nullptr);
        ASSERT(m_Display != nullptr);

        // Enable all input masks for the window
        long eventMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                     EnterWindowMask | LeaveWindowMask | PointerMotionMask | ExposureMask |
                     StructureNotifyMask | SubstructureNotifyMask | FocusChangeMask |
                     PropertyChangeMask | VisibilityChangeMask;

        static int visualAttribs[] = {
            GLX_RGBA,
            GLX_DEPTH_SIZE, 24,
            GLX_DOUBLEBUFFER,
            None
        };

        m_Visual = glXChooseVisual(m_Display, DefaultScreen(m_Display), visualAttribs);
        
        int screen = DefaultScreen(m_Display);
        Window root = RootWindow(m_Display, screen);
        XSetWindowAttributes windowAttribs;
        windowAttribs.colormap = XCreateColormap(m_Display, root, m_Visual->visual, AllocNone);
        windowAttribs.event_mask = eventMask;

        m_Window = XCreateWindow(m_Display, root, 0, 0, m_Data.Width, m_Data.Height, 0, m_Visual->depth, InputOutput, m_Visual->visual, CWColormap | CWEventMask, &windowAttribs);
        XStoreName(m_Display, m_Window, m_Data.Name.c_str());

        GLXContext glContext = glXCreateContext(m_Display, m_Visual, nullptr, GL_TRUE);
        if(!glContext)
        {
            std::cout << "Failed to create GL Context" << std::endl;
            m_Data.Running = false;
        }

        glXMakeCurrent(m_Display, m_Window, glContext);

        std::cout << "Window" << m_Data.Name.c_str() << "Created" << std::endl;

        // Map the window to the screen
        XMapWindow(m_Display, m_Window);
    }

    bool LinuxWindow::IsRunning() const 
    {
        return m_Data.Running;
    }

    AWindow* AWindow::Create(const AWindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        XDestroyWindow(m_Display, m_Window);
        XFree(m_Visual);
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
        glXSwapBuffers(m_Display, m_Window);
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