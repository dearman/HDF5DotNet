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

#include "H5Gpublic.h"

namespace HDF5DotNet
{
    ///<summary>
    /// Enumeration for storage type (COMPACT, DENSE, or SYMBOL_TABLE)
    ///</summary>
    public enum class H5GStorageType
    {
        COMPACT = H5G_STORAGE_TYPE_COMPACT,
        DENSE = H5G_STORAGE_TYPE_DENSE,
        SYMBOL_TABLE = H5G_STORAGE_TYPE_SYMBOL_TABLE
    };
}