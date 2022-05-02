/*
  TODO LIST
  - Print . on test pass, only go verbose on test fail
  - Test Vec3, Vec2, Vec4
  - Print mat4/vec's to STDOU when a test failed so it's easier to inspect the error
 */

#include <stdio.h>

#include "jsanchez_math.h"

// #pragma warning(disable:4127)  // GLM fails to compile if this warning is turned on!
// #pragma warning(disable: 4201) // GLM warning
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
// #include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp> // glm::rotate vector

void DEBUG_PrintMatrix(mat4 A)
{
    // NOTE(Jorge): This functions prints the matrix as seen on books,
    // row major order. Remember opengl internally works in column
    // major order.
    printf("  %7.2f %7.2f %7.2f %7.2f\n", A.Elements[0][0], A.Elements[1][0], A.Elements[2][0], A.Elements[3][0]);
    printf("  %7.2f %7.2f %7.2f %7.2f\n", A.Elements[0][1], A.Elements[1][1], A.Elements[2][1], A.Elements[3][1]);
    printf("  %7.2f %7.2f %7.2f %7.2f\n", A.Elements[0][2], A.Elements[1][2], A.Elements[2][2], A.Elements[3][2]);
    printf("  %7.2f %7.2f %7.2f %7.2f\n", A.Elements[0][3], A.Elements[1][3], A.Elements[2][3], A.Elements[3][3]);
}

void DEBUG_PrintMatrix( glm::mat4 mat )
{
    // NOTE(Jorge): This functions prints the matrix as seen on books,
    // row major order. Remember opengl internally works in column
    // major order.
        for( int col = 0; col < 4; col++ )
        {
            // transpose the matrix here:
            fprintf( stderr, "  %7.2f %7.2f %7.2f %7.2f\n",
			mat[0][col], mat[1][col], mat[2][col], mat[3][col] );
        }
}

void DEBUG_PrintVector(vec4 A)
{
    printf("  %4.2f %4.2f %4.2f %4.2f\n", A.x, A.y, A.z, A.w);
}

void DEBUG_PrintVector(glm::vec4 A)
{
    printf("  %4.2f %4.2f %4.2f %4.2f\n", A.x, A.y, A.z, A.w);
}

b32 MatrixEquals(mat4 Mine, glm::mat4 Glm)
{
    for(int i = 0; i < 16; i++)
    {
        if(!EqualFloats(glm::value_ptr(Glm)[i], Mine.Flat[i]))
        {
            return false;
        }
    }

    return true;
}

b32 VectorEquals(vec2 Mine, glm::vec2 Glm)
{
    if( EqualFloats(Mine.x, Glm.x) && EqualFloats(Mine.y, Glm.y) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

b32 VectorEquals(vec3 Mine, glm::vec3 Glm)
{
    if(EqualFloats(Mine.x, Glm.x) &&
       EqualFloats(Mine.y, Glm.y) &&
       EqualFloats(Mine.z, Glm.z))
    {
        return true;
    }
    else
    {
        return false;
    }
}

b32 VectorEquals(vec4 Mine, glm::vec4 Glm)
{
    if(EqualFloats(Mine.x, Glm.x) &&
       EqualFloats(Mine.y, Glm.y) &&
       EqualFloats(Mine.z, Glm.z) &&
       EqualFloats(Mine.w, Glm.w))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Run_Vec2_Tests()
{
    printf("----- Running Vec2 Tests ----\n");
    char *Passed = "%s: Passed!\n";
    char *Failed = "%s: Failed!\n";

    { // Vec2_Add
        {
            vec2 Mine = Vec2_Add(Vec2(1.0f, 0.0f), Vec2(1.0f, 0.0f));
            glm::vec2 Glm = glm::vec2(1.0f, 0.0f) + glm::vec2(1.0f, 0.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Add()") : printf(Failed, "Vec2_Add()");
        }

        {
            vec2 Mine = Vec2_Add(Vec2(1.1f, 0.0f), Vec2(1.0f, 0.0f));
            glm::vec2 Glm = glm::vec2(1.0f, 0.0f) + glm::vec2(1.0f, 0.0f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Add()") : printf(Failed, "Vec2_Add()");
        }
    }

    { // Vec2_Subtract
        {
            vec2 Mine = Vec2_Subtract(Vec2(1.0f, 0.0f), Vec2(1.0f, 0.0f));
            glm::vec2 Glm = glm::vec2(1.0f, 0.0f) - glm::vec2(1.0f, 0.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Subtract()") : printf(Failed, "Vec2_Subtract()");
        }

        {
            vec2 Mine = Vec2_Subtract(Vec2(1.1f, 0.0f), Vec2(1.0f, 0.0f));
            glm::vec2 Glm = glm::vec2(1.0f, 0.0f) - glm::vec2(1.0f, 0.0f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Subtract()") : printf(Failed, "Vec2_Subtract()");
        }
    }

    { // Vec2_Scale
        {
            vec2 Mine = Vec2_Scale(Vec2(1.0f, 1.0f), 10.0f);
            glm::vec2 Glm = glm::vec2(1.0f, 1.0f) * 10.0f;
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Scale()") : printf(Failed, "Vec2_Scale()");
        }

        {
            vec2 Mine = Vec2_Scale(Vec2(1.0f, 1.0f), 10.0f);
            glm::vec2 Glm = glm::vec2(1.0f, 1.0f) * 10.1f;
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Scale()") : printf(Failed, "Vec2_Scale()");
        }

    }

    { // Vec2_Dot
        {
            f32 Mine = Vec2_Dot(Vec2(1.0f, 1.0f), Vec2(1.0f, 0.5f));
            f32 Glm  = glm::dot(glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.5f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec2_Dot()") : printf(Failed, "Vec2_Dot()");
        }

        {
            f32 Mine = Vec2_Dot(Vec2(1.06f, 1.0f), Vec2(1.0f, 0.5f));
            f32 Glm  = glm::dot(glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.5f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec2_Dot()") : printf(Failed, "Vec2_Dot()");
        }
    }

    { // Vec2_Magnitude
        {
            f32 Mine = Vec2_Magnitude(Vec2(1.0f, 1.1f));
            f32 Glm  = glm::length(glm::vec2(1.0f, 1.1f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec2_Magnitude()") : printf(Failed, "Vec2_Magnitude()");
        }

        {
            f32 Mine = Vec2_Magnitude(Vec2(1.01f, 1.1f));
            f32 Glm  = glm::length(glm::vec2(1.0f, 1.1f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec2_Magnitude()") : printf(Failed, "Vec2_Magnitude()");
        }
    }

    { // Vec2_Normalize
        {
            vec2 Mine = Vec2_Normalize(Vec2(1.0f, 1.1f));
            glm::vec2 Glm = glm::normalize(glm::vec2(1.0f, 1.1f));
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Normalize()") : printf(Failed, "Vec2_Normalize()");
        }

        {
            vec2 Mine = Vec2_Normalize(Vec2(1.001f, 1.1f));
            glm::vec2 Glm = glm::normalize(glm::vec2(1.0f, 1.1f));
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec2_Normalize()") : printf(Failed, "Vec2_Normalize()");
        }
    }
}

void Run_Vec3_Tests()
{
    printf("----- Running Vec3 Tests ----\n");

    char *Passed = "%s: Passed!\n";
    char *Failed = "%s: Failed!\n";

    { // Vec3_Add
        {
            vec3 Mine = Vec3_Add(Vec3(1.0f, 0.0f, 1.0f), Vec3(1.0f, 1.1f, 2.4f));
            glm::vec3 Glm = glm::vec3(1.0f, 0.0f, 1.0f) + glm::vec3(1.0f, 1.1f, 2.4f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Add()") : printf(Failed, "Vec3_Add()");
        }

        {
            vec3 Mine = Vec3_Add(Vec3(1.0001f, 0.0f, 1.0f), Vec3(1.0f, 1.1f, 2.4f));
            glm::vec3 Glm = glm::vec3(1.0f, 0.0f, 1.0f) + glm::vec3(1.0f, 1.1f, 2.4f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Add()") : printf(Failed, "Vec3_Add()");
        }
    }

    { // Vec3_Subtract
        {
            vec3 Mine = Vec3_Subtract(Vec3(1.0f, 0.0f, 1.0f), Vec3(2.0f, 1.1f, 304.0f));
            glm::vec3 Glm = glm::vec3(1.0f, 0.0f, 1.0f) - glm::vec3(2.0f, 1.1f, 304.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Subtract()") : printf(Failed, "Vec3_Subtract()");
        }

        {
            vec3 Mine = Vec3_Subtract(Vec3(1.0001f, 0.0f, 1.0f), Vec3(2.0f, 1.1f, 304.0f));
            glm::vec3 Glm = glm::vec3(1.0f, 0.0f, 1.0f) - glm::vec3(2.0f, 1.1f, 304.0f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Subtract()") : printf(Failed, "Vec3_Subtract()");
        }
    }

    { // Vec3_Scale
        {
            vec3 Mine = Vec3_Scale(Vec3(1.0f, 1.0f, 1.0f), 10.0f);
            glm::vec3 Glm = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Scale()") : printf(Failed, "Vec3_Scale()");
        }

        {
            vec3 Mine = Vec3_Scale(Vec3(1.0f, 1.0f, 1.0f), 0.0f);
            glm::vec3 Glm = glm::vec3(0.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Scale()") : printf(Failed, "Vec3_Scale()");
        }
    }

    { // Vec3_Dot
        {
            f32 Mine = Vec3_Dot(Vec3(1.0f, 0.0f, 1.0f), Vec3(10.0f, 11.0f, 12.0f));
            f32 Glm = glm::dot(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec3_Dot()") : printf(Failed, "Vec3_Dot()");
        }

        {
            f32 Mine = Vec3_Dot(Vec3(1.001f, 0.0f, 1.0f), Vec3(10.0f, 11.0f, 12.0f));
            f32 Glm = glm::dot(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec3_Dot()") : printf(Failed, "Vec3_Dot()");
        }
    }

    { // Vec3_Cross
        {
            vec3 Mine = Vec3_Cross(Vec3(1.0f, 0.0f, 1.0f), Vec3(10.0f, 11.0f, 12.0f));
            glm::vec3 Glm = glm::cross(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Cross()") : printf(Failed, "Vec3_Cross()");
        }

        {
            vec3 Mine = Vec3_Cross(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 Glm = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Cross()") : printf(Failed, "Vec3_Cross()");
        }
    }

    { // Vec3_Magnitude
        {
            f32 Mine = Vec3_Magnitude(Vec3(1.0f, 1.0f, 1.0f));
            f32 Glm = glm::length(glm::vec3(1.0f, 1.0f, 1.0f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec3_Magnitude()") : printf(Failed, "Vec3_Magnitude()");
        }

        {
            f32 Mine = Vec3_Magnitude(Vec3(1.0f, 1.0f, 1.0f));
            f32 Glm = glm::length(glm::vec3(1.00001f, 1.0f, 1.0f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec3_Magnitude()") : printf(Failed, "Vec3_Magnitude()");
        }
    }

    { // Vec3_Normalize
        {
            vec3 Mine = Vec3_Normalize(Vec3(10.0f, 0.0f, 0.0f));
            glm::vec3 Glm = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Normalize()") : printf(Failed, "Vec3_Normalize()");
        }

        {
            vec3 Mine = Vec3_Normalize(Vec3(10.0f, 0.0f, 0.01f));
            glm::vec3 Glm = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec3_Normalize()") : printf(Failed, "Vec3_Normalize()");
        }
    }
}

void Run_Vec4_Tests()
{
    printf("----- Running Vec4 Tests ----\n");
    char *Passed = "%s: Passed!\n";
    char *Failed = "%s: Failed!\n";

    { // Vec4_Add
        {
            vec4 Mine = Vec4_Add(Vec4(1.0f, 0.0f, 1.0f, 10.0f), Vec4(1.0f, 1.1f, 2.4f, 10.0f));
            glm::vec4 Glm = glm::vec4(1.0f, 0.0f, 1.0f, 10.0f) + glm::vec4(1.0f, 1.1f, 2.4f, 10.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Add()") : printf(Failed, "Vec4_Add()");
        }

        {
            vec4 Mine = Vec4_Add(Vec4(1.0001f, 0.0f, 1.0f, 11.0f), Vec4(1.0f, 1.1f, 2.4f, 0.0f));
            glm::vec4 Glm = glm::vec4(1.0f, 0.0f, 1.0f, 11.0f) + glm::vec4(1.0f, 1.1f, 2.4f, 0.0f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Add()") : printf(Failed, "Vec4_Add()");
        }
    }

    { // Vec4_Subtract
        {
            vec4 Mine = Vec4_Subtract(Vec4(1.0f, 0.0f, 1.0f, 0.0f), Vec4(2.0f, 1.1f, 304.0f, 0.0f));
            glm::vec4 Glm = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f) - glm::vec4(2.0f, 1.1f, 304.0f, 0.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Subtract()") : printf(Failed, "Vec4_Subtract()");
        }

        {
            vec4 Mine = Vec4_Subtract(Vec4(1.0001f, 0.0f, 1.0f, 11.0f), Vec4(2.0f, 1.1f, 304.0f, 11.0f));
            glm::vec4 Glm = glm::vec4(1.0f, 0.0f, 1.0f, 11.0f) - glm::vec4(2.0f, 1.1f, 304.0f, 11.0f);
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Subtract()") : printf(Failed, "Vec4_Subtract()");
        }
    }

    { // Vec4_Scale
        {
            vec4 Mine = Vec4_Scale(Vec4(1.0f, 1.0f, 1.0f, 10.0f), 10.0f);
            glm::vec4 Glm = glm::vec4(1.0f, 1.0f, 1.0f, 10.0f) * 10.0f;
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Scale()") : printf(Failed, "Vec4_Scale()");
        }

        {
            vec4 Mine = Vec4_Scale(Vec4(1.0f, 1.0f, 1.0f, 1.1f), 0.0f);
            glm::vec4 Glm = glm::vec4(0.0f);
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Scale()") : printf(Failed, "Vec4_Scale()");
        }
    }

    { // Vec4_Dot
        {
            f32 Mine = Vec4_Dot(Vec4(1.0f, 0.0f, 1.0f, 10.0f), Vec4(10.0f, 11.0f, 12.0f, 10.0f));
            f32 Glm = glm::dot(glm::vec4(1.0f, 0.0f, 1.0f, 10.0f), glm::vec4(10.0f, 11.0f, 12.0f, 10.f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec4_Dot()") : printf(Failed, "Vec4_Dot()");
        }

        {
            f32 Mine = Vec4_Dot(Vec4(1.001f, 0.0f, 1.0f, 1.1f), Vec4(10.0f, 11.0f, 12.0f, 1.1f));
            f32 Glm = glm::dot(glm::vec4(1.0f, 0.0f, 1.0f, 1.1f), glm::vec4(10.0f, 11.0f, 12.0f, 1.1f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec4_Dot()") : printf(Failed, "Vec4_Dot()");
        }
    }

    { // Vec4_Cross
        // NOTE: Cross product only exists in 3 and 7th dimensiones
    }

    { // Vec4_Magnitude
        {
            f32 Mine = Vec4_Magnitude(Vec4(1.0f, 1.0f, 1.0f, 10.0f));
            f32 Glm = glm::length(glm::vec4(1.0f, 1.0f, 1.0f, 10.0f));
            EqualFloats(Mine, Glm) ? printf(Passed,"Vec4_Magnitude()") : printf(Failed, "Vec4_Magnitude()");
        }

        {
            f32 Mine = Vec4_Magnitude(Vec4(1.0f, 1.0f, 1.0f, 11.0f));
            f32 Glm = glm::length(glm::vec4(1.00001f, 1.0f, 1.0f, 11.0f));
            !EqualFloats(Mine, Glm) ? printf(Passed,"Vec4_Magnitude()") : printf(Failed, "Vec4_Magnitude()");
        }
    }

    { // Vec4_Normalize
        {
            vec4 Mine = Vec4_Normalize(Vec4(1.0f, 2.0f, 3.0f, 4.0f));
            glm::vec4 Glm = glm::normalize(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
            VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Normalize()") : printf(Failed, "Vec4_Normalize()");
        }

        {
            vec4 Mine = Vec4_Normalize(Vec4(10.0f, 0.0f, 0.01f, 12.0f));
            glm::vec4 Glm = glm::normalize(glm::vec4(1.0f, 0.0f, 0.0f, 12.0f));
            !VectorEquals(Mine, Glm) ? printf(Passed,"Vec4_Normalize()") : printf(Failed, "Vec4_Normalize()");
        }
    }
}

void Run_Mat4_Tests()
{
    printf("----- Running Mat4 Tests ----\n");
    char *Passed = "%s: Passed!\n";
    char *Failed = "%s: Failed!\n";

    { // Mat4() creates an identity matrix
        mat4 Mine = Mat4();
        glm::mat4 Glm = glm::mat4(1.0f);
        MatrixEquals(Mine, Glm) ? printf(Passed,"Mat4()") : printf(Failed, "Mat4()");
    }

    { // Mat4_Scale(vec3 A)
        {
            mat4 Mine = Mat4_Scale(Vec3(2.0f, 2.0f, 2.0f));
            glm::mat4 Glm = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed,"Mat4_Scale()") : printf(Failed, "Mat4_Scale()");
        }

        {
            mat4 Mine = Mat4_Scale(Vec3(10.0f, 11.0f, 9.0f));
            glm::mat4 Glm = glm::scale(glm::vec3(1.0f, 2.0f, 2.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed,"Mat4_Scale()") : printf(Failed, "Mat4_Scale()");
        }

        {
            mat4 Mine = Mat4_Scale(Vec3(10.0f, 11.0f, 9.0f));
            glm::mat4 Glm = glm::mat4(1.0f);
            !MatrixEquals(Mine, Glm) ? printf(Passed,"Mat4_Scale()") : printf(Failed, "Mat4_Scale()");
        }
    }

    { // Mat4_Translate
        {
            mat4 Mine = Mat4_Translate(Mat4(), Vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Translate()") : printf(Failed, "Mat4_Translate()");
        }

        {
            mat4 Mine = Mat4_Translate(Mat4(), Vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm = glm::translate(glm::mat4(1.0f), glm::vec3(11.0f, 11.0f, 12.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Translate()") : printf(Failed, "Mat4_Translate()");
        }

        {
            mat4 Test = Mat4();
            mat4 Mine = Mat4_Translate(Test, Vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm = glm::translate(glm::mat4(1.0f), glm::vec3(11.0f, 11.0f, 12.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Translate()") : printf(Failed, "Mat4_Translate()");
        }
    }

    { // Mat4_Translation
        {
            mat4 Mine = Mat4_Translation(Vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Translation()") : printf(Failed, "Mat4_Translation()");
        }

        {
            mat4 Mine = Mat4_Translation(Vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm = glm::translate(glm::mat4(1.0f), glm::vec3(11.0f, 11.0f, 12.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Translation()") : printf(Failed, "Mat4_Translation()");
        }
    }

    { // Mat4_Multiply

        {
            mat4 Mine_A = Mat4_Translation(Vec3(10.0f, 11.0f, 12.0f));
            mat4 Mine_B = Mat4_Translation(Vec3(54.0f, 22.0f, 895.0f));
            mat4 Mine = Mat4_Multiply(Mine_A, Mine_B);

            glm::mat4 Glm_A = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm_B = glm::translate(glm::mat4(1.0f), glm::vec3(54.0f, 22.0f, 895.0f));
            glm::mat4 Glm = Glm_A * Glm_B;

            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Multiply()") : printf(Failed, "Mat4_Multiply()");
        }

        {
            mat4 Mine_A = Mat4_Translation(Vec3(11.0f, 11.0f, 12.0f));
            mat4 Mine_B = Mat4_Translation(Vec3(54.0f, 22.0f, 895.0f));
            mat4 Mine = Mat4_Multiply(Mine_A, Mine_B);

            glm::mat4 Glm_A = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 11.0f, 12.0f));
            glm::mat4 Glm_B = glm::translate(glm::mat4(1.0f), glm::vec3(54.0f, 22.0f, 895.0f));
            glm::mat4 Glm = Glm_A * Glm_B;

            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Multiply()") : printf(Failed, "Mat4_Multiply()");
        }
    }

    { // Mat4_Rotation
        {
            mat4 Mine = Mat4_Rotation(ToRadians(90.0f),      Vec3(0.0f, 0.0f, 20.0f));
            glm::mat4 Glm = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Rotation()") : printf(Failed, "Mat4_Rotation()");
        }

        {
            mat4 Mine = Mat4_Rotation(ToRadians(113.5f), Vec3(123.0f, 123.0f, 77.0f));
            glm::mat4 Glm = glm::rotate(glm::radians(113.5f), glm::vec3(123.0f, 123.0f, 77.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Rotation()") : printf(Failed, "Mat4_Rotation()");
        }

        {
            mat4 Mine = Mat4_Rotation(ToRadians(113.5f), Vec3(123.0f, 123.0f, 72.0f));
            glm::mat4 Glm = glm::rotate(glm::radians(113.5f), glm::vec3(123.0f, 123.0f, 77.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Rotation()") : printf(Failed, "Mat4_Rotation()");
        }
    }

    { // Mat4_LookAt
        {
            mat4 Mine = Mat4_LookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(-10.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Glm = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_LookAt()") : printf(Failed, "Mat4_LookAt()");
        }

        {
            mat4 Mine = Mat4_LookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(-11.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Glm = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-11.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_LookAt()") : printf(Failed, "Mat4_LookAt()");
        }

        {
            mat4 Mine = Mat4_LookAt(Vec3(1.0f, 0.0f, 0.0f), Vec3(-10.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Glm = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_LookAt()") : printf(Failed, "Mat4_LookAt()");
        }
    }

    { // Mat4_Perspective
        {
            mat4 Mine = Mat4_Perspective(ToRadians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
            glm::mat4 Glm = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Perspective()") : printf(Failed, "Mat4_Perspective()");
        }

        {
            mat4 Mine = Mat4_Perspective(ToRadians(10.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
            glm::mat4 Glm = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Perspective()") : printf(Failed, "Mat4_Perspective()");
        }
    }

    { // Mat4_Orthographic
        {
            mat4 Mine = Mat4_Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
            glm::mat4 Glm = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
            MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Orthographic()") : printf(Failed, "Mat4_Orthographic()");
        }

        {
            mat4 Mine = Mat4_Orthographic(-9.9f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
            glm::mat4 Glm = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
            !MatrixEquals(Mine, Glm) ? printf(Passed, "Mat4_Orthographic()") : printf(Failed, "Mat4_Orthographic()");
        }
    }
}

void main()
{
    Run_Vec2_Tests();
    Run_Vec3_Tests();
    Run_Vec4_Tests();
    Run_Mat4_Tests();
}
