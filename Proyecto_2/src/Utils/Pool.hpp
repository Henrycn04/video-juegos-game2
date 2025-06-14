#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

class IPool{
 public:
  virtual ~IPool() = default;
};

template <typename TComponent>
class Pool : public IPool {
 private:
  std::vector<TComponent> data;

 public:
  Pool(int size = 1000){
    data.resize(size);
  }

  virtual ~Pool() = default;

  bool IsEmpty() const {
    return data.empty();
  }

  int GetSize() const{
    return static_cast<int>(data.size());
  }

  void Resize (int n){
    data.resize(n);
  }

  void Clear(){
    data.clear();
  }

  void Add(TComponent object){
    data.push_back(object);
  }

  void Set(int index, TComponent object){
    data[index] = object;
  }

  TComponent& Get(unsigned int index){
    return static_cast<TComponent&>(data[index]);
  }

   TComponent& operator[](unsigned int index){
    return static_cast<TComponent&>(data[index]);
  }
};

#endif