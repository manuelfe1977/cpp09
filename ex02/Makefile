SRCS = main.cpp PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)
NAME = PmergeMe
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
