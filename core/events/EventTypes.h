#pragma once

#include "IEvent.h"
#include "EventType.h"

namespace Eflat {
    struct EmptyEvent : IEvent {
        EventType type;
        explicit EmptyEvent(EventType t) : type(t) {}
        EventType Type() const override { return type; }
        uint64_t Timestamp() const override { return 0; }
    };

    enum class KeyAction : uint8_t { Down, Up };

    struct KeyEvent : IEvent {
        uint32_t key;
        KeyAction action;
        KeyEvent(uint32_t k, KeyAction a) : key(k), action(a) {}
        EventType Type() const override {
            return action == KeyAction::Down ? EventType::KeyDown : EventType::KeyUp;
        }
        uint64_t Timestamp() const override { return 0; }
    };
}
