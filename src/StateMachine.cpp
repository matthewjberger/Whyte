#include "StateMachine.h"

using namespace std;
using namespace whyte;

StateMachine::~StateMachine()
{
    clear_states();
}

void StateMachine::unregister_state(const std::string stateId)
{
    stateMap_.erase(stateId);
}

void StateMachine::change_state(std::string state)
{
    clear_states();
    push_state(state);
}

void StateMachine::clear_states()
{
    while (!stateStack_.empty())
    {
        pop_state();
    }
}

void StateMachine::push_state(std::string state)
{
    if (!stateStack_.empty())
    {
        stateMap_[stateStack_.back()]->pause();
    }

    stateStack_.push_back(state);
    stateMap_[stateStack_.back()]->start();
}

void StateMachine::pop_state()
{
    stateMap_[stateStack_.back()]->stop();
    stateStack_.pop_back();

    if (!stateMap_.empty())
    {
        stateMap_[stateStack_.back()]->resume();
    }
}

void StateMachine::handle_events(SDL_Event* event)
{
    if (stateStack_.empty()) return;
    stateMap_[stateStack_.back()]->handle_events(event);
}

void StateMachine::update()
{
    if (stateStack_.empty()) return;
    stateMap_[stateStack_.back()]->update();
}
