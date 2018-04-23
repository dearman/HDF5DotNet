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

#include "H5AllocCallback.h"
#include "H5D.h"
#include "H5FreeCallback.h"
#include "H5Memory.h"

#include "H5Ppublic.h"

namespace HDF5DotNet
{
    ref class H5DataTypeId;
    ref class H5PropertyListId;

    /// <summary>
    /// The H5P contains static member function for each of the supported
    /// H5P calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html"/>
    /// </summary>
    public ref class H5P sealed
    {
    public:

        ///<summary>
        /// Enumeration class for Template (H5P_DEFAULT).
        ///</summary>
        enum class Template
        {
            DEFAULT = H5P_DEFAULT
        };

        ///<summary>
        /// Enumeration class for property list class.
        ///</summary>
        enum class PropertyListClass
        {
            ROOT,
            OBJECT_CREATE,
            FILE_CREATE,
            FILE_ACCESS,
            DATASET_CREATE,
            DATASET_ACCESS,
            DATASET_XFER,
            FILE_MOUNT,
            GROUP_CREATE,
            GROUP_ACCESS,
            DATATYPE_CREATE,
            DATATYPE_ACCESS,
            STRING_CREATE,
            ATTRIBUTE_CREATE,
            OBJECT_COPY,
            LINK_CREATE,
            LINK_ACCESS
        };

#pragma region documentation
        ///<summary>
        /// Sets type conversion and background buffers.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetBuffer"/>
        ///</summary>

        ///<param name="id">
        /// IN: Identifier for the dataset transfer property list.
        ///</param>

        ///<param name="bufferSize">
        /// IN: Size, in bytes, of the type conversion and background buffers.
        ///</param>

        ///<param name="typeConversionBuffer">
        /// IN: Pointer to application-allocated type conversion buffer.
        ///</param>

        ///<param name="backgroundBuffer">
        /// IN: Pointer to application-allocated background buffer.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PsetBufferException">
        /// throws H5PsetBufferException on failure.
        /// </exception>
#pragma endregion documentation

        static void setBuffer(H5PropertyListId^ id,
            hssize_t bufferSize,
            System::IntPtr typeConversionBuffer,
            System::IntPtr backgroundBuffer);

#pragma region documentation
        ///<summary>
        /// Sets type conversion and background buffers.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetBuffer"/>
        ///</summary>

        ///<param name="id">
        /// IN: Identifier for the dataset transfer property list.
        ///</param>

        ///<param name="typeConversionBuffer">
        /// IN: Pointer to application-allocated type conversion buffer.
        ///</param>

        ///<param name="backgroundBuffer">
        /// IN: Pointer to application-allocated background buffer.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PsetBufferException">
        /// throws H5PsetBufferException on failure.
        /// </exception>
#pragma endregion documentation

        static void setBuffer(H5PropertyListId^ id,
            H5Memory^ typeConversionBuffer,
            H5Memory^ backgroundBuffer);

#pragma region documentation
        ///<summary>
        /// Creates a new property as an instance of a property list class.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-Create"/>
        ///</summary>

        ///<param name="listClass">
        /// IN: The class of the property list to create.
        ///</param>

        /// <returns>
        /// The H5PropertyListId for the new property list.
        /// </returns>

        /// <exception cref="H5PcreateException">
        /// throws H5PcreateException on failure.
        /// </exception>
#pragma endregion documentation

        static H5PropertyListId^ create(H5P::PropertyListClass listClass);

#pragma region documentation
        ///<summary>
        /// Terminates access to a property list.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-Close"/>
        ///</summary>

        ///<param name="id">
        /// IN: Identifier of the property list to terminate access to.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PcloseException">
        /// throws H5PcloseException on failure.
        /// </exception>
#pragma endregion documentation

        static void close(H5PropertyListId^ id);

        ///<summary>
        /// Retrieves the size of chunks for the raw data of a chunked layout dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-GetChunk"/>
        ///</summary>
        static array<hssize_t>^ getChunk(H5PropertyListId^ id, int maxNDims);

#pragma region documentation
        ///<summary>
        /// Sets the size of the chunks used to store a chunked layout dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetChunk"/>
        ///</summary>

        ///<param name="id">
        /// IN: Dataset creation property list identifier.
        ///</param>

        ///<param name="dimensions">
        /// IN: An array defining the size, in dataset elements, of each chunk.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PsetChunkException">
        /// throws H5PsetChunkException on failure.
        /// </exception>
#pragma endregion documentation

        static void setChunk(H5PropertyListId^ id, 
            array<hssize_t>^ dimensions);

#pragma region documentation
        ///<summary>
        /// Sets compression method and compression level.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetDeflate"/>
        ///</summary>

        ///<param name="id">
        /// IN: Identifier for the dataset creation property list.
        ///</param>

        ///<param name="level">
        /// IN: Compression level.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PsetDeflateException">
        /// throws H5PsetDeflateException on failure.
        /// </exception>
#pragma endregion documentation

        static void setDeflate(H5PropertyListId^ id, int level);

        [System::CLSCompliant(false)]
        static void setDeflate(H5PropertyListId^ id, unsigned int level);

        ///<summary>
        /// Returns the layout of the raw data for a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-GetLayout"/>
        ///</summary>
        static H5D::Layout getLayout(H5PropertyListId^ id);

#pragma region documentation
        ///<summary>
        /// Sets the memory manager for variable-length datatype allocation 
        /// in H5Dread and H5Dvlen_reclaim.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetVLMemManager"/>
        ///</summary>

        ///<param name="plistId">
        /// IN: Identifier for the dataset transfer property list.
        ///</param>

        ///<param name="allocCallback">
        /// IN: User's allocate routine, or unassigned delegate for malloc.
        ///</param>

        ///<param name="allocInfo">
        /// IN: Extra parameter for user's allocation routine.
        ///</param>

        ///<param name="freeCallback">
        /// IN: User's free routine, or or unassigned delegate for system free.
        ///</param>

        ///<param name="freeInfo">
        /// IN: Extra parameter for user's free routine.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5PsetVlenMemManagerException">
        /// throws H5PsetVlenMemManagerException on failure.
        /// </exception>
#pragma endregion documentation

        static void setVlenMemManager(
            H5PropertyListId^ plistId,
            H5AllocCallback^ allocCallback,
            System::IntPtr allocInfo,
            H5FreeCallback^ freeCallback,
            System::IntPtr freeInfo);

        ///<summary>
        /// Sets a data transform expression.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetDataTransform"/>
        ///</summary>
        static void setDataTransform(
            H5PropertyListId^ plistId,
            System::String^ expression);

        ///<summary>
        /// Retrieves a data transform expression.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-GetDataTransform"/>
        ///</summary>
        static System::String^ getDataTransform(H5PropertyListId^ plistId);

        ///<summary>
        /// Specifies in property list whether to create missing intermediate groups.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetCreateIntermediateGroup"/>
        ///</summary>
        static void SetIntermediateGroupCreation(H5PropertyListId^ plistId, bool flag);

        ///<summary>
        /// Sets creation order tracking and indexing for links in a group.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetLinkCreationOrder"/>
        ///</summary>
        ///<param name="plistId">
        /// IN: Identifier for the group creation property list.
        ///</param>
        ///<param name="indexed">
        /// IN: If true, links in the group are indexed on creation order.
        ///</param>
        static void SetLinkCreationOrder(H5PropertyListId^ plistId, bool indexed);

        ///<summary>
        /// Sets the fill value for a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetFillValue"/>
        ///</summary>
        generic <class Type>
        static void setFillValue(H5PropertyListId^ plistId,
            H5DataTypeId^ typeId,
            Type value);


    private:

        H5P() {};

    };
}
