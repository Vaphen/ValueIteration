#include "State.h"

/**
 * @brief private constructor to create a new state; if you want to instantiate a new instance, see create() method.
 * @param name unique name for the new state
 * @param reward the reward you get if you move to this state
 * @param value the initialization value
 * @param preferredTransitionProbability the probability of the preferred transition [0-1]
 */
State::State(std::string name, double reward, double value, double preferredTransitionProbability) :
    _name(name), _reward(reward), _value(value), _preferredTransitionProbability(preferredTransitionProbability)
{
}

/**
 * @brief Create a new, parameter checked state instance 
 * @param name unique name for the new state
 * @param reward the reward you get if you move to this state
 * @param value the initialization value
 * @param preferredTransitionProbability the probability of the preferred transition [0-1]
 * @return a new state object
 */
State State::create(std::string name, double reward, double value, double preferredTransitionProbability)
{
    if(preferredTransitionProbability < 0 || preferredTransitionProbability > 1) {
        throw std::logic_error("Preferred transition probability must be in range [0,1].");
    }
    return State(name, reward, value, preferredTransitionProbability);
}

/**
 * @brief Add a following state to the transitions
 * @param nextState a shared_ptr that points to the next state object
 */
void State::addNextState(const std::shared_ptr<State> nextState) {
    _transitions.push_back(std::move(nextState));
}

/**
 * @brief calculate the new optimal value for this state. The value will not be updated by this function.
 * @return the new optimal value
 */
double State::calculateNewMaxValue() 
{
    double newMaxValue = std::numeric_limits<double>::lowest();
    for(const std::shared_ptr<State> &trans : _transitions) {
        const double newValue = calculateNewValue(*trans);
        if(newValue > newMaxValue) newMaxValue = newValue;
    }
    return newMaxValue;
}

/**
 * @brief calculate the new value given a specific next state (a specific transition)
 * @param preferredState the state that should be visited next
 * @return the new value of this state given the next state that should be visited
 */
double State::calculateNewValue(const State &preferredState)    
{
    double newValue = 0.f;
    
    for(const std::shared_ptr<State> &trans : _transitions) {
        double probability = 1.f;        
        
        if(*trans == preferredState) {
            probability = _preferredTransitionProbability;
        } else {
            probability = getUnpreferredTransitionProbability();
        }
        double curResult = probability * (trans->getReward() + 0.9 * trans->getValue());
        newValue += curResult;
        //std::cout << probability << " * (" << trans.getNextState()->getReward() << " + 0.9 * " << trans.getNextState()->getValue() << ") = " << curResult << std::endl;
        
    }
    return newValue;
}


/*
 * Overloaded operators 
 */
std::ostream& operator<<(std::ostream &strm, const State &s) {
  return strm << s.getName() << "(Reward: " << s.getReward() << ", Value: " << s.getValue() << ")";
}

bool operator==(const State &state, const State &state2) {
    return state.getName() == state2.getName();
}


/*
 * Getter and Setter
 */
const std::vector<std::shared_ptr<State> >& State::getTransitions() const
{
    return _transitions;
}
void State::setName(const std::string& name)
{
    _name = name;
}
void State::setReward(double reward)
{
    _reward = reward;
}
void State::setValue(double value)
{
    _value = value;
}
const std::string& State::getName() const
{
    return _name;
}
double State::getReward() const
{
    return _reward;
}
double State::getValue() const
{
    return _value;
}
void State::setPreferredTransitionProbability(double preferredTransitionProbability)
{
    _preferredTransitionProbability = preferredTransitionProbability;
}
double State::getPreferredTransitionProbability() const
{
    if(_transitions.size() <= 1) return 1;
    return _preferredTransitionProbability;
}
double State::getUnpreferredTransitionProbability() const
{
    if(_transitions.size() <= 1) return 1;
    return (1-_preferredTransitionProbability) / (_transitions.size() - 1);
}