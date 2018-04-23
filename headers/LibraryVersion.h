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
    /// <summary>
    /// The major, minor, and release numbers of the version of the HDF library
    /// which is linked to the application.
    /// </summary>
    public value class LibraryVersion
    {
    public:

        LibraryVersion(int major, int minor, int release)
            : m_major(major), m_minor(minor), m_release(release) {}

        /// <summary>
        /// The major version of the library.
        /// </summary>
        property int Major   { int get() { return m_major;   } }
        /// <summary>
        /// The minor version of the library.
        /// </summary>
        property int Minor   { int get() { return m_minor;   } }
        /// <summary>
        /// The release number of the library.
        /// </summary>
        property int Release { int get() { return m_release; } }

    private:

        int m_major;
        int m_minor;
        int m_release;
    };
}