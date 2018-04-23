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
#pragma once

#include "HDFExceptionSubclasses.h"

#include "H5Spublic.h"

namespace HDF5DotNet
{
   ref class H5DataSpaceId;

   /// <summary>
   /// The H5S contains static member function for each of the supported
   /// H5S calls of the HDF5 library.
   /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html"/>
   /// </summary>
   public ref class H5S sealed
   {
   public:

#pragma region documentation
      /// <summary>
      /// Creates a new simple dataspace and opens it for access.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-CreateSimple"/>
      /// </summary>
      /// <param name="rank"> Number of dimensions of dataspace.
      /// </param>
      /// <param name="dims">
      /// An array of the size of each dimension.
      /// </param>
      /// <param name="maxDims">
      /// An array of the maximum size of each dimension.
      /// </param>
      /// <remarks>
      /// <p>
      /// H5Screate_simple creates a new simple dataspace and opens it 
      ///  for access.
      /// </p>
      /// <p>
      /// rank is the number of dimensions used in the dataspace.
      /// </p>
      /// <p>
      /// dims is an array specifying the size of each dimension of the 
      /// dataset while maxdims is an array specifying the upper limit
      /// on the size of each dimension. maxdims may be the null
      /// pointer, in which case the upper limit is the same as dims.
      /// </p>
      /// <p>
      /// If an element of maxdims is H5S_UNLIMITED, (-1), the maximum
      /// size of the corresponding dimension is unlimited. Otherwise,
      /// no element of maxdims should be smaller than the corresponding
      /// element of dims.
      /// </p>
      /// <p>
      /// The dataspace identifier returned from this function must be
      /// released with H5Sclose or resource leaks will occur. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static H5DataSpaceId^ create_simple(int rank, 
         array<hssize_t>^ dims,
         array<hssize_t>^ maxDims);

#pragma region documentation
      /// <summary>
      /// Creates a new simple dataspace and opens it for access.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-CreateSimple"/>
      /// </summary>
      /// <param name="rank"> Number of dimensions of dataspace.
      /// </param>
      /// <param name="dims">
      /// An array of the size of each dimension.
      /// </param>
      /// <remarks>
      /// <p>
      /// H5Screate_simple creates a new simple dataspace and opens it 
      ///  for access.
      /// </p>
      /// <p>
      /// rank is the number of dimensions used in the dataspace.
      /// </p>
      /// <p>
      /// The upper limit is the same as dims.
      /// </p>
      /// <p>
      /// The dataspace identifier returned from this function must be
      /// released with H5Sclose or resource leaks will occur. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static H5DataSpaceId^ create_simple(int rank, 
         array<hssize_t>^ dims);

      /// <summary>
      /// Releases and terminates access to a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-Close"/>
      /// </summary>
      /// <param name="id"> Identifier of dataspace to release.
      /// </param>
      static void close(H5DataSpaceId^ id);	


      ///<summary>
      /// Enumeration type for selection.
      ///</summary>
      enum class SelectOperator
      {
         /// <summary> 
         /// Replaces the existing selection with the 
         /// parameters from this call. Overlapping blocks are not 
         /// supported with this operator. 
         ///</summary>
         SET = H5S_SELECT_SET,

         /// <summary>
         /// Adds the new selection to the existing selection.    
         /// (Binary OR)
         /// </summary>
         OR = H5S_SELECT_OR,

         /// <summary>
         /// Retains only the overlapping portions of the new selection
         /// and the existing selection. (Binary AND)
         /// </summary>
         AND = H5S_SELECT_AND,

         /// <summary>
         /// Retains only the elements that are members of the new 
         /// selection or the existing selection, excluding elements that
         /// are members of both selections. (Binary exclusive-OR, XOR)
         /// </summary>
         XOR = H5S_SELECT_XOR,

         /// <summary>
         /// Retains only elements of the existing selection that are not
         /// in the new selection.
         /// </summary>
         NOTB = H5S_SELECT_NOTB,   	

         /// <summary>
         /// Retains only elements of the new selection that are not in
         /// the existing selection.
         /// </summary>
         NOTA = H5S_SELECT_NOTA 	
      };

      /// <summary>
      /// Enumeration for H5S type includes ALL and UNLIMITED.
      /// </summary>
      enum class H5SType
      {
         NO_TYPE = -1,
         ALL = H5S_ALL,
         UNLIMITED = H5S_UNLIMITED
      };

      /// <summary>
      /// Enumeration for H5S class includes SCALAR and SIMPLE.
      /// </summary>
      enum class H5SClass
      {
          /// <summary> Error </summary>
          NO_CLASS = H5S_NO_CLASS,
          /// <summary> Null dataspace </summary>
          NULLSPACE = H5S_NULL,
          /// <summary> Scalar dataspace </summary>
          SCALAR = H5S_SCALAR,
          /// <summary> Simple dataspace </summary>
          SIMPLE = H5S_SIMPLE
      };

#pragma region documentation
      /// <summary>
      /// Creates a new dataspace of a specified type.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-Create"/>
      /// </summary>
      /// <param name="createClass"> 
      /// The type of dataspace to be created.
      /// </param>
      /// <returns>
      /// Returns a dataspace identifier if successful.
      /// </returns>
      /// <exception cref="H5ScreateException">
      /// throws H5ScreateException on failure.
      /// </exception>
      /// <remarks>
      /// H5Screate creates a new dataspace of a particular type. The
      /// types currently supported are H5SClass.SCALAR and H5SClass.SIMPLE;
      /// others are planned to be added later.
      /// </remarks>
#pragma endregion documentation

      static H5DataSpaceId^ create(H5SClass createClass);

#pragma region documentation
      ///<summary>
      /// Selects array elements to be included in the selection for a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectElements"/>
      /// <param name="spaceId">
      /// IN: Identifier of dataspace selection to modify
      /// </param>
      /// <param name="selectOperator">
      /// IN: Operation to perform on current selection.
      /// </param>
      /// <param name="numElements">
      /// IN: Number of elements to be selected.
      /// </param>
      /// <param name="coord">
      /// IN: A serialized copy of a 2-dimensional array of zero-based values specifying the coordinates
      ///     of the elements in the point selection.
      /// </param>
      ///</summary>
#pragma endregion documentation

      static void selectElements(H5DataSpaceId^ spaceId,
         H5S::SelectOperator selectOperator,
         System::IntPtr   numElements,
         array<hssize_t>^ coord);

#pragma region documentation
      /// <summary>
      /// Selects a hyperslab region to add to the current selected
      /// region.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectHyperslab"/>
      /// </summary>
      /// <param name="spaceId">
      /// IN: Identifier of dataspace selection to modify
      /// </param>
      /// <param name="selectOperator">
      /// IN: Operation to perform on current selection.
      /// </param>
      /// <param name="start">
      /// IN: Offset of start of hyperslab
      /// </param>
      /// <param name="stride">
      /// IN: Hyperslab stride.
      /// </param> 
      /// <param name="count">
      /// IN: Number of blocks included in hyperslab.
      /// </param> 
      /// <param name="block"> 
      /// IN: Size of block in hyperslab.
      /// </param>
      /// <remarks>
      /// <p>
      /// H5S.selectStridedHyperslab selects a hyperslab region to add to
      /// the current selected region for the dataspace specified by 
      /// space_id.
      /// </p>
      /// <p>
      /// The start, stride, count, and block arrays must be the same
      /// size as the rank of the dataspace.
      /// </p>
      /// <p>
      /// The selection operator op determines how the new selection is
      /// to be combined with the already existing selection for the 
      /// dataspace. The following operators are supported:
      /// </p>
      /// <ul>
      /// <li>
      /// H5S_SELECT_SET - Replaces the existing selection with the 
      /// parameters from this call. Overlapping blocks are not
      /// supported with this operator.
      /// </li>
      /// <li>
      /// H5S_SELECT_OR - Adds the new selection to the existing 
      /// selection. (Binary OR)
      /// </li>
      /// <li>
      /// H5S_SELECT_AND - Retains only the overlapping portions of the 
      /// new selection and the existing selection.    (Binary AND)
      /// </li>
      /// <li>
      /// H5S_SELECT_XOR - Retains only the elements that are members of
      /// the new selection or the existing selection, excluding
      /// elements that are members of both selections. (Binary 
      /// exclusive-OR, XOR)
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTB - Retains only elements of the existing 
      /// selection that are not in the new selection.
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTA - Retains only elements of the new selection
      /// that are not in the existing selection.
      /// </li>
      /// </ul>
      /// <p>
      /// The start array determines the starting coordinates of the 
      /// hyperslab to select.
      /// </p>
      /// <p>
      /// The stride array chooses array locations from the dataspace
      /// with each value in the stride array determining how many
      /// elements to move in each dimension. Setting a value in the 
      /// stride array to 1 moves to each element in that dimension of
      /// the dataspace; setting a value of 2 in alocation in the stride
      /// array moves to every other element in that dimension of the 
      /// dataspace. In other words, the stride determines the number of
      /// elements to move from the start location in each dimension. 
      /// Stride values of 0 are not allowed. 
      /// </p>
      /// <p>
      /// The count array determines how many blocks to select from the 
      /// dataspace, in each dimension.
      /// </p>
      /// <p>
      /// The block array determines the size of the element block 
      /// selected from the dataspace. If the block parameter is
      /// omitted, the block size defaults to a single element in each 
      /// dimension (as if the block array were set to all 1's).
      /// </p>
      /// <p>
      /// For example, in a 2-dimensional dataspace, setting start 
      /// to [1,1], stride to [4,4], count to [3,7], and block to [2,2] 
      /// selects 21 2x2 blocks of array elements starting with 
      /// location (1,1) and selecting blocks at locations (1,1), 
      /// (5,1), (9,1), (1,5), (5,5), etc.
      /// </p>
      /// <p>
      /// Regions selected with this function call default to 
      /// C order iteration when I/O is performed. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static void selectStridedHyperslab(H5DataSpaceId^ spaceId,
         H5S::SelectOperator selectOperator,
         array<hssize_t>^ start,
         array<hssize_t>^ stride,
         array<hssize_t>^ count,
         array<hssize_t>^ block);

#pragma region documentation
      /// <summary>
      /// Selects a hyperslab region to add to the current selected
      /// region.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectHyperslab"/>
      /// </summary>
      /// <param name="spaceId">
      /// IN: Identifier of dataspace selection to modify
      /// </param>
      /// <param name="selectOperator">
      /// IN: Operation to perform on current selection.
      /// </param>
      /// <param name="start">
      /// IN: Offset of start of hyperslab
      /// </param>
      /// <param name="stride">
      /// IN: Hyperslab stride.
      /// </param> 
      /// <param name="count">
      /// IN: Number of blocks included in hyperslab.
      /// </param> 
      /// <remarks>
      /// <p>
      /// H5S.selectStridedHyperslab selects a hyperslab region to add to
      /// the current selected region for the dataspace specified by 
      /// space_id.
      /// </p>
      /// <p>
      /// The start, stride, count, and block arrays must be the same
      /// size as the rank of the dataspace.
      /// </p>
      /// <p>
      /// The selection operator op determines how the new selection is
      /// to be combined with the already existing selection for the 
      /// dataspace. The following operators are supported:
      /// </p>
      /// <ul>
      /// <li>
      /// H5S_SELECT_SET - Replaces the existing selection with the 
      /// parameters from this call. Overlapping blocks are not
      /// supported with this operator.
      /// </li>
      /// <li>
      /// H5S_SELECT_OR - Adds the new selection to the existing 
      /// selection. (Binary OR)
      /// </li>
      /// <li>
      /// H5S_SELECT_AND - Retains only the overlapping portions of the 
      /// new selection and the existing selection.    (Binary AND)
      /// </li>
      /// <li>
      /// H5S_SELECT_XOR - Retains only the elements that are members of
      /// the new selection or the existing selection, excluding
      /// elements that are members of both selections. (Binary 
      /// exclusive-OR, XOR)
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTB - Retains only elements of the existing 
      /// selection that are not in the new selection.
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTA - Retains only elements of the new selection
      /// that are not in the existing selection.
      /// </li>
      /// </ul>
      /// <p>
      /// The start array determines the starting coordinates of the 
      /// hyperslab to select.
      /// </p>
      /// <p>
      /// The stride array chooses array locations from the dataspace
      /// with each value in the stride array determining how many
      /// elements to move in each dimension. Setting a value in the 
      /// stride array to 1 moves to each element in that dimension of
      /// the dataspace; setting a value of 2 in alocation in the stride
      /// array moves to every other element in that dimension of the 
      /// dataspace. In other words, the stride determines the number of
      /// elements to move from the start location in each dimension. 
      /// Stride values of 0 are not allowed. 
      /// </p>
      /// <p>
      /// The count array determines how many blocks to select from the 
      /// dataspace, in each dimension.
      /// </p>
      /// <p>
      /// The block array determines the size of the element block 
      /// selected from the dataspace. If the block parameter is
      /// omitted, the block size defaults to a single element in each 
      /// dimension (as if the block array were set to all 1's).
      /// </p>
      /// <p>
      /// For example, in a 2-dimensional dataspace, setting start 
      /// to [1,1], stride to [4,4], count to [3,7], and block to [2,2] 
      /// selects 21 2x2 blocks of array elements starting with 
      /// location (1,1) and selecting blocks at locations (1,1), 
      /// (5,1), (9,1), (1,5), (5,5), etc.
      /// </p>
      /// <p>
      /// Regions selected with this function call default to 
      /// C order iteration when I/O is performed. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static void selectStridedHyperslab(H5DataSpaceId^ spaceId,
         H5S::SelectOperator selectOperator,
         array<hssize_t>^ start,
         array<hssize_t>^ stride,
         array<hssize_t>^ count);

#pragma region documentation
      /// <summary>
      /// Selects a hyperslab region to add to the current selected
      /// region.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectHyperslab"/>
      /// </summary>
      /// <param name="spaceId">
      /// IN: Identifier of dataspace selection to modify
      /// </param>
      /// <param name="selectOperator">
      /// IN: Operation to perform on current selection.
      /// </param>
      /// <param name="start">
      /// IN: Offset of start of hyperslab
      /// </param>
      /// <param name="count">
      /// IN: Number of blocks included in hyperslab.
      /// </param> 
      /// <param name="block"> 
      /// IN: Size of block in hyperslab.
      /// </param>
      /// <remarks>
      /// <p>
      /// H5S.selectStridedHyperslab selects a hyperslab region to add to
      /// the current selected region for the dataspace specified by 
      /// space_id.
      /// </p>
      /// <p>
      /// The start, count, and block arrays must be the same
      /// size as the rank of the dataspace.
      /// </p>
      /// <p>
      /// The selection operator op determines how the new selection is
      /// to be combined with the already existing selection for the 
      /// dataspace. The following operators are supported:
      /// </p>
      /// <ul>
      /// <li>
      /// H5S_SELECT_SET - Replaces the existing selection with the 
      /// parameters from this call. Overlapping blocks are not
      /// supported with this operator.
      /// </li>
      /// <li>
      /// H5S_SELECT_OR - Adds the new selection to the existing 
      /// selection. (Binary OR)
      /// </li>
      /// <li>
      /// H5S_SELECT_AND - Retains only the overlapping portions of the 
      /// new selection and the existing selection.    (Binary AND)
      /// </li>
      /// <li>
      /// H5S_SELECT_XOR - Retains only the elements that are members of
      /// the new selection or the existing selection, excluding
      /// elements that are members of both selections. (Binary 
      /// exclusive-OR, XOR)
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTB - Retains only elements of the existing 
      /// selection that are not in the new selection.
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTA - Retains only elements of the new selection
      /// that are not in the existing selection.
      /// </li>
      /// </ul>
      /// <p>
      /// The start array determines the starting coordinates of the 
      /// hyperslab to select.
      /// </p>
      /// <p>
      /// The results of calling selectHyperslab are identical to
      /// calling selectStridedHyperslab, with stride values equal to 1.
      /// </p>
      /// <p>
      /// The count array determines how many blocks to select from the 
      /// dataspace, in each dimension.
      /// </p>
      /// <p>
      ///     The block array determines the size of the element block 
      /// selected from the dataspace. If the block parameter is
      /// omitted, the block size defaults to a single element in each 
      /// dimension (as if the block array were set to all 1's).
      /// </p>
      /// <p>
      /// Regions selected with this function call default to 
      /// C order iteration when I/O is performed. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static void selectHyperslab(H5DataSpaceId^ spaceId,
         H5S::SelectOperator selectOperator,
         array<hssize_t>^ start,
         array<hssize_t>^ count,
         array<hssize_t>^ block);

#pragma region documentation
      /// <summary>
      /// Selects a hyperslab region to add to the current selected
      /// region.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectHyperslab"/>
      /// </summary>
      /// <param name="spaceId">
      /// IN: Identifier of dataspace selection to modify
      /// </param>
      /// <param name="selectOperator">
      /// IN: Operation to perform on current selection.
      /// </param>
      /// <param name="start">
      /// IN: Offset of start of hyperslab
      /// </param>
      /// <param name="count">
      /// IN: Number of blocks included in hyperslab.
      /// </param> 
      /// <remarks>
      /// <p>
      /// H5S.selectStridedHyperslab selects a hyperslab region to add to
      /// the current selected region for the dataspace specified by 
      /// space_id.
      /// </p>
      /// <p>
      /// The start, count, and block arrays must be the same
      /// size as the rank of the dataspace.
      /// </p>
      /// <p>
      /// The selection operator op determines how the new selection is
      /// to be combined with the already existing selection for the 
      /// dataspace. The following operators are supported:
      /// </p>
      /// <ul>
      /// <li>
      /// H5S_SELECT_SET - Replaces the existing selection with the 
      /// parameters from this call. Overlapping blocks are not
      /// supported with this operator.
      /// </li>
      /// <li>
      /// H5S_SELECT_OR - Adds the new selection to the existing 
      /// selection. (Binary OR)
      /// </li>
      /// <li>
      /// H5S_SELECT_AND - Retains only the overlapping portions of the 
      /// new selection and the existing selection.    (Binary AND)
      /// </li>
      /// <li>
      /// H5S_SELECT_XOR - Retains only the elements that are members of
      /// the new selection or the existing selection, excluding
      /// elements that are members of both selections. (Binary 
      /// exclusive-OR, XOR)
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTB - Retains only elements of the existing 
      /// selection that are not in the new selection.
      /// </li>
      /// <li>
      /// H5S_SELECT_NOTA - Retains only elements of the new selection
      /// that are not in the existing selection.
      /// </li>
      /// </ul>
      /// <p>
      /// The start array determines the starting coordinates of the 
      /// hyperslab to select.
      /// </p>
      /// <p>
      /// The results of calling selectHyperslab are identical to
      /// calling selectStridedHyperslab, with stride values equal to 1.
      /// </p>
      /// <p>
      /// The count array determines how many blocks to select from the 
      /// dataspace, in each dimension.
      /// </p>
      /// <p>
      ///     The block array determines the size of the element block 
      /// selected from the dataspace. If the block parameter is
      /// omitted, the block size defaults to a single element in each 
      /// dimension (as if the block array were set to all 1's).
      /// </p>
      /// <p>
      /// Regions selected with this function call default to 
      /// C order iteration when I/O is performed. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static void selectHyperslab(H5DataSpaceId^ spaceId,
         H5S::SelectOperator selectOperator,
         array<hssize_t>^ start,
         array<hssize_t>^ count);

#pragma region documentation
      ///<summary>
      /// Resets the selection region to include no elements.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectNone"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of a dataspace.
      ///</param>
      ///<returns>
      /// True on sucess, false otherwise.  
      ///</returns>
      ///<remarks>
      ///</remarks>
      ///<exception cref="H5SselectNoneException">
      /// throws H5SselectNoneException on failure such as the selection
      /// or extent not being defined.
      ///</exception>
#pragma endregion documentation

      static bool selectNone(H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// Determines the dimensionality of a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-ExtentNdims"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of the dataspace
      ///</param>
      ///<returns>
      /// Returns the number of dimensions in the dataspace if
      ///successful.
      ///</returns>
      ///<remarks>
      /// H5S.getSimpleExtentNDims determines the dimensionality (or
      ///rank) of a dataspace.
      ///</remarks>
      ///<exception cref="H5SgetSimpleExtentNDimsException">
      /// throws H5SgetSimpleExtentNDimsException on failure.
      ///</exception>
#pragma endregion documentation

      static int getSimpleExtentNDims(H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// Determines the number of elements in a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-ExtentNpoints"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of the dataspace
      ///</param>
      ///<returns>
      /// Returns the number of elements in the dataspace if
      ///successful.
      ///</returns>
      ///<remarks>
      /// H5S.getSimpleExtentNPoints determines the number of elements
      /// of a dataspace.
      ///</remarks>
      ///<exception cref="H5SgetSimpleExtentNDimsException">
      /// throws H5SgetSimpleExtentNPointsException on failure.
      ///</exception>
#pragma endregion documentation

      static int getSimpleExtentNPoints(H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// H5S.getSimpleExtentMaxDims returns the maximum size of each 
      /// dimension of a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-ExtentDims"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of the dataspace
      ///</param>
      ///<returns>
      /// An array containing the maximum size of each dimension.
      ///</returns>
      ///<remarks>
      ///</remarks>
      ///<exception cref="H5SgetSimpleExtentMaxDimsException">
      /// throws H5SgetSimpleExtentMaxDimsException on failure.
      ///</exception>
#pragma endregion documentation

      static array<hssize_t>^ getSimpleExtentMaxDims(H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// H5S.getSimpleExtentDims returns the size of each 
      /// dimension of a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-ExtentDims"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of the dataspace
      ///</param>
      ///<returns>
      /// An array containing the size of each dimension.
      ///</returns>
      ///<remarks>
      ///</remarks>
      ///<exception cref="H5SgetSimpleExtentDimsException">
      /// throws H5SgetSimpleExtentDimsException on failure.
      ///</exception>
#pragma endregion documentation

      static array<hssize_t>^ getSimpleExtentDims(H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// H5S.get_simple_extent_type the current class of a dataspace.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-ExtentType"/>
      ///</summary>
      ///<param name="spaceId">
      /// Identifier of the dataspace
      ///</param>
      ///<returns>
      /// Returns a dataspace class name if successful; otherwise NO_CLASS (-1).
      ///</returns>
#pragma endregion documentation

      static H5SClass get_simple_extent_type(H5DataSpaceId^ spaceId);

      // Disallow construction of this class.
   private:
      H5S(){ };
   };

}
