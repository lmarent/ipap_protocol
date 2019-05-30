#include "IpAp_field.h"

#ifndef IPAP_FIELD_WRAPPER_H
#define IPAP_FIELD_WRAPPER_H

extern "C"
{
    ipap_field* ipap_field_new() 
    {
        return new ipap_field();
    }
    
    void ipap_field_set_field_type(ipap_field* field, int eno, int ftype, 
                                   ssize_t length, int coding, const char* name, 
                                   const char* xml_name, const char* documentation) 
    {         
        field->set_field_type(eno, ftype, length, coding, name, xml_name, documentation);
    }

    int ipap_field_get_eno(ipap_field* field)
    {
        return field->get_eno();
    }
        
    int ipap_field_get_type(ipap_field* field)
    {
        return field->get_type();
    }
        
    size_t ipap_field_get_length(ipap_field* field)
    {
        return field->get_length();
    }

    ipap_value_field * ipap_field_get_ipap_value_field_uint8(ipap_field* field, uint8_t _value8)
    {
        return field->get_ipap_value_field_ptr(_value8);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_uint16(ipap_field* field, uint16_t _value16)
    {
        return field->get_ipap_value_field_ptr(_value16);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_uint32(ipap_field* field, uint32_t _value32)
    {
        return field->get_ipap_value_field_ptr(_value32);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_uint64(ipap_field* field, uint64_t _value64)
    {
        return field->get_ipap_value_field_ptr(_value64);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_float(ipap_field* field, float _value64)
    {
        return field->get_ipap_value_field_ptr(_value64);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_double(ipap_field* field, double dvalue)
    {
        return field->get_ipap_value_field_ptr(dvalue);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_ipv4(ipap_field* field, const char *ip_address4, int _length)
    {
        return field->get_ipap_value_field_ipv4_ptr(ip_address4, _length);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_ipv6(ipap_field* field, const char *ip_address6, int _length)
    {
        return field->get_ipap_value_field_ipv6_ptr(ip_address6, _length);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_string(ipap_field* field, const char *_valuechar, int _length)
    {
        return field->get_ipap_value_field_ptr(_valuechar, _length);
    }

    ipap_value_field * ipap_field_get_ipap_value_field_ubytes(ipap_field* field, uint8_t *_valuebyte, int _length)
    {
        return field->get_ipap_value_field_ptr(_valuebyte, _length);
    }

    ipap_value_field * ipap_field_parse(ipap_field* field, const char *_valuechar)
    {
        string val(_valuechar);
        try
        {

            return new ipap_value_field(field->parse(val));

        } catch (ipap_bad_argument &e){
            return NULL;
        }
    }


    const char* ipap_field_get_field_name(ipap_field* field)
    {
        return field->get_field_name();
    }

    char* ipap_field_write_value(ipap_field* field, ipap_value_field* value, char* result, size_t resultMaxLength)
    {
        field->writeValue(*value, result, resultMaxLength);
    }

    int ipap_field_number_characters(ipap_field* field, ipap_value_field* value)
    {
        return field->nCharacters(*value);
    }

    const char* ipap_field_get_xml_name(ipap_field* field)
    {
        return field->get_xml_name();
    }
        
    const char* ipap_field_get_documentation(ipap_field* field)
    {
        return field->get_documentation();
    }
     
    void ipap_field_destroy (ipap_field* field){
        field->~ipap_field();
    }
    
}

#endif // IPAP_FIELD_WRAPPER_H
