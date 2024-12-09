#pragma once

#include "SolutionDay.h"

class Day6 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day6(){ }

  ~Day6() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "6";
  }

  LL DoWork1()
  {
    LL ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());
    auto start = m.first_if(
      [](Point p, char c)
      {
        return c == '^';
      });
    Point crtPos = start->first;
    char  orientation = start->second;

    unordered_set<Point> visited;
    visited.insert(crtPos);
    
    while (true)
    {
      m[crtPos] = '.';
      auto newPos    = crtPos.FromDirection(orientation);


      if (!m.isSetAt(newPos))
        break;
      if (m[newPos] != '.')
      {
        orientation = Point::RotateDirection(orientation, false);
        continue;
      }
      crtPos = newPos;
      visited.insert(crtPos);
    }

    ret = visited.size();
    return ret;
  }

  bool isInLoop(DynamicMap<char> map)
  {
    LL               walkCount = 0;
    DynamicMap<char> m = map;
    auto start = m.first_if(
      [](Point p, char c)
      {
        return c == '^';
      });
    Point crtPos      = start->first;
    char  orientation = start->second;

    unordered_set<Point> visited;
    visited.insert(crtPos);

    while (true)
    {
      m[crtPos]   = '.';
      auto newPos = crtPos.FromDirection(orientation);

      if (walkCount == 2 * visited.size())
        return true;

      if (!m.isSetAt(newPos))
        return false;
      if (m[newPos] != '.')
      {
        orientation = Point::RotateDirection(orientation, false);
        continue;
      }
      crtPos = newPos;
      visited.insert(crtPos);
      walkCount++;
    }

    walkCount = visited.size();
    return walkCount;
  }

  LL DoWork2()
  {
    LL               ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    auto start = m.first_if(
      [](Point p, char c)
      {
        return c == '^';
      });
    Point startPos = start->first;

    m.for_each(
      [&](Point p, char c)
      {
        if (c == '.' && p != startPos)
        {
          auto newMap = m;
          newMap[p]   = 'O';
          if (isInLoop(newMap))
            ret += 1;
        }
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
    assert(Part1() == "41");
    assert(Part2() == "6");
    return true;
  }
};
