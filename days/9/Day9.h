#pragma once

#include "SolutionDay.h"

class Day9 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day9() {}

  ~Day9() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "9"; }

  LL DoWork1()
  {
    LL       crt     = 0;
    bool     isSpace = false;
    list<LL> mem;
    for (char c : mData[0])
    {
      int val = c - '0';

      for (int i : rangeint(1, val))
        mem.insert(end(mem), isSpace ? -1 : crt);
      if (!isSpace)
        crt++;

      isSpace = !isSpace;
    }

    vector<list<LL>::iterator> gaps;
    gaps.reserve(mem.size());
    for (auto m = mem.begin(); m != end(mem); ++m)
    {
      if (*m == -1)
        gaps.push_back(m);
    }
    auto toMove = std::prev(mem.end());
    auto gap    = begin(gaps);

    // for (auto m : mem)
    //   cout << m << " ";
    // cout << endl;

    while (true)
    {
      while (*toMove < 0)
      {
        toMove = std::prev(toMove);
      }

      **gap   = *toMove;
      *toMove = -2;
      gap++;

      bool noGapsLeft = true;
      for (auto g = *gap; g != end(mem); ++g)
        if (*g >= 0)
          noGapsLeft = false;

      toMove = std::prev(toMove);

      /* for (auto m : mem)
         cout << m << " ";
       cout << endl;*/

      if (noGapsLeft)
        break;

      if (gap == end(gaps))
        break;
      if (**gap == -2)
        break;
    }

    LL  ret = 0;
    int pos = 0;
    for (auto m : mem)
    {
      if (m >= 0)
      {
        // cout << pos << " * " << m << endl;
        ret += m * pos++;
      }
      if (m == -2)
        break;
    }
    return ret;
  }

  LL DoWork2()
  {
    LL       crt     = 0;
    bool     isSpace = false;
    list<LL> mem;
    for (char c : mData[0])
    {
      int val = c - '0';

      for (int i : rangeint(1, val))
        mem.insert(end(mem), isSpace ? -1 : crt);
      if (!isSpace)
        crt++;

      isSpace = !isSpace;
    }
    mem.insert(end(mem), -1);

    vector<tuple<list<LL>::iterator, LL, LL>> gaps;
    vector<tuple<list<LL>::iterator, LL, LL>> blocks;

    gaps.reserve(mem.size());
    blocks.reserve(mem.size());
    bool               inGap      = false;
    LL                 gapLen     = 0;
    list<LL>::iterator gapStart   = mem.begin();
    list<LL>::iterator blockStart = mem.begin();
    LL                 blockLen   = 0;
    int                blockID    = -1;
    int                crtIndex   = 0;
    for (auto m = mem.begin(); m != end(mem); ++m, ++crtIndex)
    {
      if (*m == -1)
      {
        if (blockID > -1)
        {
          blocks.push_back(make_tuple(blockStart, crtIndex, blockLen));
          blockID  = -1;
          blockLen = 0;
        }

        if (!inGap)
        {
          gapStart = m;
          gapLen   = 1;
          inGap    = true;
        }
        else
        {
          gapLen++;
        }
      }
      else
      {
        if (blockID == -1)
        {
          blockID    = *m;
          blockStart = m;
          blockLen   = 1;
        }
        else
        {
          if (*m == blockID)
            blockLen++;
          else
          {
            blocks.push_back(make_tuple(blockStart, crtIndex, blockLen));

            blockID    = *m;
            blockStart = m;
            blockLen   = 1;
          }
        }

        if (inGap)
        {
          gaps.push_back(make_tuple(gapStart, crtIndex, gapLen));
          inGap = false;
        }
      }
    }

    // for (auto m : mem)
    //   cout << m << " ";
    //  cout << endl;
    for (auto it = rbegin(blocks); it != rend(blocks); ++it)
    {
      auto & [blockIt, blockStart, blockLen] = *it;
      for (auto itG = begin(gaps); itG != end(gaps); ++itG)
      {
        auto & [gapIt, gapStart, gapLen] = *itG;

        if (gapLen >= blockLen && gapStart < blockStart)
        {
          for (int i = 0; i < blockLen; ++i)
          {
            *gapIt   = *blockIt;
            *blockIt = -1;
            gapIt    = next(gapIt);
            blockIt  = next(blockIt);

            /*  for (auto m : mem)
                cout << m << " ";
              cout << endl;*/
          }
          gapLen = gapLen - blockLen;
          // for (int i = 0; i < blockLen; ++i)
          //   advance(gapIt, 1);
          break;
        }
      }

      // for (auto m : mem)
      //   cout << m << " ";
      // cout << endl;
    }

    LL  ret = 0;
    int pos = 0;
    for (auto m : mem)
    {
      if (m >= 0)
      {
        //  cout << pos << " * " << m << endl;
        ret += m * pos;
      }
      pos++;
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
    //assert(Part2() != "");
    return true;
  }
};
