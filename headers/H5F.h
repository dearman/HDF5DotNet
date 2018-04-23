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

#include "H5FileId.h"
#include "H5ObjectId.h"
#include "HDFExceptionSubclasses.h"

#include "H5Fpublic.h"

namespace HDF5DotNet
{
    /// <summary>
    /// The H5F contains static member function for each of the supported
    /// H5F calls of the HDF5 library.  H5F indicates that this group of
    /// function operates on files.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html"/>
    /// </summary>
    public ref class H5F sealed
    {
    public:
        /// <summary>
        /// H5F.CreateMode provides the HDF5 file access modes available
        /// when creating a file.
        /// </summary>
        enum class CreateMode
        {
            /// <summary> Read only mode. </summary>
            ACC_RDONLY = H5F_ACC_RDONLY,	

            /// <summary> Read/Write mode. </summary>
            ACC_RDWR = H5F_ACC_RDWR,	

            /// <summary> Truncate (delete) data in existing file. </summary>
            ACC_TRUNC = H5F_ACC_TRUNC,

            /// <summary> Read only mode. </summary>
            ACC_EXCL = H5F_ACC_EXCL,

            /// <summary> debug mode. </summary>
            ACC_DEBUG = H5F_ACC_DEBUG,

            /// <summary> Create the file. </summary>
            ACC_CREAT = H5F_ACC_CREAT
        };

        /// <summary>
        /// H5F.OpenMode provides the HDF5 file access modes available
        /// when opening a file.
        /// </summary>
        enum class OpenMode 
        {
            /// <summary> Read only mode. </summary>
            ACC_RDONLY = H5F_ACC_RDONLY,	

            /// <summary> Read/Write mode. </summary>
            ACC_RDWR = H5F_ACC_RDWR,	

            /// <summary> debug mode. </summary>
            ACC_DEBUG = H5F_ACC_DEBUG
        };

        /// <summary>
        /// H5F.Scope defines the scope for the flushing of buffers
        /// associated with a file to disk.
        /// </summary>
        enum class Scope 
        {
            /// <summary> Flushes the entire virtual file. </summary>
            GLOBAL = H5F_SCOPE_GLOBAL,	

            /// <summary> Flushes only the specified file. </summary>
            LOCAL = H5F_SCOPE_LOCAL
        };


#pragma region documentation
        /// <summary> Create a HDF5 file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Create"/>
        /// </summary>

        /// <param name="filename"> filename for new HDF5 file</param>
        /// <param name="mode"> H5F.CreateMode enumeration type that specifies
        /// such modes as read-only (H5F.CreateMode.ACC_RDONLY) </param>

        /// <exception> throws H5CreateException when create fails
        /// </exception>

        /// <returns> a vaild H5FileId for the created file </returns>

        /// <remarks>
        /// Keeping the H5Id class implemented as an abstract data type 
        /// provides
        /// us the opportunity for future source-compatible library upgrades.
        /// </remarks>
        /// <example>
        /// <para> [C#] </para>
        /// <code>
        /// try
        /// {
        ///    // Create an HDF5 file.
        ///    H5FileId fileId = H5F.create("myCSharp.h5", 
        ///                                  H5F.CreateMode.ACC_TRUNC);
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
        ///         Try
        ///             FileId = H5F.create("HDF5_fromVB", _
        ///                                  H5F.CreateMode.ACC_TRUNC)
        ///             H5F.close(FileId)
        ///         Catch ex As HDFException
        ///             Console.WriteLine(ex.Message())
        ///         End Try
        ///         Console.WriteLine("Processing complete!")
        ///         Console.ReadLine()
        ///     End Sub
        /// End Module
        /// </code>
        /// <para> [C++/Cli] </para>
        /// <code>
        /// try
        /// {
        ///   // Create an HDF5 file.
        ///   H5FileId^ fileId = H5F::create("myCpp.h5", 
        ///		                         H5F::CreateMode::ACC_TRUNC);
        ///   // Close the file
        ///   H5F::close(fileId);
        /// }
        /// catch (HDFException^ e)
        /// {
        ///    Console::WriteLine(e->Message);
        /// }
        /// </code>
        /// </example>
#pragma endregion documentation

        static H5FileId^ create(System::String^ filename, 
            CreateMode mode);

#pragma region documentation
        /// <summary> Create a HDF5 file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Create"/>
        /// </summary>
        /// <param name="filename"> filename for new HDF5 file</param>
        /// <param name="mode"> H5F.CreateMode enumeration type that specifies
        /// such modes as read-only (H5F.CreateMode.ACC_RDONLY) </param>
        /// <exception> throws H5CreateException when create fails
        /// </exception>
        /// <returns> a vaild H5FileId for the created file </returns>
        /// <remarks>
        /// Keeping the H5Id class implemented as an abstract data type 
        /// provides
        /// us the opportunity for future source-compatible library upgrades.
        /// </remarks>
#pragma endregion documentation

        static H5FileId^ create(System::String^ filename, 
            CreateMode mode,
            H5PropertyListId^ accessPropertyList);

#pragma region documentation
        /// <summary> Create a HDF5 file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Create"/>
        /// </summary>
        /// <param name="filename"> filename for new HDF5 file</param>
        /// <param name="mode"> H5F.CreateMode enumeration type that specifies
        /// such modes as read-only (H5F.CreateMode.ACC_RDONLY) </param>
        /// <param name="creationPropertyList">
        /// IN: File creation property list identifier, used when
        /// modifying default file meta-data.
        /// </param>
        /// <param name="accessPropertyList">
        /// IN: File access property list identifier. If parallel file
        /// access is desired, this is a collective call according to the
        /// communicator stored in the access_id.
        /// </param>
        /// <exception> throws H5CreateException when create fails
        /// </exception>
        /// <returns> a vaild H5FileId for the created file </returns>
        /// <remarks>
        /// us the opportunity for future source-compatible library upgrades.
        /// </remarks>
#pragma endregion documentation

        static H5FileId^ create(System::String^ filename, 
            CreateMode mode,
            H5PropertyListId^ creationPropertyList,
            H5PropertyListId^ accessPropertyList);

#pragma region documentation
        /// <summary> Flushes all buffers associated with a file to disk.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Flush"/>
        /// </summary>
        ///
        /// <param name="objId">
        /// IN: Identifier of object used to identify the file.
        /// </param>
        /// <param name="scope">
        /// IN: Specifies the scope of the flushing action.
        /// </param>
#pragma endregion documentation

        static void flush(H5Id^ objId,
            Scope scope);

#pragma region documentation
        /// <summary> Determines whether a file is in the HDF5 format.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-IsHDF5"/>
        /// </summary>
        ///
        /// <param name="filename">
        /// IN: File name to check format.
        /// </param>
#pragma endregion documentation

        static bool is_hdf5(System::String^ filename);

#pragma region documentation
        /// <summary> Open an existing HDF5 file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Open"/>
        /// </summary>
        ///
        /// <param name="filename">
        /// IN: Name of the file to access.
        /// </param>
        /// <param name="mode">
        /// IN: File access mode (e.g., OpenMode.ACC_RDONLY)
        /// </param>
#pragma endregion documentation

        static H5FileId^ open(System::String^ filename,
            OpenMode mode);

#pragma region documentation
        /// <summary> Open an existing HDF5 file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Open"/>
        /// </summary>
        /// <param name="filename">
        /// IN: Name of the file to access.
        /// </param>
        /// <param name="mode">
        /// IN: File access mode (e.g., OpenMode.ACC_RDONLY)
        /// </param>
        /// <param name="propertyListId">
        /// IN: Identifier for the file access properties list. If
        /// parallel file access is desired, this is a collective call
        /// according to the communicator stored in the access_id.
        /// </param>
#pragma endregion documentation

        static H5FileId^ open(System::String^ filename,
            OpenMode mode, 
            H5PropertyListId^ propertyListId);

        /// <summary> Close an open file.  It is necessary to close open 
        /// files to prevent resource leaks.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Close"/>
        /// </summary>
        static void close(H5FileId^ id);

        /// <summary> Mounts a file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Mount"/>
        /// </summary>
        static void Mount(H5FileOrGroupId^ locRef,
            System::String^ name,
            H5FileId^ fileRef);

        /// <summary> Mounts a file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Mount"/>
        /// </summary>
        static void Mount(H5FileOrGroupId^ locRef,
            System::String^ name,
            H5FileId^ fileRef,
            H5PropertyListId^ pList);

        /// <summary> Unmounts a file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Unmount"/>
        /// </summary>
        static void Unmount(H5FileOrGroupId^ locRef,
            System::String^ name);

    private:
        // Disallow instances of this class.
        H5F() {};
    };
}
