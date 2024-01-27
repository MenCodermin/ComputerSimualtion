#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <matplotlibcpp.h>
#include "Public/ComputerSimulationAssignment.h"

using namespace std;
namespace plt = matplotlibcpp;

int main(int argc, char* argv[])
{
    Distribution dist;
    double Ta = ARR_TIME; // Mean time between arrivals

    // double randTriangular = dist.triangularDistribution(0.0, 2.0 * Ta, Ta);
    vector<double> lambda;
    double mu_values = 20.0;

    vector<double> theoreticalEn;
    vector<double> theoreticalResponse;

    for (int i = 1; i < mu_values; ++i)
        lambda.push_back(i);
    // Calculate theoretical va lues for different mean service rates
    for (int i = 0; i < lambda.size(); ++i)
    {
        theoreticalEn.push_back(dist.theoreticalMeanQueueLength(lambda[i], mu_values));
        theoreticalResponse.push_back(dist.theoreticalResponseTime(lambda[i], mu_values));
    }

    // for(auto i : theoreticalEn)
    //     cout<<i<<endl;
    // cout<<endl<<endl;
    // for(auto i : theoreticalResponse)
    //     cout<<i<<endl;

    plt::figure_size(1280, 768);
    plt::plot(lambda, theoreticalResponse, "ro--");
    plt::plot(lambda, theoreticalEn, "bo--");
    plt::title("Theoretical vs Simulated Results");
    plt::xlabel("Values");
    plt::ylabel("Mean Service Rate (mu)");
    plt::show();

    return 0;
    return 0;
}

// g++ ComputerSimulationAssignment.cpp -o part1 -I C:\Python312\include -I include -I
// C:\Users\oskon\AppData\Roaming\Python\Python312\site-packages\numpy\core\include -L C:\Python312\libs -lpython312
