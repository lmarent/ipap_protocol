lib_LTLIBRARIES = libipap.la

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
			  

