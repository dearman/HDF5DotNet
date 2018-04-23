/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Copyright by The HDF Group (THG).*
* All rights reserved. *
**
* This file is part of HDF5. The full HDF5 copyright notice, including*
* terms governing use, modification, and redistribution, is contained in*
* the files COPYING and Copyright.html. COPYING can be found at the root*
* of the source code distribution tree; Copyright.html can be found at the*
* root level of an installed copy of the electronic HDF5 document set and*
* is linked from the top-level documents page. It can also be found at*
* http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have*
* access to either file, you may request a copy from help@hdfgroup.org.*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "H5Ipublic.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
    ///<summary>
    /// Enumeration type for Index Type (NAME or CRT_ORDER).
    ///</summary>
    public enum class H5IndexType
    {
        /// <summary> 
        /// An alpha-numeric index by attribute name
        /// </summary>
        NAME = H5_INDEX_NAME,

        /// <summary> 
        ///  An index by creation order
        /// </summary>
        CRT_ORDER = H5_INDEX_CRT_ORDER
    };
}