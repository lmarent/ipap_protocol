/*
 * Test the ipap_field_test.cpp class.
 *
 * $Id: ipap_field_test.cpp 2015-08-28 14:54:00 amarentes $
 * $HeadURL: https://./test/ipap_field_test.cpp $
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IpAp_def.h"
#include "IpAp_field.h"
#include "IpAp_field_container.h"


class IpAp_Field_Test;


/*
 * We use a subclass for testing and make the test case a friend. This
 * way the test cases have access to protected methods and they don't have
 * to be public in mnslp_ipfix_fields.
 */
class ipap_field_test : public ipap_field {
  public:
	ipap_field_test(ipap_field_type_t param)
		: ipap_field(param) { }

	friend class IpAp_Field_Test;
};


class IpAp_Field_Test : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( IpAp_Field_Test );

	CPPUNIT_TEST( testGetters );
	CPPUNIT_TEST( testAssign );
	CPPUNIT_TEST( testAddFields );
	CPPUNIT_TEST_EXCEPTION( testException, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionInt1, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionInt2, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionInt4, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionInt8, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionAddress4, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionAddress16, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionString, ipap_bad_argument );
	CPPUNIT_TEST_EXCEPTION( testExceptionByteFixed, ipap_bad_argument );
    CPPUNIT_TEST( testFieldValues );
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp();
	void tearDown();

	void testGetters();
	void testAssign();
	void testException();
	void testAddFields();
	void testFieldValues();
	void testExceptionInt1();
	void testExceptionInt2();
	void testExceptionInt4();
	void testExceptionInt8();
	void testExceptionAddress4();
	void testExceptionAddress16();
	void testExceptionString();
	void testExceptionByteFixed();

  private:
    ipap_field_type_t field1;
    ipap_field_type_t field2;
    ipap_field_type_t field3;
    
    ipap_field *ptrField1;
    ipap_field *ptrField2;
    
    ipap_field_container field_container;

};

CPPUNIT_TEST_SUITE_REGISTRATION( IpAp_Field_Test );




void IpAp_Field_Test::setUp() {
	
	field1.eno = 0;  
	field1.ftype = IPAP_FT_MAXUNITVALUATION;
	field1.length = 8; 
	field1.coding =  IPAP_CODING_DOUBLE;
	field1.name = "auctionMaxUnitValuation";
	field1.xml_name = "MaxUnitValuation";
	field1.documentation = "";

	field2.eno = 0;  
	field2.ftype = IPAP_FT_UNITVALUE;
	field2.length = 8; 
	field2.coding =  IPAP_CODING_DOUBLE;
	field2.name = "auctionUnitValue";
	field2.xml_name = "UnitValue";
	field2.documentation = "";

	field3.eno = 0;  
	field3.ftype = IPAP_FT_UNITBUDGET;
	field3.length = 8; 
	field3.coding =  IPAP_CODING_DOUBLE;
	field3.name = "auctionUnitBudget";
	field2.xml_name = "UnitBudget";
	field3.documentation = "";

	ptrField1 = new ipap_field(field1);
	ptrField2 = new ipap_field(field2);

    ipap_field_container field_container = ipap_field_container();
}

void IpAp_Field_Test::tearDown() 
{
	delete(ptrField1);
	delete(ptrField2);
}

void IpAp_Field_Test::testGetters() 
{
	ipap_field_type_t tmp = ptrField1->get_field_type();
	CPPUNIT_ASSERT( tmp.ftype == field1.ftype );
	CPPUNIT_ASSERT( tmp.length == field1.length );
	CPPUNIT_ASSERT( tmp.coding == field1.coding );
	CPPUNIT_ASSERT( tmp.name == field1.name );
	CPPUNIT_ASSERT( tmp.documentation == field1.documentation );
}

void IpAp_Field_Test::testAssign() 
{
    ipap_field tmpField = *ptrField2;
    ipap_field_type_t tmp = tmpField.get_field_type();
    
	CPPUNIT_ASSERT( tmp.ftype == field2.ftype );
	CPPUNIT_ASSERT( tmp.length == field2.length );
	CPPUNIT_ASSERT( tmp.coding == field2.coding );
	CPPUNIT_ASSERT( tmp.name == field2.name );
	CPPUNIT_ASSERT( tmp.documentation == field2.documentation );
	
	
}

void IpAp_Field_Test::testException() 
{

    field_container.clear();     

	field_container.AddFieldType( 0, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_DOUBLE, 
     "auctionUnitBudget", "UnitBudget", "" );

	field_container.AddFieldType( 0, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_DOUBLE, 
     "auctionTotalBudget", "TotalBudget", "" );
         
    CPPUNIT_ASSERT( field_container.get_num_fields() == 2 );

}

void IpAp_Field_Test::testAddFields()
{
	field_container.initialize_forward();
	
	CPPUNIT_ASSERT( field_container.get_num_fields() == TOT_FIELD_COUNT );
	
	field_container.initialize_reverse();
	
	CPPUNIT_ASSERT( field_container.get_num_fields() == (TOT_FIELD_COUNT) * 2 );
	
	// Gets one of the fields and verifies its data.
	ipap_field tmpField = field_container.get_field( 0, IPAP_FT_UNITVALUE );
    ipap_field_type_t tmp = tmpField.get_field_type();
    
	CPPUNIT_ASSERT( tmp.ftype == field2.ftype );
	CPPUNIT_ASSERT( tmp.length == field2.length );
	CPPUNIT_ASSERT( tmp.coding == field2.coding );
	CPPUNIT_ASSERT( tmp.name == field2.name );
	CPPUNIT_ASSERT( tmp.documentation == field2.documentation );	
	
}

void IpAp_Field_Test::testFieldValues()
{
	uint8_t value8 = 8;
	uint16_t value16 = 21;
	uint32_t value32 = 3210;
	uint64_t value64 = 87654321;
	float valfloat = 0.15;
	double valdouble = 0.15;
	char valuechar[5] = "1234";
	uint8_t valuebyte0[5] = { 1, 2, 3, 4 };
	uint8_t valuebyte1[7] = { 1, 2, 3, 4, 5, 6 };
	uint8_t valuebyte2[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	uint8_t valuebyte3[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	char * charprint;
	char * charprint2;
	
	uint8_t *out;
	bool equal = true;
	
    field_container.clear();   
	field_container.initialize_forward();
	out = ( uint8_t* ) calloc (100, sizeof(uint8_t) );
	charprint = (char *) calloc (100, sizeof(char) );
	charprint2 = (char *) calloc (100, sizeof(char) );
	int relay_f;
	ipap_field tmpField;
		
	// UInt 1
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV6PREFIXLENGTH );
	ipap_value_field fvalue1 = tmpField.get_ipap_value_field(value8);
	
	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_int( fvalue1, out, relay_f );
	ipap_value_field fvalue1aResult = tmpField.ipap_decode_int( out, fvalue1.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint8_t) 8 == fvalue1aResult.get_value_int8() );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_int( fvalue1, out, relay_f );
	ipap_value_field fvalue1bResult = tmpField.ipap_decode_int( out, fvalue1.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint8_t) 8 == fvalue1bResult.get_value_int8() );
	tmpField.ipap_snprint_int( charprint, 100, fvalue1bResult );
	std::string str(charprint, charprint + fvalue1bResult.get_length());
	CPPUNIT_ASSERT( str.compare("8")  == 0 );
	
	// Test write to and read from string
	string tmpFieldStr = tmpField.writeValue(fvalue1bResult);
	ipap_value_field fvalue1cResult = tmpField.parse(tmpFieldStr);
	CPPUNIT_ASSERT( (uint8_t) 8 == fvalue1cResult.get_value_int8() );

	// Int 4
	tmpField = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMESECONDS );
	ipap_value_field fvalue3 = tmpField.get_ipap_value_field(value32);
	CPPUNIT_ASSERT( (uint32_t) 3210 == fvalue3.get_value_int32() );
	tmpField.ipap_snprint_int( charprint, 100, fvalue3 );
	std::string str3(charprint, charprint + fvalue3.get_length());
	CPPUNIT_ASSERT( str3.compare("3210")  == 0 );

		// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_int( fvalue3, out, relay_f );
	ipap_value_field fvalue3aResult = tmpField.ipap_decode_int( out, fvalue3.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint32_t) 3210 == fvalue3aResult.get_value_int32() );
		
		// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_int( fvalue3, out, relay_f );
	ipap_value_field fvalue3bResult = tmpField.ipap_decode_int( out, fvalue3.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint32_t) 3210 == fvalue3bResult.get_value_int32() );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue3aResult);
	ipap_value_field fvalue3cResult = tmpField.parse(tmpFieldStr);
	CPPUNIT_ASSERT( (uint32_t) 3210 == fvalue3cResult.get_value_int32() );

    //Address 4
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV4ADDRESS );
	ipap_value_field fvalue4 = tmpField.get_ipap_value_field((uint8_t *) valuebyte0, 4);
	uint8_t * valuebyte4 = fvalue4.get_value_address();
	for (int i=0; i < 4; i++)
		if (valuebyte0[i] != valuebyte4[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
	
	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_bytes( fvalue4, out, relay_f );
	ipap_value_field fvalue4aResult = tmpField.ipap_decode_bytes( out, fvalue4.get_length(), relay_f );	
	uint8_t * valuebyte4a = fvalue4.get_value_address();
	for (int i=0; i < 4; i++)
		if (valuebyte0[i] != valuebyte4a[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_int( fvalue4, out, relay_f );
	ipap_value_field fvalue4bResult = tmpField.ipap_decode_int( out, fvalue4.get_length(), relay_f );	
	uint8_t * valuebyte4b = fvalue4.get_value_address();
	for (int i=0; i < 4; i++)
		if (valuebyte0[i] != valuebyte4b[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue4aResult);
		
	ipap_value_field fvalue4cResult = tmpField.parse(tmpFieldStr);
	valuebyte4a = fvalue4cResult.get_value_address();
	for (int i=0; i < 4; i++)
		if (valuebyte0[i] != valuebyte4a[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
	  
	// Int 8 
	tmpField = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMEMILLISECONDS );
	ipap_value_field fvalue5 = tmpField.get_ipap_value_field(value64);
	uint64_t printv5 = fvalue5.get_value_int64();
	CPPUNIT_ASSERT( printv5 == value64 );
	
	tmpField.ipap_snprint_int( charprint, 100, fvalue5 );
	std::string str5(charprint, charprint + fvalue5.get_length());
	std::ostringstream o1;
	o1 << value64;
	std::string str6 = o1.str();
	CPPUNIT_ASSERT( str5.compare(str6)  == 0 );
	
	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_int( fvalue5, out, relay_f );
	ipap_value_field fvalue5aResult = tmpField.ipap_decode_int( out, fvalue5.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint64_t) 87654321 == fvalue5aResult.get_value_int64() );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_int( fvalue5, out, relay_f );
	ipap_value_field fvalue5bResult = tmpField.ipap_decode_int( out, fvalue5.get_length(), relay_f );	
	CPPUNIT_ASSERT( (uint64_t) 87654321 == fvalue5bResult.get_value_int64() );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue5aResult);
	ipap_value_field fvalue5cResult = tmpField.parse(tmpFieldStr);
	CPPUNIT_ASSERT( (uint64_t) 87654321 == fvalue5cResult.get_value_int64() );
		
	// Address 16
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV6ADDRESS );
	ipap_value_field fvalue6 = tmpField.get_ipap_value_field((uint8_t *) valuebyte3, 16);
	uint8_t * valuebyte6 = fvalue6.get_value_address();
	for (int i=0; i < 16; i++)
		if (valuebyte6[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );	

	// Verifies string conversion of IPV6
	
	string ipv6String = tmpField.writeValue(fvalue6);
	ipap_value_field fvalueIPv6 = tmpField.parse(ipv6String);
	ipv6String = tmpField.writeValue(fvalueIPv6);

	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_bytes( fvalue6, out, relay_f );
	ipap_value_field fvalue6aResult = tmpField.ipap_decode_bytes( out, fvalue6.get_length(), relay_f );	
	uint8_t * valuebyte6a = fvalue6aResult.get_value_address();
	for (int i=0; i < 16; i++)
		if (valuebyte6a[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
	
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_bytes( fvalue6, out, relay_f );
	ipap_value_field fvalue6bResult = tmpField.ipap_decode_bytes( out, fvalue6.get_length(), relay_f );	
	uint8_t * valuebyte6b = fvalue6bResult.get_value_address();
	for (int i=0; i < 16; i++)
		if (valuebyte6b[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue6aResult);
	ipap_value_field fvalue6cResult = tmpField.parse(tmpFieldStr);
	valuebyte6b = fvalue6cResult.get_value_address();
	for (int i=0; i < 16; i++)
		if (valuebyte6b[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Bytes
	tmpField = field_container.get_field( 0, IPAP_FT_POSTDESTINATIONMACADDRESS );
	ipap_value_field fvalue7 = tmpField.get_ipap_value_field((uint8_t *) valuebyte1, 6);
	uint8_t * valuebyte7 = fvalue7.get_value_byte();
	for (int i=0; i < 6; i++)
		if (valuebyte7[i] != valuebyte1[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
    

	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_bytes( fvalue7, out, relay_f );
	ipap_value_field fvalue7aResult = tmpField.ipap_decode_bytes( out, fvalue7.get_length(), relay_f );	
	uint8_t * valuebyte7a = fvalue7aResult.get_value_byte();
	for (int i=0; i < 6; i++)
		if (valuebyte7a[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_bytes( fvalue7, out, relay_f );
	ipap_value_field fvalue7bResult = tmpField.ipap_decode_bytes( out, fvalue7.get_length(), relay_f );	
	uint8_t * valuebyte7b = fvalue7bResult.get_value_byte();
	for (int i=0; i < 6; i++)
		if (valuebyte7b[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue7bResult);
	ipap_value_field fvalue7cResult = tmpField.parse(tmpFieldStr);
	valuebyte7b = fvalue7cResult.get_value_byte();
	for (int i=0; i < 6; i++)
		if (valuebyte7b[i] != valuebyte3[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Bytes - variable length
	tmpField = field_container.get_field( 0, IPAP_FT_IPHEADERPACKETSECTION );
	ipap_value_field fvalue8 = tmpField.get_ipap_value_field((uint8_t *) valuebyte2, 14);
	uint8_t * valuebyte8 = fvalue8.get_value_byte();
	for (int i=0; i < 14; i++)
		if (valuebyte8[i] != valuebyte2[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );


	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_bytes( fvalue8, out, relay_f );
	ipap_value_field fvalue8aResult = tmpField.ipap_decode_bytes( out, fvalue8.get_length(), relay_f );	
	uint8_t * valuebyte8a = fvalue8aResult.get_value_byte();
	for (int i=0; i < 14; i++)
		if (valuebyte8a[i] != valuebyte2[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_bytes( fvalue8, out, relay_f );
	ipap_value_field fvalue8bResult = tmpField.ipap_decode_bytes( out, fvalue8.get_length(), relay_f );	
	uint8_t * valuebyte8b = fvalue8bResult.get_value_byte();
	for (int i=0; i < 14; i++)
		if (valuebyte8b[i] != valuebyte2[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue8bResult);
	ipap_value_field fvalue8cResult = tmpField.parse(tmpFieldStr);
	valuebyte8b = fvalue8cResult.get_value_byte();
	for (int i=0; i < 14; i++)
		if (valuebyte8b[i] != valuebyte2[i]) equal = false;
	CPPUNIT_ASSERT( true == equal );
	
	// Double 8
	tmpField = field_container.get_field( 0, IPAP_FT_UNITBUDGET );
	ipap_value_field fvalue9 = tmpField.get_ipap_value_field(valdouble);
	double double1 = fvalue9.get_value_double();
	CPPUNIT_ASSERT( double1 == valdouble );

	
	// Test without encoding
	relay_f = 1;
	tmpField.ipap_encode_double( fvalue9, out, relay_f );
	ipap_value_field fvalue9aResult = tmpField.ipap_decode_double( out, fvalue9.get_length(), relay_f );	
	CPPUNIT_ASSERT( valdouble == fvalue9aResult.get_value_double() );
		
	// Test with encoding
	relay_f = 0;
	tmpField.ipap_encode_double( fvalue9, out, relay_f );
	ipap_value_field fvalue9bResult = tmpField.ipap_decode_double( out, fvalue9.get_length(), relay_f );	
	CPPUNIT_ASSERT(  valdouble == fvalue9bResult.get_value_double() );

	// Test write to and read from string
	tmpFieldStr = tmpField.writeValue(fvalue9aResult);
	ipap_value_field fvalue9cResult = tmpField.parse(tmpFieldStr);
	CPPUNIT_ASSERT(  valdouble == fvalue9cResult.get_value_double() );

	
}

void IpAp_Field_Test::testExceptionInt1()
{
	uint8_t value8 = 1;
	uint16_t value16 = 2;

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	// Int 1
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV4PREFIXLENGTH );
	ipap_value_field fvalue1 = tmpField.get_ipap_value_field(value16);
	
}

void IpAp_Field_Test::testExceptionInt2()
{
	uint8_t value8 = 1;
	uint16_t value16 = 2;

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	// Int 2
	tmpField = field_container.get_field( 0, IPAP_FT_AUCTIONINGALGORITHMCODE );
	ipap_value_field fvalue2 = tmpField.get_ipap_value_field(value8);	
	
}

void IpAp_Field_Test::testExceptionInt4()
{
	uint16_t value16 = 2;
	uint32_t value32 = 3;
	

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	// Int 4
	tmpField = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMESECONDS );
	ipap_value_field fvalue3 = tmpField.get_ipap_value_field(value16);
	
}

void IpAp_Field_Test::testExceptionInt8()
{
	uint32_t value32 = 3;
	uint64_t value64 = 4;
	
    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	// Int 8 
	tmpField = field_container.get_field( 0, IPAP_FT_AUCTIONINGTIMEMILLISECONDS );
	ipap_value_field fvalue5 = tmpField.get_ipap_value_field(value32);
	
}

void IpAp_Field_Test::testExceptionAddress4()
{
	uint8_t valuebyte0[5] = "1234";

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

    //Address 4
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV4ADDRESS );
	ipap_value_field fvalue4 = tmpField.get_ipap_value_field((uint8_t *) valuebyte0, 10);


}

void IpAp_Field_Test::testExceptionAddress16()
{
	uint8_t valuebyte3[17] = "1234567891011122";

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	// Address 16
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV6ADDRESS );
	ipap_value_field fvalue6 = tmpField.get_ipap_value_field( (uint8_t *) valuebyte3, 10);

}

void IpAp_Field_Test::testExceptionString()
{
	
	char valuechar[7] = "123467";
    field_container.clear();   
	field_container.initialize_forward();
	ipap_field tmpField;
	
	tmpField = field_container.get_field( 0, IPAP_FT_SOURCEIPV4ADDRESS );
	ipap_value_field fvalue6 = tmpField.get_ipap_value_field( (char *) valuechar, 4);
	
	
}

void IpAp_Field_Test::testExceptionByteFixed()
{
	uint8_t valuebyte1[7] = "123456";

    field_container.clear();   
	field_container.initialize_forward();

	ipap_field tmpField;

	tmpField = field_container.get_field( 0, IPAP_FT_POSTDESTINATIONMACADDRESS );
	ipap_value_field fvalue7 = tmpField.get_ipap_value_field((uint8_t *) valuebyte1, 5);
}
// EOF
