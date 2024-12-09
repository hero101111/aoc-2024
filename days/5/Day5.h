#pragma once

#include "SolutionDay.h"

class Day5 : public ISolutionDay
{
private:
  vector<string> mData;
  vector<pair<LL, LL>> rules;

public:
  Day5() {}

  ~Day5() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "5"; }

  LL DoWork1()
  {
    rules.clear();
    LL   ret       = 0;
    bool readRules = false;
    for (auto line : mData)
    {
        if (line.empty())
        {
          readRules = true;
          continue;
        }
        if (!readRules)
        {
          auto [left, right] = split(line, '|');
          rules.push_back(make_pair(stoll(left), stoll(right)));
        }
        if (readRules)
        {
          vector<LL> pages = stoll(tok(line, ','));
          bool       isOk  = true;
          for (auto rule : rules)
          {
            auto [left, right] = rule;
            for (auto i = 0; i < pages.size() - 1; ++i)
            {
              for (auto j = i + 1; j < pages.size(); ++j)
              {
                if (pages[i] == right && pages[j] == left)
                {
                  isOk = false;
                  break;
                }
              }
              if (!isOk)
                break;
            }
            if (!isOk)
              break;
          }
          if ( isOk)
            ret += pages[pages.size() / 2];
        }
    }
    return ret;
  }

  LL DoWork2()
  {
    rules.clear();
    LL   ret       = 0;
    bool readRules = false;
    for (auto line : mData)
    {
      if (line.empty())
      {
        readRules = true;
        continue;
      }
      if (!readRules)
      {
        auto [left, right] = split(line, '|');
        rules.push_back(make_pair(stoll(left), stoll(right)));
      }
      if (readRules)
      {
        vector<LL> pages = stoll(tok(line, ','));
        bool       isOk  = true;
        for (auto rule : rules)
        {
          auto [left, right] = rule;
          for (auto i = 0; i < pages.size() - 1; ++i)
          {
            for (auto j = i + 1; j < pages.size(); ++j)
            {
              if (pages[i] == right && pages[j] == left)
              {
                isOk = false;
                break;
              }
            }
            if (!isOk)
              break;
          }
          if (!isOk)
            break;
        }
        if (!isOk)
        {
          sort(begin(pages), end(pages),
               [&](LL a, LL b)
               {
                 for (auto [left, right] : rules)
                 {
                   if (b == left && a == right)
                     return false;
                 }
                 return true;
               });
          ret += pages[pages.size() / 2];
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
    assert(Part1() == "143");
    assert(Part2() == "123");
    return true;
  }
};
