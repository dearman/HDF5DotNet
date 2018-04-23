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

# This program shows how the H5Sselect_hyperslab and H5Sselect_elements
# functions are used to write selected data from memory to the file.
# Program takes 48 elements from the linear buffer and writes them into
# the matrix using 3x2 blocks, (4,3) stride and (2,4) count.
# Then four elements  of the matrix are overwritten with the new values and
# file is closed. Program reopens the file and selects the union of two
# hyperslabs in the dataset in the file. Then it reads the selection into the
# memory dataset preserving the shape of the selection.

#===============================================================================

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

#===============================================================================

import System
from System import Array, Int32, Int64, IntPtr

#===============================================================================

H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

values = Array[Int32]((53, 59, 61, 67))

vector = Array.CreateInstance(Int32, 50)
for i in range(vector.Length): vector[i] = i
vector[0] = -1
vector[-1] = -1

h5file = H5F.create('Select.h5', H5F.CreateMode.ACC_TRUNC)

ftype = H5T.copy(H5T.H5Type.NATIVE_INT)

plist = H5P.create(H5P.PropertyListClass.DATASET_CREATE)
fillValue = 0
H5P.setFillValue[Int32](plist, ftype, fillValue)

fshape = Array[Int64]((8, 12))
fspace = H5S.create_simple(fshape.Length, fshape)

dset = H5D.create(h5file, 'Matrix in file', ftype, fspace,
                  H5P_DEFAULT, plist, H5P_DEFAULT)

# Select hyperslab for the dataset in the file, using 3x2 blocks,
# (4,3) stride and (2,4) count starting at the position (0,1).

start = Array[Int64]((0, 1))
stride = Array[Int64]((4, 3))
count = Array[Int64]((2, 4))
block = Array[Int64]((3, 2))

H5S.selectStridedHyperslab(fspace, H5S.SelectOperator.SET,
                           start, stride, count, block)

mshape = Array[Int64]((50,))
mspace = H5S.create_simple(mshape.Length, mshape)

# Select hyperslab.
# We will use 48 elements of the vector buffer starting at the second element.
# Selected elements are 1 2 3 . . . 48

start[0] = 1
stride[0] = 1
count[0] = 48
block[0] = 1

H5S.selectStridedHyperslab(mspace, H5S.SelectOperator.SET,
                           start, stride, count, block)

# Write selection from the vector buffer to the dataset in the file.
#
# File dataset should look like this:
#                    0  1  2  0  3  4  0  5  6  0  7  8
#                    0  9 10  0 11 12  0 13 14  0 15 16
#                    0 17 18  0 19 20  0 21 22  0 23 24
#                    0  0  0  0  0  0  0  0  0  0  0  0
#                    0 25 26  0 27 28  0 29 30  0 31 32
#                    0 33 34  0 35 36  0 37 38  0 39 40
#                    0 41 42  0 43 44  0 45 46  0 47 48
#                    0  0  0  0  0  0  0  0  0  0  0  0

H5D.write(dset, ftype, mspace, fspace, H5P_DEFAULT, H5Array[Int32](vector))

H5S.selectNone(fspace)

mshape = Array[Int64]((4,))
mspace = H5S.create_simple(mshape.Length, mshape)

coord = Array.CreateInstance(Int64, 8)

coord[0] = coord[1] = 0
coord[2] = coord[3] = coord[4] = 3
coord[5] = coord[6] = 5
coord[7] = 6

H5S.selectElements(fspace, H5S.SelectOperator.SET, IntPtr(4), coord)

values = Array[Int32]((53, 59, 61, 67))

H5D.write(dset, ftype, mspace, fspace, H5P_DEFAULT, H5Array[Int32](values))

# Write selection of points to the dataset.
#
# File dataset should look like this:
#                   53  1  2  0  3  4  0  5  6  0  7  8
#                    0  9 10  0 11 12  0 13 14  0 15 16
#                    0 17 18  0 19 20  0 21 22  0 23 24
#                    0  0  0 59  0 61  0  0  0  0  0  0
#                    0 25 26  0 27 28  0 29 30  0 31 32
#                    0 33 34  0 35 36 67 37 38  0 39 40
#                    0 41 42  0 43 44  0 45 46  0 47 48
#                    0  0  0  0  0  0  0  0  0  0  0  0

H5S.close(mspace)
H5D.close(dset)
H5S.close(fspace)

H5F.close(h5file)

h5file = H5F.open('Select.h5', H5F.OpenMode.ACC_RDONLY)

dset = H5D.open(h5file, 'Matrix in file')
fspace = H5D.getSpace(dset)

# Select first hyperslab for the dataset in the file. The following
# elements are selected:
#                     10  0 11 12
#                     18  0 19 20
#                      0 59  0 61

start = Array[Int64]((1,2))
block = Array[Int64]((1,1))
stride = Array[Int64]((1,1))
count = Array[Int64]((3,4))
H5S.selectStridedHyperslab(fspace, H5S.SelectOperator.SET,
                           start, stride, count, block)

# Add second selected hyperslab to the selection.
# The following elements are selected:
#                    19 20  0 21 22
#                     0 61  0  0  0
#                    27 28  0 29 30
#                    35 36 67 37 38
#                    43 44  0 45 46
#                     0  0  0  0  0
# Note that two hyperslabs overlap. Common elements are:
#                                              19 20
#                                               0 61

start = Array[Int64]((2,4))
block = Array[Int64]((1,1))
stride = Array[Int64]((1,1))
count = Array[Int64]((6,5))
H5S.selectStridedHyperslab(fspace, H5S.SelectOperator.OR,
                           start, stride, count, block)

mshape = Array[Int64]((8,9))
mspace = H5S.create_simple(mshape.Length, mshape)

# Select two hyperslabs in memory. Hyperslabs has the same
# size and shape as the selected hyperslabs for the file dataspace.

start = Array[Int64]((0,0))
block = Array[Int64]((1,1))
stride = Array[Int64]((1,1))
count = Array[Int64]((3,4))
H5S.selectStridedHyperslab(mspace, H5S.SelectOperator.SET,
                           start, stride, count, block)

start = Array[Int64]((1,2))
block = Array[Int64]((1,1))
stride = Array[Int64]((1,1))
count = Array[Int64]((6,5))
H5S.selectStridedHyperslab(mspace, H5S.SelectOperator.OR,
                           start, stride, count, block)

matrix = Array.CreateInstance(Int32, mshape)

H5D.read(dset, ftype, mspace, fspace, H5P_DEFAULT, H5Array[Int32](matrix))

# Display the result. Memory dataset is:
#
#                    10  0 11 12  0  0  0  0  0
#                    18  0 19 20  0 21 22  0  0
#                     0 59  0 61  0  0  0  0  0
#                     0  0 27 28  0 29 30  0  0
#                     0  0 35 36 67 37 38  0  0
#                     0  0 43 44  0 45 46  0  0
#                     0  0  0  0  0  0  0  0  0
#                     0  0  0  0  0  0  0  0  0

for row in range(matrix.GetLength(0)):
    for col in range(matrix.GetLength(1)):
        print '%3d ' % (matrix[row,col]),
    print ''

H5S.close(fspace)
H5S.close(mspace)
H5D.close(dset)

H5F.close(h5file)
H5T.close(ftype)

print '\nShutting down HDF5 library\n'
status = H5.Close()
