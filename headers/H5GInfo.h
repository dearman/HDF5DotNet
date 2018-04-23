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

#include "H5GStorageType.h"

#include "H5Ipublic.h"

namespace HDF5DotNet
{
    /// <summary>
    /// An instance of H5GInfo is returned from H5G.getInfo.  It contains 
    /// properties that provide the link storage type, the number of links,
    /// and the current maximum creation order for the group.
    /// </summary>
    public ref class H5GInfo
    {
    public:

        ///<summary>
        /// Type of storage for links in group.  Storage types include 
        /// COMPACT, DENSE, and SYMBOL_TABLE.
        ///</summary>
        property H5GStorageType linkStorageType
        {
            H5GStorageType get() 
            {
                return linkStorageType_;
            }
        };

        ///<summary>
        /// Number of links in the group.
        ///</summary>
        property hssize_t nLinks
        {
            hssize_t get() 
            {
                return safe_cast<hssize_t>(nLinks_);
            }
        };

        ///<summary>
        /// Current maximum creation order for the group.
        ///</summary>
        property hssize_t maxCreationOrder
        {
            hssize_t get() 
            {
                return safe_cast<hssize_t>(maxCreationOrder_);
            }
        };

    internal:
        H5GInfo(H5G_info_t% info);

    private:
        ///<summary>
        /// Type of storage for links in group.  Storage types include 
        /// COMPACT, DENSE, and SYMBOL_TABLE.
        ///</summary>
        H5GStorageType linkStorageType_;

        ///<summary>
        /// Number of links in the group.
        ///</summary>
        hsize_t nLinks_;

        ///<summary>
        /// Current maximum creation order for the group.
        ///</summary>
        hsize_t maxCreationOrder_;
    };

}