#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include "./instruction.hpp"
#include "./symbol_table.hpp"
#include "./face.hpp"
#include "./global_var.hpp"

using namespace std;

unsigned int microsecond = 1000000;

#ifndef INTERPRETER
#define INTERPRETER

class Interpreter{
    public:    
    Interpreter(SymbolTable * st){
        this->st = st;
        this->pauseTime = 2;
        this->estadoOjoIzq = new GlobalVar("estadoOjoIzq", "abierto");
        this->estadoOjoDer = new GlobalVar("estadoOjoDer", "abierto");
        this->estadoBoca = new GlobalVar("estadoBoca", "cerrado");
        this->st->addItem(this->estadoOjoIzq);
        this->st->addItem(this->estadoOjoDer);
        this->st->addItem(this->estadoBoca);
    }

    void execute(Instruction * instr){
        if(instr == NULL) return;
        InstrType type = instr->getType();
        if(type == InstrType::func){
            this->execFunc(instr);
        } else if(type == InstrType::bucle){
            this->execBucle(instr);
        } else if(type == InstrType::cond) {
            this->execCond(instr);
        } else {
            this->showError("Instrucción desconocida");
        }
    }

    void execFunc(Instruction * instr){
        string functionType = instr->getFunctionType();
        vector<string> * args = instr->getArgs();        
        if(functionType.compare("creaCara") == 0){
            string id = args->at(0);
            int posX = stoi(args->at(1));
            int posY = stoi(args->at(2));
            Face * faceExists = this->st->findFace(id);
            if(faceExists != NULL){
                this->showError("Identificador previamente declarado: " + id);
            }
            Face * f = new Face(id, posX, posY, "sonriente", "abierto", "abierto");
            this->st->addItem(f);
            f->print();
        } else if(functionType.compare("borraCara") == 0){
            string id = args->at(0);
            Face * f = this->st->findFace(id);
            if(f == NULL){
                this->showError("Error al eliminar cara: " + id + " no existe");
            } else {
                this->st->deleteFace(id);
            }
        } else if(functionType.compare("cambiarNombre") == 0){
            string id = args->at(0);
            string newId = args->at(1);
            Face * f = this->st->findFace(id);
            if(f == NULL){
                this->showError("Identificador previamente no declarado: " + id);
            } else {
                f->setId(newId);
            }
            f->print();
        } else if(functionType.compare("cambiaEstadoOjos") == 0){
            string id = args->at(0);
            string edoOjos = args->at(1);
            Face * f = this->st->findFace(id);
            this->estadoOjoIzq->setValue(edoOjos);
            this->estadoOjoDer->setValue(edoOjos);             
            if(f == NULL){
                this->showError("Identificador previamente no declarado: " + id);
            } else {
                f->setEdoOjos(edoOjos);
                f->print();
            }
        } else if(functionType.compare("cambiaEstadoOjo") == 0){
            string id = args->at(0);
            string ladoOjo = args->at(1);
            string edoOjo = args->at(2);
            Face * f = this->st->findFace(id);            
            if(f == NULL){
                this->showError("Identificador previamente no declarado: " + id);
            } else {
                if(ladoOjo.compare("izquierdo") == 0){
                    this->estadoOjoIzq->setValue(edoOjo);
                    f->setEdoOjoIzq(edoOjo);
                } else if(ladoOjo.compare("derecho") == 0){
                    this->estadoOjoDer->setValue(edoOjo);
                    f->setEdoOjoDer(edoOjo);
                }
                f->print();
            }
        } else if(functionType.compare("cambiaEstadoBoca") == 0){
            string id = args->at(0);
            string edoBoca = args->at(1);
            Face * f = this->st->findFace(id);
            if(f == NULL){
                this->showError("Identificador previamente no declarado: " + id);
            } else {
                this->estadoBoca->setValue(edoBoca);
                f->setEdoBoca(edoBoca);
                f->print();
            }
        }
        this->pause();
        this->execute(instr->getNextInstr());
    }

    void execBucle(Instruction * instr){
        for(int i = 0; i < instr->getLimit(); i++){
            this->execute(instr->getInstrTrue());
            instr->setCount(i);
        }
        this->execute(instr->getNextInstr());
    }

    void execCond(Instruction * instr){
        string opBool1 = this->getOpBoolValue(instr->getOpBool1());
        string opBool2 = this->getOpBoolValue(instr->getOpBool2());
        string comp = instr->getComp();
        //cout << "Exec cond" << opBool1 << comp << opBool2 << endl;
        if(
            (comp.compare("=") == 0 && opBool2.compare(opBool1) == 0) ||
            (comp.compare("<>") == 0 && opBool2.compare(opBool1) != 0)
        ) {
            //cout << "In cond" << opBool1 << comp << opBool2 << endl;
            this->execute(instr->getInstrTrue());
        } else if(instr->getInstrFalse() != NULL){
            //cout << "In cond else" << opBool1 << comp << opBool2 << endl;
            this->execute(instr->getInstrFalse());
        }
        
        this->execute(instr->getNextInstr());
    }

    string getOpBoolValue(string opBool){
        if(opBool.compare("estadoOjoIzq") == 0){
            return this->estadoOjoIzq->getValue();
        } else if(opBool.compare("estadoOjoDer") == 0){
            return this->estadoOjoDer->getValue();
        } else if(opBool.compare("estadoBoca") == 0){
            return this->estadoBoca->getValue();
        }
        return opBool;
    }

    void showError(string message){
        cout << "\n ==================================================== " << endl;
        cout << "\n Error de interpretación ... " << endl;
        cout << "\n " << message << endl;
        cout << "\n ==================================================== " << endl;
        exit(-1);
    }

    void pause(){
        usleep(this->pauseTime * microsecond);
    }

    string getNSpaces(int n){
        string spaces = "";
        for(int i = 0; i < n; i++){
            spaces += " ";
        }
        return spaces;
    }

    private:
    SymbolTable * st;    
    int pauseTime;
    GlobalVar * estadoOjoIzq, * estadoOjoDer, * estadoBoca;
};

#endif