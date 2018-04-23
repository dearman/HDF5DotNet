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

# This example reads hyperslab from the SDS.h5 file
# created by h5_write.py program into two-dimensional
# plane of the three-dimensional array.
# Information about dataset in the SDS.h5 file is obtained.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Int32, Int64

print 'Initializing HDF5 library'
status = H5.Open()

h5file = H5F.open('SDS.h5', H5F.OpenMode.ACC_RDONLY)

dset = H5D.open(h5file, 'IntArray')

dtype = H5D.getType(dset)
tclass = H5T.getClass(dtype)
if tclass == H5T.H5TClass.INTEGER: print 'Data set has INTEGER type'
# TODO: Warp H5Tget_order!
#order = H5T.getOrder(dtype)
#if order == H5T.Order.LE: print 'Little endian order'

size = H5T.getSize(dtype)
print 'Data size is %d' % size

dspace = H5D.getSpace(dset)
rank = H5S.getSimpleExtentNDims(dspace)
dims = H5S.getSimpleExtentDims(dspace)

print 'rank %d, dimensions %ld x %ld' % (rank, dims[0], dims[1])

offset = Array[Int64]((1, 2))
count = Array[Int64]((3, 4))
H5S.selectHyperslab(dspace, H5S.SelectOperator.SET, offset, count)

dimsm = Array[Int64]((7, 7, 3))
memspace = H5S.create_simple(dimsm.Length, dimsm)

offset = Array[Int64]((3, 0, 0))
count = Array[Int64]((3, 4, 1))
H5S.selectHyperslab(memspace, H5S.SelectOperator.SET, offset, count)

shape = Array[Int64]((7, 7, 3))
data = Array.CreateInstance(Int32, shape)

dtype = H5T.copy(H5T.H5Type.NATIVE_INT)

P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

H5D.read(dset, dtype, memspace, dspace, P_DEFAULT, H5Array[Int32](data))

for row in range(shape[0]):
    for col in range(shape[1]):
        print '%d ' % data[row,col,0],
    print ''

# 0 0 0 0 0 0 0
# 0 0 0 0 0 0 0
# 0 0 0 0 0 0 0
# 3 4 5 6 0 0 0
# 4 5 6 7 0 0 0
# 5 6 7 8 0 0 0
# 0 0 0 0 0 0 0

H5T.close(dtype)
H5S.close(memspace)
H5S.close(dspace)
H5D.close(dset)

H5F.close(h5file)

print 'Shutting down HDF5 library'
status = H5.Close()
