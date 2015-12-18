/**
   requires -std=c++11
***/
#include <iostream>
#include <functional>

using namespace std;

template <typename T>
class constrainted{
public:
  T value;
  T& other;
  function<T(T)> constraint;

  constrainted(T& _other, function<T(T)> _constraint):
    other(_other), constraint(_constraint){
    ; // do nothing other than initialization
  }

  operator T(){
    value = constraint(other);
    return value;
  }

  T operator =(const T& substituted){
    value = substituted;
    other = constraint(value);
    return value;
  }
};

void example1(){
  bool a = false;
  constrainted<bool> b(a, [](bool x)->bool { return !x; }); // a and b satsfy "a = !b, b = !a"

  if(b) 
    cout << "b is true" << endl;

  // Chaning the value of b automatically changes the value of a as well
  b = false;
  if(a)
    cout << "a is true" << endl;

  cout << "--------------------------------------" << endl;
}

void example2(){
  double alpha;
  constrainted<double> beta(alpha, [](double x)->double { return 1-x; }); // alpha and beta satsfy "alpha = 1 - beta, beta = 1 - alpha"

  alpha = 0.2;
  cout << "alpha: " << alpha << endl; // 0.2
  cout << "beta: " << beta << endl;   // 0.8
  cout << "--------------------------------------" << endl;

  // Chaning the value of beta automatically changes the value of alpha as well
  beta = 0.3;
  cout << "alpha: " << alpha << endl; // 0.7
  cout << "beta: " << beta << endl;   // 0.3
  cout << "--------------------------------------" << endl;
}

main(){
  example1();
  example2();
}
