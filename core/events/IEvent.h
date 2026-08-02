#pragma once
#include "EventType.h"

namespace Eflat
{
	class IEvent {
	public:
		virtual ~IEvent() = default;
		virtual EventType Type() const = 0;
		virtual uint64_t Timestamp() const = 0;
	};
}