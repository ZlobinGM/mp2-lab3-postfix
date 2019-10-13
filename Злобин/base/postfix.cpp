#include "postfix.h"
#include "stack.h"

void TPostfix::SetInfix(const string& str)
{
	if (str == infix)return;
	infix = str;
	postfix = "";
}

string TPostfix::ToPostfix()
{
  postfix = string("ab+");
  return postfix;
}

double TPostfix::Calculate()
{
  return 0;
}
