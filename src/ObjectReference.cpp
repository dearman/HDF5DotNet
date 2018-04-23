/* * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group (THG).                                       *
 * All rights reserved.                                                    *
 *                                                                         *
 * This file is part of HDF5. The full HDF5 copyright notice, including    *
 * terms governing use, modification, and redistribution, is contained in  *
 * the files COPYING and Copyright.html. COPYING can be found at the root  *
 * of the source code distribution tree; Copyright.html can be found at the*
 * root level of an installed copy of the electronic HDF5 document set and *
 * is linked from the top-level documents page. It can also be found at    *
 * http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have     *
 * access to either file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ObjectReference.h"

using namespace System;

namespace HDF5DotNet
{

    ObjectReference::ObjectReference()
    {
        m_or = gcnew array<Byte>(H5R_OBJ_REF_BUF_SIZE);
    }

    ObjectReference::ObjectReference(array<Byte>^ a)
    {
        m_or = gcnew array<Byte>(H5R_OBJ_REF_BUF_SIZE);
        Array::Copy(a, m_or, H5R_OBJ_REF_BUF_SIZE);
    }

    array<Byte>^ ObjectReference::ToByteArray()
    {
        array<Byte>^ result = gcnew array<Byte>(m_or->Length);
        Array::Copy(m_or, result, m_or->Length);
        return result;
    }

}