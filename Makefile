SRCS = srcs/pipex.c \
	   srcs/utils.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror
NAME = pipex

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

.c.o :
	@gcc ${FLAGS} -I pipex.h -c $< -o ${<:.c=.o}

all : ${OBJS}
	@make -C ./libft/
	@mv ./libft/libft.a ./libft.a
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc ${FLAGS} -o ${NAME} libft.a ${OBJS}
	@echo $(GREEN)"     - Compiled -"$(NONE)
	@rm -rf $(OBJS)
	@make fclean -C ./libft/
	@rm -f libft.a
	@echo $(CURSIVE)$(GRAY) "     Deleted object files" $(NONE)

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf ${OBJS}
	@echo $(GREEN)"     - Removed -"$(NONE)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make fclean -C ./libft/
	@rm -rf $(NAME) libft.a libftprintf.a
	@echo $(GREEN)"     - Removed -"$(NONE)

re: fclean all

.PHONY : .c.o all bonus clean fclean re