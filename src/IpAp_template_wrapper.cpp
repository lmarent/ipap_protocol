#include "IpAp_template.h"
#include "IpAp_field_key.h"
#include "IpAp_field.h"


#ifndef IPAP_TEMPLATE_WRAPPER_H
#define IPAP_TEMPLATE_WRAPPER_H

extern "C"
{
    
    ipap_template * ipap_template_new()
    {
        return new ipap_template();
    }
    
    int ipap_template_get_template_type_mandatory_field_size(ipap_template *template_obj, ipap_templ_type_t templType)
    {
        return template_obj->getTemplateTypeMandatoryFieldSize(templType);
    }
    
    ipap_field_key* ipap_template_get_template_type_mandatory_field(ipap_template *template_obj, ipap_templ_type_t templType, int index)
    {
        return template_obj->getTemplateTypeMandatoryFieldVector(templType, index);
    }
    
    void ipap_template_set_id(ipap_template *template_obj,uint16_t _tid)
    {
        template_obj->set_id(_tid);
    }
    
    
    void ipap_template_set_maxfields(ipap_template *template_obj, int _maxfields)
    {
        template_obj->set_maxfields(_maxfields);
    }
    
    void ipap_template_set_type(ipap_template *template_obj, int _type)
    {
        template_obj->set_type((ipap_templ_type_t) _type);
    }
    
    void ipap_template_add_field(ipap_template *template_obj, uint16_t _flength, 
                                 uint8_t _unknown_f, int _relay_f, ipap_field *field)
    {
        template_obj->add_field(_flength, (ipap_unknown_field_t)_unknown_f, _relay_f, field);
    }
    
    int ipap_template_get_object_template_types_size(ipap_template *template_obj, uint8_t objectType)
    {
        return template_obj->getObjectTemplateTypesSize(objectType);
    }
    
    int ipap_template_get_object_template_types_at_pos(ipap_template *template_obj, uint8_t objectType, int index)
    {
        template_obj->getObjectTemplateTypesAtPos((ipap_object_type_t) objectType, index);
    }
}

#endif // IPAP_TEMPLATE_WRAPPER_H
