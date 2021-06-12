#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "tgaimage.h"
#include "Triangle.h"
#include "MathCommon.h"
#include <list>
#include <vector>

#define PI 3.1415926

#define PERSPECTIVE_DIVIDE
#define VERTEX_COLOR

using namespace std;


void ClearTarget(TGAImage& image, const uint32_t& width, const uint32_t& height, const TGAColor& color)
{
	for (uint32_t i = 0; i < width; ++i)
	{
		for (uint32_t j = 0; j < height; ++j)
		{
			image.set(i, j, color);
		}
	}
}

void DrawTriangleBC(TGAImage& image, const vec4f& v0, const vec4f& v1, const vec4f& v2)
{
    // Calculate the Min and MaxBounds
    // Points to Check for
    vec3f minBounds;
    minBounds.x = min(v0.x, min(v1.x, v2.x));
    minBounds.y = min(v0.y, min(v1.y, v2.y));

    vec3f maxBounds;
    maxBounds.x = max(v0.x, max(v1.x, v2.x));
    maxBounds.y = max(v0.y, max(v1.y, v2.y));

    vec3f c0 = vec3f(1, 0, 0);
    vec3f c1 = vec3f(0, 1, 0);
    vec3f c2 = vec3f(0, 0, 1);

#ifdef PERSPECTIVE_DIVIDE
    c0 /= v0.w;
    c1 /= v1.w;
    c2 /= v2.w;
#endif // PERSPECTIVE_DIVIDE

    vec3f st0 = vec3f(1, 1, 0);
    vec3f st1 = vec3f(0, 1, 0);
    vec3f st2 = vec3f(0, 0, 0);

#ifdef PERSPECTIVE_DIVIDE
    st0 /= v0.w;
    st1 /= v1.w;
    st2 /= v2.w;
#endif // DEBUG

    float area = vec2f::EdgeFunction(v0.GetXY(), v1.GetXY(), v2.GetXY());

    for (int x = minBounds.x; x <= maxBounds.x; ++x)
    {
        for (int y = minBounds.y; y <= maxBounds.y; ++y)
        {
            vec3f pos = vec3f(x, y, 0);
            // Direction Vectors
            vec3f V0V1 = v1.GetXYZ() - v0.GetXYZ();    // From V0 to V1
            vec3f V0V2 = v2.GetXYZ() - v0.GetXYZ();    // From V0 to V2
            vec3f V0Pos = pos - v0.GetXYZ();  // From V0 to Pos

            // Calculate the Signed Area for each edge of the triangle with the point
            float u = vec2f::EdgeFunction(v1.GetXY(), v2.GetXY(), pos.GetXY());
            float s = vec2f::EdgeFunction(v2.GetXY(), v0.GetXY(), pos.GetXY());
            float t = vec2f::EdgeFunction(v0.GetXY(), v1.GetXY(), pos.GetXY());

            // We are checking if its less than 0, because we are considering couter clockwise vertices
            // So out point lies inside the triangle if the weigts (lamda's) < 0
            if (u <= 0 && s <= 0 && t <= 0 )
            {
                // Calculate the weight's by dividing the area of the entire triangle
                u = u / area;
                s = s / area;
                t = t / area;

                //  Calculate the Z interpolation (Correctly if we have defined perspective divide(Only to show the difference)
                // interpolate z, interpolate w  and (interpolatedz/interpolatedw)

#ifdef PERSPECTIVE_DIVIDE
                float z = 1 / ((u / v0.w) + (s / v1.w) + (t / v2.w));
#endif // PERSPECTIVE_DIVIDE

                // Calculate interpolated vertex attributes
                vec3f linearColor = (c0 * u + c1 * s + c2 * t);
                vec3f tc = (st0 * u + st1 * s + st2 * t) ;

                // multiply by interpolated Z for perspective correction
#ifdef PERSPECTIVE_DIVIDE
                linearColor *= z;
                tc *= z;
#endif // DEBUG

                const int M = 10;
                // checkerboard pattern
                float p = (fmod(tc.x * M, 1.0) > 0.5) ^ (fmod(tc.y * M, 1.0) < 0.5);
                TGAColor color;

#ifdef VERTEX_COLOR
                color = TGAColor(linearColor.x * 255, linearColor.y * 255, linearColor.z * 255);
#endif // VERTEX_COLOR

#ifndef VERTEX_COLOR
                color = TGAColor(p * 255, p * 255, p * 255);
#endif // !VERTEX_COLOR


                image.set(pos.x, pos.y, color);
            }
        }
    }
}


void DrawTriangleBC(TGAImage& image, const vec4f& v0, const vec4f& v1, const vec4f& v2, vec3f c0, vec3f c1, vec3f c2)
{
    // Calculate the Min and MaxBounds
    // Points to Check for
    vec3f minBounds;
    minBounds.x = min(v0.x, min(v1.x, v2.x));
    minBounds.y = min(v0.y, min(v1.y, v2.y));

    vec3f maxBounds;
    maxBounds.x = max(v0.x, max(v1.x, v2.x));
    maxBounds.y = max(v0.y, max(v1.y, v2.y));


#ifdef PERSPECTIVE_DIVIDE
    c0 /= v0.w;
    c1 /= v1.w;
    c2 /= v2.w;
#endif // PERSPECTIVE_DIVIDE

    vec3f st0 = vec3f(1, 1, 0);
    vec3f st1 = vec3f(0, 1, 0);
    vec3f st2 = vec3f(0, 0, 0);

#ifdef PERSPECTIVE_DIVIDE
    st0 /= v0.w;
    st1 /= v1.w;
    st2 /= v2.w;
#endif // DEBUG

    float area = vec2f::EdgeFunction(v0.GetXY(), v1.GetXY(), v2.GetXY());

    for (int x = minBounds.x; x <= maxBounds.x; ++x)
    {
        for (int y = minBounds.y; y <= maxBounds.y; ++y)
        {
            vec3f pos = vec3f(x, y, 0);
            // Direction Vectors
            vec3f V0V1 = v1.GetXYZ() - v0.GetXYZ();    // From V0 to V1
            vec3f V0V2 = v2.GetXYZ() - v0.GetXYZ();    // From V0 to V2
            vec3f V0Pos = pos - v0.GetXYZ();  // From V0 to Pos

            // Calculate the Signed Area for each edge of the triangle with the point
            float u = vec2f::EdgeFunction(v1.GetXY(), v2.GetXY(), pos.GetXY());
            float s = vec2f::EdgeFunction(v2.GetXY(), v0.GetXY(), pos.GetXY());
            float t = vec2f::EdgeFunction(v0.GetXY(), v1.GetXY(), pos.GetXY());

            // We are checking if its less than 0, because we are considering couter clockwise vertices
            // So out point lies inside the triangle if the weigts (lamda's) < 0
            if (u <= 0 && s <= 0 && t <= 0)
            {
                // Calculate the weight's by dividing the area of the entire triangle
                u = u / area;
                s = s / area;
                t = t / area;

                //  Calculate the Z interpolation (Correctly if we have defined perspective divide(Only to show the difference)
                // interpolate z, interpolate w  and (interpolatedz/interpolatedw)

#ifdef PERSPECTIVE_DIVIDE
                float z = 1 / ((u / v0.w) + (s / v1.w) + (t / v2.w));
#endif // PERSPECTIVE_DIVIDE

                // Calculate interpolated vertex attributes
                vec3f linearColor = (c0 * u + c1 * s + c2 * t);
                vec3f tc = (st0 * u + st1 * s + st2 * t);

                // multiply by interpolated Z for perspective correction
#ifdef PERSPECTIVE_DIVIDE
                linearColor *= z;
                tc *= z;
#endif // DEBUG

                const int M = 10;
                // checkerboard pattern
                float p = (fmod(tc.x * M, 1.0) > 0.5) ^ (fmod(tc.y * M, 1.0) < 0.5);
                TGAColor color;

#ifdef VERTEX_COLOR
                color = TGAColor(linearColor.x * 255, linearColor.y * 255, linearColor.z * 255);
#endif // VERTEX_COLOR

#ifndef VERTEX_COLOR
                color = TGAColor(p * 255, p * 255, p * 255);
#endif // !VERTEX_COLOR


                image.set(pos.x, pos.y, color);
            }
        }
    }
}

void ClipAgainstPlane(const Triangle& triangle, std::list<Triangle>& outlist, Plane plane)
{
    bool isV0Inside = IsInsidePlane(plane, triangle.vertices[0]);
    bool isV1Inside = IsInsidePlane(plane, triangle.vertices[1]);
    bool isV2Inside = IsInsidePlane(plane, triangle.vertices[2]);

    if (isV0Inside && isV1Inside && isV2Inside)
    {
        outlist.push_back(triangle);
        return;
    }

    else if (!isV0Inside && !isV1Inside && !isV2Inside)
    {
        return;
    }

    else
    {
        std::vector<vec4f> vertices;
        std::vector<vec3f> colors;

        for (int i = 0; i < 3; ++i)
        {
            vec4f prev = triangle.vertices[(i + 2) % 3];
            vec4f curr = triangle.vertices[i];

            vec3f prevC = triangle.colors[(i + 2) % 3];
            vec3f currC = triangle.colors[i];

            bool isPrevInside = IsInsidePlane(plane, prev);
            bool isCurrInside = IsInsidePlane(plane, curr);

            if (isPrevInside != isCurrInside)
            {
                float ratio = GetIntersectionRatio(plane, curr, prev);

                vec4f point = prev + (curr - prev) * ratio;
                vec3f color = prevC + (currC - prevC) * ratio;

                vertices.push_back(point);
                colors.push_back(color);
            }

            if (isCurrInside)
            {
                vertices.push_back(curr);
                colors.push_back(currC);
            }
        }

        for (int i = 0; i < vertices.size() - 2; ++i)
        {
            outlist.push_back(Triangle(vertices[0], vertices[i + 1], vertices[i + 2], colors[0], colors[i+1], colors[i+2]));
        }
    }

}


void ClipTriangle(const Triangle& triangle, std::list<Triangle>& outList)
{
    // Lamda to check if the triangle is inside view frustrum
    auto compare = [](const vec4f& vertex)
    {
        return (fabsf(vertex.x) <= vertex.w && fabsf(vertex.y) <= vertex.w && fabsf(vertex.z) <= vertex.w);
    };

    // Check if Entire triangle is inside View Frustum
    if (compare(triangle.vertices[0]) && compare(triangle.vertices[1]) && compare(triangle.vertices[2]))
    {
        outList.push_back(triangle);

        return;
    }

    // One more list to swap the triangles
    std::list<Triangle> inTriList;

    inTriList.push_back(triangle);


    auto loopOver = [](std::list<Triangle>& inList, std::list<Triangle>& outList, Plane plane)
    {
        while (inList.size() > 0)
        {
            ClipAgainstPlane(inList.front(), outList, plane);

            inList.pop_front(); //
        }
    };

    loopOver(inTriList, outList, Plane::POSITIVEW); 
    loopOver(outList, inTriList, Plane::RIGHT);
    loopOver(inTriList, outList, Plane::LEFT);
    loopOver(outList, inTriList, Plane::TOP);
    loopOver(inTriList, outList, Plane::BOTTOM);
    loopOver(outList, inTriList, Plane::NEAR);
    loopOver(inTriList, outList, Plane::FAR);

}

void ConvertToRasterSpace(const vec3f& vertex, vec3f& rasterVertex,
    const float& r, const float& t, const float& l, const float& b, const float& near,
    const uint32_t& width, const uint32_t height)
{
    // Since the vertex is already in camera space. Because camera is at origin looking at -z
    vec3f vertex_screen = vec3f(near * vertex.x / -vertex.z, near * vertex.y / -vertex.z, -vertex.z);

    // Map from Frustum corners to the Cube (i.e -1 to 1)
    vec3f vertex_ndc;
    vertex_ndc.x = (2 * vertex_screen.x / (r - l)) + ((r + l) / (r - l));
    vertex_ndc.y = (2 * vertex_screen.y / (t - b)) + ((t + b) / (t - b));
    vertex_ndc.z = vertex_screen.z;

    // Convert from NDC to Raster
    rasterVertex.x = (vertex_ndc.x + 1) * 0.5f * width;

    // in raster space Y is down, top left corner of the screen is (0, 0)
    rasterVertex.y = (1 - vertex_ndc.y) * 0.5f * height;
    rasterVertex.z = vertex_ndc.z;
}


int main()
{
	uint32_t Width = 800, Height = 600;
	TGAImage image(Width, Height, TGAImage::RGB);

    ClearTarget(image, Width, Height, TGAColor(0, 0, 0));

    // Calculate canvas corners.
    float zNear = 0.03;
    float zFar = 1000;
    float fov = 60.0f * PI / 180.0f;

    float aspect = Width / Height;

    float cWidth = 2 * tan(fov / 2) * zNear;

    float right = cWidth * aspect;
    float left = -right;
    float top = cWidth;
    float bottom = -top;

    vec3f v0(30.f, 130.f, -40.f);
    vec3f v1(30.f, -130.f, -80.f);
    vec3f v2(-180.f, -10.f, -120.f);

    //Calculate RasterSpace position of the vertices
    vec4f rasterv0, rasterv1, rasterv2;

    mat4f projectionMatrix;

    mat4f::CreateProjectionMatrix(projectionMatrix, right, left, top, bottom, zNear, zFar);
    vec4f clip0, clip1, clip2;

    // Might feel like its a column major;
    clip0 = projectionMatrix * vec4f(v0);
    clip1 = projectionMatrix * vec4f(v1);
    clip2 = projectionMatrix * vec4f(v2);

    Triangle tri(clip0, clip1, clip2);

    // List to hold all the new clipped triangles
    std::list<Triangle> outTriangleList;

    ClipTriangle(tri, outTriangleList);

    auto convert = [](const vec4f& clipVertex, float width, float height) -> vec4f
    {
        // Perspective division
        vec4f ndcVertex = clipVertex;
        ndcVertex.x = clipVertex.x / clipVertex.w;
        ndcVertex.y = clipVertex.y / clipVertex.w;
        ndcVertex.z = clipVertex.z / clipVertex.w;

        ndcVertex.x = (ndcVertex.x + 1) * 0.5f * width; // 0-widht range

        // in raster space Y is down, top left corner of the screen is (0, 0)
        ndcVertex.y = (1 - ndcVertex.y) * 0.5f * height; // 0-height range
        ndcVertex.z = (ndcVertex.z + 1) * 0.5f;         // 0-1 range

        return ndcVertex;
    };

    for (auto itr : outTriangleList)
    {
        rasterv0 = convert(itr.vertices[0], Width, Height);
        rasterv1 = convert(itr.vertices[1], Width, Height);
        rasterv2 = convert(itr.vertices[2], Width, Height);


#ifdef PERSPECTIVE_DIVIDE
        DrawTriangleBC(image, rasterv0, rasterv1, rasterv2, itr.colors[0], itr.colors[1], itr.colors[2]);

#ifndef VERTEX_COLOR
        image.write_tga_file("TrianglePerstc.tga");
#endif // !VERTEX_COLOR
#ifdef VERTEX_COLOR
        image.write_tga_file("TrianglePersvc.tga");
#endif // VERTEX_COLOR
#endif // PERSPECTIVE_DIVIDE


#ifndef PERSPECTIVE_DIVIDE
        DrawTriangleBC(image, rasterv0, rasterv1, rasterv2);

#ifndef VERTEX_COLOR
        image.write_tga_file("TriangleNoPerstc.tga");
#endif // !VERTEX_COLOR
#ifdef VERTEX_COLOR
        image.write_tga_file("TriangleNoPersvc.tga");
#endif // VERTEX_COLOR
#endif // PERSPECTIVE_DIVIDE
    }
    return 0;
}