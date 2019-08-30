CC   = gcc
NAME = test

W_FLAGS = -Wall -Werror -Wshadow -Wformat-security -Wpointer-arith -Wcast-align -Wredundant-decls

C_FLAGS = -g3 $(W_FLAGS) $(INCLUDES)
L_FLAGS = -lz -lm
D_FLAGS = -ggdb $(W_FLAGS)

O_FILES = list.o test.o

all: $(O_FILES)
	rm -f $(NAME)
	$(CC) -o $(NAME) $(O_FILES) $(L_FLAGS) $(C_FLAGS) $(D_FLAGS)

.c.o: all
	@$(CC) -c $(C_FLAGS) $<

clean:
	@echo Cleaning code $< ...
	@rm -rf *.o
	@rm -f $(NAME)
	@rm -f *.*~
