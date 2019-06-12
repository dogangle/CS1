#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

double binarySearch(double min, double max, double key, double radius);
double segArea(double angle, double radius);
double degreeToRadian(double degree);

// Declare function prototypes

int main()
{
    double answer=0, radius, r1, r2, ratio, area, angle;
    // Declare variables
    scanf("%lf %lf %lf", &radius, &r1, &r2);
    // Scan for the radius, and the two ratios
    if (r2<r1) {
    // Determine if the right portion you will *have* is smaller than the left portion you will *eat*
        ratio = (r2/(r1+r2));
        area = ((PI*(pow(radius,2)))*ratio);
        // Determine the ratio of the cut, and the area of the smaller segment;
        angle = binarySearch(0, 180, area, radius);
        // Use binary search to determine the theta of the triangle, min is 0 and max is 180
        answer = (radius*cos(degreeToRadian(angle/2)));
        // Using theta, use Pythagorean theorems to determine the length of X, where you will make the cut
        printf("\n%lf", answer);
        // Print answer
    }
    else if (r1<r2) {
        ratio = (r1/(r1+r2));
        area = ((PI*(pow(radius,2)))*ratio);
        // Determine the ratio of the cut, and the area of the smaller segment;
        angle = binarySearch(0, 180, area, radius);
        // Use binary search to determine the theta of the triangle, min is 0 and max is 180
        answer = (radius*cos(degreeToRadian(angle/2)));
        // Using theta, use Pythagorean theorems to determine the length of X, where you will make the cut
        printf("\n-%lf", answer);
        // Print answer, negative because of the ratio
    }

    else {
        printf("\n%lf", answer);
        // If r1 and r2 are equal, the cut is 0.0000
    }


    return EXIT_SUCCESS;
}

double binarySearch(double min, double max, double key, double radius)
{

    if (min>=0) {
        double mid = min+((max-min)/2);
        // Determine midpoint
        if (segArea(mid,radius)<=(key+0.000001) && segArea(mid,radius)>=(key-0.000001)) {
            return mid;
            // If theta is within the range, return the result
        }
        else if (segArea(mid, radius) > key) {
            return binarySearch(min, mid, key, radius);
            // If theta is too big, recursively search in the smaller half
        }
        else if (segArea(mid, radius) < key) {
            return binarySearch(mid, max, key, radius);
            // If theta is too small, recursively search in the larger half
        }
        else return EXIT_FAILURE;
    }
    else return EXIT_FAILURE;
}

double segArea(double angle, double radius)
{
    double area;
    area = 0.5*(pow(radius,2)*(degreeToRadian(angle)-sin(degreeToRadian(angle))));
    return area;
    // Calculate and return the segment area by using the circular segment formula A=1/2 R^2 (theta-sin(theta))
}

double degreeToRadian(double degree)
{
    double radian = (degree * (PI/180));
    return radian;
    // Convert from degrees to radians
}
