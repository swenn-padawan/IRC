#@Makefile######################################################################

#@Variables#####################################################################

NAME		:= ircserv

CC			:=	c++

CFLAGS		:= -Wall -Wextra -Werror -std=c++98

VERBOSE		?=	0

ifeq ($(VERBOSE), 1)
	CFLAGS += -DVERBOSE
endif

ifeq ($(LAZY), 1)
	CFLAGS		:= -Wall -Wextra -std=c++98
endif

IFLAGS		:=	-I includes

SRCS_DIR	:= srcs

SRCS		:= main.cpp \
			   IRCMessage.cpp \

SRCS		:=	$(addprefix $(SRCS_DIR)/, $(SRCS))

BUILD		:= .objs

OBJS		:= $(addprefix $(BUILD)/, $(SRCS:%.cpp=%.o))

MAKEFLAGS	+= --no-print-directory

RM			:= rm -rf

DIR_UP		= mkdir -p $(@D)

#@Rules#########################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo " $(GREEN)$(BOLD)$(ITALIC)■$(RESET)  building	$(GREEN)$(BOLD)$(ITALIC)$(NAME)$(RESET)"

$(BUILD)/%.o: %.cpp
	@$(DIR_UP)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$^$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	@$(RM) $(BUILD)
	@echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  deleting	$(RED)$(BOLD)$(ITALIC)$(BUILD)$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  deleting	$(RED)$(BOLD)$(ITALIC)$(NAME)$(RESET)"

re: fclean all

#@Colors#########################################################################

BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
GRAY		=	\033[90m

BOLD		=	\033[1m
ITALIC		=	\033[3m

RESET		=	\033[0m
LINE_CLR	=	\33[2K\r

################################################################################
