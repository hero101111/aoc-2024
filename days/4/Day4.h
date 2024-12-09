#pragma once

#include "SolutionDay.h"

class Day4 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day4(){ }

  ~Day4() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "4";
  }

  LL DoWork1()
  {
    LL ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    function<int(Point, int, Point, string)> search;
    search = [&](Point p, int xmasPos, Point dir, string cw) -> int 
    {
      string word = "XMAS";
      char   c    = m[p];
      if (c != word[xmasPos])
        return 0;

      cw += c;

      if (xmasPos == word.size() - 1)
      {
        assert(cw == word);
        return 1;
      }

      int  retCount   = 0;
      /* auto neigh    = p.GetNeighbours();
      for (auto n : neigh)
      {
        if (m.isSetAt(n))
          retCount += search(n, xmasPos + 1, cw);
      }*/
      if (dir == Point{ 0, 0 })
      {
        for (int i = -1; i <= 1; ++i)
          for (int j = -1; j <= 1; ++j)
            retCount += search(p + Point{ i, j }, xmasPos + 1, Point{ i, j }, cw);
      }
      else
        retCount += search(p + dir, xmasPos + 1, dir, cw);
      return retCount;
    };
    m.for_each([&](Point p, char c) 
        {
        auto k = search(p, 0, Point {}, ""s);
        if (k > 0)
        {
          int i = 0;
        }
        ret += k;
        });
    return ret;
  }

  LL DoWork2()
  {
    LL               ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    auto search = [&](Point p) -> int
    {
      if (m[p] != 'A')
        return 0;
      
      string xs = "";
      
      xs += m[p.Left().Up()];
      xs += m[p.Right().Down()];
      if (xs != "MS" && xs != "SM")
        return 0;

      xs = "";
      xs += m[p.Right().Up()];
      xs += m[p.Left().Down()];
      if (xs != "MS" && xs != "SM")
        return 0;

      return 1;
    };
    m.for_each(
      [&](Point p, char c)
      {
        auto k = search(p);
        if (k > 0)
        {
          int i = 0;
        }
        ret += k;
      });
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
    assert(Part1() == "18");
    //assert(Part2() != "");
    return true;
  }
};
