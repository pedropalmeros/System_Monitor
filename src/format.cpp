#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  string time = "00:00:00";
  long cal = 0;
  if (seconds > 0) {
    // calculate hours
    cal = seconds / 3600;
    time = CompleteZero(cal) + ":";
    // calculate minutes
    cal = (seconds / 60) % 60;
    time += CompleteZero(cal) + ":";
    // calculate seconds
    cal = seconds % 60;
    time += CompleteZero(cal);
  }

  return time;
}

// check if calculated number is smaller than 10 and return the appropriate
// string
std::string Format::CompleteZero(long time) {
  if (time < 10)
    return "0" + std::to_string(time);
  else
    return std::to_string(time);
}
