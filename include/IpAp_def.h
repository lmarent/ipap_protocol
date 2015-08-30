/*! \file   IpAp_def.h

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
    IPAP structs in the system - types and definitions

    $Id: ApAp_def.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_DEF_H
#define IPAP_DEF_H

#include "stdincpp.h"

#define IPAP_CODING_INT    1
#define IPAP_CODING_UINT   2
#define IPAP_CODING_BYTES  3
#define IPAP_CODING_STRING 4
#define IPAP_CODING_FLOAT  5
#define IPAP_CODING_NTP    6
#define IPAP_CODING_IPADDR 7

#define REV_PEN 29305

typedef int (*ipap_encode_func) (void *, void*, size_t);
typedef int (*ipap_decode_func) (void *, void*, size_t);
typedef int (*ipap_snprint_func) (char *, size_t, void*, size_t);

typedef struct
{
    int         eno;                /* enterprise number or 0 */
    int         ftype;              /* field type */
    ssize_t     length;             /* field length */
    int         coding;
    string      name;
    string	    documentation;

} ipap_field_type_t;

typedef struct
{
    struct ipap_field   *next;
    ipap_field_type_t   *ft;
    ipap_encode_func    encode;
    ipap_decode_func    decode;
    ipap_snprint_func   snprint;

} ipap_field_t;

#define IPAP_FT_MAXUNITVALUATION       			1
#define IPAP_FT_UNITVALUE             			2
#define IPAP_FT_UNITBUDGET            			3
#define IPAP_FT_TOTALBUDGET           			4
#define IPAP_FT_AUCTIONINGTIMESECONDS       	5
#define IPAP_FT_AUCTIONINGTIMEMILLISECONDS  	6
#define IPAP_FT_AUCTIONINGTIMEMICROSECONDS  	7
#define IPAP_FT_AUCTIONINGTIMENANOSECONDS   	8
#define IPAP_FT_AUCTIONINGALGORITHMCODE       	9
#define IPAP_FT_SOURCEIPV4ADDRESS            	10
#define IPAP_FT_SOURCEIPV4PREFIXLENGTH       	11
#define IPAP_FT_DESTINATIONIPV4ADDRESS       	12
#define IPAP_FT_DESTINATIONIPV4PREFIXLENGTH  	13
#define IPAP_FT_SOURCEIPV6ADDRESS            	14
#define IPAP_FT_DESTINATIONIPV6ADDRESS       	15
#define IPAP_FT_SOURCEIPV6PREFIXLENGTH       	16
#define IPAP_FT_DESTINATIONIPV6PREFIXLENGTH  	17
#define IPAP_FT_PADDINGOCTETS				 	18
#define IPAP_FT_IPHEADERPACKETSECTION        	19
#define IPAP_FT_IPPAYLOADPACKETSECTION       	20
#define IPAP_FT_DATALINKFRAMESECTION         	21
#define IPAP_FT_SOURCEMACADDRESS             	22
#define IPAP_FT_POSTDESTINATIONMACADDRESS    	23
#define IPAP_FT_IDAUCTION			    		24
#define IPAP_FT_IDBID			    			25
#define IPAP_FT_IDALLOCATION					26
#define IPAP_FT_STARTSECONDS             		27
#define IPAP_FT_ENDSECONDS               		28
#define IPAP_FT_STARTMILLISECONDS        		29
#define IPAP_FT_ENDMILLISECONDS          		30
#define IPAP_FT_AUCTIONINGALGORITHMNAME       	31






/* column name definitions
 */

#define IPAP_CN_MAXVALUE              			"ie0_1"
#define IPAP_CN_UNITVALUE             			"ie0_2"
#define IPAP_CN_UNITBUDGET            			"ie0_3"
#define IPAP_CN_TOTALBUDGET           			"ie0_4"
#define IPAP_CN_AUCTIONINGTIMESECONDS       	"ie0_5"
#define IPAP_CN_AUCTIONINGTIMEMILLISECONDS  	"ie0_6"
#define IPAP_CN_AUCTIONINGTIMEMICROSECONDS  	"ie0_7"
#define IPAP_CN_AUCTIONINGTIMENANOSECONDS   	"ie0_8"
#define IPAP_CN_AUCTIONINGALGORITHM           	"ie0_9"
#define IPAP_CN_SOURCEIPV4ADDRESS            	"ie0_10"
#define IPAP_CN_SOURCEIPV4PREFIXLENGTH       	"ie0_11"
#define IPAP_CN_DESTINATIONIPV4ADDRESS       	"ie0_12"
#define IPAP_CN_DESTINATIONIPV4PREFIXLENGTH  	"ie0_13"
#define IPAP_CN_SOURCEIPV6ADDRESS            	"ie0_14"
#define IPAP_CN_DESTINATIONIPV6ADDRESS       	"ie0_15"
#define IPAP_CN_SOURCEIPV6PREFIXLENGTH       	"ie0_16"
#define IPAP_CN_DESTINATIONIPV6PREFIXLENGTH  	"ie0_17"
#define IPAP_CN_PADDINGOCTETS				 	"ie0_18"
#define IPAP_CN_IPHEADERPACKETSECTION        	"ie0_19"
#define IPAP_CN_IPPAYLOADPACKETSECTION       	"ie0_20"
#define IPAP_CN_DATALINKFRAMESECTION         	"ie0_21"
#define IPAP_CN_SOURCEMACADDRESS             	"ie0_22"
#define IPAP_CN_POSTDESTINATIONMACADDRESS    	"ie0_23"
#define IPAP_CN_IDAUCTION			    		"ie0_24"
#define IPAP_CN_IDBID			    			"ie0_25"
#define IPAP_CN_IDALLOCATION					"ie0_26"
#define IPAP_CN_STARTSECONDS             		"ie0_27"
#define IPAP_CN_ENDSECONDS               		"ie0_28"
#define IPAP_CN_STARTMILLISECONDS        		"ie0_29"
#define IPAP_CN_ENDMILLISECONDS          		"ie0_30"
 
 
 
#endif // IPAP_DEF_H
