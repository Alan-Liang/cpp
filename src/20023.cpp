#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>


char c = -2;
auto getcc () -> char {
  if (c != -2) {
    char ch = c;
    c = -2;
    return ch;
  }
  return getchar();
}
auto ungetcc (char ch) -> void {
  c = ch;
}

struct Token {
  virtual ~Token () {}
};
struct NumberToken : public Token {
  int value;
  NumberToken (int value) : value(value) {}
};
struct OperatorToken : public Token {
  enum Type { kAdd, kSub, kXor };
  Type type;
  OperatorToken (Type type) : type(type) {}
};
struct ParenToken : public Token {
  enum Type { kStart, kEnd };
  Type type;
  ParenToken (Type type) : type(type) {}
};

auto nextToken () -> Token * {
  char c = getcc();
  if (c == EOF || c == '\n') return nullptr;
  if (c == '+') return new OperatorToken{OperatorToken::kAdd};
  if (c == '-') return new OperatorToken{OperatorToken::kSub};
  if (c == '^') return new OperatorToken{OperatorToken::kXor};
  if (c == '(') return new ParenToken{ParenToken::kStart};
  if (c == ')') return new ParenToken{ParenToken::kEnd};
  int i = 0;
  while (std::isdigit(c)) {
    i = i * 10 + c - '0';
    c = getcc();
  }
  ungetcc(c);
  return new NumberToken(i);
}
auto scan2 () -> int;
auto scan1 () -> int {
  Token *token = nextToken();
  int value;
  if (dynamic_cast<ParenToken *>(token)) value = scan2();
  else value = ((NumberToken *)token)->value;
  while (true) {
    token = nextToken();
    if (!token) {
      ungetcc('\n');
      return value;
    }
    int value2;
    if (auto x = dynamic_cast<ParenToken *>(token)) {
      if (x->type == ParenToken::kEnd) {
        ungetcc(')');
        return value;
      }
    }
    if (auto x = dynamic_cast<OperatorToken *>(token)) {
      if (x->type == OperatorToken::kXor) {
        ungetcc('^');
        return value;
      }
      token = nextToken();
      if (auto y = dynamic_cast<NumberToken *>(token)) {
        value2 = y->value;
      }
      if (dynamic_cast<ParenToken *>(token)) value2 = scan2();
      if (x->type == OperatorToken::kAdd) value += value2;
      else value -= value2;
    }
  }
}

auto scan2 () -> int {
  int value = scan1();
  while (true) {
    Token *token = nextToken();
    if (!token || dynamic_cast<ParenToken *>(token)) return value;
    int value2 = scan1();
    value ^= value2;
  }
}

auto main () -> int {
  printf("%d\n", scan2());
  return 0;
}

