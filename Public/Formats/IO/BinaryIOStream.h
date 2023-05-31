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

		virtual F_S8 ReadByte() = 0;
		virtual F_S16 ReadShort() = 0;
		virtual F_S24 ReadInt24() = 0;
		virtual F_S32 ReadInt() = 0;
		virtual F_S64 ReadLong() = 0;

		virtual F_U8 ReadUByte() = 0;
		virtual F_U16 ReadUShort() = 0;
		virtual F_U24 ReadUInt24() = 0;
		virtual F_U32 ReadUInt() = 0;
		virtual F_U64 ReadULong() = 0;

		virtual F_F32 ReadFloat() = 0;
		virtual F_F64 ReadDouble() = 0;

		virtual void WriteByte(F_S8 value) = 0;
		virtual void WriteShort(F_S16 value) = 0;
		virtual void WriteInt24(F_S24 value) = 0;
		virtual void WriteInt(F_S32 value) = 0;
		virtual void WriteLong(F_S64 value) = 0;

		virtual void WriteUByte(F_U8 value) = 0;
		virtual void WriteUShort(F_U16 value) = 0;
		virtual void WriteUInt24(F_U24 value) = 0;
		virtual void WriteUInt(F_U32 value) = 0;
		virtual void WriteULong(F_U64 value) = 0;

		virtual void WriteFloat(F_F32 value) = 0;
		virtual void WriteDouble(F_F64 value) = 0;

	protected:
		std::iostream& mStream;
		std::vector<std::streampos> mSeekStack;
	};
}