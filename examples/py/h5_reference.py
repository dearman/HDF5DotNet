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

# This program illustrates how references to objects can be used.
# Program creates a dataset and a group in a file. It also creates
# second dataset, and references to the first dataset and the group
# are stored in it.
# Program reopens the file and reads dataset with the references.
# References are used to open the objects. Information about the
# objects is displayed.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, IntPtr

#===============================================================================

H5T_NATIVE_FLOAT = H5T.H5Type.NATIVE_FLOAT
H5T_STD_REF_OBJ = H5T.H5Type.STD_REF_OBJ

#===============================================================================

def writeGroupAndDatasets(h5file):

    grp = H5G.create(h5file, 'A')

    dtype = H5T.copy(H5T_NATIVE_FLOAT)
    shape = Array[Int64]((2,6))
    dspacev = H5S.create_simple(shape.Length, shape)
    dsetv = H5D.create(h5file, 'B', dtype, dspacev)
    H5T.close(dtype)

    dtype = H5T.copy(H5T_STD_REF_OBJ)
    shape = Array[Int64]((2,))
    dspacer = H5S.create_simple(shape.Length, shape)
    dsetr = H5D.create(h5file, 'R', dtype, dspacer)

    oref = Array.CreateInstance(ObjectReference, 2)
    oref[0] = H5R.createObjectReference(h5file, 'A')
    oref[1] = H5R.createObjectReference(h5file, 'B')

    nBytes = ObjectReference.SizeInBytes
    data = Array.CreateInstance(Byte, oref.Length*nBytes)
    for i in range(oref.Length):
        Array.Copy(oref[i].ToByteArray(), 0, data, i*nBytes, nBytes)

    H5D.write(dsetr, dtype, H5Array[Byte](data))

    H5T.close(dtype)
    H5D.close(dsetv)
    H5S.close(dspacev)
    H5D.close(dsetr)
    H5S.close(dspacer)

    return None

#===============================================================================

def readAndDereference(h5file):

    dsetr = H5D.open(h5file, 'R')
    dtyper = H5T.copy(H5T_STD_REF_OBJ)
    dspacer = H5D.getSpace(dsetr)
    npoints = H5S.getSimpleExtentNPoints(dspacer)
    nBytes = ObjectReference.SizeInBytes

    datar = Array.CreateInstance(Byte, npoints*nBytes)
    H5D.read(dsetr, dtyper, H5Array[Byte](datar))

    oref = Array.CreateInstance(ObjectReference, npoints)
    a = Array.CreateInstance(Byte, nBytes)
    for i in range(oref.Length):
        Array.Copy(datar, i*nBytes, a, 0, nBytes)
        oref[i] = ObjectReference(a)

    otype = H5R.getObjectType(h5file, oref[0])
    if (otype == H5O.ObjectType.GROUP):
        print 'First dereferenced object is a group.'

    otype = H5R.getObjectType(h5file, oref[1])
    if (otype == H5O.ObjectType.DATASET):
        print 'Second dereferenced object is a dataset.'

    dset = H5R.dereference(dsetr, H5R.ReferenceType.OBJECT, oref[1])
    dtype = H5D.getType(dset)
    dtype1 = H5T.copy(H5T_NATIVE_FLOAT)
    if (H5T.equal(dtype, dtype1)):
        print 'Datatype of the dataset is H5T_NATIVE_FLOAT.'

    H5T.close(dtype)
    H5T.close(dtype1)
    H5D.close(dset)

    H5S.close(dspacer)
    H5T.close(dtyper)
    H5D.close(dsetr)

    return None

#===============================================================================

#    print H5R.getName(dsetr, H5R.ReferenceType.DATASET_REGION, rr[0])

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('refere.h5', H5F.CreateMode.ACC_TRUNC)

writeGroupAndDatasets(h5file)

H5F.close(h5file)

h5file = H5F.open('refere.h5', H5F.OpenMode.ACC_RDONLY)

readAndDereference(h5file)

H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
