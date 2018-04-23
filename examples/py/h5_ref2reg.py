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

# This program shows how to create, store and dereference references
# to the dataset regions.
#
# It creates a file and writes a two dimensional integer dataset
# to it. Then it creates a dataset to store region references in. It
# stores references to a hyperslab and 3 points selected (for the
# integer dataset previously created).
#
# It then reopens the references dataset, reads and dereferences the
# region references, and then reads and displays the selected hyperslab
# and selected elements data from the integer dataset.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, IntPtr

#===============================================================================

H5S_ALL = H5DataSpaceId(H5S.H5SType.ALL)
H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

#===============================================================================

def writeDatasets(h5file):

    dtype = H5T.copy(H5T.H5Type.NATIVE_INT)
    shape = Array[Int64]((2,9))
    dspacev = H5S.create_simple(shape.Length, shape)
    dsetv = H5D.create(h5file, 'MATRIX', dtype, dspacev)

    data = Array.CreateInstance(Int32, shape)
    data[0,0] = data[0,1] = data[1,0] = 1
    data[0,2] = data[1,1] = data[1,2] = 2
    data[0,3] = data[0,4] = data[1,3] = 3
    data[0,5] = data[1,4] = data[1,5] = 4
    data[0,6] = data[0,7] = data[1,6] = 5
    data[0,8] = data[1,7] = data[1,8] = 6
    H5D.write(dsetv, dtype, H5Array[Int32](data))

    H5T.close(dtype)

    dtype = H5T.copy(H5T.H5Type.STD_REF_DSETREG)
    shape = Array[Int64]((2,))
    dspacer = H5S.create_simple(shape.Length, shape)
    dsetr = H5D.create(h5file, 'REGION_REFERENCES', dtype, dspacer)

    start = Array[Int64]((0,3))
    count = Array[Int64]((2,3))
    H5S.selectHyperslab(dspacev, H5S.SelectOperator.SET, start, count)
    rr = Array.CreateInstance(RegionReference, 2)
    rr[0] = H5R.createRegionReference(h5file, 'MATRIX', dspacev)

    coord = Array.CreateInstance(Int64, 6) 
    coord[0] = coord[1] = coord[4] = 0
    coord[2] = 1
    coord[3] = 6
    coord[5] = 8

    H5S.selectNone(dspacev)
    H5S.selectElements(dspacev, H5S.SelectOperator.SET, IntPtr(3), coord)
    rr[1] = H5R.createRegionReference(h5file, 'MATRIX', dspacev)

    nBytes = RegionReference.SizeInBytes
    data = Array.CreateInstance(Byte, rr.Length*nBytes)
    for i in range(rr.Length):
        Array.Copy(rr[i].ToByteArray(), 0, data, i*nBytes, nBytes)

    H5D.write(dsetr, dtype, H5Array[Byte](data))

    H5T.close(dtype)
    H5D.close(dsetv)
    H5S.close(dspacev)
    H5D.close(dsetr)
    H5S.close(dspacer)

    return None

#===============================================================================

def readDatasets(h5file):

    dsetr = H5D.open(h5file, 'REGION_REFERENCES')
    dtyper = H5T.copy(H5T.H5Type.STD_REF_DSETREG)
    dspacer = H5D.getSpace(dsetr)
    npoints = H5S.getSimpleExtentNPoints(dspacer)

    nBytes = RegionReference.SizeInBytes
    datar = Array.CreateInstance(Byte, npoints*nBytes)
    H5D.read(dsetr, dtyper, H5Array[Byte](datar))

    rr = Array.CreateInstance(RegionReference, npoints)
    a = Array.CreateInstance(Byte, nBytes)
    for i in range(rr.Length):
        Array.Copy(datar, i*nBytes, a, 0, nBytes)
        rr[i] = RegionReference(a)

    # examine the first region reference

    dsetv = H5R.dereference(dsetr, H5R.ReferenceType.DATASET_REGION, rr[0])
    name = H5R.getName(dsetr, H5R.ReferenceType.DATASET_REGION, rr[0])
    print ' The dataset\'s name (returned by H5Rget_name) the reference points to is \'%s\', name length is %d\n' % (name, len(name))

    name = H5I.getName(dsetv)
    print ' The dataset\'s name (returned by H5Iget_name) the reference points to is \'%s\', name length is %d\n' % (name, len(name))

    dspace = H5R.getRegion(dsetr, rr[0])
    dtype = H5T.copy(H5T.H5Type.NATIVE_INT)
    shape = Array[Int64]((2,9))
    data = Array.CreateInstance(Int32, shape)

    H5D.read(dsetv, dtype, H5S_ALL, dspace, H5P_DEFAULT, H5Array[Int32](data))

    print 'Selected hyperslab: '
    for i in range(data.GetLength(0)):
        print ''
        for j in range(data.GetLength(1)):
            print '%d ' % (data[i,j]),
    print '\n'

    H5S.close(dspace)
    H5D.close(dsetv)

    # examine the second region reference

    dsetv = H5R.dereference(dsetr, H5R.ReferenceType.DATASET_REGION, rr[1])
    dspace = H5R.getRegion(dsetr, rr[1])

    H5D.read(dsetv, dtype, H5S_ALL, dspace, H5P_DEFAULT, H5Array[Int32](data))

    print 'Selected points: '
    for i in range(data.GetLength(0)):
        print ''
        for j in range(data.GetLength(1)):
            print '%d ' % (data[i,j]),
    print ''

    H5T.close(dtype)
    H5S.close(dspace)
    H5D.close(dsetv)

    H5S.close(dspacer)
    H5T.close(dtyper)
    H5D.close(dsetr)

    return None

#===============================================================================

#    print H5R.getName(dsetr, H5R.ReferenceType.DATASET_REGION, rr[0])

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('REF_REG.h5', H5F.CreateMode.ACC_TRUNC)

writeDatasets(h5file)

H5F.close(h5file)

h5file = H5F.open('REF_REG.h5', H5F.OpenMode.ACC_RDONLY)

readDatasets(h5file)

H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
