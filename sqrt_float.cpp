/*
Question: Write a function to implement float sqrt(float value).

Solution 1: Use the binary search
When the number is greater than 1, its square root is between 1 and itself. If the number is less than 1, its square root is between itself and 1.
We first initialize the upper and lower bounds of the square root and use the middle point as the test.
If the square of the middle point is larger than the given number, we reset the upper bound to the middle point. Otherwise, we reset the lower bound to be the middle point. We repeat this until the error is less than a threshold.
*/

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#define EPSILON 1e-3

float sqrt1(float value){
 if(value < 0){
  std::cout << "Error in the input value" << std::endl;
  return -1;
 }
 float a = 1;
 float b = value;
 if(value < 1){
  a = value;
  b = 1;
 }
 float mid = (a + b) / 2;
 float err = mid * mid - value;
 while(fabs(err) > EPSILON){
  if(err > 0){
   b = mid;
  }else{
   a = mid;
  }
  mid = (a + b) / 2;
  err = mid * mid - value;
 }
 return mid;
}


/*
Solution 2: Use Newton method

Suppose the given number is a, we want to solve the equation x^2-a=0.
We can first guess a random number as the initial solution. We denote the first guess as x0. x1 is computed as x1=x0-f(x0)/f'(x0), which is equal to x1=x0/2+a/2x0. We do this until we find the root of the equation.
*/

float sqrt2(float value){
 if(value < 0){
  std::cout << "Error in the input value" << std::endl;
  return -1;
 }
 if(value == 0){
  return 0;
 }
 float x = (float)(rand() + 1) / ((float)RAND_MAX + 1) * std::max(1.0f, value); // x0 is in the range of (0, max(1, value)].
 while(fabs(x * x - value) > EPSILON){
  x = x / 2 + value / (2 * x);
 }
 return x;
}