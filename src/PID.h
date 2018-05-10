#ifndef PID_H
#define PID_H
#include <cstddef> // for size_t
#include <iostream>
class PID {
public:
  /*
  * Update parameters every N steps
  */
  size_t N, step;
  size_t ind;
  size_t stage;
  size_t Type;
  
  double best_error;
  double error;
  double dp,di,dd;
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
