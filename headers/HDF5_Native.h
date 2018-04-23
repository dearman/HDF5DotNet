
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group (THG).                                       *
 * All rights reserved.                                                    *
 *                                                                         *
 * This file is part of HDF5.  The full HDF5 copyright notice, including   *
 * terms governing use, modification, and redistribution, is contained in  *
 * the files COPYING and Copyright.html.  COPYING can be found at the root *
 * of the source code distribution tree; Copyright.html can be found at the*
 * root level of an installed copy of the electronic HDF5 document set and *
 * is linked from the top-level documents page.  It can also be found at   *
 * http://www.hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have    *
 * access to either file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "H5Apublic.h"
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Gpublic.h"
#include "H5Ppublic.h"
#include "H5public.h"
#include "H5Rpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"

////////////////////////////////////////////////////////////////////////////////
// H5
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5open();

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5close();

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5check_version(
    unsigned int majnum, unsigned int minnum, unsigned int relnum);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5get_libversion(
    unsigned int* majnum, unsigned int* minnum, unsigned int* relnum);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5set_free_list_limits(
    int reg_global_lim, int reg_list_lim,
    int arr_global_lim, int arr_list_lim,
    int blk_global_lim, int blk_list_lim);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5garbage_collect();

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C" herr_t _cdecl H5dont_atexit();

////////////////////////////////////////////////////////////////////////////////
// H5A
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aclose(hid_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Acreate_by_name
    (
    hid_t id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ objectName, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ attributeName, 
    hid_t typeId, 
    hid_t spaceId,
    hid_t create_plist,
    hid_t access_plist,
    hid_t lapl
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Acreate2
    (
    hid_t id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ attributeName,
    hid_t typeId,
    hid_t spaceId,
    hid_t creationPropertyListId,
    hid_t accessPropertyListId
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Adelete
    (
    hid_t id,
    [MarshalAs(UnmanagedType::LPStr)]
    String^ attributeName
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Adelete_by_name
    (
    hid_t id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ objectName,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ attributeName,
    hid_t notUsed
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aget_info
    (
    hid_t loc_id,
    H5A_info_t* info
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aget_name
    (
    hid_t loc_id,
    size_t length,
    char* buf
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aget_name_by_idx
    (
    hid_t id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ objectName,
    H5_index_t indexType,
    H5_iter_order_t iterationOrder,
    hsize_t positionIndex,
    char* attributeName,
    size_t size,
    hid_t propertyListId
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Aget_num_attrs(hid_t loc_id);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aget_space(hid_t attr_id);

[DllImport(HDF5DLL,CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aget_type(hid_t attr_id);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aopen
    (
    hid_t loc_id, 
    [MarshalAs(UnmanagedType::LPStr)]
    String^ attributeName,
    hid_t attributeAccessPropertyListId
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aopen_by_idx
    (
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)]
    String^ objectName,
    H5_index_t indexType,
    H5_iter_order_t iterationOrder,
    hsize_t positionIndex,
    hid_t aapl_id,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aopen_by_name
    (
    hid_t loc_id, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ objectName,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ attributeName,
    hid_t attributeAccessPropertyListId,
    hid_t linkAccessPropertyListId
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aopen_idx
    (
    hid_t loc_id, 
    unsigned int index
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Aopen_name
    (
    hid_t loc_id, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Aread
    (
    hid_t id,
    hid_t typeId, 
    void* buffer
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Awrite
    (
    hid_t id,
    hid_t typeId, 
    void* buffer
    );

////////////////////////////////////////////////////////////////////////////////
// H5D
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dclose(hid_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Dcreate2
    (
    hid_t fileId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ dataSetName,
    hid_t dataType,
    hid_t dataSpaceId,
    hid_t linkCreationPropertyList,
    hid_t dataSetCreationPropertyList,
    hid_t dataSetAccessPropertyList
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Dget_create_plist(hid_t dataSetId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Dget_space(hid_t dataSetId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hsize_t _cdecl H5Dget_storage_size(hid_t dataSetId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Dget_type(hid_t dataSetId);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
           CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dopen2
    (
    hid_t groupOrFileId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ dataSetName,
    hid_t dataSetAccessPropertyListId
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dread
    (
    hid_t dataSetId, 
    hid_t memType,
    hid_t memSpace, 
    hid_t fileSpace, 
    hid_t xfer, 
    void* data
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dset_extent
    (
    hid_t dataSetId,
    const hsize_t size[]
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dwrite
    (
    hid_t dataSetId, 
    hid_t memType,
    hid_t memSpace, 
    hid_t fileSpace, 
    hid_t xfer, 
    void* data
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Dvlen_reclaim
    (
    hid_t type_id, 
    hid_t space_id, 
    hid_t plist_id, 
    void *buf
    );

////////////////////////////////////////////////////////////////////////////////
// H5F
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Fclose(hid_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Fcreate
    (
    [MarshalAs(UnmanagedType::LPStr)]
    String^ filename, 
    unsigned int flags, 
    hid_t creationPropertyList, 
    hid_t accessPropertyList
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Fflush
    (
    hid_t object_id,
    H5F_scope_t scope
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    htri_t _cdecl H5Fis_hdf5(
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Fmount
    (
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    hid_t child_id,
    hid_t plist_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Fopen
    (
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName, 
    unsigned int flags, 
    hid_t accessId
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Funmount
    (
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name
    );

////////////////////////////////////////////////////////////////////////////////
// H5G
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gclose(hid_t fileId);

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Gcreate1
    (
    hid_t fileId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName,
    size_t sizeHint
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Gcreate2
    (
    hid_t fileId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName,
    hid_t linkCreation,
    hid_t groupCreation,
    hid_t groupAccess
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gget_info
    (
    hid_t loc, 
    H5G_info_t* info
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gget_info_by_name
    (
    hid_t loc,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    H5G_info_t* info,
    hid_t linkAccessPropertyList
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gget_num_objs
    (
    hid_t groupOrFileId, 
    hsize_t* size
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gget_objinfo
    (
    hid_t loc, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    hbool_t followLink,
    H5G_stat_t* info
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    ssize_t _cdecl H5Gget_objname_by_idx
    (
    hid_t group, 
    hsize_t index,
    char* name,
    size_t length
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Gopen2
    (
    hid_t groupOrFileId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName,
    hid_t groupAccessPropertyListId
    );

////////////////////////////////////////////////////////////////////////////////
// H5I
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    ssize_t _cdecl H5Iget_name
    (
    hid_t obj_id,
    char* name,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5I_type_t _cdecl H5Iget_type(hid_t obj_id);

////////////////////////////////////////////////////////////////////////////////
// H5L
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t H5Lcreate_hard
    (
    hid_t obj_loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ obj_name,
    hid_t link_loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ link_name,
    hid_t lcpl_id,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t H5Ldelete
    (
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    htri_t H5Lexists
    (
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    hid_t lapl_id
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Lget_info
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName, 
    H5L_info_t* info,
    hid_t lapl_id
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Lget_val
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ linkName, 
    void* linkval_buff,
    size_t size,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Lget_info_by_idx
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName, 
    H5_index_t index,
    H5_iter_order_t iterationOrder,
    hsize_t n,
    H5L_info_t* object_info,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Lget_name_by_idx
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName, 
    int index,
    int iterationOrder,
    hsize_t position,
    char* returnName, 
    size_t returnNameMaxSize,
    hid_t lapl_id
    );

////////////////////////////////////////////////////////////////////////////////
// H5O
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Oget_info
    (
    hid_t locId, 
    H5O_info_t* object_info
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Oget_info_by_idx
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ groupName, 
    H5_index_t sizeHint,
    H5_iter_order_t iterationOrder,
    hsize_t n,
    H5O_info_t* object_info,
    hid_t lapl_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Oget_info_by_name
    (
    hid_t locId, 
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ objectName, 
    H5O_info_t* object_info,
    hid_t propertyList
    );

////////////////////////////////////////////////////////////////////////////////
// H5P
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pclose(hid_t classId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Pcreate(hid_t classId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Pget_chunk
    ( 
    hid_t pListId, 
    int max_ndims, 
    hsize_t* dims
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    ssize_t _cdecl H5Pget_data_transform
    (
    hid_t plist_id,
    char* expression,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5D_layout_t _cdecl H5Pget_layout(hid_t plist);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_buffer
    (
    hid_t pListId,
    hsize_t size, 
    IntPtr tconv, 
    IntPtr bkg
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_chunk
    ( 
    hid_t pListId, 
    int ndims, 
    const hsize_t* dim
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_create_intermediate_group
    (
    hid_t lcpl_id,
    unsigned crt_intermed_group
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_link_creation_order
    (
    hid_t gcpl_id,
    unsigned crt_order_flags
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_data_transform
    (
    hid_t plist_id,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ expression
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_deflate
    (
    hid_t pListId,
    unsigned int level
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_fill_value
    (
    hid_t plist_id,
    hid_t type_id,
    const void *value
    );

#include "H5AllocCallback.h"
#include "H5FreeCallback.h"

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Pset_vlen_mem_manager
    (
    hid_t plist, 
    [In, MarshalAs(UnmanagedType::FunctionPtr)]
    HDF5DotNet::H5AllocCallback^ alloc, 
    IntPtr alloc_info, 
    [In, MarshalAs(UnmanagedType::FunctionPtr)]
    HDF5DotNet::H5FreeCallback^ free, 
    IntPtr free_info
    );

////////////////////////////////////////////////////////////////////////////////
// H5R
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5I_type_t _cdecl H5Iget_type(hid_t obj_id);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Rcreate
    (
    void* ref,
    hid_t loc_id,
    [MarshalAs(UnmanagedType::LPStr)]
    String^ name,
    H5R_type_t ref_type,
    hid_t space_id
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Rdereference
    (
    hid_t obj_id,
    H5R_type_t ref_type,
    void *ref
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    ssize_t _cdecl H5Rget_name
    (
    hid_t loc_id,
    H5R_type_t ref_type,
    void* ref,
    char* name,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Rget_obj_type2
    (
    hid_t loc_id,
    H5R_type_t ref_type,
    void *ref,
    H5O_type_t *obj_type
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Rget_region
    (
    hid_t loc_id,
    H5R_type_t ref_type,
    void *ref
    );

////////////////////////////////////////////////////////////////////////////////
// H5S
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Sclose(hid_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Screate(H5S_class_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Screate_simple
    (
    int rank, 
    [MarshalAs(UnmanagedType::LPArray)] 
    array<hsize_t>^ dims,
    [MarshalAs(UnmanagedType::LPArray)]
    array<hsize_t>^ maxDims
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Sget_simple_extent_dims
    (
    hid_t dataSpaceId, 
    [MarshalAs(UnmanagedType::LPArray)]
    array<hsize_t>^ dims,
    [MarshalAs(UnmanagedType::LPArray)]
    array<hsize_t>^ maxDims
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Sget_simple_extent_ndims(hid_t id);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Sget_simple_extent_npoints(hid_t id);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5S_class_t _cdecl H5Sget_simple_extent_type(hid_t id);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Sselect_elements
    (
    hid_t space_id,
    H5S_seloper_t op,
    size_t num_elements,
    const hsize_t *coord
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Sselect_hyperslab
    (
    hid_t id, 
    H5S_seloper_t selectOperator,
    [MarshalAs(UnmanagedType::LPArray)]
    array<hsize_t>^ start,
    const hsize_t* stride,
    [MarshalAs(UnmanagedType::LPArray)]
    array<hsize_t>^ count,
    const hsize_t* block
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Sselect_none(hid_t id);

////////////////////////////////////////////////////////////////////////////////
// H5T
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tclose(hid_t typeId);

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tcommit2
    (
    hid_t location,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ dataTypeName,
    hid_t typeId,
    hid_t linkCreationPropertyList,
    hid_t dataTypeCreationPropertyList,
    hid_t dataTypeAccessPropertyList
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    htri_t _cdecl H5Tcommitted(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tcopy(hid_t typeId);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tcreate
    (
    H5T_class_t type,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tarray_create2
    (
    hid_t base_type_id,
    unsigned rank,
    const hsize_t dims[]
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tenum_create(hid_t type);

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tenum_insert
    (
    hid_t typeId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ name,
    void* value
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tenum_nameof
    (
    hid_t typeId,
    void* value,
    [MarshalAs(UnmanagedType::LPStr)]
    StringBuilder^ attributeName,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tenum_valueof
    (
    hid_t typeId,
    [MarshalAs(UnmanagedType::LPStr)]
    String^ attributeName,
    void* value
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tequal
    (
    hid_t typeId1,
    hid_t typeId2
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_array_ndims(hid_t type_id);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_array_dims2
    (
    hid_t adtype_id,
    hsize_t dims[]
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tget_class(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5T_cset_t _cdecl H5Tget_cset(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tget_fields
    (
    hid_t typeId, 
    size_t* spos,
    size_t* epos,
    size_t* esize,
    size_t* mpos,
    size_t* msize
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_member_class
    (
    hid_t typeId,
    unsigned int memberNumber
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_member_index
    (
    hid_t typeId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ fieldName
    );

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    char* _cdecl H5Tget_member_name
    (
    hid_t typeId,
    unsigned int fieldIndex
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    size_t _cdecl H5Tget_member_offset
    (
    hid_t typeId, 
    unsigned int member_no
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_member_type
    (
    hid_t typeId,
    unsigned int fieldIndex
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tget_member_value
    (
    hid_t typeId,
    unsigned int memberNumber,
    void* value
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tget_native_type
    (
    hid_t typeId,
    H5T_direction_t offset
    );

[DllImport(HDF5DLL,
    CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tget_super(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_nmembers(hid_t typeId);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5T_norm_t _cdecl H5Tget_norm(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    int _cdecl H5Tget_offset(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5T_order_t _cdecl H5Tget_order(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tget_pad
    (
    hid_t dtype_id,
    H5T_pad_t* lsb,
    H5T_pad_t* msb
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    size_t _cdecl H5Tget_precision(hid_t typeId);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5T_sign_t _cdecl H5Tget_sign(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    size_t _cdecl H5Tget_size(hid_t typeId);

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    H5T_str_t _cdecl H5Tget_strpad(hid_t typeId);

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    char* _cdecl H5Tget_tag(hid_t typeId);

[DllImport(HDF5DLL,
    CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tinsert
    (
    hid_t compoundTypeId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ fieldName,
    size_t offset,
    hid_t filedId
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    htri_t _cdecl H5Tis_variable_str(hid_t typeId);

[DllImport(HDF5DLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Topen2
    (
    hid_t groupOrFileId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ datatypeName,
    hid_t accessPropertyList
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5Tset_size
    (
    hid_t typeId,
    size_t size
    );

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tset_strpad
    (
    hid_t dtype_id,
    H5T_str_t strpad
    ); 

[DllImport(HDF5DLL, CharSet=CharSet::Auto,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tset_order
    (
    hid_t typeId,
    H5T_order_t order
    );

[DllImport(HDF5DLL, CallingConvention=CallingConvention::Cdecl)]
extern "C"
    herr_t _cdecl H5Tvlen_create(hid_t typeId);

////////////////////////////////////////////////////////////////////////////////
// H5TB
////////////////////////////////////////////////////////////////////////////////

[DllImport(HDF5HLDLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5TBget_field_info
    (
    hid_t locId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ tableName,
    char** fieldName, 
    size_t* pFieldSize,
    size_t* pFieldOffset,
    size_t* pTypeSize
    );

[DllImport(HDF5HLDLL, CharSet=CharSet::Ansi,
    CallingConvention=CallingConvention::Cdecl)]
extern "C"
    hid_t _cdecl H5TBget_table_info
    (
    hid_t locId,
    [MarshalAs(UnmanagedType::LPStr)] 
    String^ tableName,
    hsize_t* nFields,
    hsize_t* nRecords
    );

