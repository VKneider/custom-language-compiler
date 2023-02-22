#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include<array> 
#include <vector>

using namespace std;

/*Añadir en Tools > Compiler options
Compiler Options -std=c++11
Library Options -static-libgcc
*/


/*
Proyecto de Desarrollo de un Compilador.
Lenguaje Copi 
Integrantes: Eduardo Morales, Andres Alvarez, Maria Fernanda, Victor Kneider.

Estructura:
Variable											Variable
	iden = numero.										X = 5.
	iden = numero.										Y_ = 7.
	iden = numero.										Sum = 3.
Inicio												Inicio
	iden = Expresion_Aritmetca							R = X + Sum * (Y_ + X)
Fin												  	Fin

FASE I: ANALIZADOR LEXICO
*/


// Enum para representar todos los tipos de tokens posibles
enum TokenType {
  KEYWORD,
  IDENTIFIER,
  DIGIT,
  ARITHMETIC_OP,
  LOGIC_OP,
  BRACKET,
  SEPARATOR,
  ENDOF
};

//Array de string para luego mostrar los tipos en los cout
string TokenTypeNames[] = {"KEYWORD", "IDEN", "DIGIT", "ARITHMETIC_OP", "LOGIC_OP", "BRACKET", "SEPARATOR", "ENDOF", "BLANK"};

//Array que contiene todas las palabras reservadas de nuestro lenguaje
string Keywords[]={"Variable", "Fin", "Inicio"};

//Clase para representar un token
class Token {
public:
  TokenType type;
  string value;

  // The colon ':' is used to initialize the members of a class 
  Token(TokenType t, string v) {
    type = t; 
    value = v;
  }
};

// Clase para representar el lexer, tokenizer (analizador lexico), contiene metodos para leer el input
class Lexer {
private:
  string input;
  int pos;
  char current_char;

public:
  Lexer(string i) {
    input = i;
    pos = 0;
    current_char = input.at(pos);
  }

  // Move to the next character in the input
  void advance() {
    pos++;
    if (pos > input.length() - 1) {
      current_char = 0;
    } else {
      current_char = input.at(pos);
    }
  }

  // Generate a token
  Token get_next_token() {
    while (current_char != 0) {

      if (isdigit(current_char)) {
        string number;
        while (isdigit(current_char)) {
          number.push_back(current_char);
          advance();
        }
        return Token(DIGIT, number);
      } 
      
      if (isalpha(current_char) || current_char == '_') {
        string word;
        while (isalpha(current_char) || current_char == '_') {
          word.push_back(current_char);
          advance();
        }
        
        int flag=0;
        int len = end(Keywords)-begin(Keywords);
        
    	for(int i=0;i<len;i++){
    		if(word==Keywords[i]){flag=1;}
    		
		}
		
        if (flag==1)
        {
          return Token(KEYWORD, word);
        }else{
          return Token(IDENTIFIER, word);
		}
        
      }

      if (isblank(current_char)) {
       // string blank;
        while (isblank(current_char)) {
         // blank.push_back(current_char);
          advance();
        }
        continue;
      }

      if (current_char == '+') {
        advance();
        return Token(ARITHMETIC_OP, "+");
      }

      if (current_char == '-') {
        advance();
        return Token(ARITHMETIC_OP, "-");
      }

      if (current_char == '*') {
        advance();
        return Token(ARITHMETIC_OP, "*");
      }

      if (current_char == '/') {
        advance();
        return Token(ARITHMETIC_OP, "/");
      }

      if (current_char == '=') {
        advance();
        return Token(LOGIC_OP, "=");
      }

      if (current_char == '.') {
        advance();
        return Token(SEPARATOR, ".");
      }

      if (current_char == '(' || current_char == ')') {
        string brace;
        brace.push_back(current_char);
        advance();
        return Token(BRACKET, brace);
      }

      throw "Error parsing input";
    }

    return Token(ENDOF, "");
  }
};

//Funcion para leer un archivo txt
string readFile(string filename) 
{ 
    ifstream inFile; 
    inFile.open(filename); // Se abre el archivo

    string content; //Contenido del archivo, donde se almacenan todas las lineas
    
    string line; //Contenido de la línea, variable temporal

    //Si el archivo ya está abierto, se termina el programa.
    if (!inFile) { 
        cout << "Unable to open file"<<endl;
        exit(1);
    }
    
    //Ciclo para obtener cada una de las lineas del archivo
    while (getline(inFile, line)) { 
        content += line;  
    }

    inFile.close(); //Se cierra el archivo

    return content; //Se retorna el contenido
}


// Función principal donde se ejecuta todo
int main() {
  
  string str = readFile("./text.txt");
  Lexer lexer(str);
  
  //Este vector representa la tabla de simbolos
  vector<Token> token_list;
  
  Token token = lexer.get_next_token();
  token_list.push_back(token);
  
  ofstream Myfile ("Compis.txt", ofstream::out);    
  
  	cout <<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
  	cout <<"		########  #######  ##    ## ######## ##    ## #### ######## ######## ########  "<< endl;
	cout <<"		   ##    ##     ## ##   ##  ##       ###   ##  ##       ##  ##       ##     ## "<< endl;
	cout <<"		   ##    ##     ## ##  ##   ##       ####  ##  ##      ##   ##       ##     ## "<< endl;
	cout <<"		   ##    ##     ## #####    ######   ## ## ##  ##     ##    ######   ########  "<< endl;
	cout <<"		   ##    ##     ## ##  ##   ##       ##  ####  ##    ##     ##       ##   ##   "<< endl;
	cout <<"		   ##    ##     ## ##   ##  ##       ##   ###  ##   ##      ##       ##    ##  "<< endl;
	cout <<"		   ##     #######  ##    ## ######## ##    ## #### ######## ######## ##     ## "<<endl;
	cout <<"-----------------------------------------------------------------------------------------------------------------------\n\n"<<endl;
	cout <<"#######################################################################################################################"<<endl;
	cout <<"#            Lexema	       #              Tipo	        #  "<<endl;
	cout <<"#######################################################################################################################"<<endl;
  while (token.type != ENDOF) {
    
    	if(TokenTypeNames[token.type]=="KEYWORD"){
    		cout << "            "<< token.value <<"          		      "<< TokenTypeNames[token.type] << endl;
    		Myfile << "            "<< token.value <<"          		      "<< TokenTypeNames[token.type] << endl;
    		
		}else{
			cout << "            "<< token.value <<"        		             "<< TokenTypeNames[token.type] << endl;
			Myfile << "            "<< token.value <<"        		             "<< TokenTypeNames[token.type] << endl;
		}
    	
        
    token = lexer.get_next_token();
    token_list.push_back(token);
  }
  Myfile.close();
  
  return 0;
}




