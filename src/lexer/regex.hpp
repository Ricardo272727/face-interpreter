#include <regex>

using namespace std;

#ifndef REGEX_CLASS
#define REGEX_CLASS

class Regex{
  public:
    Regex(string strRegex){
      this->reg = regex(strRegex);
    }
    
    bool test(string test){
      return regex_match(test, this->reg);
    }
  private:
    regex reg;
};

#endif