#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cerrno>
#include <iostream>
#include <stdlib.h>
#include <algorithm> // For std::isspace

std::string trim(const std::string& str);

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;
public:
	BitcoinExchange(/* args */);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange	&operator=(const BitcoinExchange &src);
	const std::map<std::string, double>	get_data() const;
	void	loadData(const char *str);
	void	calculateExchange(char *str);
	double	get_cotization(std::string fecha);
};

class ErrorOpenFileException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: could not open data.csv file.\n";
	}
};

class BadDataException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: bad data in data.csv file.\n";
	}
};
