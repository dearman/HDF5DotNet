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

#include "H5Array.h"

// The HDF5DotNet namespace contains all the .NET wrappers for HDF5 library
// calls.
namespace HDF5DotNet
{
   /// <summary>
   /// H5CrtHeap provides allocation and deallocation from the "C" 
   /// run-time heap.  This memory is not garbage collected, so it can be
   /// used with void pointers that are passed to the HDF5 library.  To avoid
   /// memory leaks, all memory allocated with alloc must be freed with free.
   /// </summary>
   public ref class H5CrtHeap sealed
   {
   public:

      /// <summary>
      /// Allocate  memory from the "C" run-time heap.
      /// </summary>
      /// <param name="size">
      ///  Size of memory to allocate in bytes.
      /// </param>
      static System::IntPtr Allocate(System::IntPtr size);

      [System::CLSCompliant(false)]
      static System::UIntPtr Allocate(System::UIntPtr size);
	 
      /// <summary>
      /// Deallocate memory that was previously allocated with
      /// H5CrtHeap.alloc().
      /// </summary>
      /// <param name="memory">
      /// memory is a pointer to memory previously allocted with 
      /// H5CrtHeap.alloc().
      /// </param>
      static void Free(System::IntPtr memory);

      [System::CLSCompliant(false)]
      static void Free(System::UIntPtr memory);

   private:

      H5CrtHeap() {}
   };

   /// <summary>
   /// H5Memory allocate and deallocates memory from the "C" run-time heap
   /// and wraps it so that it can be used from other .NET languages without
   /// using unsafe. 
   /// </summary>
   public ref class H5Memory
   {
   public:

      /// <summary>
      /// Create an instance of H5Memory containing a null pointer.
      /// </summary>
      H5Memory();

      /// <summary>
      /// Create an instance of H5Memory allocating a specified 
      /// amount of memory from the "C" run-time heap.
      /// </summary>
      /// <param name="size">
      ///  Number of bytes to allocate.
      /// </param>
      H5Memory(System::IntPtr size);

	  [System::CLSCompliant(false)]
	  H5Memory(System::UIntPtr size);

      /// <summary>
      /// Size (in bytes) of the allocated memory.
      /// </summary>
      property System::IntPtr Size { System::IntPtr get(); }

      /// <summary>
      /// Pointer to the allocated memory.
      /// </summary>
      property System::IntPtr Pointer { System::IntPtr get(); }

      /// <summary>
      /// Copy nElements from the specified array into the allocated memory.
      /// </summary>
      /// <param name="theArray">
      ///  Array to copy.
      /// </param>
      /// <param name="nElements">
      ///  The number of elements to copy.
      /// </param>
      generic<class Type>
      void H5Memory::Set(H5Array<Type>^ theArray, System::IntPtr nElements);

	  generic<class Type>
	  [System::CLSCompliant(false)]
	  void H5Memory::Set(H5Array<Type>^ theArray, System::UIntPtr nElements);

      /// <summary>
      /// Copy a value to the location in the allocated memory that 
      /// would correspond to memory[index] if the H5Memory were an array
      /// of the same type as the value.
      /// </summary>
      /// <param name="index">
      ///  Offset into array - units are elements of Type (not bytes).
      /// </param>
      generic<class Type>
      void SetElement(System::IntPtr index, Type% value);

	  generic<class Type>
	  [System::CLSCompliant(false)]
	  void SetElement(System::UIntPtr index, Type% value);

	  /// <summary>
      /// Get a value from the location in the allocated memory that 
      /// would correspond to memory[index] if the H5Memory were an array
      /// of the type specified.
      /// </summary>
      /// <param name="index">
      ///  Offset into array - units are elements of Type (not bytes).
      /// </param>
      generic<class Type>
      Type H5Memory::GetElement(System::IntPtr index);

	  generic<class Type>
	  [System::CLSCompliant(false)]
	  Type H5Memory::GetElement(System::UIntPtr index);

      /// <summary>
      /// Destructor for H5Memory (deallocated memory if not previously 
      /// deallocted.)
      /// </summary>
      ~H5Memory();

      /// <summary>
      /// Finalize destructor for H5Memory (deallocated memory if not 
      /// previously deallocted.)
      /// </summary>
      !H5Memory();

   private:
      /// <summary>
      /// Size of allocated memory in bytes.
      /// </summary>
      size_t m_size;

      /// <summary>
      /// Pointer to allocated memory.
      /// </summary>
      void* m_memory;

      /// <summary>
      /// Flag is true if memory_ points to allocated memory - false if 
      /// memory has not been allocated or if previously allocated memory 
      /// has been deallocated. 
      /// </summary>
      bool m_memoryIsAllocated;
   };
}

