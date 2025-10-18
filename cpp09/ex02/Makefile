NAME = PmergeMe
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp \
       PmergeMe.cpp \
       utils/Jacobsthal.cpp \
       utils/InputParser.cpp \
       utils/Validator.cpp \
       vector/VectorElement.cpp \
       vector/VectorSort.cpp \
       deque/DequeElement.cpp \
       deque/DequeSort.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
