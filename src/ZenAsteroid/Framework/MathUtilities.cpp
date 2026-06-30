/*
 * MathUtilities.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "MathUtilities.h"

#include <math.h>

Vector2f::Vector2f() = default;

Vector2f::Vector2f(float ix, float iy) {
	X = ix;
	Y = iy;
}

Matrix3f::Matrix3f() = default;

Matrix3f::Matrix3f(float InputMatrix[3][3]) {
	for (unsigned int y = 0; y < 3; y++) {
		for (unsigned int x = 0; x < 3; x++) {
			Matrix[y][x] = InputMatrix[y][x];
		}
	}
}

Matrix3f MathUtilities::SRT2DToMatrix3f(Vector2f iScale, float iRotation, Vector2f iTranslation) {
	Matrix3f output;
	output.Matrix[0][0] = iScale.X * cosf(iRotation);
	output.Matrix[0][1] = iScale.Y * sinf(iRotation);
	output.Matrix[0][2] = iTranslation.X;
	output.Matrix[1][0] = iScale.X * -sinf(iRotation);
	output.Matrix[1][1] = iScale.Y * cosf(iRotation);
	output.Matrix[1][2] = iTranslation.Y;
	return output;
}

Vector2f MathUtilities::Apply2DTransformToVector2f(Vector2f iVector2f, Matrix3f iMatrix3f) {
	Vector2f output;
	output.X = (iVector2f.X * iMatrix3f.Matrix[0][0]) + (iVector2f.Y * iMatrix3f.Matrix[0][1] + iMatrix3f.Matrix[0][2]);
	output.Y = (iVector2f.X * iMatrix3f.Matrix[1][0]) + (iVector2f.Y * iMatrix3f.Matrix[1][1] + iMatrix3f.Matrix[1][2]);
	return output;
}
