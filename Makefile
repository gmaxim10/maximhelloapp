SRC = hello.c
OBJ = $(SRC:.c=.o)
TARGET = hello

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@echo linking $@ ...
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

$(OBJ): %.o : %.c $(SRC) $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo [$(notdir $<)] '->' [$(notdir $@)]

.PHONY: clean
clean:
	@rm -rf $(OBJ) $(TARGET)
