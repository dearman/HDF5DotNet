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

#include "H5Tpublic.h"

namespace HDF5DotNet
{
    /// <summary>
    ///  An instance of this class is returned from H5T.getFields().  It
    ///  contains floating point bit field information including the 
    ///  positions of the sign bit, exponent field, mantissa field and the
    ///  number of bits in the exponent and mantissa.
    /// </summary>
    public ref class H5FloatingBitFields
    {
    public:

        /// <summary>
        /// The constructor for H5FloatingBitFields takes the values
        /// returned from a call to H5TgetFields() as parameters.
        /// </summary>
        H5FloatingBitFields(int spos,
            int epos,
            int esize,
            int mpos,
            int msize) :
        signBitPosition_(safe_cast<size_t>(spos)),
            exponentBitPosition_(safe_cast<size_t>(epos)),
            nExponentBits_(safe_cast<size_t>(esize)),
            mantissaBitPosition_(safe_cast<size_t>(mpos)),
            nMantissaBits_(safe_cast<size_t>(msize))
        {
        }

        /// <summary>
        /// Position of the sign bit.
        /// </summary>
        property int signBitPosition
        {
            int get() { return safe_cast<int>(signBitPosition_); }
        }

        /// <summary>
        /// Start bit number of the exponent.
        /// </summary>
        property int exponentBitPosition
        {
            int get() { return safe_cast<int>(exponentBitPosition_); }
        }

        /// <summary>
        ///  Number of bits in the exponent.
        /// </summary>
        property int nExponentBits
        {
            int get() { return safe_cast<int>(nExponentBits_); }
        }

        /// <summary>
        /// Start bit number of the mantissa.
        /// </summary>
        property int mantissaBitPosition
        {
            int get() { return safe_cast<int>(mantissaBitPosition_); }
        }

        /// <summary>
        ///  Number of bits in the mantissa.
        /// </summary>
        property int nMantissaBits
        {
            int get() { return safe_cast<int>(nMantissaBits_); }
        }

        /// <summary>
        /// Create a string with a readable description of the bit values.
        /// </summary>
        virtual System::String^ ToString() override
        {
            return 
                System::String::Format(
                "signBitPosition: {0}\n"
                "exponentBitPosition: {1}\n"
                "nExponentBits: {2}\n"
                "mantissaBitPosition: {3}\n"
                "nMantissaBits: {4}\n",
                signBitPosition_, 
                exponentBitPosition_,
                nExponentBits_,
                mantissaBitPosition_,
                nMantissaBits_);
        }

    private:
        /// <summary>
        /// Position of the sign bit.
        /// </summary>
        size_t signBitPosition_;

        /// <summary>
        /// Start bit number of the exponent.
        /// </summary>
        size_t exponentBitPosition_;

        /// <summary>
        ///  Number of bits in the exponent.
        /// </summary>
        size_t nExponentBits_;

        /// <summary>
        /// Start bit number of the mantissa.
        /// </summary>
        size_t mantissaBitPosition_;

        /// <summary>
        ///  Number of bits in the mantissa.
        /// </summary>
        size_t nMantissaBits_;
    };
}