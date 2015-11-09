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
										const std::string _xml_name,
										const std::string _documentation)
{
	ipap_field_type_t newType;
	newType.eno = _eno;
	newType.ftype = _ftype;
	newType.length = _length;
	newType.coding = _coding;
	newType.name = _name;
	newType.xml_name = _xml_name;
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

   AddFieldType( 0, IPAP_FT_MAXUNITVALUATION, 8, IPAP_CODING_DOUBLE, 
     "auctionMaxUnitValuation", "MaxUnitValuation", "" );
   AddFieldType( 0, IPAP_FT_UNITVALUE, 8, IPAP_CODING_DOUBLE, 
     "auctionUnitValue", "UnitValue", "" );
   AddFieldType( 0, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_DOUBLE, 
     "auctionUnitBudget", "UnitBudget", "" );
   AddFieldType( 0, IPAP_FT_TOTALBUDGET, 8, IPAP_CODING_DOUBLE, 
     "auctionTotalBudget", "TotalBudget", "" );     
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "auctionTimeSeconds", "AuctioningTimeSeconds", "" ); 
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "auctionTimeMilliseconds", "AuctioningTimeMilliSeconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "auctionTimeMicroseconds", "AuctioningTimeMicroSeconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "auctionTimeNanoseconds", "AuctioningTimeNanoSeconds", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGALGORITHMCODE, 4, IPAP_CODING_UINT, 
     "auctioningAlgorithmCode", "AuctioningAlgorithmCode", "" );   
   AddFieldType( 0, IPAP_FT_SOURCEIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "sourceIPv4Address", "SourceIpv4Address", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "sourceIPv4PrefixLength", "SourceIpv4PrefixLenght", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "destinationIPv4Address", "DestinationIpv4Address", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "destinationIPv4PrefixLength", "DestinationIpv4PrefixLen", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "sourceIPv6Address", "SourceIpv6Address", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "destinationIPv6Address", "DestinationIpv6Address", "" );
   AddFieldType( 0, IPAP_FT_SOURCEIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "sourceIPv6PrefixLength", "SourceIpv6PrefixLenght", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "destinationIPv6PrefixLength", "DestinationIpv6PrefixLenght", "" );
   AddFieldType( 0, IPAP_FT_PADDINGOCTETS, 65535, IPAP_CODING_BYTES, 
     "paddingOctets", "PaddingOctects", "" );
   AddFieldType( 0, IPAP_FT_IPHEADERPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ipHeaderPacketSection", "IpHeaderPacketSection", "" );
   AddFieldType( 0, IPAP_FT_IPPAYLOADPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "ipPayloadPacketSection", "IpPayloadPacketSection", "" );
   AddFieldType( 0, IPAP_FT_DATALINKFRAMESECTION, 65535, IPAP_CODING_BYTES, 
     "dataLinkFrameSection", "DataLinkFrameSection", "" );
   AddFieldType( 0, IPAP_FT_SOURCEMACADDRESS, 6, IPAP_CODING_BYTES, 
     "sourceMacAddress", "SourceMacAddress", "" );
   AddFieldType( 0, IPAP_FT_POSTDESTINATIONMACADDRESS, 6, IPAP_CODING_BYTES, 
     "postDestinationMacAddress", "PostDestinationMacAddress", "" );
   AddFieldType( 0, IPAP_FT_IDAUCTION, 65535, IPAP_CODING_STRING, 
     "idAuction", "IdAuction", "" );
   AddFieldType( 0, IPAP_FT_IDBIDDINGOBJECT, 65535, IPAP_CODING_STRING, 
     "idBiddingObject", "IdBidingObject", "" );
   AddFieldType( 0, IPAP_FT_BIDDINGOBJECTTYPE, 1, IPAP_CODING_UINT, 
     "biddingObjectType", "biddingObjectType", "" );
   AddFieldType( 0, IPAP_FT_STARTSECONDS, 8, IPAP_CODING_UINT, 
     "startSeconds", "StartSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_ENDSECONDS, 8, IPAP_CODING_UINT, 
     "endSeconds", "EndSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_STARTMILLISECONDS, 8, IPAP_CODING_UINT, 
     "startMilliSeconds", "StartMilliSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_ENDMILLISECONDS, 8, IPAP_CODING_UINT, 
     "endMilliSeconds", "EndMilliSeconds", "" ),      
   AddFieldType( 0, IPAP_FT_AUCTIONINGALGORITHMNAME, 65535, IPAP_CODING_STRING, 
     "auctioningAlgorithmName", "AuctioningAlgorithName", "" ),
   AddFieldType( 0, IPAP_FT_IDRECORD, 65535, IPAP_CODING_STRING, 
     "idRecord", "IdRecord", "" ),
   AddFieldType( 0, IPAP_FT_QUANTITY, 4, IPAP_CODING_FLOAT, 
     "quantity", "Quantity", "" ),
   AddFieldType( 0, IPAP_FT_INTERVALSECONDS, 8, IPAP_CODING_UINT, 
     "intervalSeconds", "IntervalsSeconds", "" ),
   AddFieldType( 0, IPAP_FT_INTERVALMILLISECONDS, 8, IPAP_CODING_UINT, 
     "intervalMilliSeconds", "IntervalsMilliSeconds", "" ),
   AddFieldType( 0, IPAP_FT_INTERVALMICROSECONDS, 8, IPAP_CODING_NTP, 
     "intervalMicroSeconds", "IntervalsMicroSeconds", "" ),
   AddFieldType( 0, IPAP_FT_INTERVALNANOSECONDS, 8, IPAP_CODING_NTP, 
     "intervalNanoSeconds", "IntervalsNanoSeconds", "" ),
   AddFieldType( 0, IPAP_FT_POSTOCTETTOTALCOUNT, 4, IPAP_CODING_FLOAT, 
     "postOctetTotalCount", "PostOctetTotalCount", "" ),
   AddFieldType( 0, IPAP_FT_RESERVEPRICE, 8, IPAP_CODING_DOUBLE, 
     "reservePrice", "ReservePrice", "" ),
   AddFieldType( 0, IPAP_FT_IDRESOURCE, 65535, IPAP_CODING_STRING, 
     "idResource", "IdResource", "" ),
   AddFieldType( 0, IPAP_FT_SOURCETRANSPORTPORT, 2, IPAP_CODING_UINT, 
     "sourceTransportPort", "SourceTransportPort", "" ),
   AddFieldType( 0, IPAP_FT_DESTINATIONTRANSPORTPORT, 2, IPAP_CODING_UINT, 
     "destinationTransportPort", "destinationTransportPort", "" ),
   AddFieldType( 0, IPAP_FT_BIDINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "bidingTimeSeconds", "BidingTimeSeconds", "" ); 
   AddFieldType( 0, IPAP_FT_BIDINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "bidingTimeMilliseconds", "BidingTimeMilliSeconds", "" );
   AddFieldType( 0, IPAP_FT_BIDINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "bidingTimeMicroseconds", "BidingTimeMicroSeconds", "" );
   AddFieldType( 0, IPAP_FT_BIDINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "bidingTimeNanoseconds", "BidingTimeNanoSeconds", "" );
   AddFieldType( 0, IPAP_FT_SOURCEAUCTIONPORT, 2, IPAP_CODING_UINT, 
     "sourceAuctionPort", "SourceAuctionPort", "" );
   AddFieldType( 0, IPAP_FT_DESTINATIONAUCTIONPORT, 2, IPAP_CODING_UINT, 
     "destinationAuctionPort", "DestinationAuctionPort", "" );
   AddFieldType( 0, IPAP_FT_IPVERSION, 1, IPAP_CODING_UINT, 
     "ipVersion", "ipVersion", "" );
   AddFieldType( 0, IPAP_FT_AUCTIONINGOBJECTSTATUS, 2, IPAP_CODING_UINT, 
     "auctioningObjectStatus", "auctioningObjectStatus", "" );
   AddFieldType( 0, IPAP_FT_TEMPLATES, 65535, IPAP_CODING_STRING, 
     "commaSeparatedlistOfTemplates", "commaSeparatedlistOfTemplates", "" );
     

   AddFieldType( 0, 0, -1, 0, "", "", "" );

}

void ipap_field_container::initialize_reverse(void)
{

   AddFieldType( REV_PEN, IPAP_FT_MAXUNITVALUATION, 8, IPAP_CODING_DOUBLE, 
     "reverseAuctionMaxUnitValuation", "MaxUnitValuation", "" );
   AddFieldType( REV_PEN, IPAP_FT_UNITVALUE, 8, IPAP_CODING_DOUBLE, 
     "reverseAuctionUnitValue", "UnitValue", "" );
   AddFieldType( REV_PEN, IPAP_FT_UNITBUDGET, 8, IPAP_CODING_DOUBLE, 
     "reverseAuctionUnitBudget", "UnitBudget", "" );
   AddFieldType( REV_PEN, IPAP_FT_TOTALBUDGET, 8, IPAP_CODING_DOUBLE, 
     "reverseAuctionTotalBudget", "TotalBudget", "" );     
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "reverseAuctionTimeSeconds", "AuctioningTimeSeconds", "" ); 
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "reverseAuctionTimeMilliseconds", "AuctioningTimeMilliSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "reverseAuctionTimeMicroseconds", "AuctioningTimeMicroSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "reverseAuctionTimeNanoseconds", "AuctioningTimeNanoSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGALGORITHMCODE, 4, IPAP_CODING_UINT, 
     "reverseAuctioningAlgorithmCode", "AuctioningAlgorithmCode", "" );   
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "reverseSourceIPv4Address", "SourceIpv4Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "reverseSourceIPv4PrefixLength", "SourceIpv4PrefixLenght", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV4ADDRESS, 4, IPAP_CODING_IPADDR, 
     "reverseDestinationIPv4Address", "DestinationIpv4Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "reverseDestinationIPv4PrefixLength", "DestinationIpv4PrefixLen", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "reverseSourceIPv6Address", "SourceIpv6Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV6ADDRESS, 16, IPAP_CODING_IPADDR, 
     "reverseDestinationIPv6Address", "DestinationIpv6Address", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "reverseSourceIPv6PrefixLength", "SourceIpv6PrefixLenght", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPAP_CODING_UINT, 
     "reverseDestinationIPv6PrefixLength", "DestinationIpv6PrefixLenght", "" );
   AddFieldType( REV_PEN, IPAP_FT_PADDINGOCTETS, 65535, IPAP_CODING_BYTES, 
     "reversePaddingOctets", "PaddingOctects", "" );
   AddFieldType( REV_PEN, IPAP_FT_IPHEADERPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "reverseIpHeaderPacketSection", "IpHeaderPacketSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_IPPAYLOADPACKETSECTION, 65535, IPAP_CODING_BYTES, 
     "reverseIpPayloadPacketSection", "IpPayloadPacketSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_DATALINKFRAMESECTION, 65535, IPAP_CODING_BYTES, 
     "reverseDataLinkFrameSection", "DataLinkFrameSection", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEMACADDRESS, 6, IPAP_CODING_BYTES, 
     "reverseSourceMacAddress", "SourceMacAddress", "" );
   AddFieldType( REV_PEN, IPAP_FT_POSTDESTINATIONMACADDRESS, 6, IPAP_CODING_BYTES, 
     "reversePostDestinationMacAddress", "PostDestinationMacAddress", "" );
   AddFieldType( REV_PEN, IPAP_FT_IDAUCTION, 65535, IPAP_CODING_STRING, 
     "reverseIdAuction", "IdAuction", "" );
   AddFieldType( REV_PEN, IPAP_FT_IDBIDDINGOBJECT, 65535, IPAP_CODING_STRING, 
     "reverseIdBiddingObject", "IdBiddingObject", "" );
   AddFieldType( REV_PEN, IPAP_FT_BIDDINGOBJECTTYPE, 1, IPAP_CODING_UINT, 
     "reverseBiddingObjectType", "BiddingObjectType", "" );
   AddFieldType( REV_PEN, IPAP_FT_STARTSECONDS, 8, IPAP_CODING_UINT, 
     "reverseStartSeconds", "StartSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_ENDSECONDS, 8, IPAP_CODING_UINT, 
     "reverseEndSeconds", "EndSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_STARTMILLISECONDS, 8, IPAP_CODING_UINT, 
     "reverseStartMilliSeconds", "StartMilliSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_ENDMILLISECONDS, 8, IPAP_CODING_UINT, 
     "reverseEndMilliSeconds", "EndMilliSeconds", "" ),      
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGALGORITHMNAME, 65535, IPAP_CODING_STRING, 
     "reverseAuctioningAlgorithmName", "AuctioningAlgorithName", "" ),
   AddFieldType( REV_PEN, IPAP_FT_IDRECORD, 65535, IPAP_CODING_STRING, 
     "reverseIdRecord", "IdRecord", "" ),
   AddFieldType( REV_PEN, IPAP_FT_QUANTITY, 4, IPAP_CODING_FLOAT, 
     "reverseQuantity", "Quantity", "" ),
   AddFieldType( REV_PEN, IPAP_FT_INTERVALSECONDS, 8, IPAP_CODING_UINT, 
     "reverseIntervalSeconds", "IntervalsSeconds", "" ),
   AddFieldType( REV_PEN, IPAP_FT_INTERVALMILLISECONDS, 8, IPAP_CODING_UINT, 
     "reverseIntervalMilliSeconds", "IntervalsMilliSeconds", "" ),
   AddFieldType( REV_PEN, IPAP_FT_INTERVALMICROSECONDS, 8, IPAP_CODING_NTP, 
     "reverseIntervalMicroSeconds", "IntervalsMicroSeconds", "" ),
   AddFieldType( REV_PEN, IPAP_FT_INTERVALNANOSECONDS, 8, IPAP_CODING_NTP, 
     "reverseIntervalNanoSeconds", "IntervalsNanoSeconds", "" ),
   AddFieldType( REV_PEN, IPAP_FT_POSTOCTETTOTALCOUNT, 4, IPAP_CODING_FLOAT, 
     "reversePostOctetTotalCount", "PostOctetTotalCount", "" ),
   AddFieldType( REV_PEN, IPAP_FT_RESERVEPRICE, 8, IPAP_CODING_DOUBLE, 
     "reverseReservePrice", "ReservePrice", "" ),
   AddFieldType( REV_PEN, IPAP_FT_IDRESOURCE, 65535, IPAP_CODING_STRING, 
     "reverseIdResource", "ReverseIdResource", "" ),
   AddFieldType( REV_PEN, IPAP_FT_SOURCETRANSPORTPORT, 2, IPAP_CODING_UINT, 
     "reverseSourceTransportPort", "ReverseSourceTransportPort", "" ),
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONTRANSPORTPORT, 2, IPAP_CODING_UINT, 
     "reverseDestinationTransportPort", "ReversedestinationTransportPort", "" ),
   AddFieldType( REV_PEN, IPAP_FT_BIDINGTIMESECONDS, 4, IPAP_CODING_UINT, 
     "reverseBidingTimeSeconds", "BidingTimeSeconds", "" ); 
   AddFieldType( REV_PEN, IPAP_FT_BIDINGTIMEMILLISECONDS, 8, IPAP_CODING_UINT, 
     "reverseBidingTimeMilliseconds", "BidingTimeMilliSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_BIDINGTIMEMICROSECONDS, 8, IPAP_CODING_NTP, 
     "reverseBidingTimeMicroseconds", "BidingTimeMicroSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_BIDINGTIMENANOSECONDS, 8, IPAP_CODING_NTP, 
     "reverseBidingTimeNanoseconds", "BidingTimeNanoSeconds", "" );
   AddFieldType( REV_PEN, IPAP_FT_SOURCEAUCTIONPORT, 2, IPAP_CODING_UINT, 
     "reverseSourceAuctionPort", "SourceAuctionPort", "" );
   AddFieldType( REV_PEN, IPAP_FT_DESTINATIONAUCTIONPORT, 2, IPAP_CODING_UINT, 
     "reverseDestinationAuctionPort", "DestinationAuctionPort", "" );
   AddFieldType( REV_PEN, IPAP_FT_IPVERSION, 1, IPAP_CODING_UINT, 
     "reverseIpVersion", "reverseIpVersion", "" );
   AddFieldType( REV_PEN, IPAP_FT_AUCTIONINGOBJECTSTATUS, 2, IPAP_CODING_UINT, 
     "revauctioningObjectStatus", "revauctioningObjectStatus", "" );
   AddFieldType( REV_PEN, IPAP_FT_TEMPLATES, 65535, IPAP_CODING_STRING, 
     "reverseCommaSeparatedlistOfTemplates", "commaSeparatedlistOfTemplates", "" );


   AddFieldType( REV_PEN, 0, -1, 0, "", "", "");

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
