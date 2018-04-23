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

# This example writes data to the HDF5 file.
# Data conversion is performed during write operation.

#===============================================================================

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

#===============================================================================

import System
from System import Array, Int32, Int64

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

shape = Array[Int64]((5, 6))
data = Array.CreateInstance(Int32, shape)

for row in range(0, shape[0]):
    for col in range(0, shape[1]):
        data[row,col] = Int32(row+col)

h5file = H5F.create('SDS.h5', H5F.CreateMode.ACC_TRUNC)

dspace = H5S.create_simple(shape.Length, shape)
dtype = H5T.copy(H5T.H5Type.NATIVE_INT)
status = H5T.setOrder(dtype, H5T.Order.LE)

dset = H5D.create(h5file, 'IntArray', dtype, dspace)

dtype = H5T.copy(H5T.H5Type.NATIVE_INT)

status = H5D.write(dset, dtype, H5Array[Int32](data))

H5D.close(dset)
H5T.close(dtype)
H5S.close(dspace)
H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()
