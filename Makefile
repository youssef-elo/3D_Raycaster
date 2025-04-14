FILES = mandatory/end.c \
		mandatory/gnl.c  \
		mandatory/fog.c   \
		mandatory/main.c   \
		mandatory/tools.c   \
		mandatory/view_3d.c  \
		mandatory/parsing.c   \
		mandatory/mlx_init.c   \
		mandatory/ft_split.c    \
		mandatory/textures.c     \
		mandatory/draw_wall.c     \
		mandatory/gnl_utils.c      \
		mandatory/game_init.c       \
		mandatory/raycaster.c        \
		mandatory/pixel_utils.c       \
		mandatory/player_hooks.c       \
		mandatory/parsing_error.c       \
		mandatory/parsing_helper.c       \
		mandatory/parsing_read_map.c      \
		mandatory/parsing_free_map.c       \
		mandatory/player_movements.c        \
		mandatory/parsing_read_file.c        \
		mandatory/parsing_helpful_func.c      \
		mandatory/parsing_double_array.c       \
		mandatory/parsing_convert_color.c       \

B_FIL = bonus/end_bonus.c   \
		bonus/fog_bonus.c    \
		bonus/fps_bonus.c     \
		bonus/gnl_bonus.c      \
		bonus/main_bonus.c      \
		bonus/tools_bonus.c      \
		bonus/minimap_bonus.c     \
		bonus/view_3d_bonus.c      \
		bonus/parsing_bonus.c       \
		bonus/mlx_init_bonus.c       \
		bonus/ft_split_bonus.c        \
		bonus/game_init_bonus.c        \
		bonus/gnl_utils_bonus.c         \
		bonus/draw_wall_bonus.c          \
		bonus/raycaster_bonus.c           \
		bonus/set_hooks_bonus.c            \
		bonus/mlx_init_2_bonus.c            \
		bonus/pixel_utils_bonus.c            \
		bonus/hook_toggles_bonus.c            \
		bonus/player_hooks_bonus.c             \
		bonus/parsing_error_bonus.c             \
		bonus/gun_animation_bonus.c              \
		bonus/parsing_helper_bonus.c              \
		bonus/gun_animation_2_bonus.c              \
		bonus/player_movements_bonus.c              \
		bonus/parsing_read_map_bonus.c               \
		bonus/parsing_free_map_bonus.c                \
		bonus/parsing_valid_dor_bonus.c                \
		bonus/parsing_read_file_bonus.c                 \
		bonus/parsing_helpful_func_bonus.c               \
		bonus/parsing_double_array_bonus.c                \
		bonus/parsing_convert_color_bonus.c                \

NAME=cub3d

BONUS=cub3d_bonus

FLAGS= -Wall -Wextra -Werror 

# FLAGS+= -fsanitize=address -g

opti= -funroll-loops -O3 -ffast-math -mavx2

MlX_FLAGS= -Iinclude -ldl -lglfw -pthread -lm

INCLUDES= mandatory/cub3d.h

B_INCLUDES= bonus/cub3d_bonus.h

MLX= MLX/build/libmlx42.a

OFILES= $(FILES:.c=.o)

B_OFILES= $(B_FIL:.c=.o)


all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME) $(MLX) $(MlX_FLAGS) 

$(BONUS) : $(B_OFILES)
	cc $(FLAGS) $(B_OFILES) -o $(BONUS) $(MLX) $(MlX_FLAGS) 

%.o: %.c $(INCLUDES)
	$(CC) $(FLAGS) $< -c -o $@ $(opti)

%bonus.o: %bonus.c $(B_INCLUDES)
	$(CC) $(FLAGS) $< -c -o $@ $(opti)

clean :
	rm -f $(OFILES) $(B_OFILES)

fclean : clean
	rm -f $(NAME) $(BONUS) 

re : fclean all