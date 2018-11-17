#include "IpAp_field_container.h"

#ifndef IPAP_FIELD_CONTAINER_WRAPPER_H
#define IPAP_FIELD_CONTAINER_WRAPPER_H

extern "C"
{
 
    ipap_field_container* ipap_field_container_new()
    {
        return new ipap_field_container();
    }
   
    void ipap_field_container_initialize_forward(ipap_field_container* container)
    {
        return container->initialize_forward();
    }
    
    void ipap_field_container_initialize_reverse(ipap_field_container* container)
    {
        return container->initialize_reverse();
    }
    
    ipap_field* ipap_field_container_get_field_pointer(ipap_field_container* container, int eno, int type)
    {
        try
        {
            return container->get_field_pointer(eno, type);
        } catch (ipap_bad_argument e)
        {
            return NULL;
        }
    }
    
    int ipap_field_container_get_num_fields(ipap_field_container* container)
    {
        return container->get_num_fields();
    }
    
    void ipap_field_container_clear(ipap_field_container* container)
    {
        return container->clear();
    }
    
}

#endif // IPAP_FIELD_CONTAINER_WRAPPER_H
