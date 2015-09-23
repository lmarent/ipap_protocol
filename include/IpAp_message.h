/*! \file   IpAp_message.h

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

    $Id: IpAp_message.h 748 2015-08-26 18:48:00Z amarentes $
*/


#ifndef IPAP_MESSAGE_H
#define IPAP_MESSAGE_H

#include "stdincpp.h"
#include "Logger.h"
#include "IpAp_def.h"
#include "IpAp_field.h"
#include "IpAp_field_container.h"
#include "IpAp_data_record.h"
#include "IpAp_template.h"
#include "IpAp_t.h"

#ifndef ENOTSUP
#define ENOTSUP EOPNOTSUPP
#endif


	
/*------ structs ---------------------------------------------------------*/

/** ipap header format
 **  0                   1                   2                   3
 **    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 **   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 **   |       Version Number          |            Length             |
 **   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 **   |                         Export Time                           |
 **   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 **   |                       Sequence Number                         |
 **   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */   

#define IPAP_HDR_BYTES             	12
#define IPAP_SETID_AUCTEMPLATE     	1  // Auction Template
#define IPAP_SETID_BIDTEMPLATE     	2  // Bid Template
#define IPAP_SETID_ALLTEMPLATE     	3  // Allocation Template
#define IPAP_FT_VARLEN             65535
#define IPAP_FT_NOENO              0
#define IPAP_EFT_VENDOR_BIT        0x8000

#define IPAP_DFLT_TEMPLRESENDINT   30
#define IPAP_DFLT_TEMPLLIFETIME    300


/**
 * \class export_fields_t
 *
 * \brief This structure is used to create a template associated to the message 
 *   
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2014/12/18 9:57:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */
typedef struct {
    int       eno;		/* IPFIX enterprize number, 0 for standard element */
    uint16_t  ienum;		/* IPFIX information element number */
    uint16_t  length;		/* length of this element in bytes - use 65535 for varlen elements */
} export_fields_t;


typedef vector<ipap_data_record>   dataRecordList_t;
typedef vector<ipap_data_record>::iterator dateRecordListIter_t;
typedef vector<ipap_data_record>::const_iterator dateRecordListConstIter_t;


/**
 * \class ipap_message
 *
 * \brief This class is the factory class to export and import a IPAP messsage
 * 
 * This class is the factory class to export and import a IPAP messsage
 * 
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2014/12/18 9:57:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */
class ipap_message
{
	
   private:
   
	   Logger *log; //!< link to global logger object
	   int ch;      //!< logging channel number used by objects of this class

	   ipap_t * 							message;			///< Header Information, templates and end buffer for the message
	   ipap_field_container 				g_ipap_fields;		///< Collection of fields that can be exchanged
	   time_t             					g_tstart;			///< datetime when the message starts for processing
	   uint16_t           					g_lasttid;          ///< last sequence id given
	   vector<ipap_data_record> 			data_list; 			///< List of data record asociated with the message
	   bool                             	encode_network;		///< Convert to network encoding 
	   bool 								require_output;		///< Control in the messsage has changed since the last output execution.
														
	
   protected:
	
	   /**
	    * Alloc memory for buffers and pointers used to construct the message
	    */
	   void init( int ipap_version );
	   	   
	   /**
	    * Adds a field of vendor type to the collection of fields
	    */
	   void add_vendor_information_elements( ipap_field_type_t *fields );
	   
	   /**
	    * creates and add a new template for the messsage
	    * @param  nfields	- The number of fields to include in the template
	    * @return 			- Template id.
	    */
	   uint16_t new_template( int nfields );


	   /**
	    * Find a return a reference to a template with id: templid
	    * @param templid - Id of the template
	    * @return reference to the template, if not found, it returns NULL.
	    */
	   ipap_template * get_template(uint16_t templid);
	   
	   /**
	    * Finish the current record set assigning the lenght and te template id.
	    */
	   void finish_cs( void );
	   
	   /**
	    * Write the message header. When the data associated with the message is empty 
	    * it does not do anything.
	    */
	   void _write_hdr( void );
	   	   
	   /**
	    * This method is used for completing the message once it is ready. 
	    */
	   void _output_flush( void );
	   
	   /**
	    * This method reallocates memory for the output buffer.
	    * @param additional - the number of additional bytes to allocate.
	    */
	   void allocate_additional_memory( size_t additional );
	   
	   /**
	    * This method write into the buffer the template definition.
	    * @param templ - pointer to the template object to write.
	    */
	   void _write_template( ipap_template  *templ );
	   			   
	   /**
	    * This method parse the header of a IPAP message that is on mes character string
	    * @param mes - Character string containing the message
	    * 		 offset - Lenght of character string
	    */
	   void ipap_parse_hdr( unsigned char *mes, int offset );
	   
	   /**
	    * parse and construct a template reading characters in buf.
	    * @param setid - template id
	    * 		 buf   - character string to read
	    * 		 len   - Number of characters to read as part of template
	    * 		 nread - Number of characters read ( output).
	    */
	   void ipap_decode_trecord( int setid,
								const unsigned char     *buf,
								size_t         len,
								int            *nread );
	   
	   /**
	    * parse and read a field value from characters in buf.
	    * @param templ 	- template pointer associated to the record data which the field belongs to
	    * 		 buf2  	- character string to read
	    * 		 buflen - Number of characters to read
	    * 		 nread 	- Number of read characters ( output).
	    */
	   void read_field(ipap_template *templ, 
					   const uint8_t  *buf2, 
					   size_t   buflen, 
					   size_t   *nread);

	   /**
	    * parse and read a record set  from characters in buf.
	    * @param templ 	- template pointer associated to the record data
	    * 		 buf2  	- character string to read
	    * 		 buflen - Number of characters to read
	    * 		 nread 	- Number of read characters ( output).
	    */
	   void ipap_decode_datarecord( ipap_template *templ,
								    unsigned char      *buf, 
								    int                buflen,
								    int                *nread );
	   	   	   
	   /**
	    * Return the number of templates included
	    */
	    int get_num_templates(void);
	    
	    /**
	    * Export the message to the internal buffer. Only export the data associated 
	    * with the template given as parameter
	    *  @param templid 		- Template Id.
	    */
	   void output_set( uint16_t templid );
	   
   public:	

	   /**
	    * Create a new class ipap_message
	    * @param By default it sets the version in IPAP and encode in true, 
	    * 		    the source id is set to 0.
	    */
	   ipap_message();

	   /**
	    * Create a new class ipap_message
	    * @param _encode_network - establish whether the message is going to be network encoded or not. 
	    */
	   ipap_message(bool _encode_network);

	   /**
	    * Create a new class ipap_message
	    * @param ipap_version 	 - message version. 
	    *  		 _encode_network - establish whether the message is going to be network encoded or not. 
	    */
	   ipap_message( int ipap_version, bool _encode_network);
	   
	   /**
	    * Create a new class ipap_message
	    * @param param  		 - buffer containing the message.
	    * 		 message_length	 - length of the message.
	    *  		 _decode_network - establish whether the message is going to be network decoded or not. 
	    */
	   ipap_message(unsigned char * param, size_t message_length, bool _decode_network);
	   
	   ipap_message(const ipap_message &rhs);
	   
	   /**
	    * Destructor.
	    */
	   ~ipap_message(void);

	   /**
	    * Release memory for buffers and pointers used to construct the message
	    */
	   void close( void );
	      
	   /**
	    * creates and add a new data template for the messsage
	    * @param  nfields	- The number of fields to include in the template
	    * 		  type 		- Type of template to create.
	    * @return template id  
	    */
	   uint16_t new_data_template( int nfields, ipap_templ_type_t type );
                              
	   /**
	    * Find a return a reference to a template with id: templid 
	    * It makes an object copy.
	    * @param templid - Id of the template
	    * @return reference to the template, if not found, it returns NULL.
	    */
	   ipap_template * get_template_object(uint16_t templid);

                   
	   /**
	    * Get a field definition from the container field
	    * @param eno 		- Enterprise field number id
	    * 		 type		- field type.
	    */
	   ipap_field get_field_definition( int eno, int type );
                                
	   /**
	    * add a data field to the message within a template
	    * @param templid 	- Pointer to the template
	    * 		 eno		- Enterprise field number id
	    *        type		- Field type.
	    */
	   void  add_field( uint16_t templid,
                       uint32_t eno,
                       uint16_t type );
                                                  
	   /**
	    * delete a template associated to the message.
	    * @param templid 		- template id to delete
	    */
	   void delete_template( uint16_t templid );
	   
	   /**
	    * delete all template associated to the message.
	    */
	   void delete_all_templates();
	   
	   /**
	    * Take a list of field types and create a template containing all those fields.
	    * @param fields 	- list of field types to include
	    * 		 nfields 	- number of fields to include
	    * 		 type		- type of template to create.
	    * @return template id  
	    */
	   uint16_t make_template( export_fields_t *fields, 
							   int nfields,
							   ipap_templ_type_t type );
	   
	   /**
	    * Export the message to the internal buffer. This function must be
	    * executed before associating the message as an spec object.
	    */
	   void output(void);	
	   
	   /**
	    * Include set data record to the message 
	    * @param templ 	- Pointer to the template associated to the record data set
	    * 		 data 	- record data set to be included. It must have the same amount
	    * 				  of fields as the template.
	    */
	   void include_data( uint16_t templid, 
						  ipap_data_record &data );
	   
					
	   /**
	    * Get the internal buffer that was exported
	    */
	   unsigned char * get_message(void) const;

	   /**
	    * Get the length of the internal buffer that was exported
	    */
	   int get_offset(void) const;
	   
	   /**
	   *  Equals to operator. 
	   *  It is equal when it has the same amount of templates and 
	   *  data records, and the information inside is equal. The order in
	   * the data records must be same too.
	   */
	   bool operator== (const ipap_message& rhs) const;

	   /**
	    * Assignment operator. 
	    */
	   ipap_message &operator=(const ipap_message &other);


	   /**
	    * parse a message from characters in buf.
	    * @param buffer			- character string to read
	    * 		 message_length - Message length in characters
	    * 		 nread 	- Number of read characters ( output).
	    * @return number of read characters 
	    */
	   int ipap_import(unsigned char *buffer, size_t message_length );
	   
	   /**
	    * Return a list with all templates IDs included
	    */
	   std::list<int> get_template_list(void) const;
	   
	   bool get_require_output(void) const;	   
	   
	   dateRecordListConstIter_t begin(void) const;
	   
	   dateRecordListConstIter_t end(void) const;
};


#endif // IPAP_MESSAGE_H
