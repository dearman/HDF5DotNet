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

namespace HDF5DotNet
{
    ///<summary>
    /// Delegate for user-specified memory deallocation.
    ///</summary>
    ///<param name="mem">
    /// Pointer to memory to reclaim.
    ///</param>
    ///<param name="free_info">
    /// Void pointer to memory containing addional user-specified information.
    /// Note that all void* must point to memory that is pinned or 
    /// otherwise immune from relocation by the garbage collector.
    ///</param>
    [System::Runtime::InteropServices::UnmanagedFunctionPointer(
        System::Runtime::InteropServices::CallingConvention::Cdecl)]
    public delegate void  H5FreeCallback(
        System::IntPtr mem, System::IntPtr free_info);

}