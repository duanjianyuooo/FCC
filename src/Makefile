#
#	version: 1.0
#	author:	 duan
#	http://www.gnu.org/software/make/manual/make.html#toc_Top

TARGET=ifsf_main
-include ../env.mk
WORKDIR:=$$(pwd)

$(warning $(WORKDIR))
OBJDIR:=$(WORKDIR)/obj
LIBDIR:=../lib
define build
for dir in $(SUBDIR);do  $(MAKE) -C $$dir all ;done
endef

all:
	$(call build)
	$(CC) -o $(TARGET) $(CFLAG)  $(OBJDIR)/*.o $(LIBDIR)/libduan.a
clean:
	rm $(OBJDIR)/*.o $(TARGET)

.PHONY:all clean
