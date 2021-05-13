#include <iostream>

using namespace std;
#ifndef GLOBAL_VAR_CLASS
#define GLOBAL_VAR_CLASS

class GlobalVar{
    public:
    GlobalVar(string id, string  value){
        this->id = id;
        this->value = value;
    }

    void setId(string id) { this->id = id; }
    void setValue(string value) { this->value = value; }
    string getId(){ return this->id; }
    string getValue(){ return this->value; }


    private:
        string id, value;
};

#endif