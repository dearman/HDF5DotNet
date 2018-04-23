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

namespace HDF5DotNet
{
    /// <summary>
    ///  Object returned from H5TB.getFieldInfo.  Properties include the name
    /// of each field, the size of
    /// each field, offset of each field, and type size of each field. 
    /// </summary>
    public ref class TableFieldInfo
    {
    public:

        /// <summary>
        /// Constructor for table info takes values returned from
        /// H5TBget_field_info.
        /// </summary>
        TableFieldInfo(array<System::String^>^ fieldName,
            array<System::IntPtr>^ fieldSize,
            array<System::IntPtr>^ fieldOffset,
            array<System::IntPtr>^ typeSize) :
        fieldName_(fieldName),
            fieldSize_(fieldSize),
            fieldOffset_(fieldOffset),
            typeSize_(typeSize)
        {
        }

        /// <summary>
        /// An array containing the names of the fields. 
        /// </summary>
        property array<System::String^>^ fieldName
        {
            array<System::String^>^ get() { return fieldName_; } 
        }

        /// <summary>
        /// An array containing the size of the fields. 
        /// </summary>
        property array<System::IntPtr>^ fieldSize
        {
            array<System::IntPtr>^ get() { return fieldSize_; } 
        }

        /// <summary>
        /// An array containing the offsets of the fields. 
        /// </summary>
        property array<System::IntPtr>^ fieldOffset
        {
            array<System::IntPtr>^ get() { return fieldOffset_; } 
        }

        /// <summary>
        /// An array containing the size of the HDF5 type associated with the 
        /// table.
        /// </summary>
        property array<System::IntPtr>^ typeSize
        {
            array<System::IntPtr>^ get() { return typeSize_; } 
        }

    private:
        /// <summary>
        /// An array containing the names of the fields. 
        /// </summary>
        array<System::String^>^ fieldName_;

        /// <summary>
        /// An array containing the size of the fields. 
        /// </summary>
        array<System::IntPtr>^ fieldSize_;

        /// <summary>
        /// An array containing the offsets of the fields. 
        /// </summary>
        array<System::IntPtr>^ fieldOffset_;

        /// <summary>
        /// An array containing the size of the HDF5 type associated with the 
        /// table.
        /// </summary>
        array<System::IntPtr>^ typeSize_;
    };
}