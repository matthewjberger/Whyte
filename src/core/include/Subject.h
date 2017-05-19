#pragma once

#include <functional>
#include <map>
#include <vector>

namespace whyte
{
    template <typename Event, typename EventInfo>
    class Subject
    {
    public:
        Subject() = default;
        virtual ~Subject(){}

        template <typename Observer>
        void register_observer(const Event& event, Observer&& observer)
        {
            observers_[event].push_back(std::forward<Observer>(observer));
        }

        void notify(const Event& event, const EventInfo& info) const
        {
            for (const auto& observe : observers_.at(event)) observe(info);
        }

        // Prevent copy, move, and assignment
        Subject(const Subject&) = delete;
        Subject(Subject&&) = delete;
        Subject& operator=(const Subject&) = delete;

    private:
        using ObserverAction = std::function<void(const EventInfo&)>;
        std::map<Event, std::vector<ObserverAction>> observers_;
    };
}
