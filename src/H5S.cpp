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

#include "H5DataSpaceId.h"
#include "H5S.h"
#include "HDFExceptionSubclasses.h"
#include "IntPtrAux.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{
    H5DataSpaceId^ H5S::create_simple(int rank, 
        array<hssize_t>^ dims,
        array<hssize_t>^ maxDims)
    {
        array<hsize_t>^ dimsCopy = gcnew array<hsize_t>(rank);
        array<hsize_t>^ maxDimsCopy = gcnew array<hsize_t>(rank);

        for (int i = 0; i < rank; ++i)
        {
            dimsCopy[i] = safe_cast<hsize_t>(dims[i]);
            maxDimsCopy[i] = safe_cast<hsize_t>(maxDims[i]);
        }

        hid_t status = H5Screate_simple(rank, dimsCopy, maxDimsCopy);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.create_simple: \n"
                "  Failed to create data space with status = {0}\n"
                "    rank = {1}\n"
                "    dims = {2}\n"
                "    maxDims = {3}\n",
                status, rank, dims, maxDims);
            throw gcnew H5ScreateSimpleException(message, status);
        }

        return gcnew H5DataSpaceId(status);
    }

    H5DataSpaceId^ H5S::create_simple(int rank, 
        array<hssize_t>^ dims)
    {
        array<hsize_t>^ dimsCopy = gcnew array<hsize_t>(rank);
        for (int i = 0; i < rank; ++i)
            dimsCopy[i] = safe_cast<hsize_t>(dims[i]);

        hid_t status = H5Screate_simple(rank, dimsCopy, dimsCopy);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.create_simple: \n"
                "  Failed to create data space with status = {0}\n"
                "    rank = {1}\n"
                "    dims = {2}\n",
                status, rank, dims);
            throw gcnew H5ScreateSimpleException(message, status);
        }

        return gcnew H5DataSpaceId(status);
    }

    void H5S::close(H5DataSpaceId^ id)	
    {
        herr_t status = H5Sclose(id->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.close: \n"
                "  Failed to close data space {0:x} with status {1}\n",
                id->Id, status);

            throw gcnew H5ScloseException(message, status);
        }
    }

    H5DataSpaceId^ H5S::create(H5SClass createClass)
    {
        hid_t status = H5Screate(safe_cast<H5S_class_t>(createClass));

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.create: \n"
                "  Failed to create data space of class {0} with status {1}\n",
                createClass, status);

            throw gcnew H5ScreateException(message, status);
        }

        return gcnew H5DataSpaceId(status);
    }

    void H5S::selectStridedHyperslab(H5DataSpaceId^ spaceId,
        H5S::SelectOperator selectOperator,
        array<hssize_t>^ start,
        array<hssize_t>^ stride,
        array<hssize_t>^ count,
        array<hssize_t>^ block)
    {
        array<hsize_t>^ startCopy = gcnew array<hsize_t>(start->Length);
        array<hsize_t>^ strideCopy = gcnew array<hsize_t>(stride->Length);
        array<hsize_t>^ countCopy = gcnew array<hsize_t>(count->Length);
        array<hsize_t>^ blockCopy = gcnew array<hsize_t>(block->Length);

        for (int i = 0; i < start->Length; ++i)
            startCopy[i] = safe_cast<hsize_t>(start[i]);
        for (int i = 0; i < stride->Length; ++i)
            strideCopy[i] = safe_cast<hsize_t>(stride[i]);
        for (int i = 0; i < count->Length; ++i)
            countCopy[i] = safe_cast<hsize_t>(count[i]);
        for (int i = 0; i < block->Length; ++i)
            blockCopy[i] = safe_cast<hsize_t>(block[i]);

        // Create a pinned pointer so that garbage collection/compaction 
        //will not move the stride array
        pin_ptr<hsize_t> pinnedStridePtr(&strideCopy[0]);

        // Get a hsize_t pointer to the pinned array.
        hsize_t* stridePtr = pinnedStridePtr;

        // Create a pinned pointer so that garbage collection/compaction 
        //will not move the block array
        pin_ptr<hsize_t> pinnedBlockPtr(&blockCopy[0]);

        // Get a hsize_t pointer to the pinned array.
        hsize_t* blockPtr = pinnedBlockPtr;

        hid_t status = H5Sselect_hyperslab(
            spaceId->Id,
            safe_cast<H5S_seloper_t>(selectOperator),
            startCopy,
            stridePtr,
            countCopy,
            blockPtr);


        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.selectStridedHyperslab: \n"
                "  Failed to select hyperslabe with: \n"
                "  id = {0:x} \n"
                "  selectOperator = {1}\n"
                "  start = {2}\n"
                "  stride = {3}\n"
                "  count = {4}\n"
                "  block = {5}\n"
                "  status = {6}\n",
                spaceId->Id, selectOperator, startCopy, strideCopy, countCopy, blockCopy, status);

            throw gcnew H5SselectStridedHyperslabException(message, status);
        }
    }


    void H5S::selectStridedHyperslab(H5DataSpaceId^ spaceId,
        H5S::SelectOperator selectOperator,
        array<hssize_t>^ start,
        array<hssize_t>^ stride,
        array<hssize_t>^ count)
    {
        array<hsize_t>^ startCopy = gcnew array<hsize_t>(start->Length);
        array<hsize_t>^ strideCopy = gcnew array<hsize_t>(stride->Length);
        array<hsize_t>^ countCopy = gcnew array<hsize_t>(count->Length);

        for (int i = 0; i < start->Length; ++i)
            startCopy[i] = safe_cast<hsize_t>(start[i]);
        for (int i = 0; i < stride->Length; ++i)
            strideCopy[i] = safe_cast<hsize_t>(stride[i]);
        for (int i = 0; i < count->Length; ++i)
            countCopy[i] = safe_cast<hsize_t>(count[i]);

        // Create a pinned pointer so that garbage collection/compaction 
        //will not move the stride array
        pin_ptr<hsize_t> pinnedStridePtr(&strideCopy[0]);

        // Get a hsize_t pointer to the pinned array.
        hsize_t* stridePtr = pinnedStridePtr;

        hid_t status = H5Sselect_hyperslab(
            spaceId->Id,
            safe_cast<H5S_seloper_t>(selectOperator),
            startCopy,
            stridePtr,
            countCopy,
            0);


        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.selectStridedHyperslab: \n"
                "  Failed to select hyperslabe with: \n"
                "  id = {0:x} \n"
                "  selectOperator = {1}\n"
                "  start = {2}\n"
                "  stride = {3}\n"
                "  count = {4}\n"
                "  status = {5}\n",
                spaceId->Id, selectOperator, startCopy, strideCopy, countCopy, status);

            throw gcnew H5SselectStridedHyperslabException(message, status);
        }
    }


    void H5S::selectHyperslab(H5DataSpaceId^ spaceId,
        H5S::SelectOperator selectOperator,
        array<hssize_t>^ start,
        array<hssize_t>^ count,
        array<hssize_t>^ block)
    {
        array<hsize_t>^ startCopy = gcnew array<hsize_t>(start->Length);
        array<hsize_t>^ countCopy = gcnew array<hsize_t>(count->Length);
        array<hsize_t>^ blockCopy = gcnew array<hsize_t>(block->Length);

        for (int i = 0; i < start->Length; ++i)
            startCopy[i] = safe_cast<hsize_t>(start[i]);
        for (int i = 0; i < count->Length; ++i)
            countCopy[i] = safe_cast<hsize_t>(count[i]);
        for (int i = 0; i < block->Length; ++i)
            blockCopy[i] = safe_cast<hsize_t>(block[i]);

        // Create a pinned pointer so that garbage collection/compaction 
        //will not move the block array
        pin_ptr<hsize_t> pinnedBlockPtr(&blockCopy[0]);

        // Get a hsize_t pointer to the pinned array.
        hsize_t* blockPtr = pinnedBlockPtr;

        hid_t status = H5Sselect_hyperslab(
            spaceId->Id,
            safe_cast<H5S_seloper_t>(selectOperator),
            startCopy,
            0,
            countCopy,
            blockPtr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.selectHyperslab: \n"
                "  Failed to select hyperslabe with: \n"
                "  id = {0:x} \n"
                "  selectOperator = {1}\n"
                "  start = {2}\n"
                "  count = {3}\n"
                "  block = {4}\n"
                "  status = {5}\n",
                spaceId->Id, selectOperator, startCopy, countCopy, blockCopy, status);

            throw gcnew H5SselectHyperslabException(message, status);
        }
    }



    void H5S::selectHyperslab(H5DataSpaceId^ spaceId,
        H5S::SelectOperator selectOperator,
        array<hssize_t>^ start,
        array<hssize_t>^ count)
    {
        array<hsize_t>^ startCopy = gcnew array<hsize_t>(start->Length);
        array<hsize_t>^ countCopy = gcnew array<hsize_t>(count->Length);

        for (int i = 0; i < start->Length; ++i)
            startCopy[i] = safe_cast<hsize_t>(start[i]);
        for (int i = 0; i < count->Length; ++i)
            countCopy[i] = safe_cast<hsize_t>(count[i]);

        hid_t status = H5Sselect_hyperslab(
            spaceId->Id,
            safe_cast<H5S_seloper_t>(selectOperator),
            startCopy,
            0,
            countCopy,
            0);


        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.selectStridedHyperslab: \n"
                "  Failed to select hyperslabe with: \n"
                "  id = {0:x} \n"
                "  selectOperator = {1}\n"
                "  start = {2}\n"
                "  count = {3}\n"
                "  status = {4}\n",
                spaceId->Id, selectOperator, start, count, status);

            throw gcnew H5SselectStridedHyperslabException(message, status);
        }
    }

    int H5S::getSimpleExtentNDims(H5DataSpaceId^ spaceId)
    {
        hid_t status = H5Sget_simple_extent_ndims(spaceId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.getSimpleExtentNDims: \n"
                "  Failed to get number of dimentsions\n"
                "    dataspace id = {0:x}\n"
                "    status = {1}\n",
                spaceId->Id, status);
            throw gcnew H5SgetSimpleExtentNDimsException(message, status);
        }
        return status;
    }

    int H5S::getSimpleExtentNPoints(H5DataSpaceId^ spaceId)
    {
        hid_t status = H5Sget_simple_extent_npoints(spaceId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.getSimpleExtentNPoints: \n"
                "  Failed to get number of dimentsions\n"
                "    dataspace id = {0:x}\n"
                "    status = {1}\n",
                spaceId->Id, status);
            throw gcnew H5SgetSimpleExtentNPointsException(message, status);
        }
        return status;
    }

    H5S::H5SClass H5S::get_simple_extent_type(H5DataSpaceId^ spaceId)
    {
        return safe_cast<H5S::H5SClass>(H5Sget_simple_extent_type(spaceId->Id));
    }

    bool H5S::selectNone(H5DataSpaceId^ spaceId)
    {
        hid_t status = H5Sselect_none(spaceId->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S.selectNone: \n"
                "  Failed with\n"
                "    dataspace id = {0:x}\n"
                "    status = {1}\n",
                spaceId->Id, status);
            throw gcnew H5SselectNoneException(message, status);
        }
        return (status != 0);
    }


    array<hssize_t>^ H5S::getSimpleExtentMaxDims(H5DataSpaceId^ spaceId)
    {
        array<hsize_t>^ extent = gcnew array<hsize_t>(H5S_MAX_RANK);
        array<hsize_t>^ maxExtent = gcnew array<hsize_t>(H5S_MAX_RANK);

        // Find the extents
        hid_t nDimensions = H5Sget_simple_extent_dims(
            spaceId->Id,
            extent,
            maxExtent);

        // If nDimensions is not valid
        if ((nDimensions < 0) || (nDimensions > H5S_MAX_RANK))
        {
            String^ message = String::Format(
                "H5S.getSimpleExtentMaxDims: \n"
                "  Failed to get max extent with status {0}\n",
                nDimensions);

            throw gcnew H5SgetSimpleExtentMaxDimsException(message, nDimensions);
        }


        // Copy the extents to the return array
        array<hssize_t>^ returnExtent = gcnew array<hssize_t>(nDimensions);

        for(int i=0;i<nDimensions;i++)
        {
            returnExtent[i] = safe_cast<hssize_t>(maxExtent[i]);
        }

        return returnExtent;
    }

    array<hssize_t>^ H5S::getSimpleExtentDims(H5DataSpaceId^ spaceId)
    {
        array<hsize_t>^ extent = gcnew array<hsize_t>(H5S_MAX_RANK);
        array<hsize_t>^ maxExtent = gcnew array<hsize_t>(H5S_MAX_RANK);

        // Find the extents
        hid_t nDimensions = H5Sget_simple_extent_dims(
            spaceId->Id,
            extent,
            maxExtent);

        // If nDimensions is not valid
        if ((nDimensions < 0) || (nDimensions > H5S_MAX_RANK))
        {
            String^ message = String::Format(
                "H5S.getSimpleExtentDims: \n"
                "  Failed to get extent with status {0}\n",
                nDimensions);

            throw gcnew H5SgetSimpleExtentDimsException(message, nDimensions);
        }

        // Copy the extents to the return array
        array<hssize_t>^ returnExtent = gcnew array<hssize_t>(nDimensions);

        for(int i=0;i<nDimensions;i++)
        {
            returnExtent[i] = safe_cast<hssize_t>(extent[i]);
        }

        return returnExtent;
    }

    void H5S::selectElements
        (
        H5DataSpaceId^   spaceId,
        SelectOperator   selectOperator,
        IntPtr           numElements,
        array<hssize_t>^ coord
        )
    {
        array<hsize_t>^ coordCopy = gcnew array<hsize_t>(coord->Length);

        for (int i = 0; i < coord->Length; ++i)
            coordCopy[i] = safe_cast<hsize_t>(coord[i]);
        
        pin_ptr<hsize_t> ptr = &coordCopy[0];

        herr_t status = H5Sselect_elements(spaceId->Id,
            safe_cast<H5S_seloper_t>(selectOperator), IntPtrAux::ToSize_t(numElements),
            ptr);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5S::selectElements: \n"
                "  Failed to select elements with: \n"
                "  id = {0:x} \n"
                "  selectOperator = {1}\n"
                "  numElements = {2}\n"
                "  status = {5}\n",
                spaceId->Id, selectOperator, numElements, status);

            throw gcnew HDFException(message, status);
        }
    }
}
