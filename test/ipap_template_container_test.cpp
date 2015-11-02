/*
 * Test the ipap_template_container_test class.
 *
 * $Id: ipap_template_container_test.cpp 2015-08-28 17:31:09 amarentes $
 * $HeadURL: https://./test/ipap_template_container_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_def.h"
#include "IpAp_field.h"
#include "IpAp_template.h"
#include "IpAp_field_container.h"
#include "IpAp_template_container.h"



class IpAp_Container_Template_Test;


/*
 * We use a subclass for testing and make the test case a friend. This
 * way the test cases have access to protected methods and they don't have
 * to be public in mnslp_ipfix_fields.
 */
class ipap_container_template_test : public ipap_template_container
{
  public:

	ipap_container_template_test()
		: ipap_template_container() { }

	friend class IpAp_Container_Template_Test;
};


class IpAp_Container_Template_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( IpAp_Container_Template_Test );

	CPPUNIT_TEST( testAssign );

	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testAssign();

  private:
    
      
    ipap_field_container field_container;   
    ipap_container_template_test *container1;
    ipap_container_template_test *container2;
    
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( IpAp_Container_Template_Test );


void IpAp_Container_Template_Test::setUp() 
{
	container1 = new ipap_container_template_test();
	container2 = new ipap_container_template_test();
    ipap_field_container field_container = ipap_field_container();
}

void IpAp_Container_Template_Test::tearDown() 
{
	saveDelete(container1);
	saveDelete(container2);
}

void IpAp_Container_Template_Test::testAssign()
{

	ipap_template *template1;
	ipap_template *template2;
	ipap_template *template3;
	
	template1 = new ipap_template();
	template2 = new ipap_template();
	template3 = new ipap_template();
	
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

	template2->set_id(2);
	template2->set_type(IPAP_SETID_BID_OBJECT_TEMPLATE);
	template2->set_maxfields(3);
	template2->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template2->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template2->add_field((field3.get_field_type()).length, KNOWN, 1, field3);
		
	template3->set_id(3);
	template3->set_type(IPAP_OPTNS_BID_OBJECT_TEMPLATE);
	template3->set_maxfields(3);
	template3->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template3->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template3->add_field((field4.get_field_type()).length, KNOWN, 1, field4);

	container1->add_template(template1);
	container1->add_template(template2);
	container1->add_template(template3);
	
	CPPUNIT_ASSERT(container1->get_num_templates() == 3 );
	
	container1->delete_template(template3->get_template_id());
	
	CPPUNIT_ASSERT(container1->get_num_templates() == 2 );
	
	container1->delete_template(template2->get_template_id());
	
	CPPUNIT_ASSERT(container1->get_num_templates() == 1 );
	
	ipap_template_container container3 = *container1;
	 
	CPPUNIT_ASSERT(*container1 == container3 );
	
	CPPUNIT_ASSERT(container3.get_num_templates() == 1 );
	
}
// EOF
