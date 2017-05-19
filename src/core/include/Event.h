#pragma once

namespace whyte
{
    // TODO: Make Subject take std::pair<E,I>
    // EventType, EventInfo

    // TODO: Find a way to separate out events 
    // to their specific domain.

    /* Event Definitions */
    enum class ApplicationEvent
    {
        QUIT
    };

    enum class StateMachineEvent
    {
        CHANGE_STATE,
        PUSH_STATE,
        POP_STATE,
        CLEAR_STATES
    };

    enum class Event
    {
        APPLICATION_EVENT,
        STATE_MACHINE_EVENT
    };

    /* Event information */
    struct ApplicationEventInfo
    {
        ApplicationEvent type;
    };

    class State;
    struct StateMachineEventInfo
    {
        StateMachineEvent type;
        State* state;
    };

    struct EventInfo
    {
        Event type;
        ApplicationEventInfo app;
        StateMachineEventInfo stateMachine;
    };
}
