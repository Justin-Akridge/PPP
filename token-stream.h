#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

class Token_stream {
public:
  Token_stream();
  Token get();
  void putback(Token t);

private:
  bool full;
  Token buffer;
};
#endif //TOKEN_STREAM_H
