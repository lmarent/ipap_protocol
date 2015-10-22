/*! \file   IpAp_message.cpp

    Copyright 2014-2015 Universidad de los Andes, Bogotá, Colombia

    This file is part of IP Auction Processing protocol (IPAP).

    IPAP is free software; you can redistribute it and/or modify 
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    IPAP is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this software; if not, write to the Free Software 
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Description:
    message class of ipap protocol

    $Id: IpAp_message.cpp 748 2015-08-26 18:48:00Z amarentes $
*/


#include "IpAp_t.h"
#include "IpAp_field.h"
#include "IpAp_message.h"
#include "IpAp_data_record.h"
#include "IpAp_exception.h"




/*------------------------------ defines ----------------------------*/

#define NODEBUG


#define INSERTU16(b,l,val) \
        { uint16_t _t=htons((val)); memcpy((b),&_t,2); (l)+=2; }
#define INSERTU32(b,l,val) \
        { uint32_t _t=htonl((val)); memcpy((b),&_t,4); (l)+=4; }

#define INSERT_U16_NOENCODE(b,l,val) \
		{ uint16_t _t = val; memcpy((b),&_t,2); (l)+=2; }

#define INSERT_U32_NOENCODE(b,l,val) \
        { uint32_t _t=val; memcpy((b),&_t,4); (l)+=4; }

#define READ16_NOENCODE(val,b) \
        { memcpy((&val),b,2); }

#define READ32_NOENCODE(val,b) \
	    { memcpy((&val),b,4); } 


#define READ16(val,b) \
        { uint16_t _t; memcpy((&_t),b,2); val= ntohs(_t); }

#define READ32(val,b) \
		{ uint32_t _t; memcpy((&_t),b,4); val = ntohl(_t); }

ipap_message::ipap_message( ):
		message(NULL), g_tstart(0), encode_network(true), 
		require_output(true)
{
    log = Logger::getInstance();
    ch = log->createChannel("IPAP_MESSAGE");

#ifdef DEBUG
    log->dlog(ch, "Starting ipap message constructor");
#endif 
    
    init( 0, IPAP_VERSION );

#ifdef DEBUG
    log->dlog(ch, "Ending ipap message constructor");
#endif 

}

ipap_message::ipap_message( bool _encode_network ):
		message(NULL), g_tstart(0), 
		encode_network(_encode_network), require_output(true)
{

    log = Logger::getInstance();
    ch = log->createChannel("IPAP_MESSAGE");
    
    init( 0, IPAP_VERSION );

#ifdef DEBUG
    log->dlog(ch, "ipap message constructor");
#endif    


}


ipap_message::ipap_message( int domain_id, int ipap_version, bool _encode_network):
		message(NULL), g_tstart(0), encode_network(_encode_network), 
		require_output(true)
{
		
    log = Logger::getInstance();
    ch = log->createChannel("IPAP_MESSAGE");

#ifdef DEBUG
    log->dlog(ch, "ipap message constructor");
#endif    

    switch( ipap_version ) 
    {
      case IPAP_VERSION:
          break;
      default:
          throw ipap_bad_argument("Invalid IP AP Version");
    }
    
    init( domain_id, ipap_version );

}


ipap_message::~ipap_message( void )
{

#ifdef DEBUG
    log->dlog(ch, "destroying ipap_message");
#endif    

    close( );
    g_tstart = 0;
    
}

/*
 * name:        ipap_add_vendor_information_elements()
 * parameters:  > fields - array of fields of size nfields+1
 *                         the last field has ftype = 0
 * description: add information elements to global list of field types
 * remarks:
 */
void ipap_message::add_vendor_information_elements( ipap_field_type_t *fields )
{

#ifdef DEBUG
    log->dlog(ch, "Starting add_vendor_information_elements");
#endif    


    ipap_field_type_t *ft;

    if ( ! g_tstart ) {  
        throw ipap_bad_argument("Message not initialized");
    }

    /** add to list of field types
     */
    ft = fields;
    while ( ft->ftype !=0 ) {
        /** create new node
         */
        g_ipap_fields.AddFieldType(*ft);

        ft++;
        continue;
    }

}

void ipap_message::allocate_additional_memory(size_t additional)
{

#ifdef DEBUG
    log->dlog(ch, "starting allocate_additional_memory");
#endif
	
	if (message)
	{
		if ((message->offset + additional) > message->buffer_lenght)
		{
			message->buffer=(unsigned char *)realloc(message->buffer, message->offset + additional + 1);
			if (message->buffer == NULL)
				message->buffer_lenght = message->offset + additional + 1;
			else
				throw ipap_bad_argument("Could not increse the memory of the final char pointer");
		}
	}
	else
	{
		throw ipap_bad_argument("Not initializated message");
	}
}

/**
 * name:        init()
 * parameters:
 * remarks:     init module, read field type info.
 */
void ipap_message::init( int domain_id, int ipap_version )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method init");
#endif    

    ipap_t       *i;

	try
	{		
		i = new ipap_t();
	}
	catch(std::bad_alloc& exc)
	{
		if ( i != NULL )
			delete( i );
        throw std::bad_alloc(exc);
    }

    i->domain_id = domain_id;
    i->version   = ipap_version;
    message = i;


    g_tstart = time(NULL);
    signal( SIGPIPE, SIG_IGN );
    g_lasttid = 255;

    g_ipap_fields.initialize_forward();

    g_ipap_fields.initialize_reverse();

#ifdef DEBUG
    log->dlog(ch, "Ending method init");
#endif  

}

/*
 * name:        new_template()
 * parameters:
 * return:     
 */
uint16_t  
ipap_message::new_template( int nfields )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method new_template");
#endif    	
	
    ipap_template  *t;

    if ( ! message  ) 
        throw ipap_bad_argument("Message is not initialized");
    
    if ( nfields<1 )
		throw ipap_bad_argument("The number of fields to insert in a \
									template must be greater than zero");

    /** alloc mem
     */
    try
    {
		
		t = new ipap_template();
		
		/** generate template id, todo!
		 */
		g_lasttid++;
		t->set_id( g_lasttid );
		t->set_maxfields( nfields );

		/** add template to template container
		 */
		(message->templates).add_template(t);
		
		/**
		* The message change, so it requires a new output 
		*/
		require_output = true;
		
		return t->get_template_id();
	
	}
	catch (std::bad_alloc& exc)
	{
		if (t != NULL)
			delete t;
		throw std::bad_alloc(exc);
	}

}



/*
 * name:        new_data_template()
 * parameters:
 * return:      
 */
uint16_t 
ipap_message::new_data_template( int nfields, ipap_templ_type_t type )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method new_data_template");
#endif    	

    uint16_t templid;
    ipap_template *templ;

    templid = new_template( nfields );
    templ = message->templates.get_template(templid);
    templ->set_type(type);
    /**
	* The message change, so it requires a new output 
	*/
	require_output = true;    
    return templid;
    
}


ipap_field
ipap_message::get_field_definition( int eno, int type )
{
	return g_ipap_fields.get_field(eno, type);
}


/*
 * name:        add_field()
 * parameters:
 * return:      
 */
void 
ipap_message::add_field(  uint16_t templid,
               uint32_t         eno,
               uint16_t         type )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method add_field");
#endif    	
    
    ipap_template *templ;     
    templ = message->templates.get_template(templid);
    
    if (templ== NULL)
		throw ipap_bad_argument("template not included in the message");
    
    if ( ( templ->get_numfields() < templ->get_maxfields() )
         && (type < IPAP_EFT_VENDOR_BIT) ) {
        /** set template field
         */

        ipap_field field = g_ipap_fields.get_field(eno, type);
        uint16_t length = (uint16_t) field.get_field_type().length;
        
        if (encode_network){
			templ->add_field(length,KNOWN,1,field);
		}else{
			templ->add_field(length,KNOWN,0,field);
		}
		
		/**
		* The message change, so it requires a new output 
		*/
		require_output = true;
    }
    else{ 
        throw ipap_bad_argument("Maximum number of field reach");
    }
}

/*
 * name:        delete_template()
 * parameters:
 * return:
 */
void ipap_message::delete_template( uint16_t templid )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method delete_template");
#endif


    /** remove template from list
     */
    message->templates.delete_template(templid);
   
   /**
	* The message change, so it requires a new output 
	*/
	require_output = true;

}

/*
 * name:        delete_all_templates()
 * parameters:
 * return:
 */
void ipap_message::delete_all_templates( void )
{

#ifdef DEBUG
    log->dlog(ch, "delete_all_templates");
#endif	

    /** remove all templates from list
     */
    message->templates.delete_all_templates();
   
    /**
	* The message change, so it requires a new output 
	*/
	require_output = true;

}


/*
 * name:        make_template()
 * parameters:
 * return:      generates a new template and stores a pointer to it into the templ parameter
 */
uint16_t 
ipap_message::make_template( ipap_fields_t *fields, 
							 int nfields,
							 ipap_templ_type_t type,
							 uint16_t templid )
{
	
#ifdef DEBUG
    log->dlog(ch, "Starting method make_template");
#endif

    ipap_template *t = NULL;
    int i;

	try
	{

		t = new ipap_template();
			
		/** generate template id, todo!
		 */
		t->set_id( templid );
		t->set_maxfields( nfields );
		t->set_type(type);

		if 	(g_lasttid < templid){
			g_lasttid = templid;
		}
		
		/** add template to template container
		 */
		(message->templates).add_template(t);
			
		for ( i=0; i<nfields; i++ )
		{
			add_field( templid, fields[i].eno, fields[i].ienum);
		}
		
		/**
		* The message change, so it requires a new output 
		*/
		require_output = true;		
	}
	catch(...)
	{
		delete_template( templid );
		throw ipap_bad_argument("Could not insert all fields"); 
	}

    return templid;
}

void 
ipap_message::make_template(ipap_template *templ)
{

    ipap_template *t = NULL;
    int i;

	try
	{

		t = new ipap_template();
			
		/** generate template id, todo!
		 */
		t->set_id( templ->get_template_id() );
		t->set_maxfields( templ->get_maxfields() );
		t->set_type(templ->get_type());

		if 	(g_lasttid < templ->get_template_id() ){
			g_lasttid = templ->get_template_id();
		}
		
		/** add template to template container
		 */
		(message->templates).add_template(t);
		
		for (int i=0; i < templ->get_maxfields(); i++){
			ipap_template_field_t field = templ->get_field(i);
			add_field( t->get_template_id(), 
				field.elem.get_field_type().eno, field.elem.get_field_type().ftype);
		}
 
	}
	catch(...)
	{
		delete_template( templ->get_template_id() );
		throw ipap_bad_argument("Could not insert all fields"); 
	}
}

void ipap_message::finish_cs( void )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method finish_cs");
#endif

    size_t   buflen;
    uint8_t  *buf;
	std::string 	func = "finish_cs";

    /* finish current dataset */
    if ( (buf = message->cs_header) ==NULL )
        return;
    buflen = 0;

#ifdef DEBUG
    log->dlog(ch, "finish_cs - tid:%d num_bytes %d", message->cs_tid,  message->cs_bytes);
#endif    
    
    if (encode_network == true){
		INSERTU16( buf+buflen, buflen, message->cs_tid );
		INSERTU16( buf+buflen, buflen, message->cs_bytes );
	}
	else{
		INSERT_U16_NOENCODE( buf+buflen, buflen, message->cs_tid );
		INSERT_U16_NOENCODE( buf+buflen, buflen, message->cs_bytes );		
	}
    message->cs_bytes = 0;
    message->cs_offset = 0;
    message->cs_header = NULL;
    message->cs_tid = 0;
}

/*
 * name:        _write_hdr()
 * parameters:
 * return:      0/-1
 */
void ipap_message::_write_hdr( void )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method _write_hdr");
#endif
	
    int hsize, buflen = 0;
    time_t      now = time(NULL);

    /** fill ipfix header
     */
    char *buf; 
    hsize = IPAP_HDR_BYTES;
        
    if ( hsize + message->offset > message->buffer_lenght ) 
		allocate_additional_memory(hsize + message->offset - message->buffer_lenght );

    /* write header before any other data */
	if ( message->offset > 0 )
		memmove( message->buffer + hsize, message->buffer, message->offset );
		
    if (encode_network == true){
		INSERTU16( message->buffer+buflen, buflen, message->version );
		INSERTU16( message->buffer+buflen, buflen, message->offset + IPAP_HDR_BYTES );
		INSERTU32( message->buffer+buflen, buflen, now );
		INSERTU32( message->buffer+buflen, buflen, message->nrecords);
		INSERTU32( message->buffer+buflen, buflen, message->domain_id );
	}
	else{
		INSERT_U16_NOENCODE( message->buffer+buflen, buflen, message->version );
		INSERT_U16_NOENCODE( message->buffer+buflen, buflen, message->offset + IPAP_HDR_BYTES );
		INSERT_U32_NOENCODE( message->buffer+buflen, buflen, now );
		INSERT_U32_NOENCODE( message->buffer+buflen, buflen, message->nrecords);
		INSERT_U32_NOENCODE( message->buffer+buflen, buflen, message->domain_id );
	}
	message->length = message->offset + IPAP_HDR_BYTES;
	message->exporttime = now;
	message->offset += hsize;

#ifdef DEBUG
    log->dlog(ch, "_write_hdr version:%d exporttime=%d offset:%d", 
						message->version, message->exporttime, message->offset);
#endif
		
}



/* name:        _output_flush()
 * parameters:
 * remarks:    
 */
void ipap_message::_output_flush( void )
{
    int               ret;

#ifdef DEBUG
    log->dlog(ch, "Starting method _output_flush");
#endif


    if ( (message==NULL) || (message->offset==0) )
        return;
    
    if ( message->cs_tid > 0 ) {
        /* finish current dataset */
        finish_cs( );
    }

}

/*
 * name:        close()
 * parameters:
 * return:      0 = ok, -1 = error
 */
void ipap_message::close( void )
{
	
#ifdef DEBUG
    log->dlog(ch, "Starting method close");
#endif

	
    if ( message )
        delete (message);
   
    g_ipap_fields.clear();
    data_list.clear();
}



/*
 * name:        _write_template()
 * parameters:
 * return:      0/-1
 */
void 
ipap_message::_write_template( ipap_template  *templ )
{

#ifdef DEBUG
    log->dlog(ch, "Starting method _write_template");
#endif	
	
    size_t            buflen, tsize=0, ssize=0, osize=0;
    unsigned char     *buf;
    uint16_t          tmp16;
    int               i, n;

    /** calc template size
     */
    for ( tsize=8,i=0; i < templ->get_numfields(); i++ ) {
        tsize += 4;
        if ((templ->get_field(i).elem).get_field_type().eno != IPAP_FT_NOENO ){
            tsize += 4;
        }   
    }

#ifdef DEBUG
    log->dlog(ch, "_write_template- template length:%d type:%d numFields:%d, templateId:%d offset:%d ", 
				tsize, templ->get_type(), templ->get_numfields(), templ->get_template_id(), message->offset);
#endif	

    /* check space */
    if ( tsize + message->offset > message->buffer_lenght ) 
    {
         allocate_additional_memory(tsize + message->offset - message->buffer_lenght );
    }

    /* write template prior to data */
    if ( message->offset > 0 ) 
    {
         memmove( message->buffer + tsize, message->buffer, message->offset );
         if ( message->cs_tid )
             message->cs_header += tsize;
             message->cs_offset += tsize;
    }

    buf = message->buffer;
    buflen = 0;

    /** insert template set into buffer
     */
     
    if (encode_network == true){
		INSERTU16( buf+buflen, buflen, templ->get_type());
		INSERTU16( buf+buflen, buflen, tsize );
		INSERTU16( buf+buflen, buflen, templ->get_template_id() );
		INSERTU16( buf+buflen, buflen, templ->get_numfields() );
	}
	else{
		INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_type());
		INSERT_U16_NOENCODE( buf+buflen, buflen, tsize );
		INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_template_id() );
		INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_numfields() );				
	}

	i = 0;
    n = templ->get_numfields();
    for ( ; i<templ->get_numfields(); i++ )
    {
        if ( (templ->get_field(i).elem).get_field_type().eno == IPAP_FT_NOENO ) {
			if (encode_network == true){
				INSERTU16( buf+buflen, buflen, (templ->get_field(i).elem).get_field_type().ftype );
				INSERTU16( buf+buflen, buflen, templ->get_field(i).flength );
			}
			else{
				INSERT_U16_NOENCODE( buf+buflen, buflen, (templ->get_field(i).elem).get_field_type().ftype );
				INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_field(i).flength );				
			}
        } 
        else {
            tmp16 = (templ->get_field(i).elem).get_field_type().ftype|IPAP_EFT_VENDOR_BIT;
            if (encode_network == true){
				INSERTU16( buf+buflen, buflen, tmp16 );
				INSERTU16( buf+buflen, buflen, templ->get_field(i).flength );
				INSERTU32( buf+buflen, buflen, (templ->get_field(i).elem).get_field_type().eno );
			}
			else{
				INSERT_U16_NOENCODE( buf+buflen, buflen, tmp16 );
				INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_field(i).flength );
				INSERT_U32_NOENCODE( buf+buflen, buflen, (templ->get_field(i).elem).get_field_type().eno );				
			}
        }
    }
    templ->set_time_send( time(NULL) );
	
    message->offset += buflen;

#ifdef DEBUG
    log->dlog(ch, "_write_template- buffer len:%d ", buflen);
#endif	

}


void
ipap_message::output(void)
{

#ifdef DEBUG
    log->dlog(ch, "starting output");
#endif    
	
	if (message == NULL){
		throw ipap_bad_argument("Error: The message is not initialized");
    }
    else{
		if (require_output == true)
		{
			// Clear the internal buffer.
			message->reinitiate_buffer();
			
			std::list<int>::iterator it;
			std::list<int> lst_templates = get_template_list();
					
			// Put in internal buffer template definition and data related. 
			for ( it = lst_templates.begin(); it != lst_templates.end(); ++it)
			{
				ipap_template *templ = get_template(*it);
				output_set( templ->get_template_id() );
			}

			// Calculate message header information and put it on the buffer.
			_write_hdr( );
			
			/** The message changed, so it requires a new output 
			*/
			require_output = false;
		}
	}
#ifdef DEBUG
    log->dlog(ch, "ending output");
#endif 

}

/*
 * name:        output_set()
 * parameters:  Write in the buffer template definition and all 
 * 				data records related to templateid given as parameter.
 * return:      
 */
void 
ipap_message::output_set( uint16_t templid )
{
		
    int               i, newset_f=0;
    size_t            buflen, datasetlen;
    uint8_t           *p, *buf;
    ipap_template 	  *templ; 

#ifdef DEBUG
    log->dlog(ch, "Starting output_set %d ", templid);
#endif 
    
    templ = message->templates.get_template(templid);

    /** parameter check
     */
    if (templ==NULL)
        throw ipap_bad_argument("template not included in the message");
    	
    /** writes the templates if it was not done before
     */
    if ( templ->get_tsend() == 0 ){
        _write_template( templ ); 
    }
    

    /** get size of data set, check space
    */ 
    if ( templ->get_template_id() == message->cs_tid ) 
    {
        newset_f = 0;
        datasetlen = 0;
    }
    else 
    {
        if ( message->cs_tid > 0 ) {
            finish_cs( );
        }
        newset_f = 1;
        datasetlen = 4;
    }
            	
    // insert the data records associated with the template.
    for ( int data_index= 0; data_index < data_list.size(); data_index++)
	{

#ifdef DEBUG
			log->dlog(ch, "Output set - data set:%d template: %d", 
							data_index, data_list[data_index].get_template_id() );
#endif
		
		if (data_list[data_index].get_template_id() == templ->get_template_id())
		{

#ifdef DEBUG
			log->dlog(ch, "Output set - Data associated with template %d", 
							templ->get_template_id());
#endif 
				
			ipap_data_record g_data = data_list[data_index];
			for ( i=0; i < templ->get_numfields(); i++ )
			{

				ipap_field temp_field = templ->get_field(i).elem;

				ipap_field_key field_key = ipap_field_key(temp_field.get_field_type().eno, 
																		temp_field.get_field_type().ftype);
				uint16_t field_len = 0;
				try
				{
					 field_len = g_data.get_length(field_key);
					
				}catch (ipap_bad_argument){
#ifdef DEBUG
					log->dlog(ch, "Output set - Data associated with \
								   template %d field:%d has not found - \
								   fieldkey:%s - dataRecord:%s", 
							templ->get_template_id(), i, 
							field_key.to_string().c_str(), 
							g_data.to_string().c_str());
#endif 							
					throw ipap_bad_argument("Field not included:" +
										field_key.to_string() );
					
				}		
					
				if ( templ->get_field(i).flength == IPAP_FT_VARLEN ) {
	
					if ( field_len > 254 )
						datasetlen += 3;
					else
						datasetlen += 1;
				} 
				else{
					if ( field_len > templ->get_field(i).flength )
						throw ipap_bad_argument("Data length greater than field definition lenght");
				}		
				
				datasetlen += field_len;
			}

#ifdef DEBUG
			log->dlog(ch, "Output set - finish calculating dataset %d", 
							datasetlen);
#endif 

			if ( (message->offset + datasetlen) > message->buffer_lenght )
				allocate_additional_memory(datasetlen + message->offset - message->buffer_lenght );
			
			// fill buffer 
			buf    = (uint8_t*)(message->buffer) + message->offset;
			buflen = 0;

			if ( newset_f ) {
				
				// insert data set 
				message->cs_bytes = 0;
				message->cs_header = buf;
				message->cs_offset = message->offset;
				message->cs_tid = templ->get_template_id();
				
				
				if (encode_network == true){
					INSERTU16( buf+buflen, buflen, templ->get_template_id() );
					INSERTU16( buf+buflen, buflen, datasetlen );
				}
				else{
					INSERT_U16_NOENCODE( buf+buflen, buflen, templ->get_template_id() );
					INSERT_U16_NOENCODE( buf+buflen, buflen, datasetlen );			
				}
			}

#ifdef DEBUG
			log->dlog(ch, "Output set - finish writing dataset header");
#endif
			for ( i=0; i < templ->get_numfields(); i++ ) {
								
				ipap_field_key field_key = ipap_field_key((templ->get_field(i).elem).get_field_type().eno, 
																		(templ->get_field(i).elem).get_field_type().ftype);
				
				if ( templ->get_field(i).flength == IPAP_FT_VARLEN ) {
					if ( g_data.get_length(field_key) > 254 ) {
						*(buf+buflen) = 0xFF;
						buflen++;
						if (encode_network == true){
							INSERTU16( buf+buflen, buflen, g_data.get_length(field_key) );
						}
						else{
							INSERT_U16_NOENCODE( buf+buflen, buflen, g_data.get_length(field_key) );
						}
					}
					else {
						*(buf+buflen) = g_data.get_length(field_key);
						buflen++;
					}
				}
				
				(templ->get_field(i).elem).encode( g_data.get_field(field_key), 
												   buf+buflen, 
												   templ->get_field(i).relay_f );

				buflen += g_data.get_length(field_key);
			}

#ifdef DEBUG
			log->dlog(ch, "Output set - finish writing dataset fields");
#endif			
			message->nrecords ++;
			message->offset += buflen;
			message->cs_bytes += buflen;
			finish_cs( );
		    if ( message->version == IPAP_VERSION )
				message->seqno ++;
		}
	}
	 
    _output_flush( );

#ifdef DEBUG
    log->dlog(ch, "Ending output_set");
#endif 
		        
}


void 
ipap_message::include_data( uint16_t templid, 
								   ipap_data_record &data )
{
	
#ifdef DEBUG
    log->dlog(ch, "Starting method include_data");
#endif	

	
    int i;
	ipap_template *templ;
	
	templ = message->templates.get_template(templid);
	
    if ( !templ ) {
        throw ipap_bad_argument("Parameter templateId:%d not defined", templid);
    }
       
    if ( ( templ->get_numfields() != data.get_num_fields())  ){
        throw ipap_bad_argument("The number of field values:%d is different from template's fields:%d", 
				templ->get_numfields(), data.get_num_fields());
	}
	
	// Verifies that fields correspond to template fields.
	for ( i=0; i < templ->get_numfields(); i++ )
	{	

		ipap_field temp_field = templ->get_field(i).elem;

		ipap_field_key field_key = ipap_field_key(temp_field.get_field_type().eno, 
									temp_field.get_field_type().ftype);
		
		// This line generates an exception when the value for the field is not found.
		ipap_value_field val = data.get_field(field_key);
	}
				
    data_list.push_back(data);
}

unsigned char * 
ipap_message::get_message(void) const
{

#ifdef DEBUG
    log->dlog(ch, "starting get_message");
#endif
	if (message != NULL)
		return message->buffer;
	else
		return NULL;
}

bool 
ipap_message::get_require_output(void) const
{
	return require_output;
}

int 
ipap_message::get_offset(void) const
{

#ifdef DEBUG
    log->dlog(ch, "starting get_offset");
#endif
	
	int offset = 0;
	
	if (message != NULL){
		if (require_output == true){
			offset = -1;
		}
		return message->offset;
	}
	else{
		offset = -2;
	}

#ifdef DEBUG
    log->dlog(ch, "ending get_offset: %d", offset);
#endif	
	return offset;
}

ipap_message::ipap_message(unsigned char * param, size_t message_length, bool _encode_network):
	message(NULL), g_tstart(0), encode_network(_encode_network), require_output(true)
{
	
    log = Logger::getInstance();
    ch = log->createChannel("IPAP_MESSAGE");

#ifdef DEBUG
    log->dlog(ch, "Starting method ipap_message");
#endif	
	
	int nrecords;
	nrecords = ipap_import(param, message_length );

#ifdef DEBUG
    log->dlog(ch, "Ending method ipap_message - bytes read:%d", nrecords);
#endif		

}


/*
 * name:        ipap_parse_hdr()
 * parameters:
 */
void 
ipap_message::ipap_parse_hdr( unsigned char *mes, int offset )
{
	
#ifdef DEBUG
    log->dlog(ch, "Starting method ipap_parse_hdr");
#endif
	
    uint16_t _count, _length, _version;
    uint32_t _sysuptime, _unixtime, _exporttime, _seqno, _domainid; 
        
    if (encode_network == true){
		READ16(_version, mes);
	}
	else{
		READ16_NOENCODE(_version,mes);
	}
	
    switch ( _version ) {

      case IPAP_VERSION:

          if ( (offset) < IPAP_HDR_BYTES )
              throw ipap_bad_argument("Length of the message header is less than required");

		  if (encode_network == true){
		      READ16(_length, mes+2);
		      READ32(_exporttime, mes+4);		      
		      READ32(_seqno, mes+8);
		      READ32(_domainid, mes+12);
		  }
		  else{
			  READ16_NOENCODE(_length,mes+2);
			  READ32_NOENCODE(_exporttime,mes+4);
			  READ32_NOENCODE(_seqno,mes+8);
			  READ32_NOENCODE(_domainid, mes+12);
		  }
#ifdef DEBUG
		  log->dlog(ch, "Header received - lengh:%d exporttime %d seqno:%d domainid:%d", _length, _exporttime, _seqno, _domainid );
#endif

		  /* Initialize the message object */
		  init(_domainid, _version); 
          message->version = _version;
          message->length = _length;
          message->exporttime = _exporttime;
          message->seqno = _seqno;
          message->domain_id = _domainid;
          break;

      default:
          message->version = -1;
          throw ipap_bad_argument("Invalid Message Version");
    }

#ifdef DEBUG
    log->dlog(ch, "Ending method ipap_parse_hdr");
#endif
	
}


/*
 * name:        ipap_decode_trecord()
 * func:        create or update template inside ifh. 
 * return:      0/-1
 */
void
ipap_message::ipap_decode_trecord( int setid,
								   const unsigned char     *buf2,
								   size_t         len,
								   int            *nread )
{

    ipap_template *t;
    uint16_t          templid, nfields, ndatafields;
    int               i;
    size_t            offset;

    errno = EIO;
    const uint8_t * buf = reinterpret_cast<const uint8_t*>(buf2);

#ifdef DEBUG
    log->dlog(ch, "Starting method ipap_decode_trecord");
#endif	

    /** read template header
     */
    switch( setid ) {
      case IPAP_SETID_AUCTION_TEMPLATE:
      case IPAP_SETID_BID_TEMPLATE:
      case IPAP_SETID_ALLOCATION_TEMPLATE:
      case IPAP_OPTNS_AUCTION_TEMPLATE:
      case IPAP_OPTNS_BID_TEMPLATE:
      case IPAP_OPTNS_ALLOCATION_TEMPLATE:
                    
          if ( len<4 )
             throw ipap_bad_argument("invalid message lenght");
          if (encode_network == true){
			  READ16(templid, buf);
              READ16(nfields, buf+2);

          }
          else{
			  READ16_NOENCODE(templid,buf);
              READ16_NOENCODE(nfields,buf+2);
		  }

#ifdef DEBUG
		  log->dlog(ch, "Method ipap_decode_trecord - templid:%d, nfields:%d", 
						templid, nfields);
#endif	
					
          offset = 4;
          ndatafields  = nfields;
          break;
      default:
          throw ipap_bad_argument("Invalid template the setid is wrong");
    }

    if ( nfields == 0 ) {
        /** 
         * template withdrawal message
         */
        if ( templid == setid ) {
            delete_all_templates();
        }
        else{
			message->templates.delete_template(templid);
		}

        *nread = offset;
    }


    /** 
     * gets template node ( create or obtain it from the message).
     */
    try
    {
		t = message->templates.get_template(templid);
        // Replace the template.
        message->templates.delete_template( templid );
    }
    catch(ipap_bad_argument &bad){
		// Continue.
	}	

#ifdef DEBUG
	log->dlog(ch, "It is going to create the template");
#endif
	
	/** alloc mem
	*/
	switch( setid ) {
      case IPAP_SETID_AUCTION_TEMPLATE:
      case IPAP_SETID_BID_TEMPLATE:
      case IPAP_SETID_ALLOCATION_TEMPLATE:
	  case IPAP_OPTNS_AUCTION_TEMPLATE:
      case IPAP_OPTNS_BID_TEMPLATE:
      case IPAP_OPTNS_ALLOCATION_TEMPLATE:
      
			templid = new_data_template( nfields, (ipap_templ_type_t) setid );
			break;
	  default:
		    throw ipap_bad_argument("Invalid template type"); 
	        break;
	}
	
	t = message->templates.get_template(templid);	
    t->set_id(templid);
    t->set_maxfields(nfields);

#ifdef DEBUG
		  log->dlog(ch, "Method ipap_decode_trecord - type of template::%d", 
						t->get_type());
#endif	    

    /** read field definitions
     */
    try
    {
		for( i=0;  i < nfields; i++ ) {
			if (offset >= len)
				throw ipap_bad_argument("Field in template has a longer length than message"); 
			else
				read_field(t, buf+offset, len-offset, &offset);
		}
		*nread = offset;		
	}
	catch (ipap_bad_argument bad)
	{
		message->templates.get_template(templid);
		throw ipap_bad_argument("Could not read the template information"); 
	}

}


int
ipap_message::get_num_templates(void)
{

#ifdef DEBUG
    log->dlog(ch, "Starting method get_num_templates");
#endif

	if (message == NULL)
		return 0;
	else
		return (message->templates).get_num_templates();
}

void 
ipap_message::read_field(ipap_template *templ, const uint8_t  *buf, 
						 size_t   buflen, size_t   *nread)
{
    uint16_t ftype;
    uint16_t length;
    int unknown_f;
    int relay_f;
    int eno;

#ifdef DEBUG
    log->dlog(ch, "Starting method read_field");
#endif

    
    if (encode_network == true)
		relay_f = 1;
	else 
		relay_f = 0;    

    if ( buflen<4 ) 
    {
        throw ipap_bad_argument("Buffer has not enough information to read a field");
    }
    
    if (templ== NULL){
		throw ipap_bad_argument("Invalid template definition for reading a field");
	}
    
    // Verifies that the field can be added
    if ( ( templ->get_numfields() >= templ->get_maxfields() )){
		throw ipap_bad_argument("It cannot insert the new field, max field reached");	
	}
    
    // Reads the field from the buffer.
    if (encode_network == true){
		READ16(ftype, buf);
		READ16(length, buf+2);
	}
	else{
		READ16_NOENCODE(ftype, buf);
		READ16_NOENCODE(length, buf+2);		
	}
    (*nread) += 4;

    if ( ftype & IPAP_EFT_VENDOR_BIT ) {
        if ( buflen<8 ) {
            throw ipap_bad_argument("Invalid buffer len for reading a vendor field");
        }
        ftype &= (~IPAP_EFT_VENDOR_BIT);
        if (encode_network == true){
			READ32(eno, buf+4);
		}
		else{
			READ32_NOENCODE(eno,buf+4);
		}
        (*nread) += 4;
    } 
    else {
        eno = IPAP_FT_NOENO;
    }
		
    try
    {
        ipap_field field = g_ipap_fields.get_field(eno, (int) ftype);
        templ->add_field(length, KNOWN, relay_f, field);
		
#ifdef DEBUG
    log->dlog(ch, "Method read_field - fields found: %s", 
					(field.get_field_type().name).c_str()  );
#endif		
		
	}
	catch(ipap_bad_argument e)
	{	
        /** unknown field -> generate node
         */
        /* mark node, so we can drop it later */
        ipap_field field = g_ipap_fields.get_field(0, 0);
        templ->add_field(length, UNKNOWN, relay_f, field);
#ifdef DEBUG
		log->dlog(ch, "Method read_field - field unfound: %s", 
						(field.get_field_type().name).c_str()  );
#endif	
	}

#ifdef DEBUG
    log->dlog(ch, "Method read_field - total fields: %d", 
					templ->get_numfields()  );
#endif	
	
}


/*
 * name:        ipap_decode_datarecord()
 * parameters:
 * desc:        this func parses and exports the ipfix data set
 * todo:        parse message before calling this func
 */
void ipap_message::ipap_decode_datarecord( ipap_template *templ,
											unsigned char  *buf, 
											int   buflen,
											int   *nread )
{
    uint8_t       *p;
    int           i, len, bytesleft;
    ipap_data_record g_data(templ->get_template_id());
    char salida[30];

#ifdef DEBUG
    log->dlog(ch, "Starting method ipap_decode_datarecord");
#endif

    /** parse message
     */
    bytesleft = buflen;
    *nread    = 0;
    p         = reinterpret_cast<uint8_t*>(buf);
        
    for ( i=0; i < templ->get_numfields(); i++ ) {

        len = templ->get_field(i).flength;

#ifdef DEBUG
	log->dlog(ch, "Starting to read field %d len:%d bytesleft:%d",i, len,bytesleft);
#endif	
        if ( len == IPAP_FT_VARLEN ) {
            len =*p;
            p++;
            (*nread) ++;
            if ( len == 255 ) {
				if (encode_network == true){
					READ16(len, p);
				}
				else{
					READ16_NOENCODE(len,p);
				}
                p += 2;
                (*nread) +=2;
            }
        }
		
        bytesleft -= len;
        if ( bytesleft < 0 ) {
            throw ipap_bad_argument("Invalid buffer len for reading the data");
        }
		
        ipap_value_field value;
        if (encode_network)
        {
			value = (templ->get_field(i).elem).decode(p,len, 1);
		}
		else
		{
			value = (templ->get_field(i).elem).decode(p,len, 0);
		}

#ifdef DEBUG
		(templ->get_field(i).elem).snprint(salida, 30, value);
		log->dlog(ch, "Reading field eno:%d ftype:%d value:%s", 
					(templ->get_field(i).elem).get_field_type().eno,
					(templ->get_field(i).elem).get_field_type().ftype,
					 salida);
#endif
				
        g_data.insert_field((templ->get_field(i).elem).get_field_type().eno, 
						    (templ->get_field(i).elem).get_field_type().ftype, value); 
						    
        p        += len;
        (*nread) += len;
    }
    
    data_list.push_back(g_data);

#ifdef DEBUG
    log->dlog(ch, "Ending method ipap_decode_datarecord");
#endif

}

ipap_template * 
ipap_message::get_template(uint16_t templid)
{

#ifdef DEBUG
    log->dlog(ch, "Starting method get_template - id: %d", (int) templid);
#endif

	ipap_template * templ = NULL;

	if (message != NULL)
		templ = message->templates.get_template(templid);

#ifdef DEBUG
    log->dlog(ch, "Ending get_template");
#endif

	return templ;
}

ipap_template * 
ipap_message::get_template_object(uint16_t templid)
{

#ifdef DEBUG
    log->dlog(ch, "Starting method get_template");
#endif

	if (message != NULL){
		try{
			ipap_template *templ = (message->templates).get_template(templid);
			templ->copy();
		} catch(ipap_bad_argument &e){
			return NULL;
		}
	}
	else
		return NULL;
}

ipap_template * 
ipap_message::get_template_object(uint16_t templid) const
{

#ifdef DEBUG
    log->dlog(ch, "Starting method get_template");
#endif

	if (message != NULL){
		try{
			ipap_template *templ = (message->templates).get_template(templid);
			templ->copy();
		} catch(ipap_bad_argument &e){
			return NULL;
		}
	}
	else
		return NULL;
}

int 
ipap_message::ipap_import( unsigned char  *buffer, size_t message_length )
{
    unsigned char        *buf;                 /* ipfix payload */
    uint16_t             setid, setlen;        /* set id, set lenght */
    int                  i, nread, offset;     /* counter */
    int                  bytes, bytesleft;
    int                  err_flag = 0;

#ifdef DEBUG
    log->dlog(ch, "Starting method ipap_import: %d", message_length);
#endif

    if (message_length < 2)
		throw ipap_bad_argument("Invalid Message");

    ipap_parse_hdr( buffer, message_length );
	
    switch( message->version ) {
      case IPAP_VERSION:
          buf   = buffer;
          nread = IPAP_HDR_BYTES;
          break;
      default:
          throw ipap_bad_argument("Invalid IPAP Version");
    }
	
    /** read ipap sets
     */
    for ( i=0; (nread+4) < message_length; i++ ) {


        /** read ipap record header (set id, lenght). Verifies that the lenght 
         *  given is valid.
         */
        if (encode_network == true){
			READ16(setid, buf+nread);
			READ16(setlen, buf+nread+2);
		}
		else{
			READ16_NOENCODE(setid, buf+nread);
			READ16_NOENCODE(setlen, buf+nread+2);
		}
		
#ifdef DEBUG
		log->dlog(ch, "Reading data set:%d setid:%d length:%d", i, setid, setlen);
#endif
		
        nread  += 4;
        if ( setlen <4 ) {
            continue;
        }
        setlen -= 4;  // this corresponds to the record's header.
        if (setlen > (message_length - nread)) {
			int ii;

			for (ii = 0; ii < message_length; ii++)
				fprintf(stderr, "[%02x]", ((buffer)[ii] & 0xFF));
			fprintf(stderr, "\n");

			goto end;
		}

		/** read rest of ipap message
         */
        if ( (setid == IPAP_SETID_AUCTION_TEMPLATE)
             || (setid == IPAP_SETID_BID_TEMPLATE)
             || (setid == IPAP_SETID_ALLOCATION_TEMPLATE)
             || (setid == IPAP_OPTNS_AUCTION_TEMPLATE)
             || (setid == IPAP_OPTNS_BID_TEMPLATE)
             || (setid == IPAP_OPTNS_ALLOCATION_TEMPLATE) ) {
            /** parse a template set ( option or normal template ).
             */

            for (offset = nread, bytesleft = setlen; bytesleft > 4;) {

				// mlogf(4, "[%s] set%d: decode template, setlen=%d, left=%d\n",
				//		func, i + 1, setlen, bytesleft);

				ipap_decode_trecord(setid, buf + offset, bytesleft,&bytes);
				bytesleft -= bytes;
				offset += bytes;
			}
            nread += setlen;
        }
        else if ( setid > 255 )
        {
            /** get template
             */
            ipap_template *templ = get_template(setid);

            if ( templ == NULL ) {
                nread += setlen;
                err_flag = 1;
            }
            else {
                /** read data records
                 */
                for ( offset=nread, bytesleft=setlen; bytesleft>0; ) {
                    ipap_decode_datarecord( templ, buf+offset, bytesleft, &bytes );
                    
                    bytesleft -= bytes;
                    offset    += bytes;
                }

                if ( bytesleft ) {
                    // mlogf( 3, "[%s] set%d: skip %d bytes padding\n",
                    //       func, i+1, bytesleft );
#ifdef DEBUG
					log->dlog(ch, "Set:%d skip:%d", setid, bytesleft);
#endif                    
                }
                nread += setlen;
            }
        }
        else {
            // mlogf( 0, "[%s] set%d: invalid set id %d, set skipped!\n",
            //       func, i+1, setid );
            nread += setlen;
        }
    } /* for (read sets */

    if ( err_flag )
        goto errend;

end:
    message->copy_raw_message(buffer, nread);
    
    // Establishes correct values for the current data set.
    if ( setid > 255 ){
		message->cs_tid = setid;
		message->cs_bytes = setlen;
		message->cs_offset = nread - setlen;
		message->cs_header = (u_int8_t *) message->buffer + message->cs_offset;
	}
    message->nrecords = data_list.size();
    
    /** The message does not require ouput.
     */
    require_output = false;

#ifdef DEBUG
		log->dlog(ch, "Ending method ipap_import- characters read %d", nread);
#endif

    
    return nread;

 errend:
    data_list.clear();
    return -1;
	
}


bool 
ipap_message::operator== (const ipap_message& rhs) const
{

#ifdef DEBUG
    log->dlog(ch, "Starting method operator==");
#endif		
		
	if ((rhs.message == NULL) and (message == NULL))
		return true;

	if ((rhs.message != NULL) and (message == NULL))
		return false;

	if ((rhs.message == NULL) and (message != NULL))
		return false;
			
	// compare message header information.
	if ((rhs.message != NULL) and (message != NULL)){
		
		if (*(rhs.message) != *message){
#ifdef DEBUG
			log->dlog(ch, "Ending method operator== different message header");
#endif				
			return false;
		}
									
		try
		{
			for (int i = 0; i < data_list.size(); i++){
				if ( data_list[i] != rhs.data_list[i] ){
#ifdef DEBUG
					log->dlog(ch, "Ending method operator== different data");
#endif				
					return false;
				}
			}
		}
		catch(const std::out_of_range& oor)
		{
			return false;
		}
	}

#ifdef DEBUG
    log->dlog(ch, "Ending method operator== return true");
#endif			
	return true;
			
}

/**
* Assignment operator. 
*/
ipap_message &
ipap_message::operator=(const ipap_message &other)
{

#ifdef DEBUG
    log->dlog(ch, "Starting method operator=");
#endif	
	
	if (other.message != NULL)
	   message = new ipap_t(*other.message);
	g_ipap_fields = other.g_ipap_fields;
	g_tstart = other.g_tstart;
	g_lasttid = other.g_lasttid;
	data_list = other.data_list;
	encode_network = other.encode_network;
	require_output = other.require_output;
	
	return *this;
	
}

/*
 * name:        get_template_list()
 * parameters:
 */
std::list<int> ipap_message::get_template_list(void) const
{
	if (message != NULL)
		return message->templates.get_template_list();
	else{
		std::list<int> empty;
		return empty;
	}
}

/*
 * name:        ipap_message()
 * parameters:
 */
ipap_message::ipap_message(const ipap_message &other):
	message(NULL), g_tstart(other.g_tstart), 
	g_ipap_fields(other.g_ipap_fields), g_lasttid(other.g_lasttid), 
	data_list(other.data_list), encode_network(other.encode_network),
	require_output(other.require_output)
{

    log = Logger::getInstance();
    ch = log->createChannel("IPAP_MESSAGE");

#ifdef DEBUG
    log->dlog(ch, "Starting constructor ipap_message based in another \
					instance, require output %d", other.require_output);
#endif
    	
	if (other.message != NULL)
	{
		message = new ipap_t(*(other.message));
	}

#ifdef DEBUG
    log->dlog(ch, "Ending constructor ipap_message based in another \
					instance, require output %d", require_output);
#endif	    


}

/*
 * name:        begin()
 * parameters:
 */
dateRecordListConstIter_t ipap_message::begin(void) const
{
	return data_list.begin();
}
	   
/*
 * name:        end()
 * parameters:
 */
dateRecordListConstIter_t ipap_message::end(void) const
{
	return data_list.end();
}

/*
 * name:        get_domain()
 * parameters:
 */
int ipap_message::get_domain()
{
	if (message != NULL){
		return message->domain_id;
	} else{
		return 0;
	}
}

/*
 * name:        get_domain()
 * parameters:
 */
int ipap_message::get_domain() const
{
	if (message != NULL){
		return message->domain_id;
	} else{
		return 0;
	}
}

/*
 * name:        get_last_template_id()
 * parameters:
 */
uint16_t ipap_message::get_last_template_id()
{	
	return g_lasttid;
}

/*
 * name:        get_last_template_id()
 * parameters:
 */
uint16_t ipap_message::get_last_template_id() const
{	
	return g_lasttid;
}

/*
 * name:        get_version()
 * parameters:
 */
int ipap_message::get_version()
{
	if (message != NULL){
		return message->version;
	} else{
		return IPAP_VERSION;
	}
}

/*
 * name:        get_version()
 * parameters:
 */
int ipap_message::get_version() const
{
	if (message != NULL){
		return message->version;
	} else{
		return IPAP_VERSION;
	}
}

/*
 * name:        get_seqno()
 * parameters:
 */
uint32_t ipap_message::get_seqno()
{
	if (message != NULL){
		return message->seqno;
	} else{
		return 0;
	}
}

/*
 * name:        get_seqno()
 * parameters:
 */	   
uint32_t ipap_message::get_seqno() const
{
	if (message != NULL){
		return message->seqno;
	} else{
		return 0;
	}	
}
	   
/*
 * name:        get_exporttime()
 * parameters:
 */
uint32_t ipap_message::get_exporttime()
{
	if (message != NULL){
		return message->exporttime;
	} else{
		return 0;
	}
}

/*
 * name:        get_exporttime()
 * parameters:
 */
uint32_t ipap_message::get_exporttime() const
{
	if (message != NULL){
		return message->exporttime;
	} else {
		return 0;
	}
}

/*
 * name:        set_seqno()
 * parameters:
 */
void ipap_message::set_seqno(uint32_t _seqno)
{
	if (message != NULL){
		message->seqno = _seqno;
	} else {
		throw  ipap_bad_argument("IpAp_message: set seqno, message not initiazed");
	}
}

/*
 * name:        set_exporttime()
 * parameters:
 */
void ipap_message::set_exporttime(uint32_t _exporttime)
{
	if (message != NULL){
		message->exporttime = _exporttime;
	} else {
		throw  ipap_bad_argument("IpAp_message: set exporttime, message not initiazed");
	}
}
