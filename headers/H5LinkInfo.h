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

#include "H5T.h"

#include "H5Lpublic.h"

namespace HDF5DotNet
{
    /// <summary>
    ///  The H5LinkInfo class contains properties that provide read-only access
    ///  to its data members.
    /// </summary>
    public ref class H5LinkInfo
    {
    public:
        H5LinkInfo(const H5L_info_t& info)
            : linkType_(safe_cast<H5T::LinkType>(info.type)),
            creationOrderValid_(info.corder_valid != 0),
            creationOrder_(info.corder),
            charSet_(safe_cast<H5T::CharSet>(info.cset)),
            address_(info.u.address),
            softLinkSizeOrUD_(info.u.val_size)
        {
        }

        property H5T::LinkType linkType
        {
            H5T::LinkType get() { return linkType_; }
        }

        property bool creationOrderValid
        {
            bool get() { return creationOrderValid_; }
        }

        property hssize_t creationOrder
        {
            hssize_t get() { return creationOrder_; }
        }

        property H5T::CharSet charSet
        {
            H5T::CharSet get() { return charSet_; }
        }

        property haddr_t address
        {
            haddr_t get() { return address_; }
        }

        property System::IntPtr softLinkSizeOrUD
        {
            System::IntPtr get()
            {
                return System::IntPtr((System::IntPtr::Size ==4)
                    ? safe_cast<System::Int32>(softLinkSizeOrUD_)
                    : safe_cast<System::Int64>(softLinkSizeOrUD_));
            }
        }

    private:
        H5T::LinkType linkType_;
        bool creationOrderValid_;
        hssize_t creationOrder_;
        H5T::CharSet charSet_;
        haddr_t address_;
        size_t softLinkSizeOrUD_;

        // Disallow the default constructor
        H5LinkInfo() {}
    };
}
