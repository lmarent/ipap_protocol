/*! \file   IpAp_data_record.cpp

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
    data values within a record

    $Id: IpAp_data_record.cpp 748 2015-08-27 14:42:00Z amarentes $
*/

#include "IpAp_data_record.h"



ipap_data_record::ipap_data_record(uint16_t _template_id):
template_id(_template_id)
{

}

ipap_data_record::ipap_data_record(const ipap_data_record &param)
{

    template_id = param.template_id;

    fieldDataListConstIter_t iter;
    for (iter = param.fields.begin(); iter != param.fields.end(); ++iter) {
        ipap_field_key key = iter->first;
        ipap_value_field value = iter->second;
        fields[key] = value;
    }	
    
}

ipap_data_record::~ipap_data_record()
{

}

void 
ipap_data_record::insert_field(int eno, int ftype, 
                               ipap_value_field &value)
{
    ipap_field_key key = ipap_field_key(eno, ftype);	
    insert_field(key, value);

}

void 
ipap_data_record::insert_field(int eno, int ftype, 
                               ipap_value_field *value)
{
    ipap_field_key key = ipap_field_key(eno, ftype);	
    insert_field(key, *value);

}

void 
ipap_data_record::insert_field(ipap_field_key &param, 
                               ipap_value_field &value)
{
    fields.insert( std::pair<ipap_field_key, ipap_value_field>(param,value) );
}


int 
ipap_data_record::get_num_fields()
{
    return fields.size();
}


ipap_value_field 
ipap_data_record::get_field(ipap_field_key &param)
{
    
    fieldDataListIter_t it;
    it = fields.find(param);
    if (it == fields.end()){
        throw ipap_bad_argument("Parameter field was not found");
    }
    else{
        return it->second;
    }
}

ipap_value_field 
ipap_data_record::get_field(const ipap_field_key &param) const
{
    
    fieldDataListConstIter_t it;
    it = fields.find(param);
    if (it == fields.end()){
        throw ipap_bad_argument("Parameter field was not found");
    }
    else{
        return it->second;
    }
}

ipap_value_field 
ipap_data_record::get_field(int eno, int ftype)
{
    ipap_field_key key = ipap_field_key(eno, ftype);
    return get_field(key);
}


ipap_value_field 
ipap_data_record::get_field(int eno, int ftype) const
{
    const ipap_field_key key = ipap_field_key(eno, ftype);
    return get_field(key);
}

ipap_value_field*
ipap_data_record::get_field_pointer(int eno, int ftype)
{
    ipap_field_key key = ipap_field_key(eno, ftype);
    fieldDataListIter_t it;
    it = fields.find(key);
    if (it == fields.end()){
        throw ipap_bad_argument("Parameter field was not found");
    }
    else{
        return &(it->second);
    }
}


uint16_t 
ipap_data_record::get_length(ipap_field_key &param)
{
    ipap_value_field fieldvalue = get_field(param);
    uint16_t len = (uint16_t) fieldvalue.get_length();
    
    return fieldvalue.get_length();
}

uint16_t 
ipap_data_record::get_length(int eno, int ftype)
{
    ipap_field_key key = ipap_field_key(eno, ftype);
    return get_length(key);
}

void 
ipap_data_record::clear()
{
    // free the memory assigned to data values.	
    fields.clear();
}

std::string 
ipap_data_record::to_string()
{
    std::map<ipap_field_key, ipap_value_field>::iterator iter;
    std::string strToReturn;
    
    for (iter = fields.begin(); iter != fields.end(); ++iter) 
    {
         ipap_field_key temp = iter->first;
         strToReturn.append(temp.to_string()); 
         strToReturn.append("=");
         strToReturn.append((iter->second).to_string());
    }
    return strToReturn;
}

bool 
ipap_data_record::operator== (const ipap_data_record& rhs) const
{

    fieldDataListConstIter_t iter;
    for (iter = fields.begin(); iter != fields.end(); ++iter) {
        ipap_field_key key = iter->first;
        const ipap_value_field tmp = rhs.get_field(key);
        const ipap_value_field tmp2 = iter->second;
        if (tmp != tmp2){
            return false;
        }
    }
    return true;
}


ipap_data_record& 
ipap_data_record::operator= (const ipap_data_record& rhs)
{
    // Delete all field values in the container.
    fields.clear();
    
    template_id = rhs.template_id;

    fieldDataListConstIter_t iter;
    for (iter = rhs.fields.begin(); iter != rhs.fields.end(); ++iter) {
        ipap_field_key key = iter->first;
        ipap_value_field value = iter->second;
        fields[key] = value;
    }	
    return *this;

}

bool 
ipap_data_record::operator!= (const ipap_data_record& rhs) const
{

    fieldDataListConstIter_t iter;
    for (iter = fields.begin(); iter != fields.end(); ++iter) {
        ipap_field_key key = iter->first;
        ipap_value_field tmp = rhs.get_field(key);
        ipap_value_field tmp2 = iter->second;
        if (tmp != tmp2){
            return true;
        }
    }
    return false;
}

fieldDataListIter_t 
ipap_data_record::begin(void) 
{
    return fields.begin();
}

fieldDataListIter_t 
ipap_data_record::end(void) 
{
    return fields.end();
}
