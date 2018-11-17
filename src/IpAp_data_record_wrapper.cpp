#include "IpAp_data_record.h"

#ifndef IPAP_DATA_RECORD_WRAPPER_H
#define IPAP_DATA_RECORD_WRAPPER_H

extern "C"
{
    ipap_data_record * ipap_data_record_new(uint16_t _template_id)
    {
        return new ipap_data_record(_template_id);
    }
    
    uint16_t ipap_data_record_get_template_id(ipap_data_record *data_record)
    {
        return data_record->get_template_id();
    }
    
    void ipap_data_record_insert_field(ipap_data_record *data_record, 
                                       int eno, int ftype, ipap_value_field *value)
    {
        data_record->insert_field(eno,ftype,value);
    }
    
    int ipap_data_record_get_num_fields(ipap_data_record *data_record)
    {
        data_record->get_num_fields();
    }
    
    ipap_value_field* get_field(ipap_data_record *data_record, int eno, int ftype)
    {
        data_record->get_field_pointer(eno, ftype);
    }
    
    uint16_t get_length(ipap_data_record *data_record, int eno, int ftype)
    {
        data_record->get_length(eno,ftype);
    }
    
    void clear(ipap_data_record *data_record)
    {
        data_record->clear();
    }
    
}

#endif // IPAP_DATA_RECORD_WRAPPER_H