#include "core/log/Log.h"
#include "core/events/EventDispatcher.h"

struct TestEvent : public Eflat::IEvent {
	int value;
	explicit TestEvent(int v) : value(v) {}

	Eflat::EventType Type() const override { return Eflat::EventType::KeyDown; }
	uint64_t Timestamp() const override { return 0; }
};

int main()
{
    Eflat::EventDispatcher dispatcher;

	TestEvent evt1(43);
	TestEvent evt2(10);

	dispatcher.Register(Eflat::EventType::KeyDown, [](const Eflat::IEvent& e) {
		const TestEvent& event = static_cast<const TestEvent&>(e);

		EF_LOG_INFO("value: {}", event.value);	
	});

	dispatcher.Dispatch(evt1);
	
	dispatcher.Register(Eflat::EventType::KeyDown, [](const Eflat::IEvent& e) {
		const TestEvent& event = static_cast<const TestEvent&>(e);

		EF_LOG_INFO("The VALUE: {}", event.value);
	});
	
	//dispatcher.Dispatch(evt2);
	dispatcher.DispatchAsync(evt2);
}