#pragma once

#include <Formats/Aliases/Primitives.h>

#include <istream>

namespace Formats::IO {
	class BinaryIOStream {
	public:
		BinaryIOStream(std::iostream& stream) : mStream(stream) {

		}

		inline void SeekRead(std::streampos pos) {
			mStream.seekg(pos);
		}

		inline void SeekWrite(std::streampos pos) {
			mStream.seekp(pos);
		}

		virtual BYTE ReadByte() = 0;
		virtual SHORT ReadShort() = 0;
		virtual INT ReadInt() = 0;
		virtual LONG ReadLong() = 0;

		virtual UBYTE ReadUByte() = 0;
		virtual USHORT ReadUShort() = 0;
		virtual UINT ReadUInt() = 0;
		virtual ULONG ReadULong() = 0;

		virtual FLOAT ReadFloat() = 0;
		virtual DOUBLE ReadDouble() = 0;

		virtual void WriteByte(BYTE value) = 0;
		virtual void WriteShort(SHORT value) = 0;
		virtual void WriteInt(INT value) = 0;
		virtual void WriteLong(LONG value) = 0;

		virtual void WriteUByte(UBYTE value) = 0;
		virtual void WriteUShort(USHORT value) = 0;
		virtual void WriteUInt(UINT value) = 0;
		virtual void WriteULong(ULONG value) = 0;

		virtual void WriteFloat(FLOAT value) = 0;
		virtual void WriteDouble(DOUBLE value) = 0;

	protected:
		std::iostream& mStream;
	};
}