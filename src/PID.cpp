#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID()
{
    N = 10e2;
    step = 0;
    ind = 0;
    stage = 0;
    best_error = 1e12;
    error = 0.;
    dp = 0.005;
    di = 1e-5;
    dd = 0.001;
    Type = 0; // steer
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0.;
    i_error = 0.;
    d_error = 0.;
}

void PID::UpdateError(double cte)
{
    d_error = (cte - p_error) / 1;
    i_error += p_error;
    p_error = cte;

    error += cte * cte;
    // twiddle: update PID parameters based on total error of N steps
    if ((step + 1) % N == 0 && Type < 1)
    {
        if (step == N - 1)
        {
            best_error = error;
        }
        const double INC = 1.2;
        const double DEC = 0.7;

        std::cout << "error = " << error << " Kp = " << Kp << " Ki = " << Ki << " Kd = " << Kd << " dp = " << dp << " di = " << di << " dd= " << dd << std::endl;
        double param[] = {Kp, Ki, Kd};
        double dparam[] = {dp, di, dd};

        switch (stage)
        {
        case 0:
            param[ind] += dparam[ind];
            stage++;
            error = 0.;
            break;

        case 1:
            if (error < best_error)
            {
                best_error = error;
                error = 0.;
                dparam[ind] *= INC;
                ind = (ind + 1) % 3;
                stage = 0;

                param[ind] += dparam[ind];
                stage++;
                error = 0.;
            }
            else
            {
                param[ind] -= 2 * dparam[ind];
                error = 0.;
                stage++;
            }
            break;

        case 2:
            if (error < best_error)
            {
                best_error = error;
                error = 0.;
                dparam[ind] *= INC;
            }
            else
            {
                param[ind] += dparam[ind];
                dparam[ind] *= DEC;
            }
            ind = (ind + 1) % 3;
            stage = 0;
            param[ind] += dparam[ind];
            stage++;
            error = 0.;
            break;
        }
        error = 0.;
        Kp = param[0];
        Ki = param[1];
        Kd = param[2];
        dp = dparam[0];
        di = dparam[1];
        dd = dparam[2];

        std::cout << "new              Kp = " << Kp << " Ki = " << Ki << " Kd = " << Kd << " dp = " << dp << " di = " << di << " dd= " << dd << std::endl;
    }
    step++;
}

double PID::TotalError()
{
    return -(Kp * p_error + Ki * i_error + Kd * d_error);
}
