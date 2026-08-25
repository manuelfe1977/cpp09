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

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;

