using System;
using System.Collections.Generic;
using System.Text;
using HDF5DotNet;

namespace tproplists
{
   using hsize_t = UInt64;
   using hssize_t = Int64;
   using uchar = System.Char;

   class Program
   {
      const int DSET_DIM1 = 1;
      const int DSET_DIM2 = 2;
      static int nerrors = 0;

      static void test_buffer()
      {
         try
         {
            Console.Write("Testing setting buffer");

            const string FILE_NAME = ("SDStwodim.h5");
            const string DSET_NAME = ("Two-dim IntArray");
            const int NX = 5;   // data set dimension
            const int NY = 2;
            const int RANK = 2; // two-dimension

            // Data and input buffer initialization.
            int i, j;
            int[,] data = new int[NX, NY];
            for (i = 0; i < NX; i++)
               for (j = 0; j < NY; j++)
                  data[i, j] = i + j;

            // Create a new file using H5F_ACC_TRUNC access,
            // default file creation properties, and default file
            // access properties.
            H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            // Describe the size of the array and create the data space for fixed
            // size dataset.
            long[] dims = new long[RANK];
            dims[0] = NX;
            dims[1] = NY;
            H5DataSpaceId dspaceId = H5S.create_simple(RANK, dims);

            // Define datatype for the data in the file.
            H5DataTypeId dtypeId = H5T.copy(H5T.H5Type.NATIVE_INT);

            // Create a dataset property list.
            H5PropertyListId xferId
                = H5P.create(H5P.PropertyListClass.DATASET_XFER);

            // Create a small conversion buffer.
            unsafe
            {
               IntPtr tconv_buf = H5CrtHeap.Allocate(new IntPtr(1000));

               // Set buffer size.
               H5P.setBuffer(xferId, 1000, tconv_buf, IntPtr.Zero);

               // Create the data set DATASETNAME.
               H5DataSetId dsetId = H5D.create(fileId, DSET_NAME, dtypeId, dspaceId);

               // Write the one-dimensional data set array
               H5DataSpaceId H5S_ALL = new H5DataSpaceId(H5S.H5SType.ALL);
               H5D.write(dsetId, new H5DataTypeId(H5T.H5Type.NATIVE_INT), H5S_ALL, H5S_ALL, xferId, new H5Array<int>(data));

               // Read data back.
               int[,] outdata = new int[NX, NY];
               H5D.read(dsetId, new H5DataTypeId(H5T.H5Type.NATIVE_INT), H5S_ALL, H5S_ALL, xferId, new H5Array<int>(outdata));

               // Compare against input buffer to verify.
               for (i = 0; i < NX; i++)
                  for (j = 0; j < NY; j++)
                  {
                     if (outdata[i, j] != data[i, j])
                     {
                        Console.WriteLine("\ntest_twodim_array: read value differs from input: read {0} - input {1}",
                            outdata[i, j], data[i, j]);
                        nerrors++;
                     }
                  }

               // Close all objects and file.
               H5D.close(dsetId);
               H5T.close(dtypeId);
               H5S.close(dspaceId);
               H5P.close(xferId);
               H5F.close(fileId);

               // Free the buffer.
               H5CrtHeap.Free(tconv_buf);
            } // end unsafe block

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
      }  // test_buffer

      // Create a new dataset that uses chunked storage instead of the default layout.
      static void test_chunked_dset()
      {
         try
         {
            Console.Write("Testing dataset with chunked storage layout");

            const string FILE_NAME = ("SDSchunked.h5");
            const string DSET_CHUNKED_NAME = ("Chunked IntArray");
            const int NX = 50;   // data set dimension
            const int NY = 20;
            const int RANK = 2; // two-dimension
            H5PropertyListId P_DEFAULT = new H5PropertyListId(H5P.Template.DEFAULT);

            // Data and input buffer initialization.
            int i, j;
            int[,] data = new int[NX, NY];
            for (i = 0; i < NX; i++)
               for (j = 0; j < NY; j++)
                  data[i, j] = i + j;

            // Create a new file using H5F_ACC_TRUNC access,
            // default file creation properties, and default file
            // access properties.
            H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            // Describe the size of the array and create the data space for fixed
            // size dataset.
            long[] dims = new long[RANK];
            dims[0] = NX;
            dims[1] = NY;
            H5DataSpaceId dspaceId = H5S.create_simple(RANK, dims);

            // Define datatype for the data in the file.
            H5DataTypeId dtypeId = H5T.copy(H5T.H5Type.NATIVE_INT);

            // Create dataset creation property list.
            H5PropertyListId crtpltId
                = H5P.create(H5P.PropertyListClass.DATASET_CREATE);

            // Set chunk sizes for the dataset.
            long[] csize = new long[2] { 5, 2 };
            H5P.setChunk(crtpltId, csize);

            // Set deflate for the dataset.
            H5P.setDeflate(crtpltId, 9);

            // Create the data set DATASETNAME.
            H5DataSetId dsetId = H5D.create(fileId, DSET_CHUNKED_NAME, dtypeId, dspaceId, P_DEFAULT, crtpltId, P_DEFAULT);

            // Write the one-dimensional data set array
            H5D.write(dsetId, dtypeId, new H5Array<int>(data));

            // Close dataset and file.
            H5D.close(dsetId);
            H5F.close(fileId);

            // Open the file again in read only mode.
            fileId = H5F.open(FILE_NAME, H5F.OpenMode.ACC_RDONLY);

            // Open the dataset using its name.
            dsetId = H5D.open(fileId, DSET_CHUNKED_NAME);

            int[,] outdata = new int[NX, NY];
            for (i = 0; i < NX; i++)
               for (j = 0; j < NY; j++)
                  outdata[i, j] = 0;

            // Read data back.
            H5D.read(dsetId, new H5DataTypeId(H5T.H5Type.NATIVE_INT), new H5Array<int>(outdata));

            // Compare against input buffer to verify.
            for (i = 0; i < NX; i++)
               for (j = 0; j < NY; j++)
               {
                  if (outdata[i, j] != data[i, j])
                  {
                     Console.WriteLine("\ntest_chunked_dset: read value differs from input: read {0} - input {1}",
                         outdata[i, j], data[i, j]);
                     nerrors++;
                  }
               }

            // Close all objects and file.
            H5D.close(dsetId);
            H5T.close(dtypeId);
            H5S.close(dspaceId);
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
      }  // test_chunked_dset

      static void Main(string[] args)
      {
         Console.WriteLine();
         Console.WriteLine("TEST: HDF5DotNet Property List API");
         Console.WriteLine();
         try
         {
            const string FILE_NAME = ("Dataset.h5");

            // Suppress error printing from the C library.
            H5E.suppressPrinting();

            // Create a new file using H5F_ACC_TRUNC access,
            // default file creation properties, and default file
            // access properties.
            H5FileId fileId = H5F.create(FILE_NAME, H5F.CreateMode.ACC_TRUNC);

            test_buffer();
            test_chunked_dset();

            // Close the file.
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
         Console.WriteLine();
         if (nerrors > 0)
            Console.WriteLine("Test(s) failed: ", nerrors, "occurred!");
         else
            Console.WriteLine("---- All property list tests passed.");
         Console.WriteLine();
      }
   }
}
