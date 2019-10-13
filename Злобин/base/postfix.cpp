#include "postfix.h"
#include "stack.h"

void TPostfix::SetInfix(const string& str)
{
	if (str == infix)return;
	infix = str;
	postfix = "";
}

bool TPostfix::IsCorrect()
{
	if (correct != -1)return correct;
	return false;
}

string TPostfix::ToPostfix()
{
	if (!IsCorrect()) throw "not_correct";
	string operations = "+-*/^()";
	TStack<char> st(20);
	int postfix_index = 0;
	postfix.resize(infix.length);
	for (int i = 0; i < infix.length; i++)
	{
		if (infix[i] == ' ')continue;
		else if (operations.find(infix[i]) == string::npos)
			postfix[postfix_index++] = infix[i];
		else if (infix[i] == '(') st.Push(infix[i]);
		else if (infix[i] == '(');

	}
}

double TPostfix::Calculate()
{
  return 0;
}
