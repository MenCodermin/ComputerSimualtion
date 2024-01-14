
#pragma 

class Distribution
{
private:
    double uniform();

public:
    double theoreticalMeanQueueLength(double lambda, double mu);
    double theoreticalResponseTime(double lambda, double mu);
    double triangularDistribution(double minVal, double maxVal, double mode);
    double expntl(double x);

};
