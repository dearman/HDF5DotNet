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
    ref class Message;
    ref class Space;

    /// <summary>
    /// Object header information.
    /// </summary>
    public ref class Header
    {
    public:

        ///<summary>
        /// Version number of header format in file
        ///</summary>
        property int version
        {
            int get() { return  version_; }
        }

        ///<summary>
        /// Number of object header messages
        ///</summary>
        property int nMessages
        {
            int get() { return  nmesgs_; }
        }

        // nChunks property
        ///<summary>
        /// Number of object header chunks
        ///</summary>
        property int nChunks
        {
            int get() { return  nchunks_; }
        }

        // flags property
        ///<summary>
        /// Object header status flags
        ///</summary>
        property int flags
        {
            int get() { return  flags_; }
        }

        // space property
        ///<summary>
        /// Object that contains properties about object space usage.
        ///</summary>
        property Space^ space
        {
            Space^ get() { return  space_; }
        }

        // message property
        ///<summary>
        /// Message type info.
        ///</summary>
        property Message^ message
        {
            Message^ get() { return  message_; }
        }

    private:
        ///<summary>
        /// Version number of header format in file
        ///</summary>
        int version_;   

        ///<summary>
        /// Number of object header messages
        ///</summary>
        int nmesgs_;    

        ///<summary>
        /// Number of object header chunks
        ///</summary>
        int nchunks_;   

        ///<summary>
        /// Object header status flags
        ///</summary>
        int flags_;  

        ///<summary>
        /// Object that contains properties about object space usage.
        ///</summary>
        Space^ space_;

        ///<summary>
        /// Message type info.
        ///</summary>
        Message^ message_;

        // Disallow the default constructor
        Header();

    internal:
        Header(int version, int nmesgs, int nchunks,
            int flags, Space^ space, Message^ message);

    };
}