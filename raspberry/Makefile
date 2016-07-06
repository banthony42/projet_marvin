NAME = marvin

INC_DIR = includes


NAME_LIB = marvin.a\

#CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -I $(INC_LIB_DIR)
CFLAGS = -I$(INC_DIR)

SRC = main.c  ft_init.c print_memory.c marvin_debug.c\
	  marvin_destruct.c send_message.c marvin_list.c\
	 	receive_message.c marvin_tri_ordre.c marvin_ordres.c

SRCS = $(addprefix sources/,$(SRC))

OBJ = $(SRCS:.c=.o)
CC = clang 
all : $(NAME)

$(NAME) : $(OBJ)
			ar -r $(NAME_LIB) $(OBJ)
			gcc -o $(NAME) $(NAME_LIB)

clean :
			rm -rf $(OBJ)

fclean : clean
			rm -rf $(NAME)
			rm -rf $(NAME_LIB)

re : fclean all

.PHONY: all clean fclean re
