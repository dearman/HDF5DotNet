/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Copyright by The HDF Group (THG).                                        *
* All rights reserved.                                                     *
*                                                                          *
* This file is part of HDF5. The full HDF5 copyright notice, including     *
* terms governing use, modification, and redistribution, is contained in   *
* the files COPYING and Copyright.html. COPYING can be found at the root   *
* of the source code distribution tree; Copyright.html can be found at the *
* root level of an installed copy of the electronic HDF5 document set and  *
* is linked from the top-level documents page. It can also be found at     *
* http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have      *
* access to either file, you may request a copy from help@hdfgroup.org.    *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "H5T.h"

#include "H5Ipublic.h"

namespace HDF5DotNet
{
    /// <summary>
    ///  An instance of the class is generated from a call to H5A.getInfo.
    ///  The information it contains includes the validity of the creation 
    ///  order, creation order, character set, and data size.
    /// </summary>
    public ref class H5AttributeInfo
    {
    public:

        /// <summary> 
        /// creationOrder valid indicates whether the 
        /// creation order data is valid for this attribute. Note that if 
        /// creation order is not being tracked, no creation order data will 
        /// be valid. 
        /// </summary>
        property bool creationOrderValid
        {
            bool get() { return creationOrderValid_; }
        }

        /// <summary> 
        /// creationOrder is a positive integer containing the 
        /// creation order of the attribute. This value is 0-based, so, for 
        /// example, the third attribute created will have a corder value of 2.
        /// </summary>
        property int creationOrder
        {
            int get() { return safe_cast<int>(creationOrder_); }
        }

        /// <summary> 
        /// characterSet indicates the character set used for the attribute's 
        /// name. 
        /// </summary>
        property H5T::CharSet characterSet
        {
            H5T::CharSet get() { return characterSet_; }
        }

        /// <summary> 
        /// dataSize indicates the size, in the number of characters, of the 
        /// attribute.
        /// </summary>
        property hssize_t dataSize
        {
            hssize_t get() { return safe_cast<hssize_t>(dataSize_); }
        }

        /// <summary> 
        /// The constructor takes the parameters returned from
        /// H5Aget_info.
        /// </summary>
        H5AttributeInfo(
            bool creationOrderValid,
            int  creationOrder,
            H5T::CharSet characterSet,
            hssize_t dataSize
            );

    private:

        // Disallow default constructor
        H5AttributeInfo();

        /// <summary> 
        /// creationOrder valid indicates whether the 
        /// creation order data is valid for this attribute. Note that if 
        /// creation order is not being tracked, no creation order data will 
        /// be valid. 
        /// </summary>
        bool             creationOrderValid_;   

        /// <summary> 
        /// creationOrder is a positive integer containing the 
        /// creation order of the attribute. This value is 0-based, so, for 
        /// example, the third attribute created will have a corder value of 2.
        /// </summary>
        unsigned int   creationOrder_;         

        /// <summary> 
        /// characterSet indicates the character set used for the attribute's 
        /// name. 
        /// </summary>
        H5T::CharSet        characterSet_;           

        /// <summary> 
        /// dataSize indicates the size, in the number of characters, of the 
        /// attribute.
        /// </summary>
        hsize_t             dataSize_;
    };
}
