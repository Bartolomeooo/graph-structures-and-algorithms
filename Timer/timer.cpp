#include<iostream>
#include<chrono>

struct Timer
{

    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now(); //set the timer
    }

    ~Timer(){}

    std::chrono::duration<float> getTime()
    {
        end = std::chrono::high_resolution_clock::now(); //stop the timer
        duration = end - start; //count the duration based on the starting and ending times from the timer
        return duration; //return the duration
    }
};