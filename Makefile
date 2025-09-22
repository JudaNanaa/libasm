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

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: all $(OBJS_BONUS)
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s
	@mkdir -p $(@D)
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJS_DIR)%.o: $(BONUS_DIR)%.s
	@mkdir -p $(@D)
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean bonus

.PHONY: all bonus clean fclean re
