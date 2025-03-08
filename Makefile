SRC_FILES := $(wildcard *.c)
GNL_FILES := $(wildcard get_next_line/*.c)

FILES := $(SRC_FILES) $(GNL_FILES)

NAME=cub3d


# FLAGS= -Wall -Wextra -Werror 
# FLAGS= -fsanitize=address -g 
opti =-funroll-loops -O3 -ffast-math
MlX_FLAGS= -Iinclude -ldl -lglfw -pthread -lm 

INCLUDES= $(wildcard *.h) $(wildcard get_next_line/*.h)

MLX=MLX/build/libmlx42.a

OFILES= $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME) $(MLX) $(MlX_FLAGS) 

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(FLAGS) $< -c -o $@ $(opti)

clean :
	rm -f $(OFILES) 

fclean :
	rm -f $(NAME) $(OFILES) 

re : fclean all