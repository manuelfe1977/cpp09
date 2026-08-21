#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <limits.h>

class RPN
{
private:
	std::stack<int>	_stack;
	int				res;
	const char		*exp;
	void	resolveOperator(const char c);
public:
	RPN();
	RPN(const char *exp);
	RPN(const RPN &src);
	RPN	&operator=(const RPN &src);
	void	solveExpresion();
	~RPN();
};

class ExpresionNotValidException : public std::exception
{
public:
	virtual const char*	what() const throw();
};

#endif
