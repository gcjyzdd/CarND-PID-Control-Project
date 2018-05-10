# Report of PID Conbtroller Project


## Introduction

In this project, I used two PID controllers to control the vehicle, one for throtle and the other for steer angle. The "twiddle" algorithm was applied to update PID parameters in real time.

To simply the problem, only the PID controller of steer angle was able to *train* parameters. The parameters of throtle PID controller was manually tuned by trial and error.

## Twiddle

In the class of `PID` (see [PID.cpp](./src/PID.h)), I defined a variable called `Type` to let the user update PID parameters or not. When `Type` set to zero, the PID parameters will be updated using the "twiddle" algorithm.

The algorithm was implemented in line `44-114` of [PID.cpp](./src/PID.cpp). The twiddle algorithm updates PID parameters based on the total cross track error over N = 1000 steps.

Line `90-97` of [main.cpp](./src/main.cpp) increases the velocity of the car every 40 laps. 

**Notes**: In order to *train* PID parameters, the initial settings is critical. If initial parameter were not set well, the car could easily go out of the track.

## Result

[A log file](./log8.txt) of how "twiddle" updates PID parameters is included. As shown in the log file, the car can go at a speed of 46mph in the end. 

In the submitted code, the reference velocity is set to 45mph because the car moves more stable at a bit slower speed.

Here are a few reasons that the car cannot go faster:

* the totoal error of every N steps is not consistent, because the car keeps going and does not start at the same point. The car rougly moves one lap over N steps. As a result, the road segment that N-step covers keeps driftting. Since the cross track error is related to the shape of the road segment, the total cross track error over N steps is not an accurate measure of performance of the PID controller.
* the simulator system has small tolerence; the car easily moves out of road and cannot move back to the road.
* algorithm `twiddle` needs too many iterations, which is not practical using the simulator. 




