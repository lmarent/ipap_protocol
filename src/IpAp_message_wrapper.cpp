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
        try {

            return new ipap_message(param, message_length, _decode_network);

        }  catch(ipap_bad_argument e) {
            // The message given is not a valid message.
            cout << "the mssage given was invalid" << endl;
            return NULL;
        }
    }
        
    uint16_t ipap_message_new_data_template(ipap_message* message, int nfields, int template_type_id)
    {
        try {

            return message->new_data_template(nfields, (ipap_templ_type_t) template_type_id);

        } catch(ipap_bad_argument e) {
            cout << "An exception occurred. Exception Nr. " << e << '\n';
            return -1;
        }
    }
    
    int ipap_message_add_field(ipap_message* message, uint16_t templid, uint32_t eno, uint16_t type)
    {
        try{
            message->add_field(templid, eno, type);
            
        } catch(ipap_bad_argument e){
            return -1;
        }
    }
    
    void ipap_message_delete_template(ipap_message* message, uint16_t templid)
    {
        message->delete_template(templid);
    }
   
    void ipap_message_delete_all_templates(ipap_message* message)
    {
        message->delete_all_templates();
    }
    
    ipap_template * ipap_message_get_template_object(ipap_message* message, uint16_t templid)
    {
        return message->get_template_object(templid);
    }
    
    int ipap_message_get_template_list_size(ipap_message* message)
    {
        return message->get_template_list_size();
    }
    
    int ipap_message_get_template_at_pos(ipap_message* message, int pos)
    {
        return message->get_template_at_pos(pos);
    }
    
    void ipap_message_output(ipap_message* message)
    {
        message->output();
    }
    
    int ipap_message_include_data(ipap_message* message, uint16_t templid,
                           ipap_data_record *data )
    {
        try
        {

            message->include_data(templid, *data);

            return 1;

        } catch(ipap_bad_argument e) {
            cout << "An exception occurred. Exception Nr. " << e << '\n';
            return -1;
        }
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

    ipap_field * ipap_message_get_field_definition(ipap_message* message, int eno, int type)
    {
        return message->get_field_definition_ptr(eno, type);
    }

    uint16_t ipap_message_get_last_template_id(ipap_message* message)
    {
        return message->get_last_template_id();
    }

    int ipap_message_get_message_length(ipap_message* message)
    {
        return message->get_lenght();
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
    
    int ipap_message_get_data_record_size(ipap_message* message)
    {
        message->get_data_record_size();
    }
    
    ipap_data_record * ipap_message_get_data_record_at_pos(ipap_message* message, int pos)
    {
        message->get_data_record_at_pos(pos);
    }

    void ipap_message_set_syn(ipap_message* message, bool syn)
    {
        message->set_syn(syn);
    }

    bool ipap_message_get_syn(ipap_message* message)
    {
        message->get_syn();
    }

    void ipap_message_set_ack(ipap_message* message, bool ack)
    {
        message->set_ack(ack);
    }

    bool ipap_message_get_ack(ipap_message* message)
    {
        message->get_ack();
    }

    void ipap_message_set_fin(ipap_message* message, bool fin)
    {
        message->set_fin(fin);
    }

    bool ipap_message_get_fin(ipap_message* message)
    {
        message->get_fin();
    }

    void ipap_message_make_template(ipap_message* message, ipap_template* templ)
    {
        message->make_template(templ);
    }

    void ipap_message_destroy(ipap_message* message)
    {
        message->~ipap_message();
    }
}

#endif // IPAP_MESSAGE_WRAPPER_H
