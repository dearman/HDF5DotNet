/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group (THG).                                       *
 * All rights reserved.                                                    *
 *                                                                         *
 * This file is part of HDF5.  The full HDF5 copyright notice, including   *
 * terms governing use, modification, and redistribution, is contained in  *
 * the files COPYING and Copyright.html.  COPYING can be found at the root *
 * of the source code distribution tree; Copyright.html can be found at the*
 * root level of an installed copy of the electronic HDF5 document set and *
 * is linked from the top-level documents page.  It can also be found at   *
 * http://www.hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have    *
 * access to either file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include "H5Ipublic.h"

namespace HDF5DotNet
{

    ///<summary>
    /// Object that contains properties about object space usage.
    ///</summary>
    public ref class Space
    {

    public:

        ///<summary>
        /// Total space for storing object header in file 
        ///</summary>
        property hssize_t total
        {
            hssize_t get() { return safe_cast<hssize_t>(total_); }
        }

        ///<summary>
        /// Space within header for object header metadata
        ///</summary>
        property hssize_t meta
        {
            hssize_t get() { return safe_cast<hssize_t>(meta_); }
        }

        ///<summary>
        /// Space within header for actual message information 
        ///</summary>
        property hssize_t message
        {
            hssize_t get() { return safe_cast<hssize_t>(mesg_); }
        }

        ///<summary>
        /// Free space within object header
        ///</summary>
        property hssize_t free
        {
            hssize_t get() { return safe_cast<hssize_t>(free_); }
        }

    private:
        ///<summary>
        /// Total space for storing object header in file 
        ///</summary>
        hsize_t total_;  

        ///<summary>
        /// Space within header for object header metadata
        ///</summary>
        hsize_t meta_;   

        /* information */

        ///<summary>
        /// Space within header for actual message information 
        ///</summary>
        hsize_t mesg_;   

        ///<summary>
        /// Free space within object header
        ///</summary>
        hsize_t free_;   

        // Disallow the default constructor.
        Space();

    internal:
        Space(hsize_t total, hsize_t meta, hsize_t mesg, hsize_t free);

    };

}