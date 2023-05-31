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

		virtual F_S8 ReadS8() = 0;
		virtual F_S16 ReadS16() = 0;
		virtual F_S24 ReadS24() = 0;
		virtual F_S32 ReadS32() = 0;
		virtual F_S64 ReadS64() = 0;

		virtual F_U8 ReadU8() = 0;
		virtual F_U16 ReadU16() = 0;
		virtual F_U24 ReadU24() = 0;
		virtual F_U32 ReadU32() = 0;
		virtual F_U64 ReadU64() = 0;

		virtual F_F32 ReadF32() = 0;
		virtual F_F64 ReadF64() = 0;

		virtual void WriteS8(F_S8 value) = 0;
		virtual void WriteS16(F_S16 value) = 0;
		virtual void WriteS24(F_S24 value) = 0;
		virtual void WriteS32(F_S32 value) = 0;
		virtual void WriteS64(F_S64 value) = 0;

		virtual void WriteU8(F_U8 value) = 0;
		virtual void WriteU16(F_U16 value) = 0;
		virtual void WriteU24(F_U24 value) = 0;
		virtual void WriteU32(F_U32 value) = 0;
		virtual void WriteU64(F_U64 value) = 0;

		virtual void WriteF32(F_F32 value) = 0;
		virtual void WriteF64(F_F64 value) = 0;

		void ReadBytes(F_U8* out, F_U32 size) {
			mStream.read(reinterpret_cast<char*>(out), size);
		}

		void WriteBytes(F_U8* in, F_U32 size) {
			mStream.write(reinterpret_cast<char*>(in), size);
		}

	protected:
		std::iostream& mStream;
		std::vector<std::streampos> mSeekStack;
	};
}