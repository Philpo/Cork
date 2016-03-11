#pragma once

class IDataComponent {
public:
  virtual ~IDataComponent() {}

  virtual void* getData() = 0;
  virtual void setData(void* data) = 0;
};