#pragma once

#include "SolutionDay.h"

class Day1 : public ISolutionDay
{
private:

  vector<string> mData;
  vector<int>    l1, l2;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "1";
  }

  LL DoWork1()
  {
    LL ret = 0;
    for (auto l : mData)
    {
      auto [s1, s2] = RegExMatch2(l, R"((\d+)\s+(\d+))");
      int i1        = stoi(s1);
      int i2        = stoi(s2);
      l1.push_back(i1);
      l2.push_back(i2);
    }
    sort(begin(l1), end(l1));
    sort(begin(l2), end(l2));
    for (int i = 0; i < l1.size(); ++i)
      ret += abs(l2[i] - l1[i]);
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;
    for (auto l : mData)
    {
      auto [s1, s2] = RegExMatch2(l, R"((\d+)\s+(\d+))");
      int i1        = stoi(s1);
      int i2        = stoi(s2);
      l1.push_back(i1);
      l2.push_back(i2);
    }
    for (auto n : l1)
    {
      auto cnt = count(begin(l2), end(l2), n);
      ret += n * cnt;
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
    //assert(Part1() != "");
    //assert(Part2() != "");
    return true;
  }
};
