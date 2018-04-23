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

#include "H5O.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{

    H5ObjectInfo^ H5O::getInfoByName( H5Id^ objectId)
    {
        return H5O::getInfoByName(objectId, ".", gcnew H5PropertyListId(0));
    }


    H5ObjectInfo^ H5O::getInfoByName( H5Id^ objectId, String^ name) 
    {
        return H5O::getInfoByName(objectId, name, gcnew H5PropertyListId(0));
    }

    H5ObjectInfo^ H5O::getInfoByName(
        H5Id^ objectId,
        String^ name, 
        H5PropertyListId^ linkAccessPropertyListId)
    {
        H5O_info_t nativeInfo;

        herr_t status = H5Oget_info_by_name(objectId->Id, name, &nativeInfo, 
            linkAccessPropertyListId->Id);

        // Check for error status (so we can throw an exception)
        if (status < 0)
        {
            String^ message = String::Format(
                "H5O.getInfoByName:\n"
                " Object Id: {0:x} failed to return object information"
                " with status {1}", objectId->Id, status);


            throw gcnew H5OgetInfoByNameException(message, status);
        }

        // Success - Copy the information to a reference class and return
        return gcnew H5ObjectInfo(nativeInfo);
    }

    H5ObjectInfo^ H5O::getInfoByIndex(H5LocId^ locId,
        String^ groupName, 
        H5IndexType index,
        H5IterationOrder iterationOrder,
        hssize_t position)
    {
        return getInfoByIndex(
            locId, groupName, index, iterationOrder, safe_cast<hsize_t>(position));
    }

    H5ObjectInfo^ H5O::getInfoByIndex(H5LocId^ locId,
        String^ groupName, 
        H5IndexType index,
        H5IterationOrder iterationOrder,
        hsize_t position)
    {
        return
            H5O::getInfoByIndex(locId, groupName, index, iterationOrder,
                position, gcnew H5PropertyListId(0));
    }

    H5ObjectInfo^ H5O::getInfoByIndex(
        H5LocId^ locId,
        String^ groupName, 
        H5IndexType index,
        H5IterationOrder iterationOrder,
        hssize_t position,
        H5PropertyListId^ linkAccessPropertyListId
        )
    {
        return getInfoByIndex(
            locId, groupName, index, iterationOrder, safe_cast<hsize_t>(position),
            linkAccessPropertyListId);
    }

    H5ObjectInfo^ H5O::getInfoByIndex(
        H5LocId^ locId,
        String^ groupName, 
        H5IndexType index,
        H5IterationOrder iterationOrder,
        hsize_t position,
        H5PropertyListId^ linkAccessPropertyListId
        )
    {
        H5O_info_t nativeInfo;

        // Call "C" routine.
        herr_t status = H5Oget_info_by_idx(locId->Id, 
            groupName,
            safe_cast<H5_index_t>(index),
            safe_cast<H5_iter_order_t>(iterationOrder),
            position,
            &nativeInfo,
            linkAccessPropertyListId->Id);

        // Check for error status (so we can throw an exception)
        if (status < 0)
        {
            String^ message = String::Format(
                "H5O.getInfoByIndex:\n"
                " Object Id: {0:x} failed to return object information"
                " with status {1}", locId->Id, status);


            throw gcnew H5OgetInfoByIndexException(message, status);
        }

        // Success - Copy the information to a reference class and return
        return gcnew H5ObjectInfo(nativeInfo);
    }

    H5ObjectInfo^ H5O::getInfo(H5Id^ locId)
    {
        H5O_info_t nativeInfo;

        // Call "C" routine.
        herr_t status = H5Oget_info(locId->Id, 
            &nativeInfo);

        // Check for error status (so we can throw an exception)
        if (status < 0)
        {
            String^ message = String::Format(
                "H5O.getInfo:\n"
                " Object Id: {0:x} failed to return object information"
                " with status {1}", locId->Id, status);


            throw gcnew H5OgetInfoException(message, status);
        }

        // Success - Copy the information to a reference class and return
        return gcnew H5ObjectInfo(nativeInfo);
    }


    // Convert to .NET DateTime from Unix time.
    DateTime^ fromUnixTime(time_t secondsSinceJan1)
    {
        int unixStartMonth = 1;
        int unixStartDay = 1;
        int unixStartYear = 1970;
        int unixHour = 0;
        int unixMinute = 0;
        int unixSecond = 0;

        DateTime^ unixStartDate = 
            gcnew DateTime(unixStartYear, unixStartMonth, unixStartDay,
            unixHour, unixMinute, unixSecond);

        return unixStartDate->AddSeconds(
            static_cast<double>(secondsSinceJan1));
    }

 

    H5O::H5O() {};
}
