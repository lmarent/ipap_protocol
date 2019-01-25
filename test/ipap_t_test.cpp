/*
 * Test the ipap_t_test class.
 *
 * $Id: ipap_t_test.cpp 2015-08-28 17:14:00 amarentes $
 * $HeadURL: https://./test/ipap_t_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_field_container.h"
#include "IpAp_t.h"


class Ipap_T_Test;


/*
 * We use a subclass for testing and make the test case a friend. This
 * way test cases have access to protected methods and they don't have
 * to be public.
 */
class ipap_t_test : public ipap_t
{
  public:

	ipap_t_test()
		: ipap_t() { }

	friend class Ipap_T_Test;
};

class Ipap_T_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( Ipap_T_Test );

	CPPUNIT_TEST( testAssign );

	CPPUNIT_TEST( testSetFlags );

	CPPUNIT_TEST( testGetFlags );

	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testAssign();
	void testSetFlags();
	void testGetFlags();

  private:
    
    ipap_field_container field_container; 
    ipap_t *ptrIpap_t1;
    ipap_t *ptrIpap_t2;
    ipap_t *ptrIpap_t3;
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( Ipap_T_Test );


void Ipap_T_Test::setUp() 
{		
	ptrIpap_t1 = new ipap_t();

	ipap_template *template1;
	ipap_template *template2;
	ipap_template *template3;
	
	template1 = new ipap_template();
	template2 = new ipap_template();
	template3 = new ipap_template();
	
	ipap_field_container field_container = ipap_field_container();
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
	template2->set_type(IPAP_SETID_AUCTION_TEMPLATE);
	template2->set_maxfields(3);
	template2->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template2->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template2->add_field((field3.get_field_type()).length, KNOWN, 1, field3);
		
	template3->set_id(3);
	template3->set_type(IPAP_SETID_BID_OBJECT_TEMPLATE);
	template3->set_maxfields(3);
	template3->add_field((field1.get_field_type()).length, KNOWN, 1, field1);
	template3->add_field((field2.get_field_type()).length, KNOWN, 1, field2);
	template3->add_field((field4.get_field_type()).length, KNOWN, 1, field4);
			
	(ptrIpap_t1->templates).add_template(template1);
	(ptrIpap_t1->templates).add_template(template2);
	(ptrIpap_t1->templates).add_template(template3);
	
}

void Ipap_T_Test::tearDown() 
{
	delete ptrIpap_t1;
	delete ptrIpap_t2;
}

void Ipap_T_Test::testAssign()
{
	
	
	CPPUNIT_ASSERT( ptrIpap_t1->templates.get_num_templates() == 3 );
		
	ptrIpap_t1->buffer[0] =  'a';
	ptrIpap_t1->buffer[1] =  'b';
	ptrIpap_t1->buffer[2] =  'c';
	ptrIpap_t1->buffer[3] =  'd';
	ptrIpap_t1->buffer[4] =  'e';
	ptrIpap_t1->buffer[5] =  'f';
	ptrIpap_t1->buffer[6] =  '\0';
	ptrIpap_t1->offset = 7;
	ptrIpap_t1->nrecords = 0;
	ptrIpap_t1->seqno = 0;
	ptrIpap_t1->cs_tid = 1;
	ptrIpap_t1->cs_bytes = 3;
	ptrIpap_t1->cs_offset= 4;
	ptrIpap_t1->cs_header = (uint8_t*) ptrIpap_t1->buffer + ptrIpap_t1->cs_offset;
		
	ptrIpap_t2 = new ipap_t();
	*ptrIpap_t2 = *ptrIpap_t1;
	
	CPPUNIT_ASSERT( *ptrIpap_t2  == *ptrIpap_t1 );
	CPPUNIT_ASSERT( *(ptrIpap_t2->cs_header)  == 'e' );
	
}
// EOF

void Ipap_T_Test::testSetFlags()
{
    uint8_t none = 0;
    uint8_t syn = 1;
    uint8_t ack = 2;
    uint8_t syn_ack = 3;
    uint8_t fin = 4;
    uint8_t fin_syn = 5;
    uint8_t fin_ack = 6;
    uint8_t fin_ack_syn = 7;

    ptrIpap_t1->set_flags(none);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == false );

    ptrIpap_t1->set_flags(syn);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == false );

    ptrIpap_t1->set_flags(ack);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == false );

    ptrIpap_t1->set_flags(fin);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == true );

    ptrIpap_t1->set_flags(syn_ack);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == false );

    ptrIpap_t1->set_flags(fin_syn);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == true );

    ptrIpap_t1->set_flags(fin_ack);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == false );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == true );

    ptrIpap_t1->set_flags(fin_ack_syn);
    CPPUNIT_ASSERT( ptrIpap_t1->syn  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->ack  == true );
    CPPUNIT_ASSERT( ptrIpap_t1->fin  == true );

}


void Ipap_T_Test::testGetFlags()
{
    uint8_t none = 0;
    uint8_t syn = 1;
    uint8_t ack = 2;
    uint8_t syn_ack = 3;
    uint8_t fin = 4;
    uint8_t fin_syn = 5;
    uint8_t fin_ack = 6;
    uint8_t fin_ack_syn = 7;

    ptrIpap_t1->syn = false;
    ptrIpap_t1->ack = false;
    ptrIpap_t1->fin = false;
    CPPUNIT_ASSERT(  ptrIpap_t1->get_flags() == none);

    ptrIpap_t1->syn = true;
    ptrIpap_t1->ack = false;
    ptrIpap_t1->fin = false;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == syn);

    ptrIpap_t1->syn = false;
    ptrIpap_t1->ack = true;
    ptrIpap_t1->fin = false;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == ack);

    ptrIpap_t1->syn = false;
    ptrIpap_t1->ack = false;
    ptrIpap_t1->fin = true;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == fin);

    ptrIpap_t1->syn = true;
    ptrIpap_t1->ack = true;
    ptrIpap_t1->fin = false;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == syn_ack);

    ptrIpap_t1->syn = true;
    ptrIpap_t1->ack = false;
    ptrIpap_t1->fin = true;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == fin_syn);

    ptrIpap_t1->syn = false;
    ptrIpap_t1->ack = true;
    ptrIpap_t1->fin = true;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == fin_ack);

    ptrIpap_t1->syn = true;
    ptrIpap_t1->ack = true;
    ptrIpap_t1->fin = true;
    CPPUNIT_ASSERT( ptrIpap_t1->get_flags() == fin_ack_syn);

}