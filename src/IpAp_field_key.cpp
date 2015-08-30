/*! \file   IpAp_field_key.cpp

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

    $Id: ApAp_field_key.cpp 748 2015-08-26 18:48:00Z amarentes $
*/

#include "IpAp_field_key.h"


std::string 
ipap_field_key::to_string()
{
	std::ostringstream o1;
	o1 << "eno:" << eno;
	o1 << "ftype:" << ftype;
	return o1.str();

}
