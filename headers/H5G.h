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
#include "H5GInfo.h"
#include "H5GIterateCallback.h"
#include "H5GType.h"
#include "H5LocId.h"
#include "HDFExceptionSubclasses.h"
#include "LinkType.h"

#include "H5Ipublic.h"

namespace HDF5DotNet
{
    ref class H5GroupId;
    ref class H5PropertyListId;
    ref class ObjectInfo;

    /// <summary>
    /// The H5G contains static member function for each of the supported
    /// H5G calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html"/>
    /// </summary>

    public ref class H5G sealed
    {
    public:

#pragma region documentation
        /// <summary>
        /// Create a HDF5 group.  Creates a new empty group and gives 
        ///  it a name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Create"/>
        /// </summary>
        /// <param name="groupOrFileId"> IN: provides a group or file id. 
        /// </param>
        /// <param name= "groupName"> IN: Absolute or relative name of the
        /// new group.
        /// </param>
        /// <returns> Returns a valid group identifier 
        /// </returns>
        /// <remarks>
        /// <para>
        /// H5G.create creates a new group with the specified name at the 
        /// specified location, loc_id. The location is identified by a 
        /// file or group identifier. The name must not already be 
        /// taken by some other object and all parent groups must already 
        /// exist.
        /// </para>
        /// <para> 
        /// The return value is a group identifier for the open group. 
        /// This group identifier should be closed by calling H5G.close
        /// when it is no longer needed.  
        /// </para>
        /// </remarks>
        /// <exception>
        /// throws H5GcreateException if the creation fails.
        /// </exception>
#pragma endregion documentation

        static H5GroupId^ create(H5LocId^ groupOrFileId, System::String^ groupName);

#pragma region documentation
        /// <summary>
        /// Create a HDF5 group.  Creates a new empty group and gives 
        ///  it a name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Create"/>
        /// </summary>
        /// <param name="groupOrFileId"> IN: provides a group or file id. 
        /// </param>
        /// <param name="groupName"> IN: Absolute or relative name of the
        /// new group.
        /// </param>
        /// <param name="linkCreation">
        /// </param>
        /// <param name="groupCreation">
        /// </param>
        /// <param name="groupAccess">
        /// </param>
        /// <returns> Returns a valid group identifier 
        /// </returns>
        /// <remarks>
        /// <para>
        /// H5G.create creates a new group with the specified name at the 
        /// specified location, loc_id. The location is identified by a 
        /// file or group identifier. The name must not already be 
        /// taken by some other object and all parent groups must already 
        /// exist.
        /// </para>
        /// <para> 
        /// The return value is a group identifier for the open group. 
        /// This group identifier should be closed by calling H5G.close
        /// when it is no longer needed.  
        /// </para>
        /// </remarks>
        /// <exception>
        /// throws H5GcreateException if the creation fails.
        /// </exception>
#pragma endregion documentation

        static H5GroupId^ create(H5LocId^ groupOrFileId, 
            System::String^ groupName,
            H5PropertyListId^ linkCreation,
            H5PropertyListId^ groupCreation,
            H5PropertyListId^ groupAccess);

#pragma region documentation
        /// <summary>
        ///  Opens an existing group for modification and returns a group
        /// identifier for that group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Open"/>
        /// </summary>
        /// <param name="groupOrFileId">
        /// IN: File or group identifier
        /// within which group is to be open. 
        /// </param>
        /// <param name="groupName"> 
        /// IN: Name of group to open.
        /// </param>
        /// <remarks>
        /// H5G.open opens an existing group with the specified name
        /// at the specified location, groupOrFileId. The location is 
        /// identified 
        /// by a file or group identifier.  H5G.open returns a group
        /// identifier for the group that was opened. This group
        /// identifier should be released by calling H5G.close when it is
        /// no longer needed. 
        /// </remarks>
        /// <exception>
        /// H5G.open throws H5GopenException on failure.
        /// </exception>
#pragma endregion documentation

        static H5GroupId^ open(H5LocId^ groupOrFileId, System::String^ groupName,
            H5PropertyListId^ groupAccessPropertyListId);

        static H5GroupId^ open(H5LocId^ groupOrFileId, System::String^ groupName);

#pragma region documentation
        /// <summary>
        /// Closes the specified group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Close"/>
        /// </summary>
        /// <param name="groupId"> IN: Group identifier to release. 
        /// </param>
        /// <remarks> H5Gclose releases resources used by a group which
        /// was opened by H5Gcreate or H5Gopen. After closing a group, the
        /// group_id cannot be used again. 
        /// </remarks>
        /// <exception>
        /// throws H5GcloseException if the close fails.
        /// </exception>
#pragma endregion documentation

        static void close(H5GroupId^ groupId);

#pragma region documentation
        /// <summary>
        /// Gets the number of objects in the specified group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetNumObjs"/>
        /// </summary>
        /// <param name="groupId"> IN: Group identifier
        /// </param>
        /// <exception cref="H5GgetNumObjectsException"> 
        /// throws H5GgetNumObjectsException if request fails 
        /// </exception>
        /// <remarks> 
        /// </remarks>
#pragma endregion documentation

        static hssize_t getNumObjects(H5GroupId^ groupId);

#pragma region documentation
        /// <summary>
        /// Gets the name of the object with the specified object index.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetObjNameByIdx"/>
        /// </summary>
        /// <param name="groupId"> IN: Group in which object is a
        /// member.
        /// </param>
        /// <exception cref="H5GgetObjectNameByIndexException"> 
        /// throws H5GgetObjectNameByIndexException if request fails 
        /// </exception>
        /// <remarks> 
        /// </remarks>
#pragma endregion documentation

        static System::String^ getObjectNameByIndex(H5GroupId^ groupId, 
            hsize_t objectIndex);

#pragma region documentation
        /// <summary>
        /// Iterates an operation over the entries of a group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Iterate"/>
        /// </summary>
        /// <param name="loc"> 
        /// IN: File or group identifier.
        /// </param>
        /// <param name="name"> 
        /// IN: Group over which the iteration is performed.
        /// </param>
        /// <param name="func"> 
        /// IN: Operation to be performed on an object at each step of the
        /// iteration.
        /// </param>
        /// <param name="startIndex"> 
        ///   IN: Location at which to begin the iteration
        /// </param>
        /// <returns>
        /// Returns the return value of the last operator if it was
        /// non-zero, or zero if all group members were processed. 
        /// </returns>
        /// <remarks> 
        /// </remarks>
#pragma endregion documentation

        static int iterate(H5LocId^ loc, System::String^ name, 
            H5GIterateCallback^ func,
            Object^ parameters, int% startIndex);

#pragma region documentation
        /// <summary>
        /// Returns information about an object.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetObjinfo"/>
        /// </summary>
        /// <note>This function is deprecated in favor of the function <c>H5Oget_info</c> and <c>H5Lget_info</c>.</note>
        /// <param name="groupOrFileId">
        /// IN: File or group Id.
        /// </param>
        /// <param name="name"> 
        /// IN: Name of the object for which status is being sought.
        /// </param>
        /// <param name="followLink"> 
        /// IN: If the object is a symbolic link and followLink is false,
        /// then the information returned is that for the link itself;
        /// otherwise the link is followed and information is returned
        /// about the object to which the link points.
        /// </param>
        /// <returns>
        /// The filenumber and objectnumber properties contain two values
        /// each.  Together, these four values uniquely
        /// identify an object among those HDF5 files which are open: if
        /// all four values are the same between two objects, then the two
        /// objects are the same (provided both files are still open).
        /// <ul>
        /// <li>
        /// Note that if a file is closed and re-opened, the value in
        /// fileno will change.
        /// </li>
        /// <li>
        /// If a VFL driver either does not or cannot detect that two
        /// H5Fopen calls referencing the same file actually open the same
        /// file, each will get a different fileno.
        /// </li>
        /// </ul>
        /// <p>
        /// The nHardLinks property is the number of hard links to the
        /// object or zero when information is being returned about a
        /// symbolic link (symbolic links do not have hard links but all
        /// other objects always have at least one).
        /// </p>
        /// <p>
        /// The objectType property contains the type of the object, one of
        /// H5GType.GROUP, H5GType.DATASET, H5GType.LINK, or H5GType.TYPE.
        /// </p>
        /// <p>
        /// The modificationTime property contains the modification time.
        /// </p>
        /// <p>
        /// If information is being returned about a symbolic link then
        /// the linkLength property will be the length of the link value 
        /// (the name of the
        /// pointed-to object with the null terminator); otherwise it
        /// will be zero.
        /// </p>
        /// <p>
        /// The headerSize property is the total size of all the object 
        /// header information in the file (for all chunks).
        /// </p>
        /// <p>
        /// The unusedHeaderSpace property is the size of unused space in
        /// the object header.
        /// </p>
        /// <p>
        /// The nHeaderMessages property is the number of object header
        /// messages.
        /// </p>
        /// <p>
        /// The nHeaderChunks property is the number of chunks the 
        /// object header is broken up into. 
        /// </p>
        /// </returns>
#pragma endregion documentation

        static ObjectInfo^ getObjectInfo(H5LocId^ groupOrFileId, System::String^ name,
            bool followLink);

#pragma region documentation
        ///<summary>
        /// H5Gget_info retrieves information about the group specified by 
        /// group_id. The information is returned in an object of type H5GInfo.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfo"/>
        ///</summary>

        ///<param name="groupId">
        /// IN: Group identifier
        ///</param>

        /// <returns cref="H5GInfo">
        /// H5GInfo
        /// </returns>

        /// <exception cref="H5GgetInfoException">
        /// throws H5GgetInfoException on failure.
        /// </exception>
#pragma endregion documentation

        static H5GInfo^ getInfo(H5GroupId^ groupId);

#pragma region documentation
        ///<summary>
        /// Retrieves information about a file or group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfoByName"/>
        ///</summary>

        ///<param name="fileOrGroup">
        /// IN: File or group identifier
        ///</param>

        /// <returns cref="H5GInfo">
        /// H5GInfo
        /// </returns>

        /// <exception cref="H5GgetInfoByNameException">
        /// throws H5GgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5GInfo^ getInfoByName(H5GroupId^ fileOrGroup);

#pragma region documentation
        ///<summary>
        /// Retrieves information about a file or group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfoByName"/>
        ///</summary>

        ///<param name="fileOrGroup">
        /// IN: File or group identifier
        ///</param>

        ///<param name="groupName">
        /// IN: Name of group for which information is to be retrieved
        ///</param>

        /// <returns cref="H5GInfo">
        /// H5GInfo
        /// </returns>

        /// <exception cref="H5GgetInfoByNameException">
        /// throws H5GgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5GInfo^ getInfoByName(H5FileOrGroupId^ fileOrGroup, 
            System::String^ groupName);

#pragma region documentation
        ///<summary>
        /// Retrieves information about a file or group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfoByName"/>
        ///</summary>

        ///<param name="fileOrGroup">
        /// IN: File or group identifier
        ///</param>

        ///<param name="groupName">
        /// IN: Name of group for which information is to be retrieved
        ///</param>

        ///<param name="linkAccessPropertyList">
        /// IN: Link access property list
        ///</param>

        /// <returns cref="H5GInfo">
        /// H5GInfo
        /// </returns>

        /// <exception cref="H5GgetInfoByNameException">
        /// throws H5GgetInfoByNameException on failure.
        /// </exception>
#pragma endregion documentation

        static H5GInfo^ getInfoByName(
            H5FileOrGroupId^ fileOrGroup, 
            System::String^ groupName, 
            H5PropertyListId^ linkAccessPropertyList);

    private:
        // There is no reason to create instances of this class.
        H5G(){};
    };

    // end of H5File implementation

}// end of namespace HDF5DotNet
