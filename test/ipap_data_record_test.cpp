/*
 * Test the ipap_data_record_test class.
 *
 * $Id: ipap_data_record_test.cpp 2014-11-29 10:36:00 amarentes $
 * $HeadURL: https://./test/ipap_data_record_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_def.h"
#include "IpAp_field.h"
#include "IpAp_field_container.h"
#include "IpAp_data_record.h"

class IpAp_Data_Record_Test;

/*
 * We use a subclass for testing and make the test case a friend. This
 * way the test cases have access to protected methods and they don't have
 * to be public in ipap_fields.
 */
class ipap_data_record_test : public ipap_data_record 
{
  public:

    ipap_data_record_test(uint16_t _template_id)
        : ipap_data_record(_template_id) { }

    friend class IpAp_Data_Record_Test;
};


class IpAp_Data_Record_Test : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( IpAp_Data_Record_Test );

    CPPUNIT_TEST( testAssign );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();
    void testAssign();

  private:
    
    ipap_field field1;
    ipap_field field2;
    ipap_field field3;
    
    ipap_field_container field_container;
    ipap_data_record *data;

};

CPPUNIT_TEST_SUITE_REGISTRATION( IpAp_Data_Record_Test );


void IpAp_Data_Record_Test::setUp() 
{
        
    data = new ipap_data_record(256);
    field_container.initialize_forward();
    
}

void IpAp_Data_Record_Test::tearDown() 
{
    
}

void IpAp_Data_Record_Test::testAssign()
{

    uint8_t value8 = 1;
    uint32_t value32 = 3;
    uint8_t valuebyte0[5] = "1234";
    int num_fields = 0;
    int num_field_length = 0;

    // Int 1
    field1 = field_container.get_field( 0, IPAP_FT_SOURCEIPV4PREFIXLENGTH );
    ipap_value_field fvalue1 = field1.get_ipap_value_field(value8);
    data->insert_field(0, IPAP_FT_SOURCEIPV4PREFIXLENGTH, fvalue1);

    // Int 4
    field2 = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMESECONDS );
    ipap_value_field fvalue2 = field2.get_ipap_value_field(value32);
    data->insert_field(0, IPAP_FT_AUCTIONINGTIMESECONDS, fvalue2);

    //Address 4
    field3 = field_container.get_field( 0, IPAP_FT_SOURCEIPV4ADDRESS );
    ipap_value_field fvalue3 = field3.get_ipap_value_field((uint8_t *) valuebyte0, 4);
    data->insert_field(0, IPAP_FT_SOURCEIPV4ADDRESS, fvalue3);

    num_fields = data->get_num_fields();
    CPPUNIT_ASSERT( num_fields == 3 );

    ipap_value_field fieltmp = data->get_field(0, IPAP_FT_AUCTIONINGTIMESECONDS);
    CPPUNIT_ASSERT( fieltmp.get_value_int32() == value32 );

}