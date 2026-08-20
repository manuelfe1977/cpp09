#include "RPN.hpp"

int	main(int argc, char **av)
{
	if (argc != 2)
	{
		std::cerr << "Error: not valid argument" << std::endl;
	}
	else
		std::cout << av[1] << std::endl;
	return 0;
}
