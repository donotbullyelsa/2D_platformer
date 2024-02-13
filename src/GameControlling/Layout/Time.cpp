
#include "Time.h"

std::string Time::time_to_string(int time)
{
  std::string time_string;
  int second = static_cast<int>(time / 1000);
  int millisecond = static_cast<int>((time % 1000) / 10);
  if (time > 59999)
  {
    int minute = 0;
    while (second > 60)
    {
      second -= 60;
      minute++;
    }
    if (second < 10)
    {
      time_string = "0" + std::to_string(minute) + ":0" + std::to_string(second) + ":" + std::to_string(millisecond);
    }
    else
    {
      time_string = "0" + std::to_string(minute) + ":" + std::to_string(second) + ":" + std::to_string(millisecond);
    }
  }
  else
  {
    time_string = std::to_string(second) + ":" + std::to_string(millisecond);
    if (second < 10)
    {
      time_string = "0" + time_string;
    }
  }
  return time_string;
}