#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <climits>

template<typename C>
class PmergeMe
{
private:
	C	_container;
	C	_generateJacobSequence(size_t smaller_size);
	C	_sort(C &input);
	void	_binaryInsert(C &main, int element, size_t maxSearch);
public:
	PmergeMe();
	~PmergeMe();
	int		size();
	void	loadArguments(char **arg);
	void	sortSequence();
	void	printContainer();
};


#endif
