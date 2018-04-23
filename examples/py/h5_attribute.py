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

#  This program illustrates the usage of the H5A Interface functions.
#  It creates and writes a dataset, and then creates and writes array,
#  scalar, and string attributes of the dataset.
#  Program reopens the file, attaches to the scalar attribute using
#  attribute name and reads and displays its value. Then index of the
#  third attribute is used to read and display attribute values.
#  The H5Aiterate function is used to iterate through the dataset attributes,
#  and display their names. The function is also reads and displays the values
#  of the array attribute.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, Single

#===============================================================================

H5T_C_S1 = H5T.H5Type.C_S1
H5T_NATIVE_FLOAT = H5T.H5Type.NATIVE_FLOAT
H5T_NATIVE_INT = H5T.H5Type.NATIVE_INT

#===============================================================================

def addDataset():

    shape = Array[Int64]((7,))
    vector = Array[Int32]((1, 2, 3, 4, 5, 6, 7))

    dspace = H5S.create_simple(shape.Length, shape)
    dtype = H5T.copy(H5T_NATIVE_INT)
    dset = H5D.create(h5file, 'Dataset', dtype, dspace);

    H5D.write(dset, dtype, H5Array[Int32](vector))

    H5T.close(dtype)
    H5S.close(dspace)

    return dset

#===============================================================================

def addSimpleFloatAttribute(dset):

    shape = Array[Int64]((2, 3))
    matrix = Array.CreateInstance(Single, shape)

    for row in range(matrix.GetLength(0)):
        for col in range(matrix.GetLength(1)):
            matrix[row,col] = -1;

    dspace = H5S.create_simple(shape.Length, shape)
    dtype = H5T.copy(H5T_NATIVE_FLOAT)
    attr = H5A.create(dset, 'Float attribute', dtype, dspace);

    H5A.write(attr, dtype, H5Array[Single](matrix))

    H5A.close(attr)
    H5T.close(dtype)
    H5S.close(dspace)
    return None

#===============================================================================

def addScalarIntegerAttribute(dset, name, value):

    point = Array[Int32]((0,))
    point[0] = value

    dspace = H5S.create(H5S.H5SClass.SCALAR)
    dtype = H5T.copy(H5T_NATIVE_INT)
    attr = H5A.create(dset, name, dtype, dspace);

    H5A.write(attr, dtype, H5Array[Int32](point))

    H5A.close(attr)
    H5T.close(dtype)
    H5S.close(dspace)
    return None

#===============================================================================

def addScalarFixedStringAttribute(dset, name, string):

    dspace = H5S.create(H5S.H5SClass.SCALAR)
    dtype = H5T.copy(H5T_C_S1)
    H5T.setSize(dtype, len(string)+1)
    H5T.setStrPad(dtype, H5T.StringPadding.NULLTERM)
    attr = H5A.create(dset, name, dtype, dspace)

    enc = System.Text.ASCIIEncoding()
    H5A.write(attr, dtype, H5Array[Byte](enc.GetBytes(string)))

    H5A.close(attr)
    H5T.close(dtype)
    H5S.close(dspace)
    return None

#===============================================================================

def readScalarIntegerAttribute(dset, name):

    attr = H5A.open(dset, name)
    dtype = H5A.getType(attr)
    buffer = Array.CreateInstance(Int32, 1)
    H5A.read(attr, dtype, H5Array[Int32](buffer))
    fmt = 'The value of the attribute "%s" is %d'
    print fmt % (name, buffer[0])

    H5T.close(dtype)
    H5A.close(attr)
    return None

#===============================================================================

def findScalarFixedStringAttribute(dset):

    info = H5O.getInfo(dset)
    for i in range(info.nAttributes):
        attr = H5A.openByIndex(dset, '.', H5IndexType.CRT_ORDER,
                               H5IterationOrder.INCREASING, Int64(i)) 
        dtype = H5A.getType(attr)
        tclass = H5T.getClass(dtype)

        # ignore variable length strings
        if tclass == H5T.H5TClass.STRING and not H5T.isVariableString(dtype):

            mtype = H5T.getNativeType(dtype, H5T.Direction.ASCEND)
            buffer = Array.CreateInstance(Byte, H5T.getSize(mtype))
            H5A.read(attr, mtype, H5Array[Byte](buffer))

            enc = System.Text.ASCIIEncoding()
            fmt = 'Found string attribute; its index is %d , value = %s'
            print fmt % (i, enc.GetString(buffer))

            H5T.close(mtype)

        H5T.close(dtype)
        H5A.close(attr)

    return None

#===============================================================================

def callback(attr, name, info, obj):

    print 'Name : ' + name

    dtype = H5A.getType(attr)
    dspace = H5A.getSpace(attr)
    rank = H5S.getSimpleExtentNDims(dspace)
    dims = H5S.getSimpleExtentDims(dspace)

    if rank > 0:

        print 'Rank : %d' % rank
        print 'Dimension sizes : ',
        for i in range(rank):
            print '%d' % dims[i],
        print '\n'

    if H5T.getClass(dtype) == H5T.H5TClass.FLOAT and H5T.getSize(dtype) == 4:

        print 'Type : FLOAT'
        npoints = H5S.getSimpleExtentNPoints(dspace)
        buffer = Array.CreateInstance(Single, npoints)
        H5A.read(attr, dtype, H5Array[Single](buffer))

        print 'Values : ',
        for i in range(npoints):
            print '%f ' % buffer[i],
        print '\n'

    return H5IterationResult.SUCCESS 


def iterateAttributes(dset):

    H5A.iterate(dset, H5IndexType.NAME, H5IterationOrder.INCREASING, 0, callback, 0)

    return None

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('Attributes.h5', H5F.CreateMode.ACC_TRUNC)
dset = addDataset()

addSimpleFloatAttribute(dset)
addScalarIntegerAttribute(dset, 'Integer attribute', 1)
addScalarFixedStringAttribute(dset, 'Character atttribute', 'ABCD')

H5D.close(dset)
H5F.close(h5file)

h5file = H5F.open('Attributes.h5', H5F.OpenMode.ACC_RDONLY)

dset = H5D.open(h5file, 'Dataset')

readScalarIntegerAttribute(dset, 'Integer attribute')
findScalarFixedStringAttribute(dset)
iterateAttributes(dset)

H5D.close(dset)
H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()
