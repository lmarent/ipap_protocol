/*! \file   IpAp_t.h

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
    raw information required for a messsage

    $Id: IpAp_t.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_T_H
#define IPAP_T_H	

#include "IpAp_template.h"
#include "IpAp_template_container.h"
#include "IpAp_field.h"




#define IPAP_DEFAULT_BUFLEN 		1400
#define IPAP_VERSION               	0x01

	
class ipap_t
{
    public: 
		int              domain_id;				  ///< Id of the auction domain.
		int              version;     			  ///< ipap version to export.
		ipap_template_container templates;   	  ///< list of templates. 

		unsigned char   *buffer;          		  ///< output buffer - the actual message when exported is put it here.
		int         	nrecords;        		  ///< no. of records in buffer.
		size_t      	offset;           		  ///< Number of bytes in the buffer, output buffer fill level.
		int 			buffer_lenght;    		  ///< output buffer allocated length, it is readjusted as more memory is needed.
		uint32_t   		seqno;            		  ///< sequence no. of the message.
		uint32_t        ackseqno;				  ///< Ack sequence no. for the message.

		int        		cs_tid;            		  ///< template id of current dataset 
		int        		cs_bytes;          		  ///< size of current set
		int 	   		cs_offset;				  ///< offset required for the current set
		uint8_t    		*cs_header;        		  ///< start of current set

        /* Header ipap fields */
        uint16_t   length;      			  ///< total number of record in this packet
        uint32_t   exporttime;  			  ///< seconds since 1970
		
	/**
	 * Constructor of the class
	 */
	ipap_t();
	
	/**
	 * Constructor of the class
	 */
	ipap_t(const ipap_t &rhs);
	
	/**
	 * Destructor of the class
	 */
	~ipap_t();
	
	/**
	 * Assignment operator
	 */
	ipap_t & operator=(const ipap_t & rhs);
	
	/**
	*  Equals to operator. 
	*  It is equal when it has the same amount of templates and every 
	*    template is equal.
	*/
	bool operator== (const ipap_t& rhs);
		
	/**
	*  Not equal to operator. 
	*  It is not equal when it does not have the same amount of templates and at least 
	*    one field is not a template.
	*/
	bool operator!= (const ipap_t& rhs);
	
	/**
	 * Copy the definition of a message into the buffer. It is assumed that 
	 * the message is in the correct ipfix message
	 */
	void copy_raw_message(unsigned char * msg, size_t _offset);

	/**
	 * Release the buffer and reinitiate it
	 */
	void reinitiate_buffer(void);	

};

#endif // IPAP_T_H
