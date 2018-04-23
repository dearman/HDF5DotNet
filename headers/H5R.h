/* * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group (THG).                                       *
 * All rights reserved.                                                    *
 *                                                                         *
 * This file is part of HDF5. The full HDF5 copyright notice, including    *
 * terms governing use, modification, and redistribution, is contained in  *
 * the files COPYING and Copyright.html. COPYING can be found at the root  *
 * of the source code distribution tree; Copyright.html can be found at the*
 * root level of an installed copy of the electronic HDF5 document set and *
 * is linked from the top-level documents page. It can also be found at    *
 * http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have     *
 * access to either file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "H5O.h"
#include "H5ObjectWithAttributes.h"

#include "H5Rpublic.h"

namespace HDF5DotNet
{
    ref class H5DataSpaceId;
    ref class ObjectReference;
    ref class RegionReference;

    /// <summary>
    /// The Reference interface allows the user to create references to specific objects
    /// and data regions in an HDF5 file. 
    /// </summary>
    public ref class H5R sealed
    {
    public:

        /// <summary>
        /// Interface for object and region references
        /// </summary>
        interface class IReference
        {
            array<System::Byte>^ ToByteArray();

            static property int SizeInBytes
            {
                int get() { return 0; }
            }
        };

        /// <summary>
        /// Reference types allowed.
        /// </summary>
        enum class ReferenceType
        {
            /// <summary>invalid Reference Type</summary>
            BADTYPE = H5R_BADTYPE,

            /// <summary> Object reference </summary>
            OBJECT = H5R_OBJECT,

            /// <summary> Dataset Region Reference </summary>
            DATASET_REGION = H5R_DATASET_REGION,

            /// <summary> highest type (Invalid as true type) </summary>
            MAXTYPE = H5R_MAXTYPE
        };

        /// <summary>
        /// Creates a region reference.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Create"/>
        /// </summary>
        static RegionReference^ createRegionReference
            (
            H5ObjectWithAttributes^ locId,
            System::String^         name,
            H5DataSpaceId^          spaceId
            );

        /// <summary>
        /// Creates an object reference.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Create"/>
        /// </summary>
        static ObjectReference^ createObjectReference
            (
            H5ObjectWithAttributes^ locId,
            System::String^         name
            );

        /// <summary>
        /// Retrieves a name of a referenced object.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-GetName"/>
        /// </summary>
        static System::String^ getName
            (
            H5ObjectWithAttributes^ locId,
            ReferenceType           refType,
            IReference^             ref
            );

        /// <summary>
        /// Opens the HDF5 object referenced.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Dereference"/>
        /// </summary>
        static H5ObjectWithAttributes^ dereference
            (
            H5ObjectWithAttributes^ locId,
            ReferenceType           refType,
            IReference^             ref
            );

        /// <summary>
        /// Sets up a dataspace and selection as specified by a region reference.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-GetRegion"/>
        /// </summary>
        static H5DataSpaceId^ getRegion
            (
            H5ObjectWithAttributes^ locId,
            RegionReference^        ref
            );

        /// <summary>
        /// Retrieves the type of object that an object reference points to.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-GetObjType"/>
        /// </summary>
        static H5O::ObjectType getObjectType
            (
            H5ObjectWithAttributes^ locId,
            ObjectReference^        ref
            );

    private:
        // Disallow the creation of instances of this class.
        H5R() { };
    };
}