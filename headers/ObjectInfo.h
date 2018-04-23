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

#include "H5Gpublic.h"
#include "H5Ipublic.h"

namespace HDF5DotNet
{
    ref class H5GroupId;

    /// <summary>
    /// An instance of this class is returned from H5G.getObjectInfo.  The
    /// class provides properties for the following values:
    ///  file number, object number, number of hard links to object,
    ///  basic object type, modification time, symbolic link value length,
    ///  size of object header, free space in object header, number of 
    ///  header messages, and the number of object header chunks.
    /// </summary>
    public ref class ObjectInfo 
    {
    internal:
        ObjectInfo(H5G_stat_t% stats);

    public:
        ///<summary> file number </summary>
        property array<hssize_t>^ fileNumber 
        {
            array<hssize_t>^ get() { return fileno_;}
        }

        ///<summary> object number </summary>
        property array<hssize_t>^ objectNumber 
        {
            array<hssize_t>^ get() { return objno_; }
        }

        ///<summary> number of hard links to object </summary>
        property int nHardLinks	
        {
            int get() { return nlink_; }
        }

        ///<summary> basic object type </summary>
        property H5GType objectType
        {
            H5GType get() { return type_; }
        }

        ///<summary> modification time </summary>
        property time_t modificationTime
        {
            time_t get() { return mtime_; }
        }

        ///<summary> symbolic link value length </summary>
        property System::IntPtr linkLength
        {
            System::IntPtr get()
            {
                return (System::IntPtr::Size == 4) ? System::IntPtr(safe_cast<System::Int32>(linklen_))
                    : System::IntPtr(safe_cast<System::Int64>(linklen_));
            }
        }

        // H5O_stat_t  members

        ///<summary> Total size of object header in file </summary>
        property hssize_t headerSize
        {
            hssize_t get() { return size_; }
        }

        ///<summary> Free space within object header </summary>
        property hssize_t unusedHeaderSpace
        {
            hssize_t get() { return free_; }
        }

        ///<summary> Number of object header messages </summary>
        property int nHeaderMessages
        {
            int get() { return nmesgs_; }
        }

        ///<summary> Number of object header chunks </summary>
        property int nHeaderChunks
        {
            int get() { return nchunks_; }
        }

    private:
        ///<summary> file number </summary>
        array<hssize_t>^  fileno_;

        ///<summary> object number </summary>
        array<hssize_t>^  objno_;

        ///<summary> number of hard links to object </summary>
        int  nlink_;

        ///<summary> basic object type </summary>
        H5GType  type_;

        ///<summary> modification time </summary>
        time_t  mtime_;

        ///<summary> symbolic link value length </summary>
        size_t  linklen_;

        ///<summary> Total size of object header in file </summary>
        hssize_t  size_;

        ///<summary> Free space within object header </summary>
        hssize_t  free_;

        ///<summary> Number of object header messages </summary>
        int  nmesgs_;

        ///<summary> Number of object header chunks </summary>
        int  nchunks_;
    };
}