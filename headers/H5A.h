/* * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Copyright by The HDF Group (THG).*
* All rights reserved. *
**
* This file is part of HDF5. The full HDF5 copyright notice, including*
* terms governing use, modification, and redistribution, is contained in*
* the files COPYING and Copyright.html. COPYING can be found at the root*
* of the source code distribution tree; Copyright.html can be found at the*
* root level of an installed copy of the electronic HDF5 document set and*
* is linked from the top-level documents page. It can also be found at*
* http://www.hdfgroup.org/HDF5/doc/Copyright.html. If you do not have*
* access to either file, you may request a copy from help@hdfgroup.org.*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "H5AIterateCallback.h"
#include "H5AttributeInfo.h"
#include "H5IndexType.h"
#include "H5IterationOrder.h"
#include "H5ObjectWithAttributes.h"

#include "H5Apublic.h"

namespace HDF5DotNet
{
    ref class H5DataSpaceId;
    ref class H5DataTypeId;
    ref class H5PropertyListId;

   /// <summary>
   /// The H5A class contains static member function for each of the supported
   /// H5A calls of the HDF5 library.
   /// The purpose of these calls is to create and manipulate attributes and 
   /// information about attributes.
   /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html"/>
   /// </summary>
   public ref class H5A sealed
   {
   public:

#pragma region documentation
      ///<summary>
      /// Creates an attribute attached to a specified object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Create"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Location or object identifier; may be dataset or group
      ///</param>

      ///<param name="attributeName">
      /// IN: Attribute name
      ///</param>

      ///<param name="typeId">
      /// IN: Attribute datatype identifier
      ///</param>

      ///<param name="spaceId">
      /// IN: Attribute dataspace identifier
      ///</param>

      /// <returns>
      /// H5AttributeId for the created attribute.
      /// </returns>
      /// <exception cref="H5AcreateException">
      /// throws H5AcreateException on failure.
      /// </exception>
#pragma endregion documentation

	   static H5AttributeId^ create(H5ObjectWithAttributes^ objectId, 
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId);

#pragma region documentation
      ///<summary>
      /// Creates an attribute attached to a specified object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Create"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Location or object identifier; may be dataset or group
      ///</param>

      ///<param name="attributeName">
      /// IN: Attribute name
      ///</param>

      ///<param name="typeId">
      /// IN: Attribute datatype identifier
      ///</param>

      ///<param name="spaceId">
      /// IN: Attribute dataspace identifier
      ///</param>

      ///<param name="creationPropertyListId">
      /// IN: Attribute creation property list identifier
      ///</param>

      /// <returns>
      /// H5AttributeId for the created attribute.
      /// </returns>
      /// <exception cref="H5AcreateException">
      /// throws H5AcreateException on failure.
      /// </exception>
#pragma endregion documentation

	   static H5AttributeId^ create(H5ObjectWithAttributes^ objectId, 
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId,
         H5PropertyListId^ creationPropertyListId);

#pragma region documentation
      ///<summary>
      /// Creates an attribute attached to a specified object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Create"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Location or object identifier; may be dataset or group
      ///</param>

      ///<param name="attributeName">
      /// IN: Attribute name
      ///</param>

      ///<param name="typeId">
      /// IN: Attribute datatype identifier
      ///</param>

      ///<param name="spaceId">
      /// IN: Attribute dataspace identifier
      ///</param>

      ///<param name="creationPropertyListId">
      /// IN: Attribute creation property list identifier
      ///</param>

      ///<param name="accessPropertyListId">
      /// IN: Attribute access property list identifier
      ///</param>

      /// <returns>
      /// H5AttributeId for the created attribute.
      /// </returns>
      /// <exception cref="H5AcreateException">
      /// throws H5AcreateException on failure.
      /// </exception>
#pragma endregion documentation

	   static H5AttributeId^ create(H5ObjectWithAttributes^ objectId, 
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId,
         H5PropertyListId^ creationPropertyListId,
         H5PropertyListId^ accessPropertyListId);

#pragma region documentation
      ///<summary>
      /// Creates an attribute attached to a specified object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Create"/>
      ///</summary>

      ///<param name="object">
      /// IN: Location or object identifier; may be dataset or group
      ///</param>

      ///<param name="objectName">
      /// IN: Name, relative to loc_id, of object that attribute is to 
      /// be attached to
      ///</param>

      ///<param name="attributeName">
      /// IN: Attribute name
      ///</param>

      ///<param name="typeId">
      /// IN: Attribute datatype identifier
      ///</param>

      ///<param name="spaceId">
      /// IN: Attribute dataspace identifier
      ///</param>

      ///<param name="attributeCreationProperties">
      /// IN: Attribute creation property list identifier
      /// -- Currently not used.
      ///</param>

      ///<param name="attributePermissionsProperties">
      /// IN: Attribute access property list identifier
      /// -- Currently not used.
      ///</param>

      ///<param name="linkAccessProperties">
      /// IN: Link access property list
      ///</param>

      /// <returns>
      /// H5AttributeId associated with the created attribute.
      /// </returns>
      /// <exception cref="H5AcreateByNameException">
      /// throws H5AcreateByNameException on failure.
      /// </exception>
#pragma endregion documentation

	   static H5AttributeId^ createByName(
         H5ObjectWithAttributes^ object, 
         System::String^ objectName,
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId,
         H5PropertyListId^ attributeCreationProperties,
         H5PropertyListId^ attributePermissionsProperties,
         H5PropertyListId^ linkAccessProperties);

#pragma region documentation
      ///<summary>
      /// Creates an attribute attached to a specified object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-CreateByName"/>
      ///</summary>

      ///<param name="object">
      /// IN: Location or object identifier; may be dataset or group
      ///</param>

      ///<param name="objectName">
      /// IN: Name, relative to loc_id, of object that attribute is to 
      /// be attached to
      ///</param>

      ///<param name="attributeName">
      /// IN: Attribute name
      ///</param>

      ///<param name="typeId">
      /// IN: Attribute datatype identifier
      ///</param>

      ///<param name="spaceId">
      /// IN: Attribute dataspace identifier
      ///</param>

      /// <returns>
      /// H5AttributeId associated with the created attribute.
      /// </returns>
      /// <exception cref="H5AcreateByNameException">
      /// throws H5AcreateByNameException on failure.
      /// </exception>
#pragma endregion documentation

	   static H5AttributeId^ createByName(
         H5ObjectWithAttributes^ object, 
         System::String^ objectName,
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId);

#pragma region documentation
        ///<summary>
        /// Opens an attribute for an object by object name and attribute name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location from which to find object to which attribute is 
        /// attached
        ///</param>

        ///<param name="objectName">
        /// IN: Name of object to which attribute is attached, relative to 
        /// loc_id
        ///</param>

        ///<param name="attributeName">
        /// IN: Name of attribute to open
        ///</param>

        /// <returns>
        /// Returns an attribute identifier 
        /// </returns>
        /// <exception cref="H5AopenByNameException">
        /// throws H5AopenByNameException on failure.
        /// </exception>
#pragma endregion documentation

      static H5AttributeId^ openByName(
         H5ObjectWithAttributes^ objectId,
         System::String^ objectName,
         System::String^ attributeName);

#pragma region documentation
        ///<summary>
        /// Opens an attribute for an object by object name and attribute name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location from which to find object to which attribute is 
        /// attached
        ///</param>

        ///<param name="objectName">
        /// IN: Name of object to which attribute is attached, relative to 
        /// loc_id
        ///</param>

        ///<param name="attributeName">
        /// IN: Name of attribute to open
        ///</param>

        ///<param name="attributeAccessPropertyListId">
        /// IN: Attribute access property list
        ///</param>

        ///<param name="linkAccessPropertyListId">
        /// IN: Link access property list
        ///</param>

        /// <returns>
        /// Returns an attribute identifier 
        /// </returns>
        /// <exception cref="H5AopenByNameException">
        /// throws H5AopenByNameException on failure.
        /// </exception>
#pragma endregion documentation
      
	  static H5AttributeId^ openByName(
         H5ObjectWithAttributes^ objectId,
         System::String^ objectName,
         System::String^ attributeName,
         H5PropertyListId^ attributeAccessPropertyListId,
         H5PropertyListId^ linkAccessPropertyListId);

#pragma region documentation
      ///<summary>
      /// Writes data to an attribute.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Write"/>
      ///</summary>

      ///<param name="attributeId">
      /// IN: Identifier of an attribute to write.
      ///</param>

      ///<param name="memTypeId">
      /// IN: Identifier of the attribute datatype (in memory).
      ///</param>

      ///<param name="buffer">
      /// IN: Data to be written.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5AwriteException">
      /// throws H5AwriteException on failure.
      /// </exception>
#pragma endregion documentation     

	  generic <class Type>
      static void write(
         H5AttributeId^ attributeId,
         H5DataTypeId^ memTypeId,
         H5Array<Type>^ buffer);

#pragma region documentation
      ///<summary>
      /// Reads an attribute.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Read"/>
      ///</summary>

      ///<param name="attributeId">
      /// IN: Identifier of an attribute to write.
      ///</param>

      ///<param name="memTypeId">
      /// IN: Identifier of the attribute datatype (in memory).
      ///</param>

      ///<param name="buffer">
      /// IN: Data to be written.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5AreadException">
      /// throws H5AreadException on failure.
      /// </exception>
#pragma endregion documentation

	  generic <class Type>
      static void read(
         H5AttributeId^ attributeId,
         H5DataTypeId^ memTypeId,
         H5Array<Type>^ buffer);

#pragma region documentation
        ///<summary>
        /// Opens an attribute specified by name.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenName"/>
        ///</summary>
        /// <note>Function deprecated in HDF5 1.8</note>
        ///<param name="objectId">
        /// IN: Identifier of a group, dataset, or named datatype that 
        /// attribute is attached to.
        ///</param>

        ///<param name="name">
        /// IN: Attribute name.
        ///</param>

        /// <returns>
        /// Returns attribute identifier 
        /// </returns>
        /// <exception cref="H5AopenNameException">
        /// throws H5AopenNameException on failure.
        /// </exception>
#pragma endregion documentation

      static H5AttributeId^ openName(H5ObjectWithAttributes^ objectId, 
         System::String^ name);

#pragma region documentation
        ///<summary>
        /// Opens the attribute specified by its index. (deprecated in 1.8)
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenIdx"/>
        ///</summary>
        /// <note>Function deprecated in HDF5 1.8</note>
        ///<param name="objectId">
        /// IN: Identifier of the group, dataset, or named datatype attribute 
        /// to be attached to.
        ///</param>
        ///<param name="index">
        /// IN: Index of the attribute to open.
        ///</param>
        /// <returns>
        /// Returns attribute identifier
        /// </returns>
        /// <exception cref="H5AopenIndexException">
        /// throws H5AopenIndexException on failure.
        /// </exception>
#pragma endregion documentation

      static H5AttributeId^ openIndex(H5ObjectWithAttributes^ objectId, 
         int index);

	  [System::CLSCompliant(false)]
	  static H5AttributeId^ openIndex(H5ObjectWithAttributes^ objectId, 
		  unsigned int index);

#pragma region documentation
      ///<summary>
      /// Gets an attribute datatype.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetType"/>
      ///</summary>

      ///<param name="attributeId">
      /// IN: Identifier of an attribute.
      ///</param>

      /// <returns>
      /// H5DataTypeId
      /// </returns>

      /// <exception cref="H5AgetTypeException">
      /// throws H5AgetTypeException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5DataTypeId^ getType(H5AttributeId^ attributeId);

#pragma region documentation
      ///<summary>
      /// Determines the number of attributes attached to an object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-NumAttrs"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Identifier of a group, dataset, or named datatype.
      ///</param>

      /// <returns>
      /// Returns the number of attributes.
      /// </returns>
      /// <exception cref="H5AgetNumberOfAttributesException">
      /// throws H5AgetNumberOfAttributesException on failure.
      /// </exception>
#pragma endregion documentation

      static int getNumberOfAttributes(H5ObjectWithAttributes^ objectId);

#pragma region documentation
      ///<summary>
      /// Closes the specified attribute.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Close"/>
      ///</summary>

      ///<param name="id">
      /// IN: Attribute to release access to.
      ///</param>

      /// <returns>
      /// void
      /// </returns>
      /// <exception cref="H5AcloseException">
      /// throws H5AcloseException on failure.
      /// </exception>
#pragma endregion documentation

      static void close(H5AttributeId^ id);

#pragma region documentation
      ///<summary>
      /// Deletes an attribute from a specified location.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Delete"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Identifier of the dataset, group, or named datatype to 
      /// have the attribute deleted from.
      ///</param>

      ///<param name="attributeName">
      /// IN: Name of the attribute to delete.
      ///</param>

      /// <returns>
      /// void
      /// </returns>

      /// <exception cref="H5ADeleteException">
      /// throws H5ADeleteException on failure.
      /// </exception>
#pragma endregion documentation

      static void Delete(H5ObjectWithAttributes^ objectId,
         System::String^ attributeName);

#pragma region documentation
        ///<summary>
        /// Removes an attribute from a specified location.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-DeleteByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location or object identifier; may be dataset or group
        ///</param>

        ///<param name="objectName">
        /// IN: Name of object, relative to location, from which attribute is 
        /// to be removed
        ///</param>

        ///<param name="attributeName">
        /// IN: Name of attribute to delete
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5AdeleteByNameException">
        /// throws H5AdeleteByNameException on failure.
        /// </exception>
#pragma endregion documentation

      static void DeleteByName(H5ObjectWithAttributes^ objectId, 
         System::String^ objectName,
         System::String^ attributeName);

#pragma region documentation
        ///<summary>
        /// Removes an attribute from a specified location.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-DeleteByName"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location or object identifier; may be dataset or group
        ///</param>

        ///<param name="objectName">
        /// IN: Name of object, relative to location, from which attribute is 
        /// to be removed
        ///</param>

        ///<param name="attributeName">
        /// IN: Name of attribute to delete
        ///</param>

        ///<param name="linkAccessPropertyListId">
        /// IN: Link access property list
        ///</param>

        /// <returns>
        /// void
        /// </returns>
        /// <exception cref="H5AdeleteByNameException">
        /// throws H5AdeleteByNameException on failure.
        /// </exception>
#pragma endregion documentation

	  static void DeleteByName(H5ObjectWithAttributes^ objectId, 
         System::String^ objectName,
         System::String^ attributeName,
         H5PropertyListId^ linkAccessPropertyListId);

#pragma region documentation
      ///<summary>
      /// Gets an attribute name.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetName"/>
      ///</summary>

      ///<param name="attributeId">
      /// IN: Identifier of the attribute.
      ///</param>

      /// <returns>
      /// A string containing the attribute name.
      /// </returns>

      /// <exception cref="H5AgetNameException">
      /// throws H5AgetNameException on failure.
      /// </exception>
#pragma endregion documentation

      static System::String^ getName(H5AttributeId^ attributeId);

#pragma region documentation
        ///<summary>
        /// Gets an attribute name, by attribute index position
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetNameByIdx"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location of object to which attribute is attached
        ///</param>

        ///<param name="objName">
        /// IN: Name of object to which attribute is attached, relative to 
        /// location
        ///</param>

        ///<param name="indexType">
        /// IN: Type of index
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Index traversal order
        ///</param>

        ///<param name="position">
        /// IN: Attribute's position in index
        ///</param>

        /// <returns>
        /// A string containing the attribute name.
        /// </returns>
        /// <exception cref="H5AgetNameByIndexException">
        /// throws H5AgetNameByIndexException on failure.
        /// </exception>
#pragma endregion documentation

	  static System::String^ getNameByIndex(H5ObjectWithAttributes^ objectId, 
         System::String^ objName, 
         H5IndexType indexType, 
         H5IterationOrder iterationOrder,
         hssize_t position);

	  [System::CLSCompliant(false)]
	  static System::String^ getNameByIndex(H5ObjectWithAttributes^ objectId, 
		  System::String^ objName, 
		  H5IndexType indexType, 
		  H5IterationOrder iterationOrder,
		  hsize_t position);

#pragma region documentation
        ///<summary>
        /// Gets an attribute name, by attribute index position
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetNameByIdx"/>
        ///</summary>

        ///<param name="objectId">
        /// IN: Location of object to which attribute is attached
        ///</param>

        ///<param name="objName">
        /// IN: Name of object to which attribute is attached, relative to 
        /// location
        ///</param>

        ///<param name="indexType">
        /// IN: Type of index
        ///</param>

        ///<param name="iterationOrder">
        /// IN: Index traversal order
        ///</param>

        ///<param name="position">
        /// IN: Attribute's position in index
        ///</param>

        ///<param name="propertyList">
        /// IN: Link access property list
        ///</param>

        /// <returns>
        /// A string containing the attribute name.
        /// </returns>
        /// <exception cref="H5AgetNameByIndexException">
        /// throws H5AgetNameByIndexException on failure.
        /// </exception>
#pragma endregion documentation

	  static System::String^ getNameByIndex(H5ObjectWithAttributes^ objectId, 
         System::String^ objName, 
         H5IndexType indexType, 
         H5IterationOrder iterationOrder,
         hssize_t position,
         H5PropertyListId^ propertyList);

	  [System::CLSCompliant(false)]
	  static System::String^ getNameByIndex(H5ObjectWithAttributes^ objectId, 
		  System::String^ objName, 
		  H5IndexType indexType, 
		  H5IterationOrder iterationOrder,
		  hsize_t position,
		  H5PropertyListId^ propertyList);

#pragma region documentation
      ///<summary>
      /// Opens an attribute for an object specified by object identifier 
      /// and attribute name.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Open"/>
      ///</summary>

      ///<param name="objectWithAttributes">
      /// IN: Identifer for object to which attribute is attached
      ///</param>

      ///<param name="attributeName">
      /// IN: Name of attribute to open
      ///</param>

      ///<param name="propertyList">
      /// IN: Attribute access property list
      ///</param>

      /// <returns>
      /// H5AttributeId associated with the opened attribute.
      /// </returns>

      /// <exception cref="H5AopenException">
      /// throws H5AopenException on failure.
      /// </exception>
#pragma endregion documentation

      static H5AttributeId^ open(
         H5ObjectWithAttributes^ objectWithAttributes,
         System::String^ attributeName,
         H5PropertyListId^ propertyList);

#pragma region documentation
      ///<summary>
      /// Opens an attribute for an object specified by object identifier 
      /// and attribute name.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Open"/>
      ///</summary>

      ///<param name="objectWithAttributes">
      /// IN: Identifer for object to which attribute is attached
      ///</param>

      ///<param name="attributeName">
      /// IN: Name of attribute to open
      ///</param>

      /// <returns>
      /// H5AttributeId associated with the opened attribute.
      /// </returns>

      /// <exception cref="H5AopenException">
      /// throws H5AopenException on failure.
      /// </exception>
#pragma endregion documentation

      static H5AttributeId^ open(
         H5ObjectWithAttributes^ objectWithAttributes,
         System::String^ attributeName);

#pragma region documentation
      ///<summary>
      /// H5A.openByIndex opens an existing attribute that is attached to 
      /// an object specified by location and name, loc_id and obj_name, 
      /// respectively. If loc_id fully specifies the object to which the 
      /// attribute is attached, obj_name should be '.' (a dot).
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByIdx"/>
      ///</summary>

      ///<param name="dataSetOrGroupOrDataTypeId">
      /// IN: Location of object to which attribute is attached
      ///</param>

      ///<param name="objectName">
      /// IN: Name of object to which attribute is attached, relative to 
      /// location
      ///</param>

      ///<param name="indexType">
      /// IN: Type of index
      ///</param>

      ///<param name="traversalOrder">
      /// IN: Index traversal order
      ///</param>

      ///<param name="position">
      /// IN: Attribute's position in index
      ///</param>

      /// <returns>
      /// H5AttributeId for the requested attribute.
      /// </returns>

      /// <exception cref="H5AopenByIndexException">
      /// throws H5AopenByIndexException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5AttributeId^ openByIndex(
         H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
         System::String^ objectName,
         H5IndexType indexType,
         H5IterationOrder traversalOrder,
         hssize_t position);

	  [System::CLSCompliant(false)]
	  static H5AttributeId^ openByIndex(
		  H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
		  System::String^ objectName,
		  H5IndexType indexType,
		  H5IterationOrder traversalOrder,
		  hsize_t position);

#pragma region documentation
      ///<summary>
      /// H5A.openByIndex opens an existing attribute that is attached to 
      /// an object specified by location and name, loc_id and obj_name, 
      /// respectively. If loc_id fully specifies the object to which the 
      /// attribute is attached, obj_name should be '.' (a dot).
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByIdx"/>
      ///</summary>

      ///<param name="dataSetOrGroupOrDataTypeId">
      /// IN: Location of object to which attribute is attached
      ///</param>

      ///<param name="objectName">
      /// IN: Name of object to which attribute is attached, relative to 
      /// location
      ///</param>

      ///<param name="indexType">
      /// IN: Type of index
      ///</param>

      ///<param name="traversalOrder">
      /// IN: Index traversal order
      ///</param>

      ///<param name="position">
      /// IN: Attribute's position in index
      ///</param>

      ///<param name="attributeAccessPropertyList">
      /// IN: Attribute access property list
      ///</param>

      /// <returns>
      /// H5AttributeId for the requested attribute.
      /// </returns>

      /// <exception cref="H5AopenByIndexException">
      /// throws H5AopenByIndexException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5AttributeId^ openByIndex(
         H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
         System::String^ objectName,
         H5IndexType indexType,
         H5IterationOrder traversalOrder,
         hssize_t position,
         H5PropertyListId^ attributeAccessPropertyList);

	  [System::CLSCompliant(false)]
	  static H5AttributeId^ openByIndex(
		  H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
		  System::String^ objectName,
		  H5IndexType indexType,
		  H5IterationOrder traversalOrder,
		  hsize_t position,
		  H5PropertyListId^ attributeAccessPropertyList);

#pragma region documentation
      ///<summary>
      /// H5A.openByIndex opens an existing attribute that is attached to 
      /// an object specified by location and name, loc_id and obj_name, 
      /// respectively. If loc_id fully specifies the object to which the 
      /// attribute is attached, obj_name should be '.' (a dot).
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByIdx"/>
      ///</summary>

      ///<param name="dataSetOrGroupOrDataTypeId">
      /// IN: Location of object to which attribute is attached
      ///</param>

      ///<param name="objectName">
      /// IN: Name of object to which attribute is attached, relative to 
      /// location
      ///</param>

      ///<param name="indexType">
      /// IN: Type of index
      ///</param>

      ///<param name="traversalOrder">
      /// IN: Index traversal order
      ///</param>

      ///<param name="position">
      /// IN: Attribute's position in index
      ///</param>

      ///<param name="attributeAccessPropertyList">
      /// IN: Attribute access property list
      ///</param>

      ///<param name="linkAccessPropertyList">
      /// IN: Link access property list
      ///</param>

      /// <returns>
      /// H5AttributeId for the requested attribute.
      /// </returns>

      /// <exception cref="H5AopenByIndexException">
      /// throws H5AopenByIndexException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5AttributeId^ openByIndex(
         H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
         System::String^ objectName,
         H5IndexType indexType,
         H5IterationOrder traversalOrder,
         hssize_t position,
         H5PropertyListId^ attributeAccessPropertyList,
         H5PropertyListId^ linkAccessPropertyList);

	  [System::CLSCompliant(false)]
	  static H5AttributeId^ openByIndex(
		  H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
		  System::String^ objectName,
		  H5IndexType indexType,
		  H5IterationOrder traversalOrder,
		  hsize_t position,
		  H5PropertyListId^ attributeAccessPropertyList,
		  H5PropertyListId^ linkAccessPropertyList);

#pragma region documentation
      ///<summary>
      /// H5Aget_space retrieves a copy of the dataspace for an attribute. 
      /// The dataspace identifier returned from this function must be 
      /// released with H5S.close  or resource leaks will develop.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetSpace"/>
      ///</summary>

      ///<param name="attributeId">
      /// IN: Identifier of an attribute.
      ///</param>

      /// <returns>
      /// H5DataSpaceId
      /// </returns>

      /// <exception cref="H5AgetSpaceException">
      /// throws H5AgetSpaceException on failure.
      /// </exception>
#pragma endregion documentation

      static H5DataSpaceId^ H5A::getSpace(H5AttributeId^ attributeId);

#pragma region documentation
      ///<summary>
      /// Calls user-defined function for each attribute on an object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Iterate"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Identifier for object to which attributes are attached; 
      /// may be group, dataset, or named datatype.
      ///</param>

      ///<param name="indexType">
      /// IN: Type of index
      ///</param>

      ///<param name="iterationOrder">
      /// IN: Order in which to iterate over index
      ///</param>

      ///<param name="position">
      /// IN/OUT: Initial and returned offset within index
      ///</param>

      ///<param name="iterateCallback">
      /// IN: User-defined function to pass each attribute to
      ///</param>

      ///<param name="opData">
      /// IN/OUT: User data to pass through to and to be returned by 
      /// iterator operator function
      ///</param>

      /// <returns>
      /// H5IterationResult
      /// </returns>

      /// <exception cref="H5AiterateException">
      /// throws H5AiterateException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5IterationResult iterate(H5ObjectWithAttributes^ objectId, 
		  H5IndexType indexType,
		  H5IterationOrder iterationOrder,
		  hssize_t% position,
		  H5AIterateCallback^ iterateCallback,
		  Object^ opData);

#pragma region documentation
      ///<summary>
      /// Calls user-defined function for each attribute on an object.
      /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Iterate"/>
      ///</summary>

      ///<param name="objectId">
      /// IN: Identifier for object to which attributes are attached; 
      /// may be group, dataset, or named datatype.
      ///</param>

      ///<param name="indexType">
      /// IN: Type of index
      ///</param>

      ///<param name="iterationOrder">
      /// IN: Order in which to iterate over index
      ///</param>

      ///<param name="position">
      /// IN/OUT: Initial and returned offset within index
      ///</param>

      ///<param name="iterateCallback">
      /// IN: User-defined function to pass each attribute to
      ///</param>

      ///<param name="opData">
      /// IN/OUT: User data to pass through to and to be returned by 
      /// iterator operator function
      ///</param>

      ///<param name="linkAccessPropertyListId">
      /// IN: Link access property list.
      ///</param>

      /// <returns>
      /// H5IterationResult
      /// </returns>

      /// <exception cref="H5AiterateException">
      /// throws H5AiterateException on failure.
      /// </exception>
#pragma endregion documentation

	  static H5IterationResult iterate(H5ObjectWithAttributes^ objectId, 
         H5IndexType indexType,
         H5IterationOrder iterationOrder,
         hssize_t% position,
         H5AIterateCallback^ iterateCallback,
         Object^ opData,
         H5PropertyListId^ linkAccessPropertyListId);

#pragma region documentation
        ///<summary>
        /// Retrieves attribute information, by attribute identifier.
        /// <see href="http://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetInfo"/>
        ///</summary>

        ///<param name="id">
        /// IN: Attribute identifier
        ///</param>

        /// <returns cref="H5AttributeInfo">
        /// H5AttributeInfo 
        /// </returns>
        /// <exception cref="H5AgetInfoException">
        /// throws H5AgetInfoException on failure.
        /// </exception>
#pragma endregion documentation

      static H5AttributeInfo^ getInfo(H5AttributeId^ id);

   private:

      // Disallow instances of this class.
      H5A() {};


      /// <summary>
      /// Public forms of the create call use this create to do most
      /// of the work.
      /// </summary>
      static H5AttributeId^ H5A::createByName(
         hid_t locId, 
         System::String^ objectName,
         System::String^ attributeName,
         H5DataTypeId^ typeId,
         H5DataSpaceId^ spaceId,
         H5PropertyListId^ attributeCreationProperties,
         H5PropertyListId^ attributePermissionsProperties,
         H5PropertyListId^ linkAccessProperties);

      /// <summary>
      /// Public forms of the openName call use this openName to do most
      /// of the work.
      /// </summary>
      static H5AttributeId^ openName(hid_t locId, System::String^ name);

      /// <summary>
      /// Public forms of the openIndex call use this openIndex to do most
      /// of the work.
      /// </summary>
      static H5AttributeId^ openIndex(hid_t locId, unsigned int index);

      /// <summary>
      /// Public forms of the getNumberOfAttributes call use this 
      //  getNumberOfAttributes to do most of the work.
      /// </summary>
      static int getNumberOfAttributes(hid_t locId);

   };
}
