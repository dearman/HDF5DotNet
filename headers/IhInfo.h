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

#include "H5Ipublic.h" // modified version of H5Gpublic.h

namespace HDF5DotNet
{
    /// <summary>
    /// Object that contains index and heap sizes.
    /// </summary>
    public ref class IhInfo
    {
    public:

        /// <summary>
        /// btree and/or list
        /// </summary>
        property hssize_t indexSize
        {
            hssize_t get() { return safe_cast<hssize_t>(indexSize_); }
        }

        /// <summary>
        /// The heap size
        /// </summary>
        property hssize_t heapSize
        {
            hssize_t get() { return safe_cast<hssize_t>(heapSize_); }
        }

    private:
        /// <summary>
        /// Index size (btree and/or list)
        /// </summary>
        hsize_t     indexSize_;

        /// <summary>
        /// The heap size
        /// </summary>
        hsize_t     heapSize_;

        // Disallow the default constructor.
        IhInfo();

    internal:
        IhInfo(hsize_t indexSize, hsize_t heapSize);
    }; 
}