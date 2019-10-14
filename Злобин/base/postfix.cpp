#include "postfix.h"
#include "stack.h"

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
			i--;
		}
	}
	unsigned int i = 0;
	while ((i = normal.find("  ")) != string::npos) normal.insert(i + 1, " ");
	while ((i = normal.find("( +")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("( -")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("+ )")) != string::npos) normal.insert(i + 1, " 0");
	while ((i = normal.find("- )")) != string::npos) normal.insert(i + 1, " 0");
	return normal;
}

int TPostfix::Priority(const string& str)
{
	switch (str[0])
	{
		case '(': return 0;
		case ')': return 1;
		case '+': 
		case '-': return 2;
		case '*':
		case '/': return 3;
	default:
		throw "get_priority_for_not_an_operation";
	}
	return -1;
}

bool TPostfix::IsDigit(const string & str)
{
	try { stod(str); }
	catch (invalid_argument) { return false; }
	return true;
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
	if (infix[infix.length - 1] == '-' || infix[infix.length - 1] == '+') { correct = 0; return correct; }

	short braket_flag = 0, operation_after_operation_flag = 0;

	string operation = "+-*/";

	for (int i = 0; i < infix.length; i++) {
		if (operation.find(infix[i]) == string::npos) operation_after_operation_flag = 0;
		else
			if (++operation_after_operation_flag == 2) {
				correct = 0; return correct;
			}

		if (infix[i] == '(') braket_flag++;
		if (infix[i] == ')')
			if (--braket_flag < 0) {
				correct = 0; return correct;
			}
	}
	if (braket_flag > 0)	correct = 0;

	if (correct == -1) correct = 1;
	return correct;
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
	if (postfix == "") throw "not_postfix_form";
	stringstream s(postfix);
	vector<string> v;
	string tmp;
	while (s >> tmp) v.push_back(tmp);

	string operations = "+-*/";
	for (int i = 0; i < v.size; i++)
		if (operations.find(v[i]) == string::npos && !IsDigit(v[i])) {
			string tmp(v[i]);
			cout << "Введите значение переменной " << v[i] << " = ";
			do { cin >> v[i]; } while (!IsDigit(v[i]));
			for (int j = i; j < v.size; j++)
				if (v[j] == tmp) v[j] = v[i];
		}

	double res = 0;
	TStack<double> st(20);
	for (int i = 0; i < v.size; i++) {
		if (operations.find(v[i]) == string::npos)
			st.Push(stod(v[i]));
		else {
			switch (v[i][0])
			{
			case '+': st.Push(st.Pop() + st.Pop()); break;
			case '-': double tmp = st.Pop();
				st.Push(st.Pop() - tmp); break;
			case '*': st.Push(st.Pop() * st.Pop()); break;
			case '/': double tmp = st.Pop();
				st.Push(st.Pop() / tmp); break;
			default:
				break;
			}
		}
	}
	return res = st.Pop();
}
