#include "StateMachine.h"

using namespace std;
using namespace whyte;

StateMachine::StateMachine(State* initialState)
{
    if(!initialState)
    {
        // TODO: Log this error message
        string errorMessage = "ERROR: StateMachine was created without an initial state.";
        throw std::runtime_error(errorMessage);
    }
    change_state(initialState);
}

StateMachine::~StateMachine()
{
    clear_states();
}

void StateMachine::change_state(State* state)
{
    clear_states();
    push_state(move(state));
}

void StateMachine::clear_states()
{
    while (!states_.empty())
    {
        states_.back()->stop();
        states_.pop_back();
    }
}

void StateMachine::push_state(State* state)
{
    if (!states_.empty())
    {
        states_.back()->pause();
    }

    state->register_observer(Event::APPLICATION_EVENT, [this](const EventInfo& info)
    { 
        notify(Event::APPLICATION_EVENT, info);
    });

    state->register_observer(Event::STATE_MACHINE_EVENT, [this](const EventInfo& info)
    { 
        switch(info.stateMachine.type)
        {
        case StateMachineEvent::CHANGE_STATE:
            change_state(info.stateMachine.state);
            break;
        case StateMachineEvent::PUSH_STATE: 
            push_state(info.stateMachine.state);
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

    states_.push_back(state);
    states_.back()->start();
}

void StateMachine::pop_state()
{
    states_.back()->stop();
    states_.pop_back();

    if (states_.back())
    {
        states_.back()->resume();
    }
}

void StateMachine::handle_events(SDL_Event* event)
{
    states_.back()->handle_events(event);
}

void StateMachine::update()
{
    states_.back()->update();
}
