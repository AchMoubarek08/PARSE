
# CPPFLAGS = -I/Users/fstitou/.brew/opt/readline/inlclude
# LDFLAGS = -L/Users/fstitou/.brew/opt/readline/lib
CPPFLAGS = -I/goinfre/amoubare/homebrew/opt/readline/include
LDFLAGS = -L/goinfre/amoubare/homebrew/opt/readline/lib

NAME = minishell

SRC = main.c tokenize.c utils.c get_next_line_utils.c get_next_line.c\

OBJ = main.o tokenize.o utils.o get_next_line_utils.o get_next_line.o\


all : $(NAME)

$(NAME):
	
	@gcc $(SRC) $(LDFLAGS) $(CPPFLAGS)  -lreadline -o $(NAME)
	@echo "Mino 👍👍👍"

clean :
 
	@rm -f $(OBJ)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) 
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all