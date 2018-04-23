/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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

#include "H5DataTypeId.h"
#include "H5T.h"
#include "HDFException.h"

namespace HDF5DotNet
{
    // Store the internal HDS5 id.
    H5DataTypeId::H5DataTypeId(hid_t id) : id_(id)
    {
    }

    // Allow the implicit construction of a type Id from a H5T::H5Type.
    H5DataTypeId::H5DataTypeId(H5T::H5Type h5type) :
    id_(safe_cast<hid_t>(H5T::getStdType(h5type)))
    {
    }

    // private default constructor should never be used.
    H5DataTypeId::H5DataTypeId() : id_(0)
    {
        throw gcnew HDFException("Unsupported constructor", -1);
    }

}
