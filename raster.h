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

// Build / show ASCII frame
vector<string> buildEmptyFrame(size_t width, size_t height);
void showFrame(const vector<string>& frame);


// Point helpers
bool pointInFrame(const vector<string>& frame, const GridPoint& p);
bool pointInFrame(const vector<string>& frame, int x, int y);

bool pointInTriangle(const GridPoint& p, const GridPoint& a, const GridPoint& b, const GridPoint& c);

// Drawing functions
void drawLine(vector<string>& frame, GridPoint p1, GridPoint p2, char c);

BoundingBox triangleBBox(const vector<string>& frame, const GridTriangle& t);

void drawTriangle(vector<string>& frame, const GridTriangle& t, char c);

void drawTriangleOutline(vector<string>& frame, const GridTriangle& t, char c);