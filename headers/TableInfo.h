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
    ///  Object returned from getTableInfo.  Properties include number of 
    /// table fields and number of table records.
    /// </summary>
    public ref class TableInfo
    {
    public:

        /// <summary>
        /// Constructor takes number of fields and number of records as
        /// parameters. 
        /// </summary>
        TableInfo(hssize_t nFields, hssize_t nRecords)
            : nFields_(safe_cast<hsize_t>(nFields)),
            nRecords_(safe_cast<hsize_t>(nRecords))
        {
        }

        /// <summary>
        /// Number of table fields (columns).
        /// </summary>
        property hssize_t nFields
        {
            hssize_t get() { return safe_cast<hssize_t>(nFields_); }
        }

        /// <summary>
        /// Number of table records (rows).
        /// </summary>
        property hssize_t nRecords
        {
            hssize_t get() { return safe_cast<hssize_t>(nRecords_); }
        }

        /// <summary>
        /// Produce string containg TableInfo .
        /// </summary>
        virtual System::String^ ToString() override
        { 
            return System::String::Format("nFields: {0} \n"
                "nRecords: {1} \n", nFields_, nRecords_);
        }

    private:
        /// <summary>
        /// Number of table fields (columns).
        /// </summary>
        hsize_t nFields_;

        /// <summary>
        /// Number of table records (rows).
        /// </summary>
        hsize_t nRecords_;
    };

}
