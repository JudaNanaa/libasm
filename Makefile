ASM  = nasm
ASM_FLAGS = -felf64 -g

NAME = libasm.a

SRCS_DIR = srcs/
BONUS_DIR = bonus/
OBJS_DIR = .objs/

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s ft_strchr.s
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:$(SRCS_DIR)%.s=$(OBJS_DIR)%.o)

SRCS_BONUS = ft_atoi_base.s ft_create_elem.s ft_list_push_front.s ft_list_size.s ft_list_sort.s ft_list_remove_if.s
SRCS_BONUS := $(addprefix $(BONUS_DIR), $(SRCS_BONUS))
OBJS_BONUS = $(SRCS_BONUS:$(BONUS_DIR)%.s=$(OBJS_DIR)%.o)

# Colors
BLUE=	$(shell tput -Txterm setaf 6)
GREEN= 	$(shell tput -Txterm setaf 2)
END= 	$(shell tput -Txterm sgr0)
YELLOW=	$(shell tput -Txterm setaf 3)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling done$(END)"
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Library created$(END)"

bonus: all $(OBJS_BONUS)
	@echo "$(BLUE)Compiling done (bonus)$(END)"
	@ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)Library created$(END)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<) ...$(END)"
	@$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJS_DIR)%.o: $(BONUS_DIR)%.s
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling $(notdir $<) ...$(END)"
	@$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

