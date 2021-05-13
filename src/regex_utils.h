/*
 *
Tipos de tokens

#palabras reservadas

estadoOjoIzq 
estadoOjoDer
estadoBoca
derecho
izquierdo
abierto
cerrado
sonriente
enojado
triste
Si
entonces
Sino
finSi
Ciclo
creaCara
borraCara
cambiarNombre
cambiaEstadoOjo
cambiaEstadoOjos
cambiaEstadoBoca


#signo comparacion

<>
=

#Identificador

#numero entero

#separadores
(
)
,

 *
 * */

/*
class LexicalAnalizer{
  public:
  LexicalAnalizer(string filename){
    this->filename = filename;    
  }

  void setRegex(list <Regex*> * reg){
    this->regs = reg;
  }

  void setIgnoreRegex(Regex * ignoreRegex){
    this->ignoreRegex = ignoreRegex;
  }

  void setSeparators(list <Regex*> * separators){
    this->separators = separators;
  }

  void setOperators(list <Regex*> * operators){
    this->operators = operators;
  }

  void processLine(string line){

  }

  void processFile(){
    ifstream file(this->filename);
    string line;    
    int nLine = 0;
    string buffer;
    string character;
    bool separator, ignore, charOperator, lastCharInLine;
    int lineLength;
    while (getline (file, line)) {
      // llenar buffer mientras no me tope con un separador o coincida con ignoreRegex el caracter
      // creaCara(Atenea, 10, 10)
      //cout << line << endl;

      // creaCara( Atenea, 10, 10)
      /
      ch = coma
      operador = no, no ..., no, no, no ..., no
      separador = no, no ... si, no, no ..., si
      ignorado = no, no ... no, si, no ..., no
      buffer = 
      findToken(creaCara)
      findSeparatorToken("(")
      findToken(Atenea)
      /
      //cout << "Line" << line << endl;
      lineLength = line.length();
      for(int i = 0; i < line.length(); i++){
        character.push_back(line[i]);
        ignore = this->isIgnored(character);
        charOperator = this->isOperator(character);
        lastCharInLine = i == line.length() - 1;

        if(this->isOperator(buffer)){          
          this->findOperatorToken(buffer, line, nLine);
          buffer = "";
        } else if (this->isSeparator(character) || ignore || charOperator){
            if(buffer.length() > 0){
              this->findToken(buffer, line, nLine);
              buffer = "";
              i -= 1;          
            } else if(!ignore && !charOperator){
              this->findSeparatorToken(character, line, nLine);
            } else if(charOperator){
              this->findOperatorToken(character, line, nLine);
            }
        } else if(lastCharInLine){
            buffer += character;          
            this->findToken(buffer, line, nLine);
            buffer = "";          
        } else {
            buffer += character;          
        }
        character.pop_back();
        /
        // si es separador o es ignorado
        string character;
        character.push_back(line[i]);
                
        separator = this->isSeparator(character);
        is_operator = this->isOperator(character);

        if(separator || this->isIgnored(character) || is_operator){
          if(buffer.length() > 0){
            this->findToken(buffer, line, nLine);
            buffer = "";
            if(separator || is_operator){
              i -= 1;
            }
          } else if(separator || is_operator){
            this->findToken(character, line, nLine);
            buffer = "";
          }
        } else {
          buffer += character;
        }/
        //    si el buffer tiene contenido
        //       encontrar tipo de token
        //       vaciar buffer
        //       si es separador
        //          i -= 1
        //    sino
        //      si es separador
        //          encontrar tipo de token (separador)
        //          vaciar buffer
        // sino
        //    agregar al buffer
        //cout << "Buffer: >> " + this->buffer;
      }            
      nLine ++;      
    }
    
  }
  
  Token * getNextToken(){
    return NULL;
  }

  void findToken(string buffer, string line, int nLine){
    cout << "\n Esto es un token?" + buffer;
  }

  void findOperatorToken(string buffer, string line, int nLine){
    cout << "\n Esto es un token op? "  + buffer;
  }

  void findSeparatorToken(string buffer, string line, int nLine){
    cout << "\n Esto es un token sep? " + buffer;
  }

  bool isSeparator(string str){    
    list <Regex*> :: iterator it;
    for(it = this->separators->begin(); it != this->separators->end(); ++it){
      if((*it)->test(str)){
        return true;
      }
    }
    return false;
  }

  bool isOperator(string str){
    list <Regex*> :: iterator it;
    for(it = this->operators->begin(); it != this->operators->end(); ++it){
      if((*it)->test(str)){
        return true;
      }
    }
    return false;   
  }

  bool isIgnored(string str){    
    return this->ignoreRegex->test(str);
  }

  // hacer automatas de analisis lexico
  // terminar de crear las regex
  // checar que onda con preanalisis

  private:
    list <Regex*> * regs;
    list <Regex*> * separators;
    list <Regex*> * operators;
    Regex * ignoreRegex;
    list <Token*> * tokens;    
    string filename;
};*/
