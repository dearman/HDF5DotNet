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

#include "H5IndexType.h"
#include "H5IterationOrder.h"
#include "H5LocId.h"
#include "H5ObjectInfo.h"
#include "H5PropertyListId.h"
#include "HDFExceptionSubclasses.h"

#include "H5Opublic.h"

namespace HDF5DotNet
{
    /// <summary>
    /// The H5O contains static member function for each of the supported
    /// H5O calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html"/>
    /// </summary>
    public ref class H5O sealed
    {
    public:

        /// <summary>
        ///  Enumerates the different types of objects in a file.
        /// </summary>
        enum class ObjectType
        {
            /// <summary> Unknown object type </summary>
            UNKNOWN = H5O_TYPE_UNKNOWN,

            /// <summary> Object is a group </summary>
            GROUP = H5O_TYPE_GROUP,

            /// <summary> Object is a dataset </summary>
            DATASET = H5O_TYPE_DATASET,

            /// <summary> Object is a named data type </summary>
            NAMED_DATATYPE = H5O_TYPE_NAMED_DATATYPE,

            /// <summary> Number of different object types </summary>
            NTYPES = H5O_TYPE_NTYPES
        };

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object specified by an identifier.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfo"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Identifier for target object
        ///</param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoException">
        /// throws H5OgetInfoException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfo(H5Id^ objectId);

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object, identifying the object by 
        /// location and relative name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: File or group identifier specifying location of 
        /// group in which object is located
        ///</param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoByNameException">
        /// throws H5OgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfoByName(
            H5Id^ objectId);

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object, identifying the object by 
        /// location and relative name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: File or group identifier specifying location of 
        /// group in which object is located
        ///</param>

        ///<param name="name">
        /// IN: Name of group, relative to loc_id
        ///</param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoByNameException">
        /// throws H5OgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfoByName(
            H5Id^ objectId,
            System::String^ name);

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object, identifying the object by 
        /// location and relative name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: File or group identifier specifying location of 
        /// group in which object is located
        ///</param>

        ///<param name="name">
        /// IN: Name of group, relative to loc_id
        ///</param>

        ///<param name="linkAccessPropertyListId">
        /// IN: Link access property list
        /// </param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoByNameException">
        /// throws H5OgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfoByName(
            H5Id^ objectId,
            System::String^ name, 
            H5PropertyListId^ linkAccessPropertyListId);

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object, identifying the 
        /// object by an index position.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByIdx"/>
        ///</summary>

        ///<param name="locId">
        /// IN: File or group identifier specifying location of group in 
        /// which object is located
        ///</param>

        ///<param name="groupName">
        /// IN: Name of group in which object is located
        ///</param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoByIndexException">
        /// throws H5OgetInfoByIndexException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfoByIndex(H5LocId^ locId,
            System::String^ groupName, 
            H5IndexType index,
            H5IterationOrder iterationOrder,
            hssize_t position);

        [System::CLSCompliant(false)]
        static H5ObjectInfo^ getInfoByIndex(H5LocId^ locId,
            System::String^ groupName, 
            H5IndexType index,
            H5IterationOrder iterationOrder,
            hsize_t position);

#pragma region documentation
        ///<summary>
        /// Retrieves the metadata for an object, identifying the 
        /// object by an index position.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByIdx"/>
        ///</summary>

        ///<param name="locId">
        /// IN: File or group identifier specifying location of group in 
        /// which object is located
        ///</param>

        ///<param name="groupName">
        /// IN: Name of group in which object is located
        ///</param>

        ///<param name="index">
        /// IN: Index or field that determines the order
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Order within field or index
        ///</param>

        ///<param name="position">
        /// IN: Object for which information is to be returned
        ///</param>

        ///<param name="linkAccessPropertyListId">
        /// OUT: Buffer in which to return object information
        ///</param>

        /// <returns cref="H5ObjectInfo">
        /// H5ObjectInfo
        /// </returns>

        /// <exception cref="H5OgetInfoByIndexException">
        /// throws H5OgetInfoByIndexException on failure.
        /// </exception>
#pragma endregion documentation

        static H5ObjectInfo^ getInfoByIndex( 
            H5LocId^ locId,
            System::String^ groupName, 
            H5IndexType index,
            H5IterationOrder iterationOrder,
            hssize_t position,
            H5PropertyListId^ linkAccessPropertyListId);

        [System::CLSCompliant(false)]
        static H5ObjectInfo^ getInfoByIndex( 
            H5LocId^ locId,
            System::String^ groupName, 
            H5IndexType index,
            H5IterationOrder iterationOrder,
            hsize_t position,
            H5PropertyListId^ linkAccessPropertyListId);

    private:

        // Disallow default constructor.
        H5O();
    };

}  // namespace

