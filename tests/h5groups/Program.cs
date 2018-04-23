using System;
using System.Collections.Generic;
using System.Text;
using HDF5DotNet;

namespace h5groups
{
   using hsize_t = UInt64;
   using hssize_t = Int64;

   class Program
   {
      static int nerrors = 0;
      const string FILE_NAME = ("Group.h5");
      const int RANK = 2;
      static void test_group_basics()
      {
         try
         {
            Console.Write("Testing group basics");

            // Create the file.
            H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            // Create a group.
            H5GroupId groupId = H5G.create(fileId, "/fromRoot");

            // Create a dataspace for common use.
            hssize_t[] dims = { 1000, 20 };
            H5DataSpaceId dspace = H5S.create_simple(RANK, dims);

            // Create a dataset using file as location with absolute path name.
            H5DataSetId dset1Id = H5D.create(fileId, "/fromRoot/intArray", H5T.H5Type.NATIVE_INT, dspace);

            // Create a dataset using group as location with absolute path name.
            H5DataSetId dset2Id = H5D.create(groupId, "/fromRoot/shortArray", H5T.H5Type.NATIVE_SHORT, dspace);

            // Create a dataset using group as location with relative path name.
            H5DataSetId dset3Id = H5D.create(groupId, "notfromRoot", H5T.H5Type.NATIVE_UCHAR, dspace);

            ObjectInfo info = H5G.getObjectInfo(fileId, "/fromRoot/intArray", true);
            if (info.nHardLinks != 1)
               Console.WriteLine("\ntest_group_basics: number of hardlinks for /fromRoot/intArray should be = {0}", info.nHardLinks);
            if (info.objectType != H5GType.DATASET)
               Console.WriteLine("\ntest_group_basics: Object should be a dataset");

            // Close objects and files.
            H5D.close(dset1Id);
            H5D.close(dset2Id);
            H5D.close(dset3Id);
            H5S.close(dspace);
            H5G.close(groupId);

            // Check various number of objects.
            H5GroupId rootId = H5G.open(fileId, "/");
            hssize_t num_objs = H5G.getNumObjects(rootId);
            if (num_objs != 1)
            {
               Console.WriteLine("\ntest_group_basics: incorrect num_objs = {0} for root group\n", num_objs);
               nerrors++;
            }

            groupId = H5G.open(fileId, "fromRoot");
            num_objs = H5G.getNumObjects(groupId);
            if (num_objs != 3)
            {
               Console.WriteLine("\ntest_group_basics: incorrect num_objs = {0} for group \"fromRoot\"\n", num_objs);
               nerrors++;
            }

            H5G.close(rootId);
            H5G.close(groupId);
            H5F.close(fileId);

            if (nerrors == 0)
               Console.WriteLine("\t\t\t\t\tPASSED");
         }
         catch (HDFException anyHDF5E)
         {
            Console.WriteLine(anyHDF5E.Message);
            nerrors++;
         }
         catch (System.Exception sysE)
         {
            Console.WriteLine(sysE.TargetSite);
            Console.WriteLine(sysE.Message);
            nerrors++;
         }
      } // test_group_basics

      /*
       * Operator function.
       */
      static int file_info(H5GroupId id, string objectName, Object param)
      {
         string str_param = (string)param;
         Console.WriteLine("\t   {0}: {1}", str_param, objectName);
         return 0;
      }

      /*
       * test_group_iterate -- tests that group iterating works properly.
       *      - opens the file created in the test_group_basics
       *      - creates more groups and datasets
       *      - iterates through root group and each sub group priting out name of each object
       */
      static void test_group_iterate()
      {
         try
         {
            Console.Write("Testing group iteration");

            // Open the file.
            H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Create a group in the file.
            H5GroupId groupId = H5G.create(fileId, "/Data");

            // Open first dataset.
            H5DataSetId dset1Id = H5D.open(fileId, "/fromRoot/intArray");

            // Get dataspace of this dataset.
            H5DataSpaceId dspace = H5D.getSpace(dset1Id);

            // Create a dataset in the group using absolute name.
            H5DataSetId dataset = H5D.create(groupId, "/Data/IntData", H5T.H5Type.NATIVE_INT, dspace);

            // Close the first dataset.
            H5S.close(dspace);
            H5D.close(dataset);

            // Create the second dataset.

            hssize_t[] dims = { 500, 20 };
            dspace = H5S.create_simple(RANK, dims);
            dataset = H5D.create(groupId, "/Data/FloatData", H5T.H5Type.NATIVE_FLOAT, dspace);

            // Close objects and file.
            H5D.close(dataset);
            H5G.close(groupId);
            H5F.close(fileId);

            // Now reopen the file and group in the file.
            fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);
            groupId = H5G.open(fileId, "/Data");

            // Access "IntData" dataset in the group.
            dataset = H5D.open(groupId, "IntData");

            // Create a dataset in the root group.
            dataset = H5D.create(fileId, "/singleDataset", H5T.H5Type.NATIVE_INT, dspace);

            // Various checks on number of objects
            groupId = H5G.open(fileId, "/");
            hssize_t num_objs = H5G.getNumObjects(groupId);
            if (num_objs != 3)
               Console.WriteLine("\ntest_group_iterate: / should have 3 objects: /fromRoot, /Data, and /singleDataset, but is {0}", num_objs);
            H5G.close(groupId);

            groupId = H5G.open(fileId, "/fromRoot");
            num_objs = H5G.getNumObjects(groupId);
            if (num_objs != 3)
               Console.WriteLine("\ntest_group_iterate: /fromRoot should have 3 objects: intArray, shortArray, notfromRoot, but is {0}", num_objs);

            // Use iterator to see the names of the objects in the root group and sub groups.
            H5GIterateCallback myCallback;
            myCallback = file_info;
            int x = 0;

            Console.WriteLine();
            Console.WriteLine("\tRoot Group iterating:");
            int index = H5G.iterate(fileId, "/", myCallback, "Object name:", ref x);
            Console.WriteLine();

            Console.WriteLine("\t/fromRoot iterating:");
            x = 0;
            index = H5G.iterate(fileId, "/fromRoot", myCallback, "Object name:", ref x);

            // Close objects and file.
            H5D.close(dataset);
            H5G.close(groupId);
            H5S.close(dspace);
            H5F.close(fileId);

            Console.WriteLine("\t\t\t\t\t\t\tPASSED");
         }
         catch (HDFException anyHDF5E)
         {
            Console.WriteLine(anyHDF5E.Message);
            nerrors++;
         }
         catch (System.Exception sysE)
         {
            Console.WriteLine(sysE.TargetSite);
            Console.WriteLine(sysE.Message);
            nerrors++;
         }
      }  // test_group_iterate

      static void test_group_info()
      {
         try
         {
            Console.Write("Testing getting group information");

            // Open the file.
            H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Open the root group.
            H5GroupId groupId = H5G.open(fileId, "/");

            // Get number of objects in the root group.
            long num_objs = H5G.getNumObjects(groupId);
            if (num_objs != 3)
            {
               Console.WriteLine("\ntest_group_info: Root group should have 3 objects: /fromRoot, /Data, and /singleDataset, but is {0}", num_objs);
               nerrors++;
            }

            // The root group has three objects in alphabetical order:
            //    intArray
            //    notfromRoot
            //    shortArray
            // Note that, in order for this function to work correctly when taking the third
            // parameter as H5IndexType.CRT_ORDER, the group's creation order must be tracked
            // by setting the group creation property list with the C function H5Pset_link_creation_order,
            // which is not included in this .NET wrappers version. - Mar, 2008

            // Check object #3, should be "notfromRoot"
            string obj_name = H5L.getNameByIndex(groupId, ".", H5IndexType.NAME, H5IterationOrder.INCREASING, 2);
            if (obj_name != "singleDataset")
            {
               Console.WriteLine("\ntest_group_info: Incorrect name for 2nd objects from root group: {0}, should be {1}", obj_name, "singleDataset");
               nerrors++;
            }

            // Close root group.
            H5G.close(groupId);

            // Open group "/fromRoot"
            groupId = H5G.open(fileId, "/fromRoot");
            H5GInfo oinfo = H5G.getInfo(groupId);
            if (oinfo.nLinks != 3)
            {
               Console.WriteLine("\ntest_group_info: /fromRoot should have 3 objects: intArray, shortArray, notfromRoot, but is {0}", num_objs);
               nerrors++;
            }

            // Check objects #1 and #3, should be "intArray" and "notfromRoot"
            obj_name = H5L.getNameByIndex(groupId, ".", H5IndexType.NAME, H5IterationOrder.INCREASING, 0);
            if (obj_name != "intArray")
            {
               Console.WriteLine("\ntest_group_info: Incorrect name for 1st object from group named /fromRoot: {0}, should be {1}", obj_name, "intArray");
               nerrors++;
            }
            obj_name = H5L.getNameByIndex(groupId, ".", H5IndexType.NAME, H5IterationOrder.INCREASING, 2, new H5PropertyListId(H5P.Template.DEFAULT));
            if (obj_name != "shortArray")
            {
               Console.WriteLine("\ntest_group_info: Incorrect name for 3rd object from group named /fromRoot: {0}, should be {1}", obj_name, "shortArray");
               nerrors++;
            }

            // Close objects and file.
            H5G.close(groupId);
            H5F.close(fileId);

            Console.WriteLine("\t\t\tPASSED");
         }
         catch (HDFException anyHDF5E)
         {
            Console.WriteLine(anyHDF5E.Message);
            nerrors++;
         }
         catch (System.Exception sysE)
         {
            Console.WriteLine(sysE.TargetSite);
            Console.WriteLine(sysE.Message);
            nerrors++;
         }
      }  // test_group_info

      static void Main(string[] args)
      {
         Console.WriteLine();
         Console.WriteLine("TEST: HDF5DotNet Group API");
         Console.WriteLine();
         try
         {
            // Suppress error printing from the C library.
            H5E.suppressPrinting();

            test_group_basics();
            test_group_iterate();
            test_group_info();
         }
         catch (HDFException anyHDF5E)
         {
            Console.WriteLine(anyHDF5E.Message);
            nerrors++;
         }
         catch (System.Exception sysE)
         {
            Console.WriteLine(sysE.TargetSite);
            Console.WriteLine(sysE.Message);
            nerrors++;
         }
         Console.WriteLine();
         if (nerrors > 0)
            Console.WriteLine("Test(s) failed: {0}", nerrors, "occurred!");
         else
            Console.WriteLine("---- All group tests passed.");
         Console.WriteLine();
      }
   }
}
