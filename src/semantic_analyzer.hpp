#include <iostream>
#include <vector>
#include <stack>
#include "./symbol_table.hpp"
#include "./instruction.hpp"

using namespace std;

#ifndef SEMANTIC_A_CLASS
#define SEMANTIC_A_CLASS

class SemanticAnalyzer{
    public:
    SemanticAnalyzer(){
        this->firstInstr = NULL;
        this->currentInstr = NULL;
        this->stackInstr = new stack<Instruction*>();
    }

    void condInstr(string opBool1, string comp, string opBool2){
        Instruction * instr = new Instruction(InstrType::cond);
        instr->setOpBool1(opBool1);
        instr->setOpBool2(opBool2);
        instr->setComp(comp);
        this->addInstr(instr);
    }

    void finCondInstr(){
        if(this->currentInstr->getType() == InstrType::cond){
            this->currentInstr->setBuildingTrue(false);
            this->currentInstr->setBuildingFalse(false);
            if(!this->stackInstr->empty()){
                this->currentInstr = this->stackInstr->top();
                this->stackInstr->pop();
            }
        }
    }

    void condPrimaSinoInstr(){
        if(this->currentInstr->getType() == InstrType::cond){
            this->currentInstr->setBuildingFalse(true);
            this->currentInstr->setBuildingTrue(false);
        }
    }

    void bucleInstr(string n){
        Instruction * instr = new Instruction(InstrType::bucle);                        
        instr->setLimit(stoi(n));
        instr->setCount(0);
        this->addInstr(instr);        
    }

    void finBucleInstr(){
        if(this->currentInstr->getType() == InstrType::bucle){
            this->currentInstr->setBuildingTrue(false);
            if(!this->stackInstr->empty()){
                this->currentInstr = this->stackInstr->top();
                this->stackInstr->pop();
            }
        }
    }

    void creaCaraInstr(string id, string posX, string posY){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);
        args->push_back(posX);
        args->push_back(posY);
        instr->setFunctionType("creaCara");
        instr->setArgs(args);
        this->addInstr(instr); 
    }

    void borraCaraInstr(string id){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);
        instr->setFunctionType("borraCara");
        instr->setArgs(args);
        this->addInstr(instr);
    }

    void cambiarNombreInstr(string id, string newId){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);
        args->push_back(newId);
        instr->setFunctionType("cambiarNombre");
        instr->setArgs(args);
        this->addInstr(instr);
    }

    void cambiaEstadoBocaInstr(string id, string edoBoca){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);
        args->push_back(edoBoca);
        instr->setFunctionType("cambiaEstadoBoca");
        instr->setArgs(args);
        this->addInstr(instr);
    }

    void cambiaEstadoOjoInstr(string id, string ladoOjo, string edoOjo){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);
        args->push_back(ladoOjo);
        args->push_back(edoOjo);
        instr->setFunctionType("cambiaEstadoOjo");
        instr->setArgs(args);
        this->addInstr(instr);
    }

    void cambiaEstadoOjosInstr(string id, string edoOjos){
        Instruction * instr = new Instruction(InstrType::func);
        vector<string> * args = new vector<string>();
        args->push_back(id);        
        args->push_back(edoOjos);
        instr->setFunctionType("cambiaEstadoOjos");
        instr->setArgs(args);
        this->addInstr(instr);       
    }    

    void addInstr(Instruction * instr){        
        if(this->firstInstr == NULL){
            this->firstInstr = instr;
            this->currentInstr = instr;
        } else if(
            this->currentInstr->getType() == InstrType::cond ||
            this->currentInstr->getType() == InstrType::bucle
        ) {
            if(
                instr->getType() == InstrType::cond || 
                instr->getType() == InstrType::bucle
            ) {
                if(
                    this->currentInstr->getBuildingTrue() ||
                    this->currentInstr->getBuildingFalse()
                ){
                    this->stackInstr->push(this->currentInstr);
                }
                this->addInstrToInstr(this->currentInstr, instr);
                instr->setBuildingTrue(true);
                this->currentInstr = instr;
            } else {
                this->addInstrToInstr(this->currentInstr, instr);
            }
            /*
            if(this->currentInstr->getBuildingTrue()){
                if(this->currentInstr->getInstrTrue() == NULL){
                    this->currentInstr->setInstrTrue(instr);
                } else {
                    curr = this->currentInstr->getInstrTrue();
                    while(curr->getNextInstr() != NULL){
                        curr = curr->getNextInstr();
                    }
                    curr->setNextInstr(instr);
                }
            } else if(this->currentInstr->getBuildingFalse()) {
                if(this->currentInstr->getInstrFalse() == NULL){
                    this->currentInstr->setInstrFalse(instr);
                } else {
                    curr = this->currentInstr->getInstrFalse();
                    while(curr->getNextInstr() != NULL){
                        curr = curr->getNextInstr();
                    }
                    curr->setNextInstr(instr);
                }
            } else {
                this->currentInstr->setNextInstr(instr);
                this->currentInstr = instr;               
            }*/
        } else {
            this->currentInstr->setNextInstr(instr);
            this->currentInstr = instr;
        }
    }

    Instruction * getFirstInstr(){ return this->firstInstr; }

    void addInstrToInstr(Instruction * parentInstr, Instruction * instr){
        Instruction * head = NULL;
        bool buildTrue = parentInstr->getBuildingTrue();
        bool buildFalse = parentInstr->getBuildingFalse();
        if(buildTrue){
            head = parentInstr->getInstrTrue();
            if(head == NULL){
                parentInstr->setInstrTrue(instr);
            } else {
                while(head->getNextInstr() != NULL){
                    head = head->getNextInstr();
                }   
                head->setNextInstr(instr);
            }
        } else if(buildFalse){
            head = parentInstr->getInstrFalse();
            if(head == NULL){
                parentInstr->setInstrFalse(instr);
            } else {
                while(head->getNextInstr() != NULL){
                    head = head->getNextInstr();
                }   
                head->setNextInstr(instr);
            }
        } else {
            parentInstr->setNextInstr(instr);
            this->currentInstr = instr;
        }
    }

    void printInstructions(){
        Instruction * current = firstInstr;
        while(current != NULL){
            cout << "Instr type: " << current->getFunctionType() << this->getInstrTypeStr(current->getType()) << endl;
            current = current->getNextInstr();
        }
    }

    string getInstrTypeStr(InstrType type){
        if(type == InstrType::func){
            return "func";
        } else if(InstrType::bucle == type){
            return "bucle";
        } else if(InstrType::cond == type){
            return "cond";
        }
        return "unknown";
    }

    private:
    stack<Instruction*> * stackInstr;
    Instruction * firstInstr;
    Instruction * currentInstr;
};

#endif