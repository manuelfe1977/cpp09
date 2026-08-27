#include "PmergeMe.hpp"

template<typename C>
PmergeMe<C>::PmergeMe()
{
}
template<typename C>
PmergeMe<C>::~PmergeMe()
{
}

template<typename C>
void PmergeMe<C>::loadArguments(char **arg)
{
	int	i = 1;

	while (arg[i])
	{
		_container.push_back(atoi(arg[i]));
		i++;
	}
}

template<typename C>
void PmergeMe<C>::printContainer()
{
	typename C::iterator b = _container.begin();
	typename C::iterator e = _container.end();

	while (b != e)
	{
		std::cout << *b << std::endl;
		b++;
	}
}

template<typename C>
C sortFord(C &input)
{
	unsigned int	size = input.size();
	if (size < 2)
		return input;
	C	smaller;
	C	bigger;
	for (size_t i = 0; i < size; i++)
	{
		if (i %2 != 0)
			continue ;
		if (input[i] < input[i + 1])
		{
			smaller.push_back(input[i]);
			bigger.push_back(input[i + 1]);
		}
		else
		{
			smaller.push_back(input[i + 1]);
			bigger.push_back(input[i]);
		}
	}
	if (size % 2 == 0)
		smaller.push_back(input[size - 1]);
	C	sorted = sortFord(bigger);

	C	sequenceJacob = generateSequence<C>(smaller.size());
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;

