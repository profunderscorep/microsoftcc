#pragma once

#include "CommonIncludes.h"
#include <time.h>
#include "MiscDefinitions.h"
#include <mmintrin.h>
#include "VMatrix.h"

#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)

namespace Utilities
{
	void OpenConsole(std::string Title);
	void CloseConsole();
	void Log(const char *fmt, ...);
	void AngleMatrix(QAngle angle, matrix3x4 bones);
	void AngleMatrix(const QAngle & angles, const Vector & position, matrix3x4& matrix_out);

	void EnableLogFile(std::string filename);
	
	void SetConsoleColor(WORD color);  

	std::string GetTimeString();
	
	namespace Memory
	{

		DWORD WaitOnModuleHandle(std::string moduleName);

		DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask);

		DWORD FindPatternV2(std::string moduleName, std::string pattern);

		DWORD FindTextPattern(std::string moduleName, char* string);

		class VMTManager
		{
		private:
			DWORD	*CustomTable;
			bool	initComplete;
			DWORD	*OriginalTable;
			DWORD	*Instance;

			int		MethodCount(DWORD* InstancePointer);
			
		public:
			bool	Initialise(DWORD* InstancePointer); 

			DWORD	HookMethod(DWORD NewFunction, int Index);
			void	UnhookMethod(int Index);

			void	RestoreOriginal();
			void	RestoreCustom();

			template<typename T>
			T GetMethod(size_t nIndex)
			{
				return (T)OriginalTable[nIndex];
			}

			DWORD	GetOriginalFunction(int Index);
		};
	};
};

template<typename T>
FORCEINLINE T GetMethod(const void* instance, size_t index)
{
	uintptr_t* vmt = *(uintptr_t**)instance;

	return (T)vmt[index];
}


#include <xmmintrin.h>
#include <DirectXMath.h>
//#include <VectorIntrinsics.h>



typedef __m128 fltx4;

typedef __m128 XMVECTOR;
#define XM_CALLCONV __vectorcall
typedef const XMVECTOR FXMVECTOR;
XMVECTOR    XM_CALLCONV     XMVectorSplatX(FXMVECTOR V);
XMVECTOR    XM_CALLCONV     XMVectorSplatY(FXMVECTOR V);
XMVECTOR    XM_CALLCONV     XMVectorSplatZ(FXMVECTOR V);
XMVECTOR    XM_CALLCONV     XMVectorNegate(FXMVECTOR V);

inline XMVECTOR XM_CALLCONV XMVectorSplatX
(
	FXMVECTOR V
)
{
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR vResult;
	vResult.vector4_f32[0] =
		vResult.vector4_f32[1] =
		vResult.vector4_f32[2] =
		vResult.vector4_f32[3] = V.vector4_f32[0];
	return vResult;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vdupq_lane_f32(vget_low_f32(V), 0);
#elif defined(_XM_SSE_INTRINSICS_)
	return XM_PERMUTE_PS(V, _MM_SHUFFLE(0, 0, 0, 0));
#endif
}

//------------------------------------------------------------------------------
// Replicate the y component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatY
(
	FXMVECTOR V
)
{
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR vResult;
	vResult.vector4_f32[0] =
		vResult.vector4_f32[1] =
		vResult.vector4_f32[2] =
		vResult.vector4_f32[3] = V.vector4_f32[1];
	return vResult;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vdupq_lane_f32(vget_low_f32(V), 1);
#elif defined(_XM_SSE_INTRINSICS_)
	return XM_PERMUTE_PS(V, _MM_SHUFFLE(1, 1, 1, 1));
#endif
}

//------------------------------------------------------------------------------
// Replicate the z component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatZ
(
	FXMVECTOR V
)
{
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR vResult;
	vResult.vector4_f32[0] =
		vResult.vector4_f32[1] =
		vResult.vector4_f32[2] =
		vResult.vector4_f32[3] = V.vector4_f32[2];
	return vResult;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vdupq_lane_f32(vget_high_f32(V), 0);
#elif defined(_XM_SSE_INTRINSICS_)
	return XM_PERMUTE_PS(V, _MM_SHUFFLE(2, 2, 2, 2));
#endif
}


FORCEINLINE fltx4 LoadUnalignedSIMD(const void *pSIMD)
{
	return *(reinterpret_cast< const fltx4 *> (pSIMD));
}

FORCEINLINE fltx4 SplatXSIMD(fltx4 a)
{
	return XMVectorSplatX(a);
}

FORCEINLINE fltx4 SplatYSIMD(fltx4 a)
{
	return XMVectorSplatY(a);
}

FORCEINLINE fltx4 SplatZSIMD(fltx4 a)
{
	return XMVectorSplatZ(a);
}

FORCEINLINE fltx4 MulSIMD(const fltx4 & a, const fltx4 & b)				// a*b
{
	return _mm_mul_ps(a, b);
};

FORCEINLINE fltx4 AddSIMD(const fltx4 & a, const fltx4 & b)				// a+b
{
	return _mm_add_ps(a, b);
};

FORCEINLINE fltx4 AndSIMD(const fltx4 & a, const fltx4 & b)				// a & b
{
	return _mm_and_ps(a, b);
}

FORCEINLINE fltx4 CmpLeSIMD(const fltx4 & a, const fltx4 & b)				// (a<=b) ? ~0:0
{
	return _mm_cmpge_ss(b, a);
}

FORCEINLINE fltx4 CmpGeSIMD(const fltx4 & a, const fltx4 & b)				// (a>=b) ? ~0:0
{
	return _mm_cmpge_ps(a, b);
}

FORCEINLINE fltx4 NegSIMD(const fltx4 &a) // negate: -a
{
	return XMVectorNegate(a);
}

FORCEINLINE fltx4 CmpInBoundsSIMD(const fltx4 & a, const fltx4 & b)		// (a <= b && a >= -b) ? ~0 : 0
{
	return AndSIMD(CmpLeSIMD(a, b), CmpGeSIMD(a, NegSIMD(b)));
}

FORCEINLINE void StoreUnalignedSIMD(float *pSIMD, const fltx4 & a)
{
	*(reinterpret_cast< fltx4 *> (pSIMD)) = a;
}
