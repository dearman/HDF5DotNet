/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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

#include "H5A.h"
#include "H5AttributeId.h"
#include "H5DataSpaceId.h"
#include "H5DataTypeId.h"
#include "H5ObjectInfo.h"
#include "H5O.h"
#include "H5PropertyListId.h"
#include "HDFExceptionSubclasses.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#include "HDF5_Native.h"

namespace HDF5DotNet
{

    H5AttributeInfo::H5AttributeInfo()
    {
        throw gcnew HDFException("Unsopported constructor", -1);
    }

    H5AttributeInfo::H5AttributeInfo(
        bool creationOrderValid,
        int creationOrder,
        H5T::CharSet characterSet,
        hssize_t dataSize
        ) : creationOrderValid_(creationOrderValid),
        creationOrder_(safe_cast<H5O_msg_crt_idx_t>(creationOrder)),
        characterSet_(characterSet),
        dataSize_(safe_cast<hsize_t>(dataSize))
    {
    }

    // All H5A::create calls are implemented using the H5A::create overload 
    // that takes a hid_t as the first parameter.
    H5AttributeId^ H5A::createByName(H5ObjectWithAttributes^ object, 
        String^ objectName,
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId)
    {
        return createByName(
            object->Id, 
            objectName, 
            attributeName, 
            typeId, 
            spaceId, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT), 
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT)); 
    }

    H5AttributeId^ H5A::createByName(H5ObjectWithAttributes^ object, 
        String^ objectName,
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId,
        H5PropertyListId^ attributeCreationProperties,
        H5PropertyListId^ attributePermissionsProperties,
        H5PropertyListId^ linkAccessProperties)
    {
        return createByName(
            object->Id, 
            objectName, 
            attributeName, 
            typeId, 
            spaceId, 
            attributeCreationProperties,
            attributePermissionsProperties,
            linkAccessProperties);
    }

    // This is the principal call for H5A::create - all the overloads are 
    //  implemented as calls to this function.
    H5AttributeId^ H5A::createByName(
        hid_t locId, 
        String^ objectName,
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId,
        H5PropertyListId^ attributeCreationProperties,
        H5PropertyListId^ attributePermissionsProperties,
        H5PropertyListId^ linkAccessProperties)
    {
        // Make the call to the "C" library.
        int id = H5Acreate_by_name(locId, objectName, attributeName, typeId->Id, 
            spaceId->Id, attributeCreationProperties->Id,
            attributePermissionsProperties->Id,
            linkAccessProperties->Id);

        // Check conditions and throw appropriately.
        if(id < 0)
        {
            String^ message = String::Format(
                "H5A.create:\n"
                "Failed to create attribute with name {0} for object {1:x}"
                " with status {2}\n",
                attributeName, objectName, id);

            throw gcnew 
                H5AcreateException(message, id);
        }

        // return the Id in a H5AttributeId object.
        return gcnew H5AttributeId(id);
    }


    generic <class Type>
    void H5A::write(
        H5AttributeId^ attributeId,
        H5DataTypeId^ memTypeId,
        H5Array<Type>^ buffer)
    {
        pin_ptr<Type> pinnedDataPtr = buffer->getDataAddress();
        void* voidPtr = pinnedDataPtr;

        // Write using the pinned buffer.
        herr_t status = H5Awrite(attributeId->Id, 
            memTypeId->Id,
            voidPtr);

        // Throw an exception on non-zero status.
        if (status < 0)
        {
            String^ message = String::Format(
                "H5A.write:\n"
                "Failed to write data to attribute {0:x} with status {1}\n",
                attributeId->Id, status);
            throw gcnew H5AwriteException(message, status);
        }
    }

    generic <class Type>
    void H5A::read(
        H5AttributeId^ attributeId,
        H5DataTypeId^ memTypeId,
        H5Array<Type>^ buffer)
    {
        pin_ptr<Type> pinnedDataPtr = buffer->getDataAddress();
        void* voidPtr = pinnedDataPtr;

        // Write using the pinned buffer.
        herr_t status = H5Aread(attributeId->Id, 
            memTypeId->Id,
            voidPtr);

        // Throw an exception on non-zero status.
        if (status < 0)
        {
            String^ message = String::Format(
                "H5A.read:\n"
                "Failed to read data from attribute {0:x} with status {1}\n",
                attributeId->Id, status);
            throw gcnew H5AreadException(message, status);
        }
    }

    void H5A::close(H5AttributeId^ id)	
    {
        herr_t status = H5Aclose(id->Id);

        if (status < 0)
        {
            String^ message = String::Format(
                "H5A.close: \n"
                "  Failed to close attribute {0:x} with status {1}\n",
                id->Id, status);

            throw gcnew H5AcloseException(message, status);
        }
    }

    H5AttributeId^ H5A::openName(H5ObjectWithAttributes^ object, String^ name)
    {
        return openName(object->Id, name);
    }

    H5AttributeId^ H5A::openName(hid_t locId, String^ name)
    {
        hid_t id = H5Aopen_name(locId, name);

        if (id < 0)
        {
            String^ message = String::Format(
                "H5A.openName: \n"
                "  Failed to open name {0} with status {1}\n",
                name, id);

            throw gcnew H5AopenNameException(message, id);
        }

        return gcnew H5AttributeId(id);
    }

    H5AttributeId^ H5A::openByName(H5ObjectWithAttributes^ objectId,
        String^ objectName,
        String^ attributeName)
    {
        return H5A::openByName(objectId, objectName, attributeName,
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5AttributeId^ H5A::openByName(H5ObjectWithAttributes^ objectId,
        String^ objectName,
        String^ attributeName,
        H5PropertyListId^ attributeAccessPropertyListId,
        H5PropertyListId^ linkAccessPropertyListId)
    {
        hid_t id = H5Aopen_by_name(objectId->Id, objectName, attributeName,
            attributeAccessPropertyListId->Id,
            linkAccessPropertyListId->Id);

        if (id < 0)
        {
            String^ message = String::Format(
                "H5A.openByName: \n"
                "  Failed to open attribute name {0} in object {1} "
                " with status {2}\n",
                attributeName, objectName, id);

            throw gcnew H5AopenByNameException(message, id);
        }

        return gcnew H5AttributeId(id);
    }

    H5AttributeId^ H5A::openIndex(H5ObjectWithAttributes^ objectId, 
        int index)
    {
        return openIndex(objectId->Id, safe_cast<unsigned int>(index));
    }

    H5AttributeId^ H5A::openIndex(H5ObjectWithAttributes^ objectId, 
        unsigned int index)
    {
        return openIndex(objectId->Id, index);
    }

    H5AttributeId^ H5A::openIndex(hid_t locId, 
        unsigned int index)
    {
        hid_t id = H5Aopen_idx(locId, index);

        if (id < 0)
        {
            String^ message = String::Format(
                "H5A.openIndex: \n"
                "  Failed to open index number {0} with status {1}\n",
                index, id);

            throw gcnew H5AopenIndexException(message, id);
        }

        return gcnew H5AttributeId(id);
    }

    H5DataSpaceId^ H5A::getSpace(H5AttributeId^ attributeId)
    {
        hid_t id = H5Aget_space(attributeId->Id);

        if (id < 0)
        {
            String^ message = String::Format(
                "H5A.getSpace: \n"
                "  Failed to retrieve data space from attribute {0:x} with\n "
                "  status {1}\n",
                attributeId->Id, id);

            throw gcnew H5AgetSpaceException(message, id);
        }

        return gcnew H5DataSpaceId(id);
    }

    H5DataTypeId^ H5A::getType(H5AttributeId^ attributeId)
    {
        hid_t id = H5Aget_type(attributeId->Id);

        if (id < 0)
        {
            String^ message = String::Format(
                "H5A.getType: \n"
                "  Failed to retrieve data space from attribute {0:x} with\n "
                "  status {1}\n",
                attributeId->Id, id);

            throw gcnew H5AgetTypeException(message, id);
        }

        return gcnew H5DataTypeId(id);
    }


    int H5A::getNumberOfAttributes(H5ObjectWithAttributes^ objectId)
    {
        return getNumberOfAttributes(objectId->Id);
    }

    int H5A::getNumberOfAttributes(hid_t locId)
    {
        hid_t nAttributes = H5Aget_num_attrs(locId);

        if (nAttributes < 0)
        {
            String^ message = String::Format(
                "H5A.getNumberOfAttributes: \n"
                "  Failed to retrieve number of attributes for object id {0:x} \n"
                "  with status {1}\n",
                locId, nAttributes);

            throw gcnew H5AgetNumberOfAttributesException(message, locId);
        }

        return nAttributes;
    } 

    void H5A::Delete(H5ObjectWithAttributes^ objectId,
        String^ attributeName)
    {
        // Make the call to the "C" library.
        herr_t status = H5Adelete(objectId->Id, attributeName);

        // Check conditions and throw appropriately.
        if(status < 0)
        {
            String^ message = String::Format(
                "H5A.Delete:\n"
                "Failed to delete attribute with name {0} from"
                " object {1:x} with status {2}\n",
                attributeName, objectId->Id, status);
            throw gcnew 
                H5ADeleteException(message, status);
        }
    }

    void H5A::DeleteByName(H5ObjectWithAttributes^ objectId, 
        String^ objectName, 
        String^ attributeName)
    {
        H5A::DeleteByName(objectId, objectName, attributeName, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    void H5A::DeleteByName(H5ObjectWithAttributes^ objectId, 
        String^ objectName,
        String^ attributeName,
        H5PropertyListId^ linkAccessPropertyListId)
    {
        // Make the call to the "C" library.
        herr_t status = H5Adelete_by_name(objectId->Id, objectName, 
            attributeName, 
            linkAccessPropertyListId->Id);

        // Check conditions and throw appropriately.
        if(status < 0)
        {
            String^ message = String::Format(
                "H5A.DeleteByName:\n"
                "Failed to delete attribute with name {0} from"
                " object {1:x} with status {2}\n",
                attributeName, objectName, status);
            throw gcnew 
                H5AdeleteByNameException(message, status);
        }
    }

    H5AttributeId^ H5A::create(H5ObjectWithAttributes^ objectId, 
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId)
    {
        return H5A::create(objectId, attributeName, typeId, spaceId,
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5AttributeId^ H5A::create(H5ObjectWithAttributes^ objectId, 
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId,
        H5PropertyListId^ creationPropertyListId)
    {
        return H5A::create(objectId, attributeName, typeId, spaceId,
            creationPropertyListId,
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }


    H5AttributeId^ H5A::create(H5ObjectWithAttributes^ objectId, 
        String^ attributeName,
        H5DataTypeId^ typeId,
        H5DataSpaceId^ spaceId,
        H5PropertyListId^ creationPropertyListId,
        H5PropertyListId^ accessPropertyListId)
    {
        // Make the call to the "C" library.
        herr_t status = H5Acreate2(objectId->Id, 
            attributeName, 
            typeId->Id,
            spaceId->Id,
            creationPropertyListId->Id,
            accessPropertyListId->Id);

        // Check conditions and throw appropriately.
        if(status < 0)
        {
            String^ message = String::Format(
                "H5A.create:\n"
                "Failed to create attribute with name {0} from"
                " object {1:x} with status {2}\n",
                attributeName, objectId->Id, status);
            throw gcnew 
                H5AcreateException(message, status);
        }

        return gcnew H5AttributeId(status);
    }


    H5AttributeId^ H5A::open(
        H5ObjectWithAttributes^ objectWithAttributesId,
        String^ attributeName)
    {
        return H5A::open(objectWithAttributesId,
            attributeName,
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5AttributeId^ H5A::open(
        H5ObjectWithAttributes^ objectWithAttributesId,
        String^ attributeName,
        H5PropertyListId^ propertyList)
    {
        // Make the call to the "C" library.
        herr_t status = H5Aopen(objectWithAttributesId->Id, 
            attributeName, 
            propertyList->Id);

        // Check conditions and throw appropriately.
        if(status < 0)
        {
            String^ message = String::Format(
                "H5A.Open:\n"
                "Failed to open attribute with name {0} from"
                " object {1:x} with status {2}\n",
                attributeName, objectWithAttributesId->Id, status);
            throw gcnew 
                H5AopenException(message, status);
        }

        return gcnew H5AttributeId(status);
    }

    String^ H5A::getNameByIndex(H5ObjectWithAttributes^ objectId, 
        String^ objName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hssize_t position)
    {
        return getNameByIndex(objectId, objName, indexType, iterationOrder, safe_cast<hsize_t>(position));
    }

    String^ H5A::getNameByIndex(H5ObjectWithAttributes^ objectId, 
        String^ objName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hsize_t position)
    {
        String^ attributeName = 
            getNameByIndex(objectId, objName, indexType, 
            iterationOrder, position, 
            gcnew H5PropertyListId(H5P::Template::DEFAULT));

        return attributeName;
    }

    String^ H5A::getNameByIndex(H5ObjectWithAttributes^ objectId, 
        String^ objName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hssize_t position,
        H5PropertyListId^ propertyList)
    {
        return getNameByIndex(objectId, objName, indexType, iterationOrder, safe_cast<hsize_t>(position), propertyList);
    }

    String^ H5A::getNameByIndex(H5ObjectWithAttributes^ objectId, 
        String^ objName, 
        H5IndexType indexType, 
        H5IterationOrder iterationOrder,
        hsize_t position,
        H5PropertyListId^ propertyList)
    {
        // Find the number of characters in the object name.
        ssize_t nameLength = H5Aget_name_by_idx(
            objectId->Id,
            objName,
            safe_cast<H5_index_t>(indexType),
            safe_cast<H5_iter_order_t>(iterationOrder),
            position, 
            NULL,
            0,
            propertyList->Id);

        array<char>^ name;

        if (nameLength > 0)
        {
            // Allocate enough memory to hold the name.
            name = gcnew array<char>(safe_cast<int>(nameLength+1));

            // Pin the array in place
            pin_ptr<char> namePtr = &name[0];

            // Request the name
            nameLength = H5Aget_name_by_idx(
                objectId->Id,
                objName,
                safe_cast<H5_index_t>(indexType),
                safe_cast<H5_iter_order_t>(iterationOrder),
                position, 
                namePtr,
                safe_cast<size_t>(nameLength+1),
                propertyList->Id);
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5A.getNameByIndex: \n"
                "  Failed to get attribute name for id {0:x},  object {1} with "
                "status {2}\n", objectId->Id, objName, nameLength);

            throw gcnew H5AgetNameByIndexException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hssize_t position)
    {
        return openByIndex(
            dataSetOrGroupOrDataTypeId,
            objectName,
            indexType,
            traversalOrder,
            safe_cast<hsize_t>(position));
    }

    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hsize_t position)
    {
        return
            H5A::openByIndex(dataSetOrGroupOrDataTypeId,
            objectName,
            indexType,
            traversalOrder,
            position,
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hssize_t position,
        H5PropertyListId^ linkAccessPropertyList)
    {
        return openByIndex(
            dataSetOrGroupOrDataTypeId,
            objectName,
            indexType,
            traversalOrder,
            safe_cast<hsize_t>(position),
            linkAccessPropertyList);
    }

    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hsize_t position,
        H5PropertyListId^ linkAccessPropertyList)
    {
        return H5A::openByIndex(dataSetOrGroupOrDataTypeId,
            objectName,
            indexType,
            traversalOrder,
            position,
            gcnew H5PropertyListId(H5P::Template::DEFAULT),
            linkAccessPropertyList);
    }

    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hssize_t position,
        H5PropertyListId^ attributeAccessPropertyListId,
        H5PropertyListId^ linkAccessPropertyListId)
    {
        return openByIndex(
            dataSetOrGroupOrDataTypeId,
            objectName,
            indexType,
            traversalOrder,
            safe_cast<hsize_t>(position),
            attributeAccessPropertyListId,
            linkAccessPropertyListId);
    }


    H5AttributeId^ H5A::openByIndex(
        H5ObjectWithAttributes^ dataSetOrGroupOrDataTypeId, 
        String^ objectName,
        H5IndexType indexType,
        H5IterationOrder traversalOrder,
        hsize_t position,
        H5PropertyListId^ attributeAccessPropertyListId,
        H5PropertyListId^ linkAccessPropertyListId)
    {

        herr_t status = H5Aopen_by_idx(
            dataSetOrGroupOrDataTypeId->Id,
            objectName,
            safe_cast<H5_index_t>(indexType),
            safe_cast<H5_iter_order_t>(traversalOrder),
            position, 
            attributeAccessPropertyListId->Id,
            linkAccessPropertyListId->Id
            );

        if (status < 0)
        {
            String^ message = String::Format(
                "H5A.openByIndex: \n"
                "  Failed to open attribute id {0:x},  objectName {1}, "
                "  position {2} "
                "with status {3}\n", dataSetOrGroupOrDataTypeId->Id, 
                objectName, position, status);

            throw gcnew H5AopenByIndexException(message, status);
        }

        return gcnew H5AttributeId(status);
    }

    H5AttributeInfo^ H5A::getInfo(H5AttributeId^ id)
    {
        H5A_info_t info;

        herr_t status = H5Aget_info(id->Id, &info);  

        if (status < 0)
        {
            String^ message = String::Format(
                "H5A.getInfo: \n"
                "  Failed to get info for attribute id {0:x} with status {1}.",
                id->Id, status);

            throw gcnew H5AgetInfoException(message, status);
        }

        return gcnew H5AttributeInfo(info.corder_valid != 0,
            safe_cast<int>(info.corder),
            safe_cast<H5T::CharSet>(info.cset),
            safe_cast<hssize_t>(info.data_size));
    }

    String^ H5A::getName(H5AttributeId^ attributeId)
    {
        ssize_t nameLength = H5Aget_name(attributeId->Id, 0, NULL);

        array<char>^ name;

        if (nameLength > 0)
        {
            name = gcnew array<char>(safe_cast<int>(nameLength+1));
            pin_ptr<char> namePtr = &name[0];
            nameLength = H5Aget_name(attributeId->Id, 
                safe_cast<size_t>(nameLength+1),
                namePtr);
        }

        if (nameLength < 0)
        {
            String^ message = String::Format(
                "H5A.getName:\n"
                "Failed to get attribute name from"
                " attribute Id {0:x} with status {1}\n",
                attributeId->Id, nameLength);
            throw gcnew
                HDFException(message, safe_cast<int>(nameLength));
        }

        array<wchar_t>^ wideName = gcnew array<wchar_t>(safe_cast<int>(nameLength+1));
        for(int i=0; i< safe_cast<int>(nameLength); ++i)
            wideName[i] = safe_cast<wchar_t>(name[i]);

        return gcnew String(wideName,0,safe_cast<int>(nameLength));
    }

    H5IterationResult H5A::iterate(H5ObjectWithAttributes^ objectId, 
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hssize_t% position,
        H5AIterateCallback^ iterateCallback,
        Object^ opData)
    {
        return 
            H5A::iterate(objectId, indexType, iterationOrder,
            position, iterateCallback, opData,
            gcnew H5PropertyListId(H5P::Template::DEFAULT));
    }

    H5IterationResult H5A::iterate(H5ObjectWithAttributes^ objectId, 
        H5IndexType indexType,
        H5IterationOrder iterationOrder,
        hssize_t% position,
        H5AIterateCallback^ iterateCallback,
        Object^ opData,
        H5PropertyListId^ linkAccessPropertyListId)
    {
        String^ objectName = ".";
        String^ attributeName;
        H5AttributeInfo^ attributeInfo;

        // Find the number of attributes
        H5ObjectInfo^ objectInfo = H5O::getInfo(objectId);
        hssize_t nAttributes = objectInfo->nAttributes;

        // Continue calling the delegate until status is non-zero or until
        // all the attributes have been traversed.
        H5IterationResult delegateStatus = H5IterationResult::SUCCESS;

        while((position < nAttributes) && (delegateStatus == 
            H5IterationResult::SUCCESS))
        {
            // Open the attribute by index number.
            H5AttributeId^ attributeId = openByIndex(
                objectId, objectName, indexType, iterationOrder, position, 
                linkAccessPropertyListId);

            // Get the attribute info
            attributeInfo = H5A::getInfo(attributeId);

            // Get the attribute name.
            attributeName = getName(attributeId);

            // Call the delegate with the attribute Id
            delegateStatus = iterateCallback(attributeId, 
                attributeName,
                attributeInfo,
                opData);

            // Close the attribute
            H5A::close(attributeId);

            if (delegateStatus == H5IterationResult::SUCCESS)
            {
                ++position;
            }
        }

        return delegateStatus;
    }

}// end of namespace HDF5dotNET
