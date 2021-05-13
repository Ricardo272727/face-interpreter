#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include "./regex.hpp"
#include "./token_types.hpp"
#include "./state.hpp"
#include "./lexer.hpp"
#include "./row_transition_table.hpp"
#include "./transition_table.hpp"

using namespace std;




class LexerBuilder {
    public:
    static LexicalAnalizer * createLexer(string filename){

        Regex * letters = new Regex("^[a-zA-Z]$");
        Regex * digits = new Regex("^[0-9]+$");
        Regex * smallerThan = new Regex("^<$");
        Regex * greaterThan = new Regex("^>$");
        Regex * equal = new Regex("^=$");
        Regex * colon = new Regex("^[,]$");
        Regex * parenthesisO = new Regex("^[(]$");
        Regex * parenthesisC = new Regex("^[)]$");
        Regex * ignore = new Regex("[ \t\n\r]+");  

        Regex * regexRow [] = {
            letters,
            digits,
            smallerThan,
            greaterThan,
            equal,
            colon,
            parenthesisO,
            parenthesisC,
            ignore
        };

        int transitions [][9] = {
            {1,	3, 	5, -1,	7, 10,	8,	9, -1},
            {1,	1,	2,	2,	2,	2,	2,	2, 2},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, 3,	4,	4,	4,	4,	4,	4, 4},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, 6, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1}
        };

        RowTransitionTable * rows [] = {
            new RowTransitionTable(regexRow, transitions[0], 9),
            new RowTransitionTable(regexRow, transitions[1], 9),
            new RowTransitionTable(regexRow, transitions[2], 9, 1, TokenType::id),
            new RowTransitionTable(regexRow, transitions[3], 9),
            new RowTransitionTable(regexRow, transitions[4], 9, 1, TokenType::number),
            new RowTransitionTable(regexRow, transitions[5], 9),
            new RowTransitionTable(regexRow, transitions[6], 9, 0, TokenType::sign),
            new RowTransitionTable(regexRow, transitions[7], 9, 0, TokenType::sign),
            new RowTransitionTable(regexRow, transitions[8], 9, 0, TokenType::separator),
            new RowTransitionTable(regexRow, transitions[9], 9, 0, TokenType::separator),
            new RowTransitionTable(regexRow, transitions[10], 9, 0, TokenType::separator)
        };

        list<Regex*> * regs = new list<Regex*>();
        regs->push_back(new Regex("^estadoOjoIzq$"));
        regs->push_back(new Regex("^estadoOjoDer$")); 
        regs->push_back(new Regex("^estadoBoca$"));
        regs->push_back(new Regex("^derecho$"));
        regs->push_back(new Regex("^izquierdo$"));
        regs->push_back(new Regex("^abierto$"));
        regs->push_back(new Regex("^cerrado$"));
        regs->push_back(new Regex("^sonriente$"));
        regs->push_back(new Regex("^enojado$"));
        regs->push_back(new Regex("^triste$"));
        regs->push_back(new Regex("^si$"));
        regs->push_back(new Regex("^entonces$"));
        regs->push_back(new Regex("^sino$"));
        regs->push_back(new Regex("^finSi$"));
        regs->push_back(new Regex("^ciclo$"));
        regs->push_back(new Regex("^finCiclo$"));
        regs->push_back(new Regex("^creaCara$"));
        regs->push_back(new Regex("^borraCara$"));
        regs->push_back(new Regex("^cambiarNombre$"));
        regs->push_back(new Regex("^cambiaEstadoOjo$"));
        regs->push_back(new Regex("^cambiaEstadoOjos$"));
        regs->push_back(new Regex("^cambiaEstadoBoca$"));

        LexicalAnalizer * la = new LexicalAnalizer(filename);
        la->setTransitionTable(new TransitionTable(rows, 11));
        la->setReservedWords(regs);
        la->setIgnoreRegex(ignore);
        la->processFile();

        return la;
    }

};
