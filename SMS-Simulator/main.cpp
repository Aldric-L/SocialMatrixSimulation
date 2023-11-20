//
//  main.cpp
//  Sexual Market Simulation
//
//  Created by SMS&co on 21/03/2023.
//

#include <iostream>
#include "Constants.hpp"
#include "Individual.hpp"
#include "SexualMarket.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, terrible World!\n";
    
    SexualMarket sm;
    sm.initializeLinks();
    std::array<SexualMarket::Link*, GRAPH_SIZE-1> test = sm.getIndividualRelations(sm.getIndividuals()[3]);
    
    Individual* node8 = sm.getIndividuals()[7];
    
    std::vector<SexualMarket::Link> scope8 = node8->getScope();
    node8->computeUtility();
    
    return 0;
}
