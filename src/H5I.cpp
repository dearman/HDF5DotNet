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

#include "H5I.h"
#include "HDFException.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    H5I::IdentifierType H5I::getIdentifierType
        (
        H5Id^ id
        )
    {
        return safe_cast<H5I::IdentifierType>(H5Iget_type(id->Id));
    }

    String^ H5I::getName(H5Id^ objId)
    {
        ssize_t nameLength = H5Iget_name(objId->Id, NULL, 0);

        array<char>^ name;

        if (nameLength > 0)
        {
            name = gcnew array<char>(safe_cast<int>(nameLength+1));
            pin_ptr<char> namePtr = &name[0];
            nameLength = H5Iget_name(objId->Id, namePtr,
                safe_cast<size_t>(nameLength+1));
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5I.getName:\n"
                "  Object Id: {0:x} name retrieval failed "
                " with status {1}", objId->Id, nameLength);
            throw gcnew HDFException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

}
