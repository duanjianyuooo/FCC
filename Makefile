TARGET=lib_src src
.PHONY:all clean
all:
	for dir in $(TARGET);\
		do $(MAKE) -C $$dir; done
clean:
	for dir in $(TARGET);\
		do $(MAKE) clean -C $$dir; done
