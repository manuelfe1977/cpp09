#include "BitcoinExchange.hpp"

// Utility function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (std::string::npos == first) {
        return str; // No non-whitespace character found, return original string or empty
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

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
		return -1;
	double val = strtod(precio.c_str(), &endptr);
	if (endptr == precio.c_str())
		return -1;
	while (*endptr != '\0')
	{
		if (!std::isspace(*endptr))
			return -1;
		endptr++;
	}
	if (errno == ERANGE)
		return -1;
	if (val < 0 || val > 1000)
		return -1;
	d = val;
	return 1;
}

int	valid_quantity(std::string quantity, double &d)
{
	errno = 0;
	char *endptr = NULL;

	if (quantity.empty())
	{
		std::cout << "Error: No quantity" << std::endl;
		return -1;
	}
	double val = strtod(quantity.c_str(), &endptr);
	if (endptr == quantity.c_str())
	{
		std::cout << "Error: No quantity" << std::endl;
		return -1;
	}
	while (*endptr != '\0')
	{
		if (!std::isspace(*endptr))
		{
			std::cout << "Error: Bad quantity => " << quantity << std::endl;
			return -1;
		}
		endptr++;
	}
	if (errno == ERANGE)
	{
		std::cout << "Error: Too large quantity" << std::endl;
		return -1;
	}
	if (val > 1000)
	{
		std::cout << "Error: Too large quantity" << std::endl;
		return -1;
	}
	if (val < 0)
	{
		std::cout << "Error: Not positive quantity" << std::endl;
		return -1;
	}
	d = val;
	return 1;
}

int	is_digit(std::string fecha)
{
	for (size_t i = 0; i < fecha.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(fecha[i]))
			return 0;
	}
	return 1;
}

int	esBisiesto(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return 1;
	return 0;
}

int	valid_date(std::string fecha)
{
	int	year;
	int	month;
	int	day;

	if (fecha.size() != 10)
		return -1;
	if (fecha[4] != '-' && fecha[7] != '-')
		return -1;
	if (!is_digit(fecha))
		return 0;
	std::stringstream syear(fecha.substr(0, 4));
	std::stringstream smonth(fecha.substr(5, 2));
	std::stringstream sday(fecha.substr(8, 2));
	syear >> year;
	smonth >> month;
	sday >> day;
	if (year < 0 || !(month >=1 && month <=12) || day <= 0)
		return -1;
	if (year < 2009 || year > 2022)
		return -1;
	int	daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && esBisiesto(year))
		daysInMonth[2] = 29;
	if (day > daysInMonth[month])
		return -1;
	return 1;
}



void	splitLine(std::string line, std::string &fecha, std::string &precio)
{
	std::stringstream ss(line);
    std::string s_fecha;
    std::string s_precio;

    // Attempt to extract fecha
    if (!std::getline(ss, s_fecha, ',')) {
        throw BadDataException(); // Failed to get fecha (e.g., empty line or no comma)
    }

    // Attempt to extract precio
    if (!std::getline(ss, s_precio)) {
        throw BadDataException(); // Failed to get precio (e.g., no data after comma)
    }

    // Check for extra data in the stream (more than two fields)
    std::string remaining_data;
    if (std::getline(ss, remaining_data) && !trim(remaining_data).empty()) {
        throw BadDataException(); // Malformed: extra data after price
    }

    fecha = trim(s_fecha);
    precio = trim(s_precio);
	//std::cout << fecha << " " << precio << std::endl;
}

void	BitcoinExchange::loadData(const char *str)
{
	std::string fecha;
	std::string precio;
	double d = 0;

	std::ifstream file(str);
	if (!file.is_open())
	{
		file.close();
		throw ErrorOpenFileException();
	}
	std::string line;
	if (std::getline(file, line))
	{
		while (std::getline(file, line))
		{
			splitLine(line, fecha, precio);
			if (!valid_date(fecha) || !valid_price(precio, d))
			{
				file.close();
				throw BadDataException();
			}
			_data.insert(std::pair<std::string, double>(fecha, d));
		}
	}
	if (_data.empty())
	{
		file.close();
		throw BadDataException();
	}
	file.close();
}

int	splitLineInput(std::string line, std::string &fecha, std::string &quantity)
{
	std::string	delim = " | ";
	size_t pos = line.find(delim);

	if (pos == std::string::npos)
	{
		return -1;
	}

	fecha = trim(line.substr(0, pos));
	quantity = trim(line.substr(pos + delim.length()));

	// Check if there are more delimiters after the first one
	if (line.find(delim, pos + delim.length()) != std::string::npos)
	{
		return -1; // Malformed input with extra delimiter
	}

	return 1;
}

const std::map<std::string, double>	BitcoinExchange::get_data() const
{
	return _data;
}

double	BitcoinExchange::get_cotization(std::string fecha)
{
	double res = 0;

	std::map<std::string, double> map_copy = this->get_data();
	std::map<std::string, double>::const_iterator it = map_copy.upper_bound(fecha);
	if (map_copy.begin() == it)
		return 0;
	else
		it--;
	res = it->second;
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

			if (splitLineInput(line, fecha, quantity) != 1)
			{
				std::cout << "Error: Bad input => " << line << std::endl;
			}
			else if (valid_date(fecha) != 1)
				std::cout << "Error: Bad input => " << fecha << std::endl;
			else if (valid_quantity(quantity, d) == 1 )
			{
				cotization = this->get_cotization(fecha);
				if (cotization < 0)
					std::cout << "Error: no data aviable for or before date => " << fecha << std::endl;
				std::cout << fecha <<" => " << quantity << " = " << (d * cotization) << std::endl;
			}
		}
	}
}
