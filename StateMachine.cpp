#include "StateMachine.h"

/**
 * @brief add a new state to our statemachine
 * @param state
 * @return a new shared_ptr pointing to our new state
 */
std::shared_ptr<State> StateMachine::addState(const State &state)
{
    _states.push_back(std::make_shared<State>(state));
    return _states.back();
}

/**
 * @brief return all states that are currently existant
 * @return a vector of shared_ptrs pointing to states
 */
const std::vector<std::shared_ptr<State> >& StateMachine::getStates() const
{
    return _states;
}

/**
 * @brief Perform a value iteration step for each state
 */
void StateMachine::doValueIteration()
{
      // save all new values in this vector
    std::vector<double> newValues;
    
    for(auto state : _states) {
        if(state->getReward() != 0) {
            // if the reward is not zero, we don't update the value
            newValues.push_back(state->getValue());
        }else {
            // else we perform the next iteration step and calculate the new max value
            newValues.push_back(state->calculateNewMaxValue());
        }
    }
    
    // update all values
    for(unsigned j = 0; j < newValues.size(); j++) {
       _states.at(j)->setValue(newValues.at(j));
    }
}