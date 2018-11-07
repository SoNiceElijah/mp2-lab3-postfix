#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  bool TryParce(string s, double* res);
public:
  TPostfix()
  {
    infix = "a +2*( 3-2)-4 ";
  }
  TPostfix(string exp)
  {
	  infix = exp;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix(string s = "...");
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
