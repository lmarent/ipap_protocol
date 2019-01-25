#include "IpAp_template_container.h"


#ifndef IPAP_TEMPLATE_CONTAINER_WRAPPER_H
#define IPAP_TEMPLATE_CONTAINER_WRAPPER_H

extern "C"
{
    
    ipap_template_container* ipap_template_container_new()
    {
        return new ipap_template_container();
    }
    
    void ipap_template_container_add_template(ipap_template_container* container, ipap_template *ipap_template)
    {
        container->add_template(ipap_template);
    }
    
    void ipap_template_container_delete_all_templates(ipap_template_container* container)
    {
        container->delete_all_templates();
    }
    
    void ipap_template_container_delete_template(ipap_template_container* container, uint16_t templid)
    {
        container->delete_template(templid);
    }
    
    bool ipap_template_container_exists_template(ipap_template_container* container, uint16_t templid)
    {
        return container->exists_template(templid);
    }
    
    int ipap_template_container_get_num_templates(ipap_template_container* container)
    {
        return container->get_num_templates();
    }

    ipap_template * ipap_template_container_get_template(ipap_template_container* container, uint16_t templid)
    {
        return new ipap_template(*(container->get_template(templid)));
    }
    
    void ipap_template_container_destroy(ipap_template_container* container)
    {
        container->~ipap_template_container();
    }
    
}

#endif // IPAP_TEMPLATE_CONTAINER_WRAPPER_H