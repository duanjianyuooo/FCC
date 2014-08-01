AUTOMAKE_OPTIONS=foreign
SUBDIRS=lib_src src
noinst_PROGRAMS = ifsf_main
ifsf_main_SOURCES = $(top_srcdir)/src/main/ifsf_main.c 
ifsf_main_LDADD=  $(top_srcdir)/src/ifsf/ifsf_commu.o $(top_srcdir)/src/ifsf/ifsf_operate.o $(top_srcdir)/src/main/lis_common.o $(top_srcdir)/src/init/init.o $(top_srcdir)/src/main/lis_hengshan.o $(top_srcdir)/src/main/lis_jialijia.o $(top_srcdir)/lib_src/libduan.a 
INCLUDES=-I$(top_srcdir)/src/include -I$(top_srcdir)/include
export INCLUDES


