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
    /// <summary>
    /// Message type info.
    /// </summary>
    public ref class Message
    {
    public:

        /// <summary>
        /// Flags to indicate presence of message type in header
        /// </summary>
        property hssize_t present
        {
            hssize_t get() { return  present_; }
        }

        /// <summary>
        /// Flags to indicate message type is shared in header 
        /// </summary>
        property hssize_t shared
        {
            hssize_t get() { return  shared_; }
        }

    private:
        /// <summary>
        /// Flags to indicate presence of message type in header
        /// </summary>
        hssize_t present_; 

        /// <summary>
        /// Flags to indicate message type is shared in header 
        /// </summary>
        hssize_t shared_; 

        // Disallow the default constructor
        Message();

    internal:
        Message(hssize_t present, hssize_t shared);

    };

}