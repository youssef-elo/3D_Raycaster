SRC_FILES := $(wildcard mandatory/*.c)
BNS_FILES := $(wildcard bonus/*.c)
GNL_FILES := $(wildcard get_next_line/*.c)

FILES := $(SRC_FILES) $(GNL_FILES)
B_FILES := $(BNS_FILES) $(GNL_FILES)

NAME=cub3d
BONUS=cub3d_bonus


# FLAGS= -Wall -Wextra -Werror 
# FLAGS= -fsanitize=address -g
opti =  -funroll-loops -O3 -ffast-math -mavx2
MlX_FLAGS= -Iinclude -ldl -lglfw -pthread -lm

INCLUDES= $(wildcard mandatory/*.h) $(wildcard get_next_line/*.h)

B_INCLUDES= $(wildcard bonus/*.h) $(wildcard get_next_line/*.h)

MLX=MLX/build/libmlx42.a

OFILES= $(FILES:.c=.o)
B_OFILES= $(B_FILES:.c=.o)

bonus : $(BONUS)

all : $(NAME)

$(NAME) : $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME) $(MLX) $(MlX_FLAGS) 

$(BONUS) : $(B_OFILES)
	cc $(FLAGS) $(B_OFILES) -o $(BONUS) $(MLX) $(MlX_FLAGS) 

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(FLAGS) $< -c -o $@ $(opti)

%bonus.o: %bonus.c $(B_INCLUDES) Makefile
	$(CC) $(FLAGS) $< -c -o $@ $(opti)

clean :
	rm -f $(OFILES) $(B_OFILES)

fclean : clean
	rm -f $(NAME) $(BONUS) 

re : fclean all