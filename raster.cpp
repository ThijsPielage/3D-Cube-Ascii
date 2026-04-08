#include "raster.h"
#include <algorithm>
#include <iostream>

using namespace std;

Frame buildEmptyFrame(size_t width, size_t height) {
    Frame frame;
    string emptyLine(width, ' ');
    for (size_t i = 0; i < height; i++) {
        frame.push_back(emptyLine);
    }
    return frame;
}

Frame buildEmptySquareFrame(size_t size) {
    return buildEmptyFrame(2* size, size);
}

void showFrame(const Frame& frame) {
    for (size_t i = 0; i < frame.size(); i++) {
        cout << frame[i] << endl;
    }
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

DepthBuffer initializeDepthBuffer(const Frame& frame) {
    size_t height = frame.size();
    size_t width = frame[0].size();

    return DepthBuffer(height, vector<float>(width, 1e9));
}

bool pointInFrame(const Frame& frame, const GridPoint& p) {
    return pointInFrame(frame, p.x, p.y);
}

bool pointInFrame(const Frame& frame, int x, int y) {
    size_t height = frame.size();
    size_t width = frame[0].size();

    if (!(0 <= x && x < (int)width)) {
        return false;
    }
    if (!(0 <= y && y < (int)height)) {
        return false;
    }
    return true;
}

bool pointInTriangle(const GridPoint& p, const GridTriangle& t) {
    auto edge = [](GridPoint a, GridPoint b, GridPoint p) {
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    };

    int e1 = edge(t.p1, t.p2, p);
    int e2 = edge(t.p2, t.p3, p);
    int e3 = edge(t.p3, t.p1, p);

    return (e1 >= 0 && e2 >= 0 && e3 >= 0) ||
           (e1 <= 0 && e2 <= 0 && e3 <= 0);
}

void drawPoint(Frame& frame, const GridPoint p, char c) {
    frame[p.y][p.x] = c;
}

void drawLine(Frame& frame, GridPoint p1, GridPoint p2, char c){
    if (p1.x == p2.x && p1.y == p2.y) {
        if (pointInFrame(frame, p1)) {
            frame[p1.y][p1.x] = c;      
        }
        return;
    }

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    if (abs(dy) < abs(dx)) {
        // Loop over x
        float gradient = float(dy) / dx;
        if (p1.x > p2.x) {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        for (int x = p1.x; x <= p2.x; x++) {
            int y = int(round(p1.y + (x - p1.x) * gradient));
            if (pointInFrame(frame, x, y)) {
                frame[y][x] = c;
            }
        }

    } else {
        // Loop over y
        float invGradient = float(dx) / dy;
        if (p1.y > p2.y) {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }

        for (int y = p1.y; y <= p2.y; y++) {
            int x = int(round(p1.x + (y - p1.y) * invGradient));
            if (pointInFrame(frame, x, y)) {
                frame[y][x] = c;
            }
        }
    }
}

BoundingBox triangleBBox(const Frame& frame, const GridTriangle& t) {
    size_t height = frame.size();
    size_t width = frame[0].size();
    int minx = min(t.p1.x, min(t.p2.x, t.p3.x));
    int maxx = max(t.p1.x, max(t.p2.x, t.p3.x));
    int miny = min(t.p1.y, min(t.p2.y, t.p3.y));
    int maxy = max(t.p1.y, max(t.p2.y, t.p3.y));
    minx = max(0, minx);
    maxx = min(maxx, (int)width - 1);
    miny = max(0, miny);
    maxy = min(maxy, (int)height - 1);

    BoundingBox result = {minx, maxx, miny, maxy};
    return result;
}

float edgeFunction(const GridPoint& a, const GridPoint& b, const GridPoint& c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

void drawTriangle(Frame& frame,
                  DepthBuffer& db,
                  const GridTriangle& tri,
                  const Vector3D& a,
                  const Vector3D& b,
                  const Vector3D& c,
                  const Vector3D& cameraDir,
                  char shade)
{
    GridPoint p0 = tri.p1;
    GridPoint p1 = tri.p2;
    GridPoint p2 = tri.p3;

    int width = frame[0].size();
    int height = frame.size();

    // Bounding box
    int minX = std::max(0, std::min({p0.x, p1.x, p2.x}));
    int maxX = std::min(width - 1, std::max({p0.x, p1.x, p2.x}));
    int minY = std::max(0, std::min({p0.y, p1.y, p2.y}));
    int maxY = std::min(height - 1, std::max({p0.y, p1.y, p2.y}));

    float area = edgeFunction(p0, p1, p2);

    float depthA = dot(a, cameraDir);
    float depthB = dot(b, cameraDir);
    float depthC = dot(c, cameraDir);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {

            GridPoint p = {x, y};

            float w0 = edgeFunction(p1, p2, p);
            float w1 = edgeFunction(p2, p0, p);
            float w2 = edgeFunction(p0, p1, p);

            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0)) {

                w0 /= area;
                w1 /= area;
                w2 /= area;

                float depth =
                    w0 * depthA +
                    w1 * depthB +
                    w2 * depthC;

                if (depth < db[y][x]) {
                    db[y][x] = depth;
                    frame[y][x] = shade;
                }
            }
        }
    }
}