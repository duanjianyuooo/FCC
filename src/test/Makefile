TARGET=$(subst .c,,$(wildcard  *.c))
$(warning $(TARGET))
all:
	for b in $(TARGET); do\
		gcc -o $$b $$b.c -I../../include ../../lib_src/libduan.a ../../lib_src/libunp.a -lm;	\
	done
