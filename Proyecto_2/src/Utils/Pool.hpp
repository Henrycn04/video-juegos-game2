#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
/**
 * @class IPool
 * @brief Abstract base class for a component pool.
 * 
 * Used to allow polymorphic handling of different types of component pools.
 */
class IPool{
 public:
    /**
     * @brief Virtual destructor to allow proper cleanup of derived classes.
     */
  virtual ~IPool() = default;
};
/**
 * @class Pool
 * @brief A generic memory pool for storing components of a specific type.
 * 
 * This class is used in an ECS architecture to efficiently store and access components.
 * @tparam TComponent Type of the component to store in the pool.
 */
template <typename TComponent>
class Pool : public IPool {
 private:
  std::vector<TComponent> data;

 public:
     /**
     * @brief Constructs a Pool with a specified initial size.
     * @param size Initial size of the pool (default is 1000).
     */
  Pool(int size = 1000){
    data.resize(size);
  }
    /**
     * @brief Virtual destructor.
     */
  virtual ~Pool() = default;
    /**
     * @brief Checks if the pool is empty.
     * @return True if the pool is empty, false otherwise.
     */
  bool IsEmpty() const {
    return data.empty();
  }
    /**
     * @brief Gets the current size of the pool.
     * @return Number of elements in the pool.
     */
  int GetSize() const{
    return static_cast<int>(data.size());
  }
    /**
     * @brief Resizes the pool to a new size.
     * @param n The new size of the pool.
     */
  void Resize (int n){
    data.resize(n);
  }
    /**
     * @brief Clears all elements from the pool.
     */
  void Clear(){
    data.clear();
  }
    /**
     * @brief Adds a new component to the end of the pool.
     * @param object The component to add.
     */
  void Add(TComponent object){
    data.push_back(object);
  }
    /**
     * @brief Sets a component at a specific index in the pool.
     * @param index The index to set.
     * @param object The component to assign.
     */
  void Set(int index, TComponent object){
    data[index] = object;
  }
    /**
     * @brief Gets a reference to the component at the given index.
     * @param index The index of the component.
     * @return A reference to the component at the specified index.
     */
  TComponent& Get(unsigned int index){
    return static_cast<TComponent&>(data[index]);
  }
    /**
     * @brief Overloaded indexing operator for accessing components.
     * @param index The index of the component.
     * @return A reference to the component at the specified index.
     */
   TComponent& operator[](unsigned int index){
    return static_cast<TComponent&>(data[index]);
  }
};

#endif