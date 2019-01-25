/*! \file   IpAp_template_container.h

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
    template container class of ipap protocol. 
    This container does not free the memory assigned to templates.

    $Id: IpAp_template_container.h 748 2015-08-27 14:18:00Z amarentes $
*/

#ifndef IPAP_TEMPLATE_CONTAINER_H
#define IPAP_TEMPLATE_CONTAINER_H


#include "stdincpp.h"
#include "IpAp_template.h"

/**
 * \class ipap_template_container
 *
 * \brief This class stores all templates in a message
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
 
typedef map<uint16_t, ipap_template *>  		  		templateList_t;
typedef map<uint16_t, ipap_template *>::iterator  		templateListIter_t;
typedef map<uint16_t, ipap_template *>::const_iterator  templateListConstIter_t;

 
 
class ipap_template_container
{
    private:
        
        templateList_t templateList; ///< Map of templates
    
    protected:
        
        /**
         * Get the template with id equal to templid
         * @param templid	- id of the template to look for
         */
        const ipap_template * get_const_template(const uint16_t templid) const;

    
    public:
    
        /**
         * Constructor for the ipap_template_container class
         */
        ipap_template_container(void);

        /** 
         * Constructor from the data of another template container
         */
        ipap_template_container(const ipap_template_container &rhs);
        
        /**
         * Destructor for the ipap_template_container class
         */
        ~ipap_template_container(void);
    
        /**
         * Add a new template to the container
         */
        void add_template(ipap_template *param );
                
        /**
         * delete all templates from the container
         */
        void delete_all_templates(void);
        
        /**
         * delete the template with id equal to templid
         * @param templid	- id of the template to delete
         */
        void delete_template(uint16_t templid);
        
        /**
         * verify whether a template with id equal to templid exists or not
         * @param templid	- id of the template to look for
         */
        bool exists_template(uint16_t templid);
        
        /**
         * Get the template with id equal to templid
         * @param templid	- id of the template to look for
         */
        ipap_template * get_template(uint16_t templid);
                
        /**
        * Return the number of templates included
        */
        inline int get_num_templates(void){  return templateList.size(); }
        
        /**
         * Return a list with all templates IDs included
         */
        std::list<int> get_template_list(void) const;
        
        /**
         * Return the template in position pos of the list.
         */
        int get_template_at_pos(int pos);
        
        /**
        *  Equals to operator. 
        *  It is equal when it has the same amount of templates and every 
        *    template is equal.
        */
        bool operator== (const ipap_template_container& rhs);
        
        /**
        *  Not equal to operator. 
        *  It is not equal when it does not have the same amount of templates and at least 
        *    one field is not a template.
        */
        bool operator!= (const ipap_template_container& rhs);
        
        /** Assignment operator. It sets the values for the template container 
         * 						 from another template container.
        *  @param  the template container to copy from.
        */
        ipap_template_container& operator= (const ipap_template_container&);				
                
};

#endif // IPAP_TEMPLATE_CONTAINER_H
