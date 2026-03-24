#include<iostream>
#include<vector>
#include<string>
#include<cmath>

using namespace std;

struct GridPoint {
    int x, y;
};

struct GridTriangle {
    GridPoint p1, p2, p3;
};

struct Point3D {
    float x, y, z;
};

struct Triangle3D {
    Point3D p1, p2, p3;
};

struct CubeMesh {
    Point3D vertices[8];
    int triangles[12][3];
};

struct BoundingBox {
    int minx;
    int maxx;
    int miny;
    int maxy;
};

vector<string> buildEmptyFrame(size_t width, size_t height) {
    vector<string> frame;
    string emptyLine(width, '.');
    for (size_t i = 0; i < height; i++) {
        frame.push_back(emptyLine);
    }
    return frame;
}

CubeMesh buildUnitCube() {
    CubeMesh cube;

    // Assign Vertices
    cube.vertices[0] = {0,0,0};
    cube.vertices[1] = {1,0,0};
    cube.vertices[2] = {1,1,0};
    cube.vertices[3] = {0,1,0};
    cube.vertices[4] = {0,0,1};
    cube.vertices[5] = {1,0,1};
    cube.vertices[6] = {0,1,1};
    cube.vertices[7] = {1,1,1};
    
    // Assign triangle indices
    int t[12][3] = {
        {0,1,2}, {0,2,3},
        {4,5,6}, {4,6,7},
        {0,1,5}, {0,5,4},
        {2,3,7}, {2,7,6},
        {0,3,7}, {0,7,4},
        {1,2,6}, {1,6,5}
    };

    for (int i = 0; i < 12; i++) {
        cube.triangles[i][0] = t[i][0];
        cube.triangles[i][1] = t[i][1];
        cube.triangles[i][2] = t[i][2];
    }

    return cube;
}

GridPoint ortographicToGrid(Point3D p) {
    GridPoint gp = {int(round(p.x)), int(round(p.y))};
}

void showFrame(const vector<string>& frame) {
    for (size_t i = 0; i < frame.size(); i++) {
        cout << frame[i] << endl;
    }
}

// Check if point at (x, y) is in the frame
bool pointInFrame(const vector<string>& frame, int x, int y) {
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

bool pointInFrame(const vector<string>& frame, GridPoint p) {
    return pointInFrame(frame, p.x, p.y);
}

BoundingBox triangleBBox(const GridTriangle& t, size_t width, size_t height) {
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

void drawLine(vector<string>& frame, GridPoint p1, GridPoint p2, const char c){
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

void drawTriangleOutline(vector<string>& frame, const GridTriangle& t, char c) {
    drawLine(frame, t.p1, t.p2, c);
    drawLine(frame, t.p2, t.p3, c);
    drawLine(frame, t.p3, t.p1, c);
}

void drawTriangle(vector<string>& frame, const GridTriangle& t, char c) {
    BoundingBox bbox = triangleBBox(t, frame[0].size(), frame.size());
    for (int y = bbox.miny; y <= bbox.maxy; y++){
        for (int x = bbox.minx; x <= bbox.maxx; x++) {
            GridPoint p = {x, y};
            if (pointInTriangle(p, t)) {
                frame[y][x] = c;
            }
        }
    }
    drawTriangleOutline(frame, t, c);
}

int main() {
    GridPoint p1 = {2, 2};
    GridPoint p2 = {15, 2};
    GridPoint p3 = {8, 7};
    GridTriangle t = {p1, p2, p3};

    vector<string> frame = buildEmptyFrame(20, 10);

    drawTriangle(frame, t, '#');
    showFrame(frame);

    return 0;
}