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

#include "RegionReference.h"

using namespace System;

namespace HDF5DotNet
{

    RegionReference::RegionReference()
    {
        m_rr = gcnew array<Byte>(H5R_DSET_REG_REF_BUF_SIZE);
    }

    RegionReference::RegionReference(array<Byte>^ a)
    {
        m_rr = gcnew array<Byte>(H5R_DSET_REG_REF_BUF_SIZE);
        Array::Copy(a, m_rr, H5R_DSET_REG_REF_BUF_SIZE);
    }

    array<Byte>^ RegionReference::ToByteArray()
    {
        array<Byte>^ result = gcnew array<Byte>(m_rr->Length);
        Array::Copy(m_rr, result, m_rr->Length);
        return result;
    }

}