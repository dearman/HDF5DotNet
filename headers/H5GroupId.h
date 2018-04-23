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

#include "H5FileOrGroupId.h"
#include "H5LocId.h"
#include "H5ObjectWithAttributes.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
    /// <summary> H5GroupId uniquely identifies a group. </summary>
    public ref class H5GroupId : public H5LocId, H5FileOrGroupId,
        H5ObjectWithAttributes
    {
    internal:
        /// <remarks>
        /// This is the only constructor used to create an H5GroupId.  It can
        /// only be invoked by HDF5DotNet library functions.
        /// </remarks>
        /// <param name="id"> is an HDF5 library-generated identification
        /// number that serves as a unique indentifier. </param>
        H5GroupId(hid_t id);

    public:
        /// <summary>
        /// Allow read-only access to the internal HDF5 id to HDF5 library
        /// members. (members of this assembly).
        /// </summary>
        virtual property hid_t Id
        {
            hid_t get() { return id_; }
        }

    private:
        /// <summary>
        /// The default constructor is disallowed.  Only HDF5 library
        /// routines are capable of creating an instance of H5GroupId and they
        /// must supply an id when doing so.
        /// </summary>
        H5GroupId();

        /// <summary>
        // The hdf5 internal id used to identify objects.
        /// </summary>
        hid_t id_;
    };
}