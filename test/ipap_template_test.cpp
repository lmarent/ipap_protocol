/*
 * Test the ipap_template_test class.
 *
 * $Id: ipap_template_test.cpp 2015-08-28 17:00:00 amarentes $
 * $HeadURL: https://./test/ipap_template_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_def.h"
#include "IpAp_field.h"
#include "IpAp_field_container.h"
#include "IpAp_template.h"


class IpAp_Templates_Test;


/*
 * We use a subclass for testing and make the test case a friend. This
 * way the test cases have access to protected methods and they don't have
 * to be public in mnslp_ipfix_fields.
 */
class ipap_templates_test : public ipap_template
{
  public:

	ipap_templates_test()
		: ipap_template() { }

	friend class IpAp_Templates_Test;
};


class IpAp_Templates_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( IpAp_Templates_Test );

	CPPUNIT_TEST( testAssign );

	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();

	void testAssign();

  private:
    
    ipap_templates_test *template1;
    ipap_templates_test *template2;
    ipap_templates_test *template3;
    
    ipap_field_type_t field1;
    ipap_field_type_t field2;
    ipap_field_type_t field3;  
      
    ipap_field_container field_container;   
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( IpAp_Templates_Test );


void IpAp_Templates_Test::setUp() 
{
		
	template1 = new ipap_templates_test();
	template2 = new ipap_templates_test();
	template3 = new ipap_templates_test();
		
    ipap_field_container field_container = ipap_field_container();
	
}

void IpAp_Templates_Test::tearDown() 
{
	delete template1;
	delete template2;
	delete template3;
}

void IpAp_Templates_Test::testAssign()
{

	field_container.initialize_forward();
	ipap_field field1 = field_container.get_field( 0, IPAP_FT_AUCTIONINGALGORITHMCODE );
	ipap_field field2 = field_container.get_field( 0, IPAP_FT_SOURCEIPV4ADDRESS );
	ipap_field field3 = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMESECONDS );
	ipap_field field4 = field_container.get_field( 0, IPAP_FT_SOURCEIPV6ADDRESS );

	template1->set_id(1);
	template1->set_type(IPAP_SETID_AUCTION_TEMPLATE);
	template1->set_maxfields(3);
	template1->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template1->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template1->add_field((field3.get_field_type()).length, KNOWN, 1, field3);

	CPPUNIT_ASSERT( template1->get_template_id() == 1 );
	CPPUNIT_ASSERT( template1->get_type() == IPAP_SETID_AUCTION_TEMPLATE );
	CPPUNIT_ASSERT( template1->get_numfields() == 3 );
	CPPUNIT_ASSERT( template1->get_maxfields() == 3 );

	template2->set_id(1);
	template2->set_type(IPAP_SETID_AUCTION_TEMPLATE);
	template2->set_maxfields(3);
	template2->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template2->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template2->add_field((field3.get_field_type()).length, KNOWN, 1, field3);
	
	CPPUNIT_ASSERT(*template1 == *template2);

	template3->set_id(1);
	template3->set_type(IPAP_SETID_ALLOCATION_TEMPLATE);
	template3->set_maxfields(3);
	template3->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template3->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template3->add_field((field4.get_field_type()).length, KNOWN, 1, field4);

	CPPUNIT_ASSERT(*template1 != *template3);
	
	ipap_template template4 = *template3;
	
	CPPUNIT_ASSERT(template4 == *template3);
	
	ipap_template *template5 = template3->copy();
	
	CPPUNIT_ASSERT(template4 == *template5);
	
	set<ipap_field_key> set_key = ipap_template::getTemplateTypeKeys(IPAP_SETID_AUCTION_TEMPLATE);
	
	CPPUNIT_ASSERT(set_key.size() == 2);

	set<ipap_field_key> set_key2 = ipap_template::getTemplateTypeKeys(IPAP_SETID_BID_TEMPLATE);
	
	CPPUNIT_ASSERT(set_key2.size() == 3);
	
	set<ipap_field_key> set_key3 = ipap_template::getTemplateTypeKeys(IPAP_SETID_ALLOCATION_TEMPLATE);
	
	CPPUNIT_ASSERT(set_key3.size() == 4);
	
	
}
// EOF
