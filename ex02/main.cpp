#include "PmergeMe.hpp"
#include <iostream>
#include "stdio.h"
#include <stdlib.h>

int	isValidArgument(char *arg)
{
	int	i = 0;
	int num = 0;
	while (arg && arg[i] != '\0')
	{
		if (!isdigit(arg[i]))
			return 0;
		i++;
	}
	num = atoi(arg);
	if (num < 0)
		return 0;
	return 1;
}

int	isIn(int x, char **av, int pos, int limit)
{

	int	i = pos + 1;
	while (i < limit)
	{
		if (x == atoi(av[i]))
			return 1;
		i++;
	}

	return 0;
}

int	isCorrectSequence(int argc, char **av)
{
	int	i = 1;

	while (av[i] && i < argc)
	{
		if (!isValidArgument(av[i]))
			return 0;
		else if (isIn(atoi(av[i]), av, i, argc))
			return 0;
		i++;
	}
	return 1;
}


int main(int argc, char **av)
{
	if (argc == 1)
	{
		std::cerr << "You must insert a sequence of integers" << std::endl;
		return 1;
	}
	if (!isCorrectSequence(argc, av))
	{
		std::cerr << "You must insert a valid sequence of integers" << std::endl;
		return 1;
	}
	PmergeMe<std::vector<int> > pMergeVector;
	PmergeMe<std::deque<int> > pMergeDeque;
	try
	{
		pMergeVector.loadArguments(av);
		pMergeDeque.loadArguments(av);
		//pMergeDeque.printContainer();
		//pMergeVector.printContainer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
