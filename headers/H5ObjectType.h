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

#include "H5Opublic.h"

namespace HDF5DotNet
{
    /// <summary>
    ///  Enumerates the different H5Object types.
    /// </summary>
    public enum class H5ObjectType
    {
        /// <summary> The type of this object is unknown. </summary>
        UNKNOWN = H5O_TYPE_UNKNOWN,

        /// <summary> The type of this object is "group." </summary>
        GROUP = H5O_TYPE_GROUP,

        /// <summary> The type of this object is "data set." </summary>
        DATASET = H5O_TYPE_DATASET,

        /// <summary> The type of this object is "data type." </summary>
        NAMED_DATATYPE = H5O_TYPE_NAMED_DATATYPE
    };
}