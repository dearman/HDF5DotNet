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

#include "UnmanagedMemoryStream.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

namespace HDF5DotNet
{
    UnmanagedMemoryStream::UnmanagedMemoryStream()
    {
        m_storage = IntPtr::Zero;
        m_capacity = 0;
        m_count = 0;
        m_position = 0;
    }

    UnmanagedMemoryStream::UnmanagedMemoryStream(long long bytes)
    {
        m_storage = AllocateMemory(bytes);
        m_capacity = bytes;
        m_count = bytes;
        m_position = 0;
    }

    int UnmanagedMemoryStream::Read(array<unsigned char>^ buffer, int offset, int count)
    {
        // Make sure we don't read past the end of the buffer
        if (count > m_count - m_position)
            count = (int)m_count - (int)m_position;

        Marshal::Copy(IntPtr((unsigned char*)m_storage.ToPointer() + m_position), buffer, offset, count);
        m_position = m_position + count;

        return count;
    }

    long long UnmanagedMemoryStream::Seek(long long offset, SeekOrigin origin)
    {
        long long absoluteOffset = 0;
        switch (origin)
        {
        case SeekOrigin::Begin:
            absoluteOffset = offset;
            break;

        case SeekOrigin::Current:
            absoluteOffset = m_position + offset;
            break;

        case SeekOrigin::End:
            absoluteOffset = m_count - offset;
            break;
        }

        if (absoluteOffset < 0 || absoluteOffset > m_count)
            throw gcnew ArgumentOutOfRangeException("offset", "Seek index is out of range for the stream");

        m_position = absoluteOffset;
        return m_position;
    }

    void UnmanagedMemoryStream::SetLength(long long value)
    {
        Reserve(value);
        m_count = value;
        if (m_position > m_count)
            m_position = m_count;
    }

    void UnmanagedMemoryStream::Write(array<unsigned char>^ buffer, int offset, int count)
    {
        if (m_position + count > m_capacity)
        {
            // Make sure we have enough space in the buffer
            if (m_position + count > m_capacity * 2)
                Reserve(m_position + count);
            else               
                Reserve(m_capacity * 2);
        }

        // Write the new data into the stream

        Marshal::Copy(buffer, offset, IntPtr((unsigned char*)m_storage.ToPointer() + m_position), count);

        // Update our position
        m_position = m_position + count;
        if (m_count < m_position)
            m_count = m_position;
    }

    void UnmanagedMemoryStream::Reserve(long long value)
    {
        if (value != m_capacity)
        {
            // Allocate new buffer

            IntPtr newBuffer = AllocateMemory(value);

            // Copy from the old buffer to the new buffer
            if (m_count > value)
                m_count = value;

            unsigned char* source = (unsigned char*)m_storage.ToPointer();
            unsigned char* dest = (unsigned char*)newBuffer.ToPointer();
            for (long long i = 0; i < m_count; ++i)
                dest[i] = source[i];


            // Free the old buffer
            FreeMemory(m_storage);

            // save the new buffer
            m_capacity = value;
            m_storage = newBuffer;

            if (m_position > m_count)
                m_position = m_count;
        }
    }

    IntPtr UnmanagedMemoryStream::AllocateMemory(long long bytes)
    {
        // Allocate memory from the unmanaged heap
        return Marshal::AllocHGlobal(IntPtr(bytes));
    }

    void UnmanagedMemoryStream::FreeMemory(IntPtr ptr)
    {
        if (ptr == IntPtr::Zero)
            return;

        Marshal::FreeHGlobal(ptr);
    }
}

