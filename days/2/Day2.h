#pragma once

#include "SolutionDay.h"

class Day2 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day2(){ }

  ~Day2() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "2";
  }

  bool IsValid(vector<LL> d)
  {
    bool isValid    = true;
    bool increasing = true;
    if (d[1] < d[0])
      increasing = false;
    for (int i = 0; i <= d.size() - 2; ++i)
    {
      if (increasing && d[i + 1] < d[i])
      {
        isValid = false;
        break;
      }
      if (!increasing && d[i + 1] > d[i])
      {
        isValid = false;
        break;
      }
      int diff = abs(d[i + 1] - d[i]);
      if (diff < 1 || diff > 3)
      {
        isValid = false;
        break;
      }
    }
    return isValid;
  }

  LL DoWork1()
  {
    LL ret = 0;
    for (auto line : mData)
    {
      auto d = stoll(tok(line, ' '));
      bool isValid = IsValid(d);
      
      if (isValid)
      {
        cout << line << endl;
        ret++;
      }
    }
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;
    for (auto line : mData)
    {
      auto d       = stoll(tok(line, ' '));
      bool isValid = IsValid(d);

      if (isValid)
      {
        ret++;
      }
      if (!isValid)
      {
        for (int i = 0; i < d.size(); ++i)
        {
          auto d2 = d;
          d2.erase(d2.begin() + i);
          if (IsValid(d2))
          {
            ret++;
            break;
          }
        }
      }
    }
    return ret;
  }
  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  bool Test() override
  {
    mCurrentInput = "test";
   // assert(Part1() != "");
    assert(Part2() != "");
    return true;
  }
};
