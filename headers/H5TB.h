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

#include "H5LocId.h"
#include "TableFieldInfo.h"
#include "TableInfo.h"

namespace HDF5DotNet
{
    /// <summary>
    /// The H5TB contains static member function for each of the supported
    /// H5TB calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/HL/RM_H5TB.html"/>
    /// </summary>
    public ref class H5TB sealed
    {
    public:

#pragma region documentation
        ///<summary>
        /// Gets the table dimensions.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/HL/RM_H5TB.html#H5TBget_table_info"/>
        ///</summary>

        ///<param name="loc">
        /// IN: Identifier of the file or group to read the table within. 
        ///</param>

        ///<param name="tableName">
        /// IN: The name of the dataset to read.
        ///</param>

        /// <returns>
        ///  An instance of TableInfo containing the dimensions.
        /// </returns>
        /// <exception cref="H5TBgetTableInfoException">
        /// throws H5TBgetTableInfoException on failure.
        /// </exception>
#pragma endregion documentation

        static TableInfo^ getTableInfo(H5LocId^ loc, System::String^ tableName);

#pragma region documentation
        ///<summary>
        /// Gets information about a table.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/HL/RM_H5TB.html#H5TBget_field_info"/>
        ///</summary>

        ///<param name="loc">
        /// IN: Identifier of the file or group to read the table within. 
        ///</param>

        ///<param name="tableName">
        /// IN: The name of the dataset to read.
        ///</param>

        /// <returns>
        ///  An instance of TableFieldInfo containing the table field 
        /// information.
        /// </returns>

        /// <exception cref="H5TBgetFieldInfoException">
        /// throws H5TBgetFieldInfoException on failure.
        /// </exception>
#pragma endregion documentation

        static TableFieldInfo^ getFieldInfo(H5LocId^ loc, System::String^ tableName);

    private:
        /// <summary>
        /// Disallow the creation of instances of this class.
        /// </summary>
        H5TB() { };
    };
}

