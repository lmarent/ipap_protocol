/*! \file   IpAp_template.h

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
    temaplte class of ipap protocol

    $Id: IpAp_template.h 748 2015-08-26 18:48:00Z amarentes $
*/


#ifndef IPAP_TEMPLATE_H
#define IPAP_TEMPLATE_H

#include "stdincpp.h"
#include "IpAp_field.h"
#include "IpAp_field_key.h"

typedef enum 
{
    IPAP_INVALID = -1,
    IPAP_AUCTION = 0, 
    IPAP_BID,
    IPAP_ASK,
    IPAP_ALLOCATION,
    IPAP_MAX_OBJECT_TYPE
} ipap_object_type_t;

extern const char *ipap_object_type_names[IPAP_MAX_OBJECT_TYPE];


typedef enum 
{
    IPAP_SETID_AUCTION_TEMPLATE = 0, 
    IPAP_OPTNS_AUCTION_TEMPLATE,
    IPAP_SETID_BID_OBJECT_TEMPLATE,
    IPAP_OPTNS_BID_OBJECT_TEMPLATE,
    IPAP_SETID_ASK_OBJECT_TEMPLATE,
    IPAP_OPTNS_ASK_OBJECT_TEMPLATE,
    IPAP_SETID_ALLOC_OBJECT_TEMPLATE,
    IPAP_OPTNS_ALLOC_OBJECT_TEMPLATE
} ipap_templ_type_t;

typedef enum
{
    IPAP_RECORD = 0,
    IPAP_OPTIONS
} ipap_templ_subtype_t;

typedef enum
{
    KNOWN, 
    UNKNOWN
} ipap_unknown_field_t;	

/**
 * \class ipap_template_field_t
 *
 * \brief This class contains the list of fields belonging to a template
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
typedef struct
{
    uint16_t            	flength;           /* less or eq. elem->flength  */
    ipap_unknown_field_t   unknown_f;         /* set if unknown elem */
    int                 	relay_f;           /* just relay no, encoding (exp.) */
    ipap_field   			elem;
} ipap_template_field_t;

/**
 * \class ipap_template
 *
 * \brief This class represents a template.
 * 
 *  We conceptualize a template as a set of field definitions. The field set 
 *  is composed by two subsets: a data set field and a scope field set. 
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

typedef vector<ipap_template_field_t>                   templateFieldList_t;
typedef vector<ipap_template_field_t>::iterator         templateFieldIterList_t;
typedef vector<ipap_template_field_t>::const_iterator   templateFieldConstIterList_t;

typedef map<ipap_object_type_t, set<ipap_templ_type_t> >                    objectTemplateList_t;
typedef map<ipap_object_type_t, set<ipap_templ_type_t> >::iterator          objectTemplateIterList_t;
typedef map<ipap_object_type_t, set<ipap_templ_type_t> >::const_iterator    objectTemplateConstIterList_t;

typedef map<ipap_templ_type_t, set<ipap_field_key> >                    templateKeyList_t;
typedef map<ipap_templ_type_t, set<ipap_field_key> >::iterator          templateKeyIterList_t;
typedef map<ipap_templ_type_t, set<ipap_field_key> >::const_iterator    templateKeyConstIterList_t;
            
 
class ipap_template
{
    private:
        
        ipap_templ_type_t     				type;  			///< data or option template 
        time_t                  			tsend; 			///< time of last transmission
        uint16_t                			tid;			///< Template id
        int 								maxfields; 		///< Maximum number of fields
        templateFieldList_t			 		datafields;		///< Subset of data fields

    public:

        static const char *TEMPLATE_XML_TAGS[];
        
        static templateKeyList_t templateKeys;
        

        //! Maintains by template's type the list of mandatory fields.
        static templateKeyList_t templateMandatoryFields;
        
        //! Maintains the list of templates types by object
        static objectTemplateList_t objectTemplates;
        
        //! Maintain the relationship between the template type and the object type to which it is part of. 
        static map<ipap_templ_type_t, ipap_object_type_t> templateObjectRel;
        
        //! Maintain record and option templates.
        static map<ipap_templ_subtype_t, set<ipap_templ_type_t> > templatesBySubtype;
        
        /**
         * Constructor for the class ipap_template
         */
        inline ipap_template():tsend(0){}
        
        /**
         * Constructor from the data of another template
         */
        ipap_template(const ipap_template &rhs); 
        
        /**
         * Destructor for the class ipap_template
         */
        inline ~ipap_template(){}
        
        /**
         * Set the id of the template
         * @param _tid - template id.
         */
        inline void set_id(uint16_t _tid){ tid = _tid; }
        
        /**
         * Set the type of the template ( data or option)
         * @param _type - Template type.
         */
        inline void set_type(ipap_templ_type_t _type){ type = _type; }
        
        /**
         * Set the last datetime in which it was send
         * @param _tsend - Send time
         */
        inline void set_time_send(time_t _tsend){ tsend = _tsend; }
        
        /**
         * Set the maximum number of fields that the field set can have
         * @param _maxfields 	- Field maximum cardinality
         */
        inline void set_maxfields(int _maxfields){ maxfields = _maxfields; }
        
        /**
         * Get the type of the template ( data or option)
         */
        inline ipap_templ_type_t get_type(void)
        {
            return type;
        }
        
        /**
         * Get the last datetime in which it was send
         */
        inline time_t get_tsend(void)
        {
            return tsend;
        }
        
        /**
         * Get the template id
         */
        inline uint16_t get_template_id(void)
        {
            return tid;
        }
                        
        /**
         * Get the total number of fields in the template
         */
        inline int get_numfields(void)
        {
            return (int)  ( datafields.size() );
        }
        
        /**
         * Get the maximum number of fields that can be associated to the template
         */
        inline int get_maxfields(void)
        {
            return maxfields;
        }
        
        /**
         * Add a new field to the template
         */
        void add_field(uint16_t _flength, 
                       ipap_unknown_field_t _unknown_f, 
                       int _relay_f,  
                       ipap_field  &_field);
        
        /**
         * Add a new field to the template
         */        
         void add_field(uint16_t _flength, 
                        ipap_unknown_field_t _unknown_f, 
                        int _relay_f,
                        ipap_field  *_field);
        
        /**
         * Get a field located in the position i
         * The order is scope and then data fields 
         * @param i - position of the field to get. 
         */
        ipap_template_field_t get_field(int i);
        
        /**
         * Remove all fields market with the unknown tag.
         */
        void remove_unknown_fields();
        
        /**
        *  Equals to operator. 
        *  It is equal when it has the same amount of fields and every 
        *    field is in the same position and equal.
        */
        bool operator== (const ipap_template& rhs);

        /**
        *  Not equal to operator. 
        *  It is not equal when it does not have the same amount of fields 
        *    and exists a different field or it has a different position.
        */
        bool operator!= (const ipap_template& rhs);	
        
        /** Assignment operator. It sets the values for the template 
         * 						 from another template.
        *  @param  the template to copy from.
        */
        ipap_template& operator= (const ipap_template&);
        
        /** 
         * Creates a new object returning its pointer. 
         * The data to be used for the new template is taken from the
         * instance.
        */
        ipap_template * copy(void) const;
    
    
        ipap_field  get_field( int eno, int type );
        
        static set<ipap_field_key> getTemplateTypeKeys(ipap_templ_type_t templType);
        
        static set<ipap_field_key> getTemplateTypeMandatoryFields(ipap_templ_type_t templType);
        
        ipap_field_key* getTemplateTypeMandatoryFieldVector(ipap_templ_type_t templType, int index);
        
        int getTemplateTypeMandatoryFieldSize(ipap_templ_type_t templType);
        
        /** 
         * 	\short get the set of template types associated with an object type
         *  \arg   objectType - Object type 
        */
        static set<ipap_templ_type_t> getObjectTemplateTypes(ipap_object_type_t objectType);
        

        /**
         * @brief gets the number of type of templates associated with a particular object
         * @param objectType Type of object to get the number
         * @return Number of template types associated to the object type.
         */
        int getObjectTemplateTypesSize(ipap_object_type_t objectType);

        /**
         * @brief gets the template type in the index position from the list of template types
         * @param objectType Type of object to get the number
         * @param index position to bring, it should e a number between 0 and getObjectTemplateTypesSize(objectType)
         * @return template type 
         */
        ipap_templ_type_t getObjectTemplateTypesAtPos(ipap_object_type_t objectType, int index);

        
        /** 
         * 	\short Get the object type to which is associated the template type
         *  \arg   templType - Template type 
        */
        static ipap_object_type_t getObjectType(ipap_templ_type_t templType);
                
        /** 
         * 	\short Get templates associated with a specific template subtype.
         *  \arg   subtype - Template subtype. 
        */
        static set<ipap_templ_type_t> getTemplates(ipap_templ_subtype_t subtype);
        
        
        /** 
         * 	\short Get the template type for an object type an  template subtype.
         * 	\arg   objectType  - object type
         *  \arg   subtype 	   - template subtype. 
        */
        static ipap_templ_type_t getTemplateType(ipap_object_type_t objectType, 
                                                 ipap_templ_subtype_t subtype);
};


#endif // IPAP_TEMPLATE_H
