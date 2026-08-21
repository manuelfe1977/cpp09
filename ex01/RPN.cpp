#include "RPN.hpp"

RPN::RPN()
{
	exp = NULL;
	res = 0;
}

RPN::RPN(const char *exp)
{
	this->exp = exp;
	res = 0;
}
RPN::~RPN()
{
}
RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
	{
		exp = src.exp;
		_stack = src._stack;
		res = src.res;
	}
	return *this;
}

RPN::RPN(const RPN &src)
{
	*this = src;
}

int is_operator(const char c)
{
	std::string operators = "+-*/";
	for (int i = 0; i < 4; i++)
	{
		if (operators[i] == c)
			return 1;
	}
	return -1;
}

int operation(int a, int b, const char c)
{
	switch (c)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		if (b == 0)
			throw ExpresionNotValidException();
		else
			return a / b;
		break;
	default:
		throw ExpresionNotValidException();
		break;
	}
}

void RPN::resolveOperator(const char c)
{
	if (_stack.size() > 1)
	{
		int op_a = _stack.top();
		_stack.pop();
		int op_b = _stack.top();
		_stack.pop();
		int res = operation(op_b, op_a, c);
		_stack.push(res);
	}
	else
		throw ExpresionNotValidException();
}

void RPN::solveExpresion()
{
	int i = 0;

	if (exp == '\0')
		throw ExpresionNotValidException();
	while (exp[i] != '\0')
	{
		if (i % 2 != 0)
		{
			if (exp[i] != ' ')
				throw ExpresionNotValidException();
		}
		else
		{
			if (std::isdigit(exp[i]))
				_stack.push(exp[i] - '0');
			else if (is_operator(exp[i]))
				resolveOperator(exp[i]);
			else
				throw ExpresionNotValidException();
		}
		i++;
	}
	if (_stack.size() != 1)
		throw ExpresionNotValidException();
	std::cout << _stack.top() << std::endl;
	_stack.pop();
}

const char *ExpresionNotValidException::what() const throw()
{
	return "The expression is not valid";
}
