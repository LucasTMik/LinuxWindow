#pragma once
#include "functional"
#include "Events/Event.h"

#define MOUSE_MOVE_CALLBACK void(float xpos, float ypos)
#define KEY_CALLBACK        void(float keycode)


namespace MWin {
    template<typename T>
    using EventCallback = std::is_function<void(T&)>;

    struct AWindowData {
        unsigned int m_Width;
        unsigned int m_Height;
        EventCallback<Event> callback;
    };

    class AWindow {
        public:
            virtual void Update() = 0;

            void OnMouseMoveCallback(std::function<MOUSE_MOVE_CALLBACK> callback) 
            {
                m_MouseMoveCallback = callback;
            };
            
            void OnKeyPressCallback(std::function<KEY_CALLBACK> callback)
            {
                m_KeyPressCallback = callback;
            };

            void OnKeyReleaseCallback(std::function<KEY_CALLBACK> callback)
            {
                m_KeyReleasedCallback = callback;
            };

        private:
            unsigned int m_Width;
            unsigned int m_Height;
            AWindowData m_Data;

        protected:
            std::function<MOUSE_MOVE_CALLBACK> m_MouseMoveCallback;
            std::function<KEY_CALLBACK> m_KeyPressCallback;
            std::function<KEY_CALLBACK> m_KeyReleasedCallback;
    };
}