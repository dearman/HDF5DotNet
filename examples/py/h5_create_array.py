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

# This example shows how to create and write to a dataset based
# on an HDF5 array type.

print 'Loading clr'
import clr

clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import * 

import System
from System import Array, BitConverter, Byte, Int64

import System.IO
from System.IO import BinaryWriter, MemoryStream

print 'Initializing HDF5 library'
status = H5.Open()

print 'HDF5 ', H5.Version.Major, '.', H5.Version.Minor, '.', H5.Version.Release

h5file = H5F.create('SDS.h5', H5F.CreateMode.ACC_TRUNC)

baseType = H5T.copy(H5T.H5Type.NATIVE_INT)
dims = Array[Int64]((3,3))
dtype = H5T.create_array(baseType, dims)    

shape = Array[Int64]((5, 6))
dspace = H5S.create_simple(shape.Length, shape)

dset = H5D.create(h5file, 'array', dtype, dspace)

ms = MemoryStream()
writer = BinaryWriter(ms) 

for i in range(270):
    writer.Write(i) 

data = ms.ToArray()

status = H5D.write(dset, dtype, H5Array[Byte](data))

H5D.close(dset)
H5S.close(dspace)
H5T.close(baseType)
H5T.close(dtype)
H5F.close(h5file)

print 'Shutting down HDF5 library'
status = H5.Close()
