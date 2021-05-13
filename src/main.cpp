#include <iostream>
#include <string.h>
#include <list>
#include "./lexer/lexer_builder.hpp"
#include "./syntax_analyzer.hpp"
#include "./semantic_analyzer.hpp"
#include "./symbol_table.hpp"
#include "./interpreter.hpp"


int main(int argc, char *argv[]){

    if(argc < 2){
        cout << "Uso: $ asdp programa" << endl;
        return -1;
    }

    string filename = argv[1];    
    LexicalAnalizer * la = LexerBuilder::createLexer(filename);    
    SemanticAnalyzer * sema = new SemanticAnalyzer();
    SyntaxAnalyzer * sa = new SyntaxAnalyzer(la, sema);
    SymbolTable * st = new SymbolTable();
    Interpreter * inter = new Interpreter(st);
    sa->analyze();
    //sema->printInstructions();
    inter->execute(sema->getFirstInstr());


    return 0;
}