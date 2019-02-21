/*
 * Test the ipap_message_test class.
 *
 * $Id: ipap_message_test.cpp 2015-08-28 17:53:00 amarentes $
 * $HeadURL: https://./test/ipap_message_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_def.h"
#include "IpAp_data_record.h"
#include "IpAp_message.h"


class IpAp_Message_Test;

/*
 * We use a subclass for testing and make the test case a friend. This
 * way the test cases have access to protected methods and they don't have
 * to be public in mnslp_ipfix_fields.
 */
class ipap_message_test : public ipap_message {
  public:
	ipap_message_test(int domain_id, int ipap_version, bool _encode_network)
		: ipap_message(domain_id, ipap_version, _encode_network) { }
   
    ipap_message_test( unsigned char * param, size_t message_length, bool _encode_network)
		: ipap_message(param, message_length, _encode_network) { }

	ipap_message_test( ipap_message_test &rhs): ipap_message(rhs) { }

	friend class IpAp_Message_Test;
};

class IpAp_Message_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( IpAp_Message_Test );
	CPPUNIT_TEST( testAddTemplate );
	CPPUNIT_TEST( testExceptionAddTemplate );
	CPPUNIT_TEST( testDataRecords );
	CPPUNIT_TEST( testExportImport );
	CPPUNIT_TEST( testSynMessage );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();
	void testAddTemplate();
	void testExceptionAddTemplate();
	void testDataRecords();
	void testExportImport();
	void testSynMessage();

  private:
    
    ipap_message_test * mes;
    ipap_message_test * mes2;


};

CPPUNIT_TEST_SUITE_REGISTRATION( IpAp_Message_Test );


void IpAp_Message_Test::setUp() {
	
	try 
	{
		int domain_id = 6;
		mes = new ipap_message_test( domain_id, IPAP_VERSION, false);
		mes2 = new ipap_message_test( domain_id, IPAP_VERSION, true);
	}
	catch(ipap_bad_argument &e)
	{
		cout << "Error: " << e.what() << endl;
	}
	catch(Error &e)
	{
		cout << "Error setting up the log file: " << endl;
		throw e;
	}
	
}

void IpAp_Message_Test::testAddTemplate()
{

	try
	{ 
	
		uint16_t templatedataid = 0;
		int num_templates = 0;
		
		int nfields;
		int result;
		uint64_t time = 234234;
		
		uint8_t   buf[5]  = { 1, 2, 3, 4 };
						
		// Verifies the field add method.
		nfields = 4; // Maximum number of fields.
		templatedataid = mes->new_data_template( nfields, IPAP_SETID_AUCTION_TEMPLATE );
		mes->add_field(templatedataid, 0, IPAP_FT_IDAUCTION);
		mes->add_field(templatedataid, 0, IPAP_FT_STARTSECONDS);
		mes->add_field(templatedataid, 0, IPAP_FT_ENDSECONDS);	
		mes->add_field(templatedataid, 0, IPAP_FT_AUCTIONINGALGORITHMNAME);
		num_templates = mes->get_num_templates();
		CPPUNIT_ASSERT( num_templates == 1 );
					
		// Verifies the method delete template, second it verifies with a valid template
		mes->delete_all_templates();
		num_templates = mes->get_num_templates();
		CPPUNIT_ASSERT( num_templates == 0 );
				
		templatedataid = mes->new_data_template( nfields, IPAP_SETID_BID_OBJECT_TEMPLATE );
		num_templates = mes->get_num_templates();
		CPPUNIT_ASSERT( num_templates == 1 );
						
		// Verifies the method delete template, second it verifies with a valid template
		mes->delete_template(templatedataid);
		num_templates = mes->get_num_templates();
		CPPUNIT_ASSERT( num_templates == 0 );
						
		ipap_field field1 = mes->get_field_definition( 0, IPAP_FT_ENDSECONDS );
		ipap_value_field fvalue3 = field1.get_ipap_value_field(time);
		
		mes->delete_all_templates();
				
		ipap_fields_t a[3]; 
		a[0].eno = 0;
		a[0].ienum = IPAP_FT_STARTSECONDS;
		a[0].length = 8;

		a[1].eno = 0;
		a[1].ienum = IPAP_FT_ENDSECONDS;
		a[1].length = 8;

		a[2].eno = 0;
		a[2].ienum = IPAP_FT_UNITBUDGET;
		a[2].length = 8;
		
		
		uint16_t templid= 256;
		
		mes->make_template(a, 3, IPAP_OPTNS_BID_OBJECT_TEMPLATE, templid);
		num_templates = mes->get_num_templates();
		CPPUNIT_ASSERT( num_templates == 1 );
	
	}
	catch(ipap_bad_argument &e)
	{
		cout << "Error: " << e.what() << endl;
		throw e;
	}
}


void IpAp_Message_Test::testExceptionAddTemplate()
{

	int nfields = 0;
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_SETID_AUCTION_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_OPTNS_AUCTION_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_SETID_BID_OBJECT_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_OPTNS_BID_OBJECT_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_SETID_ASK_OBJECT_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_OPTNS_ASK_OBJECT_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_SETID_ALLOC_OBJECT_TEMPLATE ),ipap_bad_argument);
	CPPUNIT_ASSERT_THROW( mes->new_data_template( nfields, IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE ),ipap_bad_argument);

	uint16_t templateAuctionid = 0;
	uint16_t templateBidid = 0;
	uint16_t templateAllocationid = 0;
	

	// Verifies that a data field cannot be added to a empty template
	CPPUNIT_ASSERT_THROW( mes->add_field(templateAuctionid, 0, IPAP_FT_STARTSECONDS), 
						  ipap_bad_argument);

	CPPUNIT_ASSERT_THROW( mes->add_field(templateBidid, 0, IPAP_FT_STARTSECONDS), 
						  ipap_bad_argument);

	CPPUNIT_ASSERT_THROW( mes->add_field(templateAllocationid, 0, IPAP_FT_STARTSECONDS), 
						  ipap_bad_argument);
			
	// Verifies that only add a valid field in the collection
	CPPUNIT_ASSERT_THROW( mes->add_field(templateAuctionid, 0, 3000),
						  ipap_bad_argument);
						  
	nfields = 3;
	templateAuctionid = mes->new_data_template( nfields, IPAP_SETID_AUCTION_TEMPLATE );

	// Verifies that only the maximum number of data fields can be inserted.
	mes->add_field(templateAuctionid, 0, IPAP_FT_STARTSECONDS);
	mes->add_field(templateAuctionid, 0, IPAP_FT_ENDSECONDS);
	mes->add_field(templateAuctionid, 0, IPAP_FT_STARTMILLISECONDS);
	CPPUNIT_ASSERT_THROW( mes->add_field(templateAuctionid, 0, IPAP_FT_ENDMILLISECONDS),
						  ipap_bad_argument);
	

	mes->delete_all_templates();


}


void IpAp_Message_Test::testDataRecords()
{

	uint16_t templatedataid = 0;
	uint16_t templatescopeid = 0;
	uint64_t starttime = 100;
	uint64_t endtime = 200;
	uint64_t octdel = 100;
	uint64_t packdel = 300;
	uint64_t packdel2 = 400;
	int num_templates = 0;
	unsigned char   *buf1  = (unsigned char *) "1";
	unsigned char   *buf1a  = (unsigned char *) "2";
	unsigned char   *buf1b  = (unsigned char *) "3";
	unsigned char   *buf2  = (unsigned char *) "bas";

	try
	{
		mes->delete_all_templates();
		
		int nfields = 4;
		templatedataid = mes->new_data_template( nfields, IPAP_SETID_AUCTION_TEMPLATE );
		mes->add_field(templatedataid, 0, IPAP_FT_IDAUCTION);
		mes->add_field(templatedataid, 0, IPAP_FT_STARTSECONDS);
		mes->add_field(templatedataid, 0, IPAP_FT_ENDSECONDS);	
		mes->add_field(templatedataid, 0, IPAP_FT_AUCTIONINGALGORITHMNAME);

		ipap_field field1 = mes->get_field_definition( 0, IPAP_FT_STARTSECONDS );
		ipap_value_field fvalue1 = field1.get_ipap_value_field( starttime );

		ipap_field field2 = mes->get_field_definition( 0, IPAP_FT_ENDSECONDS );
		ipap_value_field fvalue2 = field2.get_ipap_value_field( endtime );

		ipap_field field3 = mes->get_field_definition( 0, IPAP_FT_IDAUCTION );
		ipap_value_field fvalue3 = field3.get_ipap_value_field( buf1, 1 );
		ipap_value_field fvalue3a = field3.get_ipap_value_field( buf1a, 1 );
		ipap_value_field fvalue3b = field3.get_ipap_value_field( buf1b, 1 );
		
		ipap_field field4 = mes->get_field_definition( 0, IPAP_FT_AUCTIONINGALGORITHMNAME );
		ipap_value_field fvalue4 = field3.get_ipap_value_field( buf2, 3 );
		
		ipap_data_record data(templatedataid);
		data.insert_field(0, IPAP_FT_STARTSECONDS, fvalue1);
		data.insert_field(0, IPAP_FT_ENDSECONDS, fvalue2);
		data.insert_field(0, IPAP_FT_IDAUCTION, fvalue3);
		data.insert_field(0, IPAP_FT_AUCTIONINGALGORITHMNAME, fvalue4);
		mes->include_data(templatedataid, data);
		
		ipap_data_record data2(templatedataid);
		data2.insert_field(0, IPAP_FT_STARTSECONDS, fvalue1);
		data2.insert_field(0, IPAP_FT_ENDSECONDS, fvalue2);
		data2.insert_field(0, IPAP_FT_IDAUCTION, fvalue3);
		data2.insert_field(0, IPAP_FT_AUCTIONINGALGORITHMNAME, fvalue4);
		mes->include_data(templatedataid, data2);
		
		ipap_data_record data3(templatedataid);
		data3.insert_field(0, IPAP_FT_STARTSECONDS, fvalue1);
		data3.insert_field(0, IPAP_FT_ENDSECONDS, fvalue2);
		data3.insert_field(0, IPAP_FT_IDAUCTION, fvalue3b);
		data3.insert_field(0, IPAP_FT_AUCTIONINGALGORITHMNAME, fvalue4);
		mes->include_data(templatedataid, data3);
		
		
		CPPUNIT_ASSERT( data2 == data );
		CPPUNIT_ASSERT( data2 != data3);
		
		ipap_data_record data4 = data3;
		CPPUNIT_ASSERT( data3 == data4);
		
		int num_fields_record = data3.get_num_fields();
		CPPUNIT_ASSERT( num_fields_record == 4);

		ipap_value_field fvalue1b = data3.get_field(0, IPAP_FT_STARTSECONDS);
		CPPUNIT_ASSERT( fvalue1 == fvalue1b );
		
		mes->delete_all_templates();
		
	}
	catch(ipap_bad_argument &e)
	{
		cout << "Error: " << e.what() << endl;
		throw e;
	}
}


void IpAp_Message_Test::testExportImport()
{
	uint16_t templatedataid = 0;
	uint16_t templatescopeid = 0;

	uint64_t starttime = 100;
	uint64_t endtime = 200;
	uint64_t octdel = 100;
	uint64_t packdel = 300;
	uint64_t packdel2 = 400;
	uint32_t seqNbr = 4;
	uint32_t ackSeqNbr = 4;
	
	int num_templates = 0;
	unsigned char *buf1  = (unsigned char *) "1";
	unsigned char *buf1a = (unsigned char *) "2";
	unsigned char *buf1b = (unsigned char *) "3";
	unsigned char *buf2  = (unsigned char *) "bas";
	unsigned char *buf2a = (unsigned char *) "bas2";

	int nfields = 4;
	unsigned char * message;
	int offset;
	try
	{
		
		mes->delete_all_templates();

		templatedataid = mes->new_data_template( nfields, IPAP_SETID_AUCTION_TEMPLATE );
		mes->add_field(templatedataid, 0, IPAP_FT_IDAUCTION);
		mes->add_field(templatedataid, 0, IPAP_FT_STARTSECONDS);
		mes->add_field(templatedataid, 0, IPAP_FT_ENDSECONDS);	
		mes->add_field(templatedataid, 0, IPAP_FT_AUCTIONINGALGORITHMNAME);

		ipap_field field1 = mes->get_field_definition( 0, IPAP_FT_IDAUCTION );
		ipap_value_field fvalue1 = field1.get_ipap_value_field( buf1, 1 );
		ipap_value_field fvalue1a = field1.get_ipap_value_field( buf1a, 1 );

		ipap_field field2 = mes->get_field_definition( 0, IPAP_FT_STARTSECONDS );
		ipap_value_field fvalue2 = field2.get_ipap_value_field( starttime );

		ipap_field field3 = mes->get_field_definition( 0, IPAP_FT_ENDSECONDS );
		ipap_value_field fvalue3 = field3.get_ipap_value_field( endtime );

		ipap_field field4 = mes->get_field_definition( 0, IPAP_FT_AUCTIONINGALGORITHMNAME );
		ipap_value_field fvalue4 = field4.get_ipap_value_field( buf2, 3 );
		ipap_value_field fvalue4a = field4.get_ipap_value_field( buf2a, 4 );
		
		ipap_data_record data(templatedataid);
		data.insert_field(0, IPAP_FT_IDAUCTION, fvalue1);
		data.insert_field(0, IPAP_FT_STARTSECONDS, fvalue2);
		data.insert_field(0, IPAP_FT_ENDSECONDS, fvalue3);
		data.insert_field(0, IPAP_FT_AUCTIONINGALGORITHMNAME, fvalue4);
		mes->include_data(templatedataid, data);

		ipap_data_record data2(templatedataid);
		data2.insert_field(0, IPAP_FT_IDAUCTION, fvalue1a);
		data2.insert_field(0, IPAP_FT_STARTSECONDS, fvalue2);
		data2.insert_field(0, IPAP_FT_ENDSECONDS, fvalue3);
		data2.insert_field(0, IPAP_FT_AUCTIONINGALGORITHMNAME, fvalue4a);
		mes->include_data(templatedataid, data2);
		mes->set_seqno(seqNbr);
		mes->set_ackseqno(ackSeqNbr);
		mes->set_syn(true);
		mes->set_ack(true);

		cout << "offset:" << mes->get_offset() << "buffer lenght:" << mes->get_buff_len() << endl;

		mes->output();

		message = mes->get_message();
		offset = mes->get_offset();
		
		cout << "offset:" << mes->get_offset() << "buffer lenght:" << mes->get_buff_len() << endl;

		ipap_message_test msgb (message, offset, false);

		cout << "buffer lenght - new message:" << msgb.get_buff_len() << endl;

		num_templates = msgb.get_num_templates();
		CPPUNIT_ASSERT( num_templates == 1 );

		CPPUNIT_ASSERT(msgb.get_ackseqno() == ackSeqNbr);
		CPPUNIT_ASSERT(msgb.get_syn() == mes->get_syn());
		CPPUNIT_ASSERT(msgb.get_ack() == mes->get_ack());

		
		CPPUNIT_ASSERT( msgb.operator==( *mes) );

		cout << "Here we are 3 " << endl;

	}
	catch(ipap_bad_argument &e)
	{
		cout << "Error: " << e.what() << endl;
		throw e;
	}
	
	
}


void IpAp_Message_Test::testSynMessage()
{
	uint16_t templatedataid = 0;
	uint16_t templatescopeid = 0;

	uint32_t seqNbr = 4;
	unsigned char * message;

    mes2->set_syn(true);
    mes2->set_seqno(1212);
    mes2->output();

	message = mes2->get_message();

    CPPUNIT_ASSERT(message != NULL );

    int length = mes2->get_lenght();
    cout << "message salida - message length" << length <<  endl;
    for (int i = 0; i < length; i++){
         cout << "i" << i << ":" << static_cast<unsigned>(*(message + i)) << endl;
    }

    cout << endl;

}


void IpAp_Message_Test::tearDown() 
{
	delete(mes);
	delete(mes2);
}
