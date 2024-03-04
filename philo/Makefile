NAME			:= philo
CFLAGS			:= -Wextra -Wall -Werror -Wunreachable-code

HEADERS			:= -I ./include

SRCS_DIR		:= srcs
UTILS_DIR		:= $(SRCS_DIR)/utils
THREADS_DIR		:= $(SRCS_DIR)/threads

SRCS			:= $(SRCS_DIR)/philosophers.c \
					$(SRCS_DIR)/parse_arguments.c \
					$(SRCS_DIR)/make_philosophers.c \
					$(SRCS_DIR)/run_philosophers.c \
					$(THREADS_DIR)/philosopher_thread.c \
					$(UTILS_DIR)/philotoi.c \
					$(UTILS_DIR)/get_ms_time.c \
					$(UTILS_DIR)/get_ms_stamp.c \
					$(UTILS_DIR)/stupid_sleep.c \
					$(UTILS_DIR)/is_starving.c

OBJS			:= ${SRCS:.c=.o}

all:  $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re