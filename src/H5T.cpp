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

#include "H5DataSetId.h"
#include "H5DataTypeId.h"
#include "H5FileOrGroupId.h"
#include "H5FloatingBitFields.h"
#include "H5LocId.h"
#include "H5T.h"
#include "H5PropertyListId.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

#pragma unmanaged
extern "C" void free(void* ptr);

void H5UnmanagedFree(char* ptr)
{
   free(ptr);
}
#pragma managed

namespace HDF5DotNet
{
    hid_t H5T::getStdType(H5T::H5Type stdType)
    {
        // Set the data type
        hid_t typeFlag = -1;
        switch(stdType)
        {
            // I8BE
        case H5Type::STD_I8BE:
            typeFlag = H5T_STD_I8BE_g;
            break;

            // I8LE
        case H5Type::STD_I8LE:
            typeFlag = H5T_STD_I8LE_g;
            break;

            // I16BE
        case H5Type::STD_I16BE:
            typeFlag = H5T_STD_I16BE_g;
            break;

            // I16LE
        case H5Type::STD_I16LE:
            typeFlag = H5T_STD_I16LE_g;
            break;

            // I32BE
        case H5Type::STD_I32BE:
            typeFlag = H5T_STD_I32BE_g;
            break;

            // I32LE
        case H5Type::STD_I32LE:
            typeFlag = H5T_STD_I32LE_g;
            break;

            // I64BE
        case H5Type::STD_I64BE:
            typeFlag = H5T_STD_I64BE_g;
            break;

            // I64LE
        case H5Type::STD_I64LE:
            typeFlag = H5T_STD_I64LE_g;
            break;

            // U8BE
        case H5Type::STD_U8BE:
            typeFlag = H5T_STD_U8BE_g;
            break;

            // U8LE
        case H5Type::STD_U8LE:
            typeFlag = H5T_STD_U8LE_g;
            break;

            // U16BE
        case H5Type::STD_U16BE:
            typeFlag = H5T_STD_U16BE_g;
            break;

            // U16LE
        case H5Type::STD_U16LE:
            typeFlag = H5T_STD_U16LE_g;
            break;

            // U32BE
        case H5Type::STD_U32BE:
            typeFlag = H5T_STD_U32BE_g;
            break;

            // U32LE
        case H5Type::STD_U32LE:
            typeFlag = H5T_STD_U32LE_g;
            break;

            // U64BE
        case H5Type::STD_U64BE:
            typeFlag = H5T_STD_U64BE_g;
            break;

            // U64LE
        case H5Type::STD_U64LE:
            typeFlag = H5T_STD_U64LE_g;
            break;

            // B8BE
        case H5Type::STD_B8BE:
            typeFlag = H5T_STD_B8BE_g;
            break;

            // B8LE
        case H5Type::STD_B8LE:
            typeFlag = H5T_STD_B8LE_g;
            break;

            // B16BE
        case H5Type::STD_B16BE:
            typeFlag = H5T_STD_B16BE_g;
            break;

            // B16LE
        case H5Type::STD_B16LE:
            typeFlag = H5T_STD_B16LE_g;
            break;

            // B32BE
        case H5Type::STD_B32BE:
            typeFlag = H5T_STD_B32BE_g;
            break;

            // B32LE
        case H5Type::STD_B32LE:
            typeFlag = H5T_STD_B32LE_g;
            break;

            // B64BE
        case H5Type::STD_B64BE:
            typeFlag = H5T_STD_B64BE_g;
            break;

            // B64LE
        case H5Type::STD_B64LE:
            typeFlag = H5T_STD_B64LE_g;
            break;

            // REF_OBJ
        case H5Type::STD_REF_OBJ:
            typeFlag = H5T_STD_REF_OBJ_g;
            break;

            // REF_DSETREG
        case H5Type::STD_REF_DSETREG:
            typeFlag = H5T_STD_REF_DSETREG_g;
            break;

        case H5Type::NATIVE_SCHAR:
            typeFlag = H5T_NATIVE_SCHAR_g;
            break;

        case H5Type::NATIVE_UCHAR:
            typeFlag = H5T_NATIVE_UCHAR_g;
            break;

        case H5Type::NATIVE_SHORT:
            typeFlag = H5T_NATIVE_SHORT_g;
            break;

        case H5Type::NATIVE_USHORT:
            typeFlag = H5T_NATIVE_USHORT_g;
            break;

        case H5Type::NATIVE_INT:
            typeFlag = H5T_NATIVE_INT_g;
            break;

        case H5Type::NATIVE_UINT:
            typeFlag = H5T_NATIVE_UINT_g;
            break;

        case H5Type::NATIVE_LONG:
            typeFlag = H5T_NATIVE_LONG_g;
            break;

        case H5Type::NATIVE_ULONG:
            typeFlag = H5T_NATIVE_ULONG_g;
            break;

        case H5Type::NATIVE_LLONG:
            typeFlag = H5T_NATIVE_LLONG_g;
            break;

        case H5Type::NATIVE_ULLONG:
            typeFlag = H5T_NATIVE_ULLONG_g;
            break;

        case H5Type::NATIVE_FLOAT:
            typeFlag = H5T_NATIVE_FLOAT_g;
            break;

        case H5Type::NATIVE_DOUBLE:
            typeFlag = H5T_NATIVE_DOUBLE_g;
            break;

        case H5Type::NATIVE_LDOUBLE:
            typeFlag = H5T_NATIVE_LDOUBLE_g;
            break;

        case H5Type::NATIVE_B8:
            typeFlag = H5T_NATIVE_B8_g;
            break;

        case H5Type::NATIVE_B16:
            typeFlag = H5T_NATIVE_B16_g;
            break;

        case H5Type::NATIVE_B32:
            typeFlag = H5T_NATIVE_B32_g;
            break;

        case H5Type::NATIVE_B64:
            typeFlag = H5T_NATIVE_B64_g;
            break;

        case H5Type::NATIVE_OPAQUE:
            typeFlag = H5T_NATIVE_OPAQUE_g;
            break;

        case H5Type::NATIVE_HADDR:
            typeFlag = H5T_NATIVE_HADDR_g;
            break;

        case H5Type::NATIVE_HSIZE:
            typeFlag = H5T_NATIVE_HSIZE_g;
            break;

        case H5Type::NATIVE_HSSIZE:
            typeFlag = H5T_NATIVE_HSSIZE_g;
            break;

        case H5Type::NATIVE_HERR:
            typeFlag = H5T_NATIVE_HERR_g;
            break;

        case H5Type::NATIVE_HBOOL:
            typeFlag = H5T_NATIVE_HBOOL_g;
            break;

        case H5Type::IEEE_F32LE:
            typeFlag = H5T_IEEE_F32LE_g;
            break;

        case H5Type::IEEE_F32BE:
            typeFlag = H5T_IEEE_F32BE_g;
            break;

        case H5Type::IEEE_F64LE:
            typeFlag = H5T_IEEE_F64LE_g;
            break;

        case H5Type::IEEE_F64BE:
            typeFlag = H5T_IEEE_F64BE_g;
            break;

        case H5Type::C_S1:
            typeFlag = H5T_C_S1_g;
            break;

        default:
            // All members of the enumeration class should have their own case.
            throw gcnew HDFException("H5T::getStdType : unknown type", -1);
        }
        return typeFlag;
    }

    H5DataTypeId^ H5T::copy(H5T::H5Type stdType)
    {
        herr_t status = H5Tcopy(H5T::getStdType(stdType));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.copy: \n"
                "  Failed to copy {0} with status {1}\n",
                stdType, status);
            throw gcnew H5TcopyException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::open(H5FileOrGroupId^ fileOrGroupId,
        String^ datatypeName)
    {
        return H5T::open(fileOrGroupId, datatypeName, 
            gcnew H5PropertyListId(0));
    }


    H5DataTypeId^ H5T::open(H5FileOrGroupId^ fileOrGroupId,
        String^ datatypeName,
        H5PropertyListId^ accessPropertyList)
    {
        herr_t status = H5Topen2(fileOrGroupId->Id,
            datatypeName,
            accessPropertyList->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.open: \n"
                "  Failed to open {0} in {1:x} with status {2}\n",
                datatypeName, fileOrGroupId->Id, status);
            throw gcnew H5TopenException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::copy(H5DataTypeId^ typeId)
    {
        herr_t status = H5Tcopy(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.copy: \n"
                "  Failed to copy {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TcopyException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::copy(H5DataSetId^ dataSetId)
    {
        herr_t status = H5Tcopy(dataSetId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.copy: \n"
                "  Failed to copy {0:x} with status {1}\n",
                dataSetId->Id, status);
            throw gcnew H5TcopyException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    bool H5T::equal(H5DataTypeId^ typeId1, H5DataTypeId^ typeId2)
    {
        htri_t status = H5Tequal(typeId1->Id, typeId2->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.equal: \n"
                "  Failed to check equality between Ids {0:x} and {1:x} with status {2}\n",
                typeId1->Id, typeId2->Id, status);
            throw gcnew HDFException(message, status);
        }

        return (status > 0);
    }

    void H5T::setSize(H5DataTypeId^ typeId, int size)
    {
        herr_t status = H5Tset_size(typeId->Id, safe_cast<size_t>(size));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.setSize: \n"
                "  Failed to set_size of {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TsetSizeException(message, status);
        }
    }

    void H5T::setVariableSize(H5DataTypeId^ typeId)
    {
        herr_t status = H5Tset_size(typeId->Id, H5T_VARIABLE);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.setVaribleSize: \n"
                "  Failed to set variable size of {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TsetSizeException(message, status);
        }
    }

    int H5T::getOffset(H5DataTypeId^ typeId)
    {
        herr_t status = H5Tget_offset(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getOffset: \n"
                "  Failed to get offset:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, status);

            throw gcnew H5TgetOffsetException(message, status);
        }

        return status;
    }

    array<hssize_t>^ H5T::get_array_dims(H5DataTypeId^ typeId)
    {
        array<hssize_t>^ result = nullptr;
        int rank = H5Tget_array_ndims(typeId->Id);

        if (rank > 0)
        {
            array<hsize_t>^ dims = gcnew array<hsize_t>(rank);
            pin_ptr<hsize_t> ptr = &dims[0];
            int status = H5Tget_array_dims2(typeId->Id, ptr);
            if (status < 0)
            {
                String^ message = String::Format(
                    "H5T.get_array_dims: \n"
                    "  Failed to get dims:\n"
                    "     type ID: {0:x}" 
                    "     with status {1}",
                    typeId->Id, status);

                throw gcnew H5TgetOffsetException(message, status);
            }

            result = gcnew array<hssize_t>(rank);
            for (int i = 0; i < rank; ++i) {
                result[i] = safe_cast<hssize_t>(dims[i]);
            }
        }
        else
        {
            String^ message = String::Format(
                "H5Tget_array_ndims: \n"
                "  Failed to get rank:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, rank);

            throw gcnew H5TgetOffsetException(message, rank);
        }

        return result;
    }


    int H5T::get_array_ndims(H5DataTypeId^ typeId)
    {
        return H5Tget_array_ndims(typeId->Id);
    }

    H5T::CharSet H5T::get_cset(H5DataTypeId^ typeId)
    {
        H5T_cset_t status = H5Tget_cset(typeId->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.cset: \n"
                "  Failed to get character set:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew HDFException(message, safe_cast<int>(status));
        }
        return safe_cast<CharSet>(status);
    }


    H5T::BitPadding H5T::get_lsb_pad(H5DataTypeId^ typeId)
    {
        H5T_pad_t lsb, msb;
        size_t status = H5Tget_pad(typeId->Id, &lsb, &msb);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.get_lsb_pad: \n"
                "  Failed to get bit padding:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew HDFException(message, safe_cast<int>(status));
        }

        return safe_cast<BitPadding>(lsb);
    }

    H5T::BitPadding H5T::get_msb_pad(H5DataTypeId^ typeId)
    {
        H5T_pad_t lsb, msb;
        size_t status = H5Tget_pad(typeId->Id, &lsb, &msb);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.get_msb_pad: \n"
                "  Failed to get bit padding:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew HDFException(message, safe_cast<int>(status));
        }

        return safe_cast<BitPadding>(msb);
    }

    H5T::Order H5T::get_order(H5DataTypeId^ typeId)
    {
        H5T_order_t status = H5Tget_order(typeId->Id);

        if (status != H5T_ORDER_LE && status != H5T_ORDER_BE)
        {
            String^ message = String::Format(
                "H5T.get_order: \n"
                "  Failed to get order:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew HDFException(message, safe_cast<int>(status));
        }

        return (safe_cast<Order>(status));
    }

    int H5T::getPrecision(H5DataTypeId^ typeId)
    {
        size_t status = H5Tget_precision(typeId->Id);

        if (status == 0)
        {
            String^ message = String::Format(
                "H5T.getPrecision: \n"
                "  Failed to get precision:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew H5TgetPrecisionException(message, safe_cast<int>(status));
        }

        return (safe_cast<int>(status));
    }

    H5FloatingBitFields^ H5T::getFields(H5DataTypeId^ typeId)
    {

        size_t spos;
        size_t epos;
        size_t esize;
        size_t mpos;
        size_t msize;

        herr_t status = H5Tget_fields(typeId->Id,
            &spos,
            &epos,
            &esize,
            &mpos,
            &msize);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getFields: \n"
                "  Failed to get fields:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, status);

            throw gcnew H5TgetFieldsException(message, status);
        }

        return gcnew H5FloatingBitFields(safe_cast<int>(spos),
            safe_cast<int>(epos),
            safe_cast<int>(esize),
            safe_cast<int>(mpos),
            safe_cast<int>(msize));
    }

    H5T::Norm H5T::getNorm(H5DataTypeId^ typeId)
    {
        H5T_norm_t status = H5Tget_norm(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getNorm: \n"
                "  Failed to get norm:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew H5TgetNormException(message, status);
        }

        return safe_cast<H5T::Norm>(status);
    }

    int H5T::getMemberOffset(H5DataTypeId^ typeId, 
        int memberNumber)
    {
        return safe_cast<int>(H5Tget_member_offset(typeId->Id, safe_cast<unsigned int>(memberNumber)));
    }

    bool H5T::isVariableString(H5DataTypeId^ typeId)
    {
        htri_t status = H5Tis_variable_str(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.isVariableString: \n"
                "  Failed to get information for id {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TisVariableStringException(message, status);
        }

        return (status != 0);
    }

    void H5T::close(H5DataTypeId^ typeId)
    {
        herr_t status = H5Tclose(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.close: \n"
                "  Failed to close type {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TcloseException(message, status);
        }
    }

    H5T::Sign H5T::getSign(H5DataTypeId^ typeId)
    {
        H5T_sign_t status = H5Tget_sign(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getSign: \n"
                "  Failed to get sign of {0:x} with status {1}\n",
                typeId->Id, safe_cast<int>(status));
            throw gcnew H5TgetSignException(message, status);
        }

        return H5T::Sign(status);
    }

    H5T::Sign H5T::getSign(H5T::H5Type h5Type)
    {
        H5T_sign_t status = H5Tget_sign(getStdType(h5Type));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getSign: \n"
                "  Failed to get sign of {0} with status {1}\n",
                h5Type, safe_cast<int>(status));
            throw gcnew H5TgetSignException(message, safe_cast<int>(status));
        }

        return H5T::Sign(status);
    }


    void H5T::setOrder(H5DataTypeId^ typeId, 
        Order order)
    {
        herr_t status = H5Tset_order(typeId->Id, 
            safe_cast<H5T_order_t>(order));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.setOrder: \n"
                "  Failed to set order of typeId {0:x} to {1} with status {2}\n",
                typeId->Id, order, status);
            throw gcnew H5TsetOrderException(message, status);
        }
    }

    int H5T::getSize(H5DataTypeId^ typeId)
    {
        size_t status = H5Tget_size(typeId->Id);

        // TODO fix this silly test
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getSize: \n"
                "  Failed to get size of typeId {0:x} with status {1}\n",
                typeId->Id, status);
            throw gcnew H5TgetSizeException(message, safe_cast<int>(status));
        }

        return safe_cast<int>(status);
    }

    int H5T::getSize(H5T::H5Type h5Type)
    {
        size_t status = H5Tget_size(getStdType(h5Type));

        // TODO fix this silly test
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getSize: \n"
                "  Failed to get size of type {0} with status {1}\n",
                h5Type, status);
            throw gcnew H5TgetSizeException(message, safe_cast<int>(status));
        }

        return safe_cast<int>(status);
    }

    H5DataTypeId^ H5T::create(H5T::CreateClass createClass,
        int size)
    {
        hid_t status = -1;
        if (createClass != H5T::CreateClass::STRING) {
            status = H5Tcreate(safe_cast<H5T_class_t>(createClass), safe_cast<size_t>(size));
        }
        else {
            if (size < 0) {
                status = H5Tcreate(safe_cast<H5T_class_t>(createClass), H5T_VARIABLE);
            }
            else {
                status = H5Tcreate(safe_cast<H5T_class_t>(createClass), safe_cast<size_t>(size));
            }
        }

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.create: \n"
                "  Failed to create type of {0} with {1} bytes - status {2}\n",
                createClass, size, status);
            throw gcnew H5TcreateException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::create_array(H5DataTypeId^ baseTypeId,
         array<hssize_t>^ dims)
    {
        H5DataTypeId^ result = nullptr;

        if (dims->Rank == 0 || dims->Length > H5S_MAX_RANK)
        {
            String^ message = String::Format(
                "H5T.create_array: \n"
                "  Array rank must be positive and less than {0}\n", H5S_MAX_RANK);
            throw gcnew HDFException(message, -1);
        }

        array<hsize_t>^ dimsCopy = gcnew array<hsize_t>(dims->Length);
        for (int i = 0; i < dims->Length; ++i)
            dimsCopy[i] = safe_cast<hsize_t>(dims[i]);

        pin_ptr<hsize_t> pinnedDimsPtr(&dimsCopy[0]);
        unsigned int rank = safe_cast<unsigned>(dims->Length);

        hid_t status = H5Tarray_create2(baseTypeId->Id, rank, pinnedDimsPtr);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.create_array: \n"
                "  Failed to create array type - status {0}\n",
                status);
            throw gcnew H5TcreateException(message, status);
        }

        result = gcnew H5DataTypeId(status);

        return result;
    }


    H5DataTypeId^ H5T::enumCreate(H5T::H5Type h5Type)
    {
        herr_t status = H5Tenum_create(getStdType(h5Type));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.enumCreate: \n"
                "  Failed to create type with {0} as parent - status {2}\n",
                h5Type, status);
            throw gcnew H5TenumCreateException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }


    H5DataTypeId^ H5T::enumCreate(H5DataTypeId^ parentId)
    {
        herr_t status = H5Tenum_create(parentId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.enumCreate: \n"
                "  Failed to create type with {0:x} as parent - status {2}\n",
                parentId->Id, status);
            throw gcnew H5TenumCreateException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    void H5T::insert(H5DataTypeId^ compoundDataType,
        String^ fieldName, 
        int offset,
        H5T::H5Type h5Type)
    {
        H5T::insert(compoundDataType,
            fieldName,
            offset,
            gcnew H5DataTypeId(getStdType(h5Type)));
    }

    void H5T::insert(H5DataTypeId^ compoundDataType,
        String^ fieldName, 
        int offset,
        H5DataTypeId^ fieldId)
    {
        herr_t status = H5Tinsert(compoundDataType->Id,
            fieldName,
            safe_cast<size_t>(offset),
            fieldId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.insert: \n"
                "  Failed to insert field name {0} into compound datatype with "
                " id {1:x}, offset of {2}, and fieldId of {3:x} - status is {4}\n",
                fieldName, compoundDataType->Id, offset, fieldId->Id, status);
            throw gcnew H5TinsertException(message, status);
        }
    }

    H5DataTypeId^ H5T::getNativeType(H5DataTypeId^ typeId,
        H5T::Direction direction)
    {
        hid_t status = H5Tget_native_type(typeId->Id,
            safe_cast<H5T_direction_t>(direction));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getNativeType: \n"
                "  Failed to get native type for type id {0:x} with "
                " direction {1} - status is {2}\n",
                typeId->Id, direction, status);
            throw gcnew H5TgetNativeTypeException(message, status);
        }

        return gcnew H5DataTypeId(status);

    }

    H5DataTypeId^ H5T::getNativeType(H5T::H5Type h5Type,
        H5T::Direction direction)
    {
        hid_t status = H5Tget_native_type(H5T::getStdType(h5Type),
            safe_cast<H5T_direction_t>(direction));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getNativeType: \n"
                "  Failed to get native type {0} with "
                " direction {1} - status is {2}\n",
                h5Type, direction, status);
            throw gcnew H5TgetNativeTypeException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::get_super(H5DataTypeId^ typeId)
    {
        hid_t status = H5Tget_super(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.get_super: \n"
                "  Failed to get base type for type id {0:x} "
                " - status is {1}\n",
                typeId->Id, status);
            throw gcnew HDFException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::vlenCreate(H5T::H5Type h5Type)
    {
        herr_t status = H5Tvlen_create(getStdType(h5Type));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.vlenCreate: \n"
                "  Failed to create type of {0} with status {1}",
                h5Type, status);
            throw gcnew H5TvlenCreateException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }

    H5DataTypeId^ H5T::vlenCreate(H5DataTypeId^ baseId)
    {
        herr_t status = H5Tvlen_create(baseId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.vlenCreate: \n"
                "  Failed to create type for type id {0:x} with status {1}",
                baseId->Id, status);
            throw gcnew H5TvlenCreateException(message, status);
        }

        return gcnew H5DataTypeId(status);
    }


    H5T::H5TClass H5T::getClass(H5DataTypeId^ typeId)
    {
        herr_t status = H5Tget_class(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getClass: \n"
                "  Failed to get class for type id {0:x} with status {1}",
                typeId->Id, status);
            throw gcnew H5TgetClassException(message, status);
        }
        return H5T::H5TClass(status);
    }

    H5T::H5TClass H5T::getClass(H5T::H5Type h5Type)
    {
        herr_t status = H5Tget_class(getStdType(h5Type));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getClass: \n"
                "  Failed to get class for type {0} with status {1}",
                h5Type, status);
            throw gcnew H5TgetClassException(message, status);
        }
        return H5T::H5TClass(status);
    }


    int H5T::getMemberIndex(H5DataTypeId^ typeId,
        String^ fieldName)
    {
        int status = H5Tget_member_index(typeId->Id, fieldName);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getMemberIndex: \n"
                "  Failed to get index for fieldName {0},  type id {1:x} with "
                "status {2}",
                fieldName, typeId->Id, status);
            throw gcnew H5TgetMemberIndexException(message, status);
        }
        return status;
    }

    H5DataTypeId^ H5T::getMemberType(H5DataTypeId^ typeId,
        int fieldIndex)
    {
        int status = H5Tget_member_type(typeId->Id, safe_cast<unsigned int>(fieldIndex));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getMemberType: \n"
                "  Failed to get type for fieldIndex {0},  type id {1:x} with "
                "status {2}",
                fieldIndex, typeId->Id, status);
            throw gcnew H5TgetMemberTypeException(message, status);
        }
        return gcnew H5DataTypeId(status);
    }

    String^ H5T::getMemberName(H5DataTypeId^ typeId,
        int fieldIndex)
    {
        char* name = H5Tget_member_name(typeId->Id, safe_cast<unsigned int>(fieldIndex));

        if (name == 0)
        {
            String^ message = String::Format(
                "H5T.getMemberName: \n"
                "  Failed to get name for fieldIndex {0},  type id {1:x} ",
                fieldIndex, typeId->Id);
            throw gcnew H5TgetMemberNameException(message, 0);
        }

        String^ memberName = gcnew String(name);
        //H5UnmanagedFree(name);

        return memberName;
    }


    int H5T::getNMembers(H5DataTypeId^ typeId)
    {
        int status = H5Tget_nmembers(typeId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getNMembers: \n"
                "  Failed to get class for type id {0:x} with status {1}",
                typeId->Id, status);
            throw gcnew H5TgetNMembersException(message, status);
        }
        return status;
    }

    H5T::H5TClass H5T::getMemberClass(H5DataTypeId^ typeId, 
        int memberNumber)
    {
        int status = H5Tget_member_class(typeId->Id, safe_cast<unsigned int>(memberNumber));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getMemberClass: \n"
                "  Failed to get class for member number {0} of type id {1:x} "
                "with status {2}",
                memberNumber, typeId->Id, status);
            throw gcnew H5TgetMemberClassException(message, status);
        }
        return H5T::H5TClass(status);
    }

    generic <class Type>
    void H5T::getMemberValue(H5DataTypeId^ typeId,
        int memberNumber,
        Type% value)
    {
        pin_ptr<Type> ptr = &value;
        herr_t status = H5Tget_member_value(typeId->Id,
            safe_cast<unsigned int>(memberNumber),
            ptr);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.getMemberValue: \n"
                "  Failed to get member value for :\n"
                "     TypeId: {0:x}\n"
                "     member number: {1}\n"
                "     with status: {2}\n", 
                typeId->Id, memberNumber, status);

            throw gcnew H5TgetMemberValueException(message, status);
        }
    }


    generic <class Type>
    void H5T::enumInsert(H5DataTypeId^ typeId,
        String^ name,
        Type% value)
    {
        pin_ptr<Type> ptr = &value;
        herr_t status = H5Tenum_insert(typeId->Id,
            name,
            ptr);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.enumInsert: \n"
                "  Failed to insert:\n"
                "     type ID: {0:x}\n"
                "     name: {1}\n"
                "     status: {2}\n", 
                typeId->Id, name, status);

            throw gcnew H5TenumInsertException(message, status);
        }
    }

    generic <class Type>
    void H5T::enumValueOf(H5DataTypeId^ typeId,
        String^ enumName,
        Type% value)
    {
        pin_ptr<Type> ptr = &value;

        herr_t status = H5Tenum_valueof(typeId->Id, 
            enumName,
            ptr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.enumValueOf: \n",
                "  Failed to get value for: \n"
                "  typeId: {0:x}\n"
                "  enumName: {1}\n",
                typeId->Id,
                enumName);

            throw gcnew H5TenumValueOfException(message, status);
        }
    }


    // HACK: this is ugly (MAX_ENUM_NAME_LENGTH), but I can't see a better way of doing it
    generic <class Type>
    String^ H5T::enumNameOf(H5DataTypeId^ typeId,
        Type% value)
    {
        pin_ptr<Type> ptr = &value;
        size_t MAX_ENUM_NAME_LENGTH = 64*1024;
        StringBuilder^ enumName = gcnew StringBuilder(safe_cast<int>(MAX_ENUM_NAME_LENGTH));

        herr_t status = H5Tenum_nameof(typeId->Id, 
            ptr, 
            enumName, 
            MAX_ENUM_NAME_LENGTH);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.enumNameOf: \n"
                "  Failed to get name for:\n"
                "     typeId ID: {0:x}\n"
                "     value: {1}\n"
                "     with status: {2}\n", 
                typeId->Id, value, status);

            throw gcnew H5TenumNameOfException(message, status);
        }

        return enumName->ToString();
    }


    void H5T::commit(H5LocId^ location, 
        String^ dataTypeName,
        H5DataTypeId^ typeId,
        H5PropertyListId^ linkCreationPropertyList,
        H5PropertyListId^ dataTypeCreationPropertyList,
        H5PropertyListId^ dataTypeAccessPropertyList)
    {
        herr_t status = H5Tcommit2(location->Id,
            dataTypeName,
            typeId->Id,
            linkCreationPropertyList->Id,
            dataTypeCreationPropertyList->Id,
            dataTypeAccessPropertyList->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.commit: \n"
                "  Failed to commit:\n"
                "     location ID: {0:x}\n"
                "     dataTypeName: {1}"
                "     type ID: {3:x}" 
                "     with status {4}",
                location->Id, dataTypeName, typeId->Id, status );

            throw gcnew H5TcommitException(message, status);
        }
    }

    void H5T::commit(H5LocId^ location, 
        String^ dataTypeName,
        H5DataTypeId^ typeId)
    {

        // Call the overloaded commit with default property lists.
        commit(location, 
            dataTypeName, 
            typeId, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT), 
            gcnew H5PropertyListId(H5P::Template::DEFAULT), 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    bool H5T::committed(H5DataTypeId^ typeId)
    {
        htri_t status = H5Tcommitted(typeId->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.committed: \n"
                "  Failed:\n"
                "     type ID: {0:x}" 
                "     with status {1}",
                typeId->Id, status );

            throw gcnew HDFException(message, status);
        }

        return (status > 0);
    }

    H5T::StringPadding H5T::get_strpad(H5DataTypeId^ typeId)
    {
        H5T_str_t status = H5Tget_strpad(typeId->Id);
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.get_strpad: \n"
                "  Failed to get string padding:\n"
                "     type Id: {0:x}\n"
                "     with status {1}",
                typeId->Id, safe_cast<int>(status));

            throw gcnew HDFException(message, status);
        }
        return safe_cast<StringPadding>(status);
    }

    void H5T::setStrPad
        (
        H5DataTypeId^ typeId,
        StringPadding pad
        )
    {
        herr_t status = H5Tset_strpad(typeId->Id, safe_cast<H5T_str_t>(pad));
        if (status < 0)
        {
            String^ message = String::Format(
                "H5T.setStrPad: \n"
                "  Failed to set string padding:\n"
                "     type Id: {0:x}\n"
                "     padding: {1}"
                "     with status {2}",
                typeId->Id, pad, status );

            throw gcnew HDFException(message, status);
        }
    }

    String^ H5T::get_tag(H5DataTypeId^ typeId)
    {
        String^ result = nullptr;

        if (H5T::getClass(typeId) != H5T::H5TClass::OPAQUE)
        {
            throw gcnew HDFException("H5T::get_tag: This is not an opaque datatype.", -4711);
        }

        try
        {
            char* buf = H5Tget_tag(typeId->Id);
            result = Marshal::PtrToStringAnsi(IntPtr((void*) buf));
        }
        catch (Exception^ ex)
        {
            throw gcnew HDFException(ex->Source + " : " + ex->Message, -4711);
        }

        return result;
    }

}



