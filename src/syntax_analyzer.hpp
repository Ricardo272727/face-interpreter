#include <iostream>
#include "./lexer/lexer.hpp"
#include "./semantic_analyzer.hpp"

using namespace std;

#ifndef SYNTAX_A_CLASS
#define SYNTAX_A_CLASS

class SyntaxAnalyzer {
    public:
    SyntaxAnalyzer(LexicalAnalizer * la, SemanticAnalyzer * sema){
        this->la = la;
        this->sema = sema;
    }
    
    void instr(){        
        this->notifyAnalyzing("instr");
        if(this->tokenIsEqual("creaCara")){
            this->creaCara();
        } else if(this->tokenIsEqual("borraCara")){
            this->borraCara();
        } else if(this->tokenIsEqual("cambiarNombre")){
            this->cambiarNombre();
        } else if(this->tokenIsEqual("cambiaEstadoOjo")){
            this->cambiaEstadoOjo();
        } else if(this->tokenIsEqual("cambiaEstadoOjos")){
            this->cambiaEstadoOjos();
        } else if(this->tokenIsEqual("cambiaEstadoBoca")){
            this->cambiaEstadoBoca();
        } else if(this->tokenIsEqual("ciclo")){
            this->bucle();
        } else if(this->tokenIsEqual("si")){            
            this->cond();
        } else {
            this->showSyntaxError();    
        }        
    }

    // creaCara
    void creaCara(){        
        if(this->tokenIsEqual("creaCara")){
            this->notifyAnalyzing("creaCara");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(",")){
                        this->goNextToken();
                        if(this->tokenIsType(TokenType::number)){
                            this->posX = this->token->getValue();
                            this->goNextToken();
                            if(this->tokenIsEqual(",")){
                                this->goNextToken();
                                if(this->tokenIsType(TokenType::number)){
                                    this->posY = this->token->getValue();
                                    this->goNextToken();
                                    if(this->tokenIsEqual(")")){
                                        this->sema->creaCaraInstr(this->id, this->posX, this->posY);
                                        this->goNextToken();
                                    } else {
                                        this->showSyntaxError("Token inesperado, se esperaba )");
                                    }
                                } else {
                                    this->showSyntaxError("Token inesperado, se esperaba un numero");   
                                }
                            } else {
                                this->showSyntaxError("Token inesperado, se esperaba \",\"");
                            }
                        } else {
                            this->showSyntaxError("Token inesperado, se esperaba un numero");
                        }
                    } else {
                        this->showSyntaxError("Error de sintáxis ... se esperaba \",\" ");
                    }
                } else {
                    this->showSyntaxError("Error de sintaxis ... se esperaba un identificador");
                }
            } else {
                this->showSyntaxError("Error de sintáxis ... se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }

    // borraCara
    void borraCara(){
        if(this->tokenIsEqual("borraCara")){
            this->notifyAnalyzing("borraCara");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(")")){
                        this->sema->borraCaraInstr(this->id);
                        this->goNextToken();
                    } else {
                        this->showSyntaxError("Error se esperaba )");
                    }
                } else {
                    this->showSyntaxError("Error, se esperaba identificador");
                }
            } else {
                this->showSyntaxError("Error de sintáxis, se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }


    // cambiarNombre
    void cambiarNombre(){
        if(this->tokenIsEqual("cambiarNombre")){
            this->notifyAnalyzing("cambiarNombre");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(",")){
                        this->goNextToken();
                        if(this->tokenIsType(TokenType::id)){
                            this->newId = this->token->getValue();
                            this->goNextToken();
                            if(this->tokenIsEqual(")")){
                                this->sema->cambiarNombreInstr(this->id, this->newId);
                                this->goNextToken();
                            } else {
                                this->showSyntaxError("Error, se esperaba )");
                            }
                        } else {
                            this->showSyntaxError("Error, se esperaba identificador");
                        }
                    } else {
                        this->showSyntaxError("Error, se esperaba \",\" ");
                    }
                } else {
                    this->showSyntaxError("Error, se esperaba identificador");
                }
            } else {
                this->showSyntaxError("Error, se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }

    // cambiaEstadoOjo
    void cambiaEstadoOjo(){
        if(this->tokenIsEqual("cambiaEstadoOjo")){
            this->notifyAnalyzing("cambiaEstadoOjo");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(",")){
                        this->goNextToken();
                        this->ladoOjo();
                        if(this->tokenIsEqual(",")){
                            this->goNextToken();
                            this->edoOjo();               
                            if(this->tokenIsEqual(")")){
                                this->sema->cambiaEstadoOjoInstr(this->id, this->ladoOjoVal, this->edoOjoVal);
                                this->goNextToken();
                            } else {
                                this->showSyntaxError("Error, se esperaba )");
                            }
                        } else {
                            this->showSyntaxError("Error, se esperaba ,");
                        }
                    } else {
                        this->showSyntaxError("Error, se esperaba \",\"");
                    }                    
                } else {
                    this->showSyntaxError("Error, se esperaba identificador");
                }
            } else {
                this->showSyntaxError("Error, se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }

    void edoOjo(){
        this->notifyAnalyzing("edoOjo");
        if(this->tokenIsEqual("abierto") || this->tokenIsEqual("cerrado")){            
            this->edoOjoVal = this->token->getValue();
            this->goNextToken();
        } else {
            this->showSyntaxError("Error, se esperaba abierto | cerrado");
        }
    }

    void ladoOjo(){
        this->notifyAnalyzing("ladoOjo");
        if(this->tokenIsEqual("derecho") || this->tokenIsEqual("izquierdo")){
            this->ladoOjoVal = this->token->getValue();
            this->goNextToken();
        } else {
            this->showSyntaxError("Error, se esperaba izquierdo | derecho");
        }
    }


    // cambiaEstadoOjos
    void cambiaEstadoOjos(){
        if(this->tokenIsEqual("cambiaEstadoOjos")){
            this->notifyAnalyzing("cambiaEstadoOjos");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(",")){
                        this->goNextToken();
                        this->edoOjo();
                        if(this->tokenIsEqual(")")){         
                            this->sema->cambiaEstadoOjosInstr(this->id, this->edoOjoVal);
                            this->goNextToken();
                        } else {
                            this->showSyntaxError("Error, se esperaba )");
                        }
                    } else {
                        this->showSyntaxError("Error se esperaba \",\"");
                    }
                } else {

                }
            } else {
                this->showSyntaxError("Error, se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }

    // cambiaEstadoBoca
    void cambiaEstadoBoca(){
        if(this->tokenIsEqual("cambiaEstadoBoca")){
            this->notifyAnalyzing("cambiaEstadoBoca");
            this->goNextToken();
            if(this->tokenIsEqual("(")){
                this->goNextToken();
                if(this->tokenIsType(TokenType::id)){
                    this->id = this->token->getValue();
                    this->goNextToken();
                    if(this->tokenIsEqual(",")){
                        this->goNextToken();
                        this->edoBoca();
                        if(this->tokenIsEqual(")")){
                            this->sema->cambiaEstadoBocaInstr(this->id, this->edoBocaVal);
                            this->goNextToken();
                        } else {
                            this->showSyntaxError("Error, se esperaba )");
                        }
                    } else {
                        this->showSyntaxError("Error, se esperaba \",\"");
                    }
                } else {
                    this->showSyntaxError("Error, se esperaba identificador");
                }
            } else {
                this->showSyntaxError("Error, se esperaba (");
            }
        } else {
            this->showSyntaxError();
        }
    }

    void edoBoca(){
        this->notifyAnalyzing("edoBoca");
        if(
            this->tokenIsEqual("abierto") || this->tokenIsEqual("cerrado") ||
            this->tokenIsEqual("sonriente") || this->tokenIsEqual("enojado") ||
            this->tokenIsEqual("triste")
        ) {
            this->edoBocaVal = this->token->getValue();
            this->goNextToken();
        } else {
            this->showSyntaxError("Error, se esperaba abierto | cerrado | sonriente | enojado | triste");
        }
    }

    // cond

    /*
    creaCara // ok
    si exprBool entonces // se crea cond y buildingTrue = true
        si exprBool entonces // se hace push de instr anterior y ahora current es cond2 building2True = true
            creaCara // se agrega a instrTrue de cond2 
        finSi // se pone building2True en false, pop de la pila (si existe) y actualiza current
    finSi // buildingTrue = false
    */
   
    void cond(){
        if(this->tokenIsEqual("si")) {
            this->notifyAnalyzing("cond");
            this->goNextToken();
            this->exprBool();
            if(this->tokenIsEqual("entonces")){
                this->sema->condInstr(this->opBool1, this->compVal, this->opBool2);
                this->goNextToken();
                if(this->tokenIsEqual("finSi") || this->tokenIsEqual("sino")){
                    this->showSyntaxError("Condicional no puede estar vacío");
                }
                while(this->token != NULL && !this->tokenIsEqual("finSi") && !this->tokenIsEqual("sino")){
                    this->instr(); // esto va en instrTrue
                }
                if(this->token == NULL){
                    this->showSyntaxError("Se esperaba finSi o sino");
                } else if(this->tokenIsEqual("sino")) {
                    this->condPrimaSino(); // aqui se llama a condPrimaSinoInstr
                } else if(this->tokenIsEqual("finSi")){
                    this->sema->finCondInstr();
                    this->goNextToken();
                } else {
                    this->showSyntaxError();
                }
            } else {
                this->showSyntaxError("Error se esperaba entonces");
            }
        } else {
            this->showSyntaxError("Error se esperaba si");   
        }    
    }
  
    void condPrimaSino(){
        this->notifyAnalyzing("condPrimaSino");
        if(this->tokenIsEqual("sino")){
            this->sema->condPrimaSinoInstr();
            this->goNextToken();
            if(this->tokenIsEqual("finSi")){
                this->showSyntaxError("Error sino no puede estar vacio");
            }
            while(this->token != NULL && !this->tokenIsEqual("finSi")){
                this->instr();
            }
            if(this->token == NULL){
                this->showSyntaxError();
            } else if(this->tokenIsEqual("finSi")){   
                this->sema->finCondInstr();
                this->goNextToken();
            } else {
                this->showSyntaxError();
            }
        } else {
            this->showSyntaxError("Error se esperaba sino");
        }
    }

    void exprBool(){        
        this->notifyAnalyzing("exprBool");
        this->opBool(1);        
        this->comp();        
        this->opBool(2);
    }

    void opBool(int n){
        this->notifyAnalyzing("opBool");
        if(
            this->tokenIsEqual("abierto") || this->tokenIsEqual("cerrado") ||
            this->tokenIsEqual("sonriente") || this->tokenIsEqual("enojado") ||
            this->tokenIsEqual("triste") || this->tokenIsEqual("estadoOjoIzq") ||
            this->tokenIsEqual("estadoOjoDer") || this->tokenIsEqual("estadoBoca")
        ){
            if(n == 1){
                this->opBool1 = this->token->getValue();
            } else {
                this->opBool2 = this->token->getValue();
            }
            this->goNextToken();
        } else {
            this->showSyntaxError("Error, se esperaba estado boca, estado ojos o variable global");
        }
    }

    void comp(){
        this->notifyAnalyzing("comp");
        if(this->tokenIsEqual("<>") || this->tokenIsEqual("=")){
            this->compVal = this->token->getValue();
            this->goNextToken();
        } else {
            this->showSyntaxError("Error se esperaba <> o =");
        }        
    }

    
    // bucle
    void bucle(){
        if(this->tokenIsEqual("ciclo")){
            this->notifyAnalyzing("bucle");
            this->goNextToken();                       
            if(this->tokenIsType(TokenType::number)){
                this->limit = this->token->getValue();
                this->sema->bucleInstr(this->limit);
                this->goNextToken();
                if(this->tokenIsEqual("finCiclo")){
                    this->showSyntaxError("Error de sintáxis, ciclo no puede estar vacío");
                }
                while(this->token != NULL && !this->tokenIsEqual("finCiclo")){
                    this->instr();
                }
                if(this->token == NULL){
                    this->showSyntaxError("Se esperaba finCiclo");
                } else if(this->tokenIsEqual("finCiclo")){
                    this->sema->finBucleInstr();
                    this->goNextToken();
                } else {
                    this->showSyntaxError();
                }
            } else {
                this->showSyntaxError("Error de sintáxis ... se esperaba un número");
            }
        } else {
            this->showSyntaxError("Token inválido... se esperaba ciclo");
        }
    }

   void goNextToken(){
       this->token = this->la->getNextToken();
   }

    void analyze(){
        this->goNextToken();
        while(this->token != NULL){
            this->instr();            
        }
    }

    bool tokenIsEqual(string str){
        if(this->token == NULL){
            this->showSyntaxError("Final de archivo inesperado, se esperaba: " + str);
            return false;
        }
        return this->token->getValue().compare(str) == 0;
    }

    bool tokenIsType(TokenType tokenType){
        if(this->token == NULL){
           this->showSyntaxError("Final de archivo inesperado, se esperaba: " + getTokenTypeName(tokenType));
           return false;
        }
        return this->token->getTokenType() == tokenType;
    }

    void notifyAnalyzing(string symbol){
        cout << "Syntax analizer: " << symbol << endl;
    }

    void showSyntaxError(string message = "Sintáxis inválida"){
        if(this->token == NULL){
            cout << "\n ==================================================== " << endl;
            cout << "\n " << message << endl;
            cout << "\n ==================================================== " << endl;
            exit(-1);
        }
        int nLine = this->token->getLine();
        int indexToken = this->token->getIndexToken();
        string value = this->token->getValue();
        string line = this->la->getLine(nLine);
        string prevLine = nLine > 0 ? this->la->getLine(nLine - 1) : "";
        cout << "\n ==================================================== " << endl;
        cout << "\n Error en la línea: " << nLine << "\n" << endl;
        cout << "\n " << prevLine << endl;
        cout << "\n " << line << endl;
        cout << "\n " << this->la->getNSpaces(indexToken) << "^" << endl;
        cout << "\n ------------> " << value << " <----------" << endl;
        cout << "\n " << message << endl;
        cout << "\n ==================================================== " << endl;
        exit(-1);
    }

    private:
        LexicalAnalizer * la;
        SemanticAnalyzer * sema;
        Token * token;
        string id, newId, edoOjoVal, edoBocaVal, ladoOjoVal, posX, posY, opBool1, opBool2, compVal, limit;
};

#endif