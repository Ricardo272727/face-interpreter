
#ifndef TOKEN_TYPES
#define TOKEN_TYPES

enum class TokenType : unsigned char {    
  reservedWord,
  sign,
  id,
  number,
  separator,
  ignore,
  predefinedFunc,
  state,
  globalVar,
  eyeSide
};

std::string getTokenTypeName(TokenType tokenType){
  switch(tokenType){
    case TokenType::reservedWord:
      return "reservedWord";
    case TokenType::sign:
      return "sign";
    case TokenType::id:
      return "id";
    case TokenType::number:
      return "number";
    case TokenType::separator:
      return "separator";
    case TokenType::ignore:
      return "ignore";    
    default:
      return "Unknown token type";
  }
}

#endif