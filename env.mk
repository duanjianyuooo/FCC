CC=gcc
SUBDIR:=init main
ifeq ($(ver), debug)
CFLAG=-g
else
CFLAG=-O2
endif

