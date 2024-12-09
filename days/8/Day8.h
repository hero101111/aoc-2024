#pragma once

#include "SolutionDay.h"

class Day8 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day8() {}

  ~Day8() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "8"; }

  LL DoWork1()
  {
    LL ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    map<char, vector<Point>> as;
    m.for_each(
      [&](Point p, char c)
      {
        if (c != '.')
        {
          as[c].push_back(p);
        }
      });

    auto m2 = m;
    for (auto [k, v] : as)
    {
      for (auto l1 : v)
          for (auto l2 : v)
          {
              if (l1 != l2)
              {
                Point t1, t2;
                auto qd = l2.GetQuadrant(l1);
                auto  dx = (abs(l2.x - l1.x));
                auto  dy = (abs(l2.y - l1.y));
                if (qd == 1)
                {
                  // QD 3
                  t1.x = l2.x - dx;
                  t1.y = l2.y + dy;
                  t2.x = l1.x + dx;
                  t2.y = l1.y - dy;
                }
                else if (qd == 2)
                {
                  // QD4
                  t1.x = l2.x + dx;
                  t1.y = l2.y + dy;
                  t2.x = l1.x - dx;
                  t2.y = l1.y - dy;
                }
                else if (qd == 3)
                {
                  // QD 1
                  t1.x = l2.x + dx;
                  t1.y = l2.y - dy;
                  t2.x = l1.x - dx;
                  t2.y = l1.y + dy;
                }
                else if (qd == 4)
                {
                  // QD 2
                  t1.x = l2.x - dx;
                  t1.y = l2.y - dy;
                  t2.x = l1.x + dx;
                  t2.y = l1.y + dy;
                }
                if (m2.isSetAt(t1))
                  m2[t1] = '#';
                if (m2.isSetAt(t2))
                  m2[t2] = '#';
              }
        }
    }
    m2.printf(KVERBOSE);
    ret = m2.count_occurence('#');
    return ret;
  }

  LL DoWork2()
  {
    LL               ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    map<char, vector<Point>> as;
    m.for_each(
      [&](Point p, char c)
      {
        if (c != '.')
        {
          as[c].push_back(p);
        }
      });

    auto m2 = m;
    for (auto [k, v] : as)
    {
      for (auto l1 : v)
        for (auto l2 : v)
        {
          if (l1 != l2)
          {
            m2[l1]    = '#';
            m2[l2]    = '#';
            auto  l2_ = l2;
            auto  l1_ = l1;

            Point t1, t2;
            auto  qd = l2.GetQuadrant(l1);
            auto  dx = (abs(l2.x - l1.x));
            auto  dy = (abs(l2.y - l1.y));
            if (qd == 1)
            {
              // QD 3
              while (true)
              {
                t1.x = l2_.x - dx;
                t1.y = l2_.y + dy;
                if (m2.isSetAt(t1))
                  m2[t1] = '#';
                else
                  break;
                l2_ = t1;
              }

              while (true)
              {
                t2.x = l1_.x + dx;
                t2.y = l1_.y - dy;
                if (m2.isSetAt(t2))
                  m2[t2] = '#';
                else
                  break;
                l1_ = t2;
              }
            }
            else if (qd == 2)
            {
              // QD4
              while (true)
              {
                t1.x = l2_.x + dx;
                t1.y = l2_.y + dy;
                if (m2.isSetAt(t1))
                  m2[t1] = '#';
                else
                  break;
                l2_ = t1;
              }

              while (true)
              {
                t2.x = l1_.x - dx;
                t2.y = l1_.y - dy;
                if (m2.isSetAt(t2))
                  m2[t2] = '#';
                else
                  break;
                l1_ = t2;
              }
            }
            else if (qd == 3)
            {
              // QD 1
              while (true)
              {
                t1.x = l2_.x + dx;
                t1.y = l2_.y - dy;
                if (m2.isSetAt(t1))
                  m2[t1] = '#';
                else
                  break;
                l2_ = t1;
              }

              while (true)
              {
                t2.x = l1_.x - dx;
                t2.y = l1_.y + dy;
                if (m2.isSetAt(t2))
                  m2[t2] = '#';
                else
                  break;
                l1_ = t2;
              }
            }
            else if (qd == 4)
            {
              // QD 2

              while (true)
              {
                t1.x = l2_.x - dx;
                t1.y = l2_.y - dy;
                if (m2.isSetAt(t1))
                  m2[t1] = '#';
                else
                  break;
                l2_ = t1;
              }

              while (true)
              {
                t2.x = l1_.x + dx;
                t2.y = l1_.y + dy;
                if (m2.isSetAt(t2))
                  m2[t2] = '#';
                else
                  break;
                l1_ = t2;
              }
            }
          }
        }
    }
    m2.printf(KVERBOSE);
    ret = m2.count_occurence('#');
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
    assert(Part1() == "14");
    assert(Part2() == "34");
    return true;
  }
};
