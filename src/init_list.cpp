#include <iostream>
#include <vector>
#include <initializer_list>

// A simple class representing a 2D point
struct Point {
    int x, y;
};

// A class representing a Polygon, initialized with a list of points
class Polygon {
public:
    std::vector<Point> points;

    // Constructor using an initializer_list
    Polygon(std::initializer_list<Point> initPoints) : points(initPoints) {
    }

    void print() const {
        std::cout << "Polygon with points:" << std::endl;
        for (const auto& point : points) {
            std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
        }
    }
};

int main() {
    // Create a Polygon using an initializer list
    Polygon myPolygon = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    // Print the points of the Polygon
    myPolygon.print();

    return 0;
}

