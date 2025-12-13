CC = gcc
CFLAG = -Wall -Wextra -std=c99 -g
TARG = steam_db
SOURCE = main.c data.c menu.c utils.c
OBJ = $(SOURCE:.c=.o)
HKI = data.h menu.h utils.h

all: $(TARG)

$(TARG): $(OBJ)
        $(CC) $(CFLAG) -o $@ $^

%.o: %.c $(HKI)
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f $(OBJ) $(TARG) games_db.bin

run:$(TARG)
        ./$(TARG)

debug: CFLAG += -g -DDEBUG
debug: $(TARG)

.PHONY: all clean run debug
