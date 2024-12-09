#pragma once

#include "SolutionDay.h"

class Day3 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day3(){ }

  ~Day3() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "3";
  }

  LL DoWork1()
  {
    LL ret = 0;

    for (auto line : mData)
    {
      auto maches = RegExMatchN(line, R"(mul\(\s*\d+\,\s*\d+\s*\))");
      for (auto m : maches)
      {
        cout << m << endl;
        auto [left, right] = RegExMatch2(m, R"(mul\(\s*(\d+)\,\s*(\d+)\s*\))");
        ret += stoll(left) * stoll(right);
      }
    }
    return ret;
  }

  string substrsafe(string s, int pos, int len)
  { 
    if (s.size() > pos + len)
      return s.substr(pos, len);
    else
      return s.substr(pos);
  }

  LL DoWork2()
  {
    LL ret = 0;

    string s = "abcde";
    string p = substrsafe(s, 4, 50);

    bool active = true;
    for (auto line : mData)
    {
      auto maches = RegExMatchN(line, R"(mul\(\s*\d+\,\s*\d+\s*\))");
      size_t i      = 0;

      while (true)
      {
        if (substrsafe(line, i, "do()"s.size()) == "do()"s)
          active = true;
        if (substrsafe(line, i, "don't()"s.size()) == "don't()"s)
          active = false;
        if (substrsafe(line, i, maches.front().size()) == maches.front())
        {
          if (active)
          {
            auto [left, right] = RegExMatch2(maches.front(), R"(mul\(\s*(\d+)\,\s*(\d+)\s*\))");
            ret += stoll(left) * stoll(right);
          }
          maches.erase(begin(maches));
          if (maches.empty())
            break;
        }
        ++i;
        if (i >= line.size())
          break;
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
    //assert(Part1() != "");
    //assert(Part2() != "");
    return true;
  }
};
