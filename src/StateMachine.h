#pragma once

#include <vector>
#include "State.h"
#include "Event.h"
#include <memory>

namespace whyte 
{
    class StateMachine : public Subject<Event, EventInfo>
    {
    public:
        ~StateMachine();

        template <typename StateType>
        void register_state(const std::string, std::unique_ptr<StateType>);
        void unregister_state(const std::string);

        void clear_states();
        void change_state(std::string);
        void push_state(std::string);
        void pop_state();
        void handle_events(SDL_Event*);
        void update();

    private:
        using StateMapEntry = std::pair<std::string, std::unique_ptr<State>>;
        std::map<std::string, std::unique_ptr<State>> stateMap_;
        std::vector<std::string> stateStack_;
    };

    template <typename StateType>
    void StateMachine::register_state(const std::string stateId, std::unique_ptr<StateType> state)
    {
        state->register_observer(Event::APPLICATION_EVENT, [this](const EventInfo& info)
        {
            notify(Event::APPLICATION_EVENT, info);
        });

        state->register_observer(Event::STATE_MACHINE_EVENT, [this](const EventInfo& info)
        {
            switch (info.stateMachine.type)
            {
            case StateMachineEvent::CHANGE_STATE:
                change_state(info.stateMachine.stateId);
                break;
            case StateMachineEvent::PUSH_STATE:
                push_state(info.stateMachine.stateId);
                break;
            case StateMachineEvent::POP_STATE:
                pop_state();
                break;
            case StateMachineEvent::CLEAR_STATES:
                clear_states();
                break;
            default:
                break;
            }
        });

        stateMap_.insert(StateMapEntry(stateId, move(state)));
    }
}
