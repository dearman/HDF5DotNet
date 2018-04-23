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

#include "hvl_t.h"

namespace HDF5DotNet
{
   /// <summary>
   /// Variable length data specifier.
   /// </summary>
   [System::Runtime::InteropServices::StructLayout(
    System::Runtime::InteropServices::LayoutKind::Sequential)]
   public value struct VLen
   {

      System::IntPtr Length;   /* Length of VL data (in base type units) */
      System::IntPtr Pointer;  /* Pointer to VL data */

      VLen(System::IntPtr length, System::IntPtr pointer)
      {
          Length = length;
          Pointer = pointer;
      }

      VLen(hvl_t vl)
      {
          Length = System::IntPtr(
              (System::IntPtr::Size == 4) ? safe_cast<System::Int32>(vl.len) : safe_cast<System::Int64>(vl.len)) ;
          Pointer = System::IntPtr(vl.p);
      }

      hvl_t To_hvl_t()
      {
          hvl_t result;
          result.len = safe_cast<size_t>((System::IntPtr::Size == 4) ? Length.ToInt32() : Length.ToInt64());
          result.p = Pointer.ToPointer();
          return result;
      }
   };
}