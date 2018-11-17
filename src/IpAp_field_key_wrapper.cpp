#include "IpAp_field_key.h"

#ifndef IPAP_FIELD_KEY_WRAPPER_H
#define IPAP_FIELD_KEY_WRAPPER_H

extern "C"
{
    ipap_field_key * ipap_field_key_new(int _eno, int _ftype)
    {
        return new ipap_field_key(_eno, _ftype);
    }
    
    int ipap_field_key_get_eno(ipap_field_key * field_key)
    {
        return field_key->get_eno();
    }
    
    int ipap_field_key_get_ftype(ipap_field_key * field_key)
    {
        return field_key->get_ftype();
    }
    
    void ipap_field_key_destroy (ipap_field_key* field_key){
        field_key->~ipap_field_key();
    }


}

#endif // IPAP_FIELD_KEY_WRAPPER_H