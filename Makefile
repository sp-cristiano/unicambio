CC = gcc
CFLAGS = -Iinclude -Wall -g -Wextra -std=c99 #-fsanitize=address -MMD -MP
LDFLAGS = -lsodium #-fsanitize=address

# Find all .c source files [Procurar todos os arquivos .c]
SRCS = $(wildcard src/*.c) $(wildcard src/defaultSetup/*.c) $(wildcard src/functions/*.c) $(wildcard src/functions/currencyFunctions/*.c) $(wildcard src/functions/exchangeRateFunctions/*.c) $(wildcard src/functions/menuFunctions/*.c) $(wildcard src/functions/authFunctions/*.c) $(wildcard src/functions/systemFunctions/*.c) $(wildcard src/functions/transactionFunctions/*.c) $(wildcard src/functions/userFunctions/*.c) $(wildcard src/functions/userFunctions/adminUserFunctions/*.c) $(wildcard src/functions/utilities/*.c)

# Create object files from source file then  store in object directory [Cria arquivos .o a partir dos arquivos .c e armazena na pasta object]
OBJS = $(patsubst src/%.c, build/obj/%.o, $(SRCS))

# Create executable from object files [Cria o executável a partir dos arquivos .o]
TARGET = ./build/unicambio

# Default Rule [Regra padrão]
all: $(TARGET)

# Linking the object files to create executables [Linka os arquivos .o para criar executáveis]
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Rule to compile .c files to .o files in build/obj/ [Regra para compilar os arquivos .c para .o na pasta build/obj/]
build/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and executables [Alvo para limpar arquivos .o e executáveis]
clean-all:
	rm -f $(OBJS) $(TARGET)

# Clean target to remove object files only [Alvo para limpar apenas arquivos .o]
clean-obj:
	rm -f $(OBJS)

# Clean target to remove executables only [Alvo para limpar apenas executáveis]
clean-exec:
	rm -f $(TARGET)
