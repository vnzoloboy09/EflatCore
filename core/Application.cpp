#include "Application.h"
#include "log/Log.h"

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using FloatSec = std::chrono::duration<float>;

namespace Eflat {
	Application::Application(std::string_view title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{}
	
	bool Application::Initialize() {
		EF_LOG_INFO("INIT");
		return 1;
	}
	
	void Application::Shutdown() {
		EF_LOG_WARN("SHUTDOWN");
	}
	
	int Application::Run() {
		auto previous = Clock::now();
		float accumulator = 0.0f;
		while (m_Running) {
			auto now = Clock::now();
			float elapsed = std::chrono::duration_cast<FloatSec>(now - previous).count();
			previous = now;

			if (elapsed > m_MaxFrameTime)
				elapsed = m_MaxFrameTime;

			accumulator += elapsed;

			while (accumulator >= m_FixedDt) {
				OnFixedUpdate(m_FixedDt);
				accumulator -= m_FixedDt;
			}

			float alpha = accumulator / m_FixedDt;
			OnRender(alpha);
		}

		return 0;
	}

	void Application::OnFixedUpdate(float dt) {

	}

	void Application::OnRender(float alpha) {

	}
}