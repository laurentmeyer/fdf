CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
BINARY =	fdf
BUILDDIR =	builds
SOURCEDIR =	srcs
HEADERDIR = includes

SRCFILES =	main.c					\
			init.c					\
			matrix_basics.c			\
			matrix_transforms.c		\
			vectors.c				\
			hooks.c					\
			display.c				\
			update.c				\
			projections.c			\
			lines.c					\
			read.c					\
			gradients.c				\
			colors.c				\
			utils.c					\
			print.c

LIBS =		ft						\
			mlx

LIBFT = 		./libft/

MINILIB = 		./mlx/

CCHEADERS = -I./$(HEADERDIR)		\
			-I$(LIBFT)includes/		\
			-I$(MINILIB)

CCLIBS = -L$(LIBFT) -lft			\
		 -L$(MINILIB) -lmlx

CCFRAMEWORKS = -framework AppKit -framework OpenGL

SOURCES = $(SRCFILES:%.c=$(SOURCEDIR)/%.c)
OBJECTS = $(SOURCES:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(BINARY)

$(BINARY) : $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIB)
	$(CC) $(CCHEADERS) $(CCLIBS) $(OBJECTS) $(CCFRAMEWORKS) -o $(BINARY)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MINILIB) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
