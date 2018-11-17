#include "IpAp_message.h"

#ifndef IPAP_MESSAGE_WRAPPER_H
#define IPAP_MESSAGE_WRAPPER_H

extern "C"
{
    ipap_message* ipap_message_new(int domain_id, int ipap_version, bool _encode_network)
    {
        return new ipap_message(domain_id, ipap_version, _encode_network);
    }

    ipap_message* ipap_message_new_message(unsigned char * param, size_t message_length, bool _decode_network) 
    {
        return new ipap_message(param, message_length, _decode_network);
    }
    
    void ipap_message_close(ipap_message* message)
    { 
        message->close();
    }
    
    uint16_t ipap_message_new_data_template(ipap_message* message, int nfields, int template_type_id)
    {
        return message->new_data_template(nfields, (ipap_templ_type_t) template_type_id);
    }
    
    void ipap_message_add_field(ipap_message* message, uint16_t templid, uint32_t eno, uint16_t type)
    {
        message->add_field(templid, eno, type);
    }
    
    void ipap_message_delete_template(ipap_message* message, uint16_t templid)
    {
        message->delete_template(templid);
    }
   
    void ipap_message_delete_all_templates(ipap_message* message)
    {
        message->delete_all_templates();
    }
    
    void ipap_message_output(ipap_message* message)
    {
        message->output();
    }
    
    void include_data(ipap_message* message, uint16_t templid, 
                           ipap_data_record *data )
    {
        message->include_data(templid, data);
    }
 
    unsigned char * ipap_message_get_message(ipap_message* message)
    {
        message->get_message();
    }
    
    int ipap_message_get_offset(ipap_message* message)
    {
        message->get_offset();
    }
    
    int ipap_message_ipap_import(ipap_message* message, unsigned char *buffer, size_t message_length )
    {
        message->ipap_import(buffer, message_length);
    }
    
    int ipap_message_get_domain(ipap_message* message)
    {
        return message->get_domain();
    }
    
    uint16_t ipap_message_get_last_template_id(ipap_message* message)
    {
        return message->get_last_template_id();
    }
    
    int ipap_message_get_version(ipap_message* message)
    {
        return message->get_version();
    }
    
    uint32_t ipap_message_get_seqno(ipap_message* message)
    {
        return message->get_seqno();
    }
    
    void ipap_message_set_seqno(ipap_message* message, uint32_t _seqno)
    {
        message->set_seqno(_seqno);
    }
    
    void ipap_message_set_ackseqno(ipap_message* message, uint32_t _ackseqno)
    {
        message->set_ackseqno(_ackseqno);
    }
    
    uint32_t ipap_message_get_ackseqno(ipap_message* message)
    {
        message->get_ackseqno();
    }
    
    void ipap_message_set_exporttime(ipap_message* message, uint32_t _exporttime)
    {
        message->set_exporttime(_exporttime);
    }
    
    
    uint32_t ipap_message_get_exporttime(ipap_message* message)
    {
        message->get_exporttime();
    }
}

#endif // IPAP_MESSAGE_WRAPPER_H