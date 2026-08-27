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
C PmergeMe<C>::_generateJacobSequence(size_t smaller_size)
{
	(void) smaller_size;
	C jacobSequence;

	return jacobSequence;
}

template<typename C>
void PmergeMe<C>::_binaryInsert(C &main, int element, size_t maxSearch)
{
	(void) main;
	(void) element;
	(void) maxSearch;
	// Lógica de búsqueda binaria...
}

template<typename C> C PmergeMe<C>::_sort(C &input)
{
	unsigned int	size = input.size();
	if (size < 2)
		return input;
	C	smaller;
	C	bigger;
	for (size_t i = 0; i < size - 1; i++)
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
	if (size % 2 != 0)
		smaller.push_back(input[size - 1]);

	bigger.insert(bigger.begin(), smaller[0]);
	return bigger;
}

template<typename C>
void PmergeMe<C>::sortSequence()
{
	std::clock_t start = std::clock();

	_container = _sort(_container);

	std::clock_t end = std::clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << time<< std::endl;
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;

