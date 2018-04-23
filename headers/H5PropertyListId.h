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

#pragma once

#include "H5Id.h"
#include "H5P.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
    /// <summary>
    /// H5PropertyListId uniquely identifies a property list.
    /// </summary>
    public ref class H5PropertyListId : public H5Id
    {

    public:
        H5PropertyListId(H5P::Template h5pTemplate);

    internal:
        /// <remarks>
        /// This is the only constructor used to create an
        /// H5PropertyListId.
        /// It can only be invoked by HDF5DotNet library functions.
        /// </remarks>
        /// <param name="id"> is an HDF5 library-generated identification
        /// number that serves as a unique indentifier. </param>
        H5PropertyListId(hid_t id);

        /// <summary>
        /// Allow read-only access to the internal HDF5 id to HDF5 library
        /// members. (members of this assembly).
        /// </summary>
    public:
        virtual property hid_t Id
        {
            hid_t get() { return id_; }
        }

    internal:
        /// <summary>
        ///    Allow library functions to set the allocCallback_.
        /// </summary>
        void setAllocCallback(H5AllocCallback^ allocCallback)
        {
            allocCallback_ = allocCallback;
        }

        /// <summary>
        ///    Allow library functions to set the allocCallback_.
        /// </summary>
        void setFreeCallback(H5FreeCallback^ freeCallback)
        {
            freeCallback_ = freeCallback;
        }

    private:
        /// <summary>
        /// The default constructor is disallowed.  Only HDF5 library
        /// routines are capable of creating an instance of
        /// H5PropertyListId and they must supply an id when doing so.
        /// </summary>
        H5PropertyListId();

        /// <summary>
        // The hdf5 internal id used to identify objects.
        /// </summary>
        hid_t id_;

        /// <summary>
        ///  allocCallback_ holds a handle to the last alloc delegate 
        ///  assigned in setVlenMemManager to insure that the 
        ///  garbage collector will not release the delegate even if the user's
        ///  instance of H5AllocCallback is deleted.
        /// </summary> 
        H5AllocCallback^ allocCallback_;

        /// <summary>
        ///  freeCallback_ holds a handle to the last free delegate 
        ///  assigned in setVlenMemManager to insure that the 
        ///  garbage collector will not release the delegate even if the user's
        ///  instance of H5FreeCallback is deleted.
        /// </summary> 
        H5FreeCallback^ freeCallback_;
    };
}