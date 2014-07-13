include ../../env.mk
SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o,$(SRCS))
WORKDIR:=$(PWD)
OBJDIR:=$(WORKDIR)/obj
INCLUDEDIR:=$(addprefix -I$(WORKDIR)/, $(SUBDIR))
INCLUDEDIR+=-I../../include
INCLUDEDIR+=-I../include
vpath %.h ../include
.PHONY:all
all:$(OBJS)
%.o:%.c
	$(CC) $(INCLUDEDIR) $(CFLAG)  -c  $< -o $(OBJDIR)/$@
	
