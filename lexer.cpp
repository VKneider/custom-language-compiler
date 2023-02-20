#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include<array> 

using namespace std;

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


// Enum to represent the different token types
enum TokenType {
  KEYWORD,
  IDENTIFIER,
  DIGIT,
  ARITHMETIC_OP,
  LOGIC_OP,
  BRACKET,
  SEPARATOR,
  BLANK,
  ENDOF
};

string TokenTypeNames[] = {"KEYWORD", "IDEN", "DIGIT", "ARITHMETIC_OP", "LOGIC_OP", "BRACKET", "SEPARATOR", "ENDOF", "BLANK"};
string Keywords[]={"Variable", "Fin", "Inicio"};

// Class to represent a token
class Token {
public:
  TokenType type;
  string value;

  // The colon ':' is used to initialize the members of a class 
  Token(TokenType type, string value) : type(type), value(value) {}
};

// Lexer class
class Lexer {
private:
  string input;
  int pos;
  char current_char;

public:
  // Constructor. The colon ':' is used to initialize the members of a class 
  Lexer(string input) : input(input), pos(0) {
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
        string blank;
        while (isblank(current_char)) {
          blank.push_back(current_char);
          advance();
        }
        return Token(BLANK, " ");
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



// Main function to test the lexer
int main() {

  string input = "Variable _X=5. Y_ = 7. Sum = 5. Inicio R = _X + Sum * (Y_ + _X) Fin";

  Lexer lexer(input);

  Token token = lexer.get_next_token();

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

    if (token.type != BLANK){
    	if(TokenTypeNames[token.type]=="KEYWORD"){
    		cout << "            "<< token.value <<"          		      "<< TokenTypeNames[token.type] << endl;
		}else{
			cout << "            "<< token.value <<"        		             "<< TokenTypeNames[token.type] << endl;
		}
    	
    //Myfile << "Found token '" << token.value << "' with type " << TokenTypeNames[token.type] << endl;
    }
    token = lexer.get_next_token();
  }
  Myfile.close();
  return 0;
}
