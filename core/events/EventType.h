#pragma once

#include <cstdint>

namespace Eflat
{
    enum class EventType : uint32_t {
        // Application
        AppInit,
        AppQuit,
        AppPause,
        AppResume,

        // Window
        WindowResize,
        WindowClose,
        WindowFocus,
        WindowFocusLost,

        // Input
        KeyDown,
        KeyUp,
        MouseMove,
        MouseButtonDown,
        MouseButtonUp,
        MouseWheel,
        GamepadConnected,
        GamepadDisconnected,
        GamepadButtonDown,
        GamepadButtonUp,
        GamepadAxis,

        // Assets
        AssetLoaded,
        AssetUnloaded,
        AssetLoadFailed,

        // Scene
        SceneLoadStart,
        SceneLoadComplete,
        SceneUnload,
        SceneChange,
    };
}

