#pragma once

#include "events/IEventDispatcher.h"

namespace Eflat {
	class IApplication {
	public:
		virtual ~IApplication() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual int Run() = 0;

		virtual IEventDispatcher& GetEventDispatcher() = 0;

		virtual void OnFixedUpdate(float dt) = 0;
		virtual void OnRender(float alpha) = 0;
	};
}
