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
   /// <summary>
   /// HDFException is the base class for all HDF exception classes.
   /// </summary>
   public ref class HDFException : public System::ApplicationException
   {
   internal:

      // Unknown exception. 
      HDFException();

      /// <summary>
      /// HDF Exception that includes a text description. 
      /// </summary> 
      /// <param name="message"> a text description of the problem </param> 
      HDFException(System::String^ message, int errorCode);

      // 
      // HDF Exception that includes a text description and a previously
      // thrown exception.
      // 
      /// <param name="message"> a text description of the problem</param>
      /// <param name="previouslyThrownException"> When an exception is 
      /// thrown while handling a previous exception. previouslyThrownException 
      /// provides a handle to the previous exception. </param>
      HDFException(System::String^ message, 
         int errorCode,
         Exception^ previouslyThrownException);

   public:
      property int ErrorCode
      {
         int get() { return errorCode_; }
      }

   private:
      int errorCode_;
   };
}


