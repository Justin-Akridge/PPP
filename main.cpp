#include <iostream>
#include <string>
#include "token-stream.h"

double expression();
double term(Token_stream);
double primary(Token_stream);

void error(std::string message) {
  std::cerr << message << '\n';
}

double primary(Token_stream ts) {
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

double term(Token_stream ts) {
    double left = primary(ts);
    Token t = ts.get();
    while (true) {
        switch(t.kind) {
            case '*':
                left *= primary(ts);
                break;
            case '/':
            {
                double d = primary(ts);
                if (d == 0) {
                    error("Cannot divide by 0\n");
                    break;
                }
                left /= d;
                break;
            }
            default: 
                ts.putback(t);
                return left;
        }
        t = ts.get();
    }
}

double expression(Token_stream ts) {
  double left = term(ts);
  Token t = ts.get();
  while(true) {
    switch(t.kind) {
      case '+':
        left += term(ts);
        break;
      case '-':
        left -= term(ts);
        break;
      default: 
        ts.putback(t);
        return left;
    }
    t = ts.get();
  }
  return left;
}

int main() {
  try {
    Token_stream ts;
    double val = 0;
    while (std::cin) {
      Token t = ts.get();
      if (t.kind == 'q') break;
      if (t.kind == ';') std::cout << "=" << val << '\n';
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
