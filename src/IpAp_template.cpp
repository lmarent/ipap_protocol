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

const char *ipap_object_type_names[] = { "Auction", "Bid", "Ask", "Allocation" };


templateKeyList_t ipap_template::templateKeys;
templateKeyList_t ipap_template::templateMandatoryFields;
objectTemplateList_t ipap_template::objectTemplates;
map<ipap_templ_type_t, ipap_object_type_t> ipap_template::templateObjectRel;
map<ipap_templ_subtype_t, set<ipap_templ_type_t> > ipap_template::templatesBySubtype;


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

ipap_field * 
ipap_template::get_field_by_pos(int pos)
{
    if ( (pos >= get_numfields()) || (pos < 0) ){
        throw ipap_bad_argument("Invalid field number");
    }
    else
    {
        return new ipap_field(datafields[pos].elem);
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

/** Add a  data Field
 *  
*/
void ipap_template::add_field(uint16_t _flength, 
                              ipap_unknown_field_t _unknown_f, 
                              int _relay_f,
                              ipap_field  *_field)
{
    ipap_template_field_t t;
    
    t.flength = _flength;
    t.unknown_f = _unknown_f;
    t.relay_f = _relay_f;
    t.elem = *_field;
            
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
        
        // Fill bidding object keys
        set<ipap_field_key> bid_field_keys;
        bid_field_keys.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
        bid_field_keys.insert(ipap_field_key(0,IPAP_FT_IDBIDDINGOBJECT));
                
        ipap_template::templateKeys = ipap_create_map<ipap_templ_type_t, set<ipap_field_key> >
                (IPAP_SETID_AUCTION_TEMPLATE,auc_field_keys)
                (IPAP_OPTNS_AUCTION_TEMPLATE,auc_field_keys)
                (IPAP_SETID_BID_OBJECT_TEMPLATE,bid_field_keys)
                (IPAP_OPTNS_BID_OBJECT_TEMPLATE,bid_field_keys)
                (IPAP_SETID_ASK_OBJECT_TEMPLATE,bid_field_keys)
                (IPAP_OPTNS_ASK_OBJECT_TEMPLATE,bid_field_keys)
                (IPAP_SETID_ALLOC_OBJECT_TEMPLATE,bid_field_keys)
                (IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE,bid_field_keys);
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
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_AUCTIONINGOBJECTSTATUS));		
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_IPVERSION));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONIPV4ADDRESS));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONIPV6ADDRESS));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_DESTINATIONAUCTIONPORT));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDRESOURCE));		
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_STARTSECONDS));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_ENDSECONDS));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_INTERVALSECONDS));
        d_auc_fields.insert(ipap_field_key(0,IPAP_FT_TEMPLATES));
            
        // Fill option auctions fields
        set<ipap_field_key> o_auc_fields;
        o_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
        o_auc_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
        o_auc_fields.insert(ipap_field_key(0,IPAP_FT_AUCTIONINGALGORITHMNAME));		
        
        // Fill data bid fields
        set<ipap_field_key> d_bid_fields;
        d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
        d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDBIDDINGOBJECT));
        d_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
        d_bid_fields.insert(ipap_field_key(0,IPAP_FT_AUCTIONINGOBJECTSTATUS));
        d_bid_fields.insert(ipap_field_key(0,IPAP_FT_BIDDINGOBJECTTYPE));
        
        // Fill option bid fields
        set<ipap_field_key> o_bid_fields;
        o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
        o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDBIDDINGOBJECT));
        o_bid_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
        o_bid_fields.insert(ipap_field_key(0,IPAP_FT_STARTSECONDS));
        o_bid_fields.insert(ipap_field_key(0,IPAP_FT_ENDSECONDS));

        // Fill data ask  fields
        set<ipap_field_key> d_ask_fields;
        d_ask_fields.insert(ipap_field_key(0,IPAP_FT_IDAUCTION));
        d_ask_fields.insert(ipap_field_key(0,IPAP_FT_IDBIDDINGOBJECT));
        d_ask_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
        d_ask_fields.insert(ipap_field_key(0,IPAP_FT_AUCTIONINGOBJECTSTATUS));
        d_ask_fields.insert(ipap_field_key(0,IPAP_FT_BIDDINGOBJECTTYPE));

        // Fill option ask fields
        set<ipap_field_key> o_ask_fields;
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_IDRECORD));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_STARTSECONDS));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_ENDSECONDS));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_INTERVALSECONDS));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_IDRESOURCE));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_IPVERSION));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_SOURCEIPV4ADDRESS));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_SOURCEIPV6ADDRESS));
        o_ask_fields.insert(ipap_field_key(0,IPAP_FT_SOURCEAUCTIONPORT));


        ipap_template::templateMandatoryFields = ipap_create_map<ipap_templ_type_t, set<ipap_field_key> >
                (IPAP_SETID_AUCTION_TEMPLATE,d_auc_fields)
                (IPAP_OPTNS_AUCTION_TEMPLATE,o_auc_fields)
                (IPAP_SETID_BID_OBJECT_TEMPLATE,d_bid_fields)
                (IPAP_OPTNS_BID_OBJECT_TEMPLATE,o_bid_fields)
                (IPAP_SETID_ASK_OBJECT_TEMPLATE,d_ask_fields)
                (IPAP_OPTNS_ASK_OBJECT_TEMPLATE,o_ask_fields)
                (IPAP_SETID_ALLOC_OBJECT_TEMPLATE,d_bid_fields)
                (IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE,o_bid_fields);
    }

    templateKeyIterList_t iter;
    iter = ipap_template::templateMandatoryFields.find(templType);

    if (iter == ipap_template::templateMandatoryFields.end()){
        throw ipap_bad_argument("IpAp template: type %d not valid", (int) templType);
    }

    return iter->second;
}

int 
ipap_template::getTemplateTypeMandatoryFieldSize(ipap_templ_type_t templType)
{
    set<ipap_field_key> tFields = getTemplateTypeMandatoryFields(templType);
    
    return tFields.size();
}

ipap_field_key* 
ipap_template::getTemplateTypeMandatoryFieldVector(ipap_templ_type_t templType, int index)
{
    set<ipap_field_key> tFields = getTemplateTypeMandatoryFields(templType);

    if (index >= tFields.size())
    {
        return NULL;
    } 
    else {
        std::vector<ipap_field_key> output(tFields.begin(), tFields.end()); 
        ipap_field_key* ret = new ipap_field_key(output[index]);
        return ret;
    }
}


set<ipap_templ_type_t> 
ipap_template::getObjectTemplateTypes(ipap_object_type_t objectType)
{
    // Fill object's template
    if (ipap_template::objectTemplates.size() == 0 ){
        set<ipap_templ_type_t> auc_templates;
        auc_templates.insert(IPAP_SETID_AUCTION_TEMPLATE);
        auc_templates.insert(IPAP_OPTNS_AUCTION_TEMPLATE);

        set<ipap_templ_type_t> bid_templates;
        bid_templates.insert(IPAP_SETID_BID_OBJECT_TEMPLATE);
        bid_templates.insert(IPAP_OPTNS_BID_OBJECT_TEMPLATE);

        set<ipap_templ_type_t> ask_templates;
        ask_templates.insert(IPAP_SETID_ASK_OBJECT_TEMPLATE);
        ask_templates.insert(IPAP_OPTNS_ASK_OBJECT_TEMPLATE);

        set<ipap_templ_type_t> alloc_templates;
        alloc_templates.insert(IPAP_SETID_ALLOC_OBJECT_TEMPLATE);
        alloc_templates.insert(IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE);

        ipap_template::objectTemplates = ipap_create_map<ipap_object_type_t, set<ipap_templ_type_t> >
                (IPAP_AUCTION,auc_templates)
                (IPAP_BID,bid_templates)
                (IPAP_ASK,ask_templates)
                (IPAP_ALLOCATION,alloc_templates);
    }	
    
    objectTemplateIterList_t iter;
    iter = ipap_template::objectTemplates.find(objectType);
    if (iter != ipap_template::objectTemplates.end())
        return iter->second;
    else
        throw ipap_bad_argument("IpAp template: object %d not valid", (int) objectType);
    
}

int 
ipap_template::getObjectTemplateTypesSize(ipap_object_type_t objectType)
{
    set<ipap_templ_type_t> templ_types = getObjectTemplateTypes(objectType);
    return templ_types.size();
}

ipap_templ_type_t 
ipap_template::getObjectTemplateTypesAtPos(ipap_object_type_t objectType, int index)
{
    set<ipap_templ_type_t> templ_types = getObjectTemplateTypes(objectType);

    if (index >= templ_types.size())
    {
        return IPAP_TEMPLATE_TYPE_INVALID;
    } 
    else {
        std::vector<ipap_templ_type_t> output(templ_types.begin(), templ_types.end()); 
        ipap_templ_type_t type = output[index];
        return type;
    }
}

ipap_object_type_t
ipap_template::getObjectType(ipap_templ_type_t templType)
{
    // Fill object's template
    if (ipap_template::templateObjectRel.size() == 0 ){

        ipap_template::templateObjectRel = ipap_create_map<ipap_templ_type_t, ipap_object_type_t >
                (IPAP_SETID_AUCTION_TEMPLATE, IPAP_AUCTION)
                (IPAP_OPTNS_AUCTION_TEMPLATE, IPAP_AUCTION)
                (IPAP_SETID_BID_OBJECT_TEMPLATE, IPAP_BID)
                (IPAP_OPTNS_BID_OBJECT_TEMPLATE, IPAP_BID)
                (IPAP_SETID_ASK_OBJECT_TEMPLATE, IPAP_ASK)
                (IPAP_OPTNS_ASK_OBJECT_TEMPLATE, IPAP_ASK)
                (IPAP_SETID_ALLOC_OBJECT_TEMPLATE, IPAP_ALLOCATION)
                (IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE, IPAP_ALLOCATION);
    }	
    
    map<ipap_templ_type_t, ipap_object_type_t>::iterator iter;
    iter = ipap_template::templateObjectRel.find(templType);
    if (iter != ipap_template::templateObjectRel.end())
        return iter->second;
    else
        throw ipap_bad_argument("IpAp template: type %d not valid", (int) templType);
    
}

set<ipap_templ_type_t>
ipap_template::getTemplates(ipap_templ_subtype_t subtype)
{
    // Fill subtype affiliation, if it does not exist.
    if (ipap_template::templatesBySubtype.size() == 0){
        set<ipap_templ_type_t> record;
        record.insert(IPAP_SETID_AUCTION_TEMPLATE);
        record.insert(IPAP_SETID_BID_OBJECT_TEMPLATE);
        record.insert(IPAP_SETID_ASK_OBJECT_TEMPLATE);
        record.insert(IPAP_SETID_ALLOC_OBJECT_TEMPLATE);

        set<ipap_templ_type_t> options;
        options.insert(IPAP_OPTNS_AUCTION_TEMPLATE);
        options.insert(IPAP_OPTNS_BID_OBJECT_TEMPLATE);
        options.insert(IPAP_OPTNS_ASK_OBJECT_TEMPLATE);
        options.insert(IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE);
        
        ipap_template::templatesBySubtype = ipap_create_map<ipap_templ_subtype_t, set<ipap_templ_type_t> >
                (IPAP_RECORD, record)
                (IPAP_OPTIONS, options);
    }

    map<ipap_templ_subtype_t, set<ipap_templ_type_t> >::iterator iter;
    iter = ipap_template::templatesBySubtype.find(subtype);
    if (iter != ipap_template::templatesBySubtype.end())
        return iter->second;
    else
        throw ipap_bad_argument("IpAp template: subType %d not valid", (int) subtype);
    
}


ipap_templ_type_t 
ipap_template::getTemplateType(ipap_object_type_t objectType, ipap_templ_subtype_t subtype)
{

    set<ipap_templ_type_t> templs = ipap_template::getObjectTemplateTypes(objectType);
    set<ipap_templ_type_t> subTempls = ipap_template::getTemplates(subtype);
    ipap_templ_type_t tempType;
    
    set<ipap_templ_type_t>::iterator it;
    for (it = templs.begin(); it != templs.end(); ++it){
        set<ipap_templ_type_t>::iterator it2 = subTempls.find(*it);
        if (it2 != subTempls.end()){
            return *it2;
        }
    }
    
    throw ipap_bad_argument("IpAp template: combination objectType:%d and subType %d is not valid",(int) objectType, (int) subtype);
}

