#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <stdlib.h>

template<typename C> class PmergeMe
{
private:
	C _container;
public:
	PmergeMe();
	~PmergeMe();
	void	loadArguments(char **arg);
	void	splitInPairs();
	void	printContainer();
};


#endif
