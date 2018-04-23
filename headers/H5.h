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

#include "LibraryVersion.h"

#include "H5Ipublic.h"

namespace HDF5DotNet
{
    /// <summary>
    /// The H5 class contains static member function for each of the supported
    /// H5 calls of the HDF5 library. <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html" />
    /// </summary>
    public ref class H5 sealed
    {
    public:

        /// <summary>
        /// Initializes the HDF5 library. <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-Open"/>
        /// </summary>
        static herr_t Open();

        /// <summary>
        /// Flushes all data to disk, closes all open identifiers, and cleans up memory.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-Close"/>
        /// </summary>
        static herr_t Close();

        /// <summary>
        /// Verifies that HDF5 library versions are consistent.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-VersCheck"/>
        /// </summary>
        static herr_t CheckLibraryVersion(LibraryVersion version);

        static property LibraryVersion Version
        {
            LibraryVersion get();
        }

        /// <summary>
        /// Sets free-list size limits.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-SetFreeListLimits"/>
        /// </summary>
        static herr_t SetFreeListLimits
            (
            int regularFreeListCumulativeSizeLimit,
            int regularFreeListSizeLimit,
            int arrayFreeListCumulativeSizeLimit,
            int arrayFreeListSizeLimit,
            int blockOrFactoryFreeListCumulativeSizeLimit,
            int blockOrFactoryFreeListSizeLimit
            );

        /// <summary>
        /// Garbage collects on all free-lists of all types.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-GarbageCollect"/>
        /// </summary>
        static herr_t GarbageCollect();
        
        /// <summary>
        /// Instructs library not to install <c>atexit</c> cleanup routine.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-DontAtExit"/>
        /// </summary>
        static herr_t DoNotAtExit();

    private:

        H5() {};
    };
}
