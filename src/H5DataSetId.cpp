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

#include "H5DataSetId.h"
#include "HDFException.h"

namespace HDF5DotNet
{

    H5DataSetId::H5DataSetId(H5S::H5SType h5DatasetType)
        : id_(safe_cast<hid_t>(h5DatasetType))
    {
    }

    // Store the internal HDS5 id.
    H5DataSetId::H5DataSetId(hid_t id) : id_(id)
    {
    }

    // private default constructor should never be used.
    H5DataSetId::H5DataSetId() : id_(0)
    {
        throw gcnew HDFException("Unsupported constructor", -1);
    }
}