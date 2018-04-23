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

# This example shows how to read data from a chunked dataset.
# We will read from the file created by h5_extend_write.c

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, Single

#===============================================================================

H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

H5T_NATIVE_INT = H5T.H5Type.NATIVE_INT

#===============================================================================

def readDataSet(dset):

    dspace = H5D.getSpace(dset)
    dims = H5S.getSimpleExtentDims(dspace)
    print 'dataset rank %d, dimensions %d x %d' % (dims.Length, dims[0], dims[1])

    mspace = H5S.create_simple(dims.Length, dims)
    dtype = H5T.copy(H5T_NATIVE_INT)
    data = Array.CreateInstance(Int32, dims)

    H5D.read(dset, dtype, mspace, dspace, H5P_DEFAULT, H5Array[Int32](data))

    print 'Dataset: '
    for row in range(data.GetLength(0)):
        for col in range(data.GetLength(1)):
            print '%d ' % (data[row,col]),
        print ''
    print ''
 
# dataset rank 2, dimensions 10 x 5
# chunk rank 2, dimensions 2 x 5
#
#    Dataset:
#    1 1 1 3 3
#    1 1 1 3 3
#    1 1 1 0 0
#    2 0 0 0 0
#    2 0 0 0 0
#    2 0 0 0 0
#    2 0 0 0 0
#    2 0 0 0 0
#    2 0 0 0 0
#    2 0 0 0 0

    H5T.close(dtype)
    H5S.close(mspace)
    H5S.close(dspace)

    return None

#===============================================================================

def read3rdColumn(dset):

    dtype = H5T.copy(H5T_NATIVE_INT)
 
    cdims = Array[Int64]((10,))
    mspace = H5S.create_simple(cdims.Length, cdims)

    fspace = H5D.getSpace(dset)
    offset = Array[Int64]((0, 2))
    count = Array[Int64]((10, 1))
    H5S.selectHyperslab(fspace, H5S.SelectOperator.SET, offset, count)

    data = Array.CreateInstance(Int32, cdims)

    H5D.read(dset, dtype, mspace, fspace, H5P_DEFAULT, H5Array[Int32](data))

    print 'Third column: '
    for i in range(10):
        print '%d ' % (data[i])
    print ''

#  Third column:
#  1
#  1
#  1
#  0
#  0
#  0
#  0
#  0
#  0
#  0

    H5S.close(mspace)
    H5T.close(dtype)
    H5S.close(fspace)

    return None

#===============================================================================

def readChunk(dset):

    fspace = H5D.getSpace(dset)

    cplist = H5D.getCreatePropertyList(dset)

    if H5P.getLayout(cplist) == H5D.Layout.CHUNKED:
    
        cdims = H5P.getChunk(cplist, 2)
        print 'chunk rank 2, dimensions %d x %d' % (cdims[0], cdims[1])

        dtype = H5T.copy(H5T_NATIVE_INT)

        mspace = H5S.create_simple(cdims.Length, cdims)
        offset = Array[Int64]((2, 0))
        count = Array[Int64]((cdims[0], cdims[1]))
        H5S.selectHyperslab(fspace, H5S.SelectOperator.SET, offset, count)

        data = Array.CreateInstance(Int32, cdims)

        H5D.read(dset, dtype, mspace, fspace, H5P_DEFAULT, H5Array[Int32](data))

        print 'Chunk: '
        for row in range(data.GetLength(0)):
            for col in range(data.GetLength(1)):
                print '%d ' % (data[row,col]),
            print ''
        print ''

#  Chunk:
#  1 1 1 0 0
#  2 0 0 0 0

        H5S.close(mspace)
        H5T.close(dtype)

    H5S.close(fspace)

    return None

#===============================================================================

print '\nInitializing HDF5 library\n'

status = H5.Open()

h5file = H5F.open('SDSextendible.h5', H5F.OpenMode.ACC_RDONLY)

dset = H5D.open(h5file, 'ExtendibleArray')

readDataSet(dset)

read3rdColumn(dset)

readChunk(dset)

H5D.close(dset)
H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()
