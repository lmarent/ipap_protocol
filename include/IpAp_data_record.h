/*! \file   IpAp_data_record.h

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

    $Id: IpAp_data_record.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_DATA_RECORD_H
#define IPAP_DATA_RECORD_H

#include "stdincpp.h"
#include "IpAp_field_key.h"
#include "IpAp_value_field.h"
#include "IpAp_exception.h"


typedef map<ipap_field_key, ipap_value_field > fieldDataList_t;
typedef map<ipap_field_key, ipap_value_field >::iterator fieldDataListIter_t;
typedef map<ipap_field_key, ipap_value_field >::const_iterator fieldDataListConstIter_t;
 

class ipap_data_record
{ 

private:
    
    ///! template id which is associated with this data record.
    uint16_t template_id;
 
    ///! Data value map for every field 
    fieldDataList_t fields;  														
            

public:
        
    /** 
     * Creates a data_record
     */
    ipap_data_record(uint16_t _template_id);
    
    /** 
     * Contructor of the class, it copies from another data record.
     */
    ipap_data_record(const ipap_data_record &param);
    
    ~ipap_data_record();
    
    inline uint16_t get_template_id(){ return template_id; }
    
    /**
     *  Insert a field value based on components of the field key (eno,ftype).
     */
    void insert_field(int eno, int ftype, ipap_value_field &value);
    
    /**
     *  Insert a field value based on components of the field key (eno,ftype).
     */
    void insert_field(int eno, int ftype, ipap_value_field *value);
    
    /** 
     * Insert a field value based on the field key (param).
     */
    void insert_field(ipap_field_key &param, ipap_value_field &value);
        
    /** 
     * Return the number of fields with a value
     */
    int get_num_fields();
        
    /** 
     * Return the field value based on components of the field key
     */
    ipap_value_field get_field(int eno, int ftype);

    /** 
     * Return the field value based on components of the field key
     */
    ipap_value_field * get_field_pointer(int eno, int ftype);

    /** 
     * Return the field value based on components of the field key
     */
    ipap_value_field get_field(int eno, int ftype) const;


    /** 
     * Return the field value based on the field key
     */
    ipap_value_field get_field(ipap_field_key &param);

    /** 
     * Return the field value based on the field key
     */
    ipap_value_field get_field(const ipap_field_key &param) const;
    
    /** 
     * Return the length on bytes of the value based on components of the field key
     */
    uint16_t get_length(int eno, int ftype);

    /** 
     * Return the length on bytes of the value based on the field key
     */
    uint16_t get_length(ipap_field_key &param);
    
    /** 
     * delete all fields values inserted
     */
    void clear();
    
    /** 
     * Create an string representing all field values.
     */
    std::string to_string();
    
    /**
     *  Equals to operator. 
     *  It is equal when it has the same amount of field values and every value is equal.
     */
    bool operator== (const ipap_data_record& rhs) const;
    
    /** 
     * Assignment operator. 
    */ 
    ipap_data_record& operator= (const ipap_data_record&);
    
    /** 
    * Not equal to operator. 
    */ 
    bool operator != (const ipap_data_record &rhs) const;
    
    fieldDataListIter_t begin();
    
    fieldDataListIter_t end();
    
};


#endif // IPAP_DATA_RECORD_H
