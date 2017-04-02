#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <limits>

class State
{
public:
    State() = delete;
    ~State() = default;
    State(const State&) = default;
    
    
    // use this method to get a new instance
    static State create(std::string, double, double, double);

    void addNextState(const std::shared_ptr<State>);
    
    // perform one value iteration step on this state
    double calculateNewMaxValue();
    
    
    /*
     * Getter and Setter 
     */
    const std::vector<std::shared_ptr<State> >& getTransitions() const;
    
    void setName(const std::string& name);
    const std::string& getName() const;
    
    void setReward(double reward);
    double getReward() const;
    
    void setValue(double value);
    double getValue() const;
    
    void setPreferredTransitionProbability(double preferredTransitionProbability);
    double getPreferredTransitionProbability() const;
    
    double getUnpreferredTransitionProbability() const;

private:
    // enable simple c++ standard output
    friend std::ostream& operator<<(std::ostream&, const State&);
    // enable comparison between state objects
    friend bool operator==(const State &state, const State &state2);
    
    // members
    std::string _name;
    double _reward;
    double _value;
    double _preferredTransitionProbability;
    std::vector<std::shared_ptr<State> > _transitions;
    
    State(std::string, double, double, double);
   
    double calculateNewValue(const State &nextState);
};

#endif