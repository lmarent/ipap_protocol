#include "IpAp_value_field.h"

#ifndef IPAP_VALUE_FIELD_WRAPPER_H
#define IPAP_VALUE_FIELD_WRAPPER_H

extern "C"
{
    ipap_value_field* ipap_value_field_new()
    {
        return new ipap_value_field();
    }
    
    void ipap_value_field_set_value_int8(ipap_value_field* field_value, uint8_t _value)
    {
        return field_value->set_value_int8(_value);
    }
    
    void ipap_value_field_set_value_int16(ipap_value_field* field_value, uint16_t _value)
    {
        return field_value->set_value_int16(_value);
    }
    
    void ipap_value_field_set_value_int32(ipap_value_field* field_value, uint32_t _value)
    {
        return field_value->set_value_int32(_value);
    }
    
    void ipap_value_field_set_value_int64(ipap_value_field* field_value, uint64_t _value)
    {
        return field_value->set_value_int64(_value);
    }
    
    void ipap_value_field_set_value_float32(ipap_value_field* field_value, float _value)
    {
        return field_value->set_value_float32(_value);
    }
    
    void ipap_value_field_set_value_float64(ipap_value_field* field_value, double _value)
    {
        return field_value->set_value_float64(_value);
    }
    
    void ipap_value_field_set_value_vunit8(ipap_value_field* field_value, uint8_t * _valuebyte, int _length)
    {
        return field_value->set_value_vunit8(_valuebyte, _length);
    }
    
    void ipap_value_field_set_value_vchar(ipap_value_field* field_value, const char * _valuechar, int _length)
    {
        return field_value->set_value_vchar(_valuechar, _length);
    }
    
    uint8_t ipap_value_field_get_value_int8(ipap_value_field* field_value)
    {
        return field_value->get_value_int8();
    }
    
    uint16_t ipap_value_field_get_value_int16(ipap_value_field* field_value)
    {
        return field_value->get_value_int16();
    }
    
    uint32_t ipap_value_field_get_value_int32(ipap_value_field* field_value)
    {
        return field_value->get_value_int32();
    }
    
    uint64_t ipap_value_field_get_value_int64(ipap_value_field* field_value)
    {
        return field_value->get_value_int64();
    }
    
    float ipap_value_field_get_value_float(ipap_value_field* field_value)
    {
        std::cout << "float" << field_value->get_value_float() << std::endl;
        return field_value->get_value_float();
    }
    
    double ipap_value_field_get_value_double(ipap_value_field* field_value)
    {
        std::cout << "double" << field_value->get_value_double() << std::endl;
        return field_value->get_value_double();
    }
    
    const char * ipap_value_field_get_value_vchar(ipap_value_field* field_value)
    {
        return field_value->get_value_const_string();
    }
    
    int ipap_value_field_get_length(ipap_value_field* field_value)
    {
        return field_value->get_length();
    }
    
    void ipap_value_field_destroy (ipap_value_field* field_value){
        field_value->~ipap_value_field();
    }

    
}

#endif IPAP_VALUE_FIELD_WRAPPER_H