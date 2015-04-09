#include "Factory03.h"
#include "CircularList.h"
#include "VectorDoubleSort2.h"
#include "RecordsSearch.h"
#include "HeapSort.h"
#include "LinkedListSort.h"
#include "DoubleNode.h"
#include "DoubleList.h"
#include "KthMin.h"
#include "SingleNode.h"
#include "MergeSort.h"
#include "RunningMedian.h"
#include "RadixSort.h"
#include "SmoothSort.h"





Factory03::Factory03()
{
}

Factory03::~Factory03()
{
}
 
void * Factory03::create(std::string name)
{
  if(name == "IVectorDoubleSort1"){
    return new VectorDoubleSort2();
  } else if(name == "IVectorDoubleSort2"){
    return new VectorDoubleSort2();
  } else if(name == "ISmoothSort"){
	  return new SmoothSort();
  } else if(name == "ILinkedListSort"){
    return new LinkedListSort();
  } else if(name == "IRunningMedian"){
	  return new RunningMedian();
  } else if(name == "IRecordsSearch"){
    return new RecordsSearch();
  } else if(name == "IHeapSort"){
    return new HeapSort();
  } else if(name == "ISingleNode03"){
    return new SingleNode();
  } else if(name == "ICircularList"){
    return new CircularList();
  } else if(name == "IMergeSort"){
    return new MergeSort();
  } else if(name == "IRadixSort"){
	  return new RadixSort();
  }else if (name == "IDoubleNode03"){
	  return new DoubleNode();
  } else if (name == "IDoubleList03"){
	  return new DoubleList();
  }else if(name == "IKthMin"){
    return new KthMin() ;
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory03();  
}

}
