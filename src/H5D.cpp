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

#include "H5D.h"
#include "H5DataSetId.h"
#include "H5DataSpaceId.h"
#include "H5DataTypeId.h"
#include "H5FileOrGroupId.h"
#include "H5PropertyListId.h"
#include "HDFExceptionSubclasses.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
   H5DataSetId^ H5D::create(H5FileOrGroupId^ groupOrFileId, 
      String^ datasetName,
      H5T::H5Type dataType,
      H5DataSpaceId^ dataSpaceId)
   {
      H5DataSetId^ dataset = H5D::create(
         groupOrFileId, 
         datasetName, 
         gcnew H5DataTypeId(dataType),
         dataSpaceId,
         gcnew H5PropertyListId(0),
         gcnew H5PropertyListId(0),
         gcnew H5PropertyListId(0) );

      return dataset;
   }

   H5DataSetId^ H5D::create(H5FileOrGroupId^ groupOrFileId, 
      String^ datasetName,
      H5DataTypeId^ dataType,
      H5DataSpaceId^ dataSpaceId)
   {
      return H5D::create(
         groupOrFileId, 
         datasetName, 
         dataType,
         dataSpaceId,
         gcnew H5PropertyListId(0),
         gcnew H5PropertyListId(0),
         gcnew H5PropertyListId(0) );
   }

   H5DataSetId^ H5D::create(
      H5FileOrGroupId^ groupOrFileId, 
      String^ datasetName,
      H5T::H5Type dataType,
      H5DataSpaceId^ dataSpaceId,
      H5PropertyListId^ linkCreationPropertyList,
      H5PropertyListId^ dataSetCreationPropertyList,
      H5PropertyListId^ dataSetAccessPropertyList)
   {

      return 
         H5D::create(
         groupOrFileId,
         datasetName,
         gcnew H5DataTypeId(dataType),
         dataSpaceId,
         linkCreationPropertyList,
         dataSetCreationPropertyList,
         dataSetAccessPropertyList);
   }


   H5DataSetId^ H5D::create(
      H5FileOrGroupId^ groupOrFileId, 
      String^ datasetName,
      H5DataTypeId^ dataType,
      H5DataSpaceId^ dataSpaceId,
      H5PropertyListId^ linkCreationPropertyList,
      H5PropertyListId^ dataSetCreationPropertyList,
      H5PropertyListId^ dataSetAccessPropertyList)
   {
      hid_t status = H5Dcreate2(groupOrFileId->Id, 
         datasetName, 
         dataType->Id,
         dataSpaceId->Id,
         linkCreationPropertyList->Id,
         dataSetCreationPropertyList->Id,
         dataSetAccessPropertyList->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.create: \n"
            "  Failed to create dataset with status = {0}\n"
            "    groupOrFileId = {1:x}\n"
            "    datasetName = {2}\n"
            "    dataType = {3:x}\n"
            "    dataspaceId = {4:x}\n",
            status, groupOrFileId->Id, datasetName, dataType->Id, 
            dataSpaceId->Id);
         throw gcnew H5DcreateException(message, status);
      }

      return gcnew H5DataSetId(status);
   }

   void H5D::close(H5DataSetId^ id)	
   {
      herr_t status = H5Dclose(id->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.close: \n"
            "  Failed to close data set {0:x} with status {1}\n",
            id->Id, status);

         throw gcnew H5DcloseException(message, status);
      }
   }

   generic <class Type>
   void H5D::write(H5DataSetId^ dataSetId,
      H5DataTypeId^ memTypeId,
      H5DataSpaceId^ memSpaceId,
      H5DataSpaceId^ fileSpaceId,
      H5PropertyListId^ xferPropListId,
      H5Array<Type>^ data)
   {
      pin_ptr<Type> pinnedDataPtr = data->getDataAddress();
      void* voidPtr = pinnedDataPtr;

      // Write using the pinned array
      herr_t status = H5Dwrite(dataSetId->Id, 
         memTypeId->Id,
         memSpaceId->Id, fileSpaceId->Id, 
         xferPropListId->Id, voidPtr);
      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.write: \n"
            "Failed to write data to data set {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DwriteException(message, status);
      }
   }

   generic <class Type>
   void H5D::writeScalar(H5DataSetId^ dataSetId,
      H5DataTypeId^ memTypeId,
      H5DataSpaceId^ memSpaceId,
      H5DataSpaceId^ fileSpaceId,
      H5PropertyListId^ xferPropListId,
      Type% data)
   {
      pin_ptr<Type> pinnedDataPtr = &data;
      void* voidPtr = pinnedDataPtr;

      // Write using the pinned array
      herr_t status = H5Dwrite(dataSetId->Id, 
         memTypeId->Id,
         memSpaceId->Id, fileSpaceId->Id, 
         xferPropListId->Id, voidPtr);
      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.write: \n"
            "Failed to write data to data set {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DwriteException(message, status);
      }
   }

   generic <class Type>
   void H5D::write(H5DataSetId^ dataSetId,
      H5DataTypeId^ dataType, 
      H5Array<Type>^ data)
   {
      // Write using the pinned array
      H5D::write(dataSetId, 
         dataType,
         gcnew H5DataSpaceId(H5S::H5SType::ALL), 
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5PropertyListId(H5P::Template::DEFAULT), 
         data);

   }

   generic <class Type>
   void H5D::writeScalar(H5DataSetId^ dataSetId,
      H5DataTypeId^ dataType, 
      Type% data)
   {
      H5D::writeScalar(dataSetId, 
         dataType,
         gcnew H5DataSpaceId(H5S::H5SType::ALL), 
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5PropertyListId(H5P::Template::DEFAULT), 
         data);
   }

   generic <class Type>
   void H5D::read(H5DataSetId^ dataSetId,
      H5DataTypeId^ memTypeId,
      H5DataSpaceId^ memSpaceId,
      H5DataSpaceId^ fileSpaceId,
      H5PropertyListId^ xferPropListId,
      H5Array<Type>^ data)
   {
      pin_ptr<Type> pinnedDataPtr = data->getDataAddress();
      void* voidPtr = pinnedDataPtr;

      // Read using the pinned array
      herr_t status = H5Dread(dataSetId->Id, 
         memTypeId->Id,
         memSpaceId->Id, fileSpaceId->Id, 
         xferPropListId->Id, voidPtr);
      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.read: \n"
            "Failed to read data to data set {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DreadException(message, status);
      }
   }

   generic <class Type>
   void H5D::readScalar(H5DataSetId^ dataSetId,
      H5DataTypeId^ memTypeId,
      H5DataSpaceId^ memSpaceId,
      H5DataSpaceId^ fileSpaceId,
      H5PropertyListId^ xferPropListId,
      Type% data)
   {
      pin_ptr<Type> pinnedDataPtr = &data;
      void* voidPtr = pinnedDataPtr;

      // Read using the pinned array
      herr_t status = H5Dread(dataSetId->Id, 
         memTypeId->Id,
         memSpaceId->Id, fileSpaceId->Id, 
         xferPropListId->Id, voidPtr);
      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.read: \n"
            "Failed to read data to data set {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DreadException(message, status);
      }
   }

   generic <class Type>
   void H5D::vlenReclaim(H5DataTypeId^ typeId,
      H5DataSpaceId^ spaceId,
      H5PropertyListId^ plistId,
      H5Array<Type>^ data)
   {
      // Pin the array in place.
      pin_ptr<Type> pinnedDataPtr = data->getDataAddress();
      void* voidPtr = pinnedDataPtr;

      // Reclaim using the pinned array.
      herr_t status = H5Dvlen_reclaim(typeId->Id, 
         spaceId->Id,
         plistId->Id,
         voidPtr);
      // Check status.
      if (status < 0)
      {
         // Throw on error.

         String^ message = String::Format(
            "H5D.vlenReclaim:\n"
            "  Failed to reclaim buffer:\n"
            "  type id: {0:x}\n"
            "  space id: {1:x}\n"
            "  propertyList id: {2:x}\n"
            " with status {3}\n",
            typeId->Id,
            spaceId->Id, 
            plistId->Id, 
            status);

         throw gcnew H5DvlenReclaimException(message, status);
      }
   }

   generic <class Type>
   void H5D::read(H5DataSetId^ dataSetId, H5DataTypeId^ dataType, 
      H5Array<Type>^ data)
   {
      read(dataSetId, 
         dataType,
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5PropertyListId(H5P::Template::DEFAULT), 
         data);
   }

   generic <class Type>
   void H5D::readScalar(H5DataSetId^ dataSetId,
      H5DataTypeId^ dataType,
      Type% data)
   {
      readScalar(dataSetId, 
         dataType,
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5DataSpaceId(H5S::H5SType::ALL),
         gcnew H5PropertyListId(H5P::Template::DEFAULT), 
         data);
   }

   H5DataSetId^ H5D::open(H5FileOrGroupId^ groupOrFileId, String^ dataSetName)
   {
      return
         H5D::open(groupOrFileId, dataSetName, 
         gcnew H5PropertyListId(H5P::Template::DEFAULT));
   }

   H5DataSetId^ H5D::open(H5FileOrGroupId^ groupOrFileId, 
      String^ dataSetName,
      H5PropertyListId^ dataSetAccessPropertyList)
   {
      herr_t status = H5Dopen2(groupOrFileId->Id, dataSetName,
         dataSetAccessPropertyList->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.open: \n"
            "Failed to open data set {0} from groupOrFileId {1:x} with status {2}\n",
            dataSetName, groupOrFileId->Id, status);

         throw gcnew H5DopenException(message, status);
      }

      return gcnew H5DataSetId(status);
   }

   H5PropertyListId^ H5D::getCreatePropertyList(H5DataSetId^ dataSetId)
   {
      herr_t status = H5Dget_create_plist(dataSetId->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.getCreatePropertyList: \n"
            "Failed to get create property list for dataSetid {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DgetCreatePropertyListException(message, status);
      }

      return gcnew H5PropertyListId(status);
   }

   H5DataSpaceId^ H5D::getSpace(H5DataSetId^ dataSetId)
   {
      herr_t status = H5Dget_space(dataSetId->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.getSpace: \n"
            "Failed to get space for dataSetid {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DgetSpaceException(message, status);
      }

      return gcnew H5DataSpaceId(status);
   }

   H5DataTypeId^ H5D::getType(H5DataSetId^ dataSetId)
   {
      herr_t status = H5Dget_type(dataSetId->Id);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.getType: \n"
            "Failed to get type for dataSetid {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DgetTypeException(message, status);
      }

      return gcnew H5DataTypeId(status);
   }

   hssize_t H5D::getStorageSize(H5DataSetId^ dataSetId)
   {
      return safe_cast<hssize_t>(H5Dget_storage_size(dataSetId->Id));
   }

   void H5D::setExtent(H5DataSetId^ dataSetId, array<hssize_t>^ size)
   {
      array<hsize_t>^ sizeCopy = gcnew array<hsize_t>(size->Length);
	  for (int i = 0; i < size->Length; ++i)
		  sizeCopy[i] = safe_cast<hsize_t>(size[i]);

      pin_ptr<hsize_t> pptr = &sizeCopy[0];
      hsize_t* ptr = pptr;

      herr_t status = H5Dset_extent(dataSetId->Id, ptr);

      if (status < 0)
      {
         String^ message = String::Format(
            "H5D.setExtent: \n"
            "Failed to get type for dataSetid {0:x} with status {1}\n",
            dataSetId->Id, status);

         throw gcnew H5DsetExtentException(message, status);
      }
   }

}
