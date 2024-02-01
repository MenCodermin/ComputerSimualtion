#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Public/ComputerSimulationAssignment.h"

using namespace std;

int main(int argc, char* argv[])
{
    Distribution dist;
    double end_time = SIM_TIME; // Total time to simulate
    double Ta = ARR_TIME;       // Mean time between arrivals
    double Ts = SERV_TIME;      // Mean service time
    double time = 0.0;          // Simulation time
    double t1 = 0.0;            // Time for next event #1 (arrival)
    double t2 = SIM_TIME;       // Time for next event #2 (departure)
    unsigned int n = 0;         // Number of customers in the system
    unsigned int c = 0;         // Number of service completions
    double b = 0.0;             // Total busy time
    double s = 0.0;             // Area of number of customers in system
    double tn = time;           // Variable for "last event time"
    double tb;                  // Variable for "last start of busy time"
    double x;                   // Throughput
    double u;                   // Utilization
    double l;                   // Mean number in the system
    double w;                   // Mean waiting time
    //
    // Main simulation loop
    while (time < end_time)
    {
        if (t1 < t2) // *** Event #1 (arrival) ***
        {
            time = t1;
            s += n * (time - tn); // Update area under "s" curve
            n++;
            tn = time; // tn = "last event time" for next event
            t1 = time + dist.triangularDistribution(0,Ta,Ta/2);
            if (n == 1)
            {
                tb = time; // Set "last start of busy time"
                t2 = time + dist.triangularDistribution(0,Ts,Ts/2);
            }
        }
        else // *** Event #2 (departure) ***
        {
            time = t2;
            s = s + n * (time - tn); // Update area under "s" curve
            n--;
            tn = time; // tn = "last event time" for next event
            c++;       // Increment number of completions
            if (n > 0)
                t2 = time + dist.triangularDistribution(0,Ts,Ts/2);
            else
            {
                t2 = SIM_TIME;
                b = b + time - tb; // Update busy time sum if empty
            }
        }

    }
    //
    // Compute outputs
    x = c / time; // Compute throughput rate
    u = b / time; // Compute server utilization
    l = s / time; // Compute mean number in system
    w = l / x;    // Compute mean residence or system time
    // Output results
    printf("=============================================================== \n");
    printf("= *** Results from M/M/1 simulation *** = \n");
    printf("=============================================================== \n");
    printf("= Total simulated time = %3.4f sec \n", end_time);
    printf("=============================================================== \n");
    printf("= INPUTS: \n");
    printf("= Mean time between arrivals = %f sec \n", Ta);
    printf("= Mean service time = %f sec \n", Ts);
    printf("=============================================================== \n");
    printf("= OUTPUTS: \n");
    printf("= Number of completions = %ld cust \n", c);
    printf("= Throughput rate = %f cust/sec \n", x);
    printf("= Server utilization = %f %% \n", 100.0 * u);
    printf("= Mean number in system = %f cust \n", l);
    printf("= Mean residence time = %f sec \n", w);
    printf("=============================================================== \n");
    //

    return 0;
}
