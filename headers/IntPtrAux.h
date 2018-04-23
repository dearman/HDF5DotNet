/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Copyright by The HDF Group (THG).*
* All rights reserved. *
**
* This file is part of HDF5. The full HDF5 copyright notice, including*
* terms governing use, modification, and redistribution, is contained in*
* the files COPYING and Copyright.html. COPYING can be found at the root*
* of the source code distribution tree; Copyright.html can be found at the*
* root level of an installed copy of the electronic HDF5 document set and*
* is linked from the top-level documents page. It can also be found at*
* http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have*
* access to either file, you may request a copy from help@hdfgroup.org.*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

namespace HDF5DotNet
{

    private struct IntPtrAux
    {
    public:

        static size_t ToSize_t(System::IntPtr p)
        {
            return safe_cast<size_t>((System::IntPtr::Size == 4) ? p.ToInt32() : p.ToInt64());
        }

        [System::CLSCompliant(false)]
        static size_t ToSize_t(System::UIntPtr p)
        {
            return safe_cast<size_t>((System::UIntPtr::Size == 4) ? p.ToUInt32() : p.ToUInt64());
        }
    };

}