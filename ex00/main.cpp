#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **av)
{
	char *ruta = "data.csv";
	if(argc != 2)
	{
		std::cerr << "Error: could not open file.\n";
		return -1;
	}

	BitcoinExchange btc;
	try
	{
		btc.loadData(ruta);
		btc.calculateExchange(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
