#include <iostream>
#include <vector>
#include "Public/ComputerSimulationAssignment.h"

using namespace std;

int main(int argc, char* argv[]) {
    Distribution dist;
    const int NUM_SERVERS = 2;      // Number of servers

    double end_time = SIM_TIME;
    double Ta = ARR_TIME;
    double Ts = SERV_TIME;
    double time = 0.0;
    double t1 = 0.0;
    double t2 = SIM_TIME;
    unsigned int n = 0;
    unsigned int c = 0;
    double b = 0.0;
    double s = 0.0;
    double tn = time;
    double tb;
    double x;
    double u;
    double l;
    double w;
    
    vector<bool> inService(NUM_SERVERS, false); // Flags to indicate if a server is in service

    while (time < end_time) {
        if (t1 < t2) { // Event #1 (arrival)
            time = t1;
            s += n * (time - tn);
            n++;
            tn = time;

            // Check if there is an available server
            bool serverAvailable = false;
            for (int i = 0; i < NUM_SERVERS; ++i) {
                if (!inService[i]) {
                    inService[i] = true; // Assign the customer to the server
                    serverAvailable = true;
                    break;
                }
            }

            if (serverAvailable) {
                if (n == 1) {
                    tb = time;
                    t2 = time + dist.triangularDistribution(0,Ts,Ts/2);
                    cout << t2 << endl;
                }
            } else {
                // Reject the customer if no server is available
                cout << "All servers busy, exiting arrival process" << endl;
            }

            t1 = time + dist.triangularDistribution(0,Ta,Ta/2);
        } else { // Event #2 (departure)
            time = t2;
            s = s + n * (time - tn);
            n--;

            // Find the departing server
            int i;
            for (i = 0; i < NUM_SERVERS; ++i) {
                if (inService[i]) {
                    inService[i] = false;
                    break;
                }
            }

            c++;
            if (n > 0) {
                t2 = time + dist.expntl(Ts); // Schedule the next departure
            } else {
                t2 = SIM_TIME;
                b = b + time - tb;
            }

            tn = time; // tn = "last event time" for next event
        }
    }

    x = c / time;
    u = b / (NUM_SERVERS * time);
    l = s / time;
    w = l / x;

    // Output results
    printf("=============================================================== \n");
    printf("= *** Results from M/M/%d simulation *** = \n", NUM_SERVERS);
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

    return 0;
}
