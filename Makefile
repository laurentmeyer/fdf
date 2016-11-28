OBJECTS =	main.o					\
			init.o					\
			matrix_basics.o			\
			matrix_transforms.o		\
			vectors.o				\
			hooks.o					\
			display.o				\
			print.o					\
			update.o				\
			projections.o			\
			lines.o

NAME = fdf

LIBFT = 		./libft/

MINILIB = 		./mlx/

CCHEADERS = -I./includes/			\
			-I$(LIBFT)includes/		\
			-I$(MINILIB)

CCSOURCES = ./srcs/

CCLIBS = -L$(LIBFT) -lft			\
		 -L$(MINILIB) -lmlx

CCFRAMEWORKS = -framework AppKit -framework OpenGL

CFLAGS = -Wall -Wextra -Werror

SOURCES = $(OBJECTS:%.o=$(CCSOURCES)%.c)

all : $(NAME)
.PHONY: all

$(NAME) : libs
	gcc $(CFLAGS) -o $(NAME) $(CCHEADERS) $(CCLIBS) $(SOURCES) $(CCFRAMEWORKS)

libs: 
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIB)
.PHONY: libs

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MINILIB) clean
	rm -f $(OBJECTS)
.PHONY: clean

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
