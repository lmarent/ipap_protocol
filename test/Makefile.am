AUTOMAKE_OPTIONS = foreign

# Rules for the test code (use `make check` to execute)
TESTS = test_runner
check_PROGRAMS = $(TESTS)


test_runner_SOURCES = @top_srcdir@/src/Error.cpp \
					  @top_srcdir@/src/Constants.cpp \
					  @top_srcdir@/src/Logger.cpp \
					  @top_srcdir@/src/IpAp_field.cpp \
					  @top_srcdir@/src/IpAp_value_field.cpp \
					  @top_srcdir@/src/IpAp_field_container.cpp \
					  @top_srcdir@/src/IpAp_data_record.cpp \
					  @top_srcdir@/src/IpAp_field_key.cpp \
					  @top_srcdir@/src/IpAp_template.cpp \
					  @top_srcdir@/src/IpAp_template_container.cpp \
					  @top_srcdir@/src/IpAp_t.cpp \
					  @top_srcdir@/src/IpAp_message.cpp \
					  @top_srcdir@/test/ipap_field_test.cpp \
					  @top_srcdir@/test/ipap_data_record_test.cpp \
					  @top_srcdir@/test/ipap_template_test.cpp \
					  @top_srcdir@/test/ipap_template_container_test.cpp \
					  @top_srcdir@/test/ipap_t_test.cpp \
					  @top_srcdir@/test/ipap_message_test.cpp \
				      @top_srcdir@/test/test_runner.cpp

# what flags you want to pass to the C compiler & linker
if ENABLE_DEBUG
  AM_CXXFLAGS = -g -I@top_srcdir@/include $(CPPUNIT_CFLAGS) \
				-fno-inline -D_GLIBCXX_DEBUG -DDEBUG -DPROFILING -DINTEL
  
  AM_CPPFLAGS = -g -I@top_srcdir@/include $(CPPUNIT_CFLAGS)\
			    -fno-inline -D_GLIBCXX_DEBUG -DDEBUG -DPROFILING -DINTEL
else
  AM_CXXFLAGS = -g -I@top_srcdir@/include $(CPPUNIT_CFLAGS)

  AM_CPPFLAGS = -g -I@top_srcdir@/include $(CPPUNIT_CFLAGS)
  
endif

			  
AM_LDFLAGS = $(CPPUNIT_LIBS) -ldl
LDADD = 
