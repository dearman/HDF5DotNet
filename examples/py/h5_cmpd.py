
import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Byte, Double, IntPtr, Int32, Int64

import System.IO
from System.IO import BinaryReader, BinaryWriter, MemoryStream

import System.Runtime.InteropServices
from System.Runtime.InteropServices import Marshal

#===============================================================================

H5T_NATIVE_DOUBLE = H5T.H5Type.NATIVE_DOUBLE
H5T_NATIVE_INT = H5T.H5Type.NATIVE_INT
H5T_STD_I64BE = H5T.H5Type.STD_I64BE
H5T_IEEE_F64BE = H5T.H5Type.IEEE_F64BE
STRING = H5T.CreateClass.STRING

#===============================================================================

def createMemType():

    strtype = H5T.create(STRING, -1)
    strsize = H5T.getSize(strtype)

    # component name -> (offset, size, type)

    ht = { 'Serial number': (0, 4, H5T_NATIVE_INT),
           'Location': (4, strsize, strtype),
           'Temperature': (4+strsize, 8, H5T_NATIVE_DOUBLE),
           'Pressure': (4+strsize+8, 8, H5T_NATIVE_DOUBLE) }

    sizeof = 0
    for k in ht.keys():
        sizeof  += ht[k][1]

    dtype = H5T.create(H5T.CreateClass.COMPOUND, sizeof)
    for k in ht.keys():
        H5T.insert(dtype, k, ht[k][0], ht[k][2])

    H5T.close(strtype)

    return dtype

#===============================================================================

def createFileType():

    strtype = H5T.create(STRING, -1)
    strsize = H5T.getSize(strtype)

    # component name -> (offset, size, type)

    ht = { 'Serial number': (0, 8, H5T_STD_I64BE),
           'Location': (8, strsize, strtype),
           'Temperature': (8+strsize, 8, H5T_IEEE_F64BE),
           'Pressure': (16+strsize, 8, H5T_IEEE_F64BE) }

    sizeof = 0
    for k in ht.keys():
        sizeof  += ht[k][1]

    dtype = H5T.create(H5T.CreateClass.COMPOUND, sizeof)
    for k in ht.keys():
        H5T.insert(dtype, k, ht[k][0], ht[k][2])

    H5T.close(strtype)

    return dtype

#===============================================================================

def createDatasetWithCompoundType(h5file):

    mtype = createMemType() 
    ftype = createFileType() 

    npoints = 4 
    shape = Array[Int64]((npoints,))
    dspace = H5S.create_simple(shape.Length, shape)

    dset = H5D.create(h5file, 'DS1', ftype, dspace)

    ms = MemoryStream()
    writer = BinaryWriter(ms)

    writer.Write(Int32(1153))
    s = 'Exterior (static)'
    if IntPtr.Size == 8:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt64())
    else:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt32())
    writer.Write(Double(53.23))
    writer.Write(Double(24.57))

    writer.Write(Int32(1184))
    s = 'Intake'
    if IntPtr.Size == 8:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt64())
    else:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt32())
    writer.Write(Double(55.12))
    writer.Write(Double(22.95))

    writer.Write(Int32(1027))
    s = 'Intake manifold'
    if IntPtr.Size == 8:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt64())
    else:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt32())
    writer.Write(Double(103.55))
    writer.Write(Double(31.23))

    writer.Write(Int32(1313))
    s = 'Exhaust manifold'
    if IntPtr.Size == 8:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt64())
    else:
        writer.Write(Marshal.StringToHGlobalAnsi(s).ToInt32())
    writer.Write(Double(1252.89))
    writer.Write(Double(84.11))

    byteArray = ms.ToArray()

    H5D.write(dset, mtype, H5Array[Byte](byteArray))

    H5S.close(dspace)
    H5T.close(ftype)
    H5T.close(mtype)

    return dset

#===============================================================================

def readFromDatasetWithCompoundType(dset):

    mtype = createMemType() 
    sizeof = H5T.getSize(mtype)
    dspace = H5D.getSpace(dset)
    npoints = H5S.getSimpleExtentNPoints(dspace)
    
    shape = Array[Int64]((npoints*sizeof,))
    byteArray = Array.CreateInstance(Byte, shape)

    H5D.read(dset, mtype, H5Array[Byte](byteArray))

    ms = MemoryStream(byteArray)
    reader = BinaryReader(ms)

    for i in range(npoints):
        if IntPtr.Size == 8:
            print '%d,%s,%.2f,%.2f' % (
                reader.ReadInt32(),
                Marshal.PtrToStringAnsi(IntPtr(reader.ReadInt64())),
                reader.ReadDouble(),
                reader.ReadDouble())
        else:
            print '%d,%s,%.2f,%.2f' % (
                reader.ReadInt32(),
                Marshal.PtrToStringAnsi(IntPtr(reader.ReadInt32())),
                reader.ReadDouble(),
                reader.ReadDouble())

    H5S.close(dspace)
    H5T.close(mtype)

    return None

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

name = 'SDScompound.h5'

print "Creating file '%s'" % name

h5file = H5F.create(name, H5F.CreateMode.ACC_TRUNC)

print '\nCreating dataset and writing to file...'

dset = createDatasetWithCompoundType(h5file)

print '\nReading from dataset...\n'

readFromDatasetWithCompoundType(dset)

print '\nDone.'

H5D.close(dset)

H5F.close(h5file)

print '\nShutting down HDF5 library\n'
status = H5.Close()
