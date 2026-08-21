#include "RPN.hpp"

int	main(int argc, char **av)
{

	if (argc != 2)
		std::cerr << "One argument in RPN is nedded" << std::endl;
	else
	{

		RPN rpn(av[1]);
		try
		{
			//std::cout << av[1] << std::endl;
			rpn.solveExpresion();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	return 0;
}
