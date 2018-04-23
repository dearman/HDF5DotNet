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

#include "H5.h"
#include "HDFException.h"

#include "H5public.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    herr_t H5::Open()
    {
        herr_t status = H5open();

        if(status < 0) throw gcnew HDFException("H5open failed.", status);

        return status;
    }

    herr_t H5::Close()
    {
        herr_t status = H5close();

        if(status < 0) throw gcnew HDFException("H5close failed.", status);

        return status;
    }

    herr_t H5::CheckLibraryVersion(LibraryVersion version)
    {
        herr_t status = H5check_version(
            safe_cast<unsigned int>(version.Major),
            safe_cast<unsigned int>(version.Minor),
            safe_cast<unsigned int>(version.Release));
    
        if(status < 0)
            throw gcnew HDFException("H5check_version failed.", status);

        return status;
    }

    LibraryVersion H5::Version::get()
    {
        unsigned int maj, min, rel;
        H5get_libversion(&maj, &min, &rel);
        return LibraryVersion(
            safe_cast<int>(maj), safe_cast<int>(min), safe_cast<int>(rel));
    }

    herr_t H5::SetFreeListLimits(
        int regularFreeListCumulativeSizeLimit,
        int regularFreeListSizeLimit,
        int arrayFreeListCumulativeSizeLimit,
        int arrayFreeListSizeLimit,
        int blockOrFactoryFreeListCumulativeSizeLimit,
        int blockOrFactoryFreeListSizeLimit)
    {
        herr_t status = H5set_free_list_limits(
            regularFreeListCumulativeSizeLimit,
            regularFreeListSizeLimit,
            arrayFreeListCumulativeSizeLimit,
            arrayFreeListSizeLimit,
            blockOrFactoryFreeListCumulativeSizeLimit,
            blockOrFactoryFreeListSizeLimit);

        if(status < 0)
            throw gcnew HDFException("H5get_libversion failed.", status);

        return status;
    }

    herr_t H5::GarbageCollect()
    {
        herr_t status = H5garbage_collect();

        if(status < 0)
            throw gcnew HDFException("H5garbage_collect failed.", status);

        return status;
    }

    herr_t H5::DoNotAtExit()
    {
        herr_t status = H5dont_atexit();

        if(status < 0)
            throw gcnew HDFException("H5dont_atexit failed.", status);

        return status;
    }
}
