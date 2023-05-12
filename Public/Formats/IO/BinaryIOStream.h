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
		virtual USHORT ReadUByte() = 0;
		virtual UINT ReadUByte() = 0;
		virtual ULONG ReadUByte() = 0;

		virtual FLOAT ReadFloat() = 0;
		virtual DOUBLE ReadDouble() = 0;

		virtual BYTE WriteByte() = 0;
		virtual SHORT WriteShort() = 0;
		virtual INT WriteInt() = 0;
		virtual LONG WriteLong() = 0;

		virtual UBYTE WriteUByte() = 0;
		virtual USHORT WriteUByte() = 0;
		virtual UINT WriteUByte() = 0;
		virtual ULONG WriteUByte() = 0;

		virtual FLOAT WriteFloat() = 0;
		virtual DOUBLE WriteDouble() = 0;

	protected:
		std::iostream& mStream;
	};
}