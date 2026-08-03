#pragma once
#include <functional>
#include "IEvent.h"

namespace Eflat
{
	class IEventDispatcher {
	public:
		using Callback = std::function<void(const IEvent&)>;
		using ListenerID = uint64_t;

		virtual ListenerID Register(EventType type, Callback) = 0;
		virtual ListenerID RegisterAll(Callback) = 0;
		virtual void UnRegister(ListenerID) = 0;
		virtual void Dispatch(const IEvent&) = 0;
		virtual ~IEventDispatcher() = default;
	};	
}
