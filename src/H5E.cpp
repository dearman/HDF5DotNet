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

#include "H5E.h"
#include "HDFExceptionSubclasses.h"

#include "H5Epublic.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Eset_auto1
    (
    H5E_auto_t func,
    void* clientData
    );

#pragma unmanaged
typedef int (_cdecl *H5Auto)(int eStackId, void* clientData);

#pragma managed

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Eset_auto2
    (
    hid_t stackId, 
    //H5E_auto_t function,
    [In, MarshalAs(UnmanagedType::FunctionPtr)]
    HDF5DotNet::H5AutoCallback^ function,
    [In] void* clientData
    );

namespace HDF5DotNet
{
    void H5E::suppressPrinting(hid_t errorStackId)
    {
        // Use this uninitialized delegate to marshal as null in the
        // call to H5Eset_auto2
        H5AutoCallback^ noFunction;
        herr_t status = H5Eset_auto2(errorStackId, noFunction, 0);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5E.suppressPrinting:\n"
                "  failed to suppress error message printing: "
                "  for stack {0} with status {1}", errorStackId, status);
            throw gcnew H5EsuppressPrintingException(message, status);
        }

        // Overwrite the handle to the previous delegate so that it can be 
        // garbage collected.
        keepCallbackAlive_ = noFunction;
    }

    void H5E::setAuto(hid_t errorStackId,
        H5AutoCallback^ autoCallback,
        IntPtr clientData)
    {
        herr_t status = H5Eset_auto2(
            errorStackId,
            autoCallback,
            clientData.ToPointer());

        if (status < 0)
        {
            String^ message = String::Format(
                "H5E.setAuto:\n"
                "  failed to set error message printing: "
                "  for stack {0} with status {1}", errorStackId, status);
            throw gcnew H5EsetAutoException(message, status);
        }

        // Keep a handle to the delegate so that it won't be garbage collected.
        keepCallbackAlive_ = autoCallback;

        return;
    }

    void H5E::suppressPrinting()
    {
        suppressPrinting(H5E_DEFAULT);
    }
}
