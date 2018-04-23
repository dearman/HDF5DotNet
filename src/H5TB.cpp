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
#include "H5TB.h"
#include "IntPtrAux.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    TableInfo^ H5TB::getTableInfo(H5LocId^ loc, String^ tableName)
    {
        hsize_t nFields, nRecords;

        herr_t status = H5TBget_table_info(loc->Id, tableName, &nFields, 
            &nRecords);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5TB.getTableInfo: \n"
                "  Failed to get table info for{0}, locId: {1:x} with status {2}\n",
                tableName, loc->Id, status);
            throw gcnew H5TBgetTableInfoException(message, status);
        }

        return gcnew TableInfo(
            safe_cast<hssize_t>(nFields), safe_cast<hssize_t>(nRecords));
    }


    // HACK: this is ugly (MAX_FIELD_NAME_LENGTH), but I don't see a better way

    TableFieldInfo^ H5TB::getFieldInfo(H5LocId^ loc, String^ tableName)
    {
        const int MAX_FIELD_NAME_LENGTH = 1024;

        TableInfo^ tableInfo;

        try
        {
            tableInfo = H5TB::getTableInfo(loc, tableName);
        }
        catch(HDFException^ e)
        {
            String^ message = String::Format(
                "H5TB.getFieldInfo: \n"
                "  Failed to get table info for{0}, locId: {1:x} \n"
                "  getFieldInfo failed with status {2}\n",
                tableName, loc->Id, e->ErrorCode);
            throw gcnew H5TBgetFieldInfoException(message, e->ErrorCode);
        }

        if (tableInfo->nFields == 0)
        {
            herr_t status = -1;
            String^ message = String::Format(
                "H5TB.getFieldInfo: \n"
                "  Failed to get table info for{0}, locId: {1:x} \n"
                "  The table has no fields.\n",
                tableName, loc->Id);
            throw gcnew H5TBgetFieldInfoException(message, status);
        }

        // Allocate memory for the field names
        char** fieldName = new char*[safe_cast<size_t>(tableInfo->nFields)];
        for(int i=0;i<tableInfo->nFields;i++)
        {
            fieldName[i] = new char[MAX_FIELD_NAME_LENGTH];
        }

        // Generate arrays for the other table data.
        array<size_t>^ fieldSize
            = gcnew array<size_t>(safe_cast<int>(tableInfo->nFields));
        array<size_t>^ fieldOffset
            = gcnew array<size_t>(safe_cast<int>(tableInfo->nFields));
        array<size_t>^ typeSize
            = gcnew array<size_t>(safe_cast<int>(tableInfo->nFields));

        // Pin the pointers to the array data
        pin_ptr<size_t>  pFieldSize = &fieldSize[0];
        pin_ptr<size_t>  pFieldOffset = &fieldOffset[0];
        pin_ptr<size_t>  pTypeSize = &typeSize[0];

        // Make the call to the "C" function
        herr_t status = H5TBget_field_info( loc->Id, 
            tableName, 
            fieldName, 
            pFieldSize,
            pFieldOffset,
            pTypeSize);

        if (status < 0)
        {
            for(int i=0;i<tableInfo->nFields;i++)
                delete [] fieldName[i];

            delete [] fieldName;

            // Throw an exception
            String^ message = String::Format(
                "H5TB.getFieldInfo: \n"
                "  Failed to get table info for{0}, locId: {1:x} with status {2}\n",
                tableName, loc->Id, status);
            throw gcnew H5TBgetFieldInfoException(message, status);
        }

        // Copy the field names to .NET strings
        array<String^>^ fieldArray
            = gcnew array<String^>(safe_cast<int>(tableInfo->nFields));
        for(int i=0;i<tableInfo->nFields;i++)
        {
            fieldArray[i] = gcnew String(fieldName[i]);

            delete [] fieldName[i];
        }

        delete [] fieldName;

        array<IntPtr>^ fieldSizeIntPtr
            = gcnew array<IntPtr>(safe_cast<int>(tableInfo->nFields));
        array<IntPtr>^ fieldOffsetIntPtr
            = gcnew array<IntPtr>(safe_cast<int>(tableInfo->nFields));
        array<IntPtr>^ typeSizeIntPtr
            = gcnew array<IntPtr>(safe_cast<int>(tableInfo->nFields));

        for (int i = 0; i < tableInfo->nFields; ++i)
        {
            fieldSizeIntPtr[i] = IntPtr((IntPtr::Size == 4) ? safe_cast<Int32>(fieldSize[i]) : safe_cast<Int64>(fieldSize[i]));
            fieldOffsetIntPtr[i] = IntPtr((IntPtr::Size == 4) ? safe_cast<Int32>(fieldOffset[i]) : safe_cast<Int64>(fieldOffset[i]));
            typeSizeIntPtr[i] = IntPtr((IntPtr::Size == 4) ? safe_cast<Int32>(typeSize[i]) : safe_cast<Int64>(typeSize[i]));
        }

        // Return a TableFieldInfo class instance
        return gcnew TableFieldInfo(fieldArray,
            fieldSizeIntPtr,     
            fieldOffsetIntPtr,
            typeSizeIntPtr);
    }
}
