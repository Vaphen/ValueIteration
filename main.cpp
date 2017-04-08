#include <iostream>
#include <memory>
#include <iomanip>

#include "State.h"
#include "StateMachine.h"

/**
 * @brief Print all values from the given machine visually appealing
 * @param machine the state machine that should be printed
 */
void printValues(const StateMachine &machine) 
{
    for(unsigned s = 0; s < 3; s++) {
        for(unsigned t = 0; t < 3; t++) {
            // print space in case of positive number (instead of negative numbers '-'-sign)
            if(machine.getStates().at(s*3+t)->getValue() >= 0.f) std::cout << " ";
            
            if(machine.getStates().at(s*3+t)->getReward() != 0.f) {
                std::cout << std::fixed << std::setprecision(5) << machine.getStates().at(s*3+t)->getReward() << "\t";
            } else {
                std::cout << std::fixed << std::setprecision(5) << machine.getStates().at(s*3+t)->getValue() << "\t";    
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Initialize a given statemachine
 * @param stateMachine the statemachine that should be initialized
 */
void initialize(StateMachine &stateMachine)
{
    stateMachine.setDiscountFactor(0.9);
    
    auto S0 = stateMachine.addState(State::create("S0", 0, 0, 0.7f));
    auto S1 = stateMachine.addState(State::create("S1", 0, 0, 0.7f));
    auto S2 = stateMachine.addState(State::create("S2", 0, 0, 0.7f));
    auto S3 = stateMachine.addState(State::create("S3", 0, 0, 0.7f));
    auto S4 = stateMachine.addState(State::create("S4", -1, 0, 0.7f));
    auto S5 = stateMachine.addState(State::create("S5", 0, 0, 0.7f));
    auto S6 = stateMachine.addState(State::create("S6", 0, 0, 0.7f));
    auto S7 = stateMachine.addState(State::create("S7", 0, 0, 0.7f));
    auto S8 = stateMachine.addState(State::create("S8", 1, 0, 0.7f));
    
    S0->addNextState(S1);
    S0->addNextState(S3);
    
    S1->addNextState(S0);
    S1->addNextState(S2);
    S1->addNextState(S4);

    S2->addNextState(S1);
    S2->addNextState(S5);

    S3->addNextState(S0);
    S3->addNextState(S4);
    S3->addNextState(S6);

    S4->addNextState(S1);
    S4->addNextState(S3);
    S4->addNextState(S5);
    S4->addNextState(S7);
    
    S5->addNextState(S2);
    S5->addNextState(S4);
    S5->addNextState(S8);
    
    S6->addNextState(S3);
    S6->addNextState(S7);
 
    S7->addNextState(S4);
    S7->addNextState(S6);
    S7->addNextState(S8);
    
    S8->addNextState(S5);
    S8->addNextState(S7);
}

int main(int argc, char **argv)
{
    StateMachine stateMachine;
   
    initialize(stateMachine);
    
    std::cout << "Press any key to perform an iteration; press 'q' to quit." << std::endl;
    
    unsigned iterationStep = 0;
    while(std::cin.get() != 'q')
    {
        std::cout << "Iteration: " << iterationStep++ << std::endl;
        printValues(stateMachine);
        stateMachine.doValueIteration();
    }
        
    std::cout << "Bye." << std::endl;
    
	return 0;
}
