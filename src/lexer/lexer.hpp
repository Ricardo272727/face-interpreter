#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "./regex.hpp"
#include "./transition_table.hpp"
#include "./state.hpp"
#include "./token_types.hpp"
#include "./token.hpp"

using namespace std;

#ifndef LEXER_ANALIZER
#define LEXER_ANALIZER

class LexicalAnalizer{
    public:
    LexicalAnalizer(string filename){
        this->filename = filename;
        this->tokens = new list<Token*>();        
        this->fileContent = new vector<string>();
    }

    string getNSpaces(int n){
        string spaces = "";
        for(int i = 0; i < n; i++){
            spaces += " ";
        }
        return spaces;
    }

    void setTransitionTable(TransitionTable * tt){
        this->tt = tt;
    }

    void setReservedWords(list<Regex*> * reservedWords){
        this->reservedWords = reservedWords;
    }

    void setIgnoreRegex(Regex * ignore){
        this->ignore = ignore;
    }

    void processFile(){
        ifstream file(this->filename);
        string line, character, buffer = "";
        State * state;
        int nLine = 1;
        bool lastCharInLine;
        int recoil;

        while (getline (file, line)) {        
            this->fileContent->push_back(line);
            cout << "Lexer line: " << line << endl;
            for(int i = 0; i < line.length(); i++){
                character.push_back(line[i]);
                lastCharInLine = i == line.length() - 1;
                //cout << "before if" << endl;
                if(this->ignore->test(character) && this->tt->getState() == 0){                    
                    character.pop_back();
                    continue;
                }                
                //cout << "after if" << endl;
                //cout << "tt null " << (this->tt == NULL ? "si" : "no") << endl;
                state = this->tt->nextState(character);                
                //cout << "state " << (state == NULL ? "null" : "no null") << endl;
                if(state == NULL){
                    this->notifyError(line, nLine, character, i);
                } else if(state->isFinal()){
                    recoil = state->getRecoil();

                    if(state->getTokenType() == TokenType::id){
                        this->findTokenFromId(buffer, nLine - 1, i);                                                
                    } else {                        
                        if(recoil > 0){
                            this->findTokenFromOther(state->getTokenType(), buffer, nLine - 1, i);
                        } else {
                            this->findTokenFromOther(state->getTokenType(), buffer + character, nLine - 1, i);
                        }
                    }
                    if(recoil > 0){
                        i -= recoil;
                    }
                    this->tt->resetState();
                    buffer = "";
                } else if(lastCharInLine) {
                    //cout << "state null" << (state == NULL ? "si" : "no")  << endl;
                    //cout << getTokenTypeName(state->getTokenType()) << " type" << endl;
                    state = this->tt->nextState(" ");
                    this->findTokenFromOther(state->getTokenType(), buffer + character, nLine - 1, i);
                    this->tt->resetState();
                    buffer = "";
                } else {
                    buffer += character;
                }
                character.pop_back();
            }            
            nLine ++;
        }
        /*
        cout << "in buffer" << buffer << endl;
        if(buffer.length() > 0 && !this->ignore->test(buffer)){
            state = this->tt->nextState(" ");
            this->findTokenFromOther(state->getTokenType(), buffer, nLine - 1, 1);
        }*/
    }

    void findTokenFromId(string id, int line, int indexToken){
        //cout << "Id ? " << id << endl;
        list<Regex*> :: iterator it;
        for(it = this->reservedWords->begin(); it != this->reservedWords->end(); ++it){
            if((*it)->test(id)){
                this->tokens->push_back(new Token(TokenType::reservedWord, id, line, indexToken));
                return;
            }
        }
        this->tokens->push_back(new Token(TokenType::id, id, line, indexToken));
    }

    void findTokenFromOther(TokenType tokenType, string str, int line, int indexToken){
        //cout << "Token ? " << str << endl;
        if(tokenType == TokenType::id){
            this->findTokenFromId(str, line, indexToken);
        } else {
            this->tokens->push_back(new Token(tokenType, str, line, indexToken));
        }
    }
    
    void notifyError(string line, int nLine, string character, int indexChar){
        cout << "\n ==================================================== " << endl;
        cout << "\n Error en la línea: " << nLine << "\n" << endl;
        cout << "\n " << line << endl;
        cout << "\n " << this->getNSpaces(indexChar) << "^" << endl;
        cout << "\n Caracter inesperado: " << character << endl;
        cout << "\n ==================================================== " << endl;
        exit(-1);
    }

    Token * getNextToken(){
        if(this->tokens->empty())
            return NULL;        
        Token * token = this->tokens->front();        
        this->tokens->pop_front();
        //cout << "Token: " << token->getValue() << endl;
        return token;
    }

    void test(){
        Token * t = this->getNextToken();
        while(t != NULL){
            cout << "Token: " << t->getValue()  << " Type: " << t->getTokenTypeString() << endl;
            t = this->getNextToken();
        }
    }

    string getLine(int index){
        if(this->fileContent->size() - 1< index){
            cout << "Total lines: " << this->fileContent->size() << endl;
            cout << "Error getting line: " << index << endl;
            exit(-1);
        }
        return this->fileContent->at(index);
    }

  private:
    string filename;    
    Regex * ignore;
    TransitionTable * tt;
    list<Regex*> * reservedWords;
    list<Token*> * tokens;
    vector<string> * fileContent;
};

#endif