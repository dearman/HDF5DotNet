@echo off

REM ============================================================================
REM
REM You can build the HDF5DotNet assembly and the examples without VisualStudio.
REM What used to be called the .NET Framework SDK is now part of the
REM Windows SDK. Get a copy of the Windows SDK, e.g.,
REM
REM http://msdn.microsoft.com/en-us/windows/bb980924
REM
REM and run this batch file from inside a Windows SDK command prompt.
REM You don't need the full SDK, just the compilers and tools
REM for .NET development.
REM
REM By default the Windows SDK 7.1 targets .NET 4.0.
REM When building HDFDotNet for .NET 2.0 uncomment the invocation
REM of the Manifest Tool (mt /nologo ...) below.
REM
REM Make sure that the location of hdf5dll.lib reflects your local
REM installation. The binaries can be obtained from here:
REM
REM http://www.hdfgroup.org/HDF5/release/obtain5.html
REM
REM To run the tests hdf5dll.dll, hdf5_hldll.dll, szip.dll, and
REM zlib1.dll must be in your path. (They are part of the binary distribution.)
REM
REM ============================================================================

REM Set the location of hdf5dll.lib
SET HDF5_LIB="C:\Program Files\HDF Group\HDF5\1.8.9\lib\hdf5dll.lib"

SET FLAGS=/nologo /W4 /clr /doc /DHDF5_DOT_NET /DHDF5DLL=\"hdf5dll.dll\" /DHDF5HLDLL=\"hdf5_hldll.dll\"

REM ============================================================================
REM DEBUG
REM ============================================================================

echo Building Debug version... 

mkdir .\Debug
cd Debug

del /f/q *.dll* *.exe *.h5 *.ilk *.obj *.pdb *.xdc

cl %FLAGS% /LDd /Zi /I..\headers /I..\headers\include1.8 /FeHDF5DotNetd.dll ..\AssemblyInfo.cpp ..\src\*.cpp %HDF5_LIB% 

REM Uncomment the next line if .NET 2.0
REM mt /nologo /manifest HDF5DotNetd.dll.manifest /outputresource:HDF5DotNetd.dll;#2

for /D %%i in (dsets, dspace, h5files, h5groups, tattr, ttable) do csc /nologo /debug:full /t:exe /out:%%id.exe ..\tests\%%i\Program.cs /r:HDF5DotNetd.dll

for /D %%i in (dtypes, tprop) do csc /nologo /debug:full /t:exe /out:%%id.exe ..\tests\%%i\Program.cs /r:HDF5DotNetd.dll /unsafe

copy /y ..\tests\dtypes\gen_types.h5 .

echo Running tests... 

for /D %%i in (dsetsd, dspaced, dtypesd, h5filesd, h5groupsd, tattrd, tpropd, ttabled) do %%i.exe

REM ============================================================================
REM RELEASE
REM ============================================================================

echo Building Release version...

cd ..

mkdir .\Release
cd Release

del /f/q *.dll* *.exe *.h5 *.obj *.xdc

cl %FLAGS% /LD /I..\headers /I..\headers\include1.8 /FeHDF5DotNet.dll ..\AssemblyInfo.cpp ..\src\*.cpp %HDF5_LIB% 

REM Uncomment the next line if .NET 2.0
REM mt /nologo /manifest HDF5DotNet.dll.manifest /outputresource:HDF5DotNet.dll;#2

for /D %%i in (dsets, dspace, h5files, h5groups, tattr, ttable) do csc /nologo /t:exe /out:%%i.exe ..\tests\%%i\Program.cs /r:HDF5DotNet.dll

for /D %%i in (dtypes, tprop) do csc /nologo /t:exe /out:%%i.exe ..\tests\%%i\Program.cs /r:HDF5DotNet.dll /unsafe

copy /y ..\tests\dtypes\gen_types.h5 .

echo Running tests...

for /D %%i in (dsets, dspace, dtypes, h5files, h5groups, tattr, tprop, ttable) do %%i.exe

cd ..
