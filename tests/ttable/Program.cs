using System;
using System.Collections.Generic;
using System.Text;
using HDF5DotNet;

namespace ttable
{
    using hsize_t = UInt64;
    using hssize_t = Int64;
    using uchar = System.Char;

    class Program
    {
        const int DIM0 = 1;
        const int DIM1 = 2;
        const string TABLE_NAME = "Table 1";
        const string FILE_NAME = "test_table.h5";
        const int N_RECORDS = 5; // number of records in the table
        const int N_FIELDS = 3; // number of fields
        static int nerrors = 0; // number of errors so far
        const int s1_size = 16; // pre-calculated size of struct s1
        struct s1
        {
            public char c;
            public uint i;
            public long l;
        };
        
        static void make_table()
        {
            try
            {
                Console.Write("Making a table for testing");

                uint ii, nn;
                long[] offsets = { 0, 1, 5 };
                long[] count = { N_RECORDS };
                string[] field_names = { "c", "i", "l" };

                // Allocate space for the points array
                s1[] points = new s1[DIM0];

                // Initialize the dataset
                for (ii = nn = 0; ii < DIM0; ii++)
                {
                    points[ii].c = 't';
                    points[ii].i = nn++;
                    points[ii].l = (ii * 10) * nn;
                }

                // Create the file.
                H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

                hssize_t[] dims = { N_RECORDS };
                H5DataSpaceId spaceId = H5S.create_simple(1, dims);

                // Create the memory data type.
                H5DataTypeId typeId = H5T.create(H5T.CreateClass.COMPOUND, 16);

                // Insert members.
                H5T.insert(typeId, field_names[0], 0, H5T.H5Type.STD_U8LE);
                H5T.insert(typeId, field_names[1], 1, H5T.H5Type.STD_U32LE);
                H5T.insert(typeId, field_names[2], 5, H5T.H5Type.STD_I64BE);

                // Create the dataset.
                H5DataSetId dsetId = H5D.create(fileId, TABLE_NAME, typeId, spaceId);

                // Define a hyperslab in the dataset of the size of the records */
                H5S.selectHyperslab(spaceId, H5S.SelectOperator.SET, offsets, count);

                // Write the dataset.
                H5D.write(dsetId, typeId, spaceId, spaceId, new H5PropertyListId(H5P.Template.DEFAULT), new H5Array<s1>(points));

                // Close resources.
                H5D.close(dsetId);
                H5S.close(spaceId);
                H5T.close(typeId);
                H5F.close(fileId);

                Console.WriteLine("\t\t\t\tPASSED");
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
        } // make_table

        static void test_getting_info()
        {
            try
            {
                Console.Write("Testing getting table/field information");

                // Open the file to check on the table.
                H5FileId fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDWR);

                hssize_t nfields = 0, nrecords = 0;
                string[] field_names = { "c", "i", "l" };

                // Get the table info.
                TableInfo table = H5TB.getTableInfo(fileId, TABLE_NAME);

                if (table.nFields != N_FIELDS)
                {
                    Console.WriteLine("\ntest_getting_info: incorrect number of fields: read {0} - should be {1}",
                        nfields, N_FIELDS);
                    nerrors++;
                }
                if (table.nRecords != N_RECORDS)
                {
                    Console.WriteLine("\ntest_getting_info: incorrect number of fields: read {0} - should be {1}",
                        nrecords, N_RECORDS);
                    nerrors++;
                }

                // Get field info.
                int []sizes = new int[N_FIELDS];
                int []offsets = new int[N_FIELDS];
                TableFieldInfo tablefield = H5TB.getFieldInfo(fileId, TABLE_NAME);

                int ii;
                for (ii = 0; ii < N_FIELDS; ii++)
                {
                    if (tablefield.fieldName[ii] != field_names[ii])
                    {
                        Console.WriteLine("\ntest_getting_info: field #{0} has incorrect name: read {0} - should be {1}",
                            ii, field_names[ii], tablefield.fieldName[ii]);
                        nerrors++;
                    }
                }

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
        } // test_getting_info

        static void Main(string[] args)
        {
           Console.WriteLine();
           Console.WriteLine("TEST: HDF5DotNet High-level Table API");
           Console.WriteLine();
           try
            {
                // Suppress error printing from the C library.
                H5E.suppressPrinting();

                make_table();           // create and write to a table to test
                test_getting_info();    // test getting table and field info
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
                Console.WriteLine("---- All table tests passed.");
            Console.WriteLine();
        }
    }
}
