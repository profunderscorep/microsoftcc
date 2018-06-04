#include "MathFunctions.h"
#include "CommonIncludes.h"

void AngleVectors(const Vector &angles, Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

void VectorTransform(const Vector in1, float in2[3][4], Vector &out)
{
	out[0] = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
	out[1] = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
	out[2] = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}

void SinCos(float a, float* s, float*c)
{
	*s = sin(a);
	*c = cos(a);
}

void VectorAngles(Vector forward, Vector &angles)
{
	float tmp, yaw, pitch;

	if (forward[2] == 0 && forward[0] == 0)
	{
		yaw = 0;

		if (forward[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / PI);

		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / PI);

		if (pitch < 0)
			pitch += 360;
	}

	if (pitch > 180)
		pitch -= 360;
	else if (pitch < -180)
		pitch += 360;

	if (yaw > 180)
		yaw -= 360;
	else if (yaw < -180)
		yaw += 360;

	if (pitch > 89)
		pitch = 89;
	else if (pitch < -89)
		pitch = -89;

	if (yaw > 180)
		yaw = 180;
	else if (yaw < -180)
		yaw = -180;

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0){
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}


void CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); 
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}

bool IsVisible(IClientEntity* pLocal, IClientEntity* pEntity, int BoneID)
{
	if (BoneID < 0) return false;

	trace_t Trace;
	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = GetHitboxPosition(pEntity, BoneID);

	UTIL_TraceLine(start, end, MASK_SOLID, pLocal, 0, &Trace);

	if (Trace.m_pEnt == pEntity)
	{
		return true;
	}

	if (Trace.fraction == 1.0f)
	{
		return true;
	}

	return false;
}

void NormalizeVector(Vector& vec) {
	for (int i = 0; i < 3; ++i) {
		while (vec[i] > 180.f)
			vec[i] -= 360.f;

		while (vec[i] < -180.f)
			vec[i] += 360.f;
	}
	vec[2] = 0.f;
}

inline Vector AngleVectors(Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
	auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

	auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
	auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

	return Vector(cp*cy, cp*sy, -sp);
}

void CalcAngleYawOnly(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D();
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}

void MatrixMultiply(matrix3x4 &ps, matrix3x4 &pc, matrix3x4 &pout)
{
	// ps =  source matrix | pc =  custombonetoworld | pout =  output matrix
		
	/* Format of a matrix3x4:
	xx	xy	xz	posx
	yx	yy	yz	posy
	zx	zy	zz	posz
	*/
																																																																						
	pout[0][0] = ps[0][0] * pc[0][0] + ps[0][1] * pc[1][0] + ps[0][2] * pc[2][0] + ps[0][3] * 0; pout[0][1] = ps[0][0] * pc[0][1] + ps[0][1] * pc[1][1] + ps[0][2] * pc[2][1] + ps[0][3] * 0; pout[0][2] = ps[0][0] * pc[0][2] + ps[0][1] * pc[1][2] + ps[0][2] * pc[2][2] + ps[0][3] * 0; pout[0][3] = ps[0][0] * pc[0][3] + ps[0][1] * pc[1][3] + ps[0][2] * pc[2][3] + ps[0][3] * 1;
	pout[1][0] = ps[1][0] * pc[0][0] + ps[1][1] * pc[1][0] + ps[1][2] * pc[2][0] + ps[1][3] * 0; pout[1][1] = ps[1][0] * pc[0][1] + ps[1][1] * pc[1][1] + ps[1][2] * pc[2][1] + ps[1][3] * 0; pout[1][2] = ps[1][0] * pc[0][2] + ps[1][1] * pc[1][2] + ps[1][2] * pc[2][2] + ps[1][3] * 0; pout[1][3] = ps[1][0] * pc[0][3] + ps[1][1] * pc[1][3] + ps[1][2] * pc[2][3] + ps[1][3] * 1;
	pout[2][0] = ps[2][0] * pc[0][0] + ps[2][1] * pc[1][0] + ps[2][2] * pc[2][0] + ps[2][3] * 0; pout[2][1] = ps[2][0] * pc[0][1] + ps[2][1] * pc[1][1] + ps[2][2] * pc[2][1] + ps[2][3] * 0; pout[2][2] = ps[2][0] * pc[0][2] + ps[2][1] * pc[1][2] + ps[2][2] * pc[2][2] + ps[2][3] * 0; pout[2][3] = ps[2][0] * pc[0][3] + ps[2][1] * pc[1][3] + ps[2][2] * pc[2][3] + ps[2][3] * 1;

	// last row is a zero-row, we can just delete it because we are multiplying with 0 anyway and we need a 3x4, not a 4x4

}
/*
void VectorRotate1(const Vector &in1, const matrix3x4& in2, Vector &out)
{
	//return (a.x * b.x + a.y * b.y + a.z * b.z); //dot product
	Assert(s_bMathlibInitialized);
	Assert(in1 != out);
	out[0] = in1[0] * in2[0][0] + in1[1] * in2[0][1] + in1[2] * in2[0][2];
	out[1] = in1[1] * in2[1][0] + in1[1] * in2[1][1] + in1[2] * in2[1][2];
	out[2] = in1[2] * in2[2][0] + in1[1] * in2[2][1] + in1[2] * in2[2][2];
	//check original source on sdk im too lazy
}
void VectorRotate(const Vector &in1, const QAngle &in2, Vector &out)
{
	matrix3x4 matRotate;
	Utilities::AngleMatrix(in2, matRotate);
	VectorRotate1(in1, matRotate, out);
	
}
*/

void MatrixAngles(const matrix3x4& matrix, float *angles)
{

	Assert(s_bMathlibInitialized);
	float forward[3];
	float left[3];
	float up[3];

	//
	// Extract the basis vectors from the matrix. Since we only need the Z
	// component of the up vector, we don't get X and Y.
	//
	forward[0] = matrix[0][0];
	forward[1] = matrix[1][0];
	forward[2] = matrix[2][0];
	left[0] = matrix[0][1];
	left[1] = matrix[1][1];
	left[2] = matrix[2][1];
	up[2] = matrix[2][2];
	/*
	float xyDist = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);

	// enough here to get angles?
	if (xyDist > 0.001f)
	{
		// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
		angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));

		// (roll)	z = ATAN( left.z, up.z );
		angles[2] = RAD2DEG(atan2f(left[2], up[2]));
	}
	else	// forward is mostly Z, gimbal lock-
	{
	*/
		// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
		angles[1] = RAD2DEG(atan2f(-left[0], left[1]));

		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		//angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));

		// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
		angles[2] = 0;
	/*}*/
}
/////////////////////////////REEEEEEEEEEEE COPY PASTE MODE
void AngleMatrix(const Vector angles, matrix3x4& matrix)
{
	float sr, sp, sy, cr, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	sr = sin(DEG2RAD(angles[2]));
	cr = cos(DEG2RAD(angles[2]));

	//matrix = (YAW * PITCH) * ROLL
	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

void MatrixSetColumn(const Vector &in, int column, matrix3x4& out)
{
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

void AngleMatrix(const QAngle &angles, const Vector &position, matrix3x4& matrix_out)
{
	AngleMatrix(angles, matrix_out);
	MatrixSetColumn(position, 3, matrix_out);
}

void MatrixCopy(const matrix3x4& source, matrix3x4& target)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			target[i][j] = source[i][j];
		}
	}
}



void VectorRotate(const float *in1, const matrix3x4& in2, float *out)
{
	//float_array to vec_t_or 
	Vector vec_in1, row_in2_0, row_in2_1, row_in2_2;
	vec_in1.x = in1[0]; vec_in1.y = in1[1]; vec_in1.z = in1[2];
	row_in2_0.x = in2[0][0]; row_in2_0.y = in2[0][1]; row_in2_0.z = in2[0][2];
	row_in2_1.x = in2[1][0]; row_in2_1.y = in2[1][1]; row_in2_1.z = in2[1][2];
	row_in2_2.x = in2[2][0]; row_in2_2.y = in2[2][1]; row_in2_2.z = in2[2][2];
	out[0] = DotProduct(vec_in1, row_in2_0);
	out[1] = DotProduct(vec_in1, row_in2_1);
	out[2] = DotProduct(vec_in1, row_in2_2);
}

void VectorRotate(const Vector& in1, const matrix3x4 &in2, Vector &out)
{
	VectorRotate(&in1.x, in2, &out.x);
}

void VectorRotate(const Vector &in1, const QAngle &in2, Vector &out)
{
	matrix3x4 matRotate;
	AngleMatrix(in2, matRotate);
	VectorRotate(in1, matRotate, out);
}