#pragma once

#include "SolutionDay.h"

class Day10 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day10() {}

  ~Day10() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "10"; }

  LL DoWork(bool partOne)
  {
    LL ret = 0;
    Graph<Point>    g(mData[0].size() * mData[0].size());
    DynamicMap<char> m;

    vector<Point> heads, trails;
    m.fromfile(GetInputPath());
    m.for_each(
      [&](Point p, char c) {
        if (c == '0')
          heads.push_back(p);
        if (c == '9')
          trails.push_back(p);
        int myVal = c - '0';

        auto neigh = p.GetDirectNeighbours();
        for (auto n : neigh)
        {
          if (m.isSetAt(n))
          {
            int otherVal = m[n] - '0';
            if (otherVal == myVal + 1)
              g.AddEdge(p, n, 1);
          }
        }
      });
    for (auto h : heads)
    {
      auto dist = g.GetDistances(h);
      for (auto t : trails)
      {
          if (dist[t] != numeric_limits<int>::max() - 1)
          {
            if (partOne)
            {
              ret += 1;
            }
            else
            {
              auto paths = g.GetAllPaths(h, t);
              ret += paths.size();
            }
          }
      }
    }
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  bool Test() override
  {
    mCurrentInput = "test";
     assert(Part1() != "");
    // assert(Part2() != "");
    return true;
  }
};
