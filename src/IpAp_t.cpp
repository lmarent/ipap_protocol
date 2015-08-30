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


ipap_t::ipap_t():
nrecords(0), offset(0), buffer_lenght(0), buffer(NULL), cs_tid(0), 
cs_bytes(0), cs_header(NULL), length(0), exporttime(0), cs_offset(0)
{

   buffer = new char[IPAP_DEFAULT_BUFLEN];
   buffer_lenght = IPAP_DEFAULT_BUFLEN;

}



/**
* Destructor of the class
*/
ipap_t::~ipap_t()
{
	saveDelete(buffer);
}

ipap_t &
ipap_t::operator=(const ipap_t & rhs)
{

	version = rhs.version;
	templates = rhs.templates;
	nrecords = rhs.nrecords;
	offset = rhs.offset;
	seqno = rhs.seqno;
	if (buffer_lenght > 0){
		buffer = new char[buffer_lenght];
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
	if ( (version != rhs.version) ||
	   (templates != rhs.templates) ||
	   (nrecords != rhs.nrecords) ||
	   (offset != rhs.offset) ||
	   (buffer_lenght != rhs.buffer_lenght) ||
	   (seqno != rhs.seqno)  
	   )
		return false;
					
	if (version == IPAP_VERSION)
		if ( (rhs.length != length) ||
			 (rhs.exporttime != exporttime) )
			return false;
		
	return true;
	    
}

bool 
ipap_t::operator!= (const ipap_t& rhs)
{
	return !(operator==(rhs));
}


void
ipap_t::copy_raw_message(char * msg, size_t _offset)
{
	if (offset<= buffer_lenght){
		// release the memory assigned to the buffer
		delete buffer;
		buffer = new char[buffer_lenght];
		memcpy(buffer,msg,_offset);
		offset = _offset;
	}
	else
		throw ipap_bad_argument("buffer length not enough for the raw copy");
}
