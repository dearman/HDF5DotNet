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

# This program creates a group in the file and two datasets in the group.
# Hard link to the group object is created and one of the datasets is accessed
# under new name.
# Iterator functions are used to find information about the objects
# in the root group and in the created group.


import clr
clr.AddReferenceToFile('HDF5DotNet.dll')
import HDF5DotNet
from HDF5DotNet import *

import System
from System import Array, Int32, Int64

#===============================================================================

def createGroupAndDatasets(h5file):

    H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

    grp = H5G.create(h5file, 'Data')

    dims = Array[Int64]((1000, 20))
    dspace = H5S.create_simple(dims.Length, dims)

    plist = H5P.create(H5P.PropertyListClass.DATASET_CREATE)
    cdims = Array[Int64]((20, 20))
    H5P.setChunk(plist, cdims)
    H5P.setDeflate(plist, 6)

    dtype = H5T.copy(H5T.H5Type.NATIVE_INT)
    H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

    dset = H5D.create(h5file, '/Data/Compressed_Data', dtype, dspace,
                  H5P_DEFAULT, plist, H5P_DEFAULT)

    H5D.close(dset)
    H5T.close(dtype)
    H5P.close(plist)
    H5S.close(dspace)

    dims = Array[Int64]((500, 20))
    dspace = H5S.create_simple(dims.Length, dims)
    dtype = H5T.copy(H5T.H5Type.NATIVE_FLOAT)

    dset = H5D.create(h5file, '/Data/Float_Data', dtype, dspace)

    H5D.close(dset)
    H5T.close(dtype)
    H5S.close(dspace)
    H5G.close(grp)

    return None

#===============================================================================

def checkDataset(h5file, h5path):

    dset = H5D.open(h5file, h5path)
    if dset.Id < 0:
        print 'Dataset \'%s\' not found!!!' % (h5path)
    else:
        print '\'%s\' dataset is open.' % (h5path)
    H5D.close(dset)

    return None

#===============================================================================

def fileInfo(locId, name, linfo, opdata):

    print '\nName : %s' % (name)

    return H5IterationResult.SUCCESS 

#===============================================================================

def groupInfo(locId, name, linfo, opdata):

    print '\nName : %s' % (name)

    dset = H5D.open(locId, name)
    clist = H5D.getCreatePropertyList(dset)

    if H5D.Layout.CHUNKED == H5P.getLayout(clist):

        shape = H5P.getChunk(clist, 2)
        print 'chunk rank %d, dimensions %d x %d' % (shape.Length, shape[0], shape[1])
    else:

        dtype = H5D.getType(dset)
        tclass = H5T.getClass(dtype)

        if tclass == H5T.H5TClass.INTEGER:
            print ' Datatype is \'H5T_NATIVE_INTEGER\'.'
        elif tclass == H5T.H5TClass.FLOAT:
            print ' Datatype is \'H5T_NATIVE_FLOAT\'.'
        elif tclass == H5T.H5TClass.STRING:
            print ' Datatype is \'H5T_NATIVE_STRING\'.'
        elif tclass == H5T.H5TClass.BITFIELD:
            print ' Datatype is \'H5T_NATIVE_BITFIELD\'.'
        elif tclass == H5T.H5TClass.OPAQUE:
            print ' Datatype is \'H5T_NATIVE_OPAQUE\'.'
        elif tclass == H5T.H5TClass.COMPOUND:
            print ' Datatype is \'H5T_NATIVE_COMPOUND\'.'
        else:
            print ' Datatype is unknown.'

        H5T.close(dtype)

    H5P.close(clist)
    H5D.close(dset)

    return H5IterationResult.SUCCESS 

#===============================================================================

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('group.h5', H5F.CreateMode.ACC_TRUNC)

createGroupAndDatasets(h5file)

checkDataset(h5file, '/Data/Compressed_Data')

H5L.createHardLink(h5file, 'Data', h5file, 'Data_new')

checkDataset(h5file, '/Data_new/Compressed_Data')

pos = 0 
grp = H5G.open(h5file, '/')
H5L.iterate(grp, H5IndexType.NAME, H5IterationOrder.INCREASING,
            pos, fileInfo, None)
H5G.close(grp)

H5L.Delete(h5file, 'Data')
print '\n\'Data\' is unlinked'

grp = H5G.open(h5file, 'Data_new')
H5L.iterate(grp, H5IndexType.NAME, H5IterationOrder.INCREASING,
            pos, groupInfo, None)
H5G.close(grp)

H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
