#include "postfix.h"
#include "stack.h"
#include <iostream>

string TPostfix::ToPostfix(string localInfix)
{
	bool top = false;
	//Если не рекурсия
	if (localInfix == "...")
	{
		top = true;
		localInfix = infix;

		//Чистим строку от пробелов
		int i;
		while ((i = localInfix.find(' ')) != string::npos)
			localInfix.erase(i, 1);
		
	}

	//Если есть скобки по краям, то убираем их
	if(localInfix[0] == '(' && localInfix[localInfix.length()-1]==')')
		localInfix = localInfix.substr(1,localInfix.length()-2);

	int operatorIndex = -1;
	bool insideBrackets = false;

	char triggers[] = { '+','-' };

	//Посчитаем цикл
	int j = 0;
	
	do
	{
		//Ищем самые низкие по приоритету операторы, игнорируя скобки
		for (int i = 0; i < localInfix.length(); i++)
		{
			if (localInfix[i] == '(') {
				insideBrackets = true;
				continue;
			}
			if (localInfix[i] == ')') {
				insideBrackets = false;
				continue;
			}
			if (((localInfix[i] == triggers[0]) || (localInfix[i] == triggers[1])) && !insideBrackets)
			{
				operatorIndex = i;
				break;
			}			
		}

		//Вдруг не нашли, тогда надо проверить эти операторы
		triggers[0] = '*';
		triggers[1] = '/';

		j++;

	} while (operatorIndex == -1 && j != 2);

	//Если вышли из цикла, но все еще внутри скобок, то видимо кто-то скобки направильно поставил 
	if (insideBrackets)
		throw "Error";

	//Все еще не нашли
	if (operatorIndex == -1)
		//Кажется это просто число
		return localInfix;

	string res = ToPostfix(localInfix.substr(0, operatorIndex)) + " " + ToPostfix(localInfix.substr(operatorIndex + 1, localInfix.length() - operatorIndex)) + " " + localInfix[operatorIndex];
	
	if (top)
	{
		res += " ";
		postfix = res ;
	}

	return res;

}

double TPostfix::Calculate()
{
	TStack<double> stack(postfix.length());
	int index = 0;

	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == ' ')
		{
			string token = postfix.substr(index, i - index);
			index = i + 1;

			//Если оператор

			if (token.length() == 1 && (token[0] > 39 && token[0] < 48))
			{
				double t2 = stack.Pop(), t1 = stack.Pop();

				switch (token[0])
				{
				case '*':
					stack.Push(t1 * t2);
					break;
				case '/':
					if (t2 == 0)
						throw "Dividing by Zero";
					stack.Push(t1 / t2);
					break;
				case '+':
					stack.Push(t1 + t2);
					break;
				case '-':
					stack.Push(t1 - t2);
					break;
				}

				continue;
			}

			//Если переменая
			if (token.length() == 1 && (token[0] > 96 && token[0] < 123)
				|| (token[0] > 64 && token[0] < 91))
			{
				string param = "";
				cout << token[0] << " = ";
				cin >> param;

				double res;
				if (TryParce(param, &res))
					stack.Push(res);

				continue;
			}

			//Кажется цифра;
			double res;
			if (TryParce(token, &res))
				stack.Push(res);

		}
	}

	return stack.Pop();
}

bool TPostfix::TryParce(string s, double* res)
{
	double form;

	*res = 0;

	string integer;
	string neInteger = "";

	int index;
	if ((index = s.find(".")) == string::npos)
		integer = s;
	else
	{
		integer = s.substr(0, index);
		neInteger = s.substr(index + 1, s.length() - index);
	}

	form = 1;
	for (int i = integer.length() - 1; i >= 0; i--)
	{
		*res += (integer[i] - '0') * form;
		form *= 10;
	}

	form = 0.1;
	for (int i = 0; i < neInteger.length(); i++)
	{
		*res += (neInteger[i] - '0') * form;
		form *= 0.1;
	}

	return true;
}
