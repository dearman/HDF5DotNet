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
    ref class IhInfo;

    /// <summary>
    /// MetaSize is the component of H5ObjectInfo that contains the object
    /// meta information.
    /// </summary>
    public ref class MetaSize
    {
    public:

        ///<summary>
        /// v1/v2 B-tree and local/fractal heap fro groups, B-tree for chunked
        /// datasets.
        ///</summary>
        property IhInfo^ object
        {
            IhInfo^ get() { return object_; }
        }

        /// <summary>
        /// v2 B-tree and heap for attributes
        /// </summary>
        property IhInfo^ attribute
        {
            IhInfo^ get() { return attribute_; }
        }

    private: 
        ///<summary>
        /// v1/v2 B-tree and local/fractal heap fro groups, B-tree fro chunked
        /// datasets.
        ///</summary>
        IhInfo^   object_;  

        /// <summary>
        /// v2 B-tree and heap for attributes
        /// </summary>
        IhInfo^   attribute_; 

        // Disallow the default constructor.
        MetaSize();

    internal:
        MetaSize(IhInfo^ object, IhInfo^ attribute);
    };
}