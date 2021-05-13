#include <iostream>
#include "./token_types.hpp"

using namespace std;

#ifndef TOKEN_CLASS
#define TOKEN_CLASS

class Token {
  public:
    Token(TokenType type, string value, int line, int indexToken){
      this->type = type;
      this->value = value;                
      this->line = line;
      this->indexToken = indexToken;
    }
    void setValue(string value){ this->value = value; }
    TokenType getTokenType(){ return this->type; }
    string getTokenTypeString(){ return getTokenTypeName(this->type); }
    string getValue(){ return this->value; }    
    int getLine(){ return this->line; }
    int getIndexToken(){ return this->indexToken; }
  private:    
    string value;
    TokenType type;
    int line;
    int indexToken;
};

#endif