/*! \file   IpAp_t.cpp

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
    export declarations of ipap protocol

    $Id: ApAp.cpp 748 2015-08-26 18:48:00Z amarentes $
*/


#include "IpAp_t.h"
#include <stdio.h>
#include <stdlib.h>


ipap_t::ipap_t():
domain_id(0), version(IPAP_VERSION), syn(false), ack(false), fin(false), buffer(NULL), nrecords(0), offset(0),
buffer_lenght(0), seqno(0), ackseqno(0), cs_tid(0), cs_bytes(0), cs_offset(0), 
cs_header(NULL), length(0), exporttime(0)
{

   buffer = ( unsigned char * )calloc( IPAP_DEFAULT_BUFLEN , sizeof( unsigned char ) );
   buffer_lenght = IPAP_DEFAULT_BUFLEN;

}


ipap_t::ipap_t(const ipap_t& rhs):
domain_id(0), version(IPAP_VERSION), syn(false), ack(false), fin(false),
buffer(NULL), nrecords(0), offset(0), buffer_lenght(0), seqno(0), ackseqno(0),
cs_tid(0), cs_bytes(0), cs_offset(0), cs_header(NULL), length(0), exporttime(0)
{

	domain_id = rhs.domain_id;
	version = rhs.version;
	syn = rhs.syn;
	ack = rhs.ack;
	fin = rhs.fin;
	templates = rhs.templates;
	nrecords = rhs.nrecords;
	offset = rhs.offset;
	seqno = rhs.seqno;
	ackseqno = rhs.ackseqno;
	buffer_lenght = rhs.buffer_lenght;
	if (buffer_lenght > 0){
		buffer = ( unsigned char * )calloc( buffer_lenght , sizeof( unsigned char ) );
		memcpy(buffer,rhs.buffer,rhs.offset);
	}
	
	cs_tid = rhs.cs_tid;
	cs_bytes = rhs.cs_bytes;
	cs_offset = rhs.cs_offset;
	// put the pointer the number of positions given by cs_header.
	
	if (rhs.cs_header != NULL)
		cs_header = (uint8_t*)(buffer) + cs_offset;
	else
		cs_header = NULL;
	
	length = rhs.length;
	exporttime = rhs.exporttime;

}


/**
* Destructor of the class
*/
ipap_t::~ipap_t()
{
	if (buffer != NULL)
		free(buffer);
}

ipap_t &
ipap_t::operator=(const ipap_t & rhs)
{

	if (buffer != NULL)
		free(buffer);
	
	domain_id = rhs.domain_id;
	syn = rhs.syn;
	ack = rhs.ack;
	fin = rhs.fin;
	version = rhs.version;
	templates = rhs.templates;
	nrecords = rhs.nrecords;
	offset = rhs.offset;
	seqno = rhs.seqno;
	ackseqno = rhs.ackseqno;
	buffer_lenght = rhs.buffer_lenght;	
	if (buffer_lenght > 0){
		buffer = ( unsigned char * )calloc( buffer_lenght, sizeof( unsigned char ) ); 
		memcpy(buffer,rhs.buffer,rhs.offset);
	}
	
	cs_tid = rhs.cs_tid;
	cs_bytes = rhs.cs_bytes;
	cs_offset = rhs.cs_offset;
	// put the pointer the number of positions given by cs_header.
	
	if (rhs.cs_header != NULL)
		cs_header = (uint8_t*)(buffer) + cs_offset;
	else
		cs_header = NULL;
	
	length = rhs.length;
	exporttime = rhs.exporttime;
	
	return *this;
}


bool 
ipap_t::operator== (const ipap_t& rhs)
{	

	if ( (domain_id != rhs.domain_id) ||
	   (version != rhs.version) ||
	   (syn != rhs.syn) ||
	   (ack != rhs.ack) ||
	   (fin != rhs.fin) ||
	   (nrecords != rhs.nrecords) ||
	   (seqno != rhs.seqno)  || 
	   (ackseqno != rhs.ackseqno)
	   ){
		
		return false;
	}

	if 	((offset != rhs.offset) ||
	   (buffer_lenght != rhs.buffer_lenght))
		return false;
	
	if 	(templates != rhs.templates) 
		return false;

	if (version == IPAP_VERSION){
		if ( (rhs.length != length) ||
			 (rhs.exporttime != exporttime) ){
			return false;
		}
	}

	return true;
	    
}

bool 
ipap_t::operator!= (const ipap_t& rhs)
{
	return !(operator==(rhs));
}


void
ipap_t::copy_raw_message(unsigned char * msg, size_t _offset)
{
	// release the memory assigned to the buffer
	free(buffer);
	buffer = ( unsigned char * )calloc( _offset + 1, sizeof( unsigned char ) );
	memcpy(buffer,msg,_offset);
	buffer_lenght = _offset;
	offset = _offset;

}

void 
ipap_t::reinitiate_buffer(void)
{
   if (buffer != NULL) {
	   free(buffer);
   }
   
   buffer = ( unsigned char * )calloc( IPAP_DEFAULT_BUFLEN,  sizeof( unsigned char ) ); 
   buffer_lenght = IPAP_DEFAULT_BUFLEN;
   offset = 0;

}

uint8_t
ipap_t::get_flags(void)
{
    uint8_t res= 0;
    if (syn)
        res |= 1 << 0;

    if (ack)
        res |= 1 << 1;

    if (fin)
        res |= 1 << 2;

    return res;
}

void
ipap_t::set_flags(uint8_t flags)
{

    const uint8_t syn_comp = 0x1;
    const uint8_t ack_comp = 0x2;
    const uint8_t fin_comp = 0x4;

    syn = flags & syn_comp;
    ack = (flags & ack_comp) >> 1;
    fin = (flags & ack_comp) >> 2;

}