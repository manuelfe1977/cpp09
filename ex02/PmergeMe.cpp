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
		std::cout << *b << " ";
		b++;
	}
}

template<typename C>
C PmergeMe<C>::_generateJacobSequence(size_t smaller_size)
{
	C indices;

	if (smaller_size <= 1)
		return indices;
	std::vector<size_t> jacobSequence;
	jacobSequence.push_back(0);
	jacobSequence.push_back(1);
	size_t last = 1;
	while (last < smaller_size)
	{
		size_t next = jacobSequence[jacobSequence.size() - 1] + 2 * jacobSequence[jacobSequence.size() - 2];
		jacobSequence.push_back(next);
		last = next;
	}
	size_t prev = 1;
	for (size_t k = 3; k < jacobSequence.size(); ++k)
	{
		size_t current = jacobSequence[k];
		size_t start = (current > smaller_size) ? smaller_size : current;
		size_t end = prev;
		for (size_t i = start; i > end; --i)
			indices.push_back(static_cast<int>(i - 1));
		prev = current;
		if (current >= smaller_size)
			break ;
	}
	return indices;
}

template<typename C>
void PmergeMe<C>::_binaryInsert(C &main, int element, size_t maxSearch)
{
	size_t r = (maxSearch < main.size()) ? maxSearch : main.size();
	size_t l = 0;

	while (l < r)
	{
		size_t m = l + (r - l) / 2;
		if (main[m] < element)
			l = m + 1;
		else
			r = m;
	}
	main.insert(main.begin()+ l, element);
}

template<typename C> C PmergeMe<C>::_sort(C &input)
{
	unsigned int	size = input.size();
	if (size < 2)
		return input;

	int straggler = -1;
	if (size % 2 != 0)
		straggler = input[size - 1];

	std::vector< std::pair<int, int> > pairs;
	C	bigger;
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if (input[i] < input[i + 1])
		{
			pairs.push_back(std::make_pair(input[i], input[i + 1]));
			bigger.push_back(input[i + 1]);
		}
		else
		{
			pairs.push_back(std::make_pair(input[i + 1], input[i]));
			bigger.push_back(input[i]);
		}
	}
	C main = _sort(bigger);

	C smaller;
	for (size_t i = 0; i < main.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].second == main[i])
			{
				smaller.push_back(pairs[j].first);
				break;
			}
		}
	}

	main.insert(main.begin(), smaller[0]);
	C JacobIndex = _generateJacobSequence(smaller.size());
	for (size_t i = 0; i < JacobIndex.size(); ++i)
	{
		size_t id_el = JacobIndex[i];
		int element = smaller[id_el];
		int pair = pairs[0].second;
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == element)
			{
				pair = pairs[j].second;
				break;
			}
		}
		typename C::iterator it = std::find(main.begin(), main.end(), pair);
		size_t maxSearch = (it != main.end()) ? std::distance(main.begin(), it) : main.size();
		_binaryInsert(main, element, maxSearch);
	}
	if (straggler >= 0)
		_binaryInsert(main, straggler, main.size());

	return main;
}

template<typename C>
int PmergeMe<C>::size()
{
	return _container.size();
}

template<typename C>
void PmergeMe<C>::sortSequence()
{
	_container = _sort(_container);
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;

