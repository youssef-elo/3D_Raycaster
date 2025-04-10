FILES = mandatory/draw_wall.c mandatory/end.c mandatory/fog.c mandatory/ft_split.c mandatory/game_init.c mandatory/gnl.c mandatory/gnl_utils.c mandatory/main.c mandatory/mlx_init.c mandatory/parsing.c mandatory/parsing_convert_color.c mandatory/parsing_double_array.c mandatory/parsing_error.c mandatory/parsing_free_map.c mandatory/parsing_helper.c mandatory/parsing_helpful_func.c mandatory/parsing_read_file.c mandatory/parsing_read_map.c mandatory/pixel_utils.c mandatory/player_hooks.c mandatory/player_movements.c mandatory/raycaster.c mandatory/textures.c mandatory/tools.c mandatory/view_3d.c

B_FILES = bonus/draw_wall_bonus.c bonus/end_bonus.c bonus/fog_bonus.c bonus/fps_bonus.c bonus/ft_split_bonus.c bonus/game_init_bonus.c bonus/gnl_bonus.c bonus/gnl_utils_bonus.c bonus/gun_animation_2_bonus.c bonus/gun_animation_bonus.c bonus/hook_toggles_bonus.c bonus/main_bonus.c bonus/minimap_bonus.c bonus/mlx_init_bonus.c bonus/parsing_bonus.c bonus/parsing_bonus_convert_color.c bonus/parsing_bonus_double_array.c bonus/parsing_bonus_error.c bonus/parsing_bonus_free_map.c bonus/parsing_bonus_helper.c bonus/parsing_bonus_helpful_func.c bonus/parsing_bonus_read_file.c bonus/parsing_bonus_read_map.c bonus/parsing_bonus_valid_dor.c bonus/pixel_utils_bonus.c bonus/player_hooks_bonus.c bonus/player_movements_bonus.c bonus/raycaster_bonus.c bonus/set_hooks_bonus.c bonus/tools_bonus.c bonus/view_3d_bonus.c

NAME=cub3d

BONUS=cub3d_bonus

FLAGS= -Wall -Wextra -Werror 
FLAGS+= -fsanitize=address -g
opti = -funroll-loops -O3 -ffast-math -mavx2

MlX_FLAGS= -Iinclude -ldl -lglfw -pthread -lm

INCLUDES= mandatory/cub3d.h

B_INCLUDES= bonus/cub3d_bonus.h

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