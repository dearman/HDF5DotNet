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

#include "H5Array.h"
#include "H5Memory.h"
#include "IntPtrAux.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

namespace HDF5DotNet
{

   IntPtr H5CrtHeap::Allocate(IntPtr size)
   {
      return IntPtr(reinterpret_cast<void*>(new char[IntPtrAux::ToSize_t(size)]));
   }

   UIntPtr H5CrtHeap::Allocate(UIntPtr size)
   {
	   return UIntPtr(reinterpret_cast<void*>(new char[IntPtrAux::ToSize_t(size)]));
   }

   void H5CrtHeap::Free(IntPtr memory)
   {
      delete [] memory.ToPointer();
   }

   void H5CrtHeap::Free(UIntPtr memory)
   {
	   delete [] memory.ToPointer();
   }

   H5Memory::H5Memory() : m_size(0), m_memory(0), m_memoryIsAllocated(true)
   {
   }

   H5Memory::H5Memory(IntPtr size) : m_size(IntPtrAux::ToSize_t(size))
   {
      m_memory = reinterpret_cast<void*>(new char[IntPtrAux::ToSize_t(size)]);
      m_memoryIsAllocated = (m_memory != 0);
   }

   H5Memory::H5Memory(UIntPtr size) : m_size(IntPtrAux::ToSize_t(size))
   {
	   m_memory = reinterpret_cast<void*>(new char[IntPtrAux::ToSize_t(size)]);
	   m_memoryIsAllocated = (m_memory != 0);
   }

   IntPtr H5Memory::Size::get()
   {
      return IntPtr((IntPtr::Size == 4) ?
          safe_cast<Int32>(m_size) : safe_cast<Int64>(m_size));
   }

   IntPtr H5Memory::Pointer::get() 
   {
      return IntPtr(m_memory);
   }

   generic<class Type>
   void H5Memory::Set(H5Array<Type>^ theArray, IntPtr nElements)
   {
      size_t typeSize = sizeof(Type);

      interior_ptr<Type> ptr = theArray->getDataAddress();
      pin_ptr<Type> tPtr(ptr);
      char* cPtr = reinterpret_cast< char* >(tPtr);

      char* memPtr = reinterpret_cast<char*>(m_memory);

      size_t nBytes = IntPtrAux::ToSize_t(nElements)*typeSize;

      for(size_t i=0;i<nBytes;i++)
      {
         *memPtr++ = *cPtr++;
      }
   }

   generic<class Type>
   void H5Memory::Set(H5Array<Type>^ theArray, UIntPtr nElements)
   {
	   size_t typeSize = sizeof(Type);

	   interior_ptr<Type> ptr = theArray->getDataAddress();
	   pin_ptr<Type> tPtr(ptr);
	   char* cPtr = reinterpret_cast< char* >(tPtr);

	   char* memPtr = reinterpret_cast<char*>(m_memory);

	   size_t nBytes = IntPtrAux::ToSize_t(nElements)*typeSize;

	   for(size_t i=0;i<nBytes;i++)
	   {
		   *memPtr++ = *cPtr++;
	   }
   }

   generic<class Type>
   void H5Memory::SetElement(IntPtr index, Type% value)
   {
      size_t typeBytes = sizeof(Type);

      // Get a pinned byte pointer to the value.
      interior_ptr<Type> ptr = &value;
      pin_ptr<Type> tPtr(ptr);
      char* cPtr = reinterpret_cast< char* >(tPtr);

      // Find the correct place in memory
      char* memPtr = reinterpret_cast<char*>(m_memory);
      memPtr = memPtr + (IntPtrAux::ToSize_t(index)*typeBytes);

      for(size_t i=0;i<typeBytes;i++)
      {
         *memPtr++ = *cPtr++;
      }
   }

   generic<class Type>
   void H5Memory::SetElement(UIntPtr index, Type% value)
   {
	   size_t typeBytes = sizeof(Type);

	   // Get a pinned byte pointer to the value.
	   interior_ptr<Type> ptr = &value;
	   pin_ptr<Type> tPtr(ptr);
	   char* cPtr = reinterpret_cast< char* >(tPtr);

	   // Find the correct place in memory
	   char* memPtr = reinterpret_cast<char*>(m_memory);
	   memPtr = memPtr + (IntPtrAux::ToSize_t(index)*typeBytes);

	   for(size_t i=0;i<typeBytes;i++)
	   {
		   *memPtr++ = *cPtr++;
	   }
   }

   generic<class Type>
   Type H5Memory::GetElement(IntPtr index)
   {
      Type value;
      size_t typeBytes = sizeof(value);

      // Get a pinned byte pointer to the value.
      interior_ptr<Type> ptr = &value;
      pin_ptr<Type> tPtr(ptr);
      char* cPtr = reinterpret_cast< char* >(tPtr);

      // Find the correct place in memory
      char* memPtr = reinterpret_cast<char*>(m_memory);
      memPtr = memPtr + (IntPtrAux::ToSize_t(index)*typeBytes);

      for(size_t i=0;i<typeBytes;i++)
      {
         *cPtr++ = *memPtr++;
      }

      return value;
   }

   generic<class Type>
   Type H5Memory::GetElement(UIntPtr index)
   {
	   Type value;
	   size_t typeBytes = sizeof(value);

	   // Get a pinned byte pointer to the value.
	   interior_ptr<Type> ptr = &value;
	   pin_ptr<Type> tPtr(ptr);
	   char* cPtr = reinterpret_cast< char* >(tPtr);

	   // Find the correct place in memory
	   char* memPtr = reinterpret_cast<char*>(m_memory);
	   memPtr = memPtr + (IntPtrAux::ToSize_t(index)*typeBytes);

	   for(size_t i=0;i<typeBytes;i++)
	   {
		   *cPtr++ = *memPtr++;
	   }

	   return value;
   }

   H5Memory::~H5Memory()
   {
      if (m_memoryIsAllocated)
      {
         delete [] m_memory;
      }
   }

   H5Memory::!H5Memory()
   {
      if (m_memoryIsAllocated)
      {
         delete [] m_memory;
      }
   }
}

