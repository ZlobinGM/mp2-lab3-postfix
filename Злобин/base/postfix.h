#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int correct;

	string ToNormalForm();
	int Priority(const string& str);
	bool IsDigit(const string& str);
public:
	TPostfix(const string& str = "") : infix(str), postfix(""), correct(-1) { }
	void SetInfix(const string& str);

	bool IsCorrect();
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }

	string ToPostfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
