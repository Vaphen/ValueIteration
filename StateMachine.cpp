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
    
    calculateQFunction();
    calculateVFunction();

    // update all state values
    using pairtype = decltype(_vFunction)::value_type;
    for(const pairtype &vPair : _vFunction) {
        if(vPair.first->getReward() == 0) {
            vPair.first->setValue(vPair.second);
        }
    }
}

/**
 * @brief calculate the new value function for all states
 */
void StateMachine::calculateQFunction() 
{
    for(const std::shared_ptr<State> &state : _states) {
        for(const std::shared_ptr<State> &trans : state->getTransitions()) {
            _qFunction[std::make_pair(state, trans)] = calculateNewValue(state, trans);
        }
    }
}

/**
 * @brief calculate the new value function for all states using max(a)[_qFunction[s, a]]
 */
void StateMachine::calculateVFunction() 
{
    for(const std::shared_ptr<State> &state : _states) {
        double maxValue = 0.f;
        for(const std::shared_ptr<State> &trans : state->getTransitions()) {
            if(_qFunction[std::make_pair(state, trans)] > maxValue) {
                maxValue = _qFunction[std::make_pair(state, trans)];
            }
        }
        _vFunction[state] = maxValue;
    }
}


/**
 * @brief calculate the new value given a specific next state (a specific transition)
 * @param curState the current state
 * @param nextState the state that should be visited next
 * @return the new value of this state given the next state that should be visited
 */
double StateMachine::calculateNewValue(const std::shared_ptr<State> &curState, const std::shared_ptr<State> &nextState)    
{
    // check if nextState is successor of curState
    if(std::find(curState->getTransitions().begin(), curState->getTransitions().end(), nextState) == curState->getTransitions().end()) {
        throw std::invalid_argument("Given nextState is no successor of curState.");
    }
    
    double newValue = 0.f;
    
    for(const std::shared_ptr<State> &trans : curState->getTransitions()) {
        double probability = 1.f;        
        
        if(trans == nextState) {
            probability = curState->getPreferredTransitionProbability();
        } else {
            probability = curState->getUnpreferredTransitionProbability();
        }
        double curResult = probability * (trans->getReward() + 0.9 * trans->getValue());
        newValue += curResult;
    }
    return newValue;
}

/*
 * Getter and setter
 */

std::map<StateActionPair, double> StateMachine::getQFunction() const
{
    return _qFunction;
}

std::map<std::shared_ptr<State>, double> StateMachine::getVFunction() const
{
    return _vFunction;
}

double StateMachine::getDiscountFactor() const
{
    return _discountFactor;
}

void StateMachine::setDiscountFactor(double discount) 
{
    if(discount > 1 || discount < 0) {
        throw std::range_error("Discount must be in range [0..1]");
    }
    _discountFactor = discount;
}