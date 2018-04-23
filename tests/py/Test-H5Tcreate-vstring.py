
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

# create a few string types

count = 0

testCount = str(count).zfill(4)
testName = 'Create variable-length string type check H5T::create(..., -1)'
createHeading(testCount, testName)
expect = True
    
dtype = H5T.create(H5T.CreateClass.STRING,-1)

showValues(expect, (H5T.getClass(dtype) == H5T.H5TClass.STRING) and H5T.isVariableString(dtype))

H5T.close(dtype)
    
count += 1

testCount = str(count).zfill(4)
testName = 'Create fixed-length string type check H5T::create(...,4711)'
createHeading(testCount, testName)
expect = True

dtype = H5T.create(H5T.CreateClass.STRING,4711)

showValues(expect,
    (H5T.getClass(dtype) == H5T.H5TClass.STRING) and (H5T.getSize(dtype) == 4711) and not H5T.isVariableString(dtype))

H5T.close(dtype)

count += 1

createFooter()

print 'Shutting down HDF5 library'
status = H5.Close()

