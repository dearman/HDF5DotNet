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
// This is the main DLL file.

#include "H5G.h"
#include "H5GroupId.h"
#include "H5P.h"
#include "H5PropertyListId.h"
#include "HDFExceptionSubclasses.h"
#include "ObjectInfo.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    H5GInfo::H5GInfo(H5G_info_t% info)
        : linkStorageType_(safe_cast<H5GStorageType>(info.storage_type)),
        nLinks_(safe_cast<hsize_t>(info.nlinks)),
        maxCreationOrder_(safe_cast<hsize_t>(info.max_corder))
    {
    }

    H5GInfo^ H5G::getInfo(H5GroupId^ groupId)
    {
        H5G_info_t info;
        herr_t status = H5Gget_info(groupId->Id, &info);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getInfo:\n"
                "  Group Id: {0:x} failed to return info"
                " with status {1}", groupId->Id, status);
            throw gcnew H5GgetInfoException(message, status);

        }

        return(gcnew H5GInfo(info));
    }

    H5GInfo^ H5G::getInfoByName(H5GroupId^ groupId)
    {
        return H5G::getInfoByName(groupId, ".", 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5GInfo^ H5G::getInfoByName(H5FileOrGroupId^ groupId, String^ groupName)
    {
        return H5G::getInfoByName(groupId, groupName, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5GInfo^ H5G::getInfoByName(H5FileOrGroupId^ groupId, String^ groupName, 
        H5PropertyListId^ linkAccessPropertyList)
    {
        H5G_info_t info;
        herr_t status = H5Gget_info_by_name(groupId->Id, groupName, &info, 
            linkAccessPropertyList->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getInfoByName:\n"
                "  Group Id: {0:x} failed to return info"
                " with status {1}", groupId->Id, status);
            throw gcnew H5GgetInfoByNameException(message, status);

        }

        return(gcnew H5GInfo(info));
    }


    // Implementation of HDFfile member functions
    H5GroupId^ H5G::create(H5LocId^ groupOrFileId, String^ groupName) 
    {
        // Call an overloaded version that takes all parameters.
        return H5G::create(groupOrFileId, groupName,
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5GroupId^ H5G::create(H5LocId^ groupOrFileId, 
        String^ groupName,
        H5PropertyListId^ linkCreation,
        H5PropertyListId^ groupCreation,
        H5PropertyListId^ groupAccess)
    {
        // Call "C" routine.
        hid_t id = H5Gcreate2(groupOrFileId->Id, 
            groupName, 
            linkCreation->Id,
            groupCreation->Id,
            groupAccess->Id);

        // Check for error status (so we can throw an exception)
        if (id < 0)
        {
            String^ message = String::Format(
                "H5G.create:\n"
                "  File Id: {0:x} failed to create groupname {1}"
                " with status {2}", groupOrFileId->Id, groupName, id);
            throw gcnew H5GcreateException(message, id);
        }

        // Success - return a new group id.
        return gcnew H5GroupId(id);
    }

    H5GroupId^ H5G::open(H5LocId^ groupOrFileId, String^ groupName)
    {
        return H5G::open(groupOrFileId, groupName, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }


    // Open a group
    H5GroupId^ H5G::open(H5LocId^ groupOrFileId, String^ groupName,
        H5PropertyListId^ groupAccessPropertyListId)
    {
        // Call "C" routine.
        hid_t id = H5Gopen2(groupOrFileId->Id, groupName, 
            groupAccessPropertyListId->Id);

        // Check for error status (so we can throw an exception)
        if (id < 0)
        {
            String^ message = String::Format(
                "H5G.open:\n"
                "  File Id: {0:x} failed to open groupname {1} "
                "with status {2}", groupOrFileId->Id, groupName, id);
            throw gcnew H5GopenException(message, id);
        }

        // Success - return a new group id.
        return gcnew H5GroupId(id);
    }

    // Close a group
    void H5G::close(H5GroupId^ groupId)
    {
        herr_t status  = H5Gclose(groupId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.close: \n"
                "  Failed to close group Id: {0:x} with status {1}", 
                groupId->Id, status);
            throw gcnew H5GcloseException(message, status);
        }
    }

    hssize_t H5G::getNumObjects(H5GroupId^ groupId)
    {
        hsize_t nObjects;

        herr_t status  = H5Gget_num_objs(groupId->Id, &nObjects);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getNumberObjects: \n"
                "  Failed to find number of object: {0:x} with status {1}", 
                groupId->Id, status);
            throw gcnew H5GgetNumObjectsException(message, status);
        }

        return safe_cast<hssize_t>(nObjects);
    }

    String^ H5G::getObjectNameByIndex(H5GroupId^ groupId, hsize_t objectIndex)
    {
        // Find the number of characters in the object name.
        ssize_t nameLength = H5Gget_objname_by_idx(groupId->Id, 
            objectIndex, NULL, 0);

        array<char>^ name;

        if (nameLength > 0)
        {
            // Allocate enough memory to hold the name.
            name = gcnew array<char>(safe_cast<int>(nameLength+1));

            // Pin the array in place
            pin_ptr<char> namePtr = &name[0];

            // Request the name
            nameLength = H5Gget_objname_by_idx(groupId->Id, 
                objectIndex, 
                namePtr, 
                safe_cast<size_t>(nameLength+1));
        }

        // Test again because nameLength can be reset in the previous
        // if-statement.
        if (nameLength <= 0)
        {
            String^ message = String::Format(
                "H5G.getObjectNameByIndex: \n"
                "  Failed to find name of object in group {0:x} with index {1}", 
                groupId->Id, objectIndex);
            throw gcnew H5GgetObjectNameByIndexException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); i++) wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));

    }

    ObjectInfo^ H5G::getObjectInfo(H5LocId^ loc, String^ name,
        bool followLink)
    {
        // Set the hbool_t data type to true or false depending on the
        // bool value followLink
        hbool_t bfollowLink = safe_cast<hbool_t>((followLink) ? 1 : 0);

        H5G_stat_t info;

        herr_t status = H5Gget_objinfo( loc->Id, name, bfollowLink, &info);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getObjectInfo: \n"
                "  Failed to get info for name \"{0}\" in object {1:x}", 
                name, loc->Id);
            throw gcnew H5GgetObjInfoException(message, status);
        }

        return gcnew ObjectInfo(info);
    }


    int H5G::iterate(H5LocId^ loc, String^ name, 
        H5GIterateCallback^ func,
        Object^ parameters, int% startIndex)
    {
        // Get the number of objects in the interation.

        // Open specified group
        H5GroupId^ group = H5G::open(loc, name);

        hssize_t nObjects = H5G::getNumObjects(group);

        // Iterate until we have visited all objects or delegate returns
        // non-zero status.
        int status = 0;
        for(;(status == 0) && (startIndex<nObjects);startIndex++)
        {
            // Find the name of the ith object
            String^ objectName = H5G::getObjectNameByIndex(group, safe_cast<size_t>(startIndex));

            // Invoke the delegate
            status = func->Invoke(group, objectName, parameters);
        }

        // Close the iteration group.
        H5G::close(group);


        // return the index number
        return status;
    }

    /// Copy the information from a H5G_stat_t to an ObjectInfo class.
    ObjectInfo::ObjectInfo(H5G_stat_t% stats):
    nlink_(safe_cast<int>(stats.nlink)), type_(safe_cast<H5GType>(stats.type)), 
        mtime_(stats.mtime), linklen_(stats.linklen), size_(safe_cast<hssize_t>(stats.ohdr.size)), 
        free_(safe_cast<hssize_t>(stats.ohdr.free)), nmesgs_(safe_cast<int>(stats.ohdr.nmesgs)), 
        nchunks_(safe_cast<int>(stats.ohdr.nchunks))
    {
        fileno_ = 
            gcnew array<hssize_t>(2) { safe_cast<hssize_t>(stats.fileno[0]), safe_cast<hssize_t>(stats.fileno[1]) };

        objno_ = 
            gcnew array<hssize_t>(2) { safe_cast<hssize_t>(stats.objno[0]), safe_cast<hssize_t>(stats.objno[1]) };
    }

}// end of namespace HDF5dotNET
