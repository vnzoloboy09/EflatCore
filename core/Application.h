#pragma once

#include "IApplication.h"
#include "events/EventDispatcher.h"

#include <SDL3/SDL.h>

#include <string>

namespace Eflat {
	class Application : public IApplication {
	public:
		Application(std::string_view title, int width, int height);
		~Application() override = default;

		bool Initialize() override;
		void Shutdown() override;
		int Run() override;
		IEventDispatcher& GetEventDispatcher() override { return m_Dispatcher; }

	protected:
		void OnFixedUpdate(float dt) override;
		void OnRender(float alpha) override;

	private:
		void PumpEvents();

	private:
		EventDispatcher m_Dispatcher;
		std::string m_Title;
		int m_Width, m_Height;
		bool m_Running = false;
		float m_FixedDt = 1.0f / 60.0f;
		float m_MaxFrameTime = 1.0f / 20.0f;

		SDL_Window* m_Window = nullptr;
		SDL_Renderer* m_Renderer = nullptr;
	};
}
