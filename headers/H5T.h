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

#include "H5Array.h"
#include "HDFExceptionSubclasses.h"
#include "hvl_t.h"
#include "VLen.h"

#include "H5Lpublic.h"
#include "H5Tpublic.h"

namespace HDF5DotNet
{
   ref class H5DataSetId;
   ref class H5DataTypeId;
   ref class H5FloatingBitFields;
   ref class H5PropertyListId;

   interface class H5FileOrGroupId;
   interface class H5LocId;
   
   /// <summary>
   /// The H5T contains static member function for each of the supported
   /// H5T calls of the HDF5 library.
   /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html"/>
   /// </summary>
   public ref class H5T sealed
   {
   public:

      /// <summary>
      /// Enumeration of link types.
      /// </summary>
      enum class LinkType
      {
         /// <summary>  Error code </summary>
         ERROR = H5L_TYPE_ERROR,

         /// <summary> Hard Link </summary>
         HARD = H5L_TYPE_HARD,

         /// <summary> Soft Link </summary>
         SOFT = H5L_TYPE_SOFT,

         /// <summary> External Link </summary>
         EXTERNAL = H5L_TYPE_EXTERNAL,

         /// <summary> Maximum Link Value </summary>
         MAX = H5L_TYPE_MAX
      };

      /// <summary>
      /// Enumeration of character sets.
      /// </summary>
      enum class CharSet
      {
         /// <summary>  Error code </summary>
         ERROR = H5T_CSET_ERROR,

         /// <summary> US ASCII </summary>
         ASCII = H5T_CSET_ASCII,

         /// <summary> UTF-8 Unicode encoding </summary>
         UTF8 = H5T_CSET_UTF8
      };

      /// <summary>
      /// Enumeration of bit paddings.
      /// </summary>
      enum class BitPadding
      {
         /// <summary>  Set background to zeros. </summary>
         ZERO = H5T_PAD_ZERO,

         /// <summary> Set background to ones. </summary>
         ONE = H5T_PAD_ONE,

         /// <summary> Leave background alone. </summary>
         BACKGROUND = H5T_PAD_BACKGROUND
      };

      /// <summary>
      /// Enumeration of string paddings.
      /// </summary>
      enum class StringPadding
      {
         /// <summary>  null terminate like in C </summary>
         NULLTERM = H5T_STR_NULLTERM,

         /// <summary> pad with nulls </summary>
         NULLPAD = H5T_STR_NULLPAD,

         /// <summary> pad with spaces like in Fortran </summary>
         SPACEPAD = H5T_STR_SPACEPAD
      };

      /// <summary>
      /// Enumeration of endian (BE or LE).
      /// </summary>
      enum class Order
      {
         ///<summary> Little endian </summary>
         LE = H5T_ORDER_LE,

         ///<summary> Big endian </summary>
         BE = H5T_ORDER_BE
      };

      /// <summary>
      /// Enumeration of sign (UNSIGNED or TWOS_COMPLEMENT)
      /// </summary>
      enum class Sign
      {
         ///<summary> Unsigned number </summary>
         UNSIGNED = H5T_SGN_NONE,

         ///<summary> Two's complement  number </summary>
         TWOS_COMPLEMENT = H5T_SGN_2
      };


      /// <summary>
      /// Enumeration of Direction (DEFAULT, ASCEND, DESCEND)
      /// </summary>
      enum class Direction
      {
         ///<summary> The default direction is ascending. </summary>
         DEFAULT = H5T_DIR_DEFAULT,

         ///<summary> Ascending order </summary>
         ASCEND = H5T_DIR_ASCEND,

         ///<summary> Descending order </summary>
         DESCEND = H5T_DIR_DESCEND
      };


      /// <summary>
      /// Enumeration of data types.
      /// </summary>
      enum class H5Type
      {
         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_I8BE,

         ///<summary> 8-bit signed integer (little endian)    </summary>
         STD_I8LE,

         ///<summary> 16-bit signed integer (big endian)    </summary>
         STD_I16BE,

         ///<summary> 16-bit signed integer (little endian)    </summary>
         STD_I16LE,

         ///<summary> 32-bit signed integer (big endian)    </summary>
         STD_I32BE,

         ///<summary> 32-bit signed integer (little endian)    </summary>
         STD_I32LE,

         ///<summary> 64-bit signed integer (big endian)    </summary>
         STD_I64BE,

         ///<summary> 64-bit signed integer (little endian)    </summary>
         STD_I64LE,

         ///<summary> 8-bit unsigned integer (big endian)    </summary>
         STD_U8BE,

         ///<summary> 8-bit unsigned integer (little endian)    </summary>
         STD_U8LE,

         ///<summary> 16-bit unsigned integer (big endian)    </summary>
         STD_U16BE,

         ///<summary> 16-bit unsigned integer (little endian)    </summary>
         STD_U16LE,

         ///<summary> 32-bit unsigned integer (big endian)    </summary>
         STD_U32BE,

         ///<summary> 32-bit unsigned integer (little endian)    </summary>
         STD_U32LE,

         ///<summary> 64-bit unsigned integer (big endian)    </summary>
         STD_U64BE,

         ///<summary> 64-bit unsigned integer (little endian)    </summary>
         STD_U64LE,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_B8BE,

         ///<summary> 8-bit signed integer (little endian)    </summary>
         STD_B8LE,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_B16BE,

         ///<summary> 8-bit signed integer (little endian)    </summary>
         STD_B16LE,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_B32BE,

         ///<summary> 8-bit signed integer (little endian)    </summary>
         STD_B32LE,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_B64BE,

         ///<summary> 8-bit signed integer (little endian)    </summary>
         STD_B64LE,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_REF_OBJ,

         ///<summary> 8-bit signed integer (big endian)    </summary>
         STD_REF_DSETREG,

         /// <summary> IEEE 32-bit Floating (little endian) </summary>
         IEEE_F32LE,

         /// <summary> IEEE 32-bit Floating (big endian) </summary>
         IEEE_F32BE,

         /// <summary> IEEE 64-bit Floating (little endian) </summary> 
         IEEE_F64LE,

         /// <summary> IEEE 64-bit Floating (big endian) </summary>
         IEEE_F64BE,

         /// <summary> Single character string </summary>
         C_S1,

         /// <summary> Native signed character </summary>
         NATIVE_SCHAR,

         /// <summary> Native unsigned character </summary>
         NATIVE_UCHAR,

         /// <summary> Native signed short </summary>
         NATIVE_SHORT,

         /// <summary> Native unsigned short </summary>
         NATIVE_USHORT,

         /// <summary> Native signed int </summary>
         NATIVE_INT,

         /// <summary> Native unsigned int </summary>
         NATIVE_UINT,

         /// <summary> Native signed long </summary>
         NATIVE_LONG,

         /// <summary> Native unsigned long </summary>
         NATIVE_ULONG,

         /// <summary> Native signed long long </summary>
         NATIVE_LLONG,

         /// <summary> Native unsigned long long </summary>
         NATIVE_ULLONG,

         /// <summary> Native float </summary>
         NATIVE_FLOAT,

         /// <summary> Native double </summary>
         NATIVE_DOUBLE,

         /// <summary> Native long double </summary>
         NATIVE_LDOUBLE,

         /// <summary> Native 8-bit bitfield </summary>
         NATIVE_B8,

         /// <summary> Native 16-bit bitfield </summary>
         NATIVE_B16,

         /// <summary> Native 32-bit bitfield </summary>
         NATIVE_B32,

         /// <summary> Native 64-bit bitfield </summary>
         NATIVE_B64,

         /// <summary> Native opaque </summary>
         NATIVE_OPAQUE,

         /// <summary> Native haddr</summary>
         NATIVE_HADDR,

         /// <summary> Native hsize </summary>
         NATIVE_HSIZE,

         /// <summary> Native hssize</summary>
         NATIVE_HSSIZE,

         /// <summary> Native herr</summary>
         NATIVE_HERR,

         /// <summary> Native hbool</summary>
         NATIVE_HBOOL
      };

      /// <summary> Allowable data types for H5TCreate </summary>
      enum class CreateClass
      {
         /// <summary> Compound Data Type </summary>
         COMPOUND = H5T_COMPOUND,

         /// <summary> Opaque Data Type </summary>
         OPAQUE = H5T_OPAQUE,

         /// <summary> Enum Data Type </summary>
         ENUM = H5T_ENUM,

         /// <summary> String Data Type </summary>
         STRING = H5T_STRING
      };

      /// <summary>
      /// Enumeration of Norm (IMPLIED, MSBSET, NONE)
      /// </summary>
      enum class Norm
      {
         IMPLIED = H5T_NORM_IMPLIED,
         MSBSET = H5T_NORM_MSBSET,
         NONE = H5T_NORM_NONE
      };

      /// <summary>
      /// Enumeration of type class.
      /// </summary>
      enum class H5TClass 
      {
         /// <summary> Integer class </summary>
         INTEGER = H5T_INTEGER,

         /// <summary> Float class </summary>
         FLOAT = H5T_FLOAT,

         /// <summary> Time class </summary>
         TIME = H5T_TIME,

         /// <summary> String class (fixed or variable length) </summary>
         STRING = H5T_STRING,

         /// <summary> Bitfield class </summary>
         BITFIELD = H5T_BITFIELD,

         /// <summary> Opaque class </summary>
         OPAQUE = H5T_OPAQUE,

         /// <summary> Compound class </summary>
         COMPOUND = H5T_COMPOUND,

         /// <summary> Reference class </summary>
         REFERENCE = H5T_REFERENCE,

         /// <summary> Enum class </summary>
         ENUM = H5T_ENUM,

         /// <summary> Vlen class </summary>
         VLEN = H5T_VLEN,

         /// <summary> Array class </summary>
         ARRAY = H5T_ARRAY
      };

      

#pragma region documentation
      /// <summary> 
      /// H5T.open opens a named datatype at the location specified by
      /// groupOrFileId and returns an identifier for the datatype. 
      /// groupOrFileId is
      /// either a file or group identifier. The identifier should
      /// eventually be closed by calling H5Tclose to release resources.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html"/>
      /// </summary>
      /// <param name="groupOrFileId"> 
      /// </param>
      ///  	IN: A file or group identifier.
      /// <param name="datatypeName"> 
      ///  	IN: A datatype name, defined within the file or group
      /// identified by groupOrFileId.
      /// </param>
      /// <param name="accessPropertyList">
      ///  	IN: Datatype access property list identifier.
      /// </param>
      /// <exception cref="H5TopenException"> throws H5TopenException 
      /// when open fails
      /// </exception>
      /// <returns> a vaild H5DataTypeId for the opened data type 
      /// </returns>
#pragma endregion documentation

      static H5DataTypeId^ open(H5FileOrGroupId^ groupOrFileId,
         System::String^ datatypeName,
         H5PropertyListId^ accessPropertyList);

#pragma region documentation
      /// <summary> 
      /// H5T.open opens a named datatype at the location specified by
      /// groupOrFileId and returns an identifier for the datatype. 
      /// groupOrFileId is
      /// either a file or group identifier. The identifier should
      /// eventually be closed by calling H5Tclose to release resources.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html"/>
      /// </summary>
      /// <param name="groupOrFileId"> 
      /// </param>
      ///  	IN: A file or group identifier.
      /// <param name="datatypeName"> 
      ///  	IN: A datatype name, defined within the file or group
      /// identified by groupOrFileId.
      /// </param>
      /// <exception cref="H5TopenException"> throws H5TopenException 
      /// when open fails
      /// </exception>
      /// <returns> a vaild H5DataTypeId for the opened data type 
      /// </returns>
#pragma endregion documentation

      static H5DataTypeId^ open(H5FileOrGroupId^ groupOrFileId,
         System::String^ datatypeName);

#pragma region documentation
      /// <summary> 
      /// H5T.create creates a new data type of the specified class with
      /// the specified number of bytes.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Create"/>
      /// </summary>
      /// <param name="createClass">
      ///  Available create classes include COMPOUND, OPAQUE, ENUM, and STRING.
      /// </param>
      /// <param name="size">
      /// Number of bytes in the created data type. To create a variable-length string type
      /// specify a negative size.
      /// </param>
      /// <exception cref="H5TopenException"> throws H5TopenException 
      /// when open fails
      /// </exception>
      /// <remarks>
      /// Use H5Tcopy to create integer or floating point data types.
      /// </remarks>
      /// <returns> a vaild H5DataTypeId for the created data type 
      /// </returns>
#pragma endregion documentation

      static H5DataTypeId^ create(H5T::CreateClass createClass,
         int size);

#pragma region documentation
      /// <summary> 
      /// H5T.create_array creates an array datatype object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-ArrayCreate2"/>
      /// </summary>
      /// <param name="baseTypeId">
      /// The datatype of every element of the array.
      /// </param>
      /// <param name="dims">
      /// dims is an array specifying the size of each dimension of the array type. 
      /// </param>
      /// <returns> a vaild H5DataTypeId for the created array data type 
      /// </returns>
#pragma endregion documentation

      static H5DataTypeId^ create_array(H5DataTypeId^ baseTypeId,
         array<hssize_t>^ dims
         );


#pragma region documentation
      /// <summary>
      /// Copies an existing datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Copy"/>
      /// </summary>
      /// <param name="stdType">
      ///  Identifier of datatype to copy.
      /// </param>
      /// <returns>
      /// A data type identifier.
      /// </returns>
      /// <exception cref="H5TcopyException">
      /// throws H5copyException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataTypeId^ copy(H5T::H5Type stdType);

#pragma region documentation
      /// <summary>
      /// Copies an existing datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Copy"/>
      /// </summary>
      /// <param name="typeId">
      ///  Identifier of datatype to copy.
      /// </param>
      /// <returns>
      /// A data type identifier.
      /// </returns>
      /// <exception cref="H5TcopyException">
      /// throws H5copyException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataTypeId^ copy(H5DataTypeId^ typeId);

#pragma region documentation
      /// <summary>
      /// Copies an existing datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Copy"/>
      /// </summary>
      /// <param name="dataSetId">
      ///  Identifier of datatype to copy.
      /// </param>
      /// <returns>
      /// A data type identifier.
      /// </returns>
      /// <exception cref="H5TcopyException">
      /// throws H5copyException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataTypeId^ copy(H5DataSetId^ dataSetId);

#pragma region documentation
      /// <summary>
      /// Determines whether two datatype identifiers refer to the same datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Equal"/>
      /// </summary>
      /// <param name="typeId1">
      ///  Identifier of first datatype to compare.
      /// </param>
      /// <param name="typeId2">
      ///  Identifier of second datatype to compare.
      /// </param>
      /// <returns>
      /// When successful, return a positive value, for TRUE, if the datatype
      /// identifiers refer to the same datatype, or 0 (zero), for FALSE.
      /// Otherwise returns a negative value. 
      /// </returns>
#pragma endregion documentation

      static bool equal(H5DataTypeId^ typeId1, H5DataTypeId^ typeId2);

#pragma region documentation
      ///<summary>
      /// Sets the total size for an atomic datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-SetSize"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to change size.
      ///</param>

      ///<param name="size">
      /// IN: Size in bytes to modify datatype.
      ///</param>

      /// <returns>
      /// void
      /// </returns>
      /// <exception cref="H5TsetSizeException">
      /// throws H5TsetSizeException on failure.
      /// </exception>
#pragma endregion documentation

      static void setSize(H5DataTypeId^ typeId, int size);

#pragma region documentation
      ///<summary>
      /// Sets a datatype to variable size.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-SetSize"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to change to variable size.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TsetSizeException">
      /// throws H5TsetSizeException on failure.
      /// </exception>
#pragma endregion documentation

      static void setVariableSize(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves the bit offset of the first significant bit.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetOffset"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TgetOffsetException">
      /// throws H5TgetOffsetException on failure.
      /// </exception>
#pragma endregion documentation

      static int getOffset(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves sizes of array dimensions.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetArrayDims2"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of array datatype to query.
      ///</param>

      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static array<hssize_t>^ get_array_dims(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Returns the rank of an array datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetArrayNdims"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of array datatype to query.
      ///</param>
#pragma endregion documentation

      static int get_array_ndims(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves the character set type of a string datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetCset"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of string datatype to query.
      ///</param>

      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static CharSet get_cset(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves the padding type of the least-significant bit padding.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetPad"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static BitPadding get_lsb_pad(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves the padding type of the most-significant bit padding.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetPad"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static BitPadding get_msb_pad(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Returns the byte order of an atomic datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetOrder"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// Returns a byte order constant if successful.
      /// </returns>

      /// <exception cref="H5TgetPrecisionException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static Order get_order(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Returns the precision of an atomic datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetPrecision"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// Returns the number of significant bits if successful; otherwise 0.
      /// </returns>

      /// <exception cref="H5TgetPrecisionException">
      /// throws H5TgetPrecisionException on failure.
      /// </exception>
#pragma endregion documentation

      static int getPrecision(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves the offset of a field of a compound datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberOffset"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      ///<param name="memberNumber">
      /// IN: Number of the field whose offset is requested.
      ///</param>

      /// <returns>
      /// Returns the byte offset of the field if successful; otherwise 
      /// returns 0 (zero). Note that zero is a valid offset and that this 
      /// function will fail only if a call to H5Tget_member_class() fails 
      /// with the same arguments.
      /// </returns>

      /// <exception cref="H5TgetMemberOffsetException">
      /// throws H5TgetMemberOffsetException on failure.
      /// </exception>
#pragma endregion documentation

      static int getMemberOffset(H5DataTypeId^ typeId, 
         int memberNumber);

#pragma region documentation
      ///<summary>
      /// Determines whether datatype is a variable-length string.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-IsVariableString"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// true if data type is variable string.
      /// </returns>

      /// <exception cref="H5TisVariableStringException">
      /// throws H5TisVariableStringException on failure.
      /// </exception>
#pragma endregion documentation

      static bool isVariableString(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Releases a datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Close"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to release.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TcloseException">
      /// throws H5TcloseException on failure.
      /// </exception>
#pragma endregion documentation

      static void close(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Sets the byte ordering of an atomic datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-SetOrder"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to set.
      ///</param>

      ///<param name="order">
      /// IN: Byte ordering constant.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TsetOrderException">
      /// throws H5TsetOrderException on failure.
      /// </exception>
#pragma endregion documentation

      static void setOrder(H5DataTypeId^ typeId, 
         H5T::Order order);

#pragma region documentation
      /// <summary> 
      /// getSize returns the size of a datatype in bytes.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetSize"/>
      /// </summary>
      /// <param name="typeId"> 
      ///  	IN: Identifier of datatype to query.
      /// </param>
      /// <exception cref="H5TgetSizeException"> 
      /// throws H5TgetSizeException on failure.
      /// </exception>
      /// <returns> 
      /// Returns the size of the datatype in bytes if successful.
      /// </returns>
#pragma endregion documentation

      static int getSize(H5DataTypeId^ typeId);
      static int getSize(H5T::H5Type h5Type);

#pragma region documentation
      /// <summary>
      /// Retrieves the sign type for an integer type.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetSign"/>
      /// </summary>
      /// <param name="typeId"> 
      ///  	IN: Identifier of datatype to query.
      /// </param>
      /// <exception cref="H5TgetSizeException"> 
      /// throws H5TgetSignException on failure.
      /// </exception>
      /// <returns> 
      /// Returns an H5T.Sign that indicates the sign.  Possible results
      /// include H5T.Sign.UNSIGNED and H5T.Sign.TWOS_COMPLEMENT
      /// </returns>
#pragma endregion documentation

      static H5T::Sign getSign(H5DataTypeId^ typeId);
      static H5T::Sign getSign(H5T::H5Type h5Type);

#pragma region documentation
      /// <summary>
      /// H5T.enumCreate creates a new enumeration datatype based on the
      /// specified base datatype parent_id, which must be an integer type.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-EnumCreate"/>
      /// </summary>
      /// <param name="parentId"> IN: Datatype identifier for the 
      /// base type. This must be an integer type.
      /// </param>
      /// <returns>
      /// Returns the datatype identifier for the new enumeration
      /// datatype if successful.
      /// </returns>
      /// <exception cref="H5TenumCreateException">
      /// throws H5TenumCreateException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataTypeId^ enumCreate(H5DataTypeId^ parentId);

#pragma region documentation
      /// <summary>
      /// H5T.enumCreate creates a new enumeration datatype based on the
      /// specified base datatype parent_id, which must be an integer type.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-EnumCreate"/>
      /// </summary>
      /// <param name="h5Type"> IN: Datatype identifier for the 
      /// base type.
      /// </param>
      /// <returns>
      /// Returns the datatype identifier for the new enumeration
      /// datatype if successful.
      /// </returns>
      /// <exception cref="H5TenumCreateException">
      /// throws H5TenumCreateException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataTypeId^ enumCreate(H5T::H5Type h5Type);

#pragma region documentation
      /// <summary>
      /// <c>H5Tinsert</c> adds another member to the compound datatype
      /// <c>type_id.</c> The new member has a name which must be unique within
      /// the compound datatype. The <c>offset</c> argument defines the start
      /// of the member in an instance of the compound datatype, and
      /// <c>field_id</c> is the datatype identifier of the new member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Insert"/>
      /// </summary>
      /// <param name="compoundDataType"> Identifier of compound data
      /// type to modify.
      /// </param>
      /// <param name="fieldName">
      /// Name of the field to insert.
      /// </param>
      /// <param name="offset">
      /// Offset in memory structure of the field to insert.
      /// </param>
      /// <param name="fieldId">
      /// Datatype identifier of the field to insert.
      /// </param>
      /// <exception cref="H5TinsertException">
      /// throws H5TinsertException on failure.
      /// </exception>
      /// <remarks>
      /// Members of a compound datatype do not have to be atomic
      /// datatypes; a compound datatype can have a member which is a
      /// compound datatype.
      /// </remarks>
#pragma endregion documentation

      static void insert(H5DataTypeId^ compoundDataType,
         System::String^ fieldName, 
         int offset,
         H5DataTypeId^ fieldId);

#pragma region documentation
      /// <summary>
      /// H5Tinsert adds another member to the compound datatype
      /// type_id. The new member has a name which must be unique within
      /// the compound datatype. The offset argument defines the start
      /// of the member in an instance of the compound datatype, and
      /// field_id is the datatype identifier of the new member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Insert"/>
      /// </summary>
      /// <param name="compoundDataType"> Identifier of compound data
      /// type to modify.
      /// </param>
      /// <param name="fieldName">
      /// Name of the field to insert.
      /// </param>
      /// <param name="offset">
      /// Offset in memory structure of the field to insert.
      /// </param>
      /// <param name="fieldId">
      /// Datatype identifier of the field to insert.
      /// </param>
      /// <exception cref="H5TinsertException">
      /// throws H5TinsertException on failure.
      /// </exception>
      /// <remarks>
      /// Members of a compound datatype do not have to be atomic
      /// datatypes; a compound datatype can have a member which is a
      /// compound datatype.
      /// </remarks>
#pragma endregion documentation

      static void insert(H5DataTypeId^ compoundDataType,
         System::String^ fieldName, 
         int offset,
         H5T::H5Type fieldId);

#pragma region documentation
      /// <summary>
      /// Returns the native datatype of a specified datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetNativeType"/>
      /// </summary>
      /// <param name="typeId"> 
      /// Datatype identifier for the dataset datatype.
      /// </param>
      /// <param name="direction">
      /// Direction of search.
      /// </param>
      /// <exception cref="H5TgetNativeTypeException">
      /// throws H5TgetNativeTypeException on failure.
      /// </exception>
      /// <remarks>
      ///<p>
      /// H5Tget_native_type returns the equivalent native datatype for
      /// the datatype specified in type_id.
      /// </p>
      /// <p> H5Tget_native_type is a high-level function designed 
      /// primarily to facilitate use of the H5Dread function, for which 
      /// users otherwise must undertake a multi-step process to determine 
      /// the native datatype of a dataset prior to reading it into memory. 
      /// It can be used not only to determine the native datatype for 
      /// atomic datatypes, but also to determine the native datatypes 
      /// of the individual components of a compound datatype, an 
      /// enumerated datatype, an array datatype, or a variable-length 
      /// datatype. </p>
      /// <p>
      /// H5Tget_native_type selects the matching native datatype from
      /// the following list:
      /// </p>
      /// <ul>
      /// <li>   H5T_NATIVE_CHAR   </li>
      /// <li>   H5T_NATIVE_SHORT        </li>
      /// <li>   H5T_NATIVE_INT          </li>
      /// <li>   H5T_NATIVE_LONG         </li>
      /// <li>   H5T_NATIVE_LLONG        </li>
      /// <li>   H5T_NATIVE_UCHAR </li>
      /// <li>   H5T_NATIVE_USHORT </li>
      /// <li>   H5T_NATIVE_UINT </li>
      /// <li>   H5T_NATIVE_ULONG </li>
      /// <li>   H5T_NATIVE_ULLONG </li>
      /// <li>   H5T_NATIVE_FLOAT </li>
      /// <li>   H5T_NATIVE_DOUBLE </li>
      /// <li>   H5T_NATIVE_LDOUBLE </li>
      /// </ul>
      ///<p>
      ///The direction parameter indicates the order in which the
      ///library searches for a native datatype match. Valid values for 
      /// direction are as follows:
      /// </p>
      /// <ul>
      /// <li>
      /// H5T_DIR_ASCEND searches the above list in ascending size of
      /// the datatype, i.e., from top to bottom. (Default) 
      /// </li>
      /// <li>
      /// H5T_DIR_DESCEND searches the above list in descending size of 
      /// the datatype, i.e., from bottom to top.
      /// </li>
      /// </ul>
      /// <p>
      /// H5Tget_native_type is designed primarily for use with intenger
      /// and floating point datatypes. Time, bifield, opaque, and 
      /// reference datatypes are returned as a copy of type_id.
      /// </p>
      /// <p>
      /// The identifier returned by H5Tget_native_type should
      /// eventually be closed by calling H5Tclose to release resources. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static H5DataTypeId^ getNativeType(H5DataTypeId^ typeId,
         H5T::Direction direction);

      static H5DataTypeId^ getNativeType(H5T::H5Type h5Type,
         H5T::Direction direction);

#pragma region documentation
      /// <summary>
      /// Returns the base datatype from which a datatype is derived.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetSuper"/>
      /// </summary>
      /// <param name="typeId"> 
      /// Datatype identifier of the derived datatype.
      /// </param>
#pragma endregion documentation

      static H5DataTypeId^ get_super(H5DataTypeId^ typeId);

#pragma region documentation
      /// <summary>
      /// Creates a new variable-length datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-VLCreate"/>
      /// </summary>
      /// <param name="baseId"> Base type of datatype to create.
      /// </param>
      /// <exception cref="H5TvlenCreateException">
      /// throws H5TvlenCreateException on failure.
      /// </exception>
      /// <remarks>
      /// <p>
      /// H5Tvlen_create creates a new variable-length (VL) datatype.
      /// </p>
      /// <p>
      ///    The base datatype will be the datatype that the sequence 
      /// is composed of, characters for character strings, vertex 
      /// coordinates for polygon lists, etc. The base type specified 
      /// for the VL datatype can be of any HDF5 datatype, including 
      /// another VL datatype, a compound datatype or an atomic datatype.
      /// </p>
      /// <p>
      /// When necessary, use H5Tget_super to determine the base type of
      /// the VL datatype.
      /// </p>
      /// <p>
      /// The datatype identifier returned from this function 
      /// should be released with H5Tclose or resource leaks will result. 
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static H5DataTypeId^ vlenCreate(H5DataTypeId^ baseId);

      static H5DataTypeId^ vlenCreate(H5T::H5Type h5Type);

#pragma region documentation
      /// <summary>
      /// Returns the datatype class identifier.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetClass"/>
      /// </summary>
      /// <param name="typeId"> Identifier of datatype to query.
      /// </param>
      /// <remarks>
      /// <p>
      ///H5Tget_class returns the datatype class identifier.
      /// </p>
      /// <p>
      /// Valid class identifiers, as defined in H5Tpublic.h, are:  
      /// </p>
      /// <ul>
      /// <li> H5T_INTEGER </li>
      /// <li> H5T_FLOAT </li>
      /// <li> H5T_TIME </li>
      /// <li> H5T_STRING </li>
      /// <li> H5T_BITFIELD </li>
      /// <li> H5T_OPAQUE </li>
      /// <li> H5T_COMPOUND </li>
      /// <li> H5T_REFERENCE </li>
      /// <li> H5T_ENUM </li>
      /// <li> H5T_VLEN </li>
      /// <li> H5T_ARRAY  </li>
      /// </ul> 
      /// </remarks>
      /// <exception cref="H5TgetClassException">
      /// throws H5TgetClassException on failure.
      /// </exception>
#pragma endregion documentation

      static H5TClass getClass(H5DataTypeId^ typeId);
      static H5TClass getClass(H5T::H5Type h5Type);

#pragma region documentation
      /// <summary>
      /// Retrieves the index of a compound or enumeration datatype
      /// member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberIndex"/>
      /// </summary>
      /// <param name="typeId"> 
      /// Identifier of datatype to query.
      /// </param>
      /// <returns>
      /// Returns a valid field or member index if successful.
      /// </returns>
      /// <exception cref="H5TgetMemberIndexException">
      /// throws H5TgetMemberIndexException on failure.
      /// </exception>
      /// <remarks>
      /// <p>
      /// H5Tget_member_index retrieves the index of a field of a 
      /// compound datatype or an element of an enumeration datatype.
      /// </p>
      /// <p>
      /// The name of the target field or element is specified in fieldname.
      /// </p>
      /// <p>
      /// Fields are stored in no particular order with index values 
      /// of 0 through N-1, where N is the value returned by 
      /// H5T.getNMembers.  
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static int getMemberIndex(H5DataTypeId^ typeId,
         System::String^ fieldName);

#pragma region documentation
      /// <summary>
      /// Returns the datatype of the specified member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberType"/>
      /// </summary>
      /// <param name="typeId"> 
      /// Identifier of datatype to query.
      /// </param>
      /// <param name="fieldIndex"> 
      /// Field index (0-based) of the field type to retrieve.
      /// </param>
      /// <returns>
      /// Returns the identifier of a copy of the datatype of the field
      /// if successful.
      /// </returns>
      /// <exception cref="H5TgetMemberTypeException">
      /// throws H5TgetMemberTypeException on failure.
      /// </exception>
      /// <remarks>
      /// H5Tget_member_type returns the datatype of the specified
      /// member. The caller should invoke H5Tclose() to release
      /// resources associated with the type.
      /// </remarks>
#pragma endregion documentation

      static H5DataTypeId^ getMemberType(H5DataTypeId^ typeId,
         int fieldIndex);

#pragma region documentation
      /// <summary>
      /// Retrieves the number of elements in a compound or enumeration 
      /// datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetNmembers"/>
      /// </summary>
      /// <param name="typeId"> 
      /// Identifier of datatype to query.
      /// </param>
      /// <returns>
      /// Returns the number of elements if successful.
      /// </returns>
      /// <exception cref="H5TgetNMembersException">
      /// throws H5TgetNMembersException on failure.
      /// </exception>
      /// <remarks>
      /// H5Tget_nmembers retrieves the number of fields in a compound
      /// datatype or the number of members of an enumeration datatype.
      /// </remarks>
#pragma endregion documentation

      static int getNMembers(H5DataTypeId^ typeId);

#pragma region documentation
      /// <summary>
      /// Returns datatype class of compound datatype member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberClass"/>
      /// </summary>
      /// <param name="typeId"> 
      /// IN: Datatype identifier of compound object.
      /// </param>
      /// <param name="memberNumber"> 
      /// IN: Compound object member number.
      /// </param>
      /// <returns>
      /// Returns the datatype class if successful.
      /// </returns>
      /// <exception cref="H5TgetMemberClassException">
      /// throws H5TgetMemberClassException on failure.
      /// </exception>
      /// <remarks>
      /// <p>
      /// Given a compound datatype, typeId, the function 
      /// H5T.getMemberClass returns the datatype class of the compound
      /// datatype member specified by memberNumber.
      /// </p>
      /// </remarks>
#pragma endregion documentation

      static H5TClass getMemberClass(H5DataTypeId^ typeId, 
         int memberNumber);

#pragma region documentation
      /// <summary>
      /// Retrieves the name of a compound or enumeration datatype member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberName"/>
      /// </summary>
      /// <param name="typeId"> 
      /// IN: Datatype identifier of compound object.
      /// </param>
#pragma endregion documentation

      static System::String^ getMemberName(H5DataTypeId^ typeId,
         int fieldIndex);

#pragma region documentation
      ///<summary>
      /// Retrieves mantissa normalization of a floating-point datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetNorm"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// Returns a valid normalization type.
      /// </returns>
      /// <exception cref="H5TgetNormException">
      /// throws H5TgetNormException on failure.
      /// </exception>
#pragma endregion documentation

      static Norm getNorm(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Retrieves floating point datatype bit field information.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetFields"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Identifier of datatype to query.
      ///</param>

      /// <returns>
      /// Returns an instance of H5FloatingBitFields, which contains
      /// all the bit field information.
      /// </returns>
      /// <exception cref="H5TgetFieldsException">
      /// throws H5TgetFieldsException on failure.
      /// </exception>
#pragma endregion documentation

      static H5FloatingBitFields^ getFields(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Commits a transient datatype, linking it into the file and 
      /// creating a new named datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Commit"/>
      ///</summary>

      ///<param name="location">
      /// IN: Location identifier
      ///</param>

      ///<param name="dataTypeName">
      /// IN: Name given to committed datatype
      ///</param>

      ///<param name="typeId">
      /// IN: Identifier of datatype to be committed
      ///</param>

      /// <returns>
      /// void
      /// </returns>
      /// <exception cref="H5TcommitException">
      /// throws H5TcommitException on failure.
      /// </exception>
#pragma endregion documentation

      static void commit(H5LocId^ location, 
         System::String^ dataTypeName,
         H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Commits a transient datatype, linking it into the file and 
      /// creating a new named datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Commit"/>
      ///</summary>

      ///<param name="location">
      /// IN: Location identifier
      ///</param>

      ///<param name="dataTypeName">
      /// IN: Name given to committed datatype
      ///</param>

      ///<param name="typeId">
      /// IN: Identifier of datatype to be committed
      ///</param>

      ///<param name="linkCreationPropertyList">
      /// IN: Link creation property list
      ///</param>

      ///<param name="dataTypeCreationPropertyList">
      /// IN: Datatype creation property list
      ///</param>

      ///<param name="dataTypeAccessPropertyList">
      /// IN: Datatype access property list
      ///</param>

      /// <returns>
      /// void
      /// </returns>
      /// <exception cref="H5TcommitException">
      /// throws H5TcommitException on failure.
      /// </exception>
#pragma endregion documentation

      static void commit(H5LocId^ location, 
         System::String^ dataTypeName,
         H5DataTypeId^ typeId,
         H5PropertyListId^ linkCreationPropertyList,
         H5PropertyListId^ dataTypeCreationPropertyList,
         H5PropertyListId^ dataTypeAccessPropertyList);

#pragma region documentation
      ///<summary>
      /// Determines whether a datatype is a named type or a transient type.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Committed"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Datatype identifier.
      ///</param>

      /// <returns>
      /// bool
      /// </returns>

      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static bool committed(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Returns the value of an enumeration datatype member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetMemberValue"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Datatype identifier for the enumeration datatype.
      ///</param>

      ///<param name="memberNumber">
      /// IN: Number of the enumeration datatype member.
      ///</param>

      ///<param name="value">
      /// OUT: Reference to hold output of the value of the enumeration 
      /// datatype member.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TgetMemberValueException">
      /// throws H5TgetMemberValueException on failure.
      /// </exception>
#pragma endregion documentation

      generic <class Type>
      static void getMemberValue(H5DataTypeId^ typeId,
         int memberNumber,
         [System::Runtime::InteropServices::Out] Type% value);

#pragma region documentation
      ///<summary>
      /// Returns the value corresponding to a specified member of an 
      /// enumeration datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-EnumValueOf"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Enumeration datatype identifier.
      ///</param>

      ///<param name="enumName">
      /// IN: Symbol name of the enumeration datatype.
      ///</param>

      ///<param name="value">
      /// OUT: Reference for output of the value of the enumeration datatype.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5TenumValueOfException">
      /// throws H5TenumValueOfException on failure.
      /// </exception>
#pragma endregion documentation

      generic <class Type>
      static void enumValueOf(H5DataTypeId^ typeId,
         System::String^ enumName,
         [System::Runtime::InteropServices::Out] Type% value);

#pragma region documentation
      ///<summary>
      /// Returns the symbol name corresponding to a specified member of an 
      /// enumeration datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-EnumNameOf"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Enumeration datatype identifier.
      ///</param>

      ///<param name="value">
      /// In: Value of the enumeration datatype.
      ///</param>

      /// <returns>
      ///  String containing symbolic name for the specified value.
      /// </returns>

      /// <exception cref="H5TenumNameOfException">
      /// throws H5TenumNameOfException on failure.
      /// </exception>
#pragma endregion documentation

      generic <class Type>
      static System::String^ enumNameOf(H5DataTypeId^ typeId,
         Type% value);

#pragma region documentation
      ///<summary>
      /// Inserts a new enumeration datatype member.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-EnumInsert"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: Enumeration datatype identifier.
      ///</param>

      ///<param name="value">
      /// In: Value of the enumeration datatype.
      ///</param>

      /// <returns>
      ///  void
      /// </returns>

      /// <exception cref="H5TenumInsertException">
      /// throws H5TenumInsertException on failure.
      /// </exception>
#pragma endregion documentation

      generic <class Type>
      static void enumInsert(H5DataTypeId^ typeId,
         System::String^ name,
         Type% value);

#pragma region documentation
      ///<summary>
      /// Retrieves the string padding for a string datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetStrpad"/>
      ///</summary>

      ///<param name="typeId">
      /// IN: String datatype identifier.
      ///</param>
      
      /// <returns cref="StringPadding">
      ///  StringPadding
      /// </returns>
      
      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static StringPadding get_strpad(H5DataTypeId^ typeId);

#pragma region documentation
      ///<summary>
      /// Defines the storage mechanism for character strings.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-SetStrpad"/>
      ///</summary>
      ///<param name="typeId">
      /// IN: String datatype identifier.
      ///</param>
      ///<param name="pad">
      /// In: String padding.
      ///</param>
      /// <returns>
      ///  void
      /// </returns>
      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static void setStrPad(H5DataTypeId^ typeId,
          StringPadding pad);

#pragma region documentation
      ///<summary>
      /// Gets the tag associated with an opaque datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-GetTag"/>
      ///</summary>
      ///<param name="typeId">
      /// IN: Opaque datatype identifier.
      ///</param>
      /// <returns>
      ///  String
      /// </returns>
      /// <exception cref="HDFException">
      /// throws HDFException on failure.
      /// </exception>
#pragma endregion documentation

      static System::String^ get_tag(H5DataTypeId^ typeId);

   internal:
      ///<summary>
      ///  Get the hid_t from the enumerated standard data type.
      ///</summary>
      static hid_t getStdType(H5T::H5Type stdType);

   private:
      // Disallow the creation of instances of this class.
      H5T() { };
   };
}
