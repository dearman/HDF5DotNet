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

#include "H5Id.h"

namespace HDF5DotNet
{
    /// <summary>
    /// H5I contains methods for working with object identifiers and object names.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html"/>
    /// </summary>
    public ref class H5I sealed
    {
    public:

        /// <summary>
        /// Identifier type values.
        /// </summary>
        enum class IdentifierType
        {
            /// <summary>uninitialized type</summary>
            UNINIT = H5I_UNINIT,

            /// <summary>invalid Type</summary>
            BADID = H5I_BADID,

            /// <summary>type ID for File objects</summary>
            FILE = H5I_FILE,

            /// <summary>type ID for Group objects</summary>
            GROUP = H5I_GROUP,

            /// <summary>type ID for Datatype objects</summary>
            DATATYPE = H5I_DATATYPE,

            /// <summary>type ID for Dataspace objects</summary>
            DATASPACE = H5I_DATASPACE,

            /// <summary>type ID for Dataset objects</summary>
            DATASET = H5I_DATASET,

            /// <summary>type ID for Attribute objects</summary>
            ATTR = H5I_ATTR,

            /// <summary>type ID for Reference objects</summary>
            REFERENCE = H5I_REFERENCE,

            /// <summary>type ID for virtual file layer</summary>
            VFL = H5I_VFL,

            /// <summary>type ID for generic property list classes</summary>
            GENPROP_CLS = H5I_GENPROP_CLS,

            /// <summary>type ID for generic property lists</summary>
            GENPROP_LST = H5I_GENPROP_LST,

            /// <summary>type ID for error classes</summary>
            ERROR_CLASS = H5I_ERROR_CLASS,

            /// <summary>type ID for error messages</summary>
            ERROR_MSG = H5I_ERROR_MSG,

            /// <summary>type ID for error stacks</summary>
            ERROR_STACK = H5I_ERROR_STACK,

            /// <summary> number of library types </summary>
            NTYPES = H5I_NTYPES
        };

        /// <summary>
        /// Retrieves the type of an object.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetType"/>
        /// </summary>
        static H5I::IdentifierType getIdentifierType(H5Id^ id);

        /// <summary>
        /// Retrieves a name of an object based on the object identifier.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetName"/>
        /// </summary>

        static System::String^ getName(H5Id^ objId);

    private:
        // Disallow the creation of instances of this class.
        H5I() { };

    };
}
