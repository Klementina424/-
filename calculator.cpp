#include "calculator.h"
#include "math.h"
#include <iostream>


char Const(string oper, size_t index = 0) 
{
	if (oper[index] == 'p' && oper[index + 1] == 'i') 
		return 2;
	else if (oper[index] == 'e') //e
		return 1;
	return 0;
}

bool Number(string str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return true;
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
		return true;
	if (Const(str))
		return true;
	return false;
}

bool Operator(string oper, size_t index = 0, size_t ctrl = 0) // + - * / ^
{
	if (ctrl == 0 && oper[1] >= '0' && oper[1] <= '9')
		return false;
	if (oper[index] == '+' || oper[index] == '-' || oper[index] == '*' || oper[index] == '/' || oper[index] == '^')
		return true;
	return false;
}

char Func(string oper, size_t index = 0) 
{
	if (oper[index] == 't' && oper[index + 1] == 'g') return 2;
	else if (oper[index] == 'l' && oper[index + 1] == 'n') return 2;
	else if (oper[index] == 'c' && oper[index + 1] == 'o' && oper[index + 2] == 's') return 3;
	else if (oper[index] == 'c' && oper[index + 1] == 't' && oper[index + 2] == 'g') return 3;
	else if (oper[index] == 'l' && oper[index + 1] == 'o' && oper[index + 2] == 'g') return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'i' && oper[index + 2] == 'n') return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'q' && oper[index + 2] == 'r' && oper[index + 3] == 't') return 4;
	else if (oper[index] == 'a' && oper[index + 1] == 'r' && oper[index + 2] == 'c' && oper[index + 3] == 'c' && oper[index + 4] == 'o' && oper[index + 5] == 's') return 6;
	else if (oper[index] == 'a' && oper[index + 1] == 'r' && oper[index + 2] == 'c' && oper[index + 3] == 's' && oper[index + 4] == 'i' && oper[index + 5] == 'n') return 6;
	return 0;
}

void calculator::component(string input)
{
	string temp;
	for (size_t i = 0; i < input.size(); i++)
	{
		temp.clear();
		size_t control = 0;
		while (((input[i] >= 48 && input[i] <= 57) || (input[i] == ',')) && i < input.size())
			temp.push_back(input[i++]);
		if (temp.size() != 0)
		{
			this->temp.push_back(temp);
			temp.clear();
			i--;
			continue;
		}
		if (Operator(input, i, 1))
			temp.push_back(input[i]);
		if (input[i] == '(')
			temp.push_back(')');
		else if (input[i] == ')')
			temp.push_back('(');
		if (temp.size() != 0)
		{
			this->temp.push_back(temp);
			temp.clear();
			continue;
		}
		if (input[i] == ' ')
			continue;
		try
		{
			size_t temp_2 = Func(input, i);
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++)
					temp.push_back(input[j]);
				temp_2--;
				size_t control = 0;
				do
				{
					temp_2++;
					if (input[i + temp_2] == '(')
						control++;
					if (input[i + temp_2] == ')')
						control--;
					temp.push_back(input[i + temp_2]);
				} while (control != 0 && input.size() > i + temp_2);
				if (control != 0)
					throw "";
				this->temp.push_back(temp);
				temp.clear();
				i += temp_2;
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "Ошибка ввода: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			cout << endl;
			return;
		}
		try
		{
			size_t temp_2 = Const(input, i);
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++)
					temp.push_back(input[j]);
				this->temp.push_back(temp);
				temp.clear();
				i += temp_2 - 1;
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "Незнакомый симол: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			cout << endl;
			return;
		}
		throw "Незнакомы символ";
	}
	get_normal();
	this->temp.opposite();
}

string make_res(string input)
{
	string func, num;
	char control = 0;
	for (size_t i = 0; i < input.size() - 1; i++)
	{
		if (input[i] == '(' && control == 0)
		{
			control++;
			continue;
		}
		if (control)
			num += input[i];
		else func += input[i];
	}
	double result = 0, number;
	if (num == "pi")
		number = pi;
	else if (num == "e")
		number = e;
	else
	{
		calculator temp;
		temp.component(num);
		temp.get_normal();
		temp.clone();
		temp.calculate.opposite();
		number = stod(temp.get_result());
	}
	if (func == "cos") result = cos(number);
	else if (func == "sin") result = sin(number);
	else if (func == "tg") result = tan(number);
	else if (func == "ctg") result = 1 / tan(number);
	else if (func == "ln") result = log(number);
	else if (func == "log") result = log10(number);
	else if (func == "sqrt") result = sqrt(number);
	else if (func == "arccos") result = acos(number);
	else if (func == "arcsin") result = asin(number);
	else throw "Unknown error";
	return to_string(result);
}

string make_operator(string input, string number_1, string number_2)
{
	double result = 0, num_1, num_2;
	if (number_1 == "pi")
		num_1 = pi;
	else if (number_1 == "e")
		num_1 = e;
	else num_1 = stod(number_1);
	if (number_2 == "pi")
		num_2 = pi;
	else if (number_2 == "e")
		num_2 = e;
	else num_2 = stod(number_2);
	if (input == "+") result = num_1 + num_2;
	if (input == "-") result = num_1 - num_2;
	if (input == "*") result = num_1 * num_2;
	if (input == "/") result = num_1 / num_2;
	if (input == "^") result = pow(num_1, num_2);
	return to_string(result);
};

char get_priority(string oper)
{
	if (Number(oper) || Func(oper, 0) || Const(oper, 0))
		return 0;
	if (oper[0] == '+' || oper[0] == '-')
		return 0;
	if (oper[0] == '*' || oper[0] == '/')
		return 1;
	return 2;
}

void calculator::get_normal()
{
	for (size_t i = 0; i < temp.get_size(); i++)
	{
		string new_str;
		if (Func(temp.at(i)))
		{
			calculator Temp;
			string arg = temp.at(i);
			for (size_t i = Func(arg) + 1; i < arg.size() - 1; i++)
				new_str.push_back(arg[i]);
			Temp.make_prefix(new_str);
			new_str.clear();
			for (size_t i = 0; i < Func(arg) + 1; i++)
				new_str.push_back(arg[i]);
			new_str += Temp.print_prefix() + ')';
			temp.set(i, new_str);
		}
		else if (i == 0 && temp.at(i) == "-" && temp.at(i + 1) != ")" && !Func(temp.at(i + 1)) && !Operator(temp.at(i + 1)))
		{
			new_str += temp.at(i) + temp.at(i + 1);
			temp.remove(i + 1);
			temp.set(i, new_str);
		}
		else if (i == 0 && temp.at(i) == "-" && (temp.at(i + 1) == ")" || Func(temp.at(i + 1))))
		{
			temp.push_front("0");
			i++;
		}
		else if (temp.at(i) == ")" && i + 1 < temp.get_size() && temp.at(i + 1) == "-" && !Func(temp.at(i + 2)))
		{
			new_str += temp.at(i + 1) + temp.at(i + 2);
			temp.remove(i + 1);
			temp.set(i + 1, new_str);
		}
		else if (temp.at(i) == ")" && i + 1 < temp.get_size() && temp.at(i + 1) == "-" && Func(temp.at(i + 2)))
		{
			temp.insert("0", i + 1);
		}
	}
}

void calculator::get_prefix()
{
	duaList stack;
	for (size_t i = 0; i < temp.get_size(); i++)
	{
		if (Number(temp.at(i)) || Func(temp.at(i))) 
			calculate.push_back(temp.at(i));
		else if (Operator(temp.at(i))) 
		{
			if (stack.isEmpty())
				stack.push_front(temp.at(i));
			else if (stack.top() == "(")
				stack.push_front(temp.at(i));
			else if (get_priority(temp.at(i)) >= get_priority(stack.top()))
				stack.push_front(temp.at(i));
			else
			{
				while (!stack.isEmpty() && stack.top() != "(" && get_priority(temp.at(i)) < get_priority(stack.top()))
				{
					calculate.push_back(stack.top());
					stack.pop_front();
				}
				stack.push_front(temp.at(i));
			}
		}
		else if (temp.at(i) == "(")
			stack.push_front(temp.at(i));
		else if (temp.at(i) == ")")
		{
			while (!stack.isEmpty() && stack.top() != "(")
			{
				calculate.push_back(stack.top());
				stack.pop_front();
			}
			stack.pop_front();
		}
	}
	while (!stack.isEmpty()) 
	{
		calculate.push_back(stack.top());
		stack.pop_front();
	}
	calculate.opposite();
}

void calculator::make_prefix(string input)
{
	try {
		component(input);
		get_prefix();
		temp.clear();
	}
	catch (const char* error)
	{
		temp.clear();
	}
}

string calculator::print_prefix()
{
	if (calculate.get_size() == 0)
	{
		calculate.clear();
		throw "Неизвестный символ или нулевой аргумент. Введите новое арифметическое выражение или добавьте аргумент";
	}
	string result;
	for (size_t i = 0; i < calculate.get_size(); i++)
		result += calculate.at(i) + " ";
	if (result.size() != 0)
		result.pop_back();
	return result;
}

string calculator::get_result()
{
	string result;
	size_t control = 0;
	if (calculate.get_size() == 0)
		result = "0";
	else if (calculate.get_size() == 1)
	{
		try {
			if (Func(calculate.at(0)))
				calculate.set(0, make_res(calculate.at(0)));
			else if (Const(calculate.at(0)))
				if (calculate.at(0) == "pi")
					result = to_string(pi);
				else result = to_string(e);
			else if (calculate.at(0) == "-pi")
				result = to_string(-1 * pi);
			else if (calculate.at(0) == "-e")
				result = to_string(-1 * e);
			else if (Number(calculate.at(0)))
				result = calculate.at(0);
			else
			{
				calculate.print_to_console();
				calculate.clear();
				throw "Некоректная функция";
			}
		}
		catch (const char* error)
		{
			calculate.print_to_console();
			calculate.clear();
			cout << error;
			throw "Неизвестная ошибка";
		}
	}
	else if (calculate.get_size() == 2)
	{
		if ((calculate.at(0) != "-" && calculate.at(0) != "+") || (Number(calculate.at(1))))
		{
			calculate.print_to_console();
			calculate.clear();
			throw "Лишний оператор. Добавьте операнд или уберите оператор";
		}
		if (Func(calculate.at(1)) && calculate.at(0) == "-")
		{
			calculate.set(0, to_string(-1 * stod(make_res(calculate.at(1)))));
		}
		else if (Func(calculate.at(1)) && calculate.at(0) == "+")
		{
			calculate.set(0, make_res(calculate.at(1)));
		}
		calculate.pop_back();
	}
	else
		while (calculate.get_size() > 1)
		{
			control = 0;
			for (size_t i = 0; i < calculate.get_size(); i++)
			{
				if (calculate.get_size() - i >= 3 && Operator(calculate.at(i)) && Number(calculate.at(i + 1)) && Number(calculate.at(i + 2)))
				{
					calculate.set(i, make_operator(calculate.at(i), calculate.at(i + 1), calculate.at(i + 2)));
					calculate.remove(i + 1);
					calculate.remove(i + 1);
					control++;
				}
				else if (Func(calculate.at(i)))
				{
					calculate.set(i, make_res(calculate.at(i)));
					control++;
				}
				else if (calculate.get_size() == 2 && Func(calculate.at(1)) && calculate.at(0) == "-")
				{
					control++;
					calculate.set(0, to_string(-1 * stod(make_res(calculate.at(1)))));
					calculate.pop_back();
				}
			}
			if (control == 0)
			{
				calculate.clear();
				throw "Лишний оператор или операнд. Добавьте или уберите операнд или оператор";
			}
		}
	result = calculate.at(0);
	calculate.clear();
	return result;
}

void calculator::clone()
{
	for (size_t i = 0; i < temp.get_size(); i++)
		calculate.push_back(temp.at(i));
	temp.clear();
}

void calculator::clear()
{
	temp.clear();
	calculate.clear();
}