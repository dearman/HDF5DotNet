using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using HDF5DotNet;

namespace tattr
{
   using hsize_t = UInt64;
   using hssize_t = Int64;
   using uchar = Char;

   class Program
   {
      const string FILE_NAME = "tattr.h5";
      const string COMP_FNAME = "test_compound.h5";

      /* Dataset Information */
      const string DSET1_NAME = "Dataset1";
      const string D1ATTR1_NAME = "First Attribute of Dataset1";
      const string D1ATTR2_NAME = "Second Attribute of Dataset1";
      const string D2ATTR_NAME = "Attribute of Dataset2";

      /* Group Information */
      const string GROUP1_NAME = "/Group1";
      const string GATTR_NAME = "Attribute of /Group1";
      const string RGATTR_NAME = "Attribute of root group";
      const int GATTR_RANK = 2;
      const int GATTR_DIM1 = 2;
      const int GATTR_DIM2 = 2;

      /* Attributes' Rank & Dimensions */
      const string ATTR1_NAME = "Attr1";
      const int ATTR1_RANK = 1;
      const int ATTR1_DIM = 3;


      const string ATTR2_NAME = "Attr2";
      const int ATTR2_RANK = 2;
      const int ATTR2_DIM1 = 2;
      const int ATTR2_DIM2 = 2;

      const string ATTR3_NAME = "Attr3";
      const string ATTR4_NAME = "Attr4";
      const int ATTR4_RANK = 2;
      const int ATTR4_DIM1 = 2;
      const int ATTR4_DIM2 = 2;
      const string ATTR4_FIELDNAME1 = "c";
      const string ATTR4_FIELDNAME2 = "i";
      const string ATTR4_FIELDNAME3 = "l";
      const int SPACE1_RANK = 2;
      const int SPACE1_DIM1 = 3;
      const int SPACE1_DIM2 = 15;
      const int SPACE1_DIM3 = 13;
      static int nerrors = 0;

      struct attr4_struct
      {
         public char c;
         public int i;
         public long l;
      };
            // Test data for the group attribute.
           static int[,] gattr_data = new int[,] { { 7614, -416 }, { 197814, -3 } };


      static void test_attr_basic_write()
      {
         try
         {
            Console.Write("Testing Basic Scalar Attribute Writing Functions");

            // Create a new file using H5F_ACC_TRUNC access,
            // default file creation properties, and default file
            // access properties.
            H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            // Copy datatype for use.
            H5DataTypeId typeId = H5T.copy(H5T.H5Type.NATIVE_INT);

            // Open the root group.
            H5GroupId groupId = H5G.open(fileId, "/");

            // Create dataspace for attribute.
            hssize_t[] gdims = { GATTR_DIM1, GATTR_DIM2 };
            H5DataSpaceId gspace_Id = H5S.create_simple(GATTR_RANK, gdims);

            // Create an attribute for the group.
            H5AttributeId attrId = H5A.create(groupId, RGATTR_NAME, typeId, gspace_Id);
            H5A.close(attrId);
            H5G.close(groupId);

            // Create a group in this file.
            groupId = H5G.create(fileId, GROUP1_NAME);

            // Create an attribute for group /Group1.
            attrId = H5A.create(groupId, GATTR_NAME, typeId, gspace_Id);
            H5A.write(attrId, typeId, new H5Array<int>(gattr_data));

            // Create the dataspace.
            hssize_t[] dims1 = { SPACE1_DIM1, SPACE1_DIM2 };
            H5DataSpaceId space1_Id = H5S.create_simple(SPACE1_RANK, dims1);

            // Create a dataset using default properties.
            H5DataSetId dsetId = H5D.create(fileId, DSET1_NAME, H5T.H5Type.NATIVE_UCHAR, space1_Id);

            // Close objects and file.
            H5A.close(attrId);
            H5D.close(dsetId);
            H5G.close(groupId);
            H5F.close(fileId);

            // Open the file again.
            fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Open the root group.
            groupId = H5G.open(fileId, "/");

            // Open attribute again.
            attrId = H5A.open(groupId, RGATTR_NAME);

            // Close attribute and root group.
            H5A.close(attrId);
            H5G.close(groupId);

            // Open dataset.
            dsetId = H5D.open(fileId, DSET1_NAME);

            // Create the dataspace for dataset's attribute.
            hssize_t[] attdims = { ATTR1_DIM };
            H5DataSpaceId attspaceId = H5S.create_simple(ATTR1_RANK, attdims);

            // Create an attribute for the dataset.
            attrId = H5A.create(dsetId, D1ATTR1_NAME, typeId, attspaceId);

            // Try to create the same attribute again (should fail.)
            try
            {
               H5AttributeId attr_twice = H5A.create(dsetId, D1ATTR1_NAME, typeId, attspaceId);

               // should fail, but didn't, print an error message.
               Console.WriteLine("\ntest_attr_basic_write: Attempting to create an existing attribute.");
               nerrors++;
            }
            catch (HDFException) { } // does nothing, it should fail

            // Write attribute information.
            int[] attr_data1 = new int[] { 512, -234, 98123 }; /* Test data for 1st attribute */
            H5A.write(attrId, typeId, new H5Array<int>(attr_data1));

            // Create another attribute for the dataset.
            H5AttributeId attr2Id = H5A.create(dsetId, D1ATTR2_NAME, typeId, attspaceId);

            // Write attribute information.
            int[] attr_data2 = new int[] { 256, 11945, -22107 };
            H5A.write(attr2Id, typeId, new H5Array<int>(attr_data2));

            // Read attribute information immediately, without closing attribute.
            int[] read_data1 = new int[3];
            H5A.read(attrId, typeId, new H5Array<int>(read_data1));

            // Verify values read in.
            int ii;
            for (ii = 0; ii < ATTR1_DIM; ii++)
               if (attr_data1[ii] != read_data1[ii])
               {
                  Console.WriteLine("\ntest_attr_basic_write: check1: read value differs from input: read {0} - input {1}", read_data1[ii], attr_data1[ii]);
                  nerrors++;
               }

            // Close attributes.
            H5A.close(attrId);
            H5A.close(attr2Id);

            // Open attribute again and verify its name.
            attrId = H5A.openIndex(dsetId, 0);

            string attr_name = H5A.getName(attrId);
            if (attr_name != D1ATTR1_NAME)
            {
               Console.WriteLine("\ntest_attr_basic_write: attribute name incorrect: is {0} - should be {1}", attr_name, D1ATTR1_NAME);
               nerrors++;
            }

            // Close attribute.
            H5A.close(attrId);

            // Open the second attribute again and verify its name.
            attr2Id = H5A.openIndex(dsetId, 1);
            attr_name = H5A.getName(attr2Id);
            if (attr_name != D1ATTR2_NAME)
            {
               Console.WriteLine("\ntest_attr_basic_write: attribute name incorrect: is {0} - should be {1}", attr_name, D1ATTR2_NAME);
               nerrors++;
            }
            // Close all objects.
            H5A.close(attr2Id);
            H5S.close(space1_Id);
            H5S.close(gspace_Id);
            H5D.close(dsetId);
            H5F.close(fileId);

            Console.WriteLine("\tPASSED");
         } // end try block
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
      } // test_attr_basic_write

      static void test_attr_basic_read()
      {
         try
         {
            Console.Write("Testing basic reading attribute functions");

            // Make an integer type object to use in various calls (instead of copying like in test_attr_basic_write)
            H5DataTypeId inttype = new H5DataTypeId(H5T.H5Type.NATIVE_INT);

            // Open file
            H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Open dataset DSET1_NAME.
            H5DataSetId dsetId = H5D.open(fileId, DSET1_NAME);

            // Verify the correct number of attributes.
            H5ObjectInfo oinfo = H5O.getInfo(dsetId);

            if (oinfo.nAttributes != 2)
            {
               Console.WriteLine("\ntest_attr_basic_read: incorrect number of attributes: read {0} - should be {1}",
                   oinfo.nAttributes, 2);
               nerrors++;
            }

            // Open first attribute for the dataset.
            H5AttributeId attrId = H5A.open(dsetId, D1ATTR1_NAME);

            // Read attribute data.
            int[] read_data1 = new int[3];
            H5A.read(attrId, inttype, new H5Array<int>(read_data1));

            // Verify values read in.
            int[] attr_data1 = new int[] { 512, -234, 98123 }; /* Test data for 1st attribute */
            int ii;
            for (ii = 0; ii < ATTR1_DIM; ii++)
               if (attr_data1[ii] != read_data1[ii])
               {
                  Console.WriteLine("\ntest_attr_basic_read:check2: read value differs from input: read {0} - input {1}", read_data1[ii], attr_data1[ii]);
                  nerrors++;
               }

            H5A.close(attrId);

            // Open second attribute for the dataset.
            attrId = H5A.open(dsetId, D1ATTR2_NAME);

            // Read attribute data.
            H5A.read(attrId, inttype, new H5Array<int>(read_data1));

            // Verify values read in.
            int[] attr_data2 = new int[] { 256, 11945, -22107 };  // Data to test second attribute of dataset.
            for (ii = 0; ii < ATTR1_DIM; ii++)
               if (attr_data2[ii] != read_data1[ii])
               {
                  Console.WriteLine("\ntest_attr_basic_read: check3: read value differs from input: read {0} - input {1}", read_data1[ii], attr_data2[ii]);
                  nerrors++;
               }

            // Close the attribute and dataset.
            H5A.close(attrId);
            H5D.close(dsetId);

            /* Checking group's attribute */

            // Open the group.
            H5GroupId groupId = H5G.open(fileId, GROUP1_NAME);

            // Verify the correct number of attributes for this group.
            oinfo = H5O.getInfo(groupId);
            if (oinfo.nAttributes != 1)
            {
               Console.WriteLine("\ntest_attr_basic_read: incorrect number of attributes: read {0} - should be {1}",
                   oinfo.nAttributes, 1);
               nerrors++;
            }

            // Open the attribute for the group.
            attrId = H5A.open(groupId, GATTR_NAME);

            // Read attribute information.
            int[,] read_data2 = new int[GATTR_DIM1, GATTR_DIM2];
            H5A.read(attrId, new H5DataTypeId(H5T.H5Type.NATIVE_INT), new H5Array<int>(read_data2));

            // Verify values read in.
            int jj;
            for (ii = 0; ii < GATTR_DIM1; ii++)
               for (jj = 0; jj < GATTR_DIM2; jj++)
               {
                  if (gattr_data[ii, jj] != read_data2[ii, jj])
                  {
                     Console.WriteLine("\ntest_attr_basic_read: check4: read value differs from input: read {0} - input {1}", read_data2[ii, jj], gattr_data[ii, jj]);
                     nerrors++;
                  }
               }

            // Close attribute, group, and file.
            H5A.close(attrId);
            H5G.close(groupId);
            H5F.close(fileId);

            Console.WriteLine("\t\tPASSED");
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
      } // test_attr_basic_read

      const string DSET2_NAME = "Dataset2";
      static void test_attr_plist()
      {
         try
         {
            Console.Write("Testing attribute property lists");
            hssize_t[] dims = { 256, 512 };

            const string PLST_FILE_NAME = ("tattr_plist.h5");
            hssize_t[] dims1 = { SPACE1_DIM1, SPACE1_DIM2, SPACE1_DIM3 };
            hssize_t[] dims2 = { ATTR1_DIM };

            // Create file.
            H5FileId fileId = H5F.create(PLST_FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            // Create dataspace for dataset.
            H5DataSpaceId space1_Id = H5S.create_simple(SPACE1_RANK, dims1);

            // Create a dataset.
            H5DataSetId dsetId = H5D.create(fileId, DSET1_NAME, H5T.H5Type.NATIVE_UCHAR, space1_Id);

            // Create dataspace for attribute.
            H5DataSpaceId space2_Id = H5S.create_simple(ATTR1_RANK, dims2);

            // Create default property list for attribute.
            H5PropertyListId plist
                = H5P.create(H5P.PropertyListClass.ATTRIBUTE_CREATE);

            // Create an attribute for the dataset using the property list.
            H5AttributeId attrId = H5A.create(dsetId, ATTR1_NAME, new H5DataTypeId(H5T.H5Type.NATIVE_INT), space2_Id, plist);

            // Close all objects.
            H5S.close(space1_Id);
            H5S.close(space2_Id);
            H5P.close(plist);
            H5A.close(attrId);
            H5D.close(dsetId);
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
      }  // test_attr_plist

      static void test_attr_compound_write()
      {
         try
         {
            Console.Write("Testing write attributes with compound datatype");

            const int NX = 256;   // data set dimension
            const int NY = 512;

            // Create a file.
            H5FileId fileId = H5F.create(COMP_FNAME, H5F.CreateMode.ACC_TRUNC);

            // Create dataspace for dataset.
            hssize_t[] dims = { NX, NY };
            H5DataSpaceId spaceId = H5S.create_simple(SPACE1_RANK, dims);

            // Create a dataset.
            H5DataSetId dsetId = H5D.create(fileId, DSET1_NAME, H5T.H5Type.NATIVE_UCHAR, spaceId);

            // Close dataset's dataspace
            H5S.close(spaceId);

            // this number 16 needs to be verified.
            // Create the attribute datatype.
            H5DataTypeId typeId = H5T.create(H5T.CreateClass.COMPOUND, 16);

            //tid1 = H5Tcreate(H5T_COMPOUND, sizeof(struct attr4_struct));
            int attr4_field1_off = 0;
            int attr4_field2_off = 1;
            int attr4_field3_off = 5;

            H5T.insert(typeId, "c", attr4_field1_off, H5T.H5Type.STD_U8LE);
            H5T.insert(typeId, "i", attr4_field2_off, H5T.H5Type.NATIVE_INT);
            H5T.insert(typeId, "l", attr4_field3_off, H5T.H5Type.STD_I64BE);

            // Create dataspace for first attribute.
            hssize_t[] dims2 = { ATTR4_DIM1, ATTR4_DIM2 };
            spaceId = H5S.create_simple(ATTR4_RANK, dims2);

            // Create complex attribute for the dataset.
            H5AttributeId attrId = H5A.create(dsetId, ATTR4_NAME, typeId, spaceId);

            // Try to create the same attribute again (should fail.)
            try
            {
               attrId = H5A.create(dsetId, ATTR4_NAME, typeId, spaceId);

               // should fail, but didn't, print an error message.
               Console.WriteLine("\ntest_attr_compound_write: Attempting to create an existing attribute.");
               nerrors++;
            }
            catch (HDFException) { } // does nothing, it should fail

            // Allocate space for the points & check arrays
            attr4_struct[,] attr_data4 = new attr4_struct[ATTR4_DIM1, ATTR4_DIM2];

            // Initialize the dataset
            int ii, jj, nn;
            for (ii = nn = 0; ii < ATTR4_DIM1; ii++)
            {
               for (jj = 0; jj < ATTR4_DIM2; jj++)
               {
                  attr_data4[ii, jj].c = 't';
                  attr_data4[ii, jj].i = nn++;
                  attr_data4[ii, jj].l = (ii * 10 + jj * 100) * nn;
               }
            }

            // Write complex attribute data.
            H5A.write(attrId, typeId, new H5Array<attr4_struct>(attr_data4));

            // Close all objects and file.
            H5A.close(attrId);
            H5S.close(spaceId);
            H5T.close(typeId);
            H5D.close(dsetId);
            H5F.close(fileId);

            Console.WriteLine("\t\tPASSED");
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
      }  // test_attr_compound_write

      static void test_attr_compound_read()
      {
         try
         {
            Console.Write("Testing read attribute with compound datatype");

            // Open file.
            H5FileId fileId = H5F.open(COMP_FNAME, H5F.OpenMode.ACC_RDWR);

            // Open the dataset.
            H5DataSetId dsetId = H5D.open(fileId, DSET1_NAME);

            // Verify the correct number of attributes for this dataset.
            H5ObjectInfo oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 1)
            {
               Console.WriteLine("\ntest_attr_basic_read: incorrect number of attributes: read {0} - should be {1}",
                   oinfo.nAttributes, 1);
               nerrors++;
            }

            // Open first attribute for the dataset.
            H5AttributeId attrId = H5A.openByIndex(dsetId, ".", H5IndexType.CRT_ORDER, H5IterationOrder.INCREASING, 0);

            // Verify dataspace.
            H5DataSpaceId spaceId = H5A.getSpace(attrId);

            int rank = H5S.getSimpleExtentNDims(spaceId);
            if (rank != ATTR4_RANK)
            {
               Console.WriteLine("\ntest_attr_compound_read: incorrect rank = {0} - should be {1}", rank, ATTR4_RANK);
               nerrors++;
            }

            long[] dims = H5S.getSimpleExtentDims(spaceId);
            if (dims[0] != ATTR4_DIM1)
            {
               Console.WriteLine("\ntest_attr_compound_read: incorrect dim[0] = {0} - should be {1}", dims[0], ATTR4_DIM1);
               nerrors++;
            }
            if (dims[1] != ATTR4_DIM2)
            {
               Console.WriteLine("\ntest_attr_compound_read: incorrect dim[1] = {0} - should be {1}", dims[1], ATTR4_DIM2);
               nerrors++;
            }

            // Close dataspace.
            H5S.close(spaceId);

            // Verify datatype of the attribute.
            H5DataTypeId typeId = H5A.getType(attrId);

            H5T.H5TClass t_class = H5T.getClass(typeId);
            if (t_class != H5T.H5TClass.COMPOUND)
            {
               Console.WriteLine("test_compound_dtypes: H5T.getMemberClass and H5T.getClass return different classes for the same type.");
               nerrors++;
            }
            int nfields = H5T.getNMembers(typeId);
            if (nfields != 3)
            {
               Console.WriteLine("test_compound_dtypes: H5T.getMemberClass and H5T.getClass return different classes for the same type.");
               nerrors++;
            }

            // Check name against this list
            string[] memb_names = { ATTR4_FIELDNAME1, ATTR4_FIELDNAME2, ATTR4_FIELDNAME3 };
            int[] memb_offsets = { 0, 1, 5 };   // list of member offsets

            H5DataTypeId mtypeId;   // member type
            H5T.H5TClass memb_cls1;  // member classes retrieved different ways
            string memb_name;       // member name
            int memb_idx;      // member index
            int memb_offset, idx;       // member offset, loop index

            // how to handle int versus uint for memb_idx and idx???

            // For each member, check its name, class, index, and size.
            for (idx = 0; idx < nfields; idx++)
            {
               // Get the type of the ith member to test other functions later.
               mtypeId = H5T.getMemberType(typeId, idx);

               // Get the name of the ith member.
               memb_name = H5T.getMemberName(typeId, idx);
               if (memb_name != memb_names[idx])
               {
                  Console.WriteLine("test_compound_dtypes: incorrect member name, {0}, for member no {1}", memb_name, idx);
                  nerrors++;
               }

               // Get the class of the ith member and then verify the class.
               memb_cls1 = H5T.getMemberClass(typeId, idx);
               if (memb_cls1 != H5T.H5TClass.INTEGER)
               {
                  Console.WriteLine("test_compound_dtypes: incorrect class, {0}, for member no {1}", memb_cls1, idx);
                  nerrors++;
               }

               // Get member's index back using its name and verify it.
               memb_idx = H5T.getMemberIndex(typeId, memb_name);
               if (memb_idx != idx)
               {
                  Console.WriteLine("test_attr_compound_read: H5T.getMemberName and/or H5T.getMemberIndex returned false values.");
                  nerrors++;
               }

               // Get member's offset and verify it.
               memb_offset = H5T.getMemberOffset(typeId, idx);
               if (memb_offset != memb_offsets[idx])
               {
                  Console.WriteLine("test_attr_compound_read: H5T.getMemberOffset returned incorrect value - {0}, should be {1}", memb_offset, memb_offsets[idx]);
                  nerrors++;
               }

               // Get member's size and verify it.
               int tsize = H5T.getSize(mtypeId);
               switch (idx)
               {
                  case 0:
                     if (tsize != H5T.getSize(H5T.H5Type.STD_U8LE))
                     {
                        Console.WriteLine("test_attr_compound_read: H5T.getSize returned incorrect value.");
                        nerrors++;
                     }
                     break;
                  case 1:
                     if (tsize != H5T.getSize(H5T.H5Type.NATIVE_INT))
                     {
                        Console.WriteLine("test_attr_compound_read: H5T.getSize returned incorrect value.");
                        nerrors++;
                     }
                     break;
                  case 2:
                     if (tsize != H5T.getSize(H5T.H5Type.STD_I64BE))
                     {
                        Console.WriteLine("test_attr_compound_read: H5T.getSize returned incorrect value.");
                        nerrors++;
                     }
                     break;
                  default:
                     Console.WriteLine("test_attr_compound_read: We should only have 3 members.");
                     nerrors++;
                     break;
               }  // end switch

               // Close current member type.
               H5T.close(mtypeId);
            }  // end for

            // Prepare the check array to verify read data.  It should be the same as the attr_data4 array
            // in the previous test function test_attr_compound_write.
            attr4_struct[,] check = new attr4_struct[ATTR4_DIM1, ATTR4_DIM2];

            // Initialize the dataset
            int ii, jj, nn;
            for (ii = nn = 0; ii < ATTR4_DIM1; ii++)
            {
               for (jj = 0; jj < ATTR4_DIM2; jj++)
               {
                  check[ii, jj].c = 't';
                  check[ii, jj].i = nn++;
                  check[ii, jj].l = (ii * 10 + jj * 100) * nn;
               }
            }

            // Read attribute information.
            attr4_struct[,] read_data4 = new attr4_struct[ATTR4_DIM1, ATTR4_DIM2];
            H5A.read(attrId, typeId, new H5Array<attr4_struct>(read_data4));

            // Verify values read in.
            for (ii = 0; ii < ATTR4_DIM1; ii++)
               for (jj = 0; jj < ATTR4_DIM2; jj++)
                  if ((check[ii, jj].c != read_data4[ii, jj].c) ||
                      (check[ii, jj].i != read_data4[ii, jj].i) ||
                      (check[ii, jj].l != read_data4[ii, jj].l))
                  {
                     Console.WriteLine("test_attr_compound_read: Incorrect read data: {0}, should be {1}", read_data4[ii, jj], check[ii, jj]);
                     nerrors++;
                  }

            // Close resources.
            H5T.close(typeId);
            H5A.close(attrId);
            H5D.close(dsetId);
            H5F.close(fileId);

            Console.WriteLine("\t\tPASSED");
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
      }  // test_attr_compound_read

      /*
       * Operator function.
       */
      /*        static int attr_op1(H5AttributeId id, string objectName, Object op_data)
              {
                  int *count = (int *)op_data;
                  int ret = 0;

                  switch(*count) {
                      case 0:
                          if(objectName != ATTR1_NAME)
                          {
                              Console.WriteLine("\nattr_op1: attribute name incorrect: is {0} - should be {1}", objectName, ATTR1_NAME);
                              (*count)++;
                          }
                          break;

                      case 1:
                          if(objectName != ATTR2_NAME)
                          {
                              Console.WriteLine("\nattr_op1: attribute name incorrect: is {0} - should be {1}", objectName, ATTR2_NAME);
                              (*count)++;
                          }
                          break;

                      case 2:
                          if(objectName != ATTR3_NAME)
                          {
                              Console.WriteLine("\nattr_op1: attribute name incorrect: is {0} - should be {1}", objectName, ATTR3_NAME);
                              (*count)++;
                          }
                          break;

                      default:
                          ret = -1;
                          break;
          }  /* end switch()

          return(ret);
      }*/

      // Function used with H5A.iterate
      static H5IterationResult MyH5AFunction(
         H5AttributeId attributeId,
         String attributeName,
   H5AttributeInfo info,
   Object attributeNames)
      {
         Console.WriteLine("\t\t{0}", attributeName);
         ArrayList nameList = (ArrayList)attributeNames;
         nameList.Add(attributeName);

         // Returning SUCCESS means that iteration should continue to the 
         // next attribute (if one exists).
         return H5IterationResult.SUCCESS;
      }

      static void test_attr_iterate()
      {
         try
         {
            Console.Write("Testing attribute iteration");

            // Open the file.
            H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Create a dataspace.
            H5DataSpaceId spaceId = H5S.create(H5S.H5SClass.SCALAR);

            // Create a new dataset using default properties.
            const string DSET2_NAME = ("Dataset2");
            H5DataSetId dsetId = H5D.create(fileId, DSET2_NAME, H5T.H5Type.NATIVE_INT, spaceId);

            // Close dataspace.
            H5S.close(spaceId);

            // Verify the correct number of attributes.
            H5ObjectInfo oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 0)
            {
               Console.WriteLine("\ntest_attr_iterate: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 1);
               nerrors++;
            }

            // Iterate through the attributes.
            hssize_t position = 0;
            H5AIterateCallback attributeCallback;
            attributeCallback = MyH5AFunction;
            H5ObjectInfo groupInfo = H5O.getInfo(dsetId);

            // While iterating, collect the names of all the attributes.
            ArrayList attributeNames = new ArrayList();
            Console.WriteLine();
            Console.WriteLine("\tIterating through attributes:");
            H5A.iterate(dsetId, H5IndexType.CRT_ORDER,
                        H5IterationOrder.INCREASING,
                        ref position, attributeCallback,
                        (object)attributeNames);

            // Close dataset.
            H5D.close(dsetId);

            // Open existing dataset with attributes.
            dsetId = H5D.open(fileId, DSET1_NAME);

            // Iterate through the attributes of dataset DSET1_NAME.
            position = 0;
            attributeCallback = MyH5AFunction;
            groupInfo = H5O.getInfo(dsetId);

            // While iterating, collect the names of all the attributes.
            attributeNames = new ArrayList();
            H5A.iterate(dsetId, H5IndexType.CRT_ORDER,
                        H5IterationOrder.INCREASING,
                        ref position, attributeCallback,
                        (object)attributeNames);

            // Verify the correct number of attributes.
            oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 2)
            {
               Console.WriteLine("\ntest_attr_iterate: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 2);
               nerrors++;
            }

            // Close dataset and file.
            H5D.close(dsetId);
            H5F.close(fileId);

            Console.WriteLine("\tPASSED");
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
      }

      static void test_attr_delete()
      {
         try
         {
            Console.Write("Testing deleting attributes");

            // Open file.
            H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

            // Open the dataset.
            H5DataSetId dsetId = H5D.open(fileId, DSET1_NAME);

            // Verify the correct number of attributes for this dataset.
            H5ObjectInfo oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 2)
            {
               Console.WriteLine("\ntest_attr_delete: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 2);
               nerrors++;
            }

            // Try to delete non-existing attribute, should fail.
            try
            {
               H5A.Delete(dsetId, "Bogus");

               // should fail, but didn't, print an error message.
               Console.WriteLine("\ntest_attr_delete: Attempting to delete a non-existing attribute, Bogus.");
               nerrors++;
            }
            catch (HDFException) { } // does nothing, it should fail

            // Verify the correct number of attributes after the false deletion.
            oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 2)
            {
               Console.WriteLine("\ntest_attr_delete: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 2);
               nerrors++;
            }

            // Delete middle (2nd) attribute.
            H5A.Delete(dsetId, D1ATTR2_NAME);

            // Verify the correct number of attributes after the deletion, checking both functions.
            oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 1)
            {
               Console.WriteLine("\ntest_attr_delete: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 1);
               nerrors++;
            }

            // Open first attribute for the dataset.
            H5AttributeId attrId = H5A.openByIndex(dsetId, ".", H5IndexType.CRT_ORDER, H5IterationOrder.INCREASING, 0);

            // Verify attribute name.
            string attr_name = H5A.getName(attrId);
            if (attr_name != D1ATTR1_NAME)
            {
               Console.WriteLine("\ntest_delete_attr: attribute name different: {0}, should be {1}", attr_name, ATTR1_NAME);
               nerrors++;
            }
            // Close first attribute.
            H5A.close(attrId);

            // Delete first attribute.
            H5A.Delete(dsetId, D1ATTR1_NAME);

            // Verify that there are no more attribute for this dataset.
            oinfo = H5O.getInfo(dsetId);
            if (oinfo.nAttributes != 0)
            {
               Console.WriteLine("\ntest_attr_basic_read: incorrect number of attributes: read {0} - should be {1}",
                       oinfo.nAttributes, 0);
               nerrors++;
            }

            // Close dataset and file.
            H5D.close(dsetId);
            H5F.close(fileId);

            Console.WriteLine("\t\t\t\tPASSED");
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
      }

      static void Main(string[] args)
      {
         Console.WriteLine();
         Console.WriteLine("TEST: HDF5DotNet Attribute API");
         Console.WriteLine();
         try
         {
            // Suppress error printing from the C library.
            H5E.suppressPrinting();

            test_attr_basic_write();     // test basic writing attributes
            test_attr_basic_read();      // test basic reading attributes
            test_attr_plist();        // test attribute property lists
            test_attr_compound_write();  // test writing compound values to attributes
            test_attr_compound_read();   // test reading compound values from attributes
            test_attr_iterate();         // test iterating attributes
            test_attr_delete();          // test deleting attributes
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
            Console.WriteLine("Test(s) failed: ", nerrors, "occurred!");
         else
            Console.WriteLine("---- All attribute tests passed.");
         Console.WriteLine();
      }
   }
}
