using namespace System;
using namespace HDF5DotNet;

int myErrorDelegate(int estackId, void* myPtr)
{
   Console::WriteLine("Hey! This is my error delegate!");
   Console::WriteLine("The value of myPtr is {0}", reinterpret_cast<int>(myPtr));
   return 1;
}

void* userAlloc(size_t size, void* alloc_info)
{
   Console::WriteLine("Using userAlloc to alloc {0} bytes", size);
   return new char[size];
}

void userFree(void* memory, void* free_info)
{
   Console::WriteLine("Using userFree to free memory");
   delete [] memory;
   return;
}


int main()
{
   try
   {
      // We will write and read an int array of this length.
      const int DATA_ARRAY_LENGTH = 128;

      // Rank is the number of dimensions of the data array.
      const int RANK = 1;

      // Create an HDF5 file.
      // The enumeration type H5F.CreateMode provides only the legal 
      // creation modes.  Missing H5Fcreate parameters are provided
      // with default values.
      H5FileId^ fileId = H5F::create("myCpp.h5", 
         H5F::CreateMode::ACC_TRUNC);

      // Create a HDF5 group.  
      H5GroupId^ groupId = H5G::create(fileId, "/cppGroup");

      // Prepare to create a data space for writing a 1-dimensional 
      // signed integer array.
      array<unsigned long long>^ dims = 
         gcnew array<unsigned long long>(RANK);
      dims[0] = DATA_ARRAY_LENGTH;

      HDF5DotNet::H5AutoDelegate^ d = gcnew H5AutoDelegate(&myErrorDelegate);

      H5E::setAuto(0, d, 0);
      GC::Collect();	  
      //H5E::suppressPrinting()

      // Put descending ramp data in an array so that we can
      // write it to the file.
      array<int>^ dset_data = gcnew array<int>(DATA_ARRAY_LENGTH);
      for (int i = 0; i < DATA_ARRAY_LENGTH; i++)
         dset_data[i] = DATA_ARRAY_LENGTH - i;

      // Create a data space to accommodate our 1-dimensional array.
      // The resulting H5DataSpaceId will be used to create the 
      // data set.
      H5DataSpaceId^ spaceId = H5S::create_simple(RANK, dims);

      // Create a copy of a standard data type.  We will use the 
      // resulting H5DataTypeId to create the data set.  We could
      // have  used the HST.H5Type data directly in the call to 
      // H5D.create, but this demonstrates the use of H5T.copy 
      // and the use of a H5DataTypeId in H5D.create.
      H5DataTypeId^ typeId = H5T::copy(H5T::H5Type::NATIVE_INT);

      // Create the data set.
      //  H5E::suppressPrinting(0);
      //H5S::close(spaceId);  //-- uncomment this to see H5EsetAuto work.
      H5DataSetId^ dataSetId = H5D::create(fileId, "/csharpExample", 
         typeId, spaceId);

      H5PropertyListId^ pid = H5P::create(H5P::Class::DATASET_ACCESS);


      // Test use of vlen

      // Create a vlen data type
      H5DataTypeId^ tid1 = H5T::vlenCreate(H5T::H5Type::NATIVE_UINT);

      H5DataSetId^ vDataSetId = H5D::create(fileId, "/vlenTest", tid1,
         spaceId);

      // Create a jagged array of integers.
      array<hvl_t>^ vlArray = gcnew array<hvl_t>(DATA_ARRAY_LENGTH);
      for(int i=0; i < DATA_ARRAY_LENGTH; i++) 
      {
         // Allocate memory that is not garbage collected.
         vlArray[i].p = new char[((i+1)*sizeof(unsigned int))];

         // Fill the array with integers = the row number
         int* intPointer = reinterpret_cast<int*>(vlArray[i].p);
         for(int j=0;j<i+1;j++)
         {
            intPointer[j] = i;
         }

         vlArray[i].len = i+1;
      }

      H5D::write(vDataSetId, tid1, 
         gcnew H5Array<hvl_t>(vlArray));


      array<hvl_t>^ vlReadBackArray = gcnew array<hvl_t>(DATA_ARRAY_LENGTH);
      H5D::read(vDataSetId, tid1, gcnew H5Array<hvl_t>(vlReadBackArray));

      for(int i=0;i<DATA_ARRAY_LENGTH;i++)
      {
         int* iPointer = reinterpret_cast<int*>(vlReadBackArray[i].p);
         for(int j=0;j<i+1;j++)
         {
            Console::WriteLine(iPointer[j]);
         }
      }

      H5D::vlenReclaim(tid1, spaceId, gcnew H5PropertyListId(H5P::Template::DEFAULT),
         gcnew H5Array<hvl_t>(vlReadBackArray));

      H5AllocDelegate^ allocDelegate = gcnew H5AllocDelegate(&userAlloc);
      H5FreeDelegate^ freeDelegate = gcnew H5FreeDelegate(&userFree);

      H5PropertyListId^ memManagerPlist = H5P::create(H5P::Class::DATASET_XFER);
      H5P::setVlenMemManager(memManagerPlist, allocDelegate, 0, freeDelegate, 0);


      const int BUFFER_SIZE = 1024;

      char* typeConversionBuffer = new char[BUFFER_SIZE];
      char* backgroundBuffer = new char[BUFFER_SIZE];
      for(int i=0;i<BUFFER_SIZE;i++)
      {
         typeConversionBuffer[i] = 'r';
         backgroundBuffer[i] = 'r';
      }

      H5P::setBuffer(memManagerPlist, BUFFER_SIZE,
         typeConversionBuffer, 
         backgroundBuffer);

      array<hvl_t>^ vlReadBackNew = gcnew array<hvl_t>(DATA_ARRAY_LENGTH);
      H5D::read(vDataSetId, tid1, 
         gcnew H5DataSpaceId(H5S::H5SType::ALL), 
         gcnew H5DataSpaceId(H5S::H5SType::ALL), memManagerPlist,
         gcnew H5Array<hvl_t>(vlReadBackNew));

      H5D::vlenReclaim(tid1, spaceId, memManagerPlist, gcnew H5Array<hvl_t>(vlReadBackNew));

      // Write the integer data to the data set.
      H5DataTypeId^ dataTypeId = gcnew H5DataTypeId(H5T::H5Type::NATIVE_INT);
      H5D::write(dataSetId, dataTypeId, 
         gcnew H5Array<int>(dset_data));

      // Create an integer array to receive the read data.
      array<int>^ readDataBack = gcnew array<int>(DATA_ARRAY_LENGTH);

      // Read the integer data back from the data set
      H5D::read(dataSetId, dataTypeId, gcnew H5Array<int>(readDataBack));

      // Echo the data
      for(int i=0;i<DATA_ARRAY_LENGTH;i++)
      {
         Console::WriteLine(readDataBack[i]);
      }

      // Close all the open resources.
      H5D::close(dataSetId);
      H5S::close(spaceId);
      H5T::close(typeId);
      H5G::close(groupId);
      H5F::close(fileId);

      // Reopen and reclose the file.
      H5FileId^ openId = H5F::open("myCpp.h5", 
         H5F::OpenMode::ACC_RDONLY);
      H5F::close(openId);
   }
   // This catches all the HDF exception classes.  Because each call
   // generates unique exception, different exception can be handled
   // separately.  For example, to catch open errors we could have used
   // catch (H5FopenException^ openException).
   catch (HDFException^ e)
   {
      Console::WriteLine(e->Message);
   }
   Console::WriteLine("Processing complete!");
   Console::ReadLine();
}