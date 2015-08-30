/*! \file   IpAp_field_container.cpp

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
    field container class of ipap protocol

    $Id: IpAp_field_container.cpp 748 2015-08-26 18:48:00Z amarentes $
*/

#include "IpAp_field_container.h"

ipap_field_container::ipap_field_container()
{

}

ipap_field_container::~ipap_field_container()
{

}
	

void ipap_field_container::AddFieldType(int _eno, int _ftype, ssize_t _length, 
										int _coding, const std::string _name, 
										const std::string _documentation)
{
	ipap_field_type_t newType;
	newType.eno = _eno;
	newType.ftype = _ftype;
	newType.length = _length;
	newType.coding = _coding;
	newType.name = _name;
	newType.documentation = _documentation;
	AddFieldType(newType);

};


void ipap_field_container::AddFieldType(ipap_field_type_t &param)
{
	ipap_field a = ipap_field(param);

	fieldListIter_t it;
	for (it = fieldList.begin() ; it != fieldList.end(); ++it)
	{
        if( *it== a )
			throw ipap_bad_argument("Field already exists in the container");
	}	
	fieldList.push_back(a);

}


void ipap_field_container::initialize_forward(void)
{

   AddFieldType( 0, IPAP_FT_MAXUNITVALUATION, 8, IPAP_CODING_FLOAT, 
     "auctionMaxUnitValuation", "" );
   AddFieldType( 0, IPAP_FT_UNITVALUE, 8, IPAP_CODING_FLOAT, 
     "auctionUnitValue", "" );
   AddFieldType( 0, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_FLOAT, 
     "auctionUnitBudget", "" );
   AddFieldType( 0, IPAP_FT_TOTALBUDGET, 8, IPAP_CODING_FLOAT, 
     "auctionTotalBudget", "" );     
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "auctionTimeSeconds", "" ); 
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "auctionTimeMilliseconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "auctionTimeMicroseconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "auctionTimeNanoseconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGALGORITHMCODE, 2, IPAP_CODING_UINT, 
     "auctioningAlgorithmCode", "" );   
   AddFieldType( 0, IPAP_FT_SOURCEIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "sourceIPv4Address", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "sourceIPv4PrefixLength", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "destinationIPv4Address", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "destinationIPv4PrefixLength", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "sourceIPv6Address", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "destinationIPv6Address", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "sourceIPv6PrefixLength", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "destinationIPv6PrefixLength", "" );
   AddFieldType( 0, IPAP_FT_PADDINGOCTETS, 65535, IPAP_CODING_BYTES, 
     "paddingOctets", "" );
   AddFieldType( 0, IPAP_FT_IPHEADERPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ipHeaderPacketSection", "" );
   AddFieldType( 0, IPAP_FT_IPPAYLOADPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ipPayloadPacketSection", "" );
   AddFieldType( 0, IPAP_FT_DATALINKFRAMESECTION, 65535, IPAP_CODING_BYTES, 
     "dataLinkFrameSection", "" );
   AddFieldType( 0, IPAP_FT_SOURCEMACADDRESS, 6, IPAP_CODING_BYTES, 
     "sourceMacAddress", "" );
   AddFieldType( 0, IPAP_FT_POSTDESTINATIONMACADDRESS, 6, IPAP_CODING_BYTES, 
     "postDestinationMacAddress", "" );
   AddFieldType( 0, IPAP_FT_IDAUCTION, 65535, IPAP_CODING_STRING, 
     "idAuction", "" );
   AddFieldType( 0, IPAP_FT_IDBID, 65535, IPAP_CODING_STRING, 
     "idBid", "" );
   AddFieldType( 0, IPAP_FT_IDALLOCATION, 65535, IPAP_CODING_STRING, 
     "idAllocation", "" );
   AddFieldType( 0, IPAP_FT_STARTSECONDS, 4, IPAP_CODING_UINT, 
     "startSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_ENDSECONDS, 4, IPAP_CODING_UINT, 
     "endSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_STARTMILLISECONDS, 8, IPAP_CODING_UINT, 
     "startMilliSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_ENDMILLISECONDS, 8, IPAP_CODING_UINT, 
     "endMilliSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_AUCTIONINGALGORITHMNAME, 65535, IPAP_CODING_STRING, 
     "auctioningAlgorithmName", "" ),

   AddFieldType( 0, 0, -1, 0, "", "" );

}

void ipap_field_container::initialize_reverse(void)
{

   AddFieldType( REV_PEN, IPAP_FT_MAXUNITVALUATION, 8, IPAP_CODING_FLOAT, 
     "ReverseAuctionMaxUnitValuation", "" ); 
   AddFieldType( REV_PEN, IPAP_FT_UNITVALUE, 8, IPAP_CODING_FLOAT, 
     "ReverseAuctionUnitValue", "" );
   AddFieldType( REV_PEN, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_FLOAT, 
     "ReverseAuctionUnitBudget", "" );
   AddFieldType( REV_PEN, IPAP_FT_TOTALBUDGET, 8, IPAP_CODING_FLOAT, 
     "ReverseAuctionTotalBudget", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "ReverseAuctionTimeSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "ReverseAuctionTimeMilliseconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "ReverseAuctionTimeMicroseconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "ReverseAuctionTimeNanoseconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGALGORITHMCODE, 2, IPAP_CODING_UINT, 
     "ReverseAuctioningAlgorithmCode", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "ReverseSourceIPv4Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "ReverseSourceIPv4PrefixLength", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "ReverseDestinationIPv4Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "ReverseDestinationIPv4PrefixLength", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "ReverseSourceIPv6Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "ReverseDestinationIPv6Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "ReverseSourceIPv6PrefixLength", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "ReverseDestinationIPv6PrefixLength", "" );
   AddFieldType( REV_PEN, IPAP_FT_PADDINGOCTETS, 65535, IPAP_CODING_BYTES, 
     "ReversePaddingOctets", "" );
   AddFieldType( REV_PEN, IPAP_FT_IPHEADERPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ReverseIpHeaderPacketSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_IPPAYLOADPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ReverseIpPayloadPacketSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_DATALINKFRAMESECTION, 65535, IPAP_CODING_BYTES, 
     "ReverseDataLinkFrameSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEMACADDRESS, 6, IPAP_CODING_BYTES, 
     "ReverseSourceMacAddress", "" );
   AddFieldType( REV_PEN, IPAP_FT_POSTDESTINATIONMACADDRESS, 6, IPAP_CODING_BYTES, 
     "ReversePostDestinationMacAddress", "" );    
   AddFieldType( REV_PEN, IPAP_FT_IDAUCTION, 65535, IPAP_CODING_STRING, 
     "ReverseIdAuction", "" );
   AddFieldType( REV_PEN, IPAP_FT_IDBID, 65535, IPAP_CODING_STRING, 
     "ReverseIdBid", "" );
   AddFieldType( REV_PEN, IPAP_FT_IDALLOCATION, 65535, IPAP_CODING_STRING, 
     "ReverseIdAllocation", "" );
   AddFieldType( REV_PEN, IPAP_FT_STARTSECONDS, 4, IPAP_CODING_UINT, 
     "ReverseStartSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_ENDSECONDS, 4, IPAP_CODING_UINT, 
     "ReverseEndSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_STARTMILLISECONDS, 8, IPAP_CODING_UINT, 
     "ReverseStartMilliSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_ENDMILLISECONDS, 8, IPAP_CODING_UINT, 
     "ReverseEndMilliSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGALGORITHMNAME, 65535, IPAP_CODING_STRING, 
     "ReverseAuctioningAlgorithmName", "" ),

   AddFieldType( REV_PEN, 0, -1, 0, "", "");

}


/* name:       get_field()
 * parameters: eno, ftype
 * return:     field from the container list or NULL
 */
ipap_field ipap_field_container::get_field( int eno, int type )
{
 
	fieldListIter_t it;
	for ( it = fieldList.begin(); it != fieldList.end(); ++it)
	{
        if( ((it->get_field_type()).ftype == type) && ((it->get_field_type()).eno==eno) )
			return *it;
	}
    throw ipap_bad_argument("Field not found in the container");
}
