#ifndef GRADER_01_H
#define GRADER_01_H

#include "AbstractGrader.h"
#include "Interfaces01.h"
#include "Random.h"
#include <vector>
#include <string>

class Grader01 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * singleOrderSort2(int len);
  TestCase * singleOrderSort3(int len);
  TestCase * singleSequenceOrderSort(int len);
  TestCase * singleReverse(int len);

  TestCase * doubleOrderSort2(int len);
  TestCase * doubleOrderSort3(int len);
  TestCase * doubleSequenceOrderSort(int len);
  TestCase * doubleReverse(int len);

  void createOriginalSequence(int len, std::vector<int>& ret);
  void createReverseSequence(int len, std::vector<int>& ret);
  void createRandomSequence(int len, std::vector<int>& ret);
  void createOrderSort2(std::vector<int>& org_seq, std::vector<int>& ret);
  void createOrderSort2(int len, std::vector<int>& ret);
  void createOrderSort3(int len, std::vector<int>& ret);
  void createOrderSort3(std::vector<int>& original, std::vector<int>& ret);
  void createSequenceOrderSort(std::vector<int>& original, std::vector<int>& ret);
  void createReverse(std::vector<int>& original, std::vector<int>& ret);
  Random m_random;
};

#endif
