include ../env.mk
INCLUDE:=-I../include
TARGET:=../lib/libduan.a
SRC:=$(wildcard *.c)
OBJS:=$(patsubst  %.c, %.o, $(SRC))
.PHONY:all clean
all:$(TARGET)
$(OBJS):$(SRC)
	$(CC) $(INCLUDE) -c  $< -o $@

$(TARGET):$(OBJS)
	ar rc $(TARGET) $(OBJS) 

clean:
	rm *.o ../lib/*.a
