
#ifndef ABSTRACT_GRADER_H
#define ABSTRACT_GRADER_H

#include <vector>
#include <string>
#include <map>
#include "TestCase.h"
#include "Date.h"

class AbstractGrader {
public:
  AbstractGrader();
  virtual ~AbstractGrader();
  virtual int size() = 0;
  virtual std::string getDescription(int test_case) = 0;
  virtual int getPoints(int test_case) = 0;
  virtual Date getDueDate() = 0;
  virtual TestCase * grade(int test_case) = 0;
  void setDllHandle(void * dll_handle);
protected:
  std::string toString(int value);
  TestCase * nullObject(std::string iface);
  TestCase * failed(std::string error_message);
  TestCase * passed(long time);
  void * createObject(std::string name);
  void * m_dllHandle;
};

#endif
