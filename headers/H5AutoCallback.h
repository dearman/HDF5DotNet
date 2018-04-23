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

#pragma once

#include "H5Ipublic.h"

namespace HDF5DotNet
{

    ///<summary>
    /// Callback invoked when error conditions occur (see setAuto).
    ///</summary>
    /// <param name="estackId">
    /// IN: Error stack identifier.
    /// </param>
    /// <param name="alloc_info">
    /// IN: Data passed to the error function. Note that this memory,
    /// and all memory used with void* must be pinned or otherwise
    /// immune to garbage collection or rellocation.
    /// </param>
    [System::Runtime::InteropServices::UnmanagedFunctionPointer(
        System::Runtime::InteropServices::CallingConvention::Cdecl)]
    public delegate herr_t H5AutoCallback(hid_t estackId, System::IntPtr alloc_info);

}