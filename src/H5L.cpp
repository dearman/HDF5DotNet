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

#include "HDFExceptionSubclasses.h"
#include "H5G.h"
#include "H5GInfo.h"
#include "H5GroupId.h"
#include "H5L.h"
#include "H5LinkInfo.h"
#include "H5PropertyListId.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    String^ H5L::getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hssize_t position)
    {
        return getNameByIndex(
            fileOrGroupId,
            groupName,
            indexType,
            iterationOrder,
            safe_cast<hsize_t>(position));
    }

    String^ H5L::getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hsize_t position)
    {
        return H5L::getNameByIndex(
            fileOrGroupId,
            groupName,
            indexType,
            iterationOrder,
            position,
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    String^ H5L::getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hssize_t position,
        H5PropertyListId^ linkAccessPropertyList)
    {
        return getNameByIndex(
            fileOrGroupId,
            groupName,
            indexType,
            iterationOrder,
            safe_cast<hsize_t>(position),
            linkAccessPropertyList);
    }

    String^ H5L::getNameByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hsize_t position,
        H5PropertyListId^ linkAccessPropertyList)
    {
        ssize_t nameLength = H5Lget_name_by_idx(
            fileOrGroupId->Id,
            groupName, 
            static_cast<int>(indexType),
            static_cast<int>(iterationOrder),
            position,
            NULL,
            0,	 
            linkAccessPropertyList->Id);

        array<char>^ name;

        if (nameLength > 0)
        {
            name = gcnew array<char>(safe_cast<int>(nameLength+1));
            pin_ptr<char> namePtr = &name[0];
            nameLength = H5Lget_name_by_idx(
                fileOrGroupId->Id,
                groupName, 
                static_cast<int>(indexType),
                static_cast<int>(iterationOrder),
                position,
                namePtr,
                safe_cast<size_t>(nameLength+1),	 
                linkAccessPropertyList->Id);
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5L.getNameByIndex: \n"
                "  Failed to find name for position {0} of object id {1:x}"
                "  group {2} with status {3}", 
                position, fileOrGroupId->Id, groupName, nameLength);
            throw gcnew H5LgetNameByIndexException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

    H5IterationResult H5L::iterate(H5GroupId^ groupId,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hssize_t% index,
        H5LIterateCallback^ func,
        Object^ objData)
    {
        return iterate(
            groupId,
            indexType,
            iterationOrder,
            safe_cast<hsize_t% >(index),
            func,
            objData);
    }

    H5IterationResult H5L::iterate(H5GroupId^ groupId,
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hsize_t% index,
        H5LIterateCallback^ func,
        Object^ objData)
    {

        H5IterationResult result = H5IterationResult::SUCCESS;

        H5GInfo^ objectInfo = H5G::getInfo(groupId);
        hsize_t nLinks = safe_cast<hsize_t>(objectInfo->nLinks);

        while((index < nLinks) && (result == H5IterationResult::SUCCESS))
        {
            String^ groupName = 
                H5L::getNameByIndex( groupId, ".", indexType, 
                iterationOrder, index);

            H5LinkInfo^ linkInfo = 
                H5L::getInfoByIndex(groupId, ".", indexType, 
                iterationOrder, index);

            result = func(groupId, groupName, linkInfo, objData);

            ++index;
        }

        return result;
    }

    H5LinkInfo^ H5L::getInfo(
        H5FileOrGroupId^ fileOrGroupId) 
    {
        return H5L::getInfo(
            fileOrGroupId, ".", gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5LinkInfo^ H5L::getInfo(
        H5FileOrGroupId^ fileOrGroupId, 
        String^ groupName)
    {
        return H5L::getInfo(
            fileOrGroupId, groupName, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5LinkInfo^ H5L::getInfo(
        H5FileOrGroupId^ fileOrGroupId, 
        String^ groupName,
        H5PropertyListId^ linkAccessPropertyListId)
    {
        H5L_info_t nativeInfo;

        herr_t status = H5Lget_info(fileOrGroupId->Id, groupName, &nativeInfo, 
            linkAccessPropertyListId->Id);

        // Check for error status (so we can throw an exception)
        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getInfo:\n"
                " Failed to get info for group {0}, group id {1:x}"
                " with status {2}", groupName, fileOrGroupId->Id, status);

            throw gcnew H5LgetInfoException(message, status);
        }

        // Success - Copy the information to a reference class and return
        return gcnew H5LinkInfo(nativeInfo);

    }

    H5LinkInfo^ H5L::getInfoByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hssize_t position)
    {
        return getInfoByIndex(
            fileOrGroupId,
            groupName,
            indexType,
            iterationOrder,
            safe_cast<hsize_t>(position)); 
    }


    H5LinkInfo^ H5L::getInfoByIndex(H5FileOrGroupId^ fileOrGroupId,
        String^ groupName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hsize_t position)
    {
        H5L_info_t nativeInfo;


        herr_t status = H5Lget_info_by_idx(
            fileOrGroupId->Id, 
            groupName,
            safe_cast<H5_index_t>(indexType), 
            safe_cast<H5_iter_order_t>(iterationOrder),
            position,
            &nativeInfo,
            0);

        // Check for error status (so we can throw an exception)
        if (status < 0)
        {
            String^ message = String::Format(
                "H5L.getInfoByIndex:\n"
                " Object Id: {0:x} failed to return link information"
                " with status {1}", fileOrGroupId->Id, status);

            throw gcnew H5LgetInfoByIndexException(message, status);
        }

        // Success - Copy the information to a reference class and return
        return gcnew H5LinkInfo(nativeInfo);
    }

    IntPtr H5L::get_val
        (
        H5FileOrGroupId^ fileOrGroupId,
        String^ linkName,
        H5PropertyListId^ linkAccessPropertyList
        )
    {
        IntPtr result = IntPtr::Zero;

        H5L_info_t info;

        herr_t status = H5Lget_info(fileOrGroupId->Id, linkName, &info, linkAccessPropertyList->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.getInfo:\n"
                " Failed to get info for group {0}, group id {1:x}"
                " with status {2}", linkName, fileOrGroupId->Id, status);

            throw gcnew H5LgetInfoException(message, status);
        }

        size_t size = info.u.val_size;
        result = Marshal::AllocHGlobal(safe_cast<int>(size));
        status = H5Lget_val(fileOrGroupId->Id, linkName, result.ToPointer(), size, linkAccessPropertyList->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5G.get_val:\n"
                " Failed to get value for link {0}, loc. id {1:x}"
                " with status {2}", linkName, fileOrGroupId->Id, status);

            throw gcnew HDFException(message, status);
        }

        return result;
    }

    void H5L::createHardLink
       (
       H5FileOrGroupId^ objLoc,
       String^          objName,
       H5FileOrGroupId^ linkLoc,
       String^          linkName
       )
   {
       H5PropertyListId^ plist = gcnew H5PropertyListId(H5P::Template::DEFAULT);

       herr_t status = H5Lcreate_hard(
           objLoc->Id, objName, linkLoc->Id, linkName, plist->Id, plist->Id);
       if (status < 0)
        {
            String^ message = String::Format(
                "H5L.createHardLink:\n"
                " Failed to create hard link {0}, at location id {1:x}"
                " to {2}, at location id {3:x}"
                " with status {4}", linkName, linkLoc->Id, objName, objLoc->Id, status);
            throw gcnew HDFException(message, status);
        }
   }

    void H5L::Delete
        (
        H5FileOrGroupId^ linkLocRef,
        String^          linkName
        )
    {
        H5PropertyListId^ plist = gcnew H5PropertyListId(H5P::Template::DEFAULT);
        herr_t status = H5Ldelete(linkLocRef->Id, linkName, plist->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5L.Delete:\n"
                " Failed to delete link {0}, at location id {1:x}"
                " with status {2}", linkName, linkLocRef->Id, status);
            throw gcnew HDFException(message, status);
        }
    }

    bool H5L::Exists
        (
        H5FileOrGroupId^ locRef,
        String^  name
        )
    {
        H5PropertyListId^ plist = gcnew H5PropertyListId(H5P::Template::DEFAULT);
        htri_t status = H5Lexists(locRef->Id, name, plist->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5L.Exists:\n"
                " Failed test existence of link {0}, at location id {1:x}"
                " with status {2}", name, locRef->Id, status);
            throw gcnew HDFException(message, status);
        }
        return (status == 1) ? true : false;
    }

    H5L::H5L() {}

}
