/*
 * MathUtilities.h
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_FRAMEWORK_MATHUTILITIES_H_
#define ZENASTEROID_FRAMEWORK_MATHUTILITIES_H_

struct Vector2f {
	Vector2f();
	float X = 0.0;
	float Y = 0.0;
	Vector2f(float ix, float iy);
};

struct Matrix3f {
	Matrix3f();
	float Matrix[3][3] = {	{0, 0, 0},
							{0, 0, 0},
							{0, 0, 0}};
	Matrix3f(float InputMatrix[3][3]);

	/*Matrix3f RotateMatrix3f(Vector2f PointPosition, float Rotation);

	Matrix3f TranslateMatrix3f(Vector2f PointPosition, Vector2f Translation);*/

};

class MathUtilities {
public:
	//Vector2f Transform(Vector2f PointPosition, float Rotation, Vector2f Translation);
	static Matrix3f SRT2DToMatrix3f(Vector2f iScale, float iRotation, Vector2f iTranslation);
	static Vector2f Apply2DTransformToVector2f(Vector2f iVector2f, Matrix3f iMatrix3f);
};

#endif /* ZENASTEROID_FRAMEWORK_MATHUTILITIES_H_ */
