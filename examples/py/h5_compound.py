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

# This example shows how to create a compound data type,
# write an array which has the compound data type to the file,
# and read back fields' subsets.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, BitConverter, Byte, Double, Single, Int32, Int64

#===============================================================================

H5T_NATIVE_DOUBLE = H5T.H5Type.NATIVE_DOUBLE
H5T_NATIVE_FLOAT = H5T.H5Type.NATIVE_FLOAT
H5T_NATIVE_INT = H5T.H5Type.NATIVE_INT

#===============================================================================

def createDatasetWithCompoundType(h5file):

    # component name -> (offset, size, type)

    ht = { 'a_name': (0, 4, H5T_NATIVE_INT),
           'b_name': (4, 4, H5T_NATIVE_FLOAT),
           'c_name': (8, 8, H5T_NATIVE_DOUBLE) }

    sizeof = 0
    for k in ht.keys():
        sizeof  += ht[k][1]

    dtype = H5T.create(H5T.CreateClass.COMPOUND, sizeof)
    for k in ht.keys():
        H5T.insert(dtype, k, ht[k][0], ht[k][2])

    npoints = 10
    shape = Array[Int64]((npoints,))
    dspace = H5S.create_simple(shape.Length, shape)

    dset = H5D.create(h5file, 'ArrayOfStructures', dtype, dspace)

    # create an array of Byte
    # use BitConverter to get Byte representations

    shape = Array[Int64]((npoints*sizeof,))
    byteArray = Array.CreateInstance(Byte, shape)

    for i in range(npoints):

        offset = i*sizeof

        a = Int32(i)
        Array.Copy(BitConverter.GetBytes(a), 0, byteArray,
                   offset+ht['a_name'][0], ht['a_name'][1])
        b = Single(i*i)
        Array.Copy(BitConverter.GetBytes(b), 0, byteArray,
                   offset+ht['b_name'][0], ht['b_name'][1])
        c = Double(1.0/(i+1.0))
        Array.Copy(BitConverter.GetBytes(c), 0, byteArray,
                   offset+ht['c_name'][0], ht['c_name'][1])

    H5D.write(dset, dtype, H5Array[Byte](byteArray))

    H5S.close(dspace)
    H5T.close(dtype)

    return dset

#===============================================================================

def read2FromDatasetWithCompoundType(dset):

    ht = { 'c_name': (0, 8, H5T_NATIVE_DOUBLE),
           'a_name': (8, 4, H5T_NATIVE_INT) }

    sizeof = 0
    for k in ht.keys():
        sizeof  += ht[k][1]

    dtype = H5T.create(H5T.CreateClass.COMPOUND, sizeof)
    for k in ht.keys():
        H5T.insert(dtype, k, ht[k][0], ht[k][2])

    dspace = H5D.getSpace(dset)
    npoints = H5S.getSimpleExtentNPoints(dspace)
    
    shape = Array[Int64]((npoints*sizeof,))
    byteArray = Array.CreateInstance(Byte, shape)

    H5D.read(dset, dtype, H5Array[Byte](byteArray))

    print '\nField\tc\ta'
    for i in range(npoints):
        offset = i*sizeof
        c = BitConverter.ToDouble(byteArray, offset+ht['c_name'][0])
        a = BitConverter.ToInt32(byteArray, offset + ht['a_name'][0])
        print '\t%.4f\t%d' % (c, a)
    print ''

    H5S.close(dspace)
    H5T.close(dtype)

    return dset

#===============================================================================

def read1FromDatasetWithCompoundType(dset):

    ht = { 'b_name': (0, 4, H5T_NATIVE_FLOAT) }

    sizeof = 0
    for k in ht.keys():
        sizeof  += ht[k][1]

    dtype = H5T.create(H5T.CreateClass.COMPOUND, sizeof)
    for k in ht.keys():
        H5T.insert(dtype, k, ht[k][0], ht[k][2])

    dspace = H5D.getSpace(dset)
    npoints = H5S.getSimpleExtentNPoints(dspace)
    
    shape = Array[Int64]((npoints*sizeof,))
    byteArray = Array.CreateInstance(Byte, shape)

    H5D.read(dset, dtype, H5Array[Byte](byteArray))

    print '\nField\tb'
    for i in range(npoints):
        offset = i*sizeof
        b = BitConverter.ToSingle(byteArray, offset+ht['b_name'][0])
        print '\t%.4f' % (b)
    print ''

    H5S.close(dspace)
    H5T.close(dtype)

    return dset

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

h5file = H5F.create('SDScompound.h5', H5F.CreateMode.ACC_TRUNC)

dset = createDatasetWithCompoundType(h5file)

read2FromDatasetWithCompoundType(dset)
read1FromDatasetWithCompoundType(dset)

H5D.close(dset)

H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()

