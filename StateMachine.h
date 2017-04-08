#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "State.h"
#include <map>
#include <vector>
#include <algorithm>

typedef std::pair<std::shared_ptr<State> , std::shared_ptr<State>> StateActionPair;

class StateMachine
{
public:
    StateMachine() = default;
    ~StateMachine() = default;

    // add a new state to our state machine
    std::shared_ptr<State> addState(const State&);
    
    void doValueIteration();
    
    // q and v functions are calculated using doValueIteration() function
    std::map<StateActionPair, double> getQFunction() const;
    std::map<std::shared_ptr<State>, double> getVFunction() const;
    
    const std::vector<std::shared_ptr<State> >& getStates() const;

    double getDiscountFactor() const;
    void setDiscountFactor(double);

private:

    std::vector<std::shared_ptr<State> > _states;
    std::map<StateActionPair, double> _qFunction;
    std::map<std::shared_ptr<State>, double> _vFunction;
    
    double _discountFactor = 0.9f;
    
    // calculate the Q function of the given state
    void calculateQFunction();
    
    // caluclate the value function of the given state using _qFunction
    void calculateVFunction();
    
    double calculateNewValue(const State &curState, const State &nextState);
};

#endif