/*! \file   IpAp_field.h

    Copyright 2014-2015 Universidad de los Andes, Bogotá, Colombia

    This file is part of IP Auction Processing protocol (IPAP).

    IPAP is free software; you can redistribute it and/or modify 
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    IPAP is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this software; if not, write to the Free Software 
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Description:
    field vector declarations of ipap protocol

    $Id: ApAp_field.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_FIELD_H
#define IPAP_FIELD_H

#include "stdincpp.h"
#include "IpAp_def.h"
#include "IpAp_value_field.h"
#include "IpAp_exception.h"




#ifndef NTOHLL

#define HTONLL(val)  (((uint32_t) 0x0a0b0c0d != ntohl( (uint32_t) 0x0a0b0c0d )) ? ((uint64_t)(htonl((uint32_t)((val)>>32))) | \
                          (((uint64_t)htonl((uint32_t)((val)&0xFFFFFFFF)))<<32)) : (val))
#define NTOHLL(val)  (((uint32_t) 0x0a0b0c0d != ntohl( (uint32_t) 0x0a0b0c0d )) ? ((uint64_t)(ntohl((uint32_t)((val)>>32))) | \
                          (((uint64_t)ntohl((uint32_t)((val)&0xFFFFFFFF)))<<32)) : (val))
#endif


class ipap_value_field;

/**
 * \class ipap_field
 *
 *
 * \brief This respresents a field to be exchanged
 *
 * This class is used to represent a field that is going to be exchange.
 * a field for this project knows how to create its corresponding field
 * value, it also knows how to encode, decode and convert to string a field value
 *
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2015/08/26 20:29:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */
class ipap_field
{
	private:
	
		ipap_field_type_t field_type;  ///< Type of this field.
	
	public:
	
		
		/** Constructor without parameters, this is required for the template class 
		*/
		ipap_field();
		
		/** Constructor. Creates a field 
		*  @param Takes the field type and creates the field 
		*/
		ipap_field(ipap_field_type_t &param);
		
		/** Constructor from the data of another instance
		 *
		 */
		ipap_field(const ipap_field &rhs); 
		
		/** Destructor.
		*/
		~ipap_field();
		
		/** Assignment operator. It equals a field from another field value.
		*  @param  the field to copy from.
		*/
		ipap_field& operator= (const ipap_field&);
		
		/** Equal operator. verifies is the field given as parameter is equal
		*  @param  the field to compare
		*/
		inline bool operator== (const ipap_field& rhs)
		{ 
			return (field_type.eno == (rhs.field_type).eno ) && (field_type.ftype == (rhs.field_type).ftype); 
		}

		/** Equal operator. verifies is the field given as parameter is not equal
		*  @param  the field to compare
		*/
		inline bool operator!= (const ipap_field& rhs)
		{ 
			return (field_type.eno != (rhs.field_type).eno ) || (field_type.ftype != (rhs.field_type).ftype); 
		}
				
		/** Get the field type
		*  @param  None
		*/
		inline ipap_field_type_t get_field_type(){ return field_type; }
		
		/** Encode a field value of type int into a uint8_t array. 
		*   verifies that the value is of type int. 
		*  @param  in - value to enconce
		* 		   out - array where the method puts the information
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		int ipap_encode_int( ipap_value_field &in, uint8_t *out, int relay_f );

		/** Decode from a uint8_t array to a field value of type int.
		*   verifies that the value is of type int. 
		*  @param  in - we take the value from param
		* 		   len - how many bytes are going to be taken
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		ipap_value_field ipap_decode_int( uint8_t *in, size_t len, int relay_f );
	
		/** Put the field value int into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_int( char * str, size_t size, ipap_value_field &in );

		/** Put the field value unsigned int into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_uint( char * str, size_t size, ipap_value_field &in );

		/** Encode a field value of type bytes into a uint8_t array. 
		*   verifies that the value is of type bytes. 
		*  @param  in - value to enconce
		* 		   out - array where the method put the information
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		int ipap_encode_bytes(ipap_value_field in, uint8_t *out, int relay_f );

		/** Decode from a uint8_t array to a field value of type bytes.
		*   verifies that the value is of type bytes. 
		*  @param  in - we take the value from param
		* 		   len - how many bytes are going to be taken
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		ipap_value_field ipap_decode_bytes( uint8_t *in, size_t len, int relay_f );

		/** Put a bytes field value into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_bytes( char * str, size_t size, ipap_value_field &in_field );

		/** Put an string field value into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_string( char * str, size_t size, ipap_value_field &in_field );

		/** Put an ip address field value into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_ipaddr( char * str, size_t size, ipap_value_field &in_field );

		/** Encode a field value of type float into a uint8_t array. 
		*   verifies that the value is of type float. 
		*  @param  in - value to enconce
		* 		   out - array where the method put the information
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		int ipap_encode_float( ipap_value_field in, uint8_t *out, int relay_f );
	
		/** Decode from a uint8_t array to a field value of type float.
		*   verifies that the value is a float type. 
		*  @param  in - we take the value from param
		* 		   len - how many bytes are going to be taken
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		ipap_value_field ipap_decode_float( uint8_t *in, size_t len, int relay_f );

		/** Put a float field value into a char string 
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int ipap_snprint_float( char * str, size_t size, ipap_value_field &in );

		/** Encode a field value of type string into a uint8_t array. 
		*  @param  in - value to enconce
		* 		   out - array where the method put the information
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		int ipap_encode_string(ipap_value_field in, uint8_t *out, int relay_f );

		/** Decode from a uint8_t array to a field value of type string.
		*  @param  in - we take the value from param
		* 		   len - how many bytes are going to be taken
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		ipap_value_field ipap_decode_string( uint8_t *in, size_t len, int relay_f );



		/** Get the field value from a field of type int of one character
		*  verifies that the field is of type int and one character long.
		*  @param  _value8 - Value that is going to be assigned
		*/
		ipap_value_field get_ipap_value_field(uint8_t &_value8);

		/** Get the field value from a field of type int of two characters
		*  verifies that the field is of type int and two characters long.
		*  @param  _value16 - Value that is going to be assigned
		*  @throw   ipap_exception The length of field is not one byte
		*/
		ipap_value_field get_ipap_value_field(uint16_t &_value16);

		/** Get the field value from a field of type int of four characters
		*  verifies that the field is of type int and four characters long.
		*  @param  _value32 - Value that is going to be assigned
		*  @throw   ipap_exception The length of field is not two bytes
		*/
		ipap_value_field get_ipap_value_field(uint32_t &_value32);

		/** Get the field value from a field of type int of eight characters
		*  verifies that the field is of type int and eight characters long.
		*  @param  _value64 - Value that is going to be assigned
		*  @throw   ipap_exception The length of field is not four bytes
		*/
		ipap_value_field get_ipap_value_field(uint64_t &_value64);

		/** Get the field value from a field of type char
		*  verifies that the field is of type char
		*  @param  _valuechar - Value that is going to be assigned
		* 		   _length	  - number of characters to copy from the _valuechar pointer
		*  @throw   ipap_exception The length of field is not eight bytes
		*/
		ipap_value_field get_ipap_value_field(char * _valuechar, int _length);

		/** Get the field value from a field of type unit8_t
		*  verifies that the field is of type char
		*  @param  _valuebyte - Value that is going to be assigned
		* 		   _length	  - number of characters to copy from the _valuebyte pointer
		*  @throw   ipap_exception The length requested is not as the field length
		*/
		ipap_value_field get_ipap_value_field(uint8_t * _valuebyte, int _length);
		
		/** Encode a field value. It takes the field type from the field 
		*   and encode based on the coding for that field type 
		*  @param  in - value to enconce
		* 		   out - array where the method put the information
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		* @throw   ipap_exception The length requested is not as the field length
		*/
		int encode( ipap_value_field in, 
						uint8_t *out, int relay_f);
				
		/** Decode a field value. It takes the field type from the field 
		*   and decode based on the coding for that field type 
		*  @param  in - value to deconce
		* 		   len - how many bytes are going to be taken
		* 		   relay_f - if 0 it must do network encoding, 
		* 						1 just copy the information.
		*/
		ipap_value_field decode( uint8_t *in, size_t len, int relay_f);
		
		/** Put a field value into a char string. It takes the field type from
		 *  the field object for who is call is method.
		*  @param  in - value to put
		* 		   str - string where the method puts the information
		* 		   size - number of characters allocated to str, so the method could no 
		* 				  copy more size characters.
		*/
		int snprint( char * str, size_t size, ipap_value_field &in );

};

#endif // IPAP_FIELD_H
