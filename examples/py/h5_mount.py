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

# This program shows the concept of "mounting files".
# Program creates one file with group G in it, and another
# file with dataset D. Then second file is mounted in the first one
# under the "mounting point" G. Dataset D is accessed in the first file
# under name /G/D and data is printed out.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Int32, Int64


#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('mount1.h5', H5F.CreateMode.ACC_TRUNC)
grp = H5G.create(h5file, '/G')
H5G.close(grp)
H5F.close(h5file)

h5file = H5F.create('mount2.h5', H5F.CreateMode.ACC_TRUNC)
shape = Array[Int64]((4,5))
dspace = H5S.create_simple(shape.Length, shape)
dtype = H5T.copy(H5T.H5Type.NATIVE_INT)

dset = H5D.create(h5file, 'D', dtype, dspace)

data = Array.CreateInstance(Int32, shape)
for row in range(data.GetLength(0)):
    for col in range(data.GetLength(1)):
        data[row,col] = Int32(row+col)

H5D.write(dset, dtype, H5Array[Int32](data))

H5D.close(dset)
H5T.close(dtype)
H5S.close(dspace)
H5F.close(h5file)

h5file1 = H5F.open('mount1.h5', H5F.OpenMode.ACC_RDONLY)
h5file2 = H5F.open('mount2.h5', H5F.OpenMode.ACC_RDONLY)

H5F.Mount(h5file1, '/G', h5file2)

dset = H5D.open(h5file1, '/G/D')
dtype = H5D.getType(dset)
buffer = Array.CreateInstance(Int32, shape)
H5D.read(dset, dtype, H5Array[Int32](buffer))

for row in range(buffer.GetLength(0)):
    for col in range(buffer.GetLength(1)):
        print '%d ' % (buffer[row,col]),
    print ''

H5T.close(dtype)
H5D.close(dset)

H5F.Unmount(h5file1, '/G')

H5F.close(h5file2)
H5F.close(h5file1)

print '\nShutting down HDF5 library'
status = H5.Close()
