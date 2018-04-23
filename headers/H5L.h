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

#include "H5FileOrGroupId.h"
#include "H5IndexType.h"
#include "H5IterationOrder.h"
#include "H5IterationResult.h"
#include "H5LIterateCallback.h"

#include "H5Lpublic.h"

namespace HDF5DotNet
{
    ref class H5GroupId;
    ref class H5LinkInfo;
    ref class H5PropertyListId;

    /// <summary>
    /// The H5L contains static member function for each of the supported
    /// H5L calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html"/>
    /// </summary>
    public ref class H5L sealed
    {
    public:

        ///<summary>
        /// Enumeration class for Template (H5L_SAME_LOC).
        ///</summary>
        enum class Template
        {
            SAME_LOC = H5L_SAME_LOC
        };

#pragma region documentation
        ///<summary>
        /// Retrieves metadata for a link in a group, according to the order 
        /// within a field or index.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetInfoByIdx"/>
        ///</summary>

        ///<param name="fileOrGroupId">
        /// IN: File or group identifier specifying location of subject group
        ///</param>

        ///<param name="groupName">
        /// IN: Name of subject group
        ///</param>

        ///<param name="indexType">
        /// IN: Index or field which determines the order
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Order within field or index
        ///</param>

        ///<param name="position">
        /// IN: Link for which to retrieve information
        ///</param>

        /// <returns cref="H5LinkInfo">
        /// H5LinkInfo
        /// </returns>

        /// <exception cref="H5LgetInfoByIndexException">
        /// throws H5LgetInfoByIndexException on failure.
        /// </exception>
#pragma endregion documentation

        static H5LinkInfo^ getInfoByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName, 
            H5IndexType indexType, 
            H5IterationOrder iterationOrder,
            hssize_t position);

        [System::CLSCompliant(false)]
        static H5LinkInfo^ getInfoByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName, 
            H5IndexType indexType, 
            H5IterationOrder iterationOrder,
            hsize_t position);

#pragma region documentation
        ///<summary>
        /// Retrieves name of the nth link in a group, according to the order 
        /// within a specified field or index.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetNameByIdx"/>
        ///</summary>

        ///<param name="fileOrGroupId">
        /// IN: File or group identifier specifying location of subject group
        ///</param>

        ///<param name="groupName">
        /// IN: Name of subject group
        ///</param>

        ///<param name="indexType">
        /// IN: Index or field which determines the order
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Order within field or index
        ///</param>

        ///<param name="position">
        /// IN: Link for which to retrieve information
        ///</param>

        /// <returns>
        /// A string containing the requested name.
        /// </returns>
        /// <exception cref="H5LgetNameByIndexException">
        /// throws H5LgetNameByIndexException on failure.
        /// </exception>
#pragma endregion documentation

        static System::String^  getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName,
            H5IndexType indexType,
            H5IterationOrder iterationOrder,
            hssize_t position);

        [System::CLSCompliant(false)]
        static System::String^  getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName,
            H5IndexType indexType,
            H5IterationOrder iterationOrder,
            hsize_t position);

#pragma region documentation
        ///<summary>
        /// Retrieves name of the nth link in a group, according to the order 
        /// within a specified field or index.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetNameByIdx"/>
        ///</summary>

        ///<param name="fileOrGroupId">
        /// IN: File or group identifier specifying location of subject group
        ///</param>

        ///<param name="groupName">
        /// IN: Name of subject group
        ///</param>

        ///<param name="indexType">
        /// IN: Index or field which determines the order
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Order within field or index
        ///</param>

        ///<param name="position">
        /// IN: Link for which to retrieve information
        ///</param>

        ///<param name="linkAccessPropertyList">
        /// IN: Link access property list
        ///</param>

        /// <returns>
        /// A string containing the requested name.
        /// </returns>
        /// <exception cref="H5LgetNameByIndexException">
        /// throws H5LgetNameByIndexException on failure.
        /// </exception>
#pragma endregion documentation

        static System::String^ getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName,
            H5IndexType indexType,
            H5IterationOrder iterationOrder,
            hssize_t position,
            H5PropertyListId^ linkAccessPropertyList);

        [System::CLSCompliant(false)]
        static System::String^ getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
            System::String^ groupName,
            H5IndexType indexType,
            H5IterationOrder iterationOrder,
            hsize_t position,
            H5PropertyListId^ linkAccessPropertyList);

        /// <summary>Returns information about a link.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetInfo"/>
        /// </summary>
        static H5LinkInfo^ getInfo( H5FileOrGroupId^ fileOrGroupId);

        static H5LinkInfo^ getInfo( H5FileOrGroupId^ fileOrGroupId, 
            System::String^ groupName);

        static H5LinkInfo^ getInfo( H5FileOrGroupId^ fileOrGroupId, 
            System::String^ groupName,
            H5PropertyListId^ linkAccessPropertyListId);

        /// <summary>Returns the value of a symbolic link.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetVal"/>.
        /// The buffer returned by this method must be freed with FreeHGlobal, otherwise.
        /// resource leakage will occur.
        /// <see href="http://msdn.microsoft.com/en-us/library/system.runtime.interopservices.marshal.freehglobal.aspx"/>.
        /// </summary>
        static System::IntPtr get_val(H5FileOrGroupId^ fileOrGroupId,
            System::String^ linkName,
            H5PropertyListId^ linkAccessPropertyList);

        /// <summary>Iterates through links in a group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Iterate"/>
        /// </summary>
        static H5IterationResult iterate(H5GroupId^ groupId,
            H5IndexType indextType,
            H5IterationOrder iterationOrder,
            hssize_t% index,
            H5LIterateCallback^ func,
            System::Object^ objData);

        [System::CLSCompliant(false)]
        static H5IterationResult iterate(H5GroupId^ groupId,
            H5IndexType indextType,
            H5IterationOrder iterationOrder,
            hsize_t% index,
            H5LIterateCallback^ func,
            System::Object^ objData);

        /// <summary>Creates a hard link to an object.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-CreateHard"/>
        /// </summary>
        static void createHardLink(
            H5FileOrGroupId^ objLocRef,
            System::String^  objName,
            H5FileOrGroupId^ linkLocRef,
            System::String^  linkName);

        /// <summary>Removes a link from a group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Delete"/>
        /// </summary>
        static void Delete(
            H5FileOrGroupId^ linkLocRef,
            System::String^  linkName);

        /// <summary>Determine whether a link with the specified name exists in a group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Exists"/>
        /// </summary>
        static bool Exists(
            H5FileOrGroupId^ locRef,
            System::String^  name);

    private:

        // Disallow the default constructor.
        H5L();
    };

} // namespace