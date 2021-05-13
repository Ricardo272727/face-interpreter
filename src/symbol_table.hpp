#include <iostream>
#include <list>
#include "./symbol_table_item.hpp"

using namespace std;

#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

class SymbolTable{
    public:
    SymbolTable(){
        this->symbols = new list<SymbolTableItem*>();      
    }
    
    void addItem(Face * face){
        SymbolTableItem * st = new SymbolTableItem();
        st->setFace(face);
        this->symbols->push_back(st);
    }

    void addItem(GlobalVar * gv){
        SymbolTableItem * st = new SymbolTableItem();
        st->setGlobalVar(gv);
        this->symbols->push_back(st);
    }

    void deleteFace(string id){
        list<SymbolTableItem*>::iterator it;
        for(it = this->symbols->begin(); it != this->symbols->end(); ++it){
            if((*it)->getFace() != NULL){
                if((*it)->getFace()->getId().compare(id) == 0){
                    this->symbols->erase(it);
                    break;
                }
            }
        }
    }

    Face * findFace(string id){
        list<SymbolTableItem*>::iterator it;
        Face * temp;
        for (it = this->symbols->begin(); it != this->symbols->end(); ++it){
           if((*it)->getFace() != NULL){
               temp = (*it)->getFace();
               if(temp->getId().compare(id) == 0){
                   return temp;
               }
           }
        }
        return NULL;
    }

    GlobalVar * findGlobalVar(string id){
        list<SymbolTableItem*>::iterator it;
        GlobalVar * temp;
        for (it = this->symbols->begin(); it != this->symbols->end(); ++it){
           if((*it)->getGlobalVar() != NULL){
               temp = (*it)->getGlobalVar();
               if(temp->getId().compare(id) == 0){
                   return temp;
               }
           }
        }
        return NULL;
    }

    private:
    list<SymbolTableItem*> * symbols;
};

#endif