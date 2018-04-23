
print 'Beginning Test'
import Formatting
from Formatting import *

print 'Loading clr'
import clr

print 'Loading test module'
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import * 

import System

print 'Initializing HDF5 library'
status = H5.Open()

print 'HDF5 ', H5.Version.Major, '.', H5.Version.Minor, '.', H5.Version.Release

# create a few array types

count = 0

for t in System.Enum.GetValues(H5T.H5Type):

    testCount = str(count).zfill(4)
    tName = str(t)
    testName = 'Create array type check H5T::create_array(' + tName + ',...)'
    createHeading(testCount, testName)
    expect = H5T.H5TClass.ARRAY
    
    baseType = H5T.copy(t)
    dims = System.Array[System.Int64]((4,8))    
    arrayType = H5T.create_array(baseType, dims)    

    showValues(expect, H5T.getClass(arrayType))
    
    H5T.close(baseType)
    H5T.close(arrayType)

    count += 1

createFooter()

print 'Shutting down HDF5 library'
status = H5.Close()

