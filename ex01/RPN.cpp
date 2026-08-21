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
RPN	&RPN::operator=(const RPN &src)
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

int	is_operator(const char c)
{

}

int	operation(int a, int b, const char c)
{

}

void	RPN::resolveOperator(const char c)
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

void	RPN::expresionToList()
{
	int i = 0;

	while (exp[i] != '\0')
	{
		if (i % 2 == 0)
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
}

void	RPN::solveExpresion()
{
	if (exp == '\0')
		throw ExpresionNotValidException();


}

const char*	ExpresionNotValidException::what() const throw()
{
		return "The expression is not valid";
}
