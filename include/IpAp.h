/*! \file   IpAp.h

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

    $Id: ApAp.h 748 2015-08-26 18:48:00Z amarentes $
*/


#ifndef IPAP_H
#define IPAP_H

#include <inttypes.h>
#include "IpAp_def.h"

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
typedef struct {
    uint16_t   version;     /* version of the format of this packet */
    union {
        struct {
            uint16_t   length;      /* total number of record in this packet */
            uint32_t   exporttime;  /* seconds since 1970 */
        } ipfix;
    } u;
    uint32_t   seqno;       /* incremental sequence counter */

} ipap_hdr_t;


#define IPAP_DEFAULT_BUFLEN 		1400
#define IPAP_VERSION               0x01
#define IPAP_HDR_BYTES             12
#define IPAP_SETID_AUCTEMPLATE     1  // Auction Template
#define IPAP_SETID_BIDTEMPLATE     2  // Bid Template
#define IPAP_SETID_ALLTEMPLATE     3  // Allocation Template

#define IPAP_FT_VARLEN             65535
#define IPAP_FT_NOENO              0
#define IPAP_EFT_VENDOR_BIT        0x8000


/** bearer protocol
 */
typedef enum {
    IPAP_PROTO_SCTP = 132,    /* IPPROTO_SCTP */    
    IPAP_PROTO_TCP  = 6,      /* IPPROTO_TCP  */    
    IPAP_PROTO_UDP  = 17      /* IPPROTO_UDP  */    
} ipap_proto_t;

typedef struct
{
    uint16_t            flength;           /* less or eq. elem->flength  */
    int                 unknown_f;         /* set if unknown elem */
    int                 relay_f;           /* just relay no, encoding (exp.) */
    ipap_field_t       *elem;
} ipap_template_field_t;

typedef struct ipap_datarecord
{
    void              **addrs;
    uint16_t          *lens;
    uint16_t          maxfields;         /* sizeof arrays */
} ipap_datarecord_t;

typedef enum {
    AUCTION_TEMPLATE,
    BID_TEMPLATE,
    ALLOCATION_TEMPLATE
} ipap_templ_type_t;

typedef struct ipap_template
{
    struct ipap_template   *next; /* for internal use          */
    ipap_templ_type_t      type;  /* Auction, Bid, or Allocation template   */
    time_t                  tsend; /* time of last transmission */

    uint16_t                tid;
    int                     nfields;        /* number of fields */
    ipap_template_field_t  *fields;
    int                     maxfields;         /* sizeof fields */
} ipap_template_t;

typedef struct
{
    int              version;     /* ipfix version to export */
    ipap_template_t *templates;  /* list of templates  */

    char        *buffer;          /* output buffer */
    int         nrecords;         /* no. of records in buffer */
    size_t      offset;           /* output buffer fill level */
    uint32_t    seqno;            /* sequence no. of next message */

    /* experimental */
    int        cs_tid;            /* template id of current dataset */
    int        cs_bytes;          /* size of current set */
    uint8_t    *cs_header;        /* start of current set */

} ipap_t;

typedef struct {
    int       eno;			/* IPAP enterprize number, 0 for standard element */
    uint16_t  ienum;		/* IPAP information element number */
    uint16_t  length;		/* length of this element in bytes - use 65535 for varlen elements */
} export_fields_t;


class ipap_message
{
	
   private:
   
   
   public:	
   
	   int  ipap_open( ipap_t **ifh, int sourceid, int ipap_version );

	   int  ipap_new_auction_template( ipap_t *ifh,
                              ipap_template_t **templ, int nfields );

	   int  ipap_new_bid_template( ipap_t *ifh,
                              ipap_template_t **templ, int nfields );

	   int  ipap_new_allocation_template( ipap_t *ifh,
                              ipap_template_t **templ, int nfields );
                                                              
	   int  ipap_add_field( ipap_t *ifh, ipap_template_t *templ,
                      uint32_t enterprise_number,
                      uint16_t type, uint16_t length );
                                                  
	   void ipap_delete_template( ipap_t *ifh, ipap_template_t *templ );
	   
	   int  ipap_make_template( ipap_t *handle, ipap_template_t **templ,
                         export_fields_t *fields, int nfields );
                         
	   int  ipap_export( ipap_t *ifh, ipap_template_t *templ, ... );
	   
	   
	   int  ipap_export_array( ipap_t *ifh, ipap_template_t *templ,
                         int nfields, void **fields, uint16_t *lengths );
                         
	   int  ipap_export_flush( ipap_t *ifh );
	   
	   void ipap_close( ipap_t *ifh );

	   ipap_message();
	   
	   ~ipap_message();

}

#endif // IPAP_H
