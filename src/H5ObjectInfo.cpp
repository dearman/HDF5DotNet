/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group (THG).                                       *
 * All rights reserved.                                                    *
 *                                                                         *
 * This file is part of HDF5. The full HDF5 copyright notice, including    *
 * terms governing use, modification, and redistribution, is contained in  *
 * the files COPYING and Copyright.html. COPYING can be found at the root  *
 * of the source code distribution tree; Copyright.html can be found at the*
 * root level of an installed copy of the electronic HDF5 document set and *
 * is linked from the top-level documents page. It can also be found at    *
 * http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have     *
 * access to either file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "H5ObjectInfo.h"
#include "Header.h"
#include "IhInfo.h"
#include "Message.h"
#include "MetaSize.h"
#include "Space.h"

namespace HDF5DotNet
{
    H5ObjectInfo::H5ObjectInfo(const H5O_info_t& info)
        : fileno_(info.fileno),
        addr_(info.addr),
        type_(safe_cast<H5ObjectType>(info.type)),
        rc_(info.rc),
        atime_(info.atime),
        mtime_(info.mtime),
        ctime_(info.ctime),
        btime_(info.btime),
        num_attrs_(info.num_attrs)
    {
        Space^ space =  gcnew Space(
            info.hdr.space.total,
            info.hdr.space.meta,
            info.hdr.space.mesg,
            info.hdr.space.free);

        Message^ msg = gcnew Message(
            safe_cast<hssize_t>(info.hdr.mesg.present),
            safe_cast<hssize_t>(info.hdr.mesg.shared));

        header_ = gcnew Header(
            safe_cast<int>(info.hdr.version), safe_cast<int>(info.hdr.nmesgs), 
            safe_cast<int>(info.hdr.nchunks), safe_cast<int>(info.hdr.flags),
            space, msg);

        MetaSize^ mta = gcnew MetaSize(
            gcnew IhInfo(info.meta_size.obj.index_size, info.meta_size.obj.heap_size),
            gcnew IhInfo(info.meta_size.attr.index_size, info.meta_size.attr.heap_size));

        metaSize_ = mta;
    }
}