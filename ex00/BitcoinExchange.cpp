#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(/* args */)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _data(src._data)
{
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_data = src._data;
	}
	return *this;
}

int	valid_price(std::string precio, double &d)
{
	errno = 0;
	char *endptr = NULL;
	if (precio.empty())
		return 1;
	double val = strtod(precio.c_str(), &endptr);
	if (endptr == precio.c_str())
		return 1;
	while (*endptr != '\0')
	{
		if (!std::isspace(*endptr))
			return 1;
		endptr++;
	}
	if (errno == ERANGE)
		return 1;
	if (val < 0)
		return 1;
	d = val;
	return 0;
}

int	valid_quantity(std::string quantity, double &d)
{
	errno = 0;
	char *endptr = NULL;

	if (quantity.empty())
	{
		std::cout << "Error: No quantity" << std::endl;
		return 1;
	}
	double val = strtod(quantity.c_str(), &endptr);
	if (endptr == quantity.c_str())
	{
		std::cout << "Error: No quantity" << std::endl;
		return 1;
	}
	while (*endptr != '\0')
	{
		if (!std::isspace(*endptr))
		{
			std::cout << "Error: Bad quantity => " << quantity << std::endl;
			return 1;
		}
		endptr++;
	}
	if (errno == ERANGE)
	{
		std::cout << "Error: Too large equantity" << std::endl;
		return 1;
	}
	if (val > 1000)
	{
		std::cout << "Error: Too large equantity" << std::endl;
		return 1;
	}
	if (val < 0)
	{
		std::cout << "Error: Not positive quantity" << std::endl;
		return 1;
	}
	d = val;
	return 0;
}

int	is_digit(std::string fecha)
{
	for (size_t i = 0; i < fecha.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(fecha[i]))
			return 1;
	}
	return 0;
}

int	esBisiesto(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return 0;
	return 1;
}

int	valid_date(std::string fecha)
{
	int	year;
	int	month;
	int	day;

	if (fecha.size() != 10)
		return 1;
	if (fecha[4] != '-' && fecha[7] != '-')
		return 1;
	if (!is_digit(fecha))
		return 1;
	std::stringstream syear(fecha.substr(0, 4));
	std::stringstream smonth(fecha.substr(5, 2));
	std::stringstream sday(fecha.substr(8, 2));
	syear >> year;
	smonth >> month;
	sday >> day;
	if (year < 0 || !(month >=1 && month <=12) || day <= 0)
		return 1;
	int	daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && esBisiesto(year))
		daysInMonth[2] = 29;
	if (day > daysInMonth[month])
		return 1;
	return 0;
}



void	splitLine(std::string line, std::string fecha, std::string precio)
{
	std::stringstream ss(line);

	if (!std::getline(ss,fecha,',') && std::getline(ss,precio))
		throw BadDataException();
}

void	BitcoinExchange::loadData(char *str)
{
	std::string fecha;
	std::string precio;
	double d = 0;

	std::ifstream file(str);
	if (!file.is_open())
		throw ErrorOpenFileException();

	std::string line;
	if (std::getline(file, line))
	{
		while (std::getline(file, line))
		{
			splitLine(line, fecha, precio);
			if (!valid_date(fecha) || !valid_price(precio, d))
				throw BadDataException();
		}
		_data.insert(std::pair<std::string, double>(fecha, d));
	}
	file.close();
}

int	splitLineInput(std::string line, std::string &fecha, std::string &quantity)
{
	std::string	delim = " | ";
	size_t pos = line.find(delim);

	if (pos != std::string::npos)
	{
		fecha = line.substr(0, pos);
		quantity = line.substr(pos + delim.length());
	}
	else
		return 1;
	return 0;
}

double	get_cotization(std::string fecha)
{
	double res = 0;


	return res;
}

void	BitcoinExchange::calculateExchange(char *str)
{
	std::string fecha;
	std::string quantity;
	double d = 0;
	double cotization = 0;

	std::ifstream data(str);
	if (!data.is_open())
		throw ErrorOpenFileException();

	std::string line;
	if (std::getline(data, line))
	{
		while (std::getline(data, line))
		{
			if (!splitLineInput(line, fecha, quantity))
				std::cout << "Error: Bad input => " << fecha << std::endl;
			else if (!valid_date(fecha))
				std::cout << "Error: Bad input => " << fecha << std::endl;
			else if (valid_price(quantity, d))
			{
				cotization = get_cotization(fecha);
				std::cout << fecha <<" => " << quantity << " = " << (d * cotization) << std::endl;
			}
		}
	}
}
