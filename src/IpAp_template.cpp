/*! \file   IpAp_template.cpp

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
    template class of ipap protocol

    $Id: IpAp_template.cpp 748 2015-08-27 14:18:00Z amarentes $
*/

#include "IpAp_template.h"
#include "IpAp_exception.h"
#include "IpAp_create_map.h"

const char *ipap_template::TEMPLATE_XML_TAGS[] = { "AUCTION", 
											"ELEMENT",
											"ALLOCATION",
											"ACTION",
											"AUCTION",
											"TO_DEFINE" };

templateKeyList_t ipap_template::templateKeys;
templateKeyList_t ipap_template::templateMandatoryFields;

ipap_template::ipap_template(const ipap_template &rhs)
{
	type = rhs.type;
	tsend = rhs.tsend;
	tid = rhs.tid;
	maxfields = rhs.maxfields;
	
	templateFieldConstIterList_t it;
	for( it = rhs.datafields.begin(); it != rhs.datafields.end(); ++it)
	{
		ipap_template_field_t ftmp;
		ftmp.flength = it->flength;
		ftmp.unknown_f = it->unknown_f;
		ftmp.relay_f = it->relay_f;
		ftmp.elem = it->elem;
		datafields.push_back(ftmp);
	}
	
}

ipap_template_field_t ipap_template::get_field(int i)
{
	if ( (i >= get_numfields()) || (i < 0) ){
		throw ipap_bad_argument("Invalid field number");
	}
	else
	{				
		return datafields[i];
	}
}

void
ipap_template::remove_unknown_fields()
{
	// Delete unknown datafields
	templateFieldIterList_t iter;
	for (iter = datafields.begin(); iter != datafields.end(); ) {
		if ((*iter).unknown_f == UNKNOWN )
			iter = datafields.erase(iter);
		else
			++iter;
	}	
}

/** Add a  data Field
 *  
*/
void ipap_template::add_field(uint16_t _flength, 
                              ipap_unknown_field_t _unknown_f, 
						      int _relay_f,
							  ipap_field  &_field)
{
	ipap_template_field_t t;
	
	t.flength = _flength;
	t.unknown_f = _unknown_f;
	t.relay_f = _relay_f;
	t.elem = _field;
			
	datafields.push_back(t);
}

bool
ipap_template::operator== (const ipap_template& rhs)
{
	
	if (rhs.type != type)
		return false;
		
	if (rhs.tid != tid)	
		return false;
	
	if (rhs.maxfields != maxfields)	
		return false;
		
	try
	{
		for (int i = 0; i < datafields.size(); i++){
			ipap_template_field_t lfs_item = datafields[i];
			ipap_template_field_t rhs_item = rhs.datafields[i];
			
			if ( ( lfs_item.flength != rhs_item.flength) ||
				 ( lfs_item.unknown_f != rhs_item.unknown_f) ||
				 ( lfs_item.relay_f != rhs_item.relay_f) ||
				 ( lfs_item.elem != rhs_item.elem )){
				return false;
			}
		}
								
		return true;
	
	}
	catch(const std::out_of_range& oor)
	{
		return false;
	}
}

bool
ipap_template::operator!= (const ipap_template& rhs)
{
	return !(operator==(rhs));
}

ipap_template& 
ipap_template::operator=(const ipap_template &rhs)
{
	type = rhs.type;
	tsend = rhs.tsend;
	tid = rhs.tid;
	maxfields = rhs.maxfields;

	templateFieldConstIterList_t it;
	for( it = rhs.datafields.begin(); it != rhs.datafields.end(); ++it){
		ipap_template_field_t ftmp;
		ftmp.flength = it->flength;
		ftmp.unknown_f = it->unknown_f;
		ftmp.relay_f = it->relay_f;
		ftmp.elem = it->elem;
		datafields.push_back(ftmp);
	}
	
	return *this;
}

ipap_template *
ipap_template::copy(void) const
{	
	ipap_template *q = NULL;
	q = new ipap_template(*this);
	return q;
}

/* name:       get_field()
 * parameters: eno, ftype
 * return:     field from the container list or NULL
 */
ipap_field 
ipap_template::get_field( int eno, int type )
{
 
	templateFieldIterList_t it;
	for ( it = datafields.begin(); it != datafields.end(); ++it)
	{
        if( (((it->elem).get_field_type()).ftype == type) && (((it->elem).get_field_type()).eno==eno) )
			return it->elem;
	}
    throw Error("IpapTemplate: Field not found in the container eno:%d  ftype:%d", eno, type);
}

set<ipap_field_key> 
ipap_template::getTemplateTypeKeys(ipap_templ_type_t templType)
{
	// Fill template keys.
	if (ipap_template::templateKeys.size() == 0 ){
		
		// Fill auction keys 
		set<ipap_field_key> auc_field_keys;
		auc_field_keys.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		auc_field_keys.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		
		// Fill bid keys
		set<ipap_field_key> bid_field_keys;
		bid_field_keys.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		bid_field_keys.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		bid_field_keys.insert(ipap_field_key(0,IPAP_FT_IDBID));
		
		// Fill allocation keys
		set<ipap_field_key> all_field_keys;
		all_field_keys.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		all_field_keys.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		all_field_keys.insert(ipap_field_key(0,IPAP_FT_IDBID));
		all_field_keys.insert(ipap_field_key(0,IPAP_FT_IDALLOCATION));
		
		ipap_template::templateKeys = ipap_create_map<ipap_templ_type_t, set<ipap_field_key> >
				(IPAP_SETID_AUCTION_TEMPLATE,auc_field_keys)
				(IPAP_OPTNS_AUCTION_TEMPLATE,auc_field_keys)
				(IPAP_SETID_BID_TEMPLATE,bid_field_keys)
				(IPAP_OPTNS_BID_TEMPLATE,bid_field_keys)
				(IPAP_SETID_ALLOCATION_TEMPLATE,all_field_keys)
				(IPAP_OPTNS_ALLOCATION_TEMPLATE,all_field_keys);
	}
	
	templateKeyIterList_t iter;
	iter = ipap_template::templateKeys.find(templType);
	return iter->second;
}


set<ipap_field_key> 
ipap_template::getTemplateTypeMandatoryFields(ipap_templ_type_t templType)
{
	// Fill template keys.
	if (ipap_template::templateMandatoryFields.size() == 0 ){
		
		// Fill data auctions fields
		set<ipap_field_key> d_auc_fields;
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_IPVERSION));
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONIPV4ADDRESS));
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONIPV6ADDRESS));
		d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONAUCTIONPORT));
		
		
		// Fill option auctions fields
		set<ipap_field_key> o_auc_fields;
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_STARTSECONDS));
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_ENDSECONDS));
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_INTERVALSECONDS));
		o_auc_fields.insert(ipap_field_key(0,IPAP_FT_AUCTIONINGALGORITHMNAME));		
		
		// Fill data bid fields
		set<ipap_field_key> d_bid_fields;
		d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDBID));
		
		// Fill option bid fields
		set<ipap_field_key> o_bid_fields;
		o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDBID));
		o_bid_fields.insert(ipap_field_key(0,IPAP_FT_STARTSECONDS));
		o_bid_fields.insert(ipap_field_key(0,IPAP_FT_ENDSECONDS));
		
		
		// Fill data allocation fields
		set<ipap_field_key> d_all_fields;
		d_all_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		d_all_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		d_all_fields.insert(ipap_field_key(0,IPAP_FT_IDBID));
		d_all_fields.insert(ipap_field_key(0,IPAP_FT_IDALLOCATION));
		
		// Fill option allocation fields
		set<ipap_field_key> o_all_fields;
		o_all_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
		o_all_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
		o_all_fields.insert(ipap_field_key(0,IPAP_FT_IDBID));
		o_all_fields.insert(ipap_field_key(0,IPAP_FT_IDALLOCATION));
		
		
		ipap_template::templateMandatoryFields = ipap_create_map<ipap_templ_type_t, set<ipap_field_key> >
				(IPAP_SETID_AUCTION_TEMPLATE,d_auc_fields)
				(IPAP_OPTNS_AUCTION_TEMPLATE,o_auc_fields)
				(IPAP_SETID_BID_TEMPLATE,d_bid_fields)
				(IPAP_OPTNS_BID_TEMPLATE,o_bid_fields)
				(IPAP_SETID_ALLOCATION_TEMPLATE,d_all_fields)
				(IPAP_OPTNS_ALLOCATION_TEMPLATE,o_all_fields);
	}
	
	templateKeyIterList_t iter;
	iter = ipap_template::templateMandatoryFields.find(templType);
	return iter->second;
}
