#pragma once

#include "Vector.h"
#include "SDK.h"
#include <stdint.h>

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define RADPI 57.295779513082f
#define rad(a) a * 0.01745329251

void AngleVectors(const Vector &angles, Vector *forward);
void VectorTransform(const Vector in1, float in2[3][4], Vector &out);
void SinCos(float a, float* s, float*c);
void VectorAngles(Vector forward, Vector &angles);
void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up);
void Normalize(Vector &vIn, Vector &vOut);
void CalcAngle(Vector src, Vector dst, Vector &angles);
bool IsVisible(IClientEntity* pLocal, IClientEntity* pEntity, int BoneID);
void CalcAngleYawOnly(Vector src, Vector dst, Vector &angles);
void NormalizeVector(Vector& vec);
Vector AngleVectors(const Vector meme);
float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir);
void MatrixMultiply(matrix3x4 &ps, matrix3x4 &pc, matrix3x4 &pout);
void VectorRotate(const Vector &in1, const QAngle &in2, Vector &out);
void VectorRotate(const float *in1, const matrix3x4& in2, float *out);
void VectorRotate(const Vector& in1, const matrix3x4 &in2, Vector &out);
void MatrixAngles(const matrix3x4& matrix, float *angles);
void MatrixCopy(const matrix3x4& source, matrix3x4& target);
void AngleMatrix(const QAngle &angles, const Vector &position, matrix3x4& matrix_out);
void AngleMatrix(const Vector angles, matrix3x4& matrix);
