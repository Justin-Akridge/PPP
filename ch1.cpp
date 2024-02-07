// Example program
#include <iostream>
#include <string>
#include <vector>

class Token {
public:
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, int val) : kind(ch), value(val) {}
    
    char kind;
    double value;
};

void error(std::string message) {
    std::cout << message << std::endl;
}

double expression();

std::vector<Token> tok;

double primary() {
    Token t = ts.get();
    switch(t.kind) {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("Expected ')'");
            return d;
        }
        case '8':
            return t.value;
        default:
            error("primary expected");
    }
    return 0;
}

double term() {
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch(t.kind) {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0) {
                    error("Cannot divide by 0\n");
                    break;
                }
                left /= d;
                break;
            }
            default: 
                ts.put_back(t);
                return left;
        }
        t = ts.get();
    }
}

double expression() {
    double left = term();
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default: 
                ts.put_back(t);
                return left;
        }
        t = ts.get();
    }
    return left;
}

int main() {
    try {
        double val = 0;
        while (std::cin) {
            Token t = ts.get();
            if (t.kind == 'q') break;
            if (t.kind = ';') std::cout << "=" << val << '\n';
            else ts.putback(t);
            val = expression();
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "exception \n";
        return 2;
    }
}