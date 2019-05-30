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

#include "stdinc.h"
#include "stdincpp.h"
#include <string.h>
#include <stdint.h>
#include "IpAp_field.h"

/* 
 * ipap information element list
 */
 


ipap_field::ipap_field()
{
    field_type.eno = 0;
    field_type.ftype = 0;
    field_type.length = 0;
    field_type.coding = 0;
    field_type.name = "";
    field_type.xml_name = "";
    field_type.documentation = "";
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


void ipap_field::set_field_type(int eno, int ftype, ssize_t length, 
                                int coding, const char* name, const char* xml_name,
                                const char* documentation)
{
    ipap_field_type_t field_type_t;
    
    field_type_t.eno = eno;  
    field_type_t.ftype = ftype;
    field_type_t.length = length; 
    field_type_t.coding =  coding;
    field_type_t.name = std::string(name);
    field_type_t.xml_name = std::string(xml_name);
    field_type_t.documentation = std::string(documentation);
    
    field_type = field_type_t;
}


int ipap_field::get_eno()
{

    return field_type.eno;
}
        
int ipap_field::get_type()
{
    return field_type.ftype;
}
        
size_t ipap_field::get_length()
{
    return field_type.length;
}
        
const char* ipap_field::get_field_name()
{
    return field_type.name.c_str();
}
        
const char* ipap_field::get_xml_name()
{
    
    return field_type.xml_name.c_str();
}
        
const char* ipap_field::get_documentation()
{
    return field_type.documentation.c_str();
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

unsigned long 
ipap_field::parseULong(string in, unsigned long min, unsigned long max)
{
 
    char *errp = NULL;
    unsigned long n;

    
    n = strtoul(in.c_str(), &errp, 0);
        
    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not a unsigned long:" 
                                        + string(errp) );
    }

    if ((n<min) && (n>max)) {
        throw ipap_bad_argument("parseULong - out of range:");
    }

    return 	n;
}


long long 
ipap_field::parseLLong(string in, long long min, long long max)
{
 
    char *errp = NULL;
    long long n;

    
    n = strtoll(in.c_str(), &errp, 0);

    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not a long long number:" 
                                + string(errp) );
    }

    if ((n<min) && (n>max)) {
        throw ipap_bad_argument("parseLLong - out of range:");
    }

    return 	n;
}

unsigned long long
ipap_field::parseULLong(string in, unsigned long long min, 
                                  unsigned long long max)
{
 
    char *errp = NULL;
    unsigned long long n;

    
    n = strtoull(in.c_str(), &errp, 0);

    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not a unsigned \
                                    long long number:" + string(errp) );
    }

    if ((n<min) && (n>max)) {
        throw ipap_bad_argument("parseULLong - out of range");
    }

    return 	n;
}

int 
ipap_field::parseInt(string in, int min, int max)
{
    char *errp = NULL;
    int n;

    n = (int)strtol(in.c_str(), &errp, 0);

    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not an \
                                    integer number" + string(errp));
    }
    if ((n<min) && (n>max)) {
        throw ipap_bad_argument("parseInt - out of range");
    }

    return n;
}

float 
ipap_field::parseFloat(string in, float min, float max)
{
    char *errp = NULL;
    float n;

    n = strtof(in.c_str(), &errp);

    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not an \
                                   float number" + string(errp));
    }
    if ((n<min) && (n>max)) {
        throw ipap_bad_argument("parseFloat - out of range");
    }

    return n;
}

double 
ipap_field::parseDouble(string in, double min, double max)
{
    char *errp = NULL;
    double n;

    n = strtod(in.c_str(), &errp);

    if (in.empty() || (*errp != '\0')) {
        throw ipap_bad_argument("String given is not a \
                                    double number" + string(errp));
    }
    if ((n<min) && (n>max)) {
        throw Error("parseDouble - out of range");
    }

    return n;
}

int ipap_field::ipap_snprint_uint( char *str, size_t size, ipap_value_field &in )
{

    
    switch ( in.get_length() ) {
      case 1:
          return snprintf( str, size, "%u", in.get_value_int8() );
          break;
      case 2:
          return snprintf( str, size, "%u", in.get_value_int16() );
          break;
      case 4:
          return snprintf( str, size, "%u", (unsigned int)in.get_value_int32());
          break;
      case 8:
          return snprintf( str, size, "%llu", (long long unsigned int)in.get_value_int64() );
          break;
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

    for( i=len-1; i>=0; i-- ) {
        if ( in[i] == '\0' ) {

            return snprintf( str, size, "%s", in );
        }
    }

    if ( len < size ) {
        memcpy( str, in, len );
        str[len] = '\0';
        return len;
    }

    int characters = snprintf( str, size, "%s", in );
    return characters;
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
          return snprintf( str, size, "%u.%u.%u.%u",
                           in[0], in[1], in[2], in[3] );
          
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
    memcpy( out, in.get_value_byte(), in.get_length() );
    return 0;
}

ipap_value_field 
ipap_field::ipap_decode_float( uint8_t *in,  size_t len, int relay_f )
{

    float fvalue;
    ipap_value_field value;
    
    assert(sizeof(float) == 4);
        
    if (len == sizeof(float)){
        memcpy ( &fvalue, in, sizeof(float) );
        value = get_ipap_value_field(fvalue);
    }
    return value;

}

int 
ipap_field::ipap_encode_double( ipap_value_field in, 
                                       uint8_t *out, 
                                       int relay_f )
{
    memcpy( out, in.get_value_byte(), in.get_length() );
    return 0;
}


ipap_value_field 
ipap_field::ipap_decode_double( uint8_t *in,  size_t len, int relay_f )
{

    double dvalue;
    ipap_value_field value;
    
    if (len == sizeof(double)){
        memcpy ( &dvalue, in, sizeof(double) );
        value = get_ipap_value_field(dvalue);
    }
    return value;

}


int 
ipap_field::ipap_snprint_float( char * str, size_t size, 
                                ipap_value_field &in)
{

    float value;

    if (in.get_value_byte() == NULL) {
        throw ipap_bad_argument("error assigning float %f", value  );
    }
    
    memcpy (&value, in.get_value_byte(), sizeof(float) );
        
    return snprintf( str, size, "%7f", value );

}

int 
ipap_field::ipap_snprint_double( char * str, size_t size, 
                                        ipap_value_field &in)
{

    double value;
    
    memcpy (&value, in.get_value_byte(), sizeof(double) );
    return snprintf( str, size, "%.10f", value );

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
     else if ( field_type.coding == IPAP_CODING_DOUBLE ) {
         ipap_encode_double(in, out, relay_f);
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
        else if ( field_type.coding == IPAP_CODING_DOUBLE ) {
            return ipap_decode_double(in, len, relay_f);
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

// 
// This function calculates the number of characters required to 
// print a ipap_value_field.
//
int ipap_field::nCharacters( ipap_value_field &in )
{
    char *sbuf = (char *) malloc(sizeof(char) * 2);
    int ndigits = 0;
    
    if ( field_type.coding == IPAP_CODING_INT ) {
       ndigits = ipap_snprint_int(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_UINT ) {
       ndigits = ipap_snprint_uint(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_NTP ) {
       ndigits = ipap_snprint_uint(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_FLOAT ) {
       ndigits = ipap_snprint_float(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_DOUBLE ) {
       ndigits = ipap_snprint_double(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_IPADDR ) {
       ndigits = ipap_snprint_ipaddr(sbuf,1,in);
    }
    else if ( field_type.coding == IPAP_CODING_STRING ) {
       ndigits = in.get_length();
    }
    else {
       ndigits = (in.get_length() + 1 ) * 2;
    }
    
    if (string(sbuf).compare("err") == 0){
        throw ipap_bad_argument("Error trying to print ipap value field");
    }

    free(sbuf);
    return ndigits;
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
    else if ( field_type.coding == IPAP_CODING_DOUBLE ) {
        ipap_snprint_double(str,size,in);
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
    if (field_type.length == 1){
        field.set_value_int8(_value8); 
    }
    else{
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype; 
        s << " value does not agree with Field Type expected len:1 field len:";
        s << (int) field_type.length;
        throw ipap_bad_argument(s.str());
    }
    return field;
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(uint8_t _value8)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_value8);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field
ipap_field::get_ipap_value_field(uint16_t &_value16)
{ 
    ipap_value_field field;
    if (field_type.length == 2){
        field.set_value_int16(_value16); 
    }
    else{
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype; 
        s << " value does not agree with Field Type expected len:2 field len:";
        s << (int) field_type.length;
        throw ipap_bad_argument(s.str());
    }
    return field;
        
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(uint16_t _value16)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_value16);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field
ipap_field::get_ipap_value_field(uint32_t &_value32)
{ 
    ipap_value_field field;
    if (field_type.length == 4){
        field.set_value_int32(_value32); 
    }
    else{
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype; 
        s << " value does not agree with Field Type expected len:4 field len:";
        s << (int) field_type.length;
        throw ipap_bad_argument(s.str());
    }
    return field;
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(uint32_t _value32)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_value32);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field
ipap_field::get_ipap_value_field(uint64_t &_value64)
{ 
    ipap_value_field field;
    if (field_type.length == 8){
        field.set_value_int64(_value64); 
    }
    else{
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype; 
        s << " value does not agree with Field Type expected len:8 field len:";
        s << (int) field_type.length;
        throw ipap_bad_argument(s.str());
    }
    return field;		
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(uint64_t _value64)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_value64);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field
ipap_field::get_ipap_value_field(float &_fvalue)
{ 
        
    if (get_field_type().coding == IPAP_CODING_FLOAT){
        ipap_value_field field;
        field.set_value_float32(_fvalue); 
        return field;
    }else{
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype;
        s << " value does not agree with Field Type expected float value";
        throw ipap_bad_argument(s.str());
    }
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(float _fvalue)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_fvalue);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field
ipap_field::get_ipap_value_field(double dvalue)
{ 	
    if (get_field_type().coding == IPAP_CODING_DOUBLE){
        ipap_value_field field;
        field.set_value_float64(dvalue); 
        return field;		
    } else {
        ostringstream s;
        s << "Field eno:" << get_field_type().eno << " ftype:" << get_field_type().ftype;
        s << " value does not agree with Field Type expected double value";
        throw ipap_bad_argument(s.str());
    }
}

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(double dvalue)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(dvalue);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
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

ipap_value_field *
ipap_field::get_ipap_value_field_ptr(uint8_t * _valuebyte, int _length)
{
    try
    {
        ipap_value_field val = get_ipap_value_field(_valuebyte,_length);
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
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


ipap_value_field *
ipap_field::get_ipap_value_field_ptr(const char * _valuechar, int _length)
{

    ipap_value_field field;
    if ( field_type.coding== IPAP_CODING_STRING ) {
        field.set_value_vchar(_valuechar, _length);
    }
    else
    {
        return NULL;
    }

    return new ipap_value_field(field);

}

ipap_value_field *
ipap_field::get_ipap_value_field_ipv4_ptr(const char * _valuechar, int _length)
{
    try
    {
        ipap_value_field val = parseIP4ADDR(string(_valuechar, _length));
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}

ipap_value_field *
ipap_field::get_ipap_value_field_ipv6_ptr(const char * _valuechar, int _length)
{
    try
    {
        ipap_value_field val = parseIP6ADDR(string(_valuechar, _length));
        return new ipap_value_field(val);
    }
    catch (ipap_bad_argument &e){
        return NULL;
    }
}


string 
ipap_field::writeValue(ipap_value_field &in)
{

    int char_size;

    // The pointer to char * can require a number of characters depending 
    // on the type of encoding, so it is required to verify how many 
    // are required and then it can be written.
     
    char_size = nCharacters( in ) + 1;	
        
    char * buffer = (char *) malloc(sizeof(char) * char_size);
    snprint(buffer, char_size, in );
    string val_return(buffer);

    free(buffer);

    return val_return;
}

char *
ipap_field::writeValue(ipap_value_field &in, char* result, size_t resultMaxLength)
{

    // The pointer to char * can require a number of characters depending
    // on the type of encoding, so it is required to verify how many
    // are required and then it can be written.

    int char_size = nCharacters( in ) + 1;

    assert(char_size == resultMaxLength);

    snprint(result, resultMaxLength, in );

    return result;

}


ipap_value_field
ipap_field::parseINT(string in)
{
    unsigned long nul;
    long long unsigned int nllui;
    ipap_value_field val_return;
    
    uint8_t val8;
    uint16_t val16;
    uint32_t val32;
    uint64_t val64;
    
    
    switch (get_field_type().length)
    {
      case 1:          
        nul = parseULong(in, INT8_MIN, INT8_MAX);
        val8 = nul;
        val_return.set_value_int8(val8);
        break;
      case 2:
        nul = parseULong(in, INT16_MIN, INT16_MAX);
        val16 = nul;
        val_return.set_value_int16(val16);
        break;
      case 4:
        nul = parseULong(in, INT32_MIN, INT32_MAX);  
        val32 = nul;
        val_return.set_value_int32(val32);
        break;
      case 8:
        nllui = parseULLong(in, INT64_MIN, INT64_MAX);
        val64 = nllui;
        val_return.set_value_int64(val64);
        break;
      default:
          break;
    }
    
    return val_return;
}

ipap_value_field
ipap_field::parseUINT(string in)
{
    unsigned long nul;
    long long unsigned int nllui;
    uint8_t val8;
    uint16_t val16;
    uint32_t val32;
    uint64_t val64;

    ipap_value_field val_return;
    switch (get_field_type().length)
    {
      case 1:          
        nul = parseULong(in, 0, UINT8_MAX);
        val8 = nul;
        val_return.set_value_int8(val8);
        break;
      case 2:
        nul = parseULong(in, 0, UINT16_MAX);
        val16 = nul;
        val_return.set_value_int16(val16);
        break;
      case 4:
        nul = parseULong(in, 0, UINT32_MAX);  
        val32 = nul;
        val_return.set_value_int32(val32);
        break;
      case 8:
        nllui = parseULLong(in,0, UINT64_MAX);
        val64 = nllui;
        val_return.set_value_int64(val64);
        break;

      default:
          break;
    }	

    return val_return;
}

ipap_value_field
ipap_field::parseFLOAT(string in)
{
    ipap_value_field val_return;
    float value = parseFloat(in, MINFLOAT, MAXFLOAT);
    val_return.set_value_float32(value);
    return val_return;
}

ipap_value_field
ipap_field::parseDOUBLE(string in)
{
    ipap_value_field val_return;
    double value = parseDouble(in, MINDOUBLE, MAXDOUBLE);
    val_return.set_value_float64(value);
    return val_return;
}

int 
ipap_field::isNumericIPv4(string s)
{
    return (s.find_first_not_of("0123456789.", 0) >= s.length());  
}

ipap_value_field
ipap_field::parseIP4ADDR(string in)
{
    ipap_value_field val_return;
    int error;
    
    if (isNumericIPv4(in)){
    
        struct addrinfo *result=NULL;
        struct in_addr sin;
            
        error = getaddrinfo(in.c_str(), NULL, NULL, &result);

        if (error != 0){
            throw ipap_bad_argument("invalid IPV4 address");
        }
        
        sin = ((struct sockaddr_in *) result->ai_addr)->sin_addr;
        
        uint8_t *ip = (uint8_t *) &sin.s_addr;
        
        val_return.set_value_vunit8(ip, 4);
        
        freeaddrinfo(result);
        
        return val_return;
    } else {
        throw ipap_bad_argument("invalid IPV4 address");
    }
}

int ipap_field::isNumericIPv6(string s)
{
    return (s.find_first_not_of("0123456789abcdefABCDEF:.", 0) >= s.length());
}

ipap_value_field
ipap_field::parseIP6ADDR(string in)
{
    ipap_value_field val_return;
    int error;
    
    if (isNumericIPv6(in)){
    
        struct addrinfo *result=NULL;
        struct in6_addr  sin;
            
        error = getaddrinfo(in.c_str(), NULL, NULL, &result);

        if (error != 0){
            throw ipap_bad_argument("invalid IPV6 address");
        }
        
        sin = ((struct sockaddr_in6 *) result->ai_addr)->sin6_addr;
        
        uint8_t *ip = (uint8_t *) &sin.s6_addr;
        
        val_return.set_value_vunit8(ip, 16);
        
        freeaddrinfo(result);
        
        return val_return;
    } else {
        throw ipap_bad_argument("invalid IPV6 address");
    }
}

ipap_value_field
ipap_field::parseIPAddr(string in)
{

    switch (get_field_type().length)
    {
        case 4:
            return parseIP4ADDR(in);
            break;
        
        case 16:
            return parseIP6ADDR(in);
            break;
        
        default:
            throw ipap_bad_argument("The field is not a valid address");
            break;
    }

}

ipap_value_field
ipap_field::parseString(string in)
{
    ipap_value_field val_return;

    char * cstr = new char [in.length()+1];
    strcpy (cstr, in.c_str());
    
    val_return.set_value_vchar(cstr, in.length());
    delete[] cstr;
    
    return val_return;
}

ipap_value_field
ipap_field::parseBytes(string in)
{
    ipap_value_field val_return;

    char * cstr = new char [in.length() + 1];
    strcpy (cstr, in.c_str());

    int size = (in.length() / 2 ) - 1;
    uint8_t * data = (uint8_t *) malloc(sizeof(uint8_t) * size);

    char *iter = cstr;
    iter+=2; // First character that was introduced for formating.
    for(int count = 0; count < sizeof(data)/sizeof(data[0]); count++) {
        sscanf(iter, "%2hhx", &data[count]);
        iter += 2 * sizeof(uint8_t);
    }
        
    val_return.set_value_vunit8(data, size);
    free(data);
    delete[] cstr;
    
    return val_return;
}


ipap_value_field 
ipap_field::parse(string in )
{

    switch (field_type.coding)
    { 

        case IPAP_CODING_INT:
            return parseINT(in);
            break;
    
        case IPAP_CODING_UINT: 
            return parseUINT(in);
            break;
            
        case IPAP_CODING_NTP: 
            return parseINT(in);
            break;
        
        case IPAP_CODING_FLOAT:
            return parseFLOAT(in);
            break;
            
        case IPAP_CODING_DOUBLE:
            return parseDOUBLE(in);
            break;
        
        case IPAP_CODING_IPADDR:
            return parseIPAddr(in);
            break;
        
        case IPAP_CODING_STRING:
            return parseString(in);
            break;
        
        case IPAP_CODING_BYTES:
            return parseBytes(in);
            break;
        default:
            ostringstream s;
            s << "The field type is invalid coding:" << field_type.coding;
            throw ipap_bad_argument(s.str());
            break;
    }
}

