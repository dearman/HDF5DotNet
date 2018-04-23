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

#include "H5FileOrGroupId.h"
#include "H5LocId.h"
#include "H5ObjectWithAttributes.h"
#include "H5PropertyListId.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
    /// <example>
    /// <para> [C#] </para>
    /// <code>
    /// try
    /// {
    ///    // Create an HDF5 file.
    ///    H5FileId fileId = H5F.create("myCSharp.h5", 
    ///                                  H5F.CreateMode.ACC_TRUNC);
    ///    // Create a HDF5 group.  
    ///    H5GroupId groupId = H5G.create(fileId, "/cSharpGroup", 0);
    ///    H5G.close(groupId);
    ///    H5F.close(openId);
    /// }
    /// catch (HDFException e)
    /// {
    ///    Console.WriteLine(e.Message);
    /// }
    /// </code>
    /// <para> [Visual Basic .NET] </para>
    /// Imports HDF5DotNet
    /// <code>
    /// Module Module1
    ///  Sub Main()
    ///      Dim FileId As H5FileId
    ///      Dim GroupId As H5GroupId
    /// 
    ///         Try
    ///             FileId = H5F.create("HDF5_fromVB", H5F.CreateMode.ACC_TRUNC)
    ///             GroupId = H5G.create(FileId, "/vbGroup", _
    ///                                 H5F.CreateMode.ACC_TRUNC)
    ///             
    ///             H5G.close(GroupId)
    ///             H5F.close(FileId)
    ///         Catch ex As HDFException
    ///             Console.WriteLine(ex.Message())
    /// 
    ///         End Try
    ///         Console.WriteLine("Processing complete!")
    ///         Console.ReadLine()
    ///     End Sub
    /// End Module
    /// </code>
    /// <para> [C++/Cli] </para>
    /// try
    /// {
    ///   // Create an HDF5 file.
    ///   H5FileId^ fileId = H5F::create("myCpp.h5", 
    ///		                         H5F::CreateMode::ACC_TRUNC);
    ///   // Create a HDF5 group.  
    ///   H5GroupId^ groupId = H5G::create(fileId, "/cppGroup", 0);
    ///
    ///   // Close the group.
    ///   H5G::close(groupId);
    ///
    ///   // Close the file
    ///   H5F::close(fileId);
    /// }
    /// catch (HDFException^ e)
    /// {
    ///    Console::WriteLine(e->Message);
    /// }
    /// <code>
    /// </code>
    /// </example>
    ///

    /// <summary>
    ///  H5FileId identifies an H5 file object.  Instances of this class are
    /// returned from H5create and H5open.
    /// </summary>
    public ref class H5FileId : public H5LocId, H5FileOrGroupId, H5ObjectWithAttributes
    {
    internal:
        /// <remarks>
        /// This is the only constructor used to create an H5FileId.  It can
        /// only be invoked by HDF5DotNet library functions.
        /// </remarks>
        /// <param name="id"> is an HDF5 library-generated identification
        /// number that serves as a unique indentifier. </param>
        H5FileId(hid_t id);

    public:
        /// <summary>
        /// Allow read-only access to the internal HDF5 id to HDF5 library
        /// members. (members of this assembly).
        /// </summary>
        virtual property hid_t Id
        {
            hid_t get() { return id_; }
        }

    private:
        /// <summary>
        /// The default constructor is disallowed.  Only HDF5 library
        /// routines are capable of creating an instance of H5FileId and they
        /// must supply an id when doing so.
        /// </summary>
        H5FileId();

        /// <summary>
        // The hdf5 internal id used to identify objects.
        /// </summary>
        hid_t id_;
    };
}