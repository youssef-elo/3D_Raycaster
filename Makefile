FILES:= $(wildcard *.c)

NAME=cub3d

# FLAGS= -Wall -Wextra -Werror 
# FLAGS= -fsanitize=address -
MlX_FLAGS=-Iinclude -ldl -lglfw -pthread -lm

INCLUDES= $(wildcard: *.h)

MLX=MLX/build/libmlx42.a

OFILES= $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME) $(MLX) $(MlX_FLAGS)

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(FLAGS) $< -c -o $@ 

clean :
	rm -f $(OFILES) 

fclean :
	rm -f $(NAME) $(OFILES) 

re : fclean all