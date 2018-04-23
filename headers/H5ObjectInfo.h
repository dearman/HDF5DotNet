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

#include "H5ObjectType.h"

namespace HDF5DotNet
{
    System::DateTime^ fromUnixTime(time_t secondsSinceJan1);

    ref class Header;
    ref class MetaSize;

    ///<summary>
    /// An instance of this class is returned by the H5G.getInfo calls.
    /// It contains header and metasize data about the object as well as
    /// file number, address, object type, access time, modification time,
    /// birth time, and number of attributes.
    ///</summary>
    public ref class H5ObjectInfo
    {
    public:

        /// <summary>
        /// Header information.
        /// </summary>
        property Header^ header
        {
            Header^ get() { return header_; }
        }

        /// <summary>
        ///  Meta information.
        /// </summary>
        property MetaSize^ metaSize
        {
            MetaSize^ get() { return metaSize_; }
        }

        /// <summary>
        ///  Object file number.
        /// </summary>
        property hssize_t fileNumber
        {
            hssize_t get() { return fileno_; }
        }

        /// <summary>
        /// Object address in file.
        /// </summary>
        property haddr_t address
        {
            haddr_t get() { return addr_; }
        }

        /// <summary>
        ///  Basic object type (group, dataset, etc.)
        /// </summary>
        property H5ObjectType objectType
        {
            H5ObjectType get() { return type_; }
        }

        /// <summary>
        ///  Reference count of object.
        /// </summary>
        property int referenceCount
        {
            int get() { return safe_cast<int>(rc_); }
        }

        /// <summary>
        /// Access time in .NET DataTime format.
        /// </summary>
        property System::DateTime^ accessTime
        {
            System::DateTime^ get() { return fromUnixTime(atime_); }
        }

        /// <summary>
        ///  Access time in Unix (time since 1/1/1970)
        /// </summary>
        property time_t  accessSecondsSince1970
        {
            time_t get() 
            {
                return atime_;
            }
        }

        /// <summary>
        /// Modification time in .NET DataTime format.
        /// </summary>
        property System::DateTime^ modificationTime
        {
            System::DateTime^ get() { return fromUnixTime(mtime_); }
        }

        /// <summary>
        /// Modification time in Unix (time since 1/1/1970)
        /// </summary>
        property time_t  modificationSecondsSince1970
        {
            time_t get() 
            {
                return mtime_;
            }
        }

        /// <summary>
        /// Change time in .NET DataTime format.
        /// </summary>
        property System::DateTime^ changeTime
        {
            System::DateTime^ get() { return fromUnixTime(ctime_); }
        }

        /// <summary>
        /// Change time in Unix (time since 1/1/1970)
        /// </summary>
        property time_t  changeSecondsSince1970
        {
            time_t get() 
            {
                return ctime_;
            }
        }

        /// <summary>
        /// Birth time in .NET DataTime format.
        /// </summary>
        property System::DateTime^ birthTime
        {
            System::DateTime^ get() { return fromUnixTime(btime_); }
        }

        /// <summary>
        /// Birth time in Unix (time since 1/1/1970)
        /// </summary>
        property time_t  birthSecondsSince1970
        {
            time_t get() 
            {
                return btime_;
            }
        }

        /// <summary>
        /// Number of attributes attached to the object.
        /// </summary>
        property hssize_t nAttributes
        {
            hssize_t get() { return safe_cast<hssize_t>(num_attrs_); }
        }

    private:
        Header^ header_;
        MetaSize^ metaSize_;

        /// <summary>
        ///  Object file number.
        /// </summary>
        hssize_t       fileno_;  

        /// <summary>
        /// Object address in file.
        /// </summary>
        haddr_t             addr_;  

        /// <summary>
        ///  Basic object type (group, dataset, etc.)
        /// </summary>
        H5ObjectType          type_;

        /// <summary>
        ///  Reference count of object.
        /// </summary>
        unsigned int            rc_;   

        /// <summary>
        ///  Access time in Unix (time since 1/1/1970)
        /// </summary>
        time_t              atime_;

        /// <summary>
        /// Modification time in Unix (time since 1/1/1970)
        /// </summary>
        time_t              mtime_;

        /// <summary>
        /// Change time in Unix (time since 1/1/1970)
        /// </summary>
        time_t              ctime_;

        /// <summary>
        /// Birth time in Unix (time since 1/1/1970)
        /// </summary>
        time_t              btime_;

        /// <summary>
        /// Number of attributes attached to the object.
        /// </summary>
        hsize_t             num_attrs_;

    internal:
        H5ObjectInfo(const H5O_info_t& info);
    };
}