/*! \file   IpAp_template_container.cpp

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
    template container class of ipap protocol

    $Id: IpAp_template_container.cpp 748 2015-08-27 14:18:00Z amarentes $
*/

#include "IpAp_template_container.h"

ipap_template_container::ipap_template_container(void)
{

}

ipap_template_container::ipap_template_container(const ipap_template_container &rhs)
{
    templateListConstIter_t it;
    for( it = rhs.templateList.begin(); it != rhs.templateList.end(); ++it){
        templateList[it->first] = (it->second)->copy();
    }
}


void ipap_template_container::delete_template(uint16_t templid)
{
    templateListIter_t it;
    for( it = templateList.begin(); it != templateList.end(); ++it) {
        if ( (it->first == templid) )
            break;
    }
    delete(it->second);
    templateList.erase(it);
}

bool ipap_template_container::exists_template(uint16_t templid)
{
	
	templateListIter_t it;
	for( it = templateList.begin(); it != templateList.end(); ++it) {
		if ( (it->first ==  templid ) )
			return true;		
	}
	return false;

}

ipap_template *
ipap_template_container::get_template(uint16_t templid)
{

	templateListIter_t it;
	for( it=templateList.begin(); it != templateList.end(); ++it) {
		if ( it->first == templid  ){			
			return it->second;
		}		
	}
	throw ipap_bad_argument("Template:%d not found in the container", templid);

}


const ipap_template *
ipap_template_container::get_const_template(const uint16_t templid) const
{

	templateListConstIter_t it;
	for( it=templateList.begin(); it != templateList.end(); ++it) {
		if ( it->first ==  templid  ){			
			return it->second;
		}		
	}
	throw ipap_bad_argument("Template not found in the container");

}


void 
ipap_template_container::delete_all_templates(void)
{
	templateListIter_t it;
	for( it=templateList.begin(); it != templateList.end(); ++it) {
		delete(it->second);
	}			
	templateList.clear();

}

 
ipap_template_container::~ipap_template_container(void)
{
	delete_all_templates();
}

bool 
ipap_template_container::operator== (const ipap_template_container& rhs)
{
	if (rhs.templateList.size() != templateList.size())
		return false;
	
	try
	{
		templateListIter_t it;
		for( it=templateList.begin(); it != templateList.end(); ++it) {
			const ipap_template *temp = rhs.get_const_template(it->first);
			if ( *(it->second) != *temp )
				return false;
		}
	}
	catch (ipap_bad_argument bad) 
	{
		// One of the templates was not found, so we have to return false.
		return false;
	}
	return true;
}


void 
ipap_template_container::add_template(ipap_template *param )
{
	if (param != NULL)
		templateList[param->get_template_id()] = param;
}


bool
ipap_template_container::operator!= (const ipap_template_container& rhs)
{
	return !(operator==(rhs));
}

ipap_template_container&
ipap_template_container::operator=(const ipap_template_container &rhs)
{
	delete_all_templates();
	
	templateListConstIter_t it;
	for( it = rhs.templateList.begin(); it != rhs.templateList.end(); ++it)
		templateList[it->first] = (it->second)->copy();
	
	return *this;
	
}

std::list<int>
ipap_template_container::get_template_list(void) const
{
	std::list<int> val_return;
	templateListConstIter_t it;
	for( it = templateList.begin(); it != templateList.end(); ++it)
		val_return.push_back(it->first);
	return val_return;
}
