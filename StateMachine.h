#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "State.h"
#include <memory>
#include <vector>
#include <algorithm>

class StateMachine
{
public:
    StateMachine() = default;
    ~StateMachine() = default;

    // add a new state to our state machine
    std::shared_ptr<State> addState(const State&);

    const std::vector<std::shared_ptr<State> >& getStates() const;
    
    void doValueIteration();

private:
    std::vector<std::shared_ptr<State> > _states;
};

#endif