import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import * 

import System
from System import Array, IntPtr

status = H5.Open()
print '\nWelcome to HDF5 ', H5.Version.Major, '.', H5.Version.Minor, '.', H5.Version.Release, ' !\n'

fileId = H5F.open('h5ex_t_vlstringatt.h5', H5F.OpenMode.ACC_RDONLY)
dsetId = H5D.open(fileId, '/DS1')
attrId = H5A.open(dsetId, 'A1')
typeId = H5A.getType(attrId)

print 'Attribute type class is %s' % H5T.getClass(typeId)
print 'Variable length string? %s' % H5T.isVariableString(typeId)

spaceId = H5A.getSpace(attrId)
print 'Dims = %i' % H5S.getSimpleExtentNDims(spaceId)
npoints = H5S.getSimpleExtentNPoints(spaceId)
print 'Count = %i' % npoints

mtypeId = H5T.getNativeType(typeId, H5T.Direction.ASCEND)

# since we don't know how long the strings will be
# the runtime allocates them for us
# we just provide an array of pointers
buffer = Array.CreateInstance(IntPtr, npoints)

H5A.read(attrId, mtypeId, H5Array[IntPtr](buffer))

print 'Value:\n'

for i in range(0,npoints):
    print System.Runtime.InteropServices.Marshal.PtrToStringAnsi(buffer[i])

H5T.close(mtypeId)
H5S.close(spaceId)
H5T.close(typeId)
H5A.close(attrId)
H5D.close(dsetId)
H5F.close(fileId)

print '\nShutting down HDF5 library\n'
status = H5.Close()
