/*! \file   IpAp_create_map.h

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
    ipap_create_map class of ipap protocol. Used for initializing a map.

    $Id: ipap_create_map.h 748 2015-10-08 11:45:00Z amarentes $
*/

#ifndef IPAP_CREATE_MAP_H
#define IPAP_CREATE_MAP_H

#include "stdincpp.h"

template <typename T, typename U>
class ipap_create_map
{
private:
    map<T, U> m_map;
public:
    ipap_create_map(const T& key, const U& val)
    {
        m_map[key] = val;
    }

    ipap_create_map<T, U>& operator()(const T& key, const U& val)
    {
        m_map[key] = val;
        return *this;
    }

    operator std::map<T, U>()
    {
        return m_map;
    }
};

#endif // IPAP_CREATE_MAP_H
