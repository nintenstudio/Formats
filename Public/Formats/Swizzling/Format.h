#pragma once

namespace Formats::Swizzling {

	/// <summary>
	/// Copied from https://github.com/KillzXGaming/Switch-Toolbox/blob/deeff8e9a9e76d0a0ce7e79d5a36d37937607341/Switch_Toolbox_Library/Generics/TEX_FORMAT.cs#L18
	/// </summary>
	enum class Format {
		UNKNOWN = 0,
        R32G32B32A32_TYPELESS = 1,
        R32G32B32A32_FLOAT = 2,
        R32G32B32A32_UINT = 3,
        R32G32B32A32_SINT = 4,
        R32G32B32_TYPELESS = 5,
        R32G32B32_FLOAT = 6,
        R32G32B32_UINT = 7,
        R32G32B32_SINT = 8,
        R16G16B16A16_TYPELESS = 9,
        R16G16B16A16_FLOAT = 10,
        R16G16B16A16_UNORM = 11,
        R16G16B16A16_UINT = 12,
        R16G16B16A16_SNORM = 13,
        R16G16B16A16_SINT = 14,
        R32G32_TYPELESS = 15,
        R32G32_FLOAT = 16,
        R32G32_UINT = 17,
        R32G32_SINT = 18,
        R32G8X24_TYPELESS = 19,
        D32_FLOAT_S8X24_UINT = 20,
        R32_FLOAT_X8X24_TYPELESS = 21,
        X32_TYPELESS_G8X24_UINT = 22,
        R10G10B10A2_TYPELESS = 23,
        R10G10B10A2_UNORM = 24,
        R10G10B10A2_UINT = 25,
        R11G11B10_FLOAT = 26,
        R8G8B8A8_TYPELESS = 27,
        R8G8B8A8_UNORM = 28,
        R8G8B8A8_UNORM_SRGB = 29,
        R8G8B8A8_UINT = 30,
        R8G8B8A8_SNORM = 31,
        R8G8B8A8_SINT = 32,
        R16G16_TYPELESS = 33,
        R16G16_FLOAT = 34,
        R16G16_UNORM = 35,
        R16G16_UINT = 36,
        R16G16_SNORM = 37,
        R16G16_SINT = 38,
        R32_TYPELESS = 39,
        D32_FLOAT = 40,
        R32_FLOAT = 41,
        R32_UINT = 42,
        R32_SINT = 43,
        R24G8_TYPELESS = 44,
        D24_UNORM_S8_UINT = 45,
        R24_UNORM_X8_TYPELESS = 46,
        X24_TYPELESS_G8_UINT = 47,
        R8G8_TYPELESS = 48,
        R8G8_UNORM = 49,
        R8G8_UINT = 50,
        R8G8_SNORM = 51,
        R8G8_SINT = 52,
        R16_TYPELESS = 53,
        R16_FLOAT = 54,
        D16_UNORM = 55,
        R16_UNORM = 56,
        R16_UINT = 57,
        R16_SNORM = 58,
        R16_SINT = 59,
        R8_TYPELESS = 60,
        R8_UNORM = 61,
        R8_UINT = 62,
        R8_SNORM = 63,
        R8_SINT = 64,
        A8_UNORM = 65,
        R1_UNORM = 66,
        R9G9B9E5_SHAREDEXP = 67,
        R8G8_B8G8_UNORM = 68,
        G8R8_G8B8_UNORM = 69,
        BC1_TYPELESS = 70,
        BC1_UNORM = 71,
        BC1_UNORM_SRGB = 72,
        BC2_TYPELESS = 73,
        BC2_UNORM = 74,
        BC2_UNORM_SRGB = 75,
        BC3_TYPELESS = 76,
        BC3_UNORM = 77,
        BC3_UNORM_SRGB = 78,
        BC4_TYPELESS = 79,
        BC4_UNORM = 80,
        BC4_SNORM = 81,
        BC5_TYPELESS = 82,
        BC5_UNORM = 83,
        BC5_SNORM = 84,
        B5G6R5_UNORM = 85,
        B5G5R5A1_UNORM = 86,
        B8G8R8A8_UNORM = 87,
        B8G8R8X8_UNORM = 88,
        R10G10B10_XR_BIAS_A2_UNORM = 89,
        B8G8R8A8_TYPELESS = 90,
        B8G8R8A8_UNORM_SRGB = 91,
        B8G8R8X8_TYPELESS = 92,
        B8G8R8X8_UNORM_SRGB = 93,
        BC6H_TYPELESS = 94,
        BC6H_UF16 = 95,
        BC6H_SF16 = 96,
        BC7_TYPELESS = 97,
        BC7_UNORM = 98,
        BC7_UNORM_SRGB = 99,
        AYUV = 100,
        Y410 = 101,
        Y416 = 102,
        NV12 = 103,
        P010 = 104,
        P016 = 105,
        Format_420_OPAQUE = 106,
        YUY2 = 107,
        Y210 = 108,
        Y216 = 109,
        NV11 = 110,
        AI44 = 111,
        IA44 = 112,
        P8 = 113,
        A8P8 = 114,
        B4G4R4A4_UNORM = 115,
        P208 = 130,
        V208 = 131,
        V408 = 132,
        R32G8X24_FLOAT = 133,
        ASTC_4x4_UNORM = 134,
        ASTC_4x4_SRGB = 135,
        ASTC_5x4_UNORM = 138,
        ASTC_5x4_SRGB = 139,
        ASTC_5x5_UNORM = 142,
        ASTC_5x5_SRGB = 143,
        ASTC_6x5_UNORM = 146,
        ASTC_6x5_SRGB = 147,
        ASTC_6x6_UNORM = 150,
        ASTC_6x6_SRGB = 151,
        ASTC_8x5_UNORM = 154,
        ASTC_8x5_SRGB = 155,
        ASTC_8x6_UNORM = 158,
        ASTC_8x6_SRGB = 159,
        ASTC_8x8_UNORM = 162,
        ASTC_8x8_SRGB = 163,
        ASTC_10x5_UNORM = 166,
        ASTC_10x5_SRGB = 167,
        ASTC_10x6_UNORM = 170,
        ASTC_10x6_SRGB = 171,
        ASTC_10x8_UNORM = 174,
        ASTC_10x8_SRGB = 175,
        ASTC_10x10_UNORM = 178,
        ASTC_10x10_SRGB = 179,
        ASTC_12x10_UNORM = 182,
        ASTC_12x10_SRGB = 183,
        ASTC_12x12_UNORM = 186,
        ASTC_12x12_SRGB = 187,

        ETC1_SRGB = 229,
        ETC1_UNORM = 230,
        ETC1_A4 = 231,
        L4 = 232,
        LA4 = 233,
        L8 = 234,
        LA8 = 235,
        HIL08 = 236,
        A4 = 237,
        R4G4_UNORM = 238,

        I4 = 239,
        I8 = 240,
        IA4 = 241,
        IA8 = 242,
        R5G5B5_UNORM = 243,
        R5G5B5A3_UNORM = 244,
        RGBA32 = 245,
        C4 = 246,
        C8 = 247,
        C14X2 = 248,
        CMPR = 249,
        RGB565 = 250,
        RGB5A3 = 251,
        R5G5B5A1_UNORM = 252,
	};
}