#ifndef kalman_h
#define kalman_h

struct FastKalmanFilter
{


    // system parameters
    double Bparam;
    double Fparam;
    double Qparam;
    double Hparam;
    double Rparam;
    double Kparam;

    // system dynamic parameters
    double XHatPresent;
    double XHatForward;
    double SPresent;
    double SForward;
    double PPresent;
    double PForward;
    double Y;

   
};

void FastKalmanFilter_setup(double Qparam, double Rparam, double samplingPeriod, double PNStd, double MNstd, double initialValue);
double GetEstimation(double measuredData, double FinputValue);
//struct FastKalmanFilter;


void FastKalmanFilter_setup(struct FastKalmanFilter &sensor, double Qparam, double Rparam, double samplingPeriod, double PNStd, double MNstd, double initialValue)
{
    sensor.Fparam = 1;
    sensor.Hparam = 1;
    sensor.Y = 0.0;
    sensor.Bparam = samplingPeriod;
    sensor.Qparam = Qparam * PNStd * PNStd;
    sensor.Rparam = Rparam * MNstd * MNstd;
    double PPresent = MNstd * MNstd;
    // system dynamic parameters
    sensor.XHatPresent = initialValue;
    sensor.SPresent = MNstd * MNstd;
}

double GetEstimation(struct FastKalmanFilter &sensor, double measuredData, double FinputValue)
{
    // state
    sensor.XHatForward = sensor.Fparam * sensor.XHatPresent + sensor.Bparam * FinputValue;

    // state uncertainty
    sensor.PForward = sensor.Fparam * sensor.PPresent * sensor.Fparam + sensor.Qparam;

    // update
    sensor.Y = measuredData - sensor.Hparam * sensor.XHatForward;

    // innovation
    sensor.SForward = sensor.Hparam * sensor.PForward * sensor.Hparam + sensor.Rparam;

    // coefficient
    sensor.Kparam = sensor.PForward * sensor.Hparam * 1.0 / sensor.SForward;
    sensor.XHatForward = sensor.XHatForward + sensor.Kparam * sensor.Y;
    sensor.PForward = (1.0 - sensor.Kparam * sensor.Hparam) * sensor.PForward;

    // update previous values
    sensor.PPresent = sensor.PForward;
    sensor.XHatPresent = sensor.XHatForward;
    sensor.SPresent = sensor.SForward;

    return sensor.XHatForward;
}
#endif
