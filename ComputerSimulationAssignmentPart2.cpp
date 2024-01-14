#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include "Public/ComputerSimulationAssignment.h"

#define SIM_TIME 1.0e2 // Simulation time
#define ARR_TIME 1.25  // Mean time between arrivals
#define SERV_TIME 1.00  // Mean service time

using namespace std;

int main(int argc, char *argv[]) 
{
    Distribution dist;
    double Ta = ARR_TIME;       // Mean time between arrivals
    
    double randTriangular = dist.triangularDistribution(0.0, 2.0 * Ta, Ta);

    return 0;
}
 