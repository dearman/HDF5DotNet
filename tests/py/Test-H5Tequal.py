
################################################################################
# Lookup tables for equal HDF5 datatypes
################################################################################

ht32LE = {
    'NATIVE_B8'      : ('STD_B8LE'),
    'NATIVE_B16'     : ('STD_B16LE'),
    'NATIVE_B32'     : ('STD_B32LE'),
    'NATIVE_B64'     : ('STD_B64LE'),
    'NATIVE_DOUBLE'  : ('IEEE_F64LE', 'NATIVE_LDOUBLE'),
    'NATIVE_FLOAT'   : ('IEEE_F32LE'),
    'NATIVE_HBOOL'   : ('NATIVE_HERR', 'NATIVE_INT', 'NATIVE_LONG',
                        'STD_I32LE'),
    'NATIVE_HERR'    : ('NATIVE_HBOOL', 'NATIVE_INT', 'NATIVE_LONG',
                        'STD_I32LE'),
    'NATIVE_HADDR'   : ('NATIVE_HSIZE', 'NATIVE_ULLONG', 'STD_U64LE'),
    'NATIVE_HSIZE'   : ('NATIVE_HADDR', 'NATIVE_ULLONG', 'STD_U64LE'),
    'NATIVE_HSSIZE'  : ('STD_I64LE', 'NATIVE_LLONG'),
    'NATIVE_INT'     : ('NATIVE_HERR', 'NATIVE_LONG', 'STD_I32LE'),
    'NATIVE_LDOUBLE' : ('IEEE_F64LE', 'NATIVE_DOUBLE'),
    'NATIVE_LONG'    : ('NATIVE_INT' , 'STD_I32LE'),
    'NATIVE_LLONG'   : ('NATIVE_HSSIZE', 'STD_I64LE'),
    'NATIVE_SCHAR'   : ('STD_I8LE'),
    'NATIVE_SHORT'   : ('STD_I16LE'),
    'NATIVE_UCHAR'   : ('STD_U8LE'),
    'NATIVE_USHORT'  : ('STD_U16LE'),
    'NATIVE_UINT'    : ('NATIVE_ULONG', 'STD_U32LE'),
    'NATIVE_ULONG'   : ('NATIVE_UINT', 'STD_U32LE'),
    'NATIVE_ULLONG'  : ('NATIVE_HADDR', 'NATIVE_HSIZE', 'STD_U64LE')
}

ht64LE = {
    'NATIVE_B8'      : ('STD_B8LE'),
    'NATIVE_B16'     : ('STD_B16LE'),
    'NATIVE_B32'     : ('STD_B32LE'),
    'NATIVE_B64'     : ('STD_B64LE'),
    'NATIVE_DOUBLE'  : ('IEEE_F64LE', 'NATIVE_LDOUBLE'),
    'NATIVE_FLOAT'   : ('IEEE_F32LE'),
    'NATIVE_HBOOL'   : ('NATIVE_HERR', 'NATIVE_INT', 'NATIVE_LONG',
                        'STD_I32LE'),
    'NATIVE_HERR'    : ('NATIVE_HBOOL', 'NATIVE_INT', 'NATIVE_LONG',
                        'STD_I32LE'),
    'NATIVE_HADDR'   : ('NATIVE_HSIZE', 'NATIVE_ULLONG', 'STD_U64LE'),
    'NATIVE_HSIZE'   : ('NATIVE_HADDR', 'NATIVE_ULLONG', 'STD_U64LE'),
    'NATIVE_HSSIZE'  : ('STD_I64LE', 'NATIVE_LLONG'),
    'NATIVE_INT'     : ('NATIVE_HERR', 'NATIVE_LONG', 'STD_I32LE'),
    'NATIVE_LDOUBLE' : ('IEEE_F64LE', 'NATIVE_DOUBLE'),
    'NATIVE_LONG'    : ('NATIVE_INT' , 'STD_I32LE'),
    'NATIVE_LLONG'   : ('NATIVE_HSSIZE', 'STD_I64LE'),
    'NATIVE_SCHAR'   : ('STD_I8LE'),
    'NATIVE_SHORT'   : ('STD_I16LE'),
    'NATIVE_UCHAR'   : ('STD_U8LE'),
    'NATIVE_USHORT'  : ('STD_U16LE'),
    'NATIVE_UINT'    : ('NATIVE_ULONG', 'STD_U32LE'),
    'NATIVE_ULONG'   : ('NATIVE_UINT', 'STD_U32LE'),
    'NATIVE_ULLONG'  : ('NATIVE_HADDR', 'NATIVE_HSIZE', 'STD_U64LE')
}

################################################################################

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
import platform, sys 

ht = {}

if sys.byteorder == 'little':

    if (platform.architecture())[0] == '32bit':
        ht = ht32LE
    else:
        if (platform.architecture())[0] == '64bit':
            ht = ht64LE
        else:
            print 'ERROR: Only 32- and 64-bit architectures are supported.'
            exit(-4711)

else:
    print 'ERROR: Currently, we support only the little-endian format.'
    exit(-4711)

print 'Initializing HDF5 library'
status = H5.Open()

print 'HDF5 ', H5.Version.Major, '.', H5.Version.Minor, '.', H5.Version.Release

# do a pairwise comparision of all members of H5T.H5Type

count = 0

for s in System.Enum.GetValues(H5T.H5Type):

    for t in System.Enum.GetValues(H5T.H5Type):

        testCount = str(count).zfill(4)
        sName = str(s)
        tName = str(t)
        testName = 'Equality check H5T::equal(' + sName + ',' + tName + ')'
        createHeading(testCount, testName)
        
        expect = -1
        
        # check for equivalence
        if ht.has_key(sName) and (tName in ht[sName]): expect = 1
        else:
            if ht.has_key(tName) and (sName in ht[tName]): expect = 1

        # check for enum equality
        if (expect == -1):
            if s != t: expect = 0
            else: expect = 1

        type1 = H5T.copy(s)
        type2 = H5T.copy(t)

        showValues(expect, H5T.equal(type1, type2))
        count += 1

createFooter()

H5T.close(type1)
H5T.close(type2)

print 'Shutting down HDF5 library'
status = H5.Close()

