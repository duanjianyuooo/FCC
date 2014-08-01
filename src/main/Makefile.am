AUTOMAKE_OPTIONS=foreign
noinst_PROGRAMS=lis_common lis_hengshan lis_jialijia 
lis_common_SOURCES=lis_common.c
lis_hengshan_SOURCES=lis_hengshan.c $(top_srcdir)/lib_src/libduan.a
lis_jialijia_SOURCES=lis_jialijia.c
lis_hengshan_LDADD=$(top_srcdir)/lib_src/libduan.a
lis_jialijia_LDADD=$(top_srcdir)/lib_src/libduan.a
INCLUDES=-I$(top_srcdir)/src/include -I$(top_srcdir)/include
