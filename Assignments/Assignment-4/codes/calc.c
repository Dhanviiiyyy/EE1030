#include <stdio.h>

int main() {
FILE *filePointer;
filePointer = fopen("drift_data.txt", "w");

       if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    double riverSpeed = 3.0; 
    double totalTime = 0.25; 
    int numPoints = 100; 
    double timeStep = totalTime / numPoints; 

       fprintf(filePointer, "Time (hours)\tDrift Distance (km)\n");

  
    double time, driftDistance;

   
    for (int i = 0; i <= numPoints; i++) {
        time = i * timeStep;
        driftDistance = riverSpeed * time;
        fprintf(filePointer, "%.6f\t%.6f\n", time, driftDistance);
    }

       fclose(filePointer);

    printf("Data has been written to drift_data.txt\n");
    return 0;
}

