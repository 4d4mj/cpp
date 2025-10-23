# Makefile for comparison tester
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

TARGET = test_comparisons
SRCS = test_comparisons.cpp \
       ../PmergeMe.cpp \
       ../utils/Jacobsthal.cpp \
       ../utils/Parser.cpp \
       ../utils/Validator.cpp \
       ../vector/VectorElement.cpp \
       ../vector/VectorSort.cpp \
       ../deque/DequeElement.cpp \
       ../deque/DequeSort.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
