/*! \file   IpAp_field_value.cpp

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

    $Id: ApAp_field_value.cpp 748 2015-08-26 18:48:00Z amarentes $
*/

#include "IpAp_value_field.h"

ipap_value_field::~ipap_value_field()
{
	if (valuechar != NULL)
		free( valuechar );
	
	if ( valuebyte != NULL )
		free( valuebyte );

}

void
ipap_value_field::set_value_vunit8(uint8_t * _valuebyte, int _length)
{
	
	valuebyte = (uint8_t*) malloc(sizeof(uint8_t) * _length);
	memcpy ( valuebyte, _valuebyte, _length );
	length = _length;
}

void 
ipap_value_field::set_value_float32(float &_value)
{
	uint8_t * tmp;	
	int len = sizeof(float) * sizeof(uint8_t);
	tmp = (uint8_t *) malloc ((size_t) len);
	memcpy (tmp, &_value, sizeof(float) );
		
	set_value_vunit8( tmp, len); 	
	free(tmp);

}

void 
ipap_value_field::set_value_float64(double &_value)
{
	uint8_t * tmp;
	int len = (int) sizeof(double) * sizeof(uint8_t);
	tmp = (uint8_t *) malloc (sizeof(double) * sizeof(uint8_t));
	memcpy (tmp, &_value, sizeof(double) );		
	set_value_vunit8( tmp, len);
	free(tmp);
}


void
ipap_value_field::set_value_vchar(char * _valuechar, int _length)
{

	valuechar = (char *)malloc(sizeof(char *) * _length);
	memcpy ( valuechar, _valuechar, _length );
	length = _length;
}

float 
ipap_value_field::get_value_float()
{
	float fvalue;
    
    if (length == sizeof(float)){
		memcpy ( &fvalue, valuebyte, sizeof(float) );
		return fvalue;
    } else{
		throw ipap_bad_argument("Value is not a float value");
    }
}

double 
ipap_value_field::get_value_double()
{
	double dvalue;
    
    if (length == sizeof(double)){
		memcpy ( &dvalue, valuebyte, sizeof(double) );
		return dvalue;
    } else{
		throw ipap_bad_argument("Value is not a double value");
    }
}

ipap_value_field::ipap_value_field(const ipap_value_field &param)
{
	
	value8 = param.value8;
	value16 = param.value16;
	value32 = param.value32;
	value64 = param.value64;
	length = param.length;
	
	if ((param.valuechar != NULL) && (param.length > 0))
	{
		valuechar = (char *)malloc(sizeof(char *) * param.length);
		length = param.length;
		for (int i=0; i < param.length; i++)
			valuechar[i] = param.valuechar[i];
	}
	else
	{
		valuechar = NULL;
	}
	
	if ((param.valuebyte != NULL) && (param.length > 0) )
	{
		valuebyte = (uint8_t*)malloc(sizeof(uint8_t) * param.length);
		length = param.length;
		for (int i=0; i < param.length; i++)
			valuebyte[i] = param.valuebyte[i];
	}
	else
	{
		valuebyte = NULL;
	}

}

ipap_value_field& 
ipap_value_field::operator= (const ipap_value_field &param)
{
		
	value8 = param.value8;
	value16 = param.value16;
	value32 = param.value32;
	value64 = param.value64;
	length = param.length;
	
	if ((param.valuechar != NULL) && (param.length > 0))
	{
		valuechar = (char *)malloc(sizeof(char *) * param.length);
		length = param.length;
		for (int i=0; i < param.length; i++)
			valuechar[i] = param.valuechar[i];
	}
	else
	{
		valuechar = NULL;
	}
	
	if ((param.valuebyte != NULL) && (param.length > 0))
	{
		valuebyte = (uint8_t*)malloc(sizeof(uint8_t) * param.length);
		length = param.length;
		for (int i=0; i < param.length; i++)
			valuebyte[i] = param.valuebyte[i];
	}
	else
	{
		valuebyte = NULL;
	}
}


bool
ipap_value_field::operator==(const ipap_value_field &param) const
{

	if ( ((param.valuechar == NULL ) and (valuechar == NULL)) 
	    and ((param.valuebyte == NULL ) and (valuebyte == NULL)) ) {
			
		if (length != param.length)
			return false;
				
		if ( (value8 != param.value8) and (length == 1))
			return false;
		
		if ((value16 != param.value16) and (length == 2))
			return false;
		
		if ((value32 != param.value32) and (length == 4))
			return false;

		if ((value64 != param.value64) and (length == 8))
			return false;	
	}
	else
	{
	
		/* It is different it they have the valuechar different */
		if ((param.valuechar == NULL ) and (valuechar != NULL))
			return false;
			
		else if ((param.valuechar != NULL ) and (valuechar == NULL))
			return false;
			
		else if ((param.valuechar != NULL ) 
				  and (valuechar != NULL) 
				  and (param.length != length))
			return false;
		
		if ((param.valuechar != NULL) && (param.length > 0))
		{
			for (int i=0; i < param.length; i++)
				if ( valuechar[i] != param.valuechar[i])
					return false;
		}
		
		/* It is different it they have the valuebyte different */
		if ((param.valuebyte == NULL ) and (valuebyte != NULL))
			return false;
		else if ((param.valuebyte != NULL ) and (valuebyte == NULL))
			return false;
		else if ((param.valuebyte != NULL ) 
				  and (valuebyte != NULL) 
				  and (param.length != length))
			return false;
			
		if ((param.valuebyte != NULL) && (param.length > 0) )
		{
			for (int i=0; i < param.length; i++)
				if ( valuebyte[i] != param.valuebyte[i])
					return false;
		}

	}
	
	return true;
}

bool
ipap_value_field::operator!=( const ipap_value_field &param) const
{
	return !(operator==(param));
}

void ipap_value_field::print(void)
{
	
	if (valuechar != NULL )
	{
		for (int i=0; i < length; i++)
			std::cout << valuechar[i];
	}
	
	if (valuebyte != NULL )
	{
		
		for (int i=0; i < length; i++)
			std::cout << valuebyte[i];
	}
	
}

std::string ipap_value_field::to_string(void)
{
	
	std::ostringstream o1;
	o1 << "legth:";
	o1 << length;

	if (valuechar != NULL )
	{
		o1 << "valueChar:"; 
		for (int i=0; i < length; i++)
			o1 << valuechar[i];
	}
	
	if (valuebyte != NULL )
	{
		
		o1 << "valueByte:"; 
		for (int i=0; i < length; i++)
			o1 << valuebyte[i];
	}

	if ((length == 1) and (valuechar == NULL) and (valuebyte == NULL)){
		o1 << "Value8:";
		o1 << value8;
	}
	
	if ((length == 2) and (valuechar == NULL) and (valuebyte == NULL)){
		o1 << "Value16:";
		o1 << value16;
	}
	
	if ((length == 4) and (valuechar == NULL) and (valuebyte == NULL)){
		o1 << "Value32:";
		o1 << value32;
	}

	if ((length == 8) and (valuechar == NULL) and (valuebyte == NULL)){
		o1 << "Value64:";
		o1 << value64;
	}
		
	return o1.str();
}

