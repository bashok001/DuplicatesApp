#pragma once

#include "ObjectFactory.h"

class Factory01 : public ObjectFactory {
public:
  Factory01();
  virtual ~Factory01();
  virtual void * create(std::string interface_name);
};
