import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System

print 'Initializing HDF5 library'
status = H5.Open()

print 'HDF5 ', H5.Version.Major, '.', H5.Version.Minor, '.', H5.Version.Release

h5file = H5F.create('sample.h5', H5F.CreateMode.ACC_TRUNC)

dspace = H5S.create_simple(2, System.Array[System.Int64]((256,512)))

dtype = H5T.copy(H5T.H5Type.IEEE_F64LE)

plist = H5P.create(H5P.PropertyListClass.DATASET_CREATE)
H5P.setChunk(plist, System.Array[System.Int64]((32, 64)))
H5P.setDeflate(plist, 7)

P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

dset = H5D.create(h5file, 'floats', dtype, dspace, P_DEFAULT, plist, P_DEFAULT);

data = System.Array.CreateInstance(System.Double, 256,512)
for i in range(256):
    data[i,i] = i
    data[i,256+i] = i

H5D.write(dset, dtype, H5Array[System.Double](data))

H5D.close(dset)
H5P.close(P_DEFAULT)
H5P.close(plist)
H5T.close(dtype)
H5S.close(dspace)

H5F.close(h5file)

print 'Shutting down HDF5 library'
status = H5.Close()
