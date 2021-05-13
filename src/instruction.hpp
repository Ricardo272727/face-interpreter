#include <iostream>
#include <vector>

using namespace std;

#ifndef INSTRUCTION_CLASS
#define INSTRUCTION_CLASS

enum class InstrType {
    func,
    bucle,
    cond
};

class Instruction {
    // FUNC | COND | BUCLE
    public:
    Instruction(InstrType type){        
        this->instrTrue = NULL;   
        this->instrFalse = NULL;        
        this->nextInstr = NULL;
        this->args = NULL;
        this->type = type;
        this->buildingTrue = true;
        this->buildingFalse = false;
    }

    void setInstrTrue(Instruction * instr){ this->instrTrue = instr; }
    void setInstrFalse(Instruction * instr){ this->instrFalse = instr; }
    void setArgs(vector<string>* args) { this->args = args; }
    void setFunctionType(string functionType) { this->functionType = functionType; }
    void setLimit(int limit){ this->limit = limit; }
    void setCount(int count){ this->count = count; }
    void setComp(string comp){ this->comp = comp; }
    void setNextInstr(Instruction * nextInstr){ this->nextInstr = nextInstr; }
    void setOpBool1(string opBool1){ this->opBool1 = opBool1; }
    void setOpBool2(string opBool2){ this->opBool2 = opBool2; }
    void setBuildingTrue(bool a){ this->buildingTrue = a; }
    void setBuildingFalse(bool a){ this->buildingFalse = a; }
    

    InstrType getType(){ return this->type; }
    string getFunctionType(){ return this->functionType; }
    vector<string> * getArgs(){ return this->args; }
    Instruction * getNextInstr(){ return this->nextInstr; }
    int getLimit(){ return this->limit; }
    int getCount(){ return this->count; }
    string getComp(){ return this->comp; }
    Instruction * getInstrTrue(){ return this->instrTrue; }
    Instruction * getInstrFalse(){ return this->instrFalse; }
    string getOpBool1(){ return this->opBool1; }
    string getOpBool2(){ return this->opBool2; }
    bool getBuildingTrue(){ return this->buildingTrue; }
    bool getBuildingFalse(){ return this->buildingFalse; }

    private:
    //  general attrs
        InstrType type;
        Instruction * nextInstr;
    // condition attrs
        string opBool1;
        string opBool2;
        string comp;
    // loops attrs
        int limit, count;
    // conditions and loops
        Instruction * instrTrue;
        Instruction * instrFalse;
    // function attrs
        string functionType;
        vector<string> * args;
    // build conditional vars
        bool buildingTrue, buildingFalse;
};

#endif