#pragma once

#include "SolutionDay.h"

class Day17 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day17() {}

  ~Day17() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "17"; }

  LL DoWork1()
  {
    int           crt = 0;
    map<char, LL> reg;
    vector<LL>    program;

    for (auto line : mData)
    {
      if (!line.empty())
      {
        string content = RegExMatch1(line, R"(.+: (.+))");
        if (crt == 0)
        {
          reg['A'] = stoll(content);
        }
        else if (crt == 1)
        {
          reg['B'] = stoll(content);
        }
        else if (crt == 2)
        {
          reg['C'] = stoll(content);
        }
        else if (crt == 3)
        {
          program = stoll(tok(content, ','));
        }
        crt++;
      }
    }

    auto getOperand = [&](LL op)
    {
      switch (op)
      {
      case 0:
      case 1:
      case 2:
      case 3:
        return op;
        break;
      case 4:
        return reg['A'];
        break;
      case 5:
        return reg['B'];
        break;
      case 6:
        return reg['C'];
        break;
      case 7:
        //  assert(!"invalid");
        break;
      }
    };
    size_t ip = 0;
    while (true)
    {
      // cout << "IP=" << ip << endl;
      LL   op      = program[ip];
      LL   literal = program[ip + 1];
      auto combo   = getOperand(program[ip + 1]);

      bool shouldJump = true;
      switch (op)
      {
      case 0:
        reg['A'] = reg['A'] / pow(2, combo);
        break;
      case 1:
        reg['B'] = reg['B'] ^ literal;
        break;
      case 2:
        reg['B'] = combo % 8;
        break;
      case 3:
        if (reg['A'] != 0)
        {
          ip = literal;
          continue;
        }
        else
        {
        }
        break;
      case 4:
        reg['B'] = reg['B'] ^ reg['C'];
        break;
      case 5:
        cout << "," << (combo % 8);
        break;
      case 6:
        reg['B'] = reg['A'] / pow(2, combo);
        break;
      case 7:
        reg['C'] = reg['A'] / pow(2, combo);
        break;
      }
      if (shouldJump)
        ip += 2;
      else
        ip += 1;

      if (ip >= program.size())
        break;
    }

    LL ret = 0;
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
