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

		inline void Seek(std::streampos pos) {
			mStream.seekg(pos);
			mStream.seekp(pos);
		}

		inline void PushSeek(std::streampos pos) {
			mSeekStack.push_back(mStream.tellg());

			mStream.seekg(pos);
			mStream.seekp(pos);
		}

		inline std::streampos PopSeek() {
			std::streampos res = mStream.tellg();

			mStream.seekg(mSeekStack.back());
			mStream.seekp(mSeekStack.back());
			mSeekStack.pop_back();
			
			return res;
		}

		inline std::streampos GetSeek() {
			return mStream.tellg();
		}

		inline void AlignSeek(std::streampos alignment) {
			std::streampos pos = mStream.tellg();
			pos = (pos % alignment == 0) ? pos : alignment - (pos % alignment) + pos;
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

		virtual F_BYTE ReadByte() = 0;
		virtual F_SHORT ReadShort() = 0;
		virtual F_INT24 ReadInt24() = 0;
		virtual F_INT ReadInt() = 0;
		virtual F_LONG ReadLong() = 0;

		virtual F_UBYTE ReadUByte() = 0;
		virtual F_USHORT ReadUShort() = 0;
		virtual F_UINT24 ReadUInt24() = 0;
		virtual F_UINT ReadUInt() = 0;
		virtual F_ULONG ReadULong() = 0;

		virtual F_FLOAT ReadFloat() = 0;
		virtual F_DOUBLE ReadDouble() = 0;

		virtual void WriteByte(F_BYTE value) = 0;
		virtual void WriteShort(F_SHORT value) = 0;
		virtual void WriteInt24(F_INT24 value) = 0;
		virtual void WriteInt(F_INT value) = 0;
		virtual void WriteLong(F_LONG value) = 0;

		virtual void WriteUByte(F_UBYTE value) = 0;
		virtual void WriteUShort(F_USHORT value) = 0;
		virtual void WriteUInt24(F_UINT24 value) = 0;
		virtual void WriteUInt(F_UINT value) = 0;
		virtual void WriteULong(F_ULONG value) = 0;

		virtual void WriteFloat(F_FLOAT value) = 0;
		virtual void WriteDouble(F_DOUBLE value) = 0;

	protected:
		std::iostream& mStream;
		std::vector<std::streampos> mSeekStack;
	};
}