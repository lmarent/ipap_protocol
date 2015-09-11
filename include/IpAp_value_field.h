/*! \file   IpAp_field_value.h

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
    field value class of ipap protocol

    $Id: ApAp_field_value.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef _IPAP_VALUE_FIELD_H_
#define _IPAP_VALUE_FIELD_H_

#include "stdincpp.h"
#include "IpAp_exception.h"


/**
 * \class ipap_value_field
 *
 *
 * \brief This class respresents the value a of field to be exchanged.
 * 
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2014/12/18 9:57:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */

 
 
class ipap_value_field
{

private:
	uint8_t value8; 		///< The field is int, and it has one character
	uint16_t value16;		///< The field is int, and it has two characters
	uint32_t value32;		///< The field is int or float, and it has four characters
	uint64_t value64;		///< The field is int or float, and it has eight characters
	int length;				///< The length of the field value in characters
	char *valuechar;		///< The value is a character string
	uint8_t *valuebyte;		///< The value is a byte string
	
public:
	
	/** 
	 * Contructor of the class, it copies another field value
	 */
	ipap_value_field(const ipap_value_field &param);
	
	/** 
	 * Contructor of the class, creates a field value empty
	 */
	ipap_value_field():
		value8(0), value16(0), value32(0), value64(0), 
		length(0), valuechar(NULL), valuebyte(NULL) 
		 {};
		
	/** 
	 * Destructor of the class
	 */
	~ipap_value_field();
	
	/** 
	 * Assigment operator. 
	 * @param param - value to copy.
	 */
	ipap_value_field& operator= (const ipap_value_field &param);
	
	/** 
	 * Set the value as one byte long  - Int
	 * @param _value - value to copy.
	 */
	inline void set_value_int8(uint8_t &_value){value8 =_value; length = 1;}

	/** 
	 * Set the value as two byte long - Int
	 * @param _value - value to copy.
	 */
	inline void set_value_int16(uint16_t &_value){value16 =_value; length = 2;}

	/** 
	 * Set the value as four byte long - Int
	 * @param _value - value to copy.
	 */
	inline void set_value_int32(uint32_t &_value){value32 =_value; length = 4;}

	/** 
	 * Set the value as eight byte long - Int
	 * @param _value - value to copy.
	 */
	inline void set_value_int64(uint64_t &_value){value64 =_value; length = 8;}

	/** 
	 * Set the value as four byte long - float
	 * @param _value - value to copy.
	 */
	inline void set_value_float32(uint32_t &_value){value32 =_value; length = 4;}

	/** 
	 * Set the value as eight byte long - float
	 * @param _value - value to copy.
	 */
	inline void set_value_float64(uint64_t &_value){value64 =_value; length = 8;}

	/** 
	 * Set the value as a variable string of type unit8. 
	 * @param _value - value to copy.
	 * 		  _lenght - number of bytes to copy
	 */
	void set_value_vunit8(uint8_t * _valuebyte, int _length);

	/** 
	 * Set the value as a variable string of type char. 
	 * @param _value - value to copy.
	 * 		  _lenght - number of characters to copy
	 */
	void set_value_vchar(char * _valuechar, int _length);
	
	
	/** 
	 * Obtain the value as one byte long  - Int
	 */
	inline uint8_t get_value_int8(){ return value8; }

	/** 
	 * Obtain the value as two byte long  - Int
	 */
	inline uint16_t get_value_int16(){ return value16; }

	/** 
	 * Obtain the value as four byte long  - Int
	 */
	inline uint32_t get_value_int32(){ return value32; }

	/** 
	 * Obtain the value as eight byte long  - Int
	 */
	inline uint64_t get_value_int64(){ return value64; }

	/** 
	 * Obtain the value as float
	 */
	float get_value_float();
	
	/** 
	 * Obtain the value as double
	 */
	double get_value_double();

	/** 
	 * Obtain the value as string of characters
	 */
	inline char * get_value_string(){ return valuechar; }

	/** 
	 * Obtain the value as string of bytes
	 */
	inline uint8_t * get_value_byte(){ return valuebyte; }

	/** 
	 * Obtain the ip address represented as a byte string
	 */
	inline uint8_t * get_value_address(){ return valuebyte; }

	/** 
	 * Obtain the number of bytes required to represent the value
	 */
	inline int get_length(){ return length; }
	
	bool operator!= (const ipap_value_field &rhs) const;
	
	bool operator== (const ipap_value_field &rhs) const;
	
	/**
	 *Print the value on cout
	 */
	void print(void);
	
	/**
	 *Print the value in a string and return the string.
	 */
	std::string to_string(void);
	
};

#endif // _IPAP_VALUE_FIELD_H_
