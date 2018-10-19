#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cctype>
#include <deque>
#include <map>
using namespace std;

// All tokens must derive from this token type
class base_token
{
	public:
		typedef enum {t_invalid_token=0, t_symbol,
				t_integer, t_literal,
				t_constant, t_punctuation,
				t_whitespace, t_eol, t_indent, t_dedent, t_eof
	        } type_of_token;
	private:
		type_of_token token_type;
	public:
		base_token(type_of_token token) : token_type(token) { };
        int get_token_type();
		virtual string get_token_value() = 0;
		virtual int parse_token(fstream& stream, int input_char) = 0;
		virtual void print_token() = 0;
};

int base_token::get_token_type() {
    return token_type;
}

// A token that may contain a symbol
class symbol_token : public base_token
{
	private:
		string symbol;
	public:
		symbol_token() : base_token(t_symbol) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string symbol_token::get_token_value() {
    return symbol;
};

// A token that represents an integer
class integer_token : public base_token
{
	private:
		string integer_string;
	public:
		integer_token() : base_token(t_integer) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string integer_token::get_token_value() {
    return integer_string;
};

// A token that represents a literal
class literal_token : public base_token
{
	private:
		string literal_string;
	public:
		literal_token() : base_token(t_literal) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string literal_token::get_token_value() {
    return literal_string;
};

// A token that represents a constant literal (e.g. 'A')
class constant_token : public base_token
{
	private:
		string constant_string;
	public:
		constant_token() : base_token(t_constant) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string constant_token::get_token_value() {
    return constant_string;
};

// A token that represents a punctuation or separator
class punctuation_token : public base_token
{
	private:
		string punctuation_string;
	public:
		punctuation_token() : base_token(t_punctuation) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string punctuation_token::get_token_value() {
    return punctuation_string;
};

// A token that represents whitespace
class whitespace_token : public base_token
{
	public:
		whitespace_token() : base_token(t_whitespace) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string whitespace_token::get_token_value() {
    return "0";
};

// A token that represents an eol
class eol_token : public base_token
{
	public:
		eol_token() : base_token(t_eol) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string eol_token::get_token_value() {
    return "0";
};

// A token that represents an indent
class indent_token : public base_token
{
    private:
        int indent_level;
	public:
		indent_token(int current_indent) : base_token(t_indent) {
            indent_level = current_indent;
        };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string indent_token::get_token_value() {
    return "0";
};

// A token that represents an dedent
class dedent_token : public base_token
{
    private:
        int dedent_level;
	public:
		dedent_token(int current_indent) : base_token(t_dedent) {
            dedent_level = current_indent;
        };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string dedent_token::get_token_value() {
    return "0";
};

// A token that represents an eof
class eof_token : public base_token
{
	public:
		eof_token() : base_token(t_eof) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string eof_token::get_token_value() {
    return "0";
};

// A token that represents an illegal character
class invalid_token : public base_token
{
	private:
		int invalid_character;
	public:
		invalid_token() : base_token(t_invalid_token) { };
        string get_token_value();
		int parse_token(fstream& stream, int input_char);
		void print_token();
};

string invalid_token::get_token_value() {
    return "0";
};

// The C++ token parser
class token_parser
{
	private:
		fstream& source_stream;
		list<base_token *> token_list;
	public:
		token_parser(fstream& stream) : source_stream(stream) { };
        //vector<pair<int, string> > get_token_vector();
        deque<pair<int,string>> get_token_vector();
		bool parse_tokens();
		void print_tokens();
};
/*
vector<pair<int, string> > token_parser::get_token_vector() {
    vector<pair<int, string> > token_vector;
	list<base_token *>::iterator iterator;
	iterator = token_list.begin();
	while(iterator != token_list.end()) {
        pair<int, string> p = make_pair((*iterator)->get_token_type(), (*iterator)->get_token_value());
        token_vector.push_back(p);
		++iterator;
	}
    return token_vector;
};
*/
deque<pair<int, string>> token_parser::get_token_vector(){
    deque<pair<int, string>> token_vector;
    list<base_token *>::iterator iterator;
    iterator = token_list.begin();
    pair<int,string> p;
    while(iterator != token_list.end()){
        p = make_pair((*iterator)->get_token_type(), (*iterator)->get_token_value());
        token_vector.push_back(p);
        ++iterator;
    }
    return token_vector;
}

// parse the rest of a symbol
int symbol_token::parse_token(fstream& stream, int input_char) {
	symbol = input_char;
	while (true) {
		input_char = stream.get();
		if (isalpha(input_char) || isdigit(input_char) || input_char == '_') {
			symbol += input_char;
			continue;
		}
		return input_char;
	}
}

// print the token to cout
void symbol_token::print_token() {
	cout << "TOKEN[\"symbol\" , \"" << symbol << "\"]" << endl;
}

// parse the rest of an integer
int integer_token::parse_token(fstream& stream, int input_char) {
	integer_string = input_char;
	if (input_char == '0')
	{
		input_char = stream.peek();
		if (input_char == 'X' || input_char == 'x') {
			integer_string += input_char;
			input_char = stream.get();
			while (true) {
				input_char = stream.get();
				if (isxdigit(input_char)) {
					integer_string += input_char;
					continue;
				}
				return input_char;
			}
		}
	}
	while (true) {
		input_char = stream.get();
		if (isdigit(input_char)) {
			integer_string += input_char;
			continue;
		}
		return input_char;
	}
}

// print the token to cout
void integer_token::print_token() {
	cout << "TOKEN[\"integer\" , " << integer_string << "]" << endl;
}

// parse the rest of a literal
int literal_token::parse_token(fstream& stream, int input_char) {
	literal_string.clear();
	while (true) {
		input_char = stream.get();
		if (input_char == '\\') {
			input_char = stream.peek();
			if (input_char == '\"' || input_char == '\\') {
				literal_string += '\\';
				input_char = stream.get();
				literal_string += input_char;
				continue;
			}
			if (input_char == 0x0A) {
				cout << "error: EOL encountered before closing literal quotes" << endl;
				exit(0);
			}
			if (input_char == -1) {
				cout << "error: EOF encountered before closing literal quotes" << endl;
				exit(0);
			}
			literal_string += input_char;
			continue;
		}
		if (input_char != '\"' && input_char != -1) {
			literal_string += input_char;
			continue;
		}
		if (input_char == -1) {
			cout << "error: EOF encountered before closing literal quotes" << endl;
			exit(0);
		}
		input_char = stream.get();
		return input_char;
	}
}

// print the token to cout
void literal_token::print_token() {
	cout << "TOKEN[\"literal\" , \"" << literal_string << "\"]" << endl;
}

// parse the rest of a literal
int constant_token::parse_token(fstream& stream, int input_char) {
	constant_string.clear();
	while (true) {
		input_char = stream.get();
		if (input_char == '\\') {
			input_char = stream.peek();
			if (input_char == '\'' || input_char == '\\') {
				constant_string += '\\';
				input_char = stream.get();
				constant_string += input_char;
				continue;
			}
			constant_string += input_char;
			continue;
		}
		if (input_char != '\'') {
			constant_string += input_char;
			continue;
		}
		input_char = stream.get();
		return input_char;
	}
}

// print the token to cout
void constant_token::print_token() {
	cout << "TOKEN[\"constant literal\" , \"" << constant_string << "\"]" << endl;
}

// parse the rest of a punctuation sequence - this consists of
// ending up with either one, two or three characters in the
// punctuation string. NB: The sequence .. is accepted as a 
// punctuation token, but must be rejected by the compiler at
// some later stage.
int punctuation_token::parse_token(fstream& stream, int input_char) {
	punctuation_string = input_char;
	switch (input_char) {
	case '!': // Looking for either ! or !=
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // != token
		}
		break;
	case '#': // Looking for either # or ##
		input_char = stream.peek();
		if (input_char == '#') {
			input_char = stream.get();
			punctuation_string += input_char; // ## token
		}
		break;
	case '%': // Looking for either % or %=
		input_char = stream.peek();
		if (input_char == '=') {			
			input_char = stream.get();
			punctuation_string += input_char; // %= token
		}
		break;
	case '&': // Looking for either &, && or &=
		input_char = stream.peek();
		if (input_char == '&' || input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // && token
		}
		break;
	case '*': // Looking for either * or *=
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // *= token
		}
		break;
	case '+': // Looking for either +, ++, or +=
		input_char = stream.peek();
		if (input_char == '+' || input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // ++ or += token
		}
		break;
	case '-': // Looking for either -, --, -=, ->, ->*
		input_char = stream.peek();
		if (input_char == '-' || input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // -- or -= token
		}
		if (input_char == '>') {
			input_char = stream.get();
			punctuation_string += input_char; // -> token
			input_char = stream.peek();
			if (input_char == '*') {
				input_char = stream.get();
				punctuation_string += input_char; // ->* token
			}
		}
		break;
	case '.': // Looking for either ., .. or ...
		input_char = stream.peek();
		if (input_char == '.') {
			input_char = stream.get();
			punctuation_string += input_char; // .. token (illegal!)
			input_char = stream.peek();
			if (input_char == '.') {
				input_char = stream.get();
				punctuation_string += input_char; // ... token
			}
		}
		break;
	case '/': // Looking for either / or /=
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // /= token
		}
		break;
	case ':': // Looking for either : or ::
		input_char = stream.peek();
		if (input_char == ':') {
			input_char = stream.get();
			punctuation_string += input_char; // :: token
		}
		break;
	case '<': // Looking for either < or <=, <<, or <<=
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // <= token
			break;
		}
		if (input_char == '<') {
			input_char = stream.get();
			punctuation_string += input_char; // << token
			input_char = stream.peek();
			if (input_char == '=') {
				input_char = stream.get();
				punctuation_string += input_char; // <<= token
			}
		}
		break;
	case '=': // Looking for either = or ==
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // == token
		}
		break;
	case '>': // Looking for either >, >=, >>, or >>=
		input_char = stream.peek();
		if (input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // >= token
			break;
		}
		if (input_char == '>') {
			input_char = stream.get();
			punctuation_string += input_char; // >> token
			input_char = stream.peek();
			if (input_char == '=') {
				input_char = stream.get();
				punctuation_string += input_char; // >>= token
			}
		}
		break;
	case '|': // Looking for either |, |=, or || 
		input_char = stream.peek();
		if (input_char == '|' || input_char == '=') {
			input_char = stream.get();
			punctuation_string += input_char; // || or |= token
		}
		break;
	}
	input_char = stream.get();
	return input_char;
}

// print the token to cout
void punctuation_token::print_token() {
	cout << "TOKEN[\"punctuation\" , \"" << punctuation_string << "\"]" << endl;
}

// parse the whitespace characters
int whitespace_token::parse_token(fstream& stream, int input_char) {
	while (true) {
		input_char = stream.get();
		if (input_char == ' ' || input_char == 0x09 || input_char == 0x0B || input_char == 0x0D) {
			continue;
		}
		return input_char;
	}
}

// print the token to cout
void whitespace_token::print_token() {
	cout << "TOKEN[\"whitespace\" , \" \"]" << endl;
}

// parse the eol character
int eol_token::parse_token(fstream& stream, int input_char) {
	while (true) {
		input_char = stream.get();
		return input_char;
	}
}

// print the token to cout
void eol_token::print_token() {
	cout << "TOKEN[\"EOL\"]" << endl;
}

// parse the indent character
int indent_token::parse_token(fstream& stream, int input_char) {
	while (true) {
		input_char = stream.get();
		return input_char;
	}
}

// print the token to cout
void indent_token::print_token() {
	cout << "TOKEN[\"INDENT\": " << indent_level << "]" << endl;
}

// parse the dedent character
int dedent_token::parse_token(fstream& stream, int input_char) {
	while (true) {
		input_char = stream.get();
		return input_char;
	}
}

// print the token to cout
void dedent_token::print_token() {
	cout << "TOKEN[\"DEDENT\": " << dedent_level << "]" << endl;
}

// parse the eof character
int eof_token::parse_token(fstream& stream, int input_char) {
	return 0;
}

// print the token to cout
void eof_token::print_token(void) {
	cout << "TOKEN[\"EOF\"]" << endl;
}

// parse the invalid character
int invalid_token::parse_token(fstream& stream, int input_char) {
	invalid_character = input_char;
	input_char = stream.get();
	return input_char;
}

// print the token to cout
void invalid_token::print_token(void) {
	cout << "TOKEN[\"INVALID\"" << invalid_character << endl;
}

// parse the input source
bool token_parser::parse_tokens() {
	base_token * token;

    int current_indent = 0;

	while (!source_stream.eof()) {
		int input_char = source_stream.get();

		// Determine what the leading character is of the sequence,
		// create an appropriate token and get the actual token
		// class to parse the rest of it (if any)
		
		while (!source_stream.eof()) {
			// The following do loop is there only because I hate seeing
			// if () ... else if () ... else if () ... code!!!
			// Hence it's a do ... while ( false ) - single shot
			do
			{
				// Remove any comments from the source
				if (input_char == '#') {
					int peek_character = source_stream.peek();
                    while (peek_character != 0x0A && !source_stream.eof()) {
                        peek_character = source_stream.get();
                    }
                    token = new(nothrow) eol_token;
                    break;
				}
				if (isalpha(input_char) || input_char == '_') {
					// Start of a symbol sequence
					token = new(nothrow) symbol_token;
					break;
				}
				if (input_char == 0x0A) {
					// Handle newlines, indent, and dedent
                    int spaces = 0;
                    int p = source_stream.peek();
                    if (isspace(p)) {
                        int g = source_stream.get();
                        spaces++;
                        while (g != 0x0A && !source_stream.eof()) {
                            p = source_stream.peek();
                            if (isspace(p)) {
                                g = source_stream.get();
                                spaces++;
                            }
                            else {
                                break;
                            }
                        }
                    }
                    if (spaces > current_indent) {
                        current_indent = spaces;
                        token = new(nothrow) indent_token(current_indent);
                    }
                    else if (spaces < current_indent) {
                        current_indent = spaces;
                        token = new(nothrow) dedent_token(current_indent);
                    }
                    else {
                        token = new(nothrow) eol_token;
                    }
					break;
				}
				if (isspace(input_char)) {
					// Start of whitespace sequence
					token = new(nothrow) whitespace_token;
					break;
				}
				if (input_char == '\"') {
					// Start of literal sequence
					token = new(nothrow) literal_token;
					break;
				}
				if (input_char == '\'') {
					// Start of constant literal sequence
					token = new(nothrow) constant_token;
					break;
				}
				if (isdigit(input_char)) {
					// Start of number sequence
					token = new(nothrow) integer_token;
					break;
				}
				if (ispunct(input_char)) {
					// Start of punctuation sequence
					token = new(nothrow) punctuation_token;
					break;
				}
			}
			while (false);
			if (token == NULL) return false;
			input_char = token->parse_token(source_stream, input_char);
			// Add the token to the end of the list
			token_list.push_back(token);
			continue;
		}
	}
	// Add the EOF token to the end of the list
	token = new(nothrow) eof_token;
	token_list.push_back(token);
	return true;
}

// Simply iterate through the list of tokens and print them to cout
// Of course, get the token object to print itself :o)
void token_parser::print_tokens() {
	list<base_token *>::iterator iterator;
	iterator = token_list.begin();
	while(iterator != token_list.end()) {
		(*iterator)->print_token();
		++iterator;
	}
}

typedef enum {t_invalid_token=0, t_symbol,
	t_integer, t_literal,
	t_constant, t_punctuation,
	t_whitespace, t_eol, t_indent, t_dedent, t_output, t_eof
} t_type;

map <string, pair<int,string>> var_table;
map <string,string> arithmetic_table = {{"+","+"},{"-","-"},{"*","*"},{"/","/"}};
map <string, pair<int,string>> def_table;
map <string, string> key_table = {{"if","if"},{"return","return"},{"def","def"},{"print","print"}};

int evaluate(deque<pair<int,string>> &n);
deque<pair<int,string>> remove_whitespace(deque<pair<int,string>> tokens);
int eeval(deque<pair<int,string>> &tokens, deque<pair<int,string>> &eval);
int aeval(deque<pair<int,string>> &tokens, deque<pair<int,string>> &eval, pair<int,string> &a);
int peval(deque<pair<int,string>> &tokens, pair<int,string> &a);
pair<int,string> doArith(pair<int,string>,pair<int,string>,pair<int,string>);
int printeval(deque <pair<int,string>> &tokens, pair<int, string> &a);
int eval_line(deque<pair<int,string>> &eval);

deque<pair<int,string>> remove_whitespace(deque<pair<int,string>> tokens){
    deque<pair<int,string>> newtokens;
    while(!tokens.empty()){
        if(tokens.at(0).first != t_whitespace){
            newtokens.push_back(tokens.at(0));
            tokens.pop_front();
        }else{
            tokens.pop_front();
        }
    }
    return newtokens;
}

int evaluate(deque<pair<int,string>> &tokens){
    pair<int, string> t, temp;
    deque<pair<int,string>> eval;
    
    while(!tokens.empty()){
        t = tokens.at(0);
        tokens.pop_front();
        if(t.first == t_eol){
            cout<<"eol"<<endl;
            if(eval_line(eval) != 0)
                return -1;
            continue;
        }
        if(t.first == t_eof){
            cout << "eof"<<endl;
            if(eval_line(eval) != 0)
                return -1;
            break;
        }
        if(t.first == t_literal){
            if(eval.empty()){
                eval.push_back(t);
            }else{
                return -1;
            }
        }

        if(t.first == t_integer){
            if(eval.empty()){
                eval.push_back(t);
            }else if(tokens.at(0).first == t_punctuation){
                if(arithmetic_table.count(tokens.at(0).second) != 0){
                    if(aeval(tokens, eval, t) == 0){
                        eval.push_back(t);
                        continue;
                    }else{
                        return -1;
                    }
                }else{
                    return -1;
                }
            }else{
                return -1;
            }
        }

        if(t.first == t_symbol){
            cout << t.second << endl;
            if(var_table.count(t.second) > 0){
                if(tokens.at(0).first == t_punctuation && tokens.at(0).second == "="){
                    eval.push_back(t);
                }else{
                    eval.push_back(var_table.at(t.second));
                }
            }else if(key_table.count(t.second) > 0 && t.second == "print"){
                if(printeval(tokens, t) == 0){
                    eval.push_back(t);
                }else{
                    return -1;
                }
            }else{
                if(tokens.at(0).first == t_punctuation){
                    if(tokens.at(0).second == "="){
                        eval.push_back(t);
                    }else{
                        cout << "error" << endl;
                        return -1;
                    }
                }else{
                    return -1;
                }
            }
         }
         if(t.first == t_punctuation){
            if(t.second == "="){
                cout << "push back = " << endl;
                eval.push_back(t);
                if(eeval(tokens, eval) != 0)
                    return -1;
            }
         }


    }
    /*
    pair<int, string> b;
    b.first = 0;
    b.second = "hello";
    var_table.emplace("name",b );
    cout << var_table.at("name").second << endl;
    */
    for(auto &i : var_table)
        cout << i.first << " = " << i.second.second << endl;

    return 0;
}

int eval_line(deque<pair<int,string>> &eval){
    if(eval.size() == 0){
        cout << "nothing to evaluate!" << endl;
        return 0;
    }
    else if(eval.size() == 1){
        if(eval.at(0).first == t_output){
            cout << eval.at(0).second << endl;
            eval.pop_front();
        }else{
            cout << "single integer or literal" << endl;
            eval.pop_front();
        }
        return 0;
    }else{
        return -1;
    }

}

int eeval(deque<pair<int,string>> &tokens, deque<pair<int,string>> &eval){
    pair<int, string> t; 
    deque<pair<int,string>> a;

    while(tokens.at(0).first != t_eol && tokens.at(0).first != t_eof){
        t = tokens.at(0);
        tokens.pop_front();
        if(t.first == t_literal){
            eval.push_back(t);
            //todo check if prev is =
        }else if(t.first == t_integer){
            cout << "push back num" << endl;
            eval.push_back(t);
        }else if(t.first == t_punctuation){
            if(arithmetic_table.count(t.second) > 0){
                cout << "found a arith " << endl;
                if(eval.at(eval.size()-1).first == t_integer){
                    a.push_back(eval.at(eval.size()-1));
                    eval.pop_back();
                    a.push_back(t);
                    if(aeval(tokens, a, t) == 0){
                        cout << "foudn arith in assignment" << endl;
                        eval.push_back(t);
                    }else{
                        return -1;
                    }
                }else{
                    return -1;
                }
            }else{
                return -1;
            }
        }else{
            return -1;
        }
    }
    //Todo check to see if eval has only 3 items in it
    string name = eval.at(0).second;
    int type = eval.at(2).first;
    string value = eval.at(2).second;
    cout << "name = " << name << endl;
    if(var_table.count(eval.at(0).second) == 0){
        var_table.emplace(name, make_pair(type,value));
        cout << name << " = " << var_table.at(name).first << " " << var_table.at(name).second<< endl;
     }else{
         var_table.erase(name);
         var_table.emplace(name, make_pair(type,value));
     }

     while(!eval.empty()){
         eval.pop_front();
     }
     return 0;
}

int aeval(deque<pair<int,string>> &tokens, deque<pair<int,string>> &eval, pair<int,string> &a){
    pair<int, string> t; 
    cout << "in aeval" << endl;
    while(tokens.at(0).first != t_eol && tokens.at(0).first != t_eof && tokens.at(0).second != ")"){
        t = tokens.at(0);
        tokens.pop_front();       
        cout << t.first << "-" << t.second << endl;        
        if(t.first == t_punctuation){
            if(arithmetic_table.count(t.second) > 0){
                cout << "arith operator" << endl;
                eval.push_back(t);
            }else if(t.second == "("){
                if(peval(tokens, t) == 0){
                    eval.push_back(t);
                }else{
                    return -1;
                }
            }else{
                return -1;
            }
        }else if(t.first == t_symbol){
            if(var_table.count(t.second) != 0){
                if(var_table.at(t.second).first == t_integer){
                    cout << "a variable" << endl;
                    eval.push_back(var_table.at(t.second));
                }else{
                    return -1;
                }
            }else{
                return -1;
            }
        }else if(t.first == t_integer){
            cout << "an int" <<endl;
            eval.push_back(t);
        }else{
            return -1;
        }
    }
    cout << "out of the loop" << endl;
    int cint = 0, cart = 0;
    for(auto &i : eval){
        cout << i.second << " " << endl;
        if(i.first == t_integer){
            cint++;
        }else{
            cart++;
        }
    }
    cout << "checking number of values" << endl;
    if((cint-cart) > 1){
        cout << "too many ints" << endl;
        return -1;
    }else if ((cint-cart) < 1){
        cout << "too many arithmetic operators" << endl;
        return -1;
    }else{
        cint = 0;
        cart = 0;
    }
    cout << "done checking " << endl;
    deque<pair<int,string>> as, f;
    pair<int,string> n1, n2, o;

    while(!eval.empty()){
        t = eval.at(0);
        eval.pop_front();
        if(t.first == t_integer){
            n1 = t;
            as.push_back(n1);
        }else{
            o = t;
            as.push_back(o);
            if(o.second == "*" || o.second == "/"){
                n2 = eval.at(0);
                eval.pop_front();
            
                as.pop_back();
                as.pop_back();
            
                t = doArith(n1,n2,o);
                n1 = t;
                as.push_back(t);
            }
        }

    }
    for(auto &i : as)
        cout << i.second << " " << endl;
    while(!as.empty()){
        t = as.at(0);
        as.pop_front();
        if(t.first == t_integer){
            n1 = t;
            f.push_back(n1);
        }else{
            o = t;
            f.push_back(o);
            if(o.second == "-" || o.second == "+"){
                n2 = as.at(0);
                as.pop_front();
            
                f.pop_back();
                f.pop_back();
                cout << n1.second << " " << o.second << " " <<n2.second << endl; 
                t = doArith(n1,n2,o);
                cout << t.second << endl;
                n1 = t;
                f.push_back(t);
            }
        }

    }

    for(auto &i : f){
        cout << i.first << " - " << i.second << endl;
    }

    if(f.size()==1){
        a = f.at(0);
        cout << "result " << a.second << "endl";
    }else{
        cout << "error with arithmetic" << endl;
        return -1;
    }

    return 0;
}

pair<int,string> doArith(pair<int,string> n1,pair<int,string> n2, pair<int,string> o){
    pair<int,string> result;
    result.first = t_integer;
    int r = 0, t1 = 0, t2 = 0;
    t1 = stoi(n1.second);
    t2 = stoi(n2.second);
    if(o.second == "+")
       r = t1 + t2; 
    if(o.second == "-")
       r = t1 - t2; 
    if(o.second == "*")
       r = t1 * t2; 
    if(o.second == "/")
       r = t1 / t2; 

    result.second = to_string(r);
    return result;
}

int peval(deque<pair<int,string>> &tokens, pair<int,string> &a){
    pair<int, string> t;
    deque<pair<int,string>> eval;
    while(tokens.at(0).first != t_eol && tokens.at(0).first != t_eof){
        t = tokens.at(0);
        tokens.pop_front();
        if(t.first == t_integer){
            eval.push_back(t);
        }else if(t.first == t_symbol && var_table.count(t.second) > 0){
            if(var_table.at(t.second).first == t_integer){
                eval.push_back(t);
            }else{
                if(eval.empty()){
                    eval.push_back(t);
                }else{
                    return -1;
                }
            }
        }else if(t.first == t_punctuation && arithmetic_table.count(t.second) > 0){
            if(eval.empty()){
                return -1;
            }
            if(eval.at(eval.size()-1).first != t_integer){
                return -1;
            }else{
                eval.push_back(t);
                if(aeval(tokens, eval, t) == 0){
                    eval.push_back(t);
                }else{
                    return -1;
                }
            }
        }else if(t.first == t_punctuation && t.second == ")"){
            break;
        }else{
            return -1;
        }
    }

    if(eval.size() != 1){
        return -1;
    }else{
        a = eval.at(0);
        eval.pop_front();
        return 0;
    }
}
/*
int defeval(){
    
    string name,value;
    int type;
    pair<int,string> t;
    //probably better to put this crap in a array or something
    if(tokens.at(0).first != t_symbol){
        return -1;
    }

    t = tokens.at(0);
    tokens.pop_front();
    if(def_table.count(t.second) > 0){
        return -1;
    }
    tokens.pop_front();
    if(tokens.at(0).second != "("){
        return -1;
    }
    tokens.pop_front()
    if(tokens.at(0).second != ")"){
        return -1;
    }
    tokens.pop_front();
    if(tokens.at(0).second != ":"){
         return -1;
    }
    tokens.pop_front();
    if(tokens.at(0).first != t_eol){
        return -1;
    }
    tokens.pop_front();
    while(tokens.at(0).first != t_eof){
        t = tokens.at(0);
        tokens.pop_front();
        if(t.first == t_eol){
            if(eval_line(eval)==0){
                if(tokens.at(0).first != t_indent && tokens.at(0).first != t_dedent){
                    return -1;
                }
            }else{
                return -1;
            }
        }

        if(t.first == t_dedent){
            break;
        }

        if(t.first == t_indent){
            continue;
        }
        //symbol
        if(t.first == t_symbol){
            if(key_table.count(t.second) > 0){
                if(t.second == "if"){
                    if(ifeval(tokens, t) == 0){
                        if(t.first == t_output){
                            type = t.first;
                            value = value + t.second + "\n"; 
                        }
                    }else{
                        return -1;
                    }
                }else if(t.second == "return"){
                    if(tokens.at(0).first == t_literal){
                        t = tokens.at(0);
                        tokens.pop_front();
                        type = t.first;
                        value = t.second;
                        continue;
                    }else if(tokens.at(0).first == t_integer){
                        t = tokens.at(0);
                        tokens.pop_front();
                        type = t.first;
                        value = t.second;
                        continue;
                    }else if(tokens.at(0).first == t_symbol){
                        if(local_var_table.count(tokens.at(0).second) > 0){
                            t = tokens.at(0);
                            tokens.pop_front();
                            type = t.first;
                            value = t.second;
                            continue;
                        }else{
                            return -1;
                        }
                    }else{
                        return -1;
                    }
                }else if(t.second == "print"){
                    if(dprinteval(tokens, t) == 0){
                        type = t_output;
                        value = value + t.second + "\n";
                        continue;
                    }else{
                        return -1;
                    }
                }else{
                    return -1;
                }
            }else if(local_var_table.count(t.second) > 0){
                eval.push_back(t);
            }else{
                if(tokens.at(0).first != t_punctuation && tokens.at(0).second != "="){
                    return -1;
                }else{
                    deeval();
                }
            }
        }
        //end of symbol


    }
    
    
    
}
int ifeval(){return 0;}
*/
int printeval(deque <pair<int,string>> &tokens, pair<int, string> &a){
    pair<int, string> t;
    deque<pair<int,string>> eval;
    t = tokens.at(0);
    if(t.second != "(")
        return -1;
    tokens.pop_front(); 
    
    while(tokens.at(0).first != t_eol && tokens.at(0).first != t_eof){
        t = tokens.at(0);
        tokens.pop_front();

        if(t.first == t_punctuation && t.second == ","){
            if(eval.empty()){
                return -1;
            }

            if(eval.at(eval.size()-1).first != t_literal && eval.at(eval.size()-1).first != t_integer) {
                return -1;
            }else{
                eval.push_back(make_pair(t_whitespace, " "));
            }
        }else if(t.first == t_punctuation && t.second == ")"){
            break;
        }else if(t.first == t_literal){
            if(eval.empty()){
                eval.push_back(t);
            }else if(eval.at(eval.size()-1).second == ","){
                eval.push_back(t);
            }else{
                return -1;
            }
        }else if(t.first == t_integer){
            if(eval.empty()){
                eval.push_back(t);
            }else if(eval.at(eval.size()-1).second == ","){
                eval.push_back(t);
            }else{
                return -1;
            }
        }else if(t.first == t_symbol){
            if(var_table.count(t.second) > 0){
                eval.push_back(var_table.at(t.second));
            }else{
                return -1;
            }
        }else{
            return -1;
        }


    }


    a.first = t_output;
    if(eval.empty()){
        return -1;
    }

    for(auto &i : eval){
        a.second += i.second;
    }

    return 0;
}

void remove_empty_lines(const string& file_path)
{
    std::string buffer_string = "";

    std::fstream file_stream;
    std::string current_readline;
    file_stream.open(file_path, std::fstream::in); //open the file in input mode

    // read all the lines till the end of the file
    while(getline(file_stream, current_readline))
    {
        // check if the line is empty
        if(!current_readline.empty())
            buffer_string = buffer_string + current_readline + "\n";
    }
    file_stream.close();

    file_stream.open(file_path, std::fstream::out); //open file in Output mode. This line will delete all data inside the file.
    file_stream << buffer_string;
    file_stream.close();
}

// main program entry point
int main(int argc, char** argv) {
	// Check to see that we have at least a filename
	if (argc < 2) {
		cout << "Invalid number of arguments. Filename is required." << endl;
        return -1;
	}
	string filename = argv[argc-1];

    remove_empty_lines(filename);

	fstream source;

	// Open the source file
	source.open(filename.c_str(), ios_base::in);
	if (source.fail()) {
		cout << "An error occurred while opening " << filename << endl;
        return -1;
	}

	// Create the token list
	token_parser parser(source);
	parser.parse_tokens();
	parser.print_tokens();

    // token type (int), token value (string)
    // vector<pair<int, string> > token_vector = parser.get_token_vector();

    // deque<pair<int,string>> token_deque = parser.get_token_vector();
    // deque<pair<int,string>> tokens = remove_whitespace(token_deque);
    // for(auto &i : tokens){
    //     cout << i.first << " " << i.second << endl;
    // }
    // evaluate(tokens);
}
