class Token {
public:
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, int val) : kind(ch), value(val) {}
    
    char kind;
    double value;
};
