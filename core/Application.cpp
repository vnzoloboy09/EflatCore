#include "Application.h"
#include "log/Log.h"
#include "events/EventTypes.h"

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using FloatSec = std::chrono::duration<float>;

namespace Eflat {
	Application::Application(std::string_view title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{}
	
	bool Application::Initialize() {
		EF_LOG_INFO("Application init: \"{}\" ({}x{})", m_Title, m_Width, m_Height);

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
			EF_LOG_ERROR("SDL_Init failed: {}", SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(m_Title.c_str(), m_Width, m_Height, SDL_WINDOW_RESIZABLE);
		if (!m_Window) {
			EF_LOG_ERROR("SDL_CreateWindow failed: {}", SDL_GetError());
			return false;
		}

		m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
		if (!m_Renderer) {
			EF_LOG_ERROR("SDL_CreateRenderer failed: {}", SDL_GetError());
			return false;
		}

		m_Running = true;
		return m_Running;
	}
	
	void Application::Shutdown() {
		EF_LOG_INFO("SDL shutdown: \"{}\"", m_Title);
		m_Running = false;

		if (m_Renderer) {
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = nullptr;
		}

		if (m_Window) {
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;
		}

		SDL_Quit();
	}
	
	void Application::PumpEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				m_Dispatcher.Dispatch(EmptyEvent(EventType::AppQuit));
				m_Running = false;
				break;

			case SDL_EVENT_KEY_DOWN:
				m_Dispatcher.Dispatch(KeyEvent(event.key.scancode, KeyAction::Down));
				break;

			case SDL_EVENT_KEY_UP:
				m_Dispatcher.Dispatch(KeyEvent(event.key.scancode, KeyAction::Up));
				break;

			default:
				break;
			}
		}
	}

	int Application::Run() {
		auto previous = Clock::now();
		float accumulator = 0.0f;
		while (m_Running) {
			m_Input.BeginFrame();
			PumpEvents();

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

			m_Input.EndFrame();

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