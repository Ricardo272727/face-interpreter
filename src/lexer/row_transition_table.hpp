#include <iostream>
#include "./regex.hpp"
#include "./token_types.hpp"

using namespace std;

#ifndef ROW_TRANSITION_TABLE
#define  ROW_TRANSITION_TABLE

class RowTransitionTable{
  public:
  RowTransitionTable(
    Regex ** regs, 
    int * transitions,
    unsigned int size,
    int recoil = 0,
    TokenType tokenType = TokenType::ignore
  ){
    //cout << "setting token type: " << getTokenTypeName(tokenType) << endl;
    this->regs = regs;
    this->transitions = transitions;
    this->tokenType = tokenType;
    this->size = size;
    this->recoil = recoil;
  }

  int getNextTransition(string str){    
    for(int i = 0; i < this->size; i++){
      if(this->regs[i]->test(str)){
        return this->transitions[i];
      }
    }
    return -1;
  }

  int getRecoil(){ return this->recoil; }
  TokenType getTokenType(){ return this->tokenType; }

  bool isFinalState(){
    return this->tokenType != TokenType::ignore;
  }

  private:
  Regex ** regs;
  int * transitions;
  unsigned int recoil;
  unsigned int size;
  TokenType tokenType;

};

#endif