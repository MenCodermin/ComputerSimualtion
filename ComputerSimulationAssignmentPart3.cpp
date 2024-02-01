#include "Public/ComputerSimulationAssignment.h"
#include <iostream>
#include <math.h>
// #include <matplotlibcpp.h>
#include <random>
#include <vector>

using namespace std;
// namespace plt = matplotlibcpp;
unsigned int K = 5;

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
    bool inService[K];          // Flags to indicate if a customer is in service

    // Initialize flags
    for (int i = 0; i < K; ++i)
        inService[i] = false;
    // Main simulation loop
    while (time < end_time)
    {
        if (t1 < t2) // *** Event #1 (arrival) ***
        {   
            time = t1;
            s += n * (time - tn); // Update area under "s" curve
            n++;
            tn = time; // tn = "last event time" for the next event
            t1 = time + dist.triangularDistribution(0,Ta,Ta/2);
            // Check if there is room for the arriving customer
            if (n <= K)
            {
                if (n == 1)
                {
                    tb = time; // Set "last start of busy time"
                    int i;
                    for (i = 0; i < K; ++i)
                    {
                        if (!inService[i])
                        {
                            inService[i] = true;
                            break;
                        }
                    }
                    t2 = time + dist.triangularDistribution(0,Ts,Ts/2);
                }
            }
            else
            {
                // Reject the customer, as the system is full
                cout << "Out of limits, exiting arrival process" << endl;
            }
        }
        else // *** Event #2 (departure) ***
        {
            time = t2;
            s = s + n * (time - tn); // Update area under "s" curve
            n--;
            tn = time; // tn = "last event time" for the next event
            c++;       // Increment number of completions
            int i;
            for (i = 0; i < K; ++i)
            {
                if (inService[i])
                {
                    inService[i] = false;
                    break;
                }
            }
            // If there are still customers in the system, schedule the next departure
            if (n > 0)
                t2 = time + dist.expntl(Ts);
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
    printf("= *** Results from M/M/1/k simulation *** = \n");
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

// g++ ComputerSimulationAssignment.cpp -o part1 -I C:\Python312\include -I
// include -I
// C:\Users\oskon\AppData\Roaming\Python\Python312\site-packages\numpy\core\include
// -L C:\Python312\libs -lpython312
