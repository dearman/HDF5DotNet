using System;
using System.Collections.Generic;
using System.Text;
using HDF5DotNet;

namespace dtypes
{
   using hsize_t = UInt64;
   using hssize_t = Int64;

   class Program
   {
      const int DIM0 = 3;
      const int DIM1 = 5;
      static int nerrors = 0;
      struct s1
      {
         public char c;
         public uint i;
         public long l;
      };

      static IntPtr crtHeapAllocate(IntPtr size, IntPtr allocInfo)
      {
         return H5CrtHeap.Allocate(size);
      }

      static void crtHeapFree(IntPtr memory, IntPtr info)
      {
         H5CrtHeap.Free(memory);
      }

      static void test_classes()
      {
         try
         {
            Console.Write("Testing datatype classes");

            /*-------------------------------------------------------------
             *  Check class of some atomic types.
             *-----------------------------------------------------------*/
            H5T.H5TClass tcls = H5T.getClass(H5T.H5Type.NATIVE_INT);
            if (tcls != H5T.H5TClass.INTEGER)
            {
               Console.WriteLine("Test class should have been H5T_INTEGER");
               nerrors++;
            }

            tcls = H5T.getClass(H5T.H5Type.NATIVE_DOUBLE);
            if (tcls != H5T.H5TClass.FLOAT)
            {
               Console.WriteLine("Test class should have been H5T_FLOAT");
               nerrors++;
            }

            H5DataTypeId op_type = H5T.create(H5T.CreateClass.OPAQUE, 1);
            tcls = H5T.getClass(op_type);
            if (tcls != H5T.H5TClass.OPAQUE)
            {
               Console.WriteLine("Test class should have been H5T_OPAQUE");
               nerrors++;
            }

            // Create a VL datatype of char.  It should be a VL, not a string class.
            H5DataTypeId vlcId = H5T.vlenCreate(H5T.H5Type.NATIVE_UCHAR);

            // Make certain that the correct classes can be detected
            tcls = H5T.getClass(vlcId);
            if (tcls != H5T.H5TClass.VLEN)
            {
               Console.WriteLine("Test class should have been H5T_VLEN");
               nerrors++;
            }

            // Make certain that an incorrect class is not detected */
            if (tcls == H5T.H5TClass.STRING)
            {
               Console.WriteLine("Test class should not be H5T_STRING");
               nerrors++;
            }

            // Create a VL string.  It should be a string, not a VL class.
            H5DataTypeId vlsId = H5T.copy(H5T.H5Type.C_S1);
            H5T.setSize(vlsId, -1); // for H5T_VARIABLE
            tcls = H5T.getClass(vlsId);
            if (tcls != H5T.H5TClass.STRING)
            {
               Console.WriteLine("Test class should have been H5T_STRING");
               nerrors++;
            }
            if (tcls == H5T.H5TClass.VLEN)
            {
               Console.WriteLine("Test class should not be H5T_VLEN");
               nerrors++;
            }

            // Check that this is a variable-length string.
            if (!H5T.isVariableString(vlsId))
            {
               Console.WriteLine("This type should be a variable-length string");
               nerrors++;
            }

            // Close datatype
            H5T.close(vlcId);

            Console.WriteLine("\t\t\t\tPASSED");
         } // end of try block
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
      }  // end of test_classes

      static void test_integer_dtype()
      {
         const string GEN_FILE_NAME = "gen_types.h5";
         const string INT_TYPE_NAME = "new integer type 1";
         try
         {
            Console.Write("Testing getting some integer information");

            H5FileId genfileId = H5F.open(GEN_FILE_NAME, H5F.OpenMode.ACC_RDONLY);

            // Open the datatype to check.
            H5DataTypeId dtypeId = H5T.open(genfileId, INT_TYPE_NAME);

            int offset = H5T.getOffset(dtypeId);
            if (offset != 0)
            {
               Console.WriteLine("Incorrect offset: {0}, should be {1}", offset, 0);
               nerrors++;
            }
            int size = H5T.getSize(dtypeId);
            if (size != 3)
            {
               Console.WriteLine("Incorrect size: {0}, should be {1}", size, 3);
               nerrors++;
            }

            // Close datatype and file.
            H5T.close(dtypeId);
            H5F.close(genfileId);

            Console.WriteLine("\t\tPASSED");
         } // end of try block
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
      }  // test_integer_dtype

      static void test_float_dtype()
      {
         try
         {
            Console.Write("Testing getting some floating-point information");

            const string GEN_FILE_NAME = "gen_types.h5";
            const string FLOAT_TYPE_NAME = "new float type 1";

            // Open file pre-generated by a C program.
            H5FileId genfileId = H5F.open(GEN_FILE_NAME, H5F.OpenMode.ACC_RDONLY);

            // Open the datatype to check.
            H5DataTypeId dtypeId = H5T.open(genfileId, FLOAT_TYPE_NAME);

            // Get and check fields.
            H5FloatingBitFields fields = H5T.getFields(dtypeId);

            if (fields.signBitPosition != 44)
            {
               Console.WriteLine("Incorrect sign bit position: {0}, should be {1}", fields.signBitPosition, 44);
               nerrors++;
            }
            if (fields.exponentBitPosition != 34)
            {
               Console.WriteLine("Incorrect exponential bit position: {0}, should be {1}", fields.exponentBitPosition, 34);
               nerrors++;
            }
            if (fields.nExponentBits != 10)
            {
               Console.WriteLine("Incorrect size of exponent: {0}, should be {1}", fields.nExponentBits, 10);
               nerrors++;
            }
            if (fields.mantissaBitPosition != 3)
            {
               Console.WriteLine("Incorrect mantissa bit-position: {0}, should be {1}", fields.mantissaBitPosition, 3);
               nerrors++;
            }
            if (fields.nMantissaBits != 31)
            {
               Console.WriteLine("Incorrect size of mantissa: {0}, should be {1}", fields.nMantissaBits, 44);
               nerrors++;
            }

            // Check precision.
            int precision = H5T.getPrecision(dtypeId);
            if (precision != 42)
            {
               Console.WriteLine("Incorrect precision: {0}, should be {1}", precision, 42);
               nerrors++;
            }

            // Check offset.
            int offset = H5T.getOffset(dtypeId);
            if (offset != 3)
            {
               Console.WriteLine("Incorrect offset: {0}, should be {1}", offset, 3);
               nerrors++;
            }

            // Check norm.
            H5T.Norm norm = H5T.getNorm(dtypeId);
            if (norm != H5T.Norm.IMPLIED)  // need to be determined, not really 3
            {
               Console.WriteLine("Incorrect norm: {0}, should be {1}", norm, H5T.Norm.IMPLIED);
               nerrors++;
            }

            // Check size.
            int size = H5T.getSize(dtypeId);
            if (size != 7)
            {
               Console.WriteLine("Incorrect size: {0}, should be {1}", size, 7);
               nerrors++;
            }
            // Close datatype and file.
            H5T.close(dtypeId);
            H5F.close(genfileId);

            Console.WriteLine("\t\tPASSED");
         } // end of try block
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
      }  // end of test_float_dtype

      const string DSET_ENUM_NAME = "Enum Dataset";
      static void test_enum_dtype(H5FileId fileId)
      {
         short i, j;
         string[] mname = { "RED", "GREEN", "BLUE", "YELLOW", "PINK", "PURPLE", "ORANGE", "WHITE" };
         short[,] spoints2 = new short[DIM0, DIM1];
         short[,] scheck2 = new short[DIM0, DIM1];
         try
         {
            Console.Write("Testing enumeration datatypes");

            // Create the data space */
            hssize_t[] dims = { DIM0, DIM1 };
            H5DataSpaceId dspace = H5S.create_simple(2, dims);

            // Construct enum type based on native type
            H5DataTypeId etype = H5T.enumCreate(H5T.H5Type.NATIVE_SHORT);

            // Insert members to type.
            for (i = 0; i < 8; i++)
            {
               H5T.enumInsert(etype, mname[i], ref i);
            }

            // Assign a name to the enum type, close it, and open it by name.
            H5T.commit(fileId, "Color Type", etype);
            H5T.close(etype);
            H5DataTypeId color_type = H5T.open(fileId, "Color Type");

            // Check its class
            H5T.H5TClass tcls = H5T.getClass(color_type);
            if (tcls != H5T.H5TClass.ENUM)
               Console.WriteLine("test_enum: class of color_type = {0} is incorrect, should be ENUM", tcls);

            // Create the dataset
            H5DataSetId dsetId = H5D.create(fileId, DSET_ENUM_NAME, color_type, dspace);

            // Construct enum type based on native type in memory.
            H5DataTypeId etype_m = H5T.enumCreate(H5T.H5Type.NATIVE_SHORT);

            // Insert members to type.
            for (i = 0; i < 8; i++)
            {
               H5T.enumInsert(etype_m, mname[i], ref i);
            }

            // Initialize the dataset and buffer.
            for (i = 0; i < DIM0; i++)
            {
               for (j = 0; j < DIM1; j++)
               {
                  spoints2[i, j] = i;
                  scheck2[i, j] = 0;
               }
            }
            // Write the data to the dataset.
            H5D.write(dsetId, etype_m, new H5Array<short>(spoints2));

            // Close objects.
            H5D.close(dsetId);
            H5T.close(color_type);
            H5S.close(dspace);
            H5T.close(etype_m);

            // Open dataset again to check the type.
            dsetId = H5D.open(fileId, DSET_ENUM_NAME);

            // Get dataset's datatype.
            H5DataTypeId dstype = H5D.getType(dsetId);

            // Get the datatype's class and check that it is of class ENUM.
            H5T.H5TClass tclass = H5T.getClass(dstype);
            if (tclass != H5T.H5TClass.ENUM)
            {
               Console.WriteLine("Type should be an enum class");
               nerrors++;
            }

            // Check name of an enum value.
            int memb_num = 2;
            string memb_name = H5T.enumNameOf(dstype, ref memb_num);
            if (memb_name != "BLUE")
            {
               Console.WriteLine("Member name of value 2 should be BLUE");
               nerrors++;
            }

            // Check value of an enum name.
            int memb_value = 0;
            H5T.enumValueOf(dstype, memb_name, out memb_value);
            if (memb_value != 2)
            {
               Console.WriteLine("Member value of BLUE should be 2");
               nerrors++;
            }

            // Check member's value by member number.
            H5T.getMemberValue(dstype, 4, out memb_value);

            // Read data back.
            H5D.read(dsetId, dstype, new H5Array<short>(scheck2));

            // Close objects.
            H5D.close(dsetId);
            H5T.close(dstype);

            Console.WriteLine("\t\t\t\tPASSED");
         } // end of try block
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
      }  // end of test_enum_dtype

      const string DSET_COMPOUND_NAME = "Compound Dataset";
      static void test_compound_dtype(H5FileId fileId)
      {
         uint i, j, n;
         try
         {
            Console.Write("Testing compound datatypes");

            // Allocate space for the points & check arrays
            s1[,] points = new s1[DIM0, DIM1];
            s1[,] check = new s1[DIM0, DIM1];

            // Initialize the dataset
            for (i = n = 0; i < DIM0; i++)
            {
               for (j = 0; j < DIM1; j++)
               {
                  points[i, j].c = 't';
                  points[i, j].i = n++;
                  points[i, j].l = (i * 10 + j * 100) * n;
               }
            }

            // Create the data space
            hssize_t[] dims = { DIM0, DIM1 };
            H5DataSpaceId spaceId = H5S.create_simple(2, dims);

            // Create compound datatype for disk storage
            H5DataTypeId typeId = H5T.create(H5T.CreateClass.COMPOUND, 16);

            // Insert members
            H5T.insert(typeId, "c", 0, H5T.H5Type.STD_U8LE);
            H5T.insert(typeId, "i", 1, H5T.H5Type.STD_U32LE);
            H5T.insert(typeId, "l", 5, H5T.H5Type.STD_I64BE);

            // Create the dataset
            H5DataSetId dsetId = H5D.create(fileId, DSET_COMPOUND_NAME, typeId, spaceId);

            // Write the dataset
            H5D.write(dsetId, typeId, new H5Array<s1>(points));

            // Close dataset and dataspace
            H5D.close(dsetId);
            H5S.close(spaceId);
            H5T.close(typeId);

            // Open dataset again to check various functions.
            dsetId = H5D.open(fileId, DSET_COMPOUND_NAME);

            // Get its type and native type.
            H5DataTypeId dset_typeId = H5D.getType(dsetId);
            H5DataTypeId native_type = H5T.getNativeType(dset_typeId, H5T.Direction.DEFAULT);

            // Check name against this list
            string[] memb_names = { "c", "i", "l" };
            int[] memb_offsets = { 0, 1, 5 };

            H5DataTypeId mtypeId;   // member type
            H5T.H5TClass memb_cls1, memb_cls2;  // member classes retrieved different ways
            string memb_name;       // member name
            int memb_idx;           // member index

            // Get the number of members in the type.
            int nmembers = H5T.getNMembers(native_type);

            // For each member, check its name, class, index, and size.
            for (int ii = 0; ii < nmembers; ii++)
            {
               // Get the type of the ith member.
               mtypeId = H5T.getMemberType(native_type, ii);

               // Get the name of the ith member.
               memb_name = H5T.getMemberName(native_type, ii);
               if (memb_name != memb_names[ii])
               {
                  Console.WriteLine("test_compound_dtypes: incorrect member name, {0}, for member no {1}", memb_name, i);
                  nerrors++;
               }

               // Get the class of the ith member and then verify the class.
               memb_cls1 = H5T.getMemberClass(native_type, ii);
               if (memb_cls1 != H5T.H5TClass.INTEGER)
               {
                  Console.WriteLine("test_compound_dtypes: incorrect class, {0}, for member no {1}", memb_cls1, ii);
                  nerrors++;
               }

               // Get the class via type id
               memb_cls2 = H5T.getClass(mtypeId);
               if (memb_cls1 != memb_cls2)
               {
                  Console.WriteLine("test_compound_dtypes: H5T.getMemberClass and H5T.getClass return different classes for the same type.");
                  nerrors++;
               }

               // Get member's index back from its name and verify it.
               memb_idx = H5T.getMemberIndex(dset_typeId, memb_name);
               if (memb_idx != ii)
               {
                  Console.WriteLine("test_compound_dtypes: H5T.getMemberName and/or H5T.getMemberIndex returned false values.");
                  nerrors++;
               }

               // Get member's offset and verify it.
               int memb_offset = H5T.getMemberOffset(dset_typeId, ii);
               if (memb_offset != memb_offsets[ii])
               {
                  Console.WriteLine("test_compound_dtypes: Incorrect offset value {0}, should be {1}.", memb_offset, memb_offsets[ii]);
                  nerrors++;
               }

               // Get size of the member's type and verify it.
               int tsize = H5T.getSize(mtypeId);
               switch (ii)
               {
                  case 0:
                     //Console.WriteLine("tsize = {0}, STD_U8LE = {1}", tsize, H5T.getSize(H5T.H5Type.STD_U8LE));
                     if (tsize != H5T.getSize(H5T.H5Type.STD_U8LE))
                     {
                        Console.WriteLine("test_compound_dtypes: First member has incorrect size");
                        nerrors++;
                     }
                     break;
                  case 1:
                     if (tsize != H5T.getSize(H5T.H5Type.STD_U32LE))
                     {
                        Console.WriteLine("test_compound_dtypes: Second member has incorrect size");
                        nerrors++;
                     }
                     break;
                  case 2:
                     if (tsize != H5T.getSize(H5T.H5Type.STD_I64BE))
                     {
                        Console.WriteLine("test_compound_dtypes: Third member has incorrect size");
                        nerrors++;
                     }
                     break;
                  default:
                     Console.WriteLine("test_compound_dtypes: Only 3 members.");
                     break;
               }  // end switch

               // Close current member type.
               H5T.close(mtypeId);
            }  // end for

            // Close objects.
            H5T.close(dset_typeId);
            H5T.close(native_type);
            H5D.close(dsetId);

            Console.WriteLine("\t\t\t\tPASSED");
         } // end of try block
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
      } // test_compound_dtype

      static void test_vlen_dtype(H5FileId fileId)
      {
         try
         {
            Console.Write("Testing variable-length datatypes");

            // Create a VL datatype of int.
            H5DataTypeId vltId = H5T.vlenCreate(H5T.H5Type.NATIVE_UINT);

            // Make certain that the correct classes can be detected
            H5T.H5TClass tcls = H5T.getClass(vltId);
            if (tcls != H5T.H5TClass.VLEN)
            {
               Console.WriteLine("Test class should have been H5T_VLEN");
               nerrors++;
            }

            // Create a dataset with a simple dataspace.
            hssize_t[] dims = { DIM1 };
            H5DataSpaceId spaceId = H5S.create_simple(1, dims);
            H5DataSetId dsetId = H5D.create(fileId, "Vlen Dataset", vltId, spaceId);

            // Change to the custom memory allocation routines for reading VL data.
            H5PropertyListId xferpId
                = H5P.create(H5P.PropertyListClass.DATASET_XFER);

            // Writing
            unsafe
            {
               hvl_t[] wdata = new hvl_t[DIM1];   /* Information to write */
               hvl_t[] wdata2 = new hvl_t[DIM1];  /* Information to write */
               hvl_t[] rdata = new hvl_t[DIM1];   /* Information read in */

               /* Allocate and initialize VL data to write */
               for (uint ii = 0; ii < DIM1; ii++)
               {
                   IntPtr iPtr = new IntPtr((ii + 1) * sizeof(uint));
                  wdata[ii].p = H5CrtHeap.Allocate(iPtr).ToPointer();
                  wdata[ii].len = ii + 1;
                  ((uint*)wdata[ii].p)[0] = ii * 10;

                  wdata2[ii].p = (void*)0;
                  wdata2[ii].len = 0;
               } /* end for */

               H5D.write(dsetId, vltId, new H5Array<hvl_t>(wdata));

               // Read from dataset before writing data.
               H5D.read(dsetId, vltId, new H5Array<hvl_t>(rdata));

               // Write "nil" data to disk.
               H5D.write(dsetId, vltId, new H5Array<hvl_t>(wdata2));

               // Read from dataset with "nil" data.
               H5D.read(dsetId, vltId, new H5Array<hvl_t>(rdata));

               // Check data read in.

               // Write data to dataset.
               H5D.write(dsetId, vltId, new H5Array<hvl_t>(wdata));

               // Close resources.
               H5D.close(dsetId);
               H5T.close(vltId);
               H5S.close(spaceId);

               // Open the dataset.
               dsetId = H5D.open(fileId, "Vlen Dataset");

               // Get dataspace and datatype for the dataset.
               spaceId = H5D.getSpace(dsetId);
               vltId = H5D.getType(dsetId);

               H5AllocCallback allocCallback =
                  new H5AllocCallback(Program.crtHeapAllocate);

               H5FreeCallback freeCallback =
                  new H5FreeCallback(Program.crtHeapFree);

               H5P.setVlenMemManager(xferpId,
                  allocCallback,
                  IntPtr.Zero,
                  freeCallback,
                  IntPtr.Zero);

               // Read dataset from disk.
               H5D.read(dsetId, vltId, new H5DataSpaceId(H5S.H5SType.ALL), new H5DataSpaceId(H5S.H5SType.ALL), xferpId, new H5Array<hvl_t>(rdata));

               // Reclaim the read VL data.
               H5D.vlenReclaim(vltId, spaceId, xferpId, new H5Array<hvl_t>(rdata));
            } // end of unsafe

            // Close resources.
            H5D.close(dsetId);
            H5T.close(vltId);
            H5S.close(spaceId);
            H5P.close(xferpId);

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
      } // test_vlen_dtype

      static void test_copy()
      {
         try
         {
            Console.Write("Testing copying datatypes");

            // Make a copy of a predefined type.
            H5DataTypeId inttype = H5T.copy(H5T.H5Type.NATIVE_INT);
            int intsize = H5T.getSize(inttype);

            // Make a copy of that type.
            H5DataTypeId tcopy1 = H5T.copy(inttype);
            int tcopy1_size = H5T.getSize(tcopy1);

            // The sizes of the copies should be the same.
            if (intsize != tcopy1_size)
            {
               Console.WriteLine("test_copy: copy types incorrectly");
               nerrors++;
            }

            // Close second type
            H5T.close(tcopy1);

            /*
             * Test copy a datatype from a dataset.
             */
            // Create a new file.
            H5FileId fileId = H5F.create("sometypes.h5", H5F.CreateMode.ACC_TRUNC);

            // Create a dataset with a simple dataspace.
            hssize_t[] dims = { DIM0, DIM1 };
            H5DataSpaceId dspace = H5S.create_simple(2, dims);
            H5DataSetId dset = H5D.create(fileId, "test_types", inttype, dspace);

            // Obtain the datatype from the dataset.
            H5DataTypeId dstype = H5T.copy(dset);

            // Check this datatype's class, size, and sign.
            H5T.H5TClass tclass = H5T.getClass(dstype);
            if (tclass != H5T.H5TClass.INTEGER)
            {
               Console.WriteLine("test_copy: copy of dataset's datatype has incorrect class");
               nerrors++;
            }

            int tsize = H5T.getSize(dstype);
            if (tsize != intsize)
            {
               Console.WriteLine("test_copy: copy of dataset's datatype has incorrect size");
               nerrors++;
            }

            H5T.Sign tsign = H5T.getSign(dstype);
            if (tsign != H5T.Sign.TWOS_COMPLEMENT)
            {
               Console.WriteLine("test_copy: copy of dataset's datatype has incorrect sign, {0}", tsign);
               nerrors++;
            }

            // Close objects.
            H5T.close(inttype);
            H5S.close(dspace);
            H5T.close(dstype);
            H5D.close(dset);
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
      } // test_copy

      static void Main(string[] args)
      {
         Console.WriteLine();
         Console.WriteLine("TEST: HDF5DotNet Datatype API");
         Console.WriteLine();
         try
         {
            // Suppress error printing from the C library.
            H5E.suppressPrinting();

            // Create the file
            H5FileId fileId = H5F.create("test_types.h5", H5F.CreateMode.ACC_TRUNC);

            // Invokes individual datatype tests
            test_classes();
            test_integer_dtype();
            test_float_dtype();
            test_compound_dtype(fileId);
            test_enum_dtype(fileId);
            test_vlen_dtype(fileId);
            test_copy();

            // Close the file
            H5F.close(fileId);
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

         // Report results.
         Console.WriteLine();
         if (nerrors > 0)
            Console.WriteLine("Test(s) failed: {0}", nerrors, "occurred!");
         else
            Console.WriteLine("---- All datatype tests passed.");
         Console.WriteLine();
      }
   }
}
