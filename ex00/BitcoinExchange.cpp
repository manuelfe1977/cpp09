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
	if (this != src)
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
	if (errno != 0)
		return 1;
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
	if (year % 4 == 0 && year % 100 != 0 &&) || (year % 400 == 0)
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
	if (mes == 2 && esBisiesto(year))
		daysInMonth[2] = 29;
	if (dia > daysInMonth[mes])
		return 1;
	return 0;
}



void	splitLine(std::string line, std::string fecha, std::string precio)
{
	std::stringstream ss(line);
	char *endptr = NULL;

	if (!std::getline(ss,fecha,',') && std::getline(ss,precio))
		throw BadDataException();
}

void	BitcoinExchange::loadData(char *str)
{
	std::string fecha;
	std::string precio;
	double d = 0;
	char *endptr = NULL;

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
	file.close()
}

void	BitcoinExchange::calculateExchange(char *str)
{

}
