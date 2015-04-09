#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "Interfaces03.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader03.h"
#include "vector.h"
#include <cmath>
#include <fstream>

TestCase * Grader03::testVectorDoubleSort(std::string input_filename, std::string obj_filename)
{
  std::vector<double> unsorted;
  std::vector<double> sorted;

  loadBinarySequence(input_filename, unsorted);
  sorted = unsorted;

  Stopwatch watch;
  watch.start();
  IVectorDoubleSort * sorter = (IVectorDoubleSort *) createObject(obj_filename);
  if(sorter == NULL){
    return nullObject(obj_filename);
  }
  
  sorter->sort(unsorted);
  watch.stop();

  std::sort(sorted.begin(), sorted.end());

  for(int i = 0; i < sorted.size(); ++i){
    if(sorted[i] != unsorted[i]){
      return failed("sort does not match");
    }
  }

  return passed(watch.getTime());
}
 
TestCase * Grader03::testSmoothSort(std::string input_filename, std::string heap_filename)
{
  std::vector<double> smooth_input;
  std::vector<double> smooth_heap;

  loadBinarySequence(input_filename, smooth_input);
  loadBinarySequence(heap_filename, smooth_heap);

  Stopwatch watch;
  watch.start();
  ISmoothSort * sorter = (ISmoothSort *) createObject("ISmoothSort");
  if(sorter == NULL){
    return nullObject("ISmoothSort");
  }
  smooth_input= sorter->createVector();
  sorter->buildHeap(smooth_input);
  watch.pause();

  if(vectorEqual(smooth_input, smooth_heap) == false){
    return failed("build heap incorrect"); 
  }

  watch.unpause();
  sorter->sort(smooth_input);
  watch.pause();
  
  std::sort(smooth_heap.begin(), smooth_heap.end());

  if(vectorEqual(smooth_input, smooth_heap) == false){
    return failed("sort incorrect"); 
  }

  return passed(watch.getTime());
}
  
TestCase * Grader03::testLinkedListSort(std::string input_filename)
{
  std::vector<double> input_vec;

  loadBinarySequence(input_filename, input_vec);

  std::map<double, LinkedListNode *> pointers;

  LinkedListNode * head;
  LinkedListNode * curr;

  head = new LinkedListNode();
  head->key = input_vec[0];
  pointers[input_vec[0]] = head;
  
  curr = new LinkedListNode();
  curr->key = input_vec[1];
  pointers[input_vec[1]] = curr;

  head->next = curr;

  for(size_t i = 2; i < input_vec.size(); ++i){
    double value = input_vec[i];
    LinkedListNode * next = new LinkedListNode();
    next->key = value;
    next->next = NULL;
    pointers[value] = next;
    curr->next = next;
    curr = next;
  }

  Stopwatch watch;
  watch.start();

  ILinkedListSort * sorter = (ILinkedListSort *) createObject("ILinkedListSort");
  if(sorter == NULL){
    return nullObject("ILinkedListSort");
  }

  LinkedListNode * new_head = sorter->sort(head);
  watch.stop();

  std::sort(input_vec.begin(), input_vec.end());

  curr = new_head;

  for(size_t i = 0; i < input_vec.size(); ++i){
    if(curr == NULL){
      return failed("null curr during iteration");
    }
    double key = curr->key;
    if(pointers[key] != curr){
      return failed("must move pointers and not keys");
    }
    if(key != input_vec[i]){
      return failed("incorrect key");
    }
    curr = curr->next;
  }
  return passed(watch.getTime());
}

TestCase * Grader03::testRunningMedian(std::string input_filename, 
  std::string output_filename, int window_size)
{

  std::vector<int> input_vec;
  std::vector<int> output_vec;

  loadBinarySequence(input_filename, input_vec);
  loadBinarySequence(output_filename, output_vec);

  Stopwatch watch;
  watch.start();

  IRunningMedian * running = (IRunningMedian *) createObject("IRunningMedian");
  if(running == NULL){
    return nullObject("IRunningMedian");
  }

  std::vector<int> user_output = running->compute(input_vec, window_size);
  watch.stop();

  if(vectorEqual(output_vec, user_output) == false){
    return failed("result incorrect"); 
  }

  return passed(watch.getTime());
}

std::string readString(std::ifstream& fin)
{
  int size;
  fin.read((char *) &size, sizeof(int));
  char * ch = new char[size+1];
  fin.read((char *) ch, sizeof(char)*size);
  ch[size] = 0;
  std::string ret(ch);
  delete [] ch;
  return ret;
}

void Grader03::loadEmployees(std::string input_filename, 
  std::vector<Employee>& emps)
{
  std::ifstream fin(input_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    std::string first_name = readString(fin);
    std::string last_name = readString(fin);
    std::string password = readString(fin);
    Employee emp;
    emp.first_name = first_name;
    emp.last_name = last_name;
    emp.password = password;
    emps.push_back(emp);
  }
  fin.close();
}

void Grader03::loadEmployeeCommands(std::string input_filename, 
  std::vector<EmployeeCmd>& cmds)
{
  std::ifstream fin(input_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    int action;
    fin.read((char *) &action, sizeof(int));
    std::string str = readString(fin);
    std::string first_name = readString(fin);
    std::string last_name = readString(fin);
    std::string password = readString(fin);
    EmployeeCmd cmd;
    cmd.action = action;
    cmd.str = str;
    cmd.ret.first_name = first_name;
    cmd.ret.last_name = last_name;
    cmd.ret.password = password;
    cmds.push_back(cmd);
  }
  fin.close();
}

bool matches(Employee& lhs, Employee& rhs){
  if(lhs.first_name != rhs.first_name){
    std::cout << "fname" << std::endl;
    std::cout << "  lhs: " << lhs.first_name << std::endl;
    std::cout << "  rhs: " << rhs.first_name << std::endl;
    return false;
  }
  if(lhs.last_name != rhs.last_name){
    std::cout << "lname" << std::endl;
    return false;
  }
  if(lhs.password != rhs.password){
    std::cout << "password" << std::endl;
    return false;
  }
  return true;
} 

TestCase * Grader03::testEmployeeRecords(std::string input_filename, std::string input_cmd_filename)
{
  std::vector<Employee> input_vec;
  loadEmployees(input_filename, input_vec);
  std::vector<EmployeeCmd> commands;
  loadEmployeeCommands(input_cmd_filename, commands);
  
  Stopwatch watch;
  watch.start();

  IRecordsSearch * records = (IRecordsSearch *) createObject("IRecordsSearch");
  if(records == NULL){
    return nullObject("IRecordsSearch");
  }

  records->bulkInsert(input_vec);

  int FIRST_NAME = 0;
  int LAST_NAME = 1;
  int PASSWORD = 2;

  for(size_t i = 0; i < commands.size(); ++i){
    EmployeeCmd cmd = commands[i];
    if(cmd.action == FIRST_NAME){
      Employee employ = records->searchFirstName(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search first_name mismatch");
      }
    } else if(cmd.action == LAST_NAME){
      Employee employ = records->searchLastName(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search last_name mismatch");
      }
    } else if(cmd.action == PASSWORD){
      Employee employ = records->searchPassword(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search password mismatch");
      }
    }
  }

  watch.stop();
  return passed(watch.getTime());
}

void Grader03::genVector(std::vector<int>& vec_start, std::vector<int>& vec_gold, int order, int len)
{
  if(order == 0){
    for(int i = 0; i < len; ++i){
      vec_start.push_back(i);
    }
  } else if(order == 1){
    for(int i = 0; i < len; ++i){
      vec_start.push_back(len-i);
    }
  } else {
    m_Random.randomVector(len, vec_start);
  }
  for(size_t i = 0; i < vec_start.size(); ++i){
    vec_gold.push_back(vec_start[i]);
  }
  sort(vec_gold.begin(), vec_gold.end());
}

TestCase * Grader03::testHeapSort(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  IHeapSort * sorter = (IHeapSort *) createObject("IHeapSort");
  if(sorter == NULL){
    return nullObject("IHeapSort");
  }
  Stopwatch watch;
  sorter->sort(vec_start);
  watch.stop();

  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = watch.getTime();

  if(vec_start.size() != vec_gold.size()){
    ret->passed = false;
    ret->error_message = "vec.size() != ans.size()";
    return ret;
  }

  for(size_t i = 0; i < vec_gold.size(); ++i){
    int lhs = vec_gold[i];
    int rhs = vec_start[i];
    if(lhs != rhs){
      ret->passed = false;
      ret->error_message = std::string("location ") + toString(i) + std::string(" has the first error");
      return ret;
    }
  }

  return ret;
}

TestCase * Grader03::testMergeSort(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  ICircularList * list = (ICircularList *) createObject("ICircularList");
  if(list == NULL){
    return nullObject("ICircularList");
  }
  
  for(size_t i = 0; i < vec_start.size(); ++i){
    list->addHead(vec_start[i]);
  }

  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = 0;

  std::map<ISingleNode03 *, int> pointers;
  ISingleNode03 * tail = list->getTail();
  if(tail == NULL){
    ret->passed = false;
    ret->error_message = "getTail cannot be null";
    return ret;
  }
  tail = tail->getNext();

  for(size_t i = 0; i < vec_start.size(); ++i){
    pointers[tail] = tail->getValue();
    tail = tail->getNext();
  }  

  IMergeSort * sorter = (IMergeSort *) createObject("IMergeSort");
  if(sorter == NULL){
    return nullObject("IMergeSort");
  }
  
  Stopwatch watch;
  sorter->mergeSort(list);
  watch.stop();
  ret->time = watch.getTime();

  tail = list->getTail();
  if(tail == NULL){
    ret->passed = false;
    ret->error_message = "getTail cannot be null";
    return ret;
  }

  tail = tail->getNext();
  for(size_t i = 0; i < vec_gold.size(); ++i){
    int lhs = tail->getValue();
    int rhs = vec_gold[i];

    if(lhs != rhs){
      ret->passed = false;
      ret->error_message = std::string("location ") + toString(i) + std::string(" has the first error. your answer is: ") + toString(lhs) + std::string(" , while our answer is: ") + toString(rhs);
      return ret;
    }

    if(!(pointers[tail] == lhs)){
      ret->passed = false;
      ret->error_message = "you must manipulate pointers";
      return ret;
    }

    tail = tail->getNext();
  }  
  return ret;
}

std::string Grader03::baseConversion(int value)
{
  std::string letters = "abcdefghijklmnopqrstuvwxyz";
  std::string ret = "";

  while(value > 0){
    int mod = value % letters.size();
    ret = letters[mod] + ret;
    value /= letters.size();
  }
  return ret;
}

void Grader03::genStringVector(std::vector<std::string>& vec_start, std::vector<std::string>& vec_gold, int order, int len)
{
  if(order == 0){
    for(int i = 1; i < len; ++i){
      vec_start.push_back(baseConversion(i));
    }
  } else if(order == 0){
    for(int i = 1; i < len; ++i){
      vec_start.push_back(baseConversion(len - i + 1));
    }
  } else {
    std::vector<int> choices;
    for(int i = 1; i < len; ++i){
      choices.push_back(i);
    }
    while(choices.size() > 2){
      int index = m_Random.nextInt(choices.size()-1);
      int value = choices[index];
      choices[index] = choices[choices.size()-1];
      choices.pop_back();
      vec_start.push_back(baseConversion(value));
    }
  }
  for(size_t i = 0; i < vec_start.size(); ++i){
    vec_gold.push_back(vec_start[i]);
  }
  sort(vec_gold.begin(), vec_gold.end());
}

TestCase * Grader03::testRadixSort(int order, int len)
{
  std::vector<std::string> vec_start;
  std::vector<std::string> vec_gold;
  genStringVector(vec_start, vec_gold, order, len);

  IRadixSort * sorter = (IRadixSort *) createObject("IRadixSort");
  if(sorter == NULL){
    return nullObject("IRadixSort");
  }
  
  Stopwatch watch;
  sorter->sort(vec_start);
  watch.stop();

  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = watch.getTime();

  if(vec_start.size() != vec_gold.size()){
    ret->passed = false;
    ret->error_message = std::string("error in size. accepted: ") + toString(vec_gold.size()) + std::string(" yours: ") + toString(vec_start.size());
    return ret;
  }

  for(size_t i = 0; i < vec_gold.size(); ++i){
    if(vec_gold[i] != vec_start[i]){
      ret->passed = false;
      ret->error_message = std::string("element ") + toString(i) + std::string(" is out of order");
      std::cout << "vec_gold[i]: " << vec_gold[i] << std::endl;
      std::cout << "vec_start[i]: " << vec_start[i] << std::endl;
      return ret;
    }
  }
  return ret;
}

IDoubleList03 * Grader03::createList(std::vector<int>& vec_start)
{
  IDoubleList03 * list = (IDoubleList03 * ) createObject("IDoubleList03");
  if(list == NULL){
    return NULL;
  }
    
  for(size_t j = 0; j < vec_start.size(); ++j){
    list->addBack(vec_start[j]);
  }

  return list;
}

TestCase * Grader03::testKthMin(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  TestCase * ret = new TestCase();

  Stopwatch watch;
  watch.start();
  watch.pause();

  IKthMin * min = (IKthMin *) createObject("IKthMin");
  if(min == NULL){
    return nullObject("IKthMin");
  }

  for(size_t i = 0; i < vec_gold.size(); ++i){   
    IDoubleList03 * list = createList(vec_start);
    if(list == NULL){
      return nullObject("IDoubleList03");
    }
    watch.unpause(); 
    int kth = min->findKthMin(list, i);
    watch.pause();
    delete list;

    if(kth != vec_gold[i]){
      ret->passed = false;  
      ret->error_message = std::string("the ")+toString(i)+std::string("th min should be: ")+toString(vec_gold[i])+std::string(". you said it was: ")+toString(kth);
      return ret;
    }
  }

  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = watch.getTime();

  return ret;
}

int Grader03::size(){
  return 34;
}

std::string Grader03::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "vector double sort1";
  case 1: return "vector double sort2";
  case 2: return "smoothsort small";
  case 3: return "smoothsort large";
  case 4: return "linked-list sort small";
  case 5: return "linked-list sort large";
  case 6: return "running median small";
  case 7: return "running median large";
  case 8: return "employee records small";
  case 9: return "employee records large";
  case 10: return "heapsort sorted small";
  case 11: return "heapsort reverse sorted small";
  case 12: return "heapsort random small";
  case 13: return "heapsort sorted big";
  case 14: return "heapsort reverse sorted big";
  case 15: return "heapsort random big";
  case 16: return "mergesort sorted small";
  case 17: return "mergesort reverse sorted small";
  case 18: return "mergesort random sorted small";
  case 19: return "mergesort sorted big";
  case 20: return "mergesort reverse sorted big";
  case 21: return "mergesort random big";
  case 22: return "string radix sort sorted small";
  case 23: return "string radix sort reverse sorted small";
  case 24: return "string radix sort random small";
  case 25: return "string radix sort sorted big";
  case 26: return "string radix sort reverse sorted big";
  case 27: return "string radix sort random big";
  case 28: return "kth min sorted small";
  case 29: return "kth min reverse sorted small";
  case 30: return "kth min random small";
  case 31: return "kth min sorted big";
  case 32: return "kth min reverse sorted big";
  case 33: return "kth min random big";
  }
  return "";
}

int Grader03::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 2;
  case 1: return 2;
  case 2: return 3;
  case 3: return 3;
  case 4: return 3;
  case 5: return 3;
  case 6: return 3;
  case 7: return 3;
  case 8: return 3;
  case 9: return 3;
  case 10: return 3;
  case 11: return 3;
  case 12: return 3;
  case 13: return 3;
  case 14: return 3;
  case 15: return 3;
  case 16: return 3;
  case 17: return 3;
  case 18: return 3;
  case 19: return 3;
  case 20: return 3;
  case 21: return 3;
  case 22: return 3;
  case 23: return 3;
  case 24: return 3;
  case 25: return 3;
  case 26: return 3;
  case 27: return 3;
  case 28: return 3;
  case 29: return 3;
  case 30: return 3;
  case 31: return 3;
  case 32: return 3; 
  case 33: return 3;
  }
  return 0;
}

Date Grader03::getDueDate()
{
  return Date(10, 17, 2013);
}
  
TestCase * Grader03::grade(int index){
  switch(index){
  case 0:
    return testVectorDoubleSort("workload1.bin", "IVectorDoubleSort1");
  case 1:
    return testVectorDoubleSort("workload2.bin", "IVectorDoubleSort2");
  case 2:
    return testSmoothSort("smooth_input_small.bin", "smooth_heap_small.bin");
  case 3:
    return testSmoothSort("smooth_input_large.bin", "smooth_heap_large.bin");
  case 4:
    return testLinkedListSort("linked_list_input_small.bin");
  case 5:
    return testLinkedListSort("linked_list_input_large.bin");
  case 6:
    return testRunningMedian("median_input_small.bin", "median_output_small.bin", 10);
  case 7:
    return testRunningMedian("median_input_large.bin", "median_output_large.bin", 1000);
  case 8:
    return testEmployeeRecords("records_small.bin", "records_cmds_small.bin");
  case 9:
    return testEmployeeRecords("records_large.bin", "records_cmds_large.bin");
  case 10:
    return testHeapSort(0, 50);
  case 11:
    return testHeapSort(1, 50);
  case 12:
    return testHeapSort(2, 50);
  case 13:
    return testHeapSort(0, 500000);
  case 14:
    return testHeapSort(1, 500000);
  case 15:
    return testHeapSort(2, 500000);
  case 16:
    return testMergeSort(0, 50);
  case 17:
    return testMergeSort(1, 50);
  case 18:
    return testMergeSort(2, 50);
  case 19:
    return testMergeSort(0, 3000);
  case 20: 
    return testMergeSort(1, 500000);
  case 21:
    return testMergeSort(2, 500000);
  case 22:
    return testRadixSort(0, 28);
  case 23:
    return testRadixSort(1, 50);
  case 24: 
    return testRadixSort(2, 50);
  case 25:
    return testRadixSort(0, 50000);
  case 26:
    return testRadixSort(1, 50000);
  case 27:
    return testRadixSort(2, 50000);
  case 28:
    return testKthMin(0, 4);
  case 29:
    return testKthMin(1, 4);
  case 30:
    return testKthMin(2, 4);
  case 31:
    return testKthMin(0, 500);
  case 32:
    return testKthMin(1, 500);
  case 33:
    return testKthMin(2, 500);
  default:
    return NULL;
  }
}
