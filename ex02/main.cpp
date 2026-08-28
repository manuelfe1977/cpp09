#include "PmergeMe.hpp"
#include <iostream>
#include "stdio.h"
#include <stdlib.h>

int	isValidArgument(char *arg)
{
	int	i = 0;
	long num = 0;
	while (arg && arg[i] != '\0')
	{
		if (!isdigit(arg[i]))
			return 0;
		i++;
	}
	char *endptr = NULL;
	num = strtol(arg, &endptr, 10);
	if (*endptr != '\0' || num <= 0 || num > INT_MAX)
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
		std::cerr << "Error: You must insert a sequence of integers" << std::endl;
		return 1;
	}
	if (!isCorrectSequence(argc, av))
	{
		std::cerr << "Error: You must insert a valid sequence of integers" << std::endl;
		return 1;
	}
	PmergeMe<std::vector<int> > pMergeVector;
	PmergeMe<std::deque<int> > pMergeDeque;
	try
	{
		pMergeVector.loadArguments(av);
		std::cout << "Before:";
		pMergeVector.printContainer();
		std::clock_t start = std::clock();
		pMergeVector.sortSequence();
		std::clock_t end = std::clock();
		std::cout << "\n";
		std::cout << "After:";
		pMergeVector.printContainer();
		std::cout << "\n";
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << pMergeVector.size() << " elements with std::vector : " << time <<" us\n" ;

		pMergeDeque.loadArguments(av);
		start = std::clock();
		pMergeDeque.sortSequence();
		end = std::clock();
		time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << pMergeDeque.size() << " elements with std::deque : " << time <<"us\n" ;


	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
