#pragma once

#include "events/IEventDispatcher.h"

namespace Eflat {
	class IApplication {
	public:
		virtual ~IApplication() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual int Run() = 0;

		virtual IEventDispatcher EventDispatcher() = 0;
	};
}
