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

#include "H5Ipublic.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
    ///<summary>
    /// Enumeration class for iteration order (UNKNOWN, INCREASING,
    /// DECREASING, or NATIVE).
    ///</summary>
    public enum class H5IterationOrder 
    {
        /// <summary> 
        /// Unknown iteration order.
        /// </summary>
        UNKNOWN = H5_ITER_UNKNOWN,

        /// <summary> 
        /// Iteration is from beginning to end, i.e., a 
        /// top-down iteration incrementing the index position at each 
        /// step. 
        /// </summary>
        INCREASING = H5_ITER_INC,  /* Increasing order */

        /// <summary> 
        /// Iteration starts at the end of the index, i.e., a 
        /// bottom-up iteration decrementing the index position at each 
        /// step. 
        /// </summary>
        DECREASING = H5_ITER_DEC,  /* Decreasing order */

        /// <summary> 
        /// HDF5 iterates in the fastest-available order. No information 
        /// is provided as to the order, but HDF5 ensures that each 
        /// element in the index will be visited if the iteration 
        /// completes successfully. 
        /// </summary>
        NATIVE = H5_ITER_NATIVE
    };
}