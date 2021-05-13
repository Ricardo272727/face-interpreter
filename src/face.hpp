#include <iostream>

using namespace std;

#ifndef FACE_CLASS 
#define FACE_CLASS 

class Face{
    public:
    Face(string id, int posX, int posY, string edoBoca, string edoOjoIzq, string edoOjoDer){
        this->id = id;
        this->posX = posX;
        this->posY = posY;
        this->edoBoca = edoBoca;
        this->edoOjoIzq = edoOjoIzq;
        this->edoOjoDer = edoOjoDer;
    }

    void setId(string id){ this->id = id; }
    void setPosX(int posX){ this->posX = posX; }    
    void setPosY(int posY){ this->posY = posY; }
    void setEdoBoca(string edoBoca) { this->edoBoca = edoBoca; }
    void setEdoOjoIzq(string edoOjoIzq) { this->edoOjoIzq = edoOjoIzq; }
    void setEdoOjoDer(string edoOjoDer) { this->edoOjoDer = edoOjoDer; }
    void setEdoOjos(string edoOjos) { 
        this->edoOjoDer = edoOjos;
        this->edoOjoIzq = edoOjos;
    }

    string getId(){ return this->id; }    
    int getPosX(){ return this->posX; }    
    int getPosY(){ return this->posY; }    
    string getEdoBoca(){ return this->edoBoca; }    
    string getEdoOjoIzq(){ return this->edoOjoIzq; }    
    string getEdoOjoDer(){ return this->edoOjoDer; }    

    void print(){
        string marginX = this->getNChars(this->posX, " ");
        string marginY = this->getNChars(this->posY, "\n");
        cout << marginY << endl;
        cout << this->getEyes(marginX);
        cout << this->getMouth(marginX);        
        cout << "\n" << marginX << "      " << this->id << endl;
        cout << endl;
    }

    string getEyes(string marginX){
        string edoIzq = this->edoOjoIzq, edoDer = this->edoOjoDer;
        string eyes = marginX + "____________________\n";
        if(edoIzq.compare("abierto") == 0 && edoDer.compare("abierto") == 0){
            eyes += marginX + "|    ___    ___    |\n";
            eyes += marginX + "|   | _ |  | _ |   |\n";
            eyes += marginX + "|   |___|  |___|   |\n";
        } else if(edoIzq.compare("abierto") == 0 && edoDer.compare("cerrado") == 0){
            eyes += marginX + "|    ___           |\n";
            eyes += marginX + "|   | _ |   ___    |\n";
            eyes += marginX + "|   |___|          |\n";
        } else if(edoIzq.compare("cerrado") == 0 && edoDer.compare("abierto") == 0){
            eyes += marginX + "|           ___    |\n";
            eyes += marginX + "|   ___    | _ |   |\n";
            eyes += marginX + "|          |___|   |\n";
        } else if(edoIzq.compare("cerrado") == 0 && edoDer.compare("cerrado") == 0){
            eyes += marginX + "|                  |\n";
            eyes += marginX + "|    ___    ___    |\n";
            eyes += marginX + "|                  |\n";
        }
        eyes += marginX + "|                  |\n";
        return eyes;
    }


    string getMouth(string marginX){
        string edoMouth = this->edoBoca;
        string mouth = "";
        if(edoMouth.compare("abierto") == 0){
            mouth += marginX + "|    __________    |\n";
            mouth += marginX + "|   |__________|   |\n";
            mouth += marginX + "|                  |\n";
        } else if(edoMouth.compare("cerrado") == 0){
            mouth += marginX + "|                  |\n";
            mouth += marginX + "|   ____________   |\n";
            mouth += marginX + "|                  |\n";
        } else if(edoMouth.compare("sonriente") == 0){
            mouth += marginX + "|   ____________   |\n";
            mouth += marginX + "|   \\          /   |\n";
            mouth += marginX + "|    \\________/    |\n"; 
        } else if(edoMouth.compare("enojado") == 0){
            mouth += marginX + "|                  |\n";
            mouth += marginX + "|   ?#=+-?$^#@?!!  |\n";
            mouth += marginX + "|                  |\n";
        } else if(edoMouth.compare("triste") == 0){
            mouth += marginX + "|    __________    |\n";
            mouth += marginX + "|   /          \\   |\n";
            mouth += marginX + "|  /            \\  |\n";
        }
        mouth += marginX + "|__________________|\n";
        return mouth;
    }

    string getNChars(int n, string letter){
        string chars = "";
        for(int i = 0; i < n; i++){
            chars += letter;
        }
        return chars;
    }

    private:
        string id, edoBoca, edoOjoIzq, edoOjoDer;
        int posX, posY;
        
};

#endif
