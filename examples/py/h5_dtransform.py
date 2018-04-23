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

#  This example demonstrates how the data transform features of
#  HDF5 works.
#
# (1)
#  The test first writes out data, with no data transform set.
#  Then, the test reads back this data with a data transform applied.
#
# (2)
#  Then, the test writes a new set of data, with a data transform set.
#  Then, the test reads this new set of data, without a data set.
#
# (3)
#  Lastly, the test reads the previous set of data (that was written out
#  with a data transform) with a data transform set for the read.
#
#  (4)
#  Get the transform from the property using H5Pget_data_transform.

import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Int32, Int64, Single

#===============================================================================

data = (
    (36.0, 31.0, 25.0, 19.0, 13.0, 7.0, 1.0, -5.0, -11.0, -16.0, -22.0, -28.0, -34.0, -40.0, -46.0, -52.0, -57.0, -63.0),
    (34.0, 27.0, 21.0, 15.0, 9.0, 3.0, -4.0, -10.0, -16.0, -22.0, -28.0, -35.0, -41.0, -47.0, -53.0, -59.0, -66.0, -72.0),
    (32.0, 25.0, 19.0, 13.0, 6.0, 0.0, -7.0, -13.0, -19.0, -26.0, -32.0, -39.0, -45.0, -51.0, -58.0, -64.0, -71.0, -77.0),
    (30.0, 24.0, 17.0, 11.0, 4.0, -2.0, -9.0, -15.0, -22.0, -29.0, -35.0, -42.0, -48.0, -55.0, -61.0, -68.0, -74.0, -81.0),
    (29.0, 23.0, 16.0, 9.0, 3.0, -4.0, -11.0, -17.0, -24.0, -31.0, -37.0, -44.0, -51.0, -58.0, -64.0, -71.0, -78.0, -84.0),
    (28.0, 22.0, 15.0, 8.0, 1.0, -5.0, -12.0, -19.0, -26.0, -33.0, -39.0, -46.0, -53.0, -60.0, -67.0, -73.0, -80.0, -87.0),
    (28.0, 21.0, 14.0, 7.0, 0.0, -7.0, -14.0, -21.0, -27.0, -34.0, -41.0, -48.0, -55.0, -62.0, -69.0, -76.0, -82.0, -89.0),
    (27.0, 20.0, 13.0, 6.0, -1.0, -8.0, -15.0, -22.0, -29.0, -36.0, -43.0, -50.0, -57.0, -64.0, -71.0, -78.0, -84.0, -91.0),
    (26.0, 19.0, 12.0, 5.0, -2.0, -9.0, -16.0, -23.0, -30.0, -37.0, -44.0, -51.0, -58.0, -65.0, -72.0, -79.0, -86.0, -93.0),
    (26.0, 19.0, 12.0, 4.0, -3.0, -10.0, -17.0, -24.0, -31.0, -38.0, -45.0, -52.0, -60.0, -67.0, -74.0, -81.0, -88.0, -95.0),
    (25.0, 18.0, 11.0, 4.0, -3.0, -11.0, -18.0, -25.0, -32.0, -39.0, -46.0, -54.0, -61.0, -68.0, -75.0, -82.0, -89.0, -97.0),
    (25.0, 17.0, 10.0, 3.0, -4.0, -11.0, -19.0, -26.0, -33.0, -40.0, -48.0, -55.0, -62.0, -69.0, -76.0, -84.0, -91.0, -98.0))

#===============================================================================

def part1(dset, windchillF, windchillC):

    dtype = H5T.copy(H5T.H5Type.NATIVE_FLOAT)

    H5D.write(dset, dtype, H5Array[Single](windchillF))

    plistF2C = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    F2C = '(5/9.0)*(x-32)'
    H5P.setDataTransform(plistF2C, F2C)

    dspace = H5DataSpaceId(H5S.H5SType.ALL)

    H5D.read(dset, dtype, dspace, dspace, plistF2C, H5Array[Single](windchillC))

    H5T.close(dtype)

    print '\nData with no write transform, but a read transform:'
    for row in range(windchillC.GetLength(0)):
        for col in range(windchillC.GetLength(1)):
            print '%6.2f ' % (windchillC[row,col]),
        print ''

    return None

#===============================================================================

def part2(dset, windchillF, windchillC):

    dtype = H5T.copy(H5T.H5Type.NATIVE_FLOAT)

    plistF2C = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    F2C = '(5/9.0)*(x-32)'
    H5P.setDataTransform(plistF2C, F2C)

    dspace = H5DataSpaceId(H5S.H5SType.ALL)

    H5D.write(dset, dtype, dspace, dspace, plistF2C, H5Array[Single](windchillF))

    H5D.read(dset, dtype, H5Array[Single](windchillC))

    H5T.close(dtype)
    H5P.close(plistF2C)

    print '\nData with write transform, but no read transform:'
    for row in range(windchillC.GetLength(0)):
        for col in range(windchillC.GetLength(1)):
            print '%6.2f ' % (windchillC[row,col]),
        print ''

    return None

#===============================================================================

def part3(dset, windchillF, windchillC):

    dtype = H5T.copy(H5T.H5Type.NATIVE_FLOAT)

    plistF2C = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    F2C = '(5/9.0)*(x-32)'
    H5P.setDataTransform(plistF2C, F2C)

    plistC2F = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    C2F = '(9/5.0)*x + 32'
    H5P.setDataTransform(plistC2F, C2F)

    dspace = H5DataSpaceId(H5S.H5SType.ALL)

    H5D.write(dset, dtype, dspace, dspace, plistF2C, H5Array[Single](windchillF))

    H5D.read(dset, dtype, dspace, dspace, plistC2F, H5Array[Single](windchillC))

    H5T.close(dtype)
    H5P.close(plistC2F)
    H5P.close(plistF2C)

    print '\nData with both read and write transform:'
    for row in range(windchillC.GetLength(0)):
        for col in range(windchillC.GetLength(1)):
            print '%6.2f ' % (windchillC[row,col]),
        print ''

    return None

#===============================================================================

def part4():

    plistF2C = H5P.create(H5P.PropertyListClass.DATASET_XFER)
    F2C = '(5/9.0)*(x-32)'
    H5P.setDataTransform(plistF2C, F2C)

    transform = H5P.getDataTransform(plistF2C)

    print '\nTransform string (from plistF2C) is: %s' % (transform)

    H5P.close(plistF2C)

    return None

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

shape = Array[Int64]((12,18))

windchillC = Array.CreateInstance(Single, shape)
windchillF = Array.CreateInstance(Single, shape)
print '\nOriginal Data:'
for row in range(shape[0]):
    for col in range(shape[1]):
        windchillF[row,col] = Single(data[row][col])
        print '%6.2f ' % (windchillF[row,col]),
    print ''

h5file = H5F.create('dtransform.h5', H5F.CreateMode.ACC_TRUNC)

dspace = H5S.create_simple(shape.Length, shape)
dtype = H5T.copy(H5T.H5Type.NATIVE_FLOAT)
dset = H5D.create(h5file, 'data_no_trans', dtype, dspace);

part1(dset, windchillF, windchillC)

part2(dset, windchillF, windchillC)

part3(dset, windchillF, windchillC)

part4()

H5D.close(dset)

H5T.close(dtype)
H5S.close(dspace)

H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
