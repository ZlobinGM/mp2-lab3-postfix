#include "postfix.h"
#include "stack.h"
#include <vector>
#include <sstream>

string TPostfix::ToNormalForm()
{
	string normal(infix);
	string numbers = "1234567890.";
	if (infix[0] == '-' || infix[0] == '+')normal.insert(0, "0");
	for (int i = 1; i < normal.length; i++) {
		if (normal[i] != ' ') {
			if (normal[i - 1] == ' ') continue;
			normal.insert(i++, " ");
			while (((normal[i] >= 'a' && normal[i] <= 'z') || numbers.find(normal[i]) != string::npos) 
				&& i < normal.length) i++;
		}
	}
	unsigned int i = 0;
	while ((i = normal.find("( +")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("( -")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("+ )")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("- )")) != string::npos) normal.insert(i + 1, " 0");
	return normal;
}

int TPostfix::Priority(const string& str)
{
	if (str == "(")	return 0;
	if (str == ")")	return 1;
	if (str == "+" || str == "-") return 2;
	if (str == "*" || str == "/") return 3;
	throw "get_priority_for_not_an_operation";
}

void TPostfix::SetInfix(const string& str)
{
	if (str == infix)return;
	infix = str;
	postfix = "";
	correct = -1;
}

bool TPostfix::IsCorrect()
{
	if (correct != -1)return correct;
	return false;
}

string TPostfix::ToPostfix()
{
	if (!IsCorrect()) throw "not_correct";

	stringstream s(ToNormalForm());
	vector<string> v;
	string tmp;
	while (s >> tmp) v.push_back(tmp);

	string operations = "+-*/()";
	TStack<string> st(20);

	for (int i = 0; i < v.size; i++)
	{
		if (operations.find(v[i]) == string::npos) postfix += v[i] + ' ';
		else
		{
			if (v[i] == "(") st.Push(v[i]);
			else if (v[i] == ")") {
				while (st.Top() != "(") postfix += st.Pop() + ' ';
				st.Pop;
			}
			else {
				if (st.IsEmpty()) st.Push(v[i]);
				else {
					while (Priority(v[i]) <= Priority(st.Top())) postfix += st.Pop() + ' ';
					st.Push(v[i]);
				}
			}
		}
	}

	while (!st.IsEmpty())postfix += st.Pop() + ' ';
	return postfix;
}

double TPostfix::Calculate()
{
  return 0;
}
