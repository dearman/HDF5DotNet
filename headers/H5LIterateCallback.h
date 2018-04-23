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
    ref class H5GroupId;
    ref class H5LinkInfo;

#pragma region documentation
    ///<summary>
    /// Callback used in H5L.iterate.
    ///</summary>

    ///<param name="group">
    /// IN: Identifier specifying subject group
    ///</param>

    ///<param name="name">
    /// IN: object name
    ///</param>

    ///<param name="info">
    /// IN: H5LinkInfo for the object.
    ///</param>

    ///<param name="objData">
    /// IN/Out: Handle to user-supplied data.
    ///</param>
#pragma endregion documentation

    public delegate H5IterationResult H5LIterateCallback(H5GroupId^ group,
        System::String^ name,
        H5LinkInfo^ info,
        System::Object^ objData);
}