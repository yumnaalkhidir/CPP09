CXX			:= c++
CXXFLAGS	:= -Wall -Werror -Wextra -std=c++98
NAME		:= RPN
FILES		:= main.cpp RPN.cpp
OBJ			:= $(FILES:.cpp=.o)
HEADER		:=  RPN.hpp


all: $(NAME)

%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
 
re: fclean all

.PHONY: all re clean fclean