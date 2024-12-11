#pragma once

#include "SolutionDay.h"

class Day11 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day11() {}

  ~Day11() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "11"; }

  LL DoWork1()
  {
    LL ret = 0;
    auto stonesData = stoll(tok(mData[0], ' '));
    list<LL> stones;
    for (auto s : stonesData)
      stones.insert(end(stones), s);

    for (int i = 0; i < 75; ++i)
    {
      cout << i << "        ";
      list<LL> stones2;
      for (auto s : stones)
      {
        if (s == 0)
        {
          stones2.push_back(1);
          continue;
        }
        auto sstr = to_string(s);
        if (sstr.size() % 2 == 0)
        {
          LL s1 = stoll(sstr.substr(0, sstr.size() / 2));
          LL s2 = stoll(sstr.substr(sstr.size() / 2));
          stones2.push_back(s1);
          stones2.push_back(s2);
        }
        else
        {
          stones2.push_back(s * 2024);
        }
      }
      stones = stones2;
      cout << stones.size() << endl;
    }
    ret = stones.size();
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;
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
    // assert(Part2() != "");
    return true;
  }
};
