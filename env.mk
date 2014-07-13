CC=gcc
DEFINE=WRT_LOG_FILE
SUBDIR:=init ifsf main 
ifeq ($(ver), debug)
CFLAG=-g
else
CFLAG=-O2
endif
ifeq ($(write), file)
CFLAG+=-D $(DEFINE)
endif
vpath %.h include
vpath %.h src/include
