#pragma once

#include "IEventDispatcher.h"
#include "types.h"
#include <mutex>

namespace Eflat {
	class EventDispatcher : public IEventDispatcher {
	public:
		EventDispatcher();
		~EventDispatcher() = default;

		ListenerID Register(EventType type, Callback callback) override;
		ListenerID RegisterAll(Callback callback) override;
		void UnRegister(ListenerID id) override;
		void Dispatch(const IEvent& evnet) override;
		void DispatchAsync(const IEvent& event) override;

	private:
		std::mutex m_Mutex;
		std::atomic<ListenerID> m_NextID = 1;
		std::unordered_map<EventType, std::vector<std::pair<ListenerID, Callback>>> m_Listeners;
		std::vector<std::pair<ListenerID, Callback>> m_GlobalListeners;
	};
}