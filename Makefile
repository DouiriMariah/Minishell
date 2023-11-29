
#  ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
# ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
# ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
# ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
# ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
# ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
# ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
# ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
#        ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░
                                                                      
NAME = minishell

SRC = utils/lst.c \
		utils/itoa.c\
		utils/split_quote.c\
		utils/libft.c\
		utils/split.c\
		utils/utils.c\
		parser/condition.c\
		parser/expand.c\
		parser/replace.c\
		parser/free_all.c\
		parser/type.c\
		parser/lexeur.c\
		parser/routine.c\
		parser/lst_routine.c\
		parser/expand_bis.c\
		parser/check_char.c\
		exec/init.c\
		exec/signals.c\
		exec/parsing.c\
		pipex/dup_and_close.c\
		pipex/forki.c\
		pipex/files_check.c\
		pipex/exec_cmds.c\
		pipex/pipex.c\
		pipex/orga_utils.c\
		pipex/here.c\
		builtin/unset.c\
		builtin/exit.c\
		builtin/cd.c\
		builtin/env.c\
		builtin/echo.c\
		builtin/export.c\
		builtin/pwd.c 

OBJS = ${SRC:.c=.o}

DEPS = ${OBJS:.o=.d}

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

.c.o:
			${CC} -MMD ${CFLAGS} -c $< -o ${<:.c=.o}

@ all: ${NAME}

 ${NAME}:	${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lreadline

clean: 
		${RM} ${OBJS} ${DEPS}

fclean: clean
		${RM} ${NAME}

re: fclean all



.PHONY = all bonus clean fclean re

-include ${DEPS}