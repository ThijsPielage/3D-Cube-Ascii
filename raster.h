#pragma once
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct GridPoint {
    int x, y; 
};

struct GridTriangle {
    GridPoint p1, p2, p3;
};

// Bounding box for triangle on the frame
struct BoundingBox {
    int minx;
    int maxx;
    int miny;
    int maxy;
};

using Frame = vector<string>;

// Build / show ASCII frame
Frame buildEmptyFrame(size_t width, size_t height);
void showFrame(const Frame& frame);


// Point helpers
bool pointInFrame(const Frame& frame, const GridPoint& p);
bool pointInFrame(const Frame& frame, int x, int y);
bool pointInTriangle(const GridPoint& p, const GridTriangle& t);

// Drawing functions
BoundingBox triangleBBox(const Frame& frame, const GridTriangle& t);

void drawPoint(Frame& frame, const GridPoint p, char c);
void drawLine(Frame& frame, GridPoint p1, GridPoint p2, char c);
void drawTriangleOutline(Frame& frame, const GridTriangle& t, char c);
void drawTriangle(Frame& frame, const GridTriangle& t, char c);