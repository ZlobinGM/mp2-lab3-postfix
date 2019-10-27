#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  getline(cin,expression);
  cout << expression << endl;
  postfix.SetInfix(expression);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  try { postfix.ToPostfix(); }
  catch (const char* exception) {
	  if (exception == "not_correct") {
		  cout << "Некоректное выражение: " << postfix.GetInfix() << endl;
		  return 0;
	  }
  }
  cout << "Нормализованная инфиксная форма: " << postfix.GetInfix() << endl;
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;

  return 0;
}
