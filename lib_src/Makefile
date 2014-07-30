include ../env.mk
INCLUDE:=-I../include
SRC:=$(wildcard *.c)
OBJS:=$(patsubst  %.c, %.o, $(SRC))
TARGET:=$(patsubst %.o, %.a, $(OBJS)) 
.PHONY:all
all:$(TARGET)
%.o:%.c
	$(CC) $(INCLUDE) -c  $< -o $@
%.a:%.o
	ar rc ../lib/$@  *.o
clean:
	rm ../lib/*.a
