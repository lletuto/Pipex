NAME = pipex
BONUS_NAME = pipex_bonus

# Dossiers des sous-projets
LIBFT_DIR = Incl/libft2
SRC_DIR = Src
BONUS_DIR = Bonus
OBJ_DIR = Executable
INCL_DIR = Incl

# Commandes et options
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft
INC = -I$(LIBFT_DIR) -I$(INCL_DIR)

# Sources
MAIN_SRCS = main.c path.c init.c error_free.c utils.c utils2.c
BONUS_SRCS = main_bonus.c path_bonus.c init_bonus.c error_free_bonus.c utils_bonus.c utils2_bonus.c

# Fichiers sources complets
SRCS = $(addprefix $(SRC_DIR)/, $(MAIN_SRCS))
BONUS = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

# Objets
MAIN_OBJS = $(addprefix $(OBJ_DIR)/, $(MAIN_SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation normale
$(NAME): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBS) -o $(NAME)
	@echo "Compilation réussie de $(NAME)"

# Compilation bonus
bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	@echo "Compilation réussie de $(BONUS_NAME)"

# Compilation des .o pour SRC
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compilé SRC : $<"

# Compilation des .o pour BONUS
$(OBJ_DIR)/%_bonus.o: $(BONUS_DIR)/%_bonus.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compilé BONUS : $<"

# Création du dossier obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)/*.o
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Objets nettoyés."

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Exécutables nettoyés."

re: fclean all

.PHONY: all clean fclean re bonus


