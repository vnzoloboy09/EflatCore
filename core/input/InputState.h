#pragma once
#include <cstdint>
#include <SDL3/SDL_scancode.h>

namespace Eflat {
	enum class KeyPhase : uint8_t { 
		Up, 
		Pressed, 
		Held, 
		Released 
	};
	
	constexpr size_t MAX_KEYS = SDL_SCANCODE_COUNT;

	struct KeyState {
		KeyPhase phase = KeyPhase::Up;
	};

	enum class MouseButton : uint8_t {
		Left,
		Middle,
		Right,
		X1,
		X2,
		Count
	};
	static constexpr size_t MAX_MOUSE_BUTTONS = static_cast<size_t>(MouseButton::Count);

}