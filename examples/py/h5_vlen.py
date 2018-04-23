# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# Copyright by The HDF Group.                                               *
# Copyright by the Board of Trustees of the University of Illinois.         *
# All rights reserved.                                                      *
#                                                                           *
# This file is part of HDF5.  The full HDF5 copyright notice, including     *
# terms governing use, modification, and redistribution, is contained in    *
# the files COPYING and Copyright.html.  COPYING can be found at the root   *
# of the source code distribution tree; Copyright.html can be found at the  *
# root level of an installed copy of the electronic HDF5 document set and   *
# is linked from the top-level documents page.  It can also be found at     *
# http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
# access to either file, you may request a copy from help@hdfgroup.org.     *
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

# This program illustrates the creation and use of a variable-length type.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, IntPtr
import System.Runtime.InteropServices
from System.Runtime.InteropServices import Marshal

#===============================================================================

def writeVlenData(h5file):

    dtype = H5T.vlenCreate(H5T.H5Type.NATIVE_INT)

    array = range(16) 
    npoints = len(array)
    shape = Array[Int64]((npoints,))
    dspace = H5S.create_simple(shape.Length, shape)

    dset = H5D.create(h5file, 'Vlen Dataset', dtype, dspace)

    wdata = Array.CreateInstance(hvl_t, npoints)

    sizeofInt = 4

    for i in range(npoints):

        nElems = array[i] + 1
        nBytes = nElems*sizeofInt

        # the data to be written (array of length i+1 with all elements = i)
        data = Array.CreateInstance(Byte, nBytes)
        for j in range(nElems):
            Array.Copy(System.BitConverter.GetBytes(i), 0, data,
                       j*sizeofInt, sizeofInt) 

        # allocate and copy to array in unmanaged memory 
        mem = Marshal.AllocHGlobal(nBytes)
        Marshal.Copy(data, 0, mem, nBytes)
        wdata[i] = VLen(IntPtr(nElems), mem).To_hvl_t()

    H5D.write(dset, dtype, H5Array[hvl_t](wdata))

    # free unmanaged buffer space 
    for i in range(npoints):
        vl = VLen(wdata[i])
        Marshal.FreeHGlobal(vl.Pointer)

    H5D.close(dset)
    H5S.close(dspace)
    H5T.close(dtype)
    return None

#===============================================================================

def readVlenData(h5file):

    dset = H5D.open(h5file, 'Vlen Dataset')
    dspace = H5D.getSpace(dset)
    npoints = H5S.getSimpleExtentNPoints(dspace)
    dtype = H5D.getType(dset)

    xfer = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    acb = H5AllocCallback(allocCallback)
    fcb = H5FreeCallback(freeCallback)

    H5P.setVlenMemManager(xfer, acb, IntPtr.Zero, fcb, IntPtr.Zero)

    sel = H5DataSpaceId(H5S.H5SType.ALL)
    rdata = Array.CreateInstance(hvl_t, npoints)

    H5D.read(dset, dtype, sel, sel, xfer, H5Array[hvl_t](rdata)) 

    sizeofInt = 4

# Expected output:
#
# 0
# 1 1
# 2 2 2
# 3 3 3 3
# 4 4 4 4 4
# 5 5 5 5 5 5
# 6 6 6 6 6 6 6
# 7 7 7 7 7 7 7 7
# 8 8 8 8 8 8 8 8 8
# 9 9 9 9 9 9 9 9 9 9
# 10 10 10 10 10 10 10 10 10 10 10
# 11 11 11 11 11 11 11 11 11 11 11 11
# 12 12 12 12 12 12 12 12 12 12 12 12 12
# 13 13 13 13 13 13 13 13 13 13 13 13 13 13
# 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14
# 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15

    # compute the maximum length and create a managed buffer
    nBytes = 0

    for i in range(npoints):

        vl = VLen(rdata[i])
        nElems = vl.Length.ToInt64()
        nBytes = max(nBytes, nElems * sizeofInt)

    raw = Array.CreateInstance(Byte, nBytes)

    # copy from unmanged memory into managed buffer and read values
    for i in range(npoints):

        vl = VLen(rdata[i])
        nElems = vl.Length.ToInt64()
        nBytes = nElems * sizeofInt
        Marshal.Copy(vl.Pointer, raw, 0, nBytes)

        for j in range(nElems):
            print System.BitConverter.ToInt32(raw, sizeofInt*j),
        print ''

    H5D.vlenReclaim(dtype, dspace, xfer, H5Array[hvl_t](rdata))

    H5P.close(xfer)
    H5D.close(dset)
    H5S.close(dspace)
    H5T.close(dtype)
    return None

#===============================================================================

def allocCallback(size, info):
    return Marshal.AllocHGlobal(size.ToInt32())

#===============================================================================

def freeCallback(memory, info):
    Marshal.FreeHGlobal(memory)
    return None

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('vlen.h5', H5F.CreateMode.ACC_TRUNC)

writeVlenData(h5file)

H5F.close(h5file)

h5file = H5F.open('vlen.h5', H5F.OpenMode.ACC_RDONLY)

readVlenData(h5file)

H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
