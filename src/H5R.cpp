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

#include "H5DataSetId.h"
#include "H5DataSpaceId.h"
#include "H5I.h"
#include "H5R.h"
#include "HDFException.h"
#include "ObjectReference.h"
#include "RegionReference.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

#include "HDF5_Native.h"

namespace HDF5DotNet
{

    RegionReference^ H5R::createRegionReference
        (
        H5ObjectWithAttributes^ locId,
        String^                 name,
        H5DataSpaceId^          spaceId
        )
    {
        array<Byte>^ a = gcnew array<Byte>(RegionReference::SizeInBytes);
        pin_ptr<Byte> ptr = &a[0];
        herr_t status = H5Rcreate(ptr, locId->Id, name, H5R_DATASET_REGION, spaceId->Id);
        
        if (status < 0)
        {
            String^ message = String::Format(
                "H5R.createRegionReference:\n"
                "  Object Id: {0:x} region reference creation {1} failed "
                " with status {2}", locId->Id, name, status);
            throw gcnew HDFException(message, status);
        }
        
        return gcnew RegionReference(a);
    }

    ObjectReference^ H5R::createObjectReference
        (
        H5ObjectWithAttributes^ locId,
        String^                 name
        )
    {
        array<Byte>^ a = gcnew array<Byte>(ObjectReference::SizeInBytes);
        pin_ptr<Byte> ptr = &a[0];
        herr_t status = H5Rcreate(ptr, locId->Id, name, H5R_OBJECT, -1);
        
        if (status < 0)
        {
            String^ message = String::Format(
                "H5R.createObjectReference:\n"
                "  Object Id: {0:x} object reference creation {1} failed "
                " with status {2}", locId->Id, name, status);
            throw gcnew HDFException(message, status);
        }
        
        return gcnew ObjectReference(a);
    }

    String^ H5R::getName
        (
        H5ObjectWithAttributes^ locId,
        ReferenceType           refType,
        IReference^             ref
        )
    {
        array<Byte>^ a = ref->ToByteArray();
        pin_ptr<Byte> ptr = &a[0];

        ssize_t nameLength = H5Rget_name(
            locId->Id, safe_cast<H5R_type_t>(refType), ptr, NULL, 0);

        array<char>^ name;

        if (nameLength > 0)
        {
            name = gcnew array<char>(safe_cast<int>(nameLength+1));
            pin_ptr<char> namePtr = &name[0];
            nameLength = H5Rget_name(
                locId->Id, safe_cast<H5R_type_t>(refType), ptr,
                namePtr, safe_cast<size_t>(nameLength+1));
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5R.getName:\n"
                "  Object Id: {0:x} name retrieval for reference of type {1} failed "
                " with status {2}", locId->Id, refType, nameLength);
            throw gcnew HDFException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

    
    H5ObjectWithAttributes^ H5R::dereference
        (
        H5ObjectWithAttributes^ objId,
        ReferenceType           refType,
        IReference^             ref
        )
    {
        array<Byte>^ a = ref->ToByteArray();
        pin_ptr<Byte> ptr = &a[0];
        hid_t status = H5Rdereference(objId->Id, safe_cast<H5R_type_t>(refType), ptr);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5R.dereference:\n"
                "  Object Id: {0:x} dereference of reference type {1} failed "
                " with status {2}", objId->Id, refType, status);
            throw gcnew HDFException(message, status);
        }

        if (safe_cast<H5I::IdentifierType>(H5Iget_type(status)) != H5I::IdentifierType::DATASET)
        {
            throw gcnew HDFException("H5R.dereference currently supports only datasets.\n", -1);
        }

        return gcnew H5DataSetId(status);
    }

    H5DataSpaceId^ H5R::getRegion
        (
        H5ObjectWithAttributes^ locId,
        RegionReference^        ref
        )
    {
        array<Byte>^ a = ref->ToByteArray();
        pin_ptr<Byte> ptr = &a[0];
        hid_t status = H5Rget_region(locId->Id, H5R_DATASET_REGION, ptr);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5R.getRegion:\n"
                "  Location Id: {0:x} get region failed "
                " with status {1}", locId->Id, status);
            throw gcnew HDFException(message, status);
        }

        return gcnew H5DataSpaceId(status);
    }

    H5O::ObjectType H5R::getObjectType
        (
        H5ObjectWithAttributes^ locId,
        ObjectReference^        ref
        )
    {
        array<Byte>^ a = ref->ToByteArray();
        pin_ptr<Byte> ptr = &a[0];
        H5O_type_t otype = H5O_TYPE_UNKNOWN;

        herr_t status = H5Rget_obj_type2(locId->Id, H5R_OBJECT, ptr, &otype);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5R.getObjectType:\n"
                " Location Id: {0:x} get object type for object reference failed "
                " with status {1}", locId->Id, status);
            throw gcnew HDFException(message, status);
        }
    
        return safe_cast<H5O::ObjectType>(otype);
    }

}
