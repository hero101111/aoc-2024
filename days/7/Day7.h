#pragma once

#include "SolutionDay.h"

class Day7 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day7() {}

  ~Day7() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "7"; }

  LL DoWork1()
  {
    LL ret = 0;

    std::function<bool(vector<LL> &, int, int, int)> check;
     check = [&](vector<LL> & data, int pos, int crt, int target) -> bool
        {
            if (pos < data.size())
            {
              int n = data[pos];

              if (check(data, pos + 1, crt + n, target))
                return true;
              if (check(data, pos + 1, crt * n, target))
                return true;
              return false;
            }
            else
            {
              return crt == target;
            }
        };
    for (auto line : mData)
    {
      auto [t, ns] = RegExMatch2(line, R"((\d+): (.+))");
      vector<LL> numbers = stoll(tok(ns, ' '));
      LL         total   = stoll(t);
      if (check(numbers, 1, numbers[0], total))
        ret += total;
    }
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;

    std::function<bool(vector<LL> &, LL, LL, LL)> check;
    check = [&](vector<LL> & data, LL pos, LL crt, LL target) -> bool
    {
      if (pos < data.size())
      {
        LL n = data[pos];

        if (check(data, pos + 1, crt + n, target))
          return true;
        if (check(data, pos + 1, crt * n, target))
          return true;
        string crtStr = to_string(crt);
        string nStr   = to_string(n);
        LL     comb   = stoll(crtStr + nStr);
        if (check(data, pos + 1, comb, target))
          return true;
        return false;
      }
      else
      {
        return crt == target;
      }
    };
    for (auto line : mData)
    {
      auto [t, ns]       = RegExMatch2(line, R"((\d+): (.+))");
      vector<LL> numbers = stoll(tok(ns, ' '));
      LL         total   = stoll(t);
      if (check(numbers, 1, numbers[0], total))
        ret += total;
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
    // assert(Part2() != "");
    return true;
  }
};
