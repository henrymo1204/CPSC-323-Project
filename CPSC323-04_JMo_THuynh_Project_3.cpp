#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <map>

using namespace std;

void lexer(char arr[], int size);
string convertTerminalToLetter(string a, string b);
int convertToNum(string a, string b);
int state = 0;//initial state
int before = 0;
int counter = 0;//counter for number of elements in the array record
int SIZE = 1000;//size of the record

int counter_code = 1;//counter for machine code

int* num = new int[SIZE];//integer array for the first column of the machine code table
string* machine_code = new string[SIZE];//string array for the second column for the machine code table
int* address = new int[SIZE];//integer array for the third column of the machine code table

int counter_symbol = 1;//counter for symbol table
int location = 5000;//starting address
bool symbol = false;

string* identifier = new string[SIZE];//string array for the first column of the symbol table
int* memory_location = new int[SIZE];//integer array for the second column of the symbol table
string* type = new string[SIZE];//string array for the third column of the symbol table

string* tokenRecord = new string[SIZE];//string array that stores tokens
string* lexemeRecord = new string[SIZE];//string array that stores lexemes

int main() {
	ifstream myFile;
	string input = "input.txt";
	myFile.open(input);
	ofstream output;
	output.open("output.txt");

	stack<int> jump;
	stack<string> ss;
	int p = 0;
	int table[12][23] = { { 1, 0, 0, 0, 0, 0, 0, 24, 24, 14, 15, 16, 13, 13, 13, 0, 24, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 4, 5, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6 },
	{ 7, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 10, 10, 8, 9, 0, 10, 10, 10, 0, 0, 0, 0, 0, 0, 10, 10, 0, 10, 10, 10, 10, 10 },
	{ 12, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 19, 20, 21, 22 },
	{ 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 23, 23, 23, 0, 24, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 29, 29, 0, 0, 0, 0, 0, 0, 0, 29, 28, 0, 0, 0, 0, 0 } };

	if (myFile.is_open()) {
		while (!myFile.eof()) {
			for (int i = 0; i < SIZE; i++) {
				tokenRecord[i] = "";
				lexemeRecord[i] = "";
			}
			string sLine;
			getline(myFile, sLine);//reads the file line by line
			int length = sLine.length() + 1;
			char* char_array = new char[length];
			strcpy_s(char_array, length, sLine.c_str());//convert the line to an array of char
			lexer(char_array, length);
			if (counter > 0) {
				if (ss.size() == 0) {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = "@";
					ss.push("@");
					ss.push("S");
					while (ss.size() > 0) {
						while (ss.top() == "POPM" || ss.top() == "ADD" || ss.top() == "SUB" || ss.top() == "MUL" || ss.top() == "DIV" || ss.top() == "PUSHM" || ss.top() == "SYMBOL" ||
							ss.top() == "MORESYMBOL" || ss.top() == "LABEL_FOR_WHILE" || ss.top() == "LABEL_FOR_IF" || ss.top() == "LABEL_FOR_DO_WHILE" || ss.top() == "JUMP" ||
							ss.top() == "RELOP") {
							if (ss.top() == "POPM") {
								symbol = false;
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "POPM";
								int j = 0;
								for (int i = 0; i < counter_symbol - 1; i++) {
									if (identifier[i] == ss.top()) {
										symbol = true;
										j = i;
									}
								}
								if (symbol == true) {
									address[counter_code - 1] = memory_location[j];
								}
								else {
									output << ss.top() << " is not initilized." << endl;
								}
								ss.pop();
								counter_code++;
							}
							else if (ss.top() == "ADD") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "ADD";
								address[counter_code - 1] = -1;
								counter_code++;
							}
							else if (ss.top() == "SUB") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "SUB";
								address[counter_code - 1] = -1;
								counter_code++;
							}
							else if (ss.top() == "MUL") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "MUL";
								address[counter_code - 1] = -1;
								counter_code++;
							}
							else if (ss.top() == "DIV") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "DIV";
								address[counter_code - 1] = -1;
								counter_code++;
							}
							else if (ss.top() == "PUSHM") {
								symbol = false;
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "PUSHM";
								int j = 0;
								for (int i = 0; i < counter_symbol - 1; i++) {
									if (identifier[i] == ss.top()) {
										symbol = true;
										j = i;
									}
								}
								if (symbol == true) {
									address[counter_code - 1] = memory_location[j];
								}
								else {
									output << ss.top() << " is not initilized." << endl;
								}
								ss.pop();
								counter_code++;
							}
							else if (ss.top() == "SYMBOL") {
								ss.pop();
								type[counter_symbol - 1] = ss.top();
								ss.pop();
								memory_location[counter_symbol - 1] = location;
								location++;
								identifier[counter_symbol - 1] = ss.top();
								ss.pop();
								counter_symbol++;
							}
							else if (ss.top() == "MORESYMBOL") {
								ss.pop();
								type[counter_symbol - 1] = type[counter_symbol - 2];
								memory_location[counter_symbol - 1] = location;
								location++;
								identifier[counter_symbol - 1] = ss.top();
								ss.pop();
								counter_symbol++;
							}
							else if (ss.top() == "LABEL_FOR_WHILE") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "LABEL";
								address[counter_code - 1] = -1;
								jump.push(counter_code);
								counter_code++;
							}
							else if (ss.top() == "LABEL_FOR_IF") {
								ss.pop();
								address[jump.top() - 1] = counter_code;
								jump.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "LABEL";
								address[counter_code - 1] = -1;
								jump.push(counter_code);
								counter_code++;
							}
							else if (ss.top() == "LABEL_FOR_DO_WHILE") {
								ss.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "LABEL";
								address[counter_code - 1] = -1;
								jump.push(counter_code);
								counter_code++;
							}
							else if (ss.top() == "JUMP") {
								ss.pop();
								address[jump.top() - 1] = counter_code + 1;
								jump.pop();
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "JUMP";
								address[counter_code - 1] = jump.top();
								counter_code++;
							}
							else if (ss.top() == "RELOP") {
								ss.pop();
								if (ss.top() == "<") {
									machine_code[counter_code - 1] = "LES";
								}
								else if (ss.top() == "<=") {
									machine_code[counter_code - 1] = "LEQ";
								}
								else if (ss.top() == "==") {
									machine_code[counter_code - 1] = "EQU";
								}
								else if (ss.top() == ">=") {
									machine_code[counter_code - 1] = "GEQ";
								}
								else if (ss.top() == ">") {
									machine_code[counter_code - 1] = "GRT";
								}
								num[counter_code - 1] = counter_code;
								address[counter_code - 1] = -1;
								counter_code++;
								num[counter_code - 1] = counter_code;
								machine_code[counter_code - 1] = "JUMPZ";
								if (lexemeRecord[0] == "if" || lexemeRecord[0] == "while") {
									jump.push(counter_code);
								}
								else {
									address[counter_code - 1] = jump.top();
								}
								counter_code++;
								ss.pop();
							}
						}
						if (ss.top() == "=" || lexemeRecord[p] == "%") {
							if (tokenRecord[p] == "Keyword" || tokenRecord[p] == "Operator") {
								//output << "Token: " << tokenRecord[p] << "				" << "Lexemes: " << lexemeRecord[p] << endl;
								//output << endl;
								//output << endl;
								p++;
								ss.pop();
							}
							else {
								//output << "Token: " << tokenRecord[p] << "			" << "Lexemes: " << lexemeRecord[p] << endl;
								//output << endl;
								//output << endl;
								p++;
								ss.pop();
							}
						}
						else if (convertTerminalToLetter(tokenRecord[p], lexemeRecord[p]) == ss.top()) {
							if (tokenRecord[p] == "Keyword" || tokenRecord[p] == "Operator") {
								//output << "Token: " << tokenRecord[p] << "				" << "Lexemes: " << lexemeRecord[p] << endl;
								//output << endl;
								//output << endl;
								p++;
								ss.pop();
							}
							else {
								//output << "Token: " << tokenRecord[p] << "			" << "Lexemes: " << lexemeRecord[p] << endl;
								//output << endl;
								//output << endl;
								p++;
								ss.pop();
							}
						}
						// ===================================================================================================================
						else if (lexemeRecord[p] == "@" && ss.top() == "@") {
							for (int i = 0; i < SIZE; i++) {
								tokenRecord[i] = "";
								lexemeRecord[i] = "";
							}
							break;
						}
						else {
							//output << ss.top() << endl;
							//output << convertToNum(ss.top(), "a") << endl;
							//output << lexemeRecord[p] << endl;
							//output << convertToNum(tokenRecord[p], lexemeRecord[p]) << endl;
							switch (table[convertToNum(ss.top(), "a")][convertToNum(tokenRecord[p], lexemeRecord[p])]) {
							case 1: //1.S -> A
								//output << "<Statement> -> <Assign>" << endl;
								ss.pop();
								ss.push("A");
								break;

							case 2: //2.A -> id = E {POPM, get address(id)};
								//output << "<Assign> -> <id> = <Expression> ;" << endl;
								ss.pop();
								ss.push(";");
								ss.push(lexemeRecord[p]);
								ss.push("POPM");
								ss.push("E");
								ss.push("=");
								ss.push("id");
								break;

							case 3: //3.E -> TE'
								//output << "<Expression> -> <Term><ExpressionPrime>" << endl;
								ss.pop();
								ss.push("E'");
								ss.push("T");
								break;

							case 4: //4.E' -> +T{ADD, nil}E'
								//output << "<ExpressionPrime> -> + <Term> <ExpressionPrime" << endl;
								ss.pop();
								ss.push("E'");
								ss.push("ADD");
								ss.push("T");
								ss.push("+");
								break;

							case 5: //5.E' -> -T{SUB, nil}E'
								//output << "<ExpressionPrime> -> - <Term> <ExpressionPrime>" << endl;
								ss.pop();
								ss.push("E'");
								ss.push("SUB");
								ss.push("T");
								ss.push("-");
								break;

							case 6: //6.E' -> epsilon
								//output << "<ExpressionPrime> -> <Empty>" << endl;
								ss.pop();
								break;

							case 7: //7.T -> FT'
								//output << "<Term> -> <Factor> <TermPrime>" << endl;
								ss.pop();
								ss.push("T'");
								ss.push("F");
								break;

							case 8: //8.T' -> *F{MUL, nil}T'
								//output << "<TermPrime> -> * <Factor> <TermPrime>" << endl;
								ss.pop();
								ss.push("T'");
								ss.push("MUL");
								ss.push("F");
								ss.push("*");
								break;

							case 9: //9.T' -> /F{DIV, nil}T'
								//output << "<TermPrime> -> / <Factor> <TermPrime>" << endl;
								ss.pop();
								ss.push("T'");
								ss.push("DIV");
								ss.push("F");
								ss.push("/");
								break;

							case 10: //10.T' -> epsilon
								//output << "<TermPrime> -> <Empty>" << endl;
								ss.pop();
								break;

							case 11: //11.F -> (E)
								//output << "<Factor> -> ( <Expression> )" << endl;
								ss.pop();
								ss.push(")");
								ss.push("E");
								ss.push("(");
								break;

							case 12: //12.F -> id {PUSHM, get address(id)}
								//output << "<Factor> -> id" << endl;
								ss.pop();
								ss.push(lexemeRecord[p]);
								ss.push("PUSHM");
								ss.push("id");
								break;

							case 13: //13.S -> D
								//output << "<Statements> -> <Declarative>" << endl;
								ss.pop();
								ss.push("D");
								break;

							case 14: //14.S -> if C {S}{LABEL, nil} else {S}
								//output << "<Statement> -> if <Conditional> { <Statements> } else { <Statements> }" << endl;
								ss.pop();
								ss.push("}");
								ss.push("S");
								ss.push("{");
								ss.push("else");
								ss.push("}");
								ss.push("LABEL_FOR_IF");
								ss.push("S");
								ss.push("{");
								ss.push("C");
								ss.push("if");
								break;

							case 15: //15.S -> while {LABEL, nil} C {S} {JUMP, address}
								//output << "<Statements> -> while <Conditional> { <Statements> }" << endl;
								ss.pop();
								ss.push("}");
								ss.push("JUMP");
								ss.push("S");
								ss.push("{");
								ss.push("C");
								ss.push("LABEL_FOR_WHILE");
								ss.push("while");
								break;

							case 16: //16.S -> do {S} while C
								//output << "<Statements> -> do { <Statements> } while <Conditional>" << endl;
								ss.pop();
								ss.push("C");
								ss.push("while");
								ss.push("}");
								ss.push("LABEL_FOR_DO_WHILE");
								ss.push("S");
								ss.push("{");
								ss.push("do");
								break;

							case 17: //17.C -> (ERE) {RELOP}
								//output << "<Conditional> -> ( <Expression> <Relop> <Expression> )" << endl;
								ss.pop();
								ss.push(")");
								ss.push(lexemeRecord[p + 2]);
								ss.push("RELOP");
								ss.push("E");
								ss.push("R");
								ss.push("E");
								ss.push("(");
								break;

							case 18: //18.R -> <
								//output << "<Relop> -> <" << endl;
								ss.pop();
								ss.push("<");
								break;

							case 19: //19.R -> <=
								//output << "<Relop> -> <=" << endl;
								ss.pop();
								ss.push("<=");
								break;

							case 20: //20.R -> == 
								//output << "<Relop> -> ==" << endl;
								ss.pop();
								ss.push("==");
								break;

							case 21: //21.R -> >=
								//output << "<Relop> -> >=" << endl;
								ss.pop();
								ss.push(">=");
								break;

							case 22: //22.R -> >
								//output << "<Relop> -> >" << endl;
								ss.pop();
								ss.push(">");
								break;

							case 23: //23.D -> TY {SYMBOL TABLE} id M;
								//output << "<Declarative> -> <Type> id <MoreIDs> ;" << endl;
								ss.pop();
								ss.push(";");
								ss.push("M");
								ss.push("id");
								ss.push(lexemeRecord[p + 1]);
								ss.push(lexemeRecord[p]);
								ss.push("SYMBOL");
								ss.push("TY");
								break;

							case 24: //24.D -> epsilon
								//output << "<Declarative> -> <Empty>" << endl;
								ss.pop();
								break;

							case 25: //25.TY -> int
								//output << "<Type> -> int" << endl;
								ss.pop();
								ss.push("int");
								break;

							case 26: //26.TY -> float
								//output << "<Type> -> float" << endl;
								ss.pop();
								ss.push("float");
								break;

							case 27: //27.TY -> bool
								//output << "<Type> -> bool" << endl;
								ss.pop();
								ss.push("bool");
								break;

							case 28: //28.M -> , {SYMBOL TABLE} id M
								//output << "<MoreIDs> -> , <id> <MoreIDs>" << endl;
								ss.pop();
								ss.push("M");
								ss.push("id");
								ss.push(lexemeRecord[p + 1]);
								ss.push("MORESYMBOL");
								ss.push(",");
								break;

							case 29: //29.M -> epsilon
								//output << "<MoreIDs> -> <Empty>" << endl;
								ss.pop();
								break;

							default:
								output << "parsing table defaulted" << endl;
								break;
							}
						}
					}
				}
				p = 0;
			}
		}
	}

	//output << "Parsing Generated." << endl;

	for (int i = 0; i < counter_code - 1; i++) {
		if (address[i] != -1) {
			output << num[i] << "		" << machine_code[i] << "		" << address[i] << endl;
		}
		else {
			output << num[i] << "		" << machine_code[i] << endl;
		}
	}

	output << endl;
	output << endl;
	output << endl;

	output << "Symbol Table" << endl;
	output << "Identifier" << "	" << "MemoryLocation" << "	" << "Type" << endl;
	for (int i = 0; i < counter_symbol - 1; i++) {
		output << identifier[i] << "		" << memory_location[i] << "		" << type[i] << endl;
	}

	myFile.close();
	output.close();
	delete[] num;
	delete[] machine_code;
	delete[] address;
	delete[] identifier;
	delete[] memory_location;
	delete[] type;
	delete[] tokenRecord;
	delete[] lexemeRecord;

	return 0;
}

int convertToNum(string a, string b) { //convert terminals and non-terminals to numbers
	if (a == "Identifier") {
		return 0;
	}
	else if (a == "id") {
		return 0;
	}
	else if (a == "Operator") {
		if (b == "+") {
			return 1;
		}
		else if (b == "-") {
			return 2;
		}
		else if (b == "*") {
			return 3;
		}
		else if (b == "/") {
			return 4;
		}
		else if (b == "<") {
			return 18;
		}
		else if (b == "<=") {
			return 19;
		}
		else if (b == "==") {
			return 20;
		}
		else if (b == ">=") {
			return 21;
		}
		else if (b == ">") {
			return 22;
		}
	}
	else if (a == "+") {
		return 1;
	}
	else if (a == "-") {
		return 2;
	}
	else if (a == "*") {
		return 3;
	}
	else if (a == "/") {
		return 4;
	}
	else if (a == "<") {
		return 18;
	}
	else if (a == "<=") {
		return 19;
	}
	else if (a == "==") {
		return 20;
	}
	else if (a == ">=") {
		return 21;
	}
	else if (a == ">") {
		return 22;
	}
	else if (a == "Separator") {
		if (b == "(") {
			return 5;
		}
		else if (b == ")") {
			return 6;
		}
		else if (b == "@") {
			return 7;
		}
		else if (b == ";") {
			return 8;
		}
		else if (b == "{") {
			return 15;
		}
		else if (b == "}") {
			return 16;
		}
		else if (b == ",") {
			return 17;
		}
	}
	else if (a == "(") {
		return 5;
	}
	else if (a == ")") {
		return 6;
	}
	else if (a == "@") {
		return 7;
	}
	else if (a == ";") {
		return 8;
	}
	else if (a == "{") {
		return 15;
	}
	else if (a == "}") {
		return 16;
	}
	else if (a == ",") {
		return 17;
	}
	else if (a == "Keyword") {
		if (b == "if") {
			return 9;
		}
		else if (b == "while") {
			return 10;
		}
		else if (b == "do") {
			return 11;
		}
		else if (b == "int") {
			return 12;
		}
		else if (b == "flat") {
			return 13;
		}
		else if (b == "bool") {
			return 14;
		}
	}
	else if (a == "if") {
		return 9;
	}
	else if (a == "while") {
		return 10;
	}
	else if (a == "do") {
		return 11;
	}
	else if (a == "int") {
		return 12;
	}
	else if (a == "flat") {
		return 13;
	}
	else if (a == "bool") {
		return 14;
	}
	else if (a == "S") {
		return 0;
	}
	else if (a == "A") {
		return 1;
	}
	else if (a == "E") {
		return 2;
	}
	else if (a == "E'") {
		return 3;
	}
	else if (a == "T") {
		return 4;
	}
	else if (a == "T'") {
		return 5;
	}
	else if (a == "F") {
		return 6;
	}
	else if (a == "C") {
		return 7;
	}
	else if (a == "R") {
		return 8;
	}
	else if (a == "D") {
		return 9;
	}
	else if (a == "TY") {
		return 10;
	}
	else if (a == "M") {
		return 11;
	}
	return -1;
}

string convertTerminalToLetter(string a, string b) { //convert tokens in the array list to terminals
	if (a == "Identifier") {
		return "id";
	}
	else if (a == "Operator") {
		if (b == "+") {
			return "+";
		}
		else if (b == "-") {
			return "-";
		}
		else if (b == "*") {
			return "*";
		}
		else if (b == "/") {
			return "/";
		}
		else if (b == "<") {
			return "<";
		}
		else if (b == "<=") {
			return "<=";
		}
		else if (b == "==") {
			return "==";
		}
		else if (b == ">=") {
			return ">=";
		}
		else if (b == ">") {
			return ">";
		}
	}
	else if (a == "Separator") {
		if (b == "(") {
			return "(";
		}
		else if (b == ")") {
			return ")";
		}
		else if (b == "@") {
			return "@";
		}
		else if (b == ";") {
			return ";";
		}
		else if (b == ",") {
			return ",";
		}
		else if (b == "{") {
			return "{";
		}
		else if (b == "}") {
			return "}";
		}
	}
	else if (a == "Keyword") {
		if (b == "int") {
			return "int";
		}
		else if (b == "flow") {
			return "flow";
		}
		else if (b == "bool") {
			return "bool";
		}
		else if (b == "if") {
			return "if";
		}
		else if (b == "else") {
			return "else";
		}
		else if (b == "while") {
			return "while";
		}
		else if (b == "do") {
			return "do";
		}
	}
	return "-";
}

void lexer(char arr[], int size) {//takes an array of the code and the size of the array
	counter = 0;
	int fsm[7][6] = { { 1, 3, 0, 4, 0, 5 },
	{ 1, 1, 1, 0, 2, 5 },
	{ 0, 0, 0, 0, 0, 5 },
	{ 0, 3, 0, 4, 2, 5 },
	{ 0, 4, 0, 0, 2, 5 },
	{ 5, 5, 5, 5, 5, 6 },
	{ 0, 0, 0, 0, 0, 0 } };
	string keyword[18] = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do",
		"doend", "for", "forend", "input", "output", "and", "or", "function" };
	int col;
	string save = "";

	for (int i = 0; i < size; i++) {
		if (isalpha(arr[i])) {//if the input is an alphabet
			col = 0;
			state = fsm[state][col];
			save = save + arr[i];//save the input to the string
		}
		else if (isdigit(arr[i])) {//if the input is a digit
			col = 1;
			state = fsm[state][col];
			save = save + arr[i];
		}
		else if (arr[i] == '$') {//if the input is a dollar sign
			col = 2;
			state = fsm[state][col];
			save = save + arr[i];
		}
		else if (arr[i] == '.') {//if the input is a dot
			col = 3;
			state = fsm[state][col];
			save = save + arr[i];
		}
		else if (arr[i] == '!') {//if the input is an exclamation point
			col = 5;
			state = fsm[state][col];
			save = save + arr[i];
		}
		//when the program gets a space, a semicolon, or other characters, it knows that it is the end of a lexeme, and it will check for the final state before moving to the going to the next state.
		//if the current state is a final state, it saves whatever is in string save to record array, and clears string save.
		//then it will go to the next state
		else if (arr[i] == ' ') {//if the input is a space
			if (state == 0) {
				tokenRecord[counter] = "Operator";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
			}
			else if (state == 1) {//check if the current state is a final state for identifier
				tokenRecord[counter] = "Identifier";
				for (int i = 0; i < 18; i++) {//check for keyword
					if (save == keyword[i]) {
						tokenRecord[counter] = "Keyword";
					}
				}
				lexemeRecord[counter] = save;
				save = "";//clear the string save
				counter++;
			}
			else if (state == 3) {//check if the current state is a final state for integer
				tokenRecord[counter] = "Integer";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
			}
			else if (state == 4) {//check if the current state is a final state for real number
				tokenRecord[counter] = "Real Number";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
			}
			else if (state == 5) {//if the current state is in 5, delete everything in string save
				save = "";
			}
			col = 4;
			state = fsm[state][col];//go to the next state
		}
		else if (arr[i] == ';') {//if the space is a semicolon
			if (state == 0) {//check if the current state is a final state for operator
				tokenRecord[counter] = "Operator";
				lexemeRecord[counter] = save;//save the lexeme to record
				counter++;
				save = "";//clear string save
				tokenRecord[counter] = "Separator";
				lexemeRecord[counter] = arr[i];//save the semicolon to record
				counter++;
			}
			else if (state == 1) {//check if the current state is a final state for identifier
				tokenRecord[counter] = "Identifier";
				for (int i = 0; i < 18; i++) {//check for identifier
					if (save == keyword[i]) {
						tokenRecord[counter] = "Keyword";
					}
				}
				lexemeRecord[counter] = save;
				save = "";
				counter++;
				tokenRecord[counter] = "Separator";
				lexemeRecord[counter] = arr[i];
				counter++;
			}
			else if (state == 3) {//check if the current state is a final state for integer
				tokenRecord[counter] = "Integer";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
				tokenRecord[counter] = "Separator";
				lexemeRecord[counter] = arr[i];
				counter++;
			}
			else if (state == 4) {//check if the current state is a final state for real number
				tokenRecord[counter] = "Real Number";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
				tokenRecord[counter] = "Separator";
				lexemeRecord[counter] = arr[i];
				counter++;
			}
			else if (state == 5) {//if the current state is in 5, delete everything in string save
				save = "";
			}
			col = 4;
			state = fsm[state][col];
		}
		else {//anything other than a letter, digit, money sign, digit, space, and semicolon
			if (state == 0) {//check if the current state is a final state for operator or separator
				if (arr[i] == '*' || arr[i] == '+' || arr[i] == '-' || arr[i] == '=' ||
					arr[i] == '/' || arr[i] == '>' || arr[i] == '<' || arr[i] == '%') {
					save = save + arr[i];
				}
				else if (arr[i] == 39 || arr[i] == 40 || arr[i] == 41 || arr[i] == 123 || arr[i] == 125 ||
					arr[i] == 91 || arr[i] == 93 || arr[i] == 44 || arr[i] == 46 || arr[i] == 58 ||
					arr[i] == 59 || arr[i] == 33) {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = arr[i];
					counter++;
				}
			}
			else if (state == 1) {//check if the current state is a final state for identifier
				tokenRecord[counter] = "Identifier";
				for (int i = 0; i < 18; i++) {
					if (save == keyword[i]) {
						tokenRecord[counter] = "Keyword";
					}
				}
				lexemeRecord[counter] = save;
				save = "";
				counter++;
				if (arr[i] == '*' || arr[i] == '+' || arr[i] == '-' || arr[i] == '=' ||
					arr[i] == '/' || arr[i] == '>' || arr[i] == '<' || arr[i] == '%') {
					save = save + arr[i];
				}
				else if (arr[i] == 39 || arr[i] == 40 || arr[i] == 41 || arr[i] == 123 || arr[i] == 125 ||
					arr[i] == 91 || arr[i] == 93 || arr[i] == 44 || arr[i] == 46 || arr[i] == 58 ||
					arr[i] == 59 || arr[i] == 33) {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = arr[i];
					counter++;
				}
			}
			else if (state == 2) {//check if the current state is a final state for operator or separator
								  //this only happens if there is a space before the operator or separator
				if (arr[i] == '*' || arr[i] == '+' || arr[i] == '-' || arr[i] == '=' ||
					arr[i] == '/' || arr[i] == '>' || arr[i] == '<' || arr[i] == '%') {
					save = save + arr[i];
				}
				else if (arr[i] == 39 || arr[i] == 40 || arr[i] == 41 || arr[i] == 123 || arr[i] == 125 ||
					arr[i] == 91 || arr[i] == 93 || arr[i] == 44 || arr[i] == 46 || arr[i] == 58 ||
					arr[i] == 59 || arr[i] == 33) {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = arr[i];
					counter++;
				}
			}
			else if (state == 3) {//check if the current state is a final state for integer
				tokenRecord[counter] = "Integer";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
				if (arr[i - 1] == '*' || arr[i - 1] == '+' || arr[i - 1] == '-' || arr[i - 1] == '=' ||
					arr[i - 1] == '/' || arr[i - 1] == '>' || arr[i - 1] == '<' || arr[i - 1] == '%') {
					save = save + arr[i];
				}
				else {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = arr[i];
					counter++;
				}
			}
			else if (state == 4) {//check if the current state is a final state for real number
				tokenRecord[counter] = "Real Number";
				lexemeRecord[counter] = save;
				counter++;
				save = "";
				if (arr[i - 1] == '*' || arr[i - 1] == '+' || arr[i - 1] == '-' || arr[i - 1] == '=' ||
					arr[i - 1] == '/' || arr[i - 1] == '>' || arr[i - 1] == '<' || arr[i - 1] == '%') {
					save = save + arr[i];
				}
				else {
					tokenRecord[counter] = "Separator";
					lexemeRecord[counter] = arr[i];
					counter++;
				}
			}
			else if (state == 5) {//if the current state is in 5, delete everything in string save
				save = "";
			}
			col = 4;
			state = fsm[state][col];//go to the next state
		}
	}
}