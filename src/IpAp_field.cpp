/*! \file   IpAp_field.cpp

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

    $Id: IpAp_field.cpp 748 2015-08-27 14:49:00Z amarentes $
*/

#include "IpAp_field.h"

/* 
 * ipap information element list
 */
 


ipap_field::ipap_field()
{

}

ipap_field::ipap_field(ipap_field_type_t &param): field_type(param)
{

}

ipap_field::ipap_field(const ipap_field &rhs)
{
	field_type = rhs.field_type;
}

ipap_field::~ipap_field()
{
	
}

ipap_field& ipap_field::operator= (const ipap_field &param)
{
	field_type = param.field_type;
	return *this;
}


/*
 * descr: encode,decode,print funcs
 */
int ipap_field::ipap_encode_int( ipap_value_field &in, 
										 uint8_t *out, int relay_f )
{

    uint16_t      tmp16;
    uint32_t      tmp32;
    uint64_t      tmp64;
	
	if (relay_f)
	{
		switch ( in.get_length() )
		{
		  case 1:
			  out[0] = in.get_value_int8();
			  break;
		  case 2:
			  tmp16 = in.get_value_int16();
			  memcpy( out, &tmp16, in.get_length() );
			  break;
		  case 4:
			  tmp32 = in.get_value_int32();
			  memcpy( out, &tmp32, in.get_length() );
			  break;
		  case 8:
			  tmp64 = in.get_value_int64();
			  memcpy( out, &tmp64, in.get_length() );
			  break;
		  default:
			  memset( out, 0xff, in.get_length() );
			  return -1;
		}
		
	}
	else
	{
		switch ( in.get_length() )
		{
		  case 1:
			  out[0] = in.get_value_int8();
			  break;
		  case 2:
			  tmp16 = in.get_value_int16();
			  tmp16 = htons( tmp16 );
			  memcpy( out, &tmp16, in.get_length() );
			  break;
		  case 4:
			  tmp32 = in.get_value_int32();
			  tmp32 = htonl( tmp32 );
			  memcpy( out, &tmp32, in.get_length() );
			  break;
		  case 8:
			  tmp64 = in.get_value_int64();
			  tmp64 = HTONLL( tmp64 );
			  memcpy( out, &tmp64, in.get_length() );
			  break;
		  default:
			  memset( out, 0xff, in.get_length() );
			  return -1;
		}
    }
    return 0;
}

ipap_value_field 
ipap_field::ipap_decode_int( uint8_t *in, size_t len, int relay_f )
{
    unsigned char *i = (unsigned char*) in;
    uint16_t      tmp16;
    uint32_t      tmp32;
    uint64_t      tmp64;
	ipap_value_field value;
    if (relay_f)
    {
		switch ( len )
		{
		  case 1:
			  value = get_ipap_value_field(in[0]);
			  break;
		  case 2:
			  memcpy( &tmp16, in, len );
			  value = get_ipap_value_field(tmp16);
			  break;
		  case 4:
			  memcpy( &tmp32, i, len );
			  value = get_ipap_value_field(tmp32);
			  break;
		  case 8:
			  memcpy( &tmp64, i, len );
			  value = get_ipap_value_field(tmp64);
			  break;
		  default:
			  return value;
		}
	}
	else
	{
		switch ( len )
		{
		  case 1:
			  value = get_ipap_value_field(in[0]);
			  break;
		  case 2:
			  memcpy( &tmp16, i, len );
			  tmp16 = ntohs( tmp16 );
			  value = get_ipap_value_field(tmp16);
			  break;
		  case 4:
			  memcpy( &tmp32, i, len );
			  tmp32 = ntohl( tmp32 );
			  value = get_ipap_value_field(tmp32);
			  break;
		  case 8:
			  memcpy( &tmp64, i, len );
			  tmp64 = NTOHLL( tmp64 );
			  value = get_ipap_value_field(tmp64);
			  break;
		  default:
			  return value;	
		}
	}
    return value;
}

int ipap_field::ipap_snprint_int( char *str, size_t size, ipap_value_field &in )
{
    int8_t       tmp8;
    int16_t      tmp16;
    int32_t      tmp32;
    int64_t      tmp64;

    switch ( in.get_length() ) {
      case 1:
          return snprintf( str, size, "%d", in.get_value_int8() );
      case 2:
          return snprintf( str, size, "%d", in.get_value_int16() );
      case 4:
          return snprintf( str, size, "%d", in.get_value_int32() );
      case 8:
          return snprintf( str, size, "%lld", (long long int) in.get_value_int64() );
      default:
          break;
    }
    return snprintf( str, size, "err" );
}

int ipap_field::ipap_snprint_uint( char *str, size_t size, ipap_value_field &in )
{
    uint8_t       tmp8;
    uint16_t      tmp16;
    uint32_t      tmp32;
    uint64_t      tmp64;

    switch ( in.get_length() ) {
      case 1:
          return snprintf( str, size, "%u", in.get_value_int8() );
      case 2:
          return snprintf( str, size, "%u", in.get_value_int16() );
      case 4:
          return snprintf( str, size, "%u", (unsigned int)in.get_value_int32());
      case 8:
          return snprintf( str, size, "%llu", (long long unsigned int)in.get_value_int64() );
      default:
		  break;
    }
    return snprintf( str, size, "err" );
}

int ipap_field::ipap_encode_bytes( ipap_value_field in, 
								   uint8_t *out, 
								   int relay_f  )
{
    memcpy( out, in.get_value_byte(), in.get_length() );
    return 0;
}

int ipap_field::ipap_encode_string( ipap_value_field in, 
								   uint8_t *out, 
								   int relay_f  )
{
    memcpy( out, in.get_value_string(), in.get_length() );
    return 0;
}

ipap_value_field 
ipap_field::ipap_decode_string( uint8_t *in, size_t len, int relay_f )
{
    ipap_value_field value;
    value = get_ipap_value_field(in, (int) len);      
    return value;
}


ipap_value_field 
ipap_field::ipap_decode_bytes( uint8_t *in, size_t len, int relay_f )
{
    ipap_value_field value;
    value = get_ipap_value_field(in, (int) len);      
    return value;
}

int 
ipap_field::ipap_snprint_bytes( char * str, size_t size, 
										ipap_value_field &in_field )
{
    size_t  i, n = 0;
    uint8_t *in = in_field.get_value_byte();

	int len = in_field.get_length();
    if ( size < 4 )
        return snprintf( str, size, "err" );

    while ( ((len * 2) + 2) > size )
        len--;

    sprintf( str, "0x" );
    n = 2;
    for( i=0; i<len; i++ ) {
        sprintf( str+n, "%02x", *in );
        n += 2;
        in++;
    }
    return n;
}

int 
ipap_field::ipap_snprint_string( char * str, size_t size, 
										 ipap_value_field &in_field )
{
    ssize_t  i;
    char *in = in_field.get_value_string();
    int len = in_field.get_length();

    std::cout << in_field.get_length() << "param:"<< len << std::endl << std::flush;

    for( i=len-1; i>=0; i-- ) {
        if ( in[i] == '\0' ) {
            return snprintf( str, size, "%s", in );
        }
    }

	std::cout << "1" << std::endl << std::flush;

    if ( len < size ) {
        memcpy( str, in, len );
        str[len] = '\0';
        return len;
    }

    return snprintf( str, size, "err" );
}

int 
ipap_field::ipap_snprint_ipaddr( char * str, size_t size, 
										 ipap_value_field &in_field)
{
    uint8_t *in = in_field.get_value_address();
    char    tmpbuf[100];
    int len = in_field.get_length();
    
    switch ( len ) {
      case 4:
          snprintf( str, size, "%u.%u.%u.%u",
                           in[0], in[1], in[2], in[3] );
          return 1;
      case 16:
      {
          /** change this!
           */
          uint16_t  i, tmp16;

          for( i=0, *tmpbuf=0; i<16; i+=2 ) {
              memcpy( &tmp16, (char*)in+i, 2 );
              tmp16 = htons( tmp16 );
              sprintf( tmpbuf+strlen(tmpbuf), "%s%x", i?":":"", tmp16 );
          }
          return snprintf( str, size, "%s", tmpbuf );
      }

      default:
          return ipap_snprint_bytes( str, size, in_field );
    }
}

int 
ipap_field::ipap_encode_float( ipap_value_field in, 
									   uint8_t *out, 
									   int relay_f )
{
    uint32_t      tmp32;
    uint64_t      tmp64;

    if (relay_f)
    {
		switch ( in.get_length() ) {
		  case 4:
			  tmp32 = in.get_value_float32();
			  memcpy( out, &tmp32, in.get_length() );
			  break;
		  case 8:
			  tmp64 = in.get_value_float64();
			  memcpy( out, &tmp64, in.get_length() );
			  break;
		  default:
			  memset( out, 0xff, in.get_length() );
			  return -1;
		}

	}
	else
	{
		switch ( in.get_length() ) {
		  case 4:
			  tmp32 = in.get_value_float32();
			  tmp32 = htonl( tmp32 );
			  memcpy( out, &tmp32, in.get_length() );
			  break;
		  case 8:
			  tmp64 = in.get_value_float64();
			  tmp64 = HTONLL( tmp64 );
			  memcpy( out, &tmp64, in.get_length() );
			  break;
		  default:
			  memset( out, 0xff, in.get_length() );
			  return -1;
		}
	}
    return 0;
}

ipap_value_field 
ipap_field::ipap_decode_float( uint8_t *in,  size_t len, int relay_f )
{
    uint32_t      tmp32;
    uint64_t      tmp64;
	ipap_value_field value;
    if (relay_f)
    {
		switch ( len ) {
		  case 4:
			  memcpy( &tmp32, in, len );
			  value = get_ipap_value_field(tmp32);
			  break;
		  case 8:
			  memcpy( &tmp64, in, len );
			  value = get_ipap_value_field(tmp64);
			  break;
		  default:
			  break;
		}

	}
	else
	{
		switch ( len ) {
		  case 4:
			  memcpy( &tmp32, in, len );
			  tmp32 = ntohl( tmp32 );
			  value = get_ipap_value_field(tmp32);
			  break;
		  case 8:
			  memcpy( &tmp64, in, len );
			  tmp64 = NTOHLL( tmp64 );
			  value = get_ipap_value_field(tmp64);
			  break;
		  default:
			  break;	
		}
	}
    return value;

}

int 
ipap_field::ipap_snprint_float( char * str, size_t size, 
										ipap_value_field &in)
{
	int len = in.get_length();
    switch ( len ) {
      case 4:
          return snprintf( str, size, "%f", (float)in.get_value_float32() );
      case 8:
          return snprintf( str, size, "%lf", (double) in.get_value_float64());
      default:
          break;
    }

    return snprintf( str, size, "err" );
}

int ipap_field::encode( ipap_value_field in, 
							   uint8_t *out, int relay_f)
{
	 if ( field_type.coding == IPAP_CODING_INT ) {
         ipap_encode_int(in, out, relay_f);
     }
     else if ( field_type.coding == IPAP_CODING_UINT ) {
         ipap_encode_int(in, out, relay_f);
     }
     else if ( field_type.coding == IPAP_CODING_NTP ) {
         ipap_encode_int(in, out, relay_f);
     }
     else if ( field_type.coding == IPAP_CODING_FLOAT ) {
         ipap_encode_float(in, out, relay_f);
     }
     else if ( field_type.coding == IPAP_CODING_IPADDR ) {
         ipap_encode_bytes(in, out, relay_f);
     }
     else if ( field_type.coding == IPAP_CODING_STRING ) {
         ipap_encode_string(in, out, relay_f);
     }
     else {
         ipap_encode_bytes(in, out, relay_f);
     }

}

ipap_value_field 
ipap_field::decode( uint8_t *in, 
						   size_t len, int relay_f)
{
	    if ( field_type.coding == IPAP_CODING_INT ) {
            return ipap_decode_int(in, len, relay_f);
        }
        else if ( field_type.coding == IPAP_CODING_UINT ) {
            return ipap_decode_int(in, len, relay_f);
        }
        else if ( field_type.coding == IPAP_CODING_NTP ) {
            return ipap_decode_int(in, len, relay_f);
        }
        else if ( field_type.coding == IPAP_CODING_FLOAT ) {
            return ipap_decode_float(in, len, relay_f);
        }
        else if ( field_type.coding == IPAP_CODING_IPADDR ) {
            return ipap_decode_bytes(in, len, relay_f);
        }
        else if ( field_type.coding == IPAP_CODING_STRING ) {
            return ipap_decode_bytes(in, len, relay_f);
        }
        else {
            return ipap_decode_bytes(in, len, relay_f);
        }

}

int ipap_field::snprint( char * str, size_t size, 
								ipap_value_field &in)
{
	    if ( field_type.coding == IPAP_CODING_INT ) {
            ipap_snprint_int(str,size,in);
        }
        else if ( field_type.coding == IPAP_CODING_UINT ) {
            ipap_snprint_uint(str,size,in);
        }
        else if ( field_type.coding == IPAP_CODING_NTP ) {
            ipap_snprint_uint(str,size,in);
        }
        else if ( field_type.coding == IPAP_CODING_FLOAT ) {
            ipap_snprint_float(str,size,in);
        }
        else if ( field_type.coding == IPAP_CODING_IPADDR ) {
            ipap_snprint_ipaddr(str,size,in);
        }
        else if ( field_type.coding == IPAP_CODING_STRING ) {
            ipap_snprint_string(str,size,in);
        }
        else {
            ipap_snprint_bytes(str,size,in);
        }

}

	
ipap_value_field
ipap_field::get_ipap_value_field(uint8_t &_value8)
{ 
	ipap_value_field field;
	if (field_type.length == 1)
		field.set_value_int8(_value8); 
	else
		throw ipap_bad_argument("Value does not agree with Field Type");
	
	return field;
}

ipap_value_field
ipap_field::get_ipap_value_field(uint16_t &_value16)
{ 
	ipap_value_field field;
	if (field_type.length == 2)
		field.set_value_int16(_value16); 
	else
		throw ipap_bad_argument("Value does not agree with Field Type");
	
	return field;
		
}

ipap_value_field
ipap_field::get_ipap_value_field(uint32_t &_value32)
{ 
	ipap_value_field field;
	if (field_type.length == 4)
		field.set_value_int32(_value32); 
	else
		throw ipap_bad_argument("Value does not agree with Field Type");
	
	return field;
}

ipap_value_field
ipap_field::get_ipap_value_field(uint64_t &_value64)
{ 
	ipap_value_field field;
	if (field_type.length == 8)
		field.set_value_int64(_value64); 
	else
		throw ipap_bad_argument("Value does not agree with Field Type");
	
	return field;
		
}

ipap_value_field
ipap_field::get_ipap_value_field(uint8_t * _valuebyte, int _length)
{	
        
    ipap_value_field field;
    if ( field_type.coding == IPAP_CODING_IPADDR ) 
    {
		if (field_type.length == _length){
			field.set_value_vunit8(_valuebyte, _length);
		}
		else
		{
			throw ipap_bad_argument("Value does not agree with Field Type");
		}
	}
    else if ( field_type.coding == IPAP_CODING_BYTES )
    {
		if (field_type.length == _length){
			field.set_value_vunit8(_valuebyte, _length);
		}
		else if (field_type.length == 65535 )
		{	
			field.set_value_vunit8(_valuebyte, _length);
		}
		else
		{
			throw ipap_bad_argument("Value does not agree with Field Type");
		}
    }
    else if ( field_type.coding == IPAP_CODING_STRING )
    {
		field.set_value_vchar((char *) _valuebyte, _length);
	}
    else
    {
		throw ipap_bad_argument("Value does not agree with Field Type");
	}	
	
	return field;
}

ipap_value_field
ipap_field::get_ipap_value_field(char * _valuechar, int _length)
{
		
    ipap_value_field field;
    if ( field_type.coding== IPAP_CODING_STRING ) {
		field.set_value_vchar(_valuechar, _length);
    }
    else
    {
		throw ipap_bad_argument("Value does not agree with Field Type");
	}	
	
	return field;
}




