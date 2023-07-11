#pragma once

#include <Formats/Primitives/Int24.h>
#include <Formats/Primitives/UInt24.h>
#include <cstdint>

#define F_S8 char
#define F_S16 int16_t
#define F_S24 Formats::Primitives::Int24
#define F_S32 int32_t
#define F_S64 int64_t

#define F_U8 unsigned char 
#define F_U16 uint16_t
#define F_U24 Formats::Primitives::UInt24
#define F_U32 uint32_t
#define F_U64 uint64_t
#define F_UT size_t

#define F_F32 float
#define F_F64 double