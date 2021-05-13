#include <iostream>
#include "./token_types.hpp"

using namespace std;

#ifndef STATE
#define STATE

class State{
    public:
    State(int number){
      this->number = number;
      this->tokenType = TokenType::ignore;
      this->recoil = 0;
    }
    void setTokenType(TokenType tokenType){
     this->tokenType = tokenType;
    }
    void setRecoil(int recoil){
     this->recoil = recoil; 
    }
    bool isFinal(){
      return this->tokenType != TokenType::ignore;
    }
    TokenType getTokenType(){ return this->tokenType; }
    int getRecoil(){ return this->recoil; }
    private:
    TokenType tokenType;
    int recoil;
    int number;
};

#endif