#include <iostream>
#include <string>


/* Grammer:
 *
 * Expression:
 *    Term
 *    Expression '+' Term
 *    Expression '-' Term
 * Term
 *    Primary
 *    Term '*' Primary
 *    Term '/' Primary
 *    Term '%' Primary
 * Primary:
 *    Number
 *    '(' Expression ')'
 * Number:
 *    Floating point-literal
 */

class Token {
public:
  Token(char ch) : kind(ch), val(0) {}
  Token(char ch, double value) : kind(ch), val(value) {}
  char kind;
  double val;
};

Token get_token();
double expression();
double term();
double primary();

double expression() {
  double left = term();
  Token t = get_token();
  while (true) {
    switch (t.kind) {
      case '+':
        left += term();
        t = get_token();
        break;
      case '-':
        left -= term();
        t = get_token();
        break;
      default:
        return left;
    }
  }
}

//deals with *, /, and %
double term() {
  double left = primary();
  Token t = get_token();
  while (true) {
    switch (t.kind) {
      case '*':
        left *= primary();
        t = get_token();
        break;
      case '/':
        {
          double d = primary();
          if (d == 0) {
            exit(1);
            std::cerr << "Cannot divide by zero";
          }
          left /= d;
          t = get_token();
          break;
        }
      default:
        return left;
    }
  }
}

//deals with numbers and ()
double primary() {
  Token t = get_token();
  while (true) {
    switch (t.kind) {
      case '(':
        {
          double d = expression();
          t = get_token();
          if (t.kind != ')') {
            std::cerr << "Error: ')' expected";
            exit(1);
          }
          return d;
        }
        break;
      case '8':
        return t.val;
      default:
        std::cerr << "primary expected";
        exit(1);
    }
  }
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
