#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cerrno>

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;
public:
	BitcoinExchange(/* args */);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange	operator=(const BitcoinExchange &src);
	void	loadData(char *str);
	void	calculateExchange(char *str);
};

class ErrorOpenFileException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: could not open data.csv file.\n"
	}
};

class BadDataException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: bad data in data.csv file.\n"
	}
};
