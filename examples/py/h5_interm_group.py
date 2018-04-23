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

print '\nInitializing HDF5 library\n'
status = H5.Open()

h5file = H5F.create('interm_group.h5', H5F.CreateMode.ACC_TRUNC)

grp1 = H5G.create(h5file, '/G1')
H5G.close(grp1)

H5F.close(h5file)

h5file = H5F.open('interm_group.h5', H5F.OpenMode.ACC_RDWR)

if H5L.Exists(h5file, '/G1'):
    print 'Group /G1 exists in the file'

grp1 = H5G.open(h5file, '/G1')

if not H5L.Exists(grp1, 'G2'):

    clist = H5P.create(H5P.PropertyListClass.LINK_CREATE)
    H5P.SetIntermediateGroupCreation(clist, True)

    H5P_DEFAULT = H5PropertyListId(H5P.Template.DEFAULT)

    grp = H5G.create(grp1, 'G2/G3', clist, H5P_DEFAULT, H5P_DEFAULT)
    H5G.close(grp)

if H5L.Exists(h5file, '/G1/G2'):

    grp = H5G.open(h5file, '/G1/G2')

    info = H5G.getInfo(grp)
    print 'Group /G1/G2 has %d member(s)' % (info.nLinks)

    for i in range(info.nLinks):
        name = H5L.getNameByIndex(grp, '.',
                                  H5IndexType.NAME, H5IterationOrder.NATIVE, i)
        print 'Object\'s name is %s' % (name)

    H5G.close(grp)


H5G.close(grp1)
H5F.close(h5file)

print '\nShutting down HDF5 library'
status = H5.Close()
