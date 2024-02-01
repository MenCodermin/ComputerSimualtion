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

    plt::figure_size(1280, 768);
    plt::plot(lambda, theoreticalResponse,{{"label","Response"}});
    // plt::plot(lambda,theoreticalResponse, {"Response"});
    plt::plot(lambda, theoreticalEn,{{"label","En"}});
    // plt::plot(lambda, theoreticalResponse, {"En"});
    plt::title("Theoretical vs Simulated Results");
    plt::xlabel("Values");
    plt::ylabel("Mean Service Rate (mu)");
    plt::legend();
    plt::show();

        return 0;
}


