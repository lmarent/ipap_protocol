/*! \file   IpAp_field_key.h

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
    field key class of ipap protocol

    $Id: ApAp_field_key.h 748 2015-08-26 18:48:00Z amarentes $
*/

#ifndef IPAP_FIELD_KEY_H
#define IPAP_FIELD_KEY_H


#include "stdincpp.h"

/**
 * \class ipap_field_key
 *
 *
 * \brief This respresents the key of a field to be exchanged.
 *
 * This class is used to represent the key of a field that is going to be exchange.
 * The class is the key used on the map of field values inside the record set class.
 *
 * \author Andres Marentes
 *
 * \version 0.1 
 *
 * \date 2015/08/26 20:39:00
 *
 * Contact: la.marentes455@uniandes.edu.co
 *  
 */
class ipap_field_key
{

private:

    int eno;  				///< enterprise number or 0 
    int ftype;              ///< field type 

public:
    
    /// Default constructor for the field key class.
    inline ipap_field_key():eno(0), ftype(0){}
    
    
    /// Constructor of the field key
    inline ipap_field_key(int _eno, int _ftype): 
            eno(_eno), ftype(_ftype){}
    
    /// Destructor of the field key
    inline ~ipap_field_key(){ }
    
    /// Sets the enterprise number
    inline void  set_eno(int _eno){eno = _eno;}
    
    /// Sets the field type
    inline void set_ftype(int _ftype){ftype = _ftype;}
    
    /// Get the enterprise number
    inline int get_eno(){ return eno; }
    
    /// Get the field type
    inline int get_ftype(){ return ftype; }

    /// Get the enterprise number
    inline int get_eno() const { return eno; }
    
    /// Get the field type
    inline int get_ftype() const { return ftype; }
        
    /**
     *  Equals to operator. It is equal when it has the same enterprise number an type
     */
    inline bool operator ==(const ipap_field_key &rhs) const
    { 
        return ((eno == rhs.eno) && (ftype == rhs.ftype)); 
    }

    /** less operator. a key field is less than other when the sum of its 
    *    attributes is less that the same sum for the key field given as 
    *    parameter.
    */ 
    inline bool operator< (const ipap_field_key& rhs) const
    {
        return (eno + ftype) < (rhs.eno + rhs.ftype ); 
    }

    /** 
     * Assignment operator. 
    */ 
    inline ipap_field_key& operator= (const ipap_field_key& param)
    {
        eno = param.eno;
        ftype = param.ftype;
        return *this;
    }
    
    /** 
     * Not equal to operator. 
    */ 
    inline bool operator != (const ipap_field_key &rhs) const
    {
        return ((eno != rhs.eno) || (ftype != rhs.ftype)); 
    }
    
    /** Convert the key field in a string.
    */ 
    std::string to_string();

    /** Convert the key field in a string.
    */ 
    std::string to_string() const;

};

#endif // IPAP_FIELD_KEY_H
