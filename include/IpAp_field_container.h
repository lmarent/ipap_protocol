/*! \file   IpAp_field_container.h

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

    $Id: IpAp_field_container.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_FIELD_CONTAINER_H
#define IPAP_FIELD_CONTAINER_H


/**
 * \class ipap_field_container
 *
 *
 * \brief This class is used to maintain all the fields that are possible to exchange
 * 
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2014/12/18 9:57:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */

#include "stdincpp.h"
#include "IpAp_field.h"

 
typedef vector<ipap_field> 					fieldList_t;	///< The field list 	 
typedef vector<ipap_field>::iterator 		fieldListIter_t;	///< The field list Iterator
typedef vector<ipap_field>::const_iterator  fieldListConstIter_t;	///< The field list Const Iterator 
 
class ipap_field_container
{
private:

    fieldList_t fieldList;	///< The field list 				  
    
public:
    /**
     * Contructor method.
     */ 
    ipap_field_container();
    
    /**
     * Destructor method.
     */ 
    ~ipap_field_container();

    /**
     * Insert all fields in the forward direction
     */ 
    void initialize_forward(void);
    
    /**
     * Insert all fields in the reverse direction
     */ 
    void initialize_reverse(void);
    
    /**
     * Get a field by its keys
     * @throw ipap_bad_argument - Field not found in the container
     */ 
    ipap_field get_field( int eno, int type );
        

    /**
     * Get the pointer of a field by its keys
     * @throw ipap_bad_argument - Field not found in the container
     */ 
    ipap_field* get_field_pointer( int eno, int type );
    
    
    /**
     * Add a field into the listby given the field type
     * @throw ipap_bad_argument - Field already exists in the container
     */ 
    void AddFieldType(ipap_field_type_t &param);

    /**
     * Add a field into the list by given the field type attributes
     * @throw ipap_bad_argument - Field already exists in the container
     */ 
    void AddFieldType(int _eno, int _ftype, ssize_t _length, 
                      int _coding, 
                      const std::string _name, 
                      const std::string _xml_name, 
                      const std::string _documentation );

    /**
     * Return the number of fields in the container
     */ 
    int get_num_fields(void);
    
    /**
     * Erase all fields in the container. This will destroy all fields inside.
     */ 
    inline void clear(void){ fieldList.clear(); }
    
};

inline int ipap_field_container::get_num_fields(void)
{
    return fieldList.size();
}

#endif // IPAP_FIELD_CONTAINER_H
