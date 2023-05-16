#pragma once

#include <Formats/Aliases/Primitives.h>

#include <istream>
#include <vector>
#include <string>

namespace Formats::IO {
	class BinaryIOStream {
	public:
		BinaryIOStream(std::iostream& stream) : mStream(stream) {

		}

		inline void PushSeek(std::streampos pos) {
			mSeekStack.push_back(mStream.tellg());

			mStream.seekg(pos);
			mStream.seekp(pos);
		}

		inline std::streampos PopSeek() {
			std::streampos res = mStream.tellg();

			mStream.seekg(*mSeekStack.end());
			mStream.seekp(*mSeekStack.end());
			mSeekStack.pop_back();
			
			return res;
		}

		inline std::streampos GetSeek() {
			return mStream.tellg();
		}

		inline void AlignSeek(std::streampos alignment) {
			std::streampos pos = mStream.tellg();
			pos = alignment - (pos % alignment) + pos;
			mStream.seekg(pos);
			mStream.seekp(pos);
		}

		inline std::string ReadZeroTerminatedString() {
			std::string res;
			std::getline(mStream, res, '\0');
			return res;
		}
		inline void WriteZeroTerminatedString(std::string value) {
			mStream << value.c_str();
		}

		virtual BYTE ReadByte() = 0;
		virtual SHORT ReadShort() = 0;
		virtual INT24 ReadInt24() = 0;
		virtual INT ReadInt() = 0;
		virtual LONG ReadLong() = 0;

		virtual UBYTE ReadUByte() = 0;
		virtual USHORT ReadUShort() = 0;
		virtual UINT24 ReadUInt24() = 0;
		virtual UINT ReadUInt() = 0;
		virtual ULONG ReadULong() = 0;

		virtual FLOAT ReadFloat() = 0;
		virtual DOUBLE ReadDouble() = 0;

		virtual void WriteByte(BYTE value) = 0;
		virtual void WriteShort(SHORT value) = 0;
		virtual void WriteInt24(INT24 value) = 0;
		virtual void WriteInt(INT value) = 0;
		virtual void WriteLong(LONG value) = 0;

		virtual void WriteUByte(UBYTE value) = 0;
		virtual void WriteUShort(USHORT value) = 0;
		virtual void WriteUInt24(UINT24 value) = 0;
		virtual void WriteUInt(UINT value) = 0;
		virtual void WriteULong(ULONG value) = 0;

		virtual void WriteFloat(FLOAT value) = 0;
		virtual void WriteDouble(DOUBLE value) = 0;

	protected:
		std::iostream& mStream;
		std::vector<std::streampos> mSeekStack;
	};
}