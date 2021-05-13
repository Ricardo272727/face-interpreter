#include <iostream>
#include "./face.hpp"
#include "./global_var.hpp"

using namespace std;

#ifndef SYMBOL_TABLE_ITEM
#define SYMBOL_TABLE_ITEM

enum class SymbolType {
    face,
    globalVar    
};

class SymbolTableItem {
    public:
    SymbolTableItem(){
        this->face = NULL;
        this->globalVar = NULL;
    }

    void setFace(Face * face){
        this->face = face;
    }
    
    void setGlobalVar(GlobalVar * globalVar){
        this->globalVar = globalVar;
    }

    Face * getFace(){ return this->face; }
    GlobalVar * getGlobalVar(){ return this->globalVar; }

    private:
        SymbolType symbolType;
        GlobalVar * globalVar;
        Face * face;
};

#endif