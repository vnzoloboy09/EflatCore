#include "InputManager.h"

namespace Eflat {
    InputManager::InputManager() {

    }

    void InputManager::BeginFrame() {
        m_MouseDelta = m_MousePos - m_LastMousePos;
        m_LastMousePos = m_MousePos;
        m_ScrollYThisFrame = 0.0f;
    }

    void InputManager::EndFrame() {
        for (auto& ks : m_KeyStates) {
            switch (ks.phase)
            {
            case KeyPhase::Pressed:
                ks.phase = KeyPhase::Held;
                break;
            case KeyPhase::Released:
                ks.phase = KeyPhase::Up;
                break;
            default:
                break;
            }
        }

        for (auto& ms : m_MouseStates) {
            switch (ms.phase) {
            case KeyPhase::Pressed:
                ms.phase = KeyPhase::Held;
                break;
            case KeyPhase::Released:
                ms.phase = KeyPhase::Up;
                break;
            default:
                break;
            }
        }
    }

    void InputManager::OnKeyDown(uint32_t scancode) {
        if (scancode > MAX_KEYS)
            return;
        auto& ks = m_KeyStates[scancode];
        ks.phase = (ks.phase == KeyPhase::Held || ks.phase == KeyPhase::Pressed)
            ? KeyPhase::Held
            : KeyPhase::Pressed;
    }

    void InputManager::OnKeyUp(uint32_t scancode) {
        if (scancode >= MAX_KEYS) 
            return;
        m_KeyStates[scancode].phase = KeyPhase::Released;
    }

    void InputManager::OnMouseMove(float x, float y) {
        m_MousePos = { x, y };
    }

    void InputManager::OnMouseButton(MouseButton btn, bool down) {
        size_t idx = static_cast<size_t>(btn);
        if (idx >= MAX_MOUSE_BUTTONS) return;
        auto& ms = m_MouseStates[idx];
        if (down) {
            ms.phase = (ms.phase == KeyPhase::Held || ms.phase == KeyPhase::Pressed)
                ? KeyPhase::Held
                : KeyPhase::Pressed;
        }
        else {
            ms.phase = KeyPhase::Released;
        }
    }

    void InputManager::OnMouseWheel(float x, float y) {
        m_ScrollYThisFrame += y;
    }

    bool InputManager::IsKeyHeld(uint32_t scancode) const {
        if (scancode >= MAX_KEYS) 
            return false;
        return m_KeyStates[scancode].phase == KeyPhase::Held;
    }

    bool InputManager::IsKeyPressed(uint32_t scancode) const {
        if (scancode >= MAX_KEYS) 
            return false;
        return m_KeyStates[scancode].phase == KeyPhase::Pressed;
    }

    bool InputManager::IsKeyReleased(uint32_t scancode) const {
        if (scancode >= MAX_KEYS) 
            return false;
        return m_KeyStates[scancode].phase == KeyPhase::Released;
    }

    bool InputManager::IsMouseHeld(MouseButton btn) const {
        size_t idx = static_cast<size_t>(btn);
        if (idx >= MAX_MOUSE_BUTTONS)
            return false;
        return m_MouseStates[idx].phase == KeyPhase::Held;
    }

    bool InputManager::IsMousePressed(MouseButton btn) const {
        size_t idx = static_cast<size_t>(btn);
        if (idx >= MAX_MOUSE_BUTTONS) 
            return false;
        return m_MouseStates[idx].phase == KeyPhase::Pressed;
    }

    bool InputManager::IsMouseReleased(MouseButton btn) const {
        size_t idx = static_cast<size_t>(btn);
        if (idx >= MAX_MOUSE_BUTTONS) 
            return false;
        return m_MouseStates[idx].phase == KeyPhase::Released;
    }

    void InputManager::BindAction(std::string name, uint32_t key) {
        m_ActionMap[std::move(name)] = key;
    }

    bool InputManager::IsActionHeld(std::string_view name) const {
        auto it = m_ActionMap.find(std::string(name));
        return (it != m_ActionMap.end()) ? IsKeyHeld(it->second) : false;
    }

    bool InputManager::IsActionPressed(std::string_view name) const {
        auto it = m_ActionMap.find(std::string(name));
        return (it != m_ActionMap.end()) ? IsKeyPressed(it->second) : false;
    }

    float InputManager::GetActionAxis1D(std::string_view name) const {
        auto it = m_ActionMap.find(std::string(name));
        if (it == m_ActionMap.end())
            return 0.0f;
        uint32_t key = it->second;
        auto phase = m_KeyStates[key].phase;
        return (phase == KeyPhase::Pressed || phase == KeyPhase::Held) ? 1.0f : 0.0f;
    }
}