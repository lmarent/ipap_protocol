/*! \file   IpAp_reserve_fields.h

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
    reverse field vector declarations of ipap protocol

    $Id: IpAp_reserve_fields.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_RESERVE_FIELD_H
#define IPAP_RESERVE_FIELD_H

/* 
 * ipap reverse information element list
 */
 
ipap_field_type_t ipap_reverse_field_types[] = {
   { REV_PEN, IPAP_FT_MAXUNITVALUATION, 8, IPAP_CODING_FLOAT, 
     "Reverse auctionMaxUnitValuation", "" }, 
   { REV_PEN, IPAP_FT_UNITVALUE, 8, IPAP_CODING_FLOAT, 
     "Reverse auctionUnitValue", "" }, 
   { REV_PEN, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_FLOAT, 
     "Reverse auctionUnitBudget", "" }, 
   { REV_PEN, IPAP_FT_TOTALBUDGET, 8, IPAP_CODING_FLOAT, 
     "Reverse auctionTotalBudget", "" }, 
   { REV_PEN, IPAP_FT_AUCTIONINGTIMESECONDS, 4, IPFIX_CODING_UINT, 
     "Reverse auctionTimeSeconds", "" }, 
   { REV_PEN, IPAP_FT_AUCTIONINGTIMEMILLISECONDS, 8, IPFIX_CODING_UINT, 
     "Reverse auctionTimeMilliseconds", "" }, 
   { REV_PEN, IPAP_FT_AUCTIONINGTIMEMICROSECONDS, 8, IPFIX_CODING_NTP, 
     "Reverse auctionTimeMicroseconds", "" }, 
   { REV_PEN, IPAP_FT_AUCTIONINGTIMENANOSECONDS, 8, IPFIX_CODING_NTP, 
     "Reverse auctionTimeNanoseconds", "" }, 
   { REV_PEN, IPAP_FT_AUCTIONINGALGORITHM, 2, IPFIX_CODING_UINT, 
     "Reverse auctioning Algorithm", "" }, 
   { REV_PEN, IPAP_FT_SOURCEIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "Reverse sourceIPv4Address", "" }, 
   { REV_PEN, IPAP_FT_SOURCEIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "Reverse sourceIPv4PrefixLength", "" }, 
   { REV_PEN, IPAP_FT_DESTINATIONIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "Reverse destinationIPv4Address", "" },
   { REV_PEN, IPAP_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "Reverse destinationIPv4PrefixLength", "" },      
   { REV_PEN, IPAP_FT_SOURCEIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "Reverse sourceIPv6Address", "" }, 
   { REV_PEN, IPAP_FT_DESTINATIONIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "Reverse destinationIPv6Address", "" }, 
   { REV_PEN, IPAP_FT_SOURCEIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "Reverse sourceIPv6PrefixLength", "" }, 
   { REV_PEN, IPAP_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "Reverse destinationIPv6PrefixLength", "" }, 
   { REV_PEN, IPAP_FT_PADDINGOCTETS, 65535, IPAP_CODING_BYTES, 
     "Reverse paddingOctets", "" },      
   { REV_PEN, IPAP_FT_IPHEADERPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "Reverse ipHeaderPacketSection", "" }, 
   { REV_PEN, IPAP_FT_IPPAYLOADPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "Reverse ipPayloadPacketSection", "" }, 
   { REV_PEN, IPAP_FT_DATALINKFRAMESECTION, 65535, IPAP_CODING_BYTES, 
     "Reverse dataLinkFrameSection", "" },   
   { REV_PEN, IPAP_FT_SOURCEMACADDRESS, 6, IPAP_CODING_BYTES, 
     "Reverse sourceMacAddress", "" }, 
   { REV_PEN, IPAP_FT_POSTDESTINATIONMACADDRESS, 6, IPAP_CODING_BYTES, 
     "Reverse postDestinationMacAddress", "" },
   { REV_PEN, 0, -1, 0, NULL, NULL, }
};


#endif // IPAP_RESERVE_FIELD_H
