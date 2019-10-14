#include "postfix.h"
#include "stack.h"

string TPostfix::ToNormalForm()							// Нормализация вида (ставить недостающие пробелы, убирать лишнии)
{
	if (normal) return infix;
	string numbers = "1234567890.";

	for (int i = 0; i < infix.length(); i++)			// Можно в начале ставить 0
		if (infix[i] != ' ') {
			if (infix[i] == '-' || infix[i] == '+')
				infix.insert(i, "0");
			else break;
		}

	infix.insert(0, " ");
	for (int i = 0; i < infix.length(); i++) {
		if(infix[i] == ' '){							// Убрать лишние пробелы
			int count = 1;
			while (infix[i + count] == ' ') count++;
			infix.replace(i, count, " ");
		}
		else if (infix[i] != ' ') {						// Перед каждой операцией, числом или переменной пробел
			if (i != 0 && infix[i - 1] != ' ') infix.insert(i++, " ");
			if (((infix[i] >= 'a' && infix[i] <= 'z') || numbers.find(infix[i]) != string::npos)
				&& i < infix.length()) {
				while (((infix[i] >= 'a' && infix[i] <= 'z') || numbers.find(infix[i]) != string::npos)
					&& i < infix.length()) i++;
				i--;
			}
		}
	}
	if(infix[0]==' ') infix.replace(0, 1, "");

	unsigned int i = 0;
	while ((i = infix.find("( +")) != string::npos) infix.insert(i + 1, " 0");
	while ((i = infix.find("( -")) != string::npos) infix.insert(i + 1, " 0");

	normal = 1;
	return infix;
}

int TPostfix::Priority(const string& str)				// Получить приоритет операции
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

bool TPostfix::IsDigit(const string & str)				// Определит является ли подстрока числом
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
	normal = 0;
}

bool TPostfix::IsCorrect()								// Контроль 3-х критериев правильности
{
	if (correct != -1)return correct;
	short braket_flag = 0, operation_after_operation_flag = 0;
	string operation = "+-*/";

	if (operation.find(infix[infix.length() - 1]) != string::npos) { correct = 0; return correct; }
	for (int i = 0; i < infix.length(); i++)			// Заканчивается не на операцию
		if (infix[i] != ' ') {							// Начинается не на операцию (кроме +, -)
			if (infix[i] == '*' || infix[i] == '/') { correct = 0; return correct; }
			else break;
		}

	for (int i = 0; i < infix.length(); i++) {
		if (operation.find(infix[i]) != string::npos) {
			if (++operation_after_operation_flag == 2) {
				correct = 0; return correct;			// Нет двух операций подряд
			}
		}	
		else if (infix[i] != ' ') operation_after_operation_flag = 0;

		if (infix[i] == '(') braket_flag++;
		if (infix[i] == ')')							// У каждой скобки есть пара
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

	stringstream s(ToNormalForm());						// Переход к вектору
	vector<string> v;
	string tmp;
	while (s >> tmp) v.push_back(tmp);

	string operations = "+-*/()";
	TStack<string> st(20);

	for (int i = 0; i < v.size(); i++)
	{
		if (operations.find(v[i]) == string::npos) postfix += v[i] + ' ';
		else
		{
			if (v[i] == "(") st.Push(v[i]);
			else if (v[i] == ")") {
				while (st.Top() != "(") postfix += st.Pop() + ' ';
				st.Pop();
			}
			else {
				if (st.IsEmpty()) st.Push(v[i]);
				else {
					while (!st.IsEmpty() && Priority(v[i]) <= Priority(st.Top())) postfix += st.Pop() + ' ';
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
	for (int i = 0; i < v.size(); i++)
		if (operations.find(v[i]) == string::npos && !IsDigit(v[i])) {
			string tmp(v[i]);
			cout << "Введите значение переменной " << v[i] << " = ";
			do { cin >> v[i]; } while (!IsDigit(v[i]));
			for (int j = i; j < v.size(); j++)
				if (v[j] == tmp) v[j] = v[i];
		}

	double res = 0;
	TStack<double> st(20);
	for (int i = 0; i < v.size(); i++) {
		if (operations.find(v[i]) == string::npos)
			st.Push(stod(v[i]));
		else {
			double tmp;
			switch (v[i][0])
			{
			case '+': st.Push(st.Pop() + st.Pop()); break;
			case '-': tmp = st.Pop();
				st.Push(st.Pop() - tmp); break;
			case '*': st.Push(st.Pop() * st.Pop()); break;
			case '/': tmp = st.Pop();
				if (tmp == 0)throw "divine_by_zero";
				st.Push(st.Pop() / tmp); break;
			default:
				break;
			}
		}
	}
	return res = st.Pop();
}
