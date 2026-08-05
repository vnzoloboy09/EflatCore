#include "EventDispatcher.h"

namespace Eflat {
	EventDispatcher::EventDispatcher() = default;

	IEventDispatcher::ListenerID EventDispatcher::Register(EventType type, Callback callback) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		ListenerID id = m_NextID.fetch_add(1);
		m_Listeners[type].emplace_back(id, std::move(callback));
		return id;
	}

	IEventDispatcher::ListenerID EventDispatcher::RegisterAll(Callback callback) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		ListenerID id = m_NextID.fetch_add(1);
		m_GlobalListeners.emplace_back(id, std::move(callback));
		return id;
	}

	void EventDispatcher::UnRegister(ListenerID id) {
		std::lock_guard<std::mutex> lock(m_Mutex);

		std::erase_if(m_GlobalListeners, [id](const auto& pair) {
			return pair.first == id;
		});

		for (auto& [type, listeners] : m_Listeners) {
			std::erase_if(listeners, [id](const auto& pair) {
				return pair.first == id;
			});
		}
	}

	void EventDispatcher::Dispatch(const IEvent& event) {
		std::vector<Callback> targets;

		{
			std::lock_guard<std::mutex> lock(m_Mutex);

			for (const auto& [id, cb] : m_GlobalListeners) {
				targets.push_back(cb);
			}

			auto it = m_Listeners.find(event.Type());
			if (it != m_Listeners.end()) {
				for (const auto& [id, cb] : it->second) {
					targets.push_back(cb);
				}
			}
		}

		for (const auto& cb : targets) {
			cb(event);
		}
	}
}