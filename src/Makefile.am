AUTOMAKE_OPTIONS=foreign
#SUBDIRS=ifsf main 
noinst_PROGRAMS = ifsf_main
ifsf_main_SOURCES = $(top_srcdir)/src/main/ifsf_main.c   $(top_srcdir)/src/ifsf/ifsf_commu.c $(top_srcdir)/src/ifsf/ifsf_operate.c $(top_srcdir)/src/main/lis_common.c $(top_srcdir)/src/init/init.c $(top_srcdir)/src/main/lis_hengshan.c $(top_srcdir)/src/main/lis_jialijia.c
ifsf_main_LDADD=  $(top_srcdir)/lib_src/libduan.a 
INCLUDES=-I$(top_srcdir)/src/include -I$(top_srcdir)/include
export INCLUDES


