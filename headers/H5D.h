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

#include "H5T.h"

#include "H5Dpublic.h"

namespace HDF5DotNet
{
    ref class H5DataSpaceId;
    ref class H5PropertyListId;

    /// <summary>
    /// The H5D contains static member function for each of the supported
    /// H5D calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html"/>
    /// </summary>
    public ref class H5D sealed
    {
    public:

        /// <summary>
        /// Enumeration for storage layout strategy.
        /// </summary>
        enum class Layout 
        {
            ///<summary> Compact </summary>
            COMPACT = H5D_COMPACT,

            ///<summary> Contiguous </summary>
            CONTIGUOUS = H5D_CONTIGUOUS,

            ///<summary> Chunked </summary>
            CHUNKED = H5D_CHUNKED,

            ///<summary> No strategy </summary>
            NLAYOUTS = H5D_NLAYOUTS
        };

#pragma region documentation
        ///<summary>
        /// Creates a new dataset and links it into the file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Create"/>
        ///</summary>

        ///<param name="groupOrFileId">
        /// IN: Location identifier
        ///</param>

        ///<param name="dataSetName">
        /// IN: Dataset name
        ///</param>

        ///<param name="dataType">
        /// IN: H5T::H5Type dataType
        ///</param>

        ///<param name="dataspaceId">
        /// IN: Dataspace identifier
        ///</param>

        /// <returns>
        /// A H5DataSetId associated with the created dataset.
        /// </returns>

        /// <exception cref="H5DcreateException">
        /// throws H5DcreateException on failure.
        /// </exception>
#pragma endregion documentation

        static H5DataSetId^ create(H5FileOrGroupId^ groupOrFileId, 
            System::String^ dataSetName,
            H5T::H5Type dataType,
            H5DataSpaceId^ dataspaceId);

#pragma region documentation
        ///<summary>
        /// Creates a new dataset and links it into the file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Create"/>
        ///</summary>

        ///<param name="groupOrFileId">
        /// IN: Location identifier
        ///</param>

        ///<param name="dataSetName">
        /// IN: Dataset name
        ///</param>

        ///<param name="dataTypeId">
        /// IN: Datatype identifier
        ///</param>

        ///<param name="dataspaceId">
        /// IN: Dataspace identifier
        ///</param>

        /// <returns>
        /// A H5DataSetId associated with the created dataset.
        /// </returns>

        /// <exception cref="H5DcreateException">
        /// throws H5DcreateException on failure.
        /// </exception>
#pragma endregion documentation

        static H5DataSetId^ create(H5FileOrGroupId^ groupOrFileId, 
            System::String^ dataSetName,
            H5DataTypeId^ dataTypeId,
            H5DataSpaceId^ dataspaceId);

#pragma region documentation
        ///<summary>
        /// Creates a new dataset and links it into the file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Create"/>
        ///</summary>

        ///<param name="groupOrFileId">
        /// IN: Location identifier
        ///</param>

        ///<param name="dataSetName">
        /// IN: Dataset name
        ///</param>

        ///<param name="dataType">
        /// IN: H5T::H5Type dataType
        ///</param>

        ///<param name="dataspaceId">
        /// IN: Dataspace identifier
        ///</param>

        ///<param name="linkCreationPropertyList">
        /// IN: Link creation property list
        ///</param>

        ///<param name="dataSetCreationPropertyList">
        /// IN: Dataset creation property list
        ///</param>

        ///<param name="dataSetAccessPropertyList">
        /// IN: Dataset access property list
        ///</param>

        /// <returns>
        /// A H5DataSetId associated with the created dataset.
        /// </returns>

        /// <exception cref="H5DcreateException">
        /// throws H5DcreateException on failure.
        /// </exception>
#pragma endregion documentation

        static H5DataSetId^ create(
            H5FileOrGroupId^ groupOrFileId,
            System::String^ dataSetName,
            H5T::H5Type dataType,
            H5DataSpaceId^ dataspaceId,
            H5PropertyListId^ linkCreationPropertyList,
            H5PropertyListId^ dataSetCreationPropertyList,
            H5PropertyListId^ dataSetAccessPropertyList);

#pragma region documentation
        ///<summary>
        /// Creates a new dataset and links it into the file.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Create"/>
        ///</summary>

        ///<param name="groupOrFileId">
        /// IN: Location identifier
        ///</param>

        ///<param name="dataSetName">
        /// IN: Dataset name
        ///</param>

        ///<param name="dataType">
        /// IN: Datatype identifier
        ///</param>

        ///<param name="dataspaceId">
        /// IN: Dataspace identifier
        ///</param>

        ///<param name="linkCreationPropertyList">
        /// IN: Link creation property list
        ///</param>

        ///<param name="dataSetCreationPropertyList">
        /// IN: Dataset creation property list
        ///</param>

        ///<param name="dataSetAccessPropertyList">
        /// IN: Dataset access property list
        ///</param>

        /// <returns>
        /// A H5DataSetId associated with the created dataset.
        /// </returns>

        /// <exception cref="H5DcreateException">
        /// throws H5DcreateException on failure.
        /// </exception>
#pragma endregion documentation

        static H5DataSetId^ create(
            H5FileOrGroupId^ groupOrFileId,
            System::String^ dataSetName,
            H5DataTypeId^ dataType,
            H5DataSpaceId^ dataspaceId,
            H5PropertyListId^ linkCreationPropertyList,
            H5PropertyListId^ dataSetCreationPropertyList,
            H5PropertyListId^ dataSetAccessPropertyList);

#pragma region documentation
        ///<summary>
        /// Reclaims VL datatype memory buffers.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-VLReclaim"/>
        ///</summary>

        ///<param name="typeId">
        /// IN: Identifier of the datatype.
        ///</param>

        ///<param name="spaceId">
        /// IN: Identifier of the dataspace.
        ///</param>

        ///<param name="plistId">
        /// IN: Identifier of the property list used to create the buffer.
        ///</param>

        ///<param name="data">
        /// IN: The buffer to be reclaimed.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5DvlenReclaimException">
        /// throws H5DvlenReclaimException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void vlenReclaim(H5DataTypeId^ typeId,
            H5DataSpaceId^ spaceId,
            H5PropertyListId^ plistId,
            H5Array<Type>^ data);

#pragma region documentation
        ///<summary>
        /// Writes raw data from a buffer to a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Write"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset to write to.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="memSpaceId">
        /// IN: Identifier of the memory dataspace.
        ///</param>

        ///<param name="fileSpaceId">
        /// IN: Identifier of the dataset's dataspace in the file.
        ///</param>

        ///<param name="xferPropListId">
        /// IN: Identifier of a transfer property list for this I/O operation.
        ///</param>

        ///<param name="data">
        /// IN: Array with data to be written to the file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5DwriteException">
        /// throws H5DwriteException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void write(H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId,
            H5DataSpaceId^ memSpaceId,
            H5DataSpaceId^ fileSpaceId,
            H5PropertyListId^ xferPropListId,
            H5Array<Type>^ data);

#pragma region documentation
        ///<summary>
        /// Writes raw data from a buffer to a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Write"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset to write to.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="memSpaceId">
        /// IN: Identifier of the memory dataspace.
        ///</param>

        ///<param name="fileSpaceId">
        /// IN: Identifier of the dataset's dataspace in the file.
        ///</param>

        ///<param name="xferPropListId">
        /// IN: Identifier of a transfer property list for this I/O operation.
        ///</param>

        ///<param name="data">
        /// IN: Memory with data to be written to the file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5DwriteException">
        /// throws H5DwriteException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void writeScalar(H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId,
            H5DataSpaceId^ memSpaceId,
            H5DataSpaceId^ fileSpaceId,
            H5PropertyListId^ xferPropListId,
            Type% data);

#pragma region documentation
        ///<summary>
        /// Writes raw data from a buffer to a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Write"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset to write to.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="data">
        /// IN: Array with data to be written to the file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5DwriteException">
        /// throws H5DwriteException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void write(H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId, 
            H5Array<Type>^ data);

#pragma region documentation
        ///<summary>
        /// Writes raw data from a buffer to a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Write"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset to write to.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="data">
        /// IN: Memory with data to be written to the file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5DwriteException">
        /// throws H5DwriteException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void writeScalar(H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId, 
            Type% data);

#pragma region documentation
        ///<summary>
        /// Reads raw data from a dataset into a buffer.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Read"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset read from.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="memSpaceId">
        /// IN: Identifier of the memory dataspace.
        ///</param>

        ///<param name="fileSpaceId">
        /// IN: Identifier of the dataset's dataspace in the file.
        ///</param>

        ///<param name="xferPropListId">
        /// IN: Identifier of a transfer property list for this I/O operation.
        ///</param>

        ///<param name="data">
        /// OUT: Array to receive data read from file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5DreadException">
        /// throws H5DreadException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void read(H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId,
            H5DataSpaceId^ memSpaceId,
            H5DataSpaceId^ fileSpaceId,
            H5PropertyListId^ xferPropListId,
            H5Array<Type>^ data);

#pragma region documentation
        ///<summary>
        /// Reads raw data from a dataset into a buffer.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Read"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset read from.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="memSpaceId">
        /// IN: Identifier of the memory dataspace.
        ///</param>

        ///<param name="fileSpaceId">
        /// IN: Identifier of the dataset's dataspace in the file.
        ///</param>

        ///<param name="xferPropListId">
        /// IN: Identifier of a transfer property list for this I/O operation.
        ///</param>

        ///<param name="data">
        /// OUT: Memory to receive data read from file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5DreadException">
        /// throws H5DreadException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void readScalar(
            H5DataSetId^ dataSetId,
            H5DataTypeId^ memTypeId,
            H5DataSpaceId^ memSpaceId,
            H5DataSpaceId^ fileSpaceId,
            H5PropertyListId^ xferPropListId,
            Type% data);

#pragma region documentation
        ///<summary>
        /// Reads raw data from a dataset into a buffer.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Read"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset read from.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="data">
        /// OUT: Array to receive data read from file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5DreadException">
        /// throws H5DreadException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void read(H5DataSetId^ dataSetId, 
            H5DataTypeId^ memTypeId, 
            H5Array<Type>^ data);

#pragma region documentation
        ///<summary>
        /// Reads raw data from a dataset into a buffer.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Read"/>
        ///</summary>

        ///<param name="dataSetId">
        /// IN: Identifier of the dataset read from.
        ///</param>

        ///<param name="memTypeId">
        /// IN: Identifier of the memory datatype.
        ///</param>

        ///<param name="data">
        /// OUT: Memory to receive data read from file.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5DreadException">
        /// throws H5DreadException on failure.
        /// </exception>
#pragma endregion documentation

        generic <class Type>
        static void readScalar(H5DataSetId^ dataSetId, 
            H5DataTypeId^ memTypeId, 
            Type% data);

#pragma region documentation
        /// <summary>
        /// Close a data set.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Close"/>
        /// </summary>
        /// <param name="id">
        /// IN: Id of data set to close.
        /// </param>
        /// <exception cref="H5DcloseException"> 
        /// throws H5DcloseException if close fails
        /// </exception>
#pragma endregion documentation
        static void close(H5DataSetId^ id);	

#pragma region documentation
        /// <summary>
        /// Opens an existing dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Open"/>
        /// </summary>
        /// <param name="groupOrFileId">
        /// IN: Identifier of the file or
        /// group within which the dataset to be accessed will be found. 
        /// </param>
        /// <param name="dataSetName">
        /// IN: The name of the dataset to access.
        /// </param>
        /// <exception cref="H5DopenException">
        /// throws H5DopenException on failure.
        /// </exception>
        /// <remarks>
        /// H5Dopen opens an existing dataset for access in the file or 
        /// group specified in groupOrFileId. name is a dataset name and 
        /// is used to identify the dataset in the file.
        /// </remarks>
#pragma endregion documentation

        static H5DataSetId^ open(H5FileOrGroupId^ groupOrFileId, 
            System::String^ dataSetName);

#pragma region documentation
        /// <summary>
        /// Opens an existing dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Open"/>
        /// </summary>
        /// <param name="groupOrFileId">
        /// IN: Identifier of the file or
        /// group within which the dataset to be accessed will be found. 
        /// </param>
        /// <param name="dataSetName">
        /// IN: The name of the dataset to access.
        /// </param>
        /// <param name="dataSetAccessPropertyList">
        /// IN: Dataset access property list
        /// </param>
        /// <exception cref="H5DopenException">
        /// throws H5DopenException on failure.
        /// </exception>
        /// <remarks>
        /// H5Dopen opens an existing dataset for access in the file or 
        /// group specified in groupOrFileId. name is a dataset name and 
        /// is used to identify the dataset in the file.
        /// </remarks>
#pragma endregion documentation

        static H5DataSetId^ open(H5FileOrGroupId^ groupOrFileId, 
            System::String^ dataSetName,
            H5PropertyListId^ dataSetAccessPropertyList);

#pragma region documentation
        /// <summary>
        /// Returns an identifier for a copy of the dataset creation property list for a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetCreatePlist"/>
        /// </summary>
        /// <param name="dataSetId">
        /// IN: Identifier of the dataset to be accessed. 
        /// </param>
        /// <remarks>
        /// The creation property list identifier should be released with <c>H5Pclose</c>.
        /// </remarks>
#pragma endregion documentation

        static H5PropertyListId^ getCreatePropertyList(H5DataSetId^ dataSetId);

#pragma region documentation
        ///<summary>
        /// Returns an identifier for a copy of the dataspace for a
        ///dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetSpace"/>
        ///</summary>
        ///<param name="dataSetId">
        /// IN: Identifier of the dataset to query.
        ///</param>
        ///<returns>
        /// Returns a dataspace identifier if successful.
        ///</returns>
        ///<remarks>
        /// H5Dget_space returns an identifier for a copy of the dataspace
        ///for a dataset. The dataspace identifier should be released with
        ///the H5S.close function.
        ///</remarks>
        ///<exception cref="H5DgetSpaceException">
        /// throws H5DgetSpaceException on failure.
        ///</exception>
#pragma endregion documentation

        static H5DataSpaceId^ getSpace(H5DataSetId^ dataSetId);

#pragma region documentation
        ///<summary>
        /// Returns an identifier for a copy of the datatype for a
        ///dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetType"/>
        ///</summary>
        ///<param name="dataSetId">
        /// In: Identifier of dataset to query.
        ///</param>
        ///<returns>
        /// Returns a datatype identifier if successful.
        ///</returns>
        ///<exception cref="H5DgetTypeException">
        /// throws H5DgetTypeException on failure.
        ///</exception>
#pragma endregion documentation

        static H5DataTypeId^ getType(H5DataSetId^ dataSetId);

#pragma region documentation
        ///<summary>
        /// Returns the amount of storage required for a dataset.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetStorageSize"/>
        ///</summary>
        ///<param name="dataSetId">
        /// In: Identifier of dataset to query.
        ///</param>
        ///<returns>
        /// Returns the amount of storage space allocated for the dataset, 
        /// not counting meta data; otherwise returns 0 (zero).
        ///</returns>
#pragma endregion documentation

        static hssize_t getStorageSize(H5DataSetId^ dataSetId);

#pragma region documentation
        ///<summary>
        /// Changes the sizes of a dataset’s dimensions.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-SetExtent"/>
        ///</summary>
        ///<param name="dataSetId">
        /// In: Identifier of a dataset.
        ///</param>
        ///<param name="size">
        /// In: Array containing the new magnitude of each dimension of the dataset.
        ///</param>
#pragma endregion documentation

        static void setExtent(H5DataSetId^ dataSetId, array<hssize_t>^ size);

    private:
        // Disallow instances of this class.
        H5D() {};
    };
}
