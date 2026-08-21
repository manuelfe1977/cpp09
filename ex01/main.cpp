#include "RPN.hpp"

int	main(int argc, char **av)
{

	if (argc != 2)
		std::cerr << "One argument in RPN is nedded" << std::endl;
	else
	{
		std::cout << av[1] << std::endl;
		RPN rpn(av[1]);
		try
		{
			rpn.solveExpresion();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	return 0;
}
