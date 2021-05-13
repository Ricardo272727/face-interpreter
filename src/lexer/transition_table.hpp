#include <iostream>
#include "./row_transition_table.hpp"
#include "./state.hpp"

using namespace std;

#ifndef TRANSITION_TABLE
#define TRANSITION_TABLE

class TransitionTable {
  public:
  TransitionTable(RowTransitionTable ** rows, unsigned int size){
    this->rows = rows;
    this->size = size;
    this->state = 0;
  }
  
  State * nextState(string str){
    //cout << " rows null " << (this->rows == NULL ? "si" : "no") << endl;
    //cout << "state" << state << endl;
    int newState = this->rows[state]->getNextTransition(str);
    //cout << "Estamos en: " << state << " pasamos a: " << newState << " con " << str << endl;
    if(newState >= 0){
      if(this->rows[newState]->isFinalState()){                
          State * finalState = new State(newState);
          finalState->setRecoil(this->rows[newState]->getRecoil());
          finalState->setTokenType(this->rows[newState]->getTokenType());          
          return finalState;
      } else {
        this->state = newState;
      }
    } else {
      return NULL;
    }
    return new State(newState);
  }

  void resetState(){
    this->state = 0;
  }
  
  int getState(){ return this->state; }

  private:
  RowTransitionTable ** rows;
  int state;
  unsigned int size;  
};

#endif