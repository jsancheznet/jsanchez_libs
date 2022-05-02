/*
  TODO LIST
  - mat4 Transpose
  - SIMD Math multiplication
 */
#pragma once

#include "jsanchez_shared.h"

#include <math.h>
#define Pi32 3.14159265358979323846f
#define Sqrt sqrtf
#define Sin sinf
#define Cos cosf
#define Tan tanf
#define Fabs fabs
#define Atan2 atan2

//
// Types
//

#pragma warning(disable: 4201) // Allow for anonymous structs and unions
typedef union vec2
{
    struct
    {
        f32 x, y;
    };

    struct
    {
        f32 u, v;
    };
} vec2;

typedef union vec3
{
    struct
    {
        f32 x, y, z;
    };

    struct
    {
        f32 r, g, b;
    };
} vec3;

typedef union vec4
{
    struct
    {
        f32 x, y, z, w;
    };

    struct
    {
        f32 r, g, b, a;
    };
} vec4;
typedef vec4 color;

typedef union mat4
{
    f32 Elements[4][4];
    f32 Flat[16];
} mat4;

//
// General use functions
//

f32 Remap(f32 Input, f32 InputStart, f32 InputEnd, f32 OutputStart, f32 OutputEnd)
{
    return (Input - InputStart) / (InputEnd - InputStart) * (OutputEnd - OutputStart) + OutputStart;
}

f32 Abs(f32 Input)
{
    return (f32)Fabs(Input);
}

f32 GetRotationAngle(f32 x, f32 y)
{
    return (( (f32)Atan2(y, x) * (f32)180.0f) / 3.14159265359f);
}

#define EPSILON 0.00000011920928955078125f
b32 EqualFloats(f32 A, f32 B)
{
    if(Fabs(A - B) <= EPSILON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

f32 ToRadians(f32 Input)
{
    return Input * (Pi32 / 180.0f);
}

f32 ToDegrees(f32 Input)
{
    return Input * 180.0f / Pi32;
}

//
// Vec2 Functions
//

vec2 Vec2(f32 x, f32 y)
{
    vec2 Result;

    Result.x = x;
    Result.y = y;

    return Result;
}

vec2 Vec2_Add(vec2 A, vec2 B)
{
    return Vec2(A.x + B.x, A.y + B.y);
}

vec2 Vec2_Subtract(vec2 A, vec2 B)
{
    return Vec2(A.x - B.x, A.y - B.y);
}

vec2 Vec2_Scale(vec2 A, f32 Scalar)
{
    return Vec2(A.x * Scalar, A.y * Scalar);
}

f32 Vec2_Dot(vec2 A, vec2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

f32 Vec2_Magnitude(vec2 V)
{
    return Sqrt(Vec2_Dot(V, V));
}

vec2 Vec2_Normalize(vec2 V)
{
    vec2 Result = V;

    f32 Length = Vec2_Magnitude(V);

    Result.x /= Length;
    Result.y /= Length;

    return Result;
}

//
// Vec3 Functions
//

vec3 Vec3(f32 x, f32 y, f32 z)
{
    vec3 Result;

    Result.x = x;
    Result.y = y;
    Result.z = z;

    return Result;
}

vec3 Vec3_Add(vec3 A, vec3 B)
{
    return Vec3(A.x + B.x, A.y + B.y, A.z + B.z);
}

vec3 Vec3_Subtract(vec3 A, vec3 B)
{
    return Vec3(A.x - B.x, A.y - B.y, A.z - B.z);
}

vec3 Vec3_Scale(vec3 A, f32 Scale)
{
    return Vec3(A.x * Scale, A.y * Scale, A.z * Scale);
}

f32 Vec3_Dot(vec3 A, vec3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

vec3 Vec3_Cross(vec3 A, vec3 B)
{
    vec3 Result;

    Result.x = A.y*B.z - A.z*B.y;
    Result.y = A.z*B.x - A.x*B.z;
    Result.z = A.x*B.y - A.y*B.x;

    return(Result);
}

f32 Vec3_Magnitude(vec3 A)
{
    return Sqrt(Vec3_Dot(A, A));
}

vec3 Vec3_Normalize(vec3 V)
{
    vec3 Result = V;

    f32 Length = Vec3_Magnitude(V);

    Result.x /= Length;
    Result.y /= Length;
    Result.z /= Length;

    return Result;
}

//
// Vec4 Functions
//

vec4 Vec4(f32 x, f32 y, f32 z, f32 w)
{
    vec4 Result;

    Result.x = x;
    Result.y = y;
    Result.z = z;
    Result.w = w;

    return Result;
}

vec4 Vec4_Add(vec4 A, vec4 B)
{
    return Vec4(
                 A.x + B.x,
                 A.y + B.y,
                 A.z + B.z,
                 A.w + B.w
               );
}

vec4 Vec4_Subtract(vec4 A, vec4 B)
{
    return Vec4(
                 A.x - B.x,
                 A.y - B.y,
                 A.z - B.z,
                 A.w - B.w
               );
}

vec4 Vec4_Scale(vec4 A, f32 Scalar)
{
    return Vec4(
                A.x * Scalar,
                A.y * Scalar,
                A.z * Scalar,
                A.w * Scalar
               );
}

f32 Vec4_Dot(vec4 A, vec4 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z) + (A.w * B.w);
}

f32 Vec4_Magnitude(vec4 A)
{
    return Sqrt(Vec4_Dot(A, A));
}

vec4 Vec4_Normalize(vec4 A)
{
    vec4 Result = A;

    f32 Length = Vec4_Magnitude(A);

    Result.x /= Length;
    Result.y /= Length;
    Result.z /= Length;
    Result.w /= Length;

    return Result;
}

//
// Mat4 Functions
//

mat4 Mat4(void)
{
    mat4 Result = {0};

    Result.Elements[0][0] = 1.0f;
    Result.Elements[1][1] = 1.0f;
    Result.Elements[2][2] = 1.0f;
    Result.Elements[3][3] = 1.0f;

    return Result;
}

mat4 Mat4_Scale(vec3 A)
{
    mat4 Result = {0};

    Result.Elements[0][0] = A.x;
    Result.Elements[1][1] = A.y;
    Result.Elements[2][2] = A.z;
    Result.Elements[3][3] = 1.0f;

    return (Result);
}

mat4 Mat4_Translate(mat4 A, vec3 V)
{
    mat4 Result = A;

    Result.Elements[3][0] += V.x;
    Result.Elements[3][1] += V.y;
    Result.Elements[3][2] += V.z;

    return (Result);
}

mat4 Mat4_Translation(vec3 A)
{
    mat4 Result = Mat4();

    Result.Elements[3][0] += A.x;
    Result.Elements[3][1] += A.y;
    Result.Elements[3][2] += A.z;

    return Result;
}

mat4 Mat4_Multiply(mat4 Left, mat4 Right)
{
    mat4 Result = Mat4();

    for(i32 Columns = 0; Columns < 4; Columns++)
    {
        for(i32 Rows = 0; Rows < 4; Rows++)
        {
            f32 Sum = 0;
            for(i32 CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
            {
                Sum += Left.Elements[CurrentMatrice][Rows] * Right.Elements[Columns][CurrentMatrice];
            }

            Result.Elements[Columns][Rows] = Sum;
        }
    }

    return (Result);
}

mat4 Mat4_Rotation(f32 Angle, vec3 Axis)
{
    // NOTE(Jorge): The Angle is in Radians!

    mat4 Result = Mat4();

    Axis = Vec3_Normalize(Axis);

    // f32 SinTheta = Sin(ToRadians(Angle));
    // f32 CosTheta = Cos(ToRadians(Angle));
    f32 SinTheta = Sin(Angle);
    f32 CosTheta = Cos(Angle);
    f32 CosValue = 1.0f - CosTheta;

    Result.Elements[0][0] = (Axis.x * Axis.x * CosValue) + CosTheta;
    Result.Elements[0][1] = (Axis.x * Axis.y * CosValue) + (Axis.z * SinTheta);
    Result.Elements[0][2] = (Axis.x * Axis.z * CosValue) - (Axis.y * SinTheta);

    Result.Elements[1][0] = (Axis.y * Axis.x * CosValue) - (Axis.z * SinTheta);
    Result.Elements[1][1] = (Axis.y * Axis.y * CosValue) + CosTheta;
    Result.Elements[1][2] = (Axis.y * Axis.z * CosValue) + (Axis.x * SinTheta);

    Result.Elements[2][0] = (Axis.z * Axis.x * CosValue) + (Axis.y * SinTheta);
    Result.Elements[2][1] = (Axis.z * Axis.y * CosValue) - (Axis.x * SinTheta);
    Result.Elements[2][2] = (Axis.z * Axis.z * CosValue) + CosTheta;

    return (Result);
}

mat4 Mat4_LookAt(vec3 Position, vec3 Target, vec3 Up)
{
    mat4 Result;

    vec3 F = Vec3_Normalize(Vec3_Subtract(Target, Position));
    vec3 S = Vec3_Normalize(Vec3_Cross(F, Up));
    vec3 U = Vec3_Cross(S, F);

    Result.Elements[0][0] = S.x;
    Result.Elements[0][1] = U.x;
    Result.Elements[0][2] = -F.x;
    Result.Elements[0][3] = 0.0f;

    Result.Elements[1][0] = S.y;
    Result.Elements[1][1] = U.y;
    Result.Elements[1][2] = -F.y;
    Result.Elements[1][3] = 0.0f;

    Result.Elements[2][0] = S.z;
    Result.Elements[2][1] = U.z;
    Result.Elements[2][2] = -F.z;
    Result.Elements[2][3] = 0.0f;

    Result.Elements[3][0] = -Vec3_Dot(S, Position);
    Result.Elements[3][1] = -Vec3_Dot(U, Position);
    Result.Elements[3][2] = Vec3_Dot(F, Position);
    Result.Elements[3][3] = 1.0f;

    return (Result);
}

mat4 Mat4_Orthographic(f32 Left, f32 Right, f32 Bottom, f32 Top, f32 Near, f32 Far)
{
    mat4 Result = Mat4();

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);


    return Result;
}

mat4 Mat4_Perspective(f32 FoV, f32 AspectRatio, f32 Near, f32 Far)
{
    // NOTE: * Dirty Hack *
    // I stole this perspective function from Handmade Math and they
    // in turn stole it from khrono.org gluPerspective. This function
    // expects Field of View to be in degrees but i want my API to be
    // have all angles expressed in radians. I simply convert to
    // degrees inside since i do not have a lot of time right now. In
    // the future this functions should be correctly implemented to
    // take in radians.

    mat4 Result = Mat4();

    f32 Cotangent = 1.0f / Tan(ToDegrees(FoV) * 0.5f * Pi32 / 180.0f);

    Result.Elements[0][0] = Cotangent / AspectRatio;
    Result.Elements[1][1] = Cotangent;
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.Elements[3][3] = 0.0f;

    return (Result);
}
