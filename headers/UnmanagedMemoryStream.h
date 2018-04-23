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

// This is a C++/CLI version of the UnmanagedMemoryStream class of MPI.NET
// by Douglas Gregor and Andrew Lumsdaine

namespace HDF5DotNet
{
    /// <summary>
    /// A stream object that is backed by unmanaged memory. The behavior of <c>UnmanagedMemoryStream</c> is similar to 
    /// that of the .NET <see cref="System::IO::MemoryStream"/>, because it manages memory internally and will re-allocate 
    /// its internal buffers as necessary to accommodate additional writes (the latter is not supported by 
    /// <see cref="System::IO::UnmanagedMemoryStream"/>). The memory used by this class is allocated via
    /// the <see cref="System::Runtime::InteropServices::Marshal"/> class's unmanaged memory allocation routines.
    /// </summary>
    public ref class UnmanagedMemoryStream : System::IO::Stream
    {
    public:
        /// <summary>
        /// Create a new, empty unmanaged memory stream. The memory stream can be resized by 
        /// setting <see cref="Length"/>, calling <see cref="SetLength"/>, or writing to
        /// the stream.
        /// </summary>
        UnmanagedMemoryStream();

        /// <summary>
        /// Create a new unmanaged memory stream with storage for a certain number of bytes of
        /// data. The length of the stream will be set to <paramref name="bytes"/>, but the 
        /// contents of the stream after initialization are undefined.
        /// </summary>
        /// <param name="bytes">The number of bytes in the new stream.</param>
        UnmanagedMemoryStream(long long bytes);
        
        /// <summary>
        /// Whether the stream can be read from. Always <c>true</c>.
        /// </summary>
        property bool CanRead
        {
            virtual bool get() override { return true; }
        }

        /// <summary>
        /// Whether one can seek in the stream. Always <c>true</c>.
        /// </summary>
        property bool CanSeek
        {
            virtual bool get() override { return true; }
        }

        /// <summary>
        /// Whether on can write to the stream. Always <c>true</c>.
        /// </summary>
        property bool CanWrite
        {
            virtual bool get() override { return true; }
        }

        /// <summary>
        /// "Flush" the contents of the stream. This operation does nothing.
        /// </summary>
        virtual void Flush() override
        {
            // Nothing to do.
        }

        /// <summary>
        /// The length of the stream, in bytes.
        /// </summary>
        property long long Length
        {
            virtual long long get() override { return m_count; }
        }

        /// <summary>
        /// Reports or sets the position in the stream. 
        /// </summary>
        property long long Position
        {
            virtual long long get() override
            {
                return m_position;
            }
            virtual void set (long long value) override
            {
                if (value < 0 || value > m_count)
                    throw gcnew System::ArgumentOutOfRangeException("Position value is beyond the end of the stream");
                m_position = value;
            }
        }

        /// <summary>
        /// Read <paramref name="count"/> bytes from the current position in the stream, and place
        /// them into the <paramref name="buffer"/> starting at the given <paramref name="offset"/>.
        /// The position will be updated to the point after the last byte read.
        /// </summary>
        /// <param name="buffer">Array that will receive the data read from the stream.</param>
        /// <param name="offset">The position in the buffer where the first byte will be written.</param>
        /// <param name="count">The maximum number of bytes to copy into the buffer.</param>
        /// <returns>The actual number of bytes read into the buffer.</returns>
        virtual int Read([System::Runtime::InteropServices::InAttribute]
                         [System::Runtime::InteropServices::OutAttribute]
                         array<unsigned char>^ buffer, int offset, int count) override;

        /// <summary>
        /// Seek to a specific position in the stream.
        /// </summary>
        /// <param name="offset">Offset (in bytes) from the <paramref name="origin"/>.</param>
        /// <param name="origin">Where to start seeking from.</param>
        /// <returns>The new position in the stream.</returns>
        virtual long long Seek(long long offset, System::IO::SeekOrigin origin) override;

        /// <summary>
        /// Set the length of the stream. If the new length of the stream 
        /// is larger than the old length, the contents of the stream from
        /// the old length to the new length are undefined.
        /// </summary>
        /// <param name="value">The new length.</param>
        virtual void SetLength(long long value) override;

        /// <summary>
        /// Write data into unmanaged memory. If the write would continue past the
        /// end of the memory stream, the memory stream is expanded.
        /// </summary>
        /// <param name="buffer">The buffer containing the data to write.</param>
        /// <param name="offset">The position in the buffer from which data should be read.</param>
        /// <param name="count">The number of bytes to write to the stream.</param>
        virtual void Write(array<unsigned char>^ buffer, int offset, int count) override;

        /// <summary>
        /// Reserve a certain amount of space in the buffer, to minimize the need for
        /// reallocations if you already know how much space will be needed.
        /// </summary>
        /// <param name="value">The number of bytes to reserve.</param>
        void Reserve(long long value);

        /// <summary>
        /// Releases the memory associated with the stream, if any.
        /// </summary>
        ~UnmanagedMemoryStream()
        {
            this->!UnmanagedMemoryStream();
        }

        !UnmanagedMemoryStream()
        {
            if (System::IntPtr::Zero != m_storage)
            {
                FreeMemory(m_storage);
                m_storage = System::IntPtr::Zero;
            }
        }

        /// <summary>
        /// Retrieve a pointer to the unmanaged memory buffer. Since this
        /// buffer is pointing into unmanaged memory, it does not need to be
        /// pinned.
        /// </summary>
        property System::IntPtr Buffer
        {
            System::IntPtr get() { return m_storage; }
        }

        /// <summary>
        /// The amount of space in the unmanaged memory buffer. This can be
        /// larger than the length of the stream. If you know how many bytes
        /// will be written to the stream, you might want to set the capacity
        /// (either via this property or through <see cref="Reserve"/>) large
        /// enough to avoid resizing the stream multiple times.
        /// </summary>
        property long long Capacity
        {
            long long get()
            {
                return m_capacity;
            }

            void set(long long value)
            {
                Reserve(value);
            }
        }

    private:

        /// <summary>
        /// Allocates unmanaged memory from the unmanaged heap. Memory
        /// allocated in this way should be freed via <see cref="FreeMemory"/>.
        /// </summary>
        /// <param name="bytes">The number of bytes to allocate.</param>
        /// <returns>A pointer to the newly-allocated memory.</returns>
        static System::IntPtr AllocateMemory(long long bytes);

        /// <summary>
        /// Frees memory allocated via <see cref="AllocateMemory"/>.
        /// </summary>
        /// <param name="ptr">The pointer returned from <see cref="AllocateMemory"/>.</param>
        static void FreeMemory(System::IntPtr ptr);

        /// <summary>
        /// A pointer to unmanaged storage.
        /// </summary>
        System::IntPtr m_storage;

        /// <summary>
        /// The number of bytes that <see cref="m_storage"/> refers to.
        /// </summary>
        long long m_capacity;

        /// <summary>
        /// The number of bytes in the buffer.
        /// </summary>
        long long m_count;

        /// <summary>
        /// Current position within the stream.
        /// </summary>
        long long m_position;
    };


}
