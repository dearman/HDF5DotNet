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

#include "H5AutoCallback.h"
#include "HDFExceptionSubclasses.h"

#include "H5Epublic.h"

namespace HDF5DotNet
{
    /// <summary>
    /// The H5E contains static member function for each of the supported
    /// H5E calls of the HDF5 library.
    /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5E.html"/>
    /// </summary>
    public ref class H5E sealed
    {
    public:

#pragma region documentation
        ///<summary>
        /// Turns automatic error printing on or off - assigns delegate to
        /// be called on error conditions.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5E.html#Error-SetAuto"/>
        ///</summary>

        ///<param name="errorStackId">
        /// IN: Error stack identifier.
        ///</param>

        ///<param name="autoCallback">
        /// IN: Callback to be called upon an error condition.
        ///</param>

        ///<param name="clientData">
        /// IN: Data passed to the error function (not a pointer to garbage 
        /// collected memory).
        ///</param>

        /// <returns>
        /// void
        /// </returns>

        /// <exception cref="H5EsetAutoException">
        /// throws H5EsetAutoException on failure.
        /// </exception>
#pragma endregion documentation

        static void setAuto(hid_t errorStackId,
            H5AutoCallback^ autoCallback,
            System::IntPtr clientData);

#pragma region documentation
        ///<summary>
        ///  Turns automatic error printing off
        ///</summary>

        ///<param name="errorStackId">
        /// IN: Error stack identifier.
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5EsuppressPrintingException">
        /// throws rH5EsuppressPrintingException on failure.
        /// </exception>
#pragma endregion documentation

        static void suppressPrinting(hid_t errorStackId);

#pragma region documentation
        ///<summary>
        ///  Turns automatic error printing off
        ///</summary>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5EsuppressPrintingException">
        /// throws rH5EsuppressPrintingException on failure.
        /// </exception>
#pragma endregion documentation

        static void suppressPrinting();

    private:
        static H5AutoCallback^ keepCallbackAlive_;

        H5E() {};

    };
}
