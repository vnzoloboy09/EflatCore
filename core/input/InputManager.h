#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <cstddef>

#include "types.h"
#include "InputState.h"

namespace Eflat {
	class InputManager {
	public:
		void BeginFrame();
        void EndFrame();
		void OnKeyDown(uint32_t scancode);
		void OnKeyUp(uint32_t scancode);
		void OnMouseMove(float x, float y);
		void OnMouseButton(MouseButton btn, bool down);
		void OnMouseWheel(float x, float y);

        bool IsKeyHeld(uint32_t scancode) const;
        bool IsKeyPressed(uint32_t scancode) const;
        bool IsKeyReleased(uint32_t scancode) const;

        Vec2 GetMousePos() const;
        Vec2 GetMouseDelta() const;
        bool IsMouseHeld(MouseButton btn) const;
        bool IsMousePressed(MouseButton btn) const;
        bool IsMouseReleased(MouseButton btn) const;
        float GetScrollY() const;

        void BindAction(std::string name, uint32_t key);
        bool IsActionHeld(std::string_view name) const;
        bool IsActionPressed(std::string_view name) const;
        float GetActionAxis1D(std::string_view name) const;
    
    private:
        std::array<KeyState, MAX_KEYS> m_KeyStates{};
        Vec2 m_MousePos, m_MouseDelta, m_LastMousePos;
        float m_ScrollY, m_ScrollYThisFrame;
        std::array<KeyState, MAX_MOUSE_BUTTONS> m_MouseStates{};
	};
}