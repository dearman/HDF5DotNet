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
    /// <summary>
    ///  H5Id identifies an H5 object.
    /// </summary>
    /// <remarks> 
    /// Only HDF5 library routines may
    /// create an H5Id.  Application programmers use instances of H5Id that
    /// are returned from HDF5 library calls for subsequent calls.
    /// Keeping the H5Id class implemented as an abstract data type provides
    /// the opportunity for future source-compatible library upgrades.
    /// </remarks>

    // Store the internal HDF5 id.
    /// <summary>
    /// base class for all classes that provide hid_t to the unmanaged HDF5 API.
    /// </summary>
    /// <remarks>
    ///   H5Id simply stores the hid_t id used by the unmanaged HDF5 API.
    /// Subclasses of this base class provide type saftey.
    /// </remarks>

    /// <summary>
    ///  An interface supported by all H5 Id types.
    /// </summary>
    public interface class H5Id
    {
        /// <summary>
        /// Allow read-only access to the internal HDF5 id to HDF5 library
        /// members. (members of this assembly).
        /// </summary>
        property hid_t Id
        {
            hid_t get();
        }
    };
}