ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libipap.la

pkginclude_HEADERS = $(top_srcdir)/include/Constants.h \
				     $(top_srcdir)/include/Error.h \
				     $(top_srcdir)/include/Logger.h \
				     $(top_srcdir)/include/stdinc.h \
				     $(top_srcdir)/include/stdincpp.h \
					 $(top_srcdir)/include/IpAp.h \
					 $(top_srcdir)/include/IpAp_data_record.h \
					 $(top_srcdir)/include/IpAp_def.h \
				     $(top_srcdir)/include/IpAp_exception.h \
				     $(top_srcdir)/include/IpAp_field.h \
					 $(top_srcdir)/include/IpAp_field_container.h \
					 $(top_srcdir)/include/IpAp_field_key.h \
				     $(top_srcdir)/include/IpAp_message.h \
					 $(top_srcdir)/include/IpAp_reverse_fields.h \
				     $(top_srcdir)/include/IpAp_t.h \
				     $(top_srcdir)/include/IpAp_template.h \
				     $(top_srcdir)/include/IpAp_template_container.h \
				     $(top_srcdir)/include/IpAp_value_field.h				  

if ENABLE_DEBUG
  AM_CXXFLAGS = -I$(top_srcdir)/include \
				-g  -fno-inline -DDEBUG -D_GLIBCXX_DEBUG
else
  AM_CXXFLAGS = -I$(top_srcdir)/include \
				-O2 
endif


libipap_la_SOURCES =  Error.cpp \
					  Constants.cpp \
					  Logger.cpp \
					  IpAp_field.cpp \
					  IpAp_value_field.cpp \
					  IpAp_field_container.cpp \
					  IpAp_data_record.cpp \
					  IpAp_field_key.cpp \
					  IpAp_template.cpp \
					  IpAp_template_container.cpp \
					  IpAp_t.cpp \
					  IpAp_message.cpp
					  
libipap_la_LIBADD =

# what flags you want to pass to the C compiler & linker
AM_CPPFLAGS = -g -I@top_srcdir@/include 
			  

