#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

/*A�adir en Tools > Compiler options
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
enum TokenType
{
  IDENTIFIER,
  DIGIT,
  OP_ADDITION,
  OP_SUBSTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_POWER,
  LEFT_PAREN,
  RIGHT_PAREN,
  SEPARATOR,
  KW_BEGIN,
  KW_END,
  KW_VARIABLE,
  ASSIGNER
};

string expectedToken = "KW_VARIABLE";

// Array de string para luego mostrar los tipos en los cout
string TokenTypeNames[] = {"IDENTIFIER",
                           "DIGIT",
                           "OP_ADDITION",
                           "OP_SUBSTRACT",
                           "OP_MULTIPLY",
                           "OP_DIVIDE",
                           "OP_POWER",
                           "LEFT_PAREN",
                           "RIGHT_PAREN",
                           "SEPARATOR",
                           "KW_BEGIN",
                           "KW_END",
                           "KW_VARIABLE",
						   "ASSIGNER"};

// Array que contiene todas las palabras reservadas de nuestro lenguaje
string Keywords[] = {"VARIABLE", "BEGIN", "END"};

// Clase para representar un token
class Token
{
public:
  TokenType type;
  string value;

  // The colon ':' is used to initialize the members of a class
  Token(TokenType t, string v)
  {
    type = t;
    value = v;
  }
};

// Clase para representar el lexer, tokenizer (analizador lexico), contiene metodos para leer el input
class Lexer
{
private:
  string input;
  int pos;
  char current_char;

public:
  Lexer(string i)
  {
    input = i;
    pos = 0;
    current_char = input.at(pos);
  }

  // Move to the next character in the input
  void advance()
  {
    pos++;
    if (pos > input.length() - 1)
    {
      current_char = 0;
    }
    else
    {
      current_char = input.at(pos);
    }
  }

  // Generate a token
  Token get_next_token()
  {
    while (current_char != 0)
    {

      if (isdigit(current_char))
      {
        string number;
        while (isdigit(current_char))
        {
          number.push_back(current_char);
          advance();
        }
        return Token(DIGIT, number);
      }

      if (isalpha(current_char) || current_char == '_')
      {
        string word;
        while (isalpha(current_char) || current_char == '_')
        {
          word.push_back(current_char);
          advance();
        }

        int flag = 0;
        int len = end(Keywords) - begin(Keywords);

        for (int i = 0; i < len; i++)
        {
          if (word == Keywords[i])
          {
            switch (i)
            {
            case 0:
              return Token(KW_VARIABLE, word);

            case 1:
              return Token(KW_BEGIN, word);
            case 2:
              return Token(KW_END, word);
            }
          }
          
        }
        return Token(IDENTIFIER, word);
      }

      if (isblank(current_char))
      {
        // string blank;
        while (isblank(current_char))
        {
          // blank.push_back(current_char);
          advance();
        }
        continue;
      }

      if (current_char == '+')
      {
        advance();
        return Token(OP_ADDITION, "+");
      }
      
        if (current_char == '^')
      {
        advance();
        return Token(OP_POWER, "^");
      }

      if (current_char == '-')
      {
        advance();
        return Token(OP_SUBSTRACT, "-");
      }

      if (current_char == '*')
      {
        advance();
        return Token(OP_MULTIPLY, "*");
      }

      if (current_char == '/')
      {
        advance();
        return Token(OP_DIVIDE, "/");
      }

      if (current_char == '=')
      {
        advance();
        return Token(ASSIGNER, "=");
      }

      if (current_char == '.')
      {
        advance();
        return Token(SEPARATOR, ".");
      }



      if (current_char == '(')
      {
        advance();
        return Token(LEFT_PAREN, "(");
      }

      if (current_char == ')')
      {
        advance();
        return Token(RIGHT_PAREN, ")");
      }

      throw "Error parsing input";
    }

    
  }
};

// Funcion para leer un archivo txt
string readFile(string filename)
{
  ifstream inFile;
  inFile.open(filename); // Se abre el archivo

  string content; // Contenido del archivo, donde se almacenan todas las lineas

  string line; // Contenido de la l�nea, variable temporal

  // Si el archivo ya est� abierto, se termina el programa.
  if (!inFile)
  {
    cout << "Unable to open file" << endl;
    exit(1);
  }

  // Ciclo para obtener cada una de las lineas del archivo
  while (getline(inFile, line))
  {
    content += line;
  }

  inFile.close(); // Se cierra el archivo

  return content; // Se retorna el contenido
}



class Parser {
public:
    Parser(vector<Token> tokens) : tokens(tokens), pos(0) {}

    void parse() {
        program();
        // Check that we've consumed all tokens
        if (pos != tokens.size()) {
            throw runtime_error("Unexpected token at position " + to_string(pos) + ": " + tokens[pos].value + "  with expected Token: " + expectedToken);
        }
        cout << "Parsing succeeded." << endl;
    }

private:
    void match(TokenType expected) {
    	std::ostringstream oss;
		oss << expected;
		string objectString = oss.str();
        if (tokens[pos].type != expected) {
            // Throw an exception indicating the position of the error
            throw runtime_error("Unexpected token at position " + to_string(pos) + ": " + tokens[pos].value + "  with expected Token: " + expectedToken);
        }
        pos++;
    }

    void program() {
    	expectedToken = "KW_VARIABLE";
        match(KW_VARIABLE);
        definitions();
        expectedToken = "KW_BEGIN";
        match(KW_BEGIN);
        stmt_list();
        expectedToken = "KW_END";
        match(KW_END);
    }

    void definitions() {
    	expectedToken = "IDENTIFIER";
        if (tokens[pos].type == IDENTIFIER) {
            variable_def();
            definitions();
        }
        // Otherwise, do nothing (epsilon production)
    }

    void variable_def() {
    	expectedToken = "IDENTIFIER";
        match(IDENTIFIER);
        expectedToken = "ASSIGNER";
        match(ASSIGNER);
        expectedToken = "DIGIT";
        match(DIGIT);
        expectedToken = "SEPARATOR";
        match(SEPARATOR);
    }

    void stmt_list() {
    	expectedToken = "IDENTIFIER or LEFT_PAREN";
        if (tokens[pos].type == IDENTIFIER || tokens[pos].type == LEFT_PAREN) {
            statement();
            stmt_list();
        }
        // Otherwise, do nothing (epsilon production)
    }

    void statement() {
    	expectedToken = "IDENTIFIER or TERM";
        if (tokens[pos].type == IDENTIFIER) {
            variable_assignment();
        } else {
            expression();
        }
    }

    void variable_assignment() {
    	expectedToken = "IDENTIFIER";
        match(IDENTIFIER);
        expectedToken = "ASSIGNER";
        match(ASSIGNER);
        expression();
        expectedToken = "SEPARATOR";
        match(SEPARATOR);
    }

    void expression() {
        term();
        expectedToken = "OP_ADDITTION OR OP_SUBSTRACT";
        while (tokens[pos].type == OP_ADDITION || tokens[pos].type == OP_SUBSTRACT) {
            match(tokens[pos].type);
            term();
        }
    }

    void term() {
        factor();
        expectedToken = "OP_MULTIPLY OR OP_DIVIDE OR OP_POWER";
        while (tokens[pos].type == OP_MULTIPLY || tokens[pos].type == OP_DIVIDE || tokens[pos].type == OP_POWER) {
            match(tokens[pos].type);
            factor();
        }
    }

    void factor() {
        if (tokens[pos].type == DIGIT) {
        	expectedToken = "DIGIT";
            match(DIGIT);
        } else if (tokens[pos].type == IDENTIFIER) {
        	expectedToken = "IDENTIFIER";
            match(IDENTIFIER);
        } else if (tokens[pos].type == LEFT_PAREN) {
        	expectedToken = "LEFT_PAREN";
            match(LEFT_PAREN);
            expression();
            expectedToken = "RIGHT_PAREN";
            match(RIGHT_PAREN);
        } 
    }

    vector<Token> tokens;
    size_t pos;
};



// Funci�n principal donde se ejecuta todo
int main()
{

  string str = readFile("./text.txt");
  Lexer lexer(str);

  // Este vector representa la tabla de simbolos
  vector<Token> token_list;

  Token token = lexer.get_next_token();
  token_list.push_back(token);

  ofstream Myfile("Compis.txt", ofstream::out);

  while (token.type != KW_END)
  {
    token = lexer.get_next_token();
    	cout << TokenTypeNames[token.type] << " - " << token.value << endl;
    token_list.push_back(token);
    
  }
  Myfile.close();
  
  Parser parser(token_list);
  try {
    parser.parse();
    cout << "Parsing succeeded!" << endl;
  } catch (const exception& e) {
    cout << "Parsing failed: " << e.what() << endl;
  }
  
  

  return 0;
}
