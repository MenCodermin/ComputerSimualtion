
#pragma

#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

#define SIM_TIME 1.0e6 // Simulation time
#define ARR_TIME 1.25   // Mean time between arrivals
#define SERV_TIME 1.00  // Mean service time

class Distribution
{
private:
    double uniform();

public:
    double theoreticalMeanQueueLength(double lambda, double mu);
    double theoreticalResponseTime(double lambda, double mu);
    double triangularDistribution(double minVal, double maxVal, double mode);
    double expntl(double x);
    int poisson(double lambda);

};



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

int Distribution::poisson(double lambda)
{
    random_device rd;
    mt19937 gen(rd());

    // Poisson-distributed value using the exponential distribution
    poisson_distribution<int> poissonDist(lambda);
    return poissonDist(gen);
}