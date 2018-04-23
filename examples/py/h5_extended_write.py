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

# This example shows how to work with extendible dataset.
# In the current version of the library dataset MUST be
# chunked.


import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Int32, Int64


#===============================================================================

def addExtendibleDataset(h5file, name):

    shape = Array[Int64]((3, 3))
    unlimited = Int64(H5S.H5SType.UNLIMITED)
    shapeMax = Array[Int64]((unlimited, unlimited))

    dspace = H5S.create_simple(shape.Length, shape, shapeMax)
    dtype = H5T.copy(H5T.H5Type.NATIVE_INT)

    propList = H5P.create(H5P.PropertyListClass.DATASET_CREATE)
    H5P.setChunk(propList, Array[Int64]((2, 5)))
    fillValue = 0
    H5P.setFillValue[Int32](propList, dtype, fillValue)

    H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

    dset = H5D.create(h5file, name, dtype, dspace, H5P_DEFAULT, propList, H5P_DEFAULT)

    H5P.close(propList)
    H5T.close(dtype)
    H5S.close(dspace)

    return dset

#===============================================================================

def extendAndWriteData(h5file, dset, shape, offset, count, data):

    status = H5D.setExtent(dset, shape)

    fspace = H5D.getSpace(dset)
    H5S.selectHyperslab(fspace, H5S.SelectOperator.SET, offset, count)

    dspace = H5S.create_simple(count.Length, count)
 
    dtype = H5D.getType(dset)

    H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)
    H5D.write(dset, dtype, dspace, fspace, H5P_DEFAULT, H5Array[Int32](data))

    return None

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

h5file = H5F.create('SDSextendible.h5', H5F.CreateMode.ACC_TRUNC)

dset = addExtendibleDataset(h5file, 'ExtendibleArray')

shape = Array[Int64]((3, 3))
offset = Array[Int64]((0, 0))
count = Array[Int64]((3, 3))

data = Array.CreateInstance(Int32, Array[Int32]((3, 3)))
for row in range(data.GetLength(0)):
    for col in range(data.GetLength(1)):
        data[row, col] = 1

extendAndWriteData(h5file, dset, shape, offset, count, data)

# extend dataset to 10x3
shape[0] = 10
shape[1] = 3
offset[0] = 3
offset[1] = 0
count[0] = 7
count[1] = 1

data = Array[Int32]((2, 2, 2, 2, 2, 2, 2))

extendAndWriteData(h5file, dset, shape, offset, count, data)

# extend dataset to 10x5
shape[0] = 10
shape[1] = 5
offset[0] = 0
offset[1] = 3
count[0] = 2
count[1] = 2

data = Array.CreateInstance(Int32, Array[Int32]((2, 2)))
for row in range(data.GetLength(0)):
    for col in range(data.GetLength(1)):
        data[row, col] = 3

extendAndWriteData(h5file, dset, shape, offset, count, data)

# Resulting dataset
#
#   1 1 1 3 3
#   1 1 1 3 3
#   1 1 1 0 0
#   2 0 0 0 0
#   2 0 0 0 0
#   2 0 0 0 0
#   2 0 0 0 0
#   2 0 0 0 0
#   2 0 0 0 0
#   2 0 0 0 0


H5D.close(dset)

H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()
