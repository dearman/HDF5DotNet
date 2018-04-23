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
// This is the main DLL file.

#include "H5F.h"
#include "H5Ipublic.h"
#include "H5Tpublic.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

// This prototype is necessary to translate .NET string prototype
// to null-terminated ANSI string, char*, in the HDF library.
// Note: This differs from the current prototype in H5Fpublic.h and
// it will go in H5FpublicNET.h

#include "HDF5_Native.h"

namespace HDF5DotNet
{
   H5FileId^ H5F::create(String^ filename,
      CreateMode mode,
      H5PropertyListId^ create_id,
      H5PropertyListId^ access_id)
   {
      // Make the call to the "C" library.
      int id = H5Fcreate(filename, safe_cast<unsigned int>(mode), 
         create_id->Id, access_id->Id);

      // Check conditions and throw appropriately.
      if(id < 0)
      {
         throw gcnew 
            H5FcreateException("File \"" + filename + " failed to create.",
            id);
      }

      // Put the returned id into a H5Id object.
      H5FileId^ returnH5Id = gcnew H5FileId(id);

      return returnH5Id;
   }

   H5FileId^ H5F::create(String^ filename,
      CreateMode mode,
      H5PropertyListId^ create_id)
   {
      return create(filename, mode, create_id, 
         gcnew H5PropertyListId(H5P_DEFAULT));
   }

   H5FileId^ H5F::create(String^ filename,
      CreateMode mode)
   {
      return create(filename, mode, gcnew H5PropertyListId(H5P_DEFAULT), 
         gcnew H5PropertyListId(H5P_DEFAULT));
   }

   void H5F::flush(H5Id^ object_id,
       Scope scope)
   {
       herr_t status = -1;

	   // What kind of handle is this?
	   H5I_type_t info = H5Iget_type(object_id->Id);
	   if (info == H5I_BADID)
	   {
		   status = -1;
		   String^ message = 
			   String::Format(
			   "H5F.flush: object id: {0:x} failed! Bad ID!", object_id->Id);

		   throw gcnew HDFException(message, status);
	   }

	   // we can't flush transient types
	   if (info == H5I_DATATYPE)
	   {
		   if (H5Tcommitted(object_id->Id) <= 0)
		   {
			   status = -1;
			   String^ message = 
				   String::Format(
				   "H5F.flush: object id: {0:x} failed! Cannot flush transient type!", object_id->Id);

			   throw gcnew HDFException(message, status);
		   }
	   }

	   status = H5Fflush(object_id->Id, safe_cast<H5F_scope_t>(scope));
       if (status < 0)
	   {
		   String^ message = 
			   String::Format(
			   "H5F.flush: object id: {0:x} failed with error code {1}",
			   object_id->Id, status);

		   throw gcnew HDFException(message, status);
	   }
   }

   bool H5F::is_hdf5(String^ filename)
   {
       htri_t status = H5Fis_hdf5(filename);
       if(status < 0)
       {
           String^ message = 
            String::Format(
            "H5F.is_hdf5: file: {0} failed with error code {1}",
            filename, status);

           throw gcnew HDFException(message, status);
       }

       return (status > 0);
   }

   H5FileId^ H5F::open(String^ filename, OpenMode mode)
   {
      // Make the call to the "C" library.
      int id = H5Fopen(filename, safe_cast<unsigned int>(mode), H5P_DEFAULT);

      // Check conditions and throw appropriately.
      if(id < 0)
      {
         throw gcnew 
            H5FopenException("H5F.open\n"
            "  File \"" + filename + 
            "\"  failed to open with status " + id,
            id);
      }

      // Put the returned id into a H5Id object.
      H5FileId^ returnH5Id = gcnew H5FileId(id);

      return returnH5Id;
   }


   /// <summary> open an existing HDF5 file. </summary>
   H5FileId^ H5F::open(String^ filename,
      OpenMode mode, 
      H5PropertyListId^ propertyListId)
   {
      // Make the call to the "C" library.
      int id = H5Fopen(filename, safe_cast<unsigned int>(mode), 
         propertyListId->Id);

      // Check conditions and throw appropriately.
      if(id < 0)
      {
         throw gcnew 
            H5FopenException("H5F.open\n"
            "  File \"" + filename + 
            "\"  failed to open with status " + id,
            id);
      }

      // Put the returned id into a H5Id object.
      H5FileId^ returnH5Id = gcnew H5FileId(id);

      return returnH5Id;
   }


   void H5F::close(H5FileId^ id)
   {
      hid_t status = H5Fclose(id->Id);

      if (status < 0)
      {
         String^ message = 
            String::Format(
            "H5F.close: file id: {0:x} failed with error code {1}",
            id->Id, status);

         throw gcnew H5FcloseException(message, status);
      }
   }

   void H5F::Mount
       (
       H5FileOrGroupId^ locRef,
       String^          name,
       H5FileId^        fileRef
       )
   {
       H5PropertyListId^ plist = gcnew H5PropertyListId(H5P_DEFAULT);
       herr_t status = H5Fmount(locRef->Id, name, fileRef->Id, plist->Id);
       if (status < 0)
      {
         String^ message = 
            String::Format(
            "H5F.Mount: locRef: {0:x} name: {1} and fileRef: {2:x} failed with error code {3}",
            locRef->Id, name, fileRef->Id, status);
         throw gcnew HDFException(message, status);
      }
   }

   void H5F::Mount(
       H5FileOrGroupId^  locRef,
       String^           name,
       H5FileId^         fileRef,
       H5PropertyListId^ pList
       )
   {
       herr_t status = H5Fmount(locRef->Id, name, fileRef->Id, pList->Id);
       if (status < 0)
      {
         String^ message = 
            String::Format(
            "H5F.Mount: locRef: {0:x} name: {1} fileRef: {2:x} and pList: {3:x} failed with error code {4}",
            locRef->Id, name, fileRef->Id, pList->Id, status);
         throw gcnew HDFException(message, status);
      }
   }

   void H5F::Unmount(H5FileOrGroupId^ locRef, String^ name)
   {
       herr_t status = H5Funmount(locRef->Id, name);
       if (status < 0)
      {
         String^ message = 
            String::Format(
            "H5F.Unmount: locRef: {0:x}  and name: {1} failed with error code {2}",
            locRef->Id, name, status);
         throw gcnew HDFException(message, status);
      }
   }

}// end of namespace HDF5DotNet
