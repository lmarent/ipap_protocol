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
        
    const char* ipap_field_get_field_name(ipap_field* field)
    {
        return field->get_field_name();
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
