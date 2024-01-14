#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include "Public/ComputerSimulationAssignment.h"

using namespace std;

#define SIM_TIME 1.0e6 // Simulation time
#define ARR_TIME 1.25   // Mean time between arrivals
#define SERV_TIME 1.00  // Mean service time

double Distribution::theoreticalMeanQueueLength(double lambda, double mu) {
    double rho = lambda / mu;
    return rho / (1 - rho);
}

double Distribution::theoreticalResponseTime(double lambda, double mu) {
    return theoreticalMeanQueueLength(lambda, mu) / lambda;
}

double Distribution::triangularDistribution(double minVal, double maxVal, double mode) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    double rand = dis(gen);
    double range = maxVal - minVal;
    double c = (mode - minVal) / range;

    if (rand <= c)
        return minVal + sqrt(rand * range * (mode - minVal));
    else
        return maxVal - sqrt((1 - rand) * range * (maxVal - mode));
}

double Distribution::uniform()
{
    return ((double) rand() / RAND_MAX);
}

double Distribution::expntl(double x)
{
    double z;
    do
    {
        z = uniform();
    }
    while ((z == 0) || (z == 1));
    return(-x * log(z));
}



// int main(int argc, char *argv[]) {

//     vector<double> lambda;
//     double mu_values = 20.0;

//     vector<double> theoreticalEn;
//     vector<double> theoreticalResponse;

//     for( int i = 1; i < mu_values; ++i)
//         lambda.push_back(i);
    
//     // Calculate theoretical values for different mean service rates
//     for (int i = 0; i < lambda.size(); ++i) {
//         theoreticalEn.push_back(theoreticalMeanQueueLength(lambda[i], mu_values));
//         theoreticalResponse.push_back(theoreticalResponseTime(lambda[i], mu_values));
//     }

//     // for(auto i : theoreticalEn)
//     //     cout<<i<<endl;
//     // cout<<endl<<endl;
//     // for(auto i : theoreticalResponse)
//     //     cout<<i<<endl;

//     plt::figure_size(1280,768);
//     plt::plot(lambda, theoreticalResponse, "ro--");
//     plt::plot(lambda, theoreticalEn, "bo--");
//     plt::title("Theoretical vs Simulated Results");
//     plt::xlabel("Values");
//     plt::ylabel("Mean Service Rate (mu)");
//     plt::show();

//     return 0;
// }


//g++ ComputerSimulationAssignment.cpp -o part1 -I C:\Python312\include -I include -I C:\Users\oskon\AppData\Roaming\Python\Python312\site-packages\numpy\core\include -L C:\Python312\libs -lpython312