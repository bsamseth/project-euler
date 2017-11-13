/*
 Three distinct points are plotted at random on a Cartesian plane, for
 which -1000 ≤ x, y ≤ 1000, such that a triangle is formed.
 
 Consider the following two triangles:
 
 A(-340,495), B(-153,-910), C(835,-947)
 X(-175,41), Y(-421,-714), Z(574,-645)
 
 It can be verified that triangle ABC contains the origin, whereas triangle XYZ does not.
 
 Using triangles.txt (right click and 'Save Link/Target As...'), a 27K text file
 containing the co-ordinates of one thousand "random" triangles, find the
 number of triangles for which the interior contains the origin.
 
 NOTE: The first two examples in the file represent the triangles in the example given above.
 
 
 Solution comment: Instant solution, limited only by IO.
                   Origin inside the triangle if the number of intersections
                   made by a ray from the origin with each of the 3 edges is
                   an odd number.
                   In the following the ray is a horizontal line going to
                   the right out from the origin. This intersects
                   an edge if the two vertices V[i] and V[i+1] are on opposite sides
                   of the x-axis (with maximum one of them on the line), and the
                   intersection point is to the right of the origin.
 */

#include <iostream>
#include <fstream>
using namespace std;

typedef struct { int x, y; } Point;

/*
 Crossing number, adapted from http://geomalgorithms.com/a03-_inclusion.html.
 */
int cn_PnPoly( Point* V, int n )
{
    int cn = 0;    // the  crossing number counter
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1] (V[n] = V[0])
        if (V[i].y * V[i+1].y <= 0 and (V[i].y | V[i+1].y)) {
            // compute the actual edge-ray intersect x-coordinate,
            // and check that it is to the right of the origin.
            float vt = ((float) V[i].y) / (V[i+1].y - V[i].y);
            if (0 <  V[i].x - vt * (V[i+1].x - V[i].x))
                cn++;
        }
    }
    return cn & 1;    // 0 if even (out), and 1 if  odd (in)
}

int main() {
    ifstream in ("/Users/bendik/drive/project-euler/102/p102_triangles.txt");
    int count = 0;
    char c;  // Buffer for skipping commas.
    for (int triangle = 0; triangle < 1000; triangle++) {
        Point points[4];
        int x, y;
        for (int p = 0; p < 3; p++) {
            in >> x >> c >> y;
            if (p < 2) in >> c;
            points[p] = {x, y};
        }
        points[3] = points[0];
        count += cn_PnPoly(points, 3);
    }
    printf("%d\n", count);
    return 0;
}
