//
//  SexualMarket.cpp
//  Sexual Market Simulation
//
//  Created by SMS Associates on 21/03/2023.
//
#include "SexualMarket.hpp"
#include "Individual.hpp"

SexualMarket::SexualMarket(){
    SexualMarket::EdgeSaveTrackerType::default_parameters_name = {{ "round", "vertex1", "vertex2", "old_weight", "new_weight", "accepted" }};
    SexualMarket::UtilitySaveTrackerType::default_parameters_name = {{ "round", "agentid", "utility" }};
    
    for (int indiv(0); indiv<GRAPH_SIZE; indiv++){
        individuals[indiv] = new Individual(*this, indiv);
    }
    
    int link_i(0);
    for (int indiv(0); indiv<GRAPH_SIZE; indiv++){
        for (int indiv_t(0); indiv_t<indiv; indiv_t++){
            Link l;
            l.first = individuals[indiv];
            l.second = individuals[indiv_t];
            l.weight = 0.f;
            SexualMarket::links[link_i] = l;
            link_i++;
        }
    }
}

SexualMarket::~SexualMarket(){
    for (int indiv(0); indiv<GRAPH_SIZE; indiv++){
        delete individuals[indiv];
    }
}

void SexualMarket::initializeLinks(){
    // Any link that is to be initialized should be saved
    SexualMarket::EdgeSaveTrackerType* save;
    int link_i(0);
    for (int indiv(0); indiv<GRAPH_SIZE; indiv++){
        for (int indiv_t(0); indiv_t<indiv; indiv_t++){
            if (indiv == indiv_t+1)
                SexualMarket::links[link_i].weight = 0.1;
            else if (indiv == indiv_t+7)
                SexualMarket::links[link_i].weight = 0.5;
            
            save = new SexualMarket::EdgeSaveTrackerType(SexualMarket::currentRound, SexualMarket::links[link_i].first->agentid, SexualMarket::links[link_i].second->agentid, 0, SexualMarket::links[link_i].weight, true);
            edgeTrackersManager.addSave(save);
            link_i++;
        }
    }
    SexualMarket::currentRound = 1;
}

std::array<SexualMarket::Link*, GRAPH_SIZE-1> SexualMarket::getIndividualRelations(Individual* indiv) {
    std::array<Link*, GRAPH_SIZE-1> linksForIndividual;
    unsigned short int incr = 0;
    for (int i(0); i < LINKS_NB; i++){
        if (SexualMarket::links[i].first == indiv || SexualMarket::links[i].second == indiv){
            linksForIndividual[incr] = &SexualMarket::links[i];
            incr++;
        }
    }
    if (incr != GRAPH_SIZE-1)
        throw std::invalid_argument("Something went really wrong");
    return linksForIndividual;
}

std::array<Individual*, GRAPH_SIZE> SexualMarket::getIndividuals() {
    return SexualMarket::individuals;
}

std::vector<SexualMarket::Link> SexualMarket::getIndividualScope(Individual* indiv) {
    std::vector<SexualMarket::Link> scope;
    std::array<Link*, GRAPH_SIZE-1> linksofIndividual = SexualMarket::getIndividualRelations(indiv);
    for (int level0(0); level0 < GRAPH_SIZE-1; level0++){
        if (linksofIndividual[level0]->weight > 0){
            Individual* target0 = nullptr;
            Individual* target1 = nullptr;
            
            if (linksofIndividual[level0]->first == indiv)
                target0 = linksofIndividual[level0]->second;
            else
                target0 = linksofIndividual[level0]->first;
            
            std::array<Link*, GRAPH_SIZE-1> linksofTarget = SexualMarket::getIndividualRelations(target0);
            for (int level1(0); level1 < GRAPH_SIZE-1; level1++){
                if (linksofTarget[level1]->weight > 0){
                    if (linksofTarget[level1]->first == target0)
                        target1 = linksofTarget[level1]->second;
                    else
                        target1 = linksofTarget[level1]->first;
                    
                    if (target0 != target1 && target1 != indiv && target0 != indiv){
                        Link l;
                        l.first = indiv;
                        l.second = target1;
                        l.weight = linksofTarget[level1]->weight * linksofIndividual[level0]->weight;
                        bool redundant = false;
                        for (int icheck(0); icheck < scope.size(); icheck++){
                            if ((scope[icheck].first == l.first && scope[icheck].second == l.second)
                                || (scope[icheck].first == l.second && scope[icheck].second == l.first))
                                redundant = true;
                        }
                        if (!redundant)
                            scope.push_back(l);
                    }
                }
            }
            scope.push_back(*linksofIndividual[level0]);
            
        }
    }
    return scope;
}

// Actually, I think this method should not exists : be optimized, use pointers.
void SexualMarket::editLink(Individual* indiv1, Individual* indiv2, float newWeight, bool accepted) {
    if (indiv1 == indiv2 || indiv1 == nullptr || indiv2 == nullptr)
        throw std::invalid_argument("Attempting to edit a non-consistent link");
}

void SexualMarket::editLink(SexualMarket::Link* link, float newWeight, bool accepted) {
    if (link == nullptr)
        throw std::invalid_argument("Attempting to edit a non-consistent link");
    
    SexualMarket::EdgeSaveTrackerType save(SexualMarket::currentRound, link->first->agentid, link->second->agentid, link->weight, newWeight, accepted);
    edgeTrackersManager.addSave(save);
    if (accepted)
        link->weight = newWeight;
}
