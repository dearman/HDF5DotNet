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

#include "H5Array.h"
#include "H5DataTypeId.h"
#include "H5Memory.h"
#include "H5P.h"
#include "H5PropertyListId.h"
#include "HDFExceptionSubclasses.h"
#include "IntPtrAux.h"

#include "H5Dpublic.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{

    // Implementation of HDFfile member functions
    H5PropertyListId^ H5P::create(H5P::PropertyListClass listClass)
    {
        // Find the real classType value

        hid_t classId = -1;

        switch(listClass)
        {
        case H5P::PropertyListClass::FILE_CREATE: 
            classId = H5P_CLS_FILE_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::ROOT:
            classId = H5P_CLS_ROOT_ID_g;
            break;

        case H5P::PropertyListClass::OBJECT_CREATE:
            classId = H5P_CLS_OBJECT_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::FILE_ACCESS:
            classId = H5P_CLS_FILE_ACCESS_ID_g;
            break;

        case H5P::PropertyListClass::DATASET_CREATE:
            classId = H5P_CLS_DATASET_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::DATASET_ACCESS:
            classId = H5P_CLS_DATASET_ACCESS_ID_g;
            break;

        case H5P::PropertyListClass::DATASET_XFER:
            classId = H5P_CLS_DATASET_XFER_ID_g;
            break;

        case H5P::PropertyListClass::FILE_MOUNT:
            classId = H5P_CLS_FILE_MOUNT_ID_g;
            break;

        case H5P::PropertyListClass::GROUP_CREATE:
            classId = H5P_CLS_GROUP_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::GROUP_ACCESS:
            classId = H5P_CLS_GROUP_ACCESS_ID_g;
            break;

        case H5P::PropertyListClass::DATATYPE_CREATE:
            classId = H5P_CLS_DATATYPE_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::DATATYPE_ACCESS:
            classId = H5P_CLS_DATATYPE_ACCESS_ID_g;
            break;

        case H5P::PropertyListClass::STRING_CREATE:
            classId = H5P_CLS_STRING_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::ATTRIBUTE_CREATE:
            classId = H5P_CLS_ATTRIBUTE_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::OBJECT_COPY:
            classId = H5P_CLS_OBJECT_COPY_ID_g;
            break;

        case H5P::PropertyListClass::LINK_CREATE:
            classId = H5P_CLS_LINK_CREATE_ID_g;
            break;

        case H5P::PropertyListClass::LINK_ACCESS:
            classId = H5P_CLS_LINK_ACCESS_ID_g;
            break;
        }

        // Call "C" routine.
        hid_t id = H5Pcreate(static_cast<int>(classId));

        // Check for error status (so we can throw an exception)
        if (id < 0)
        {
            String^ message = String::Format(
                "H5P.create:\n"
                "  failed to create property list of type {0}"
                " with status {1}", listClass, id);
            throw gcnew H5PcreateException(message, id);
        }

        // Success - return a new group id.
        return gcnew H5PropertyListId(id);
    }

    void H5P::close(H5PropertyListId^ id)
    {
        herr_t status = H5Pclose(id->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.close:\n"
                "  failed to close "
                " with status {0}", status);
            throw gcnew H5PcloseException(message, status);
        }
    }

    array<hssize_t>^ H5P::getChunk(H5PropertyListId^ id, int maxNDims)
    {
        array<hsize_t>^ a = gcnew array<hsize_t>(maxNDims);
        pin_ptr<hsize_t> pptr = &a[0];
        hsize_t* ptr = pptr;

        int status = H5Pget_chunk(id->Id, maxNDims, ptr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.getChunk:\n"
                "  failed to get chunk size "
                " with status {0}", status);
            throw gcnew H5PgetChunkException(message, status);
        }

        array<hssize_t>^ result = gcnew array<hssize_t>(a->Length);
        for (int i = 0; i < a->Length; ++i)
            result[i] = safe_cast<hssize_t>(a[i]);

        return result;
    }

    void H5P::setChunk(H5PropertyListId^ id, array<hssize_t>^ dimensions)
    {
        array<hsize_t>^ a = gcnew array<hsize_t>(dimensions->Length);
        for (int i = 0; i < a->Length; ++i)
            a[i] = safe_cast<hsize_t>(dimensions[i]);

        pin_ptr<hsize_t> pptr = &a[0];
        hsize_t* ptr = pptr;

        herr_t status = H5Pset_chunk(id->Id, dimensions->Length, ptr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setChunk:\n"
                "  failed to set chunk "
                " with status {0}", status);
            throw gcnew H5PsetChunkException(message, status);
        }
    }

    void H5P::setDeflate(H5PropertyListId^ id, int level)
    {
        return setDeflate(id, safe_cast<unsigned int>(level));
    }

    void H5P::setDeflate(H5PropertyListId^ id, unsigned int level)
    {
        herr_t status = H5Pset_deflate(id->Id, level);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setDeflate:\n"
                "  failed to set deflate "
                " with status {0}", status);
            throw gcnew H5PsetDeflateException(message, status);
        }
    }

    void H5P::setBuffer(H5PropertyListId^ id,
        H5Memory^ typeConversionBuffer,
        H5Memory^ backgroundBuffer)
    {    
        size_t typeConversionBufferSize = IntPtrAux::ToSize_t(typeConversionBuffer->Size);
        size_t backgroundBufferSize = IntPtrAux::ToSize_t(backgroundBuffer->Size);
        size_t bufferSize;

        if ((IntPtrAux::ToSize_t(typeConversionBuffer->Size) == 0) ||
            (IntPtrAux::ToSize_t(backgroundBuffer->Size) == 0))
        {
            // If one or both buffers is null, the buffer size is the larger
            // of the two.
            bufferSize = (typeConversionBufferSize > 
                backgroundBufferSize) ? typeConversionBufferSize :
                backgroundBufferSize;
        }
        else
        {
            // If neither buffer is null, bufferSize is the smaller of the two.
            bufferSize = (typeConversionBufferSize < 
                backgroundBufferSize) ? typeConversionBufferSize :
                backgroundBufferSize;

        }

        H5P::setBuffer(id, 
            safe_cast<hssize_t>(bufferSize),
            typeConversionBuffer->Pointer,
            backgroundBuffer->Pointer);
    }

    void H5P::setBuffer(H5PropertyListId^ id,
        hssize_t bufferSize,
        IntPtr typeConversionBuffer,
        IntPtr backgroundBuffer)
    {
        herr_t status = H5Pset_buffer(id->Id, safe_cast<hsize_t>(bufferSize), 
            typeConversionBuffer,
            backgroundBuffer);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setBuffer:\n"
                "  failed to set buffer of size {0} "
                " with status {1}", bufferSize, status);
            throw gcnew H5PsetBufferException(message, status);
        }
    }

    H5D::Layout H5P::getLayout(H5PropertyListId^ id)
    {
        herr_t status = H5Pget_layout(id->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.getLayout:\n"
                "  failed to get dataset layout for property list id: {0:x} "
                " with status {1}", id->Id, status);
            throw gcnew H5PgetLayoutException(message, status);
        }

        return safe_cast<H5D::Layout>(status);
    }

    void H5P::setVlenMemManager(H5PropertyListId^ plistId,
        H5AllocCallback^ allocCallback,
        IntPtr allocInfo,
        H5FreeCallback^ freeCallback,
        IntPtr freeInfo)
    {
        herr_t status = H5Pset_vlen_mem_manager(
            plistId->Id,
            allocCallback,
            allocInfo,
            freeCallback,
            freeInfo);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setVlenMemManager:\n"
                "  failed to set memory manager for property list id: {0:x} "
                " with status {1}", plistId->Id, status);
            throw gcnew H5PsetVlenMemManagerException(message, status);
        }

        // Hold handles to the delegates so that they are sure to survive
        // garbage collection even if the user's instances are deleted.
        plistId->setAllocCallback(allocCallback);
        plistId->setFreeCallback(freeCallback);
    }

    void H5P::setDataTransform(H5PropertyListId^ plistId,
        System::String^ expression)
    {
        herr_t status = H5Pset_data_transform(plistId->Id, expression);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setDataTransform:\n"
                "  failed to set data transform for property list id: {0:x} "
                " with status {1}", plistId->Id, status);
            throw gcnew HDFException(message, status);
        }
    }

    String^ H5P::getDataTransform(H5PropertyListId^ plistId)
    {
        ssize_t nameLength = H5Pget_data_transform(plistId->Id, NULL, 0);

        array<char>^ name;

        if (nameLength > 0)
        {
            name = gcnew array<char>(safe_cast<int>(nameLength+1));
            pin_ptr<char> namePtr = &name[0];
            nameLength = H5Pget_data_transform(plistId->Id, namePtr,
                safe_cast<size_t>(nameLength+1));
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5P.getDataTransform:\n"
                "Failed to get data transformation from"
                " property list Id {0:x} with status {1}\n",
                plistId->Id, nameLength);
            throw gcnew
                HDFException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

    void H5P::SetIntermediateGroupCreation
        (
        H5PropertyListId^ plistId,
        bool flag
        )
    {
        unsigned int crt_intermed_group = safe_cast<unsigned int>((flag) ? 1 : 0);
        herr_t status = H5Pset_create_intermediate_group(plistId->Id, crt_intermed_group);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.SetIntermediateGroupCreation:\n"
                "  failed for property list id: {0:x} "
                " with status {1}", plistId->Id, status);
            throw gcnew HDFException(message, status);
        }
    }

    void H5P::SetLinkCreationOrder
        (
        H5PropertyListId^ plistId,
        bool indexed
        )
    {
        unsigned int set_link_creation_order = H5P_CRT_ORDER_TRACKED;
        if (indexed) {
            set_link_creation_order |= H5P_CRT_ORDER_INDEXED;
        }

        herr_t status = H5Pset_link_creation_order(plistId->Id, set_link_creation_order);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.SetLinkCreationOrder:\n"
                "  failed for property list id: {0:x} "
                " with status {1}", plistId->Id, status);
            throw gcnew HDFException(message, status);
        }
    }

    generic <class Type>
    void H5P::setFillValue
        (
        H5PropertyListId^ plistId,
        H5DataTypeId^     typeId,
        Type              value
        )
    {
        pin_ptr<Type> ptr = &value;
        herr_t status = H5Pset_fill_value(plistId->Id, typeId->Id, ptr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5P.setFillValue:\n"
                "  failed for property list id: {0:x} "
                "  type id: {1:x} "
                " with status {2}", plistId->Id, typeId->Id, status);
            throw gcnew HDFException(message, status);
        }
    }

}// end of namespace HDF5DotNet
