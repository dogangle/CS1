#include <stdio.h>
#include <stdlib.h>

typedef struct Zone {
    int arr[2][2];
    int overlap;
    // Note: coordinates are always entered in format x1, y1 (lower left) x2, y2 (upper right)
} Zone;
// Define variable type Zone

int main()
{
    int numZones,count,countOverlap;
    // Declare variables
    scanf("%d", &numZones);
    // Determine number of zones
    Zone * plane = malloc(numZones * sizeof(Zone));
    // Declare and allocate memory for an array of Zones
    for (count=0;count<numZones;count++){

        scanf("%d %d %d %d", &plane[count].arr[0][0], &plane[count].arr[0][1], &plane[count].arr[1][0], &plane[count].arr[1][1]);
        // Populate 2d array of zone #count with coordinates
        plane[count].overlap=0;

        for (countOverlap=0;countOverlap<count;countOverlap++){

            if (plane[count].arr[0][0] >= plane[countOverlap].arr[1][0] || plane[countOverlap].arr[0][0] >= plane[count].arr[1][0]
                || plane[count].arr[0][1] >= plane[countOverlap].arr[1][1] || plane[countOverlap].arr[0][1] >= plane[count].arr[1][1]){
                // If the new zone's right side is to the left of zone # countOverlap's left side, or vice versa, there is no overlap
                // If the new zone's top side is underneath zone # countOverlap's bottom side, or vice versa, there is no overlap
            }

            else {
                plane[count].overlap++;
                // If none of the above is true, then there is overlap
            }

        }
        printf("%d\n", plane[count].overlap);
        // Print # of overlap

    }
    free(plane);
    // Free memory
    return EXIT_SUCCESS;
}
