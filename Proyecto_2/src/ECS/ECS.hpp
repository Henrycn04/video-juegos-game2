#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <cstddef>
#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include "../Utils/Pool.hpp"

const unsigned int MAX_COMPONENTS = 64;

/// Type alias for component signature used in systems.
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base class for all component types.
 */
struct IComponent {
 protected:
 /// Counter used to generate unique component IDs.
  static int nextId;
};

/**
 * @brief Template for generating unique component IDs.
 * @tparam TComponent Type of the component.
 */
template <typename TComponent>
class Component : public IComponent {
 public:
   /**
   * @brief Returns a unique ID for the component type.
   * @return Unique integer ID.
   */
 static int GetId(){
    static int id = nextId++;
    return id;
 }
};

/**
 * @brief Represents an entity in the ECS system.
 */
class Entity{
 private:
  int id;

 public:

   /**
   * @brief Constructs an Entity with the given ID.
   * @param id The entity's unique identifier.
   */
  Entity(int id): id(id){}

    /**
   * @brief Returns the ID of the entity.
   * @return Entity ID.
   */
  int GetId() const;

    /**
   * @brief Marks the entity for deletion.
   */
  void Kill();

  bool operator ==(const Entity& other) const {return id == other.id; }
  bool operator !=(const Entity& other) const {return id != other.id; }
  bool operator >(const Entity& other) const {return id > other.id; }
  bool operator <(const Entity& other) const {return id < other.id; }

  /// Adds a component to the entity.
  template <typename TComponent, typename... TArgs>
  void AddComponent(TArgs&&... args);

  /// Removes a component from the entity.
  template <typename TComponent>
  void RemoveComponent();

  /// Checks if the entity has a specific component.
  template <typename TComponent>
  bool HasComponent() const;

  /// Retrieves a reference to the specified component. 
  template <typename TComponent>
  TComponent& GetComponent() const;

  /// Registry that owns this entity.
  class Registry* registry;
};

/**
 * @brief Base class for systems in the ECS.
 */
class System{
 private:
  Signature componentSignature;
  std::vector<Entity> entities;

public:
 System() = default;
 ~System() = default;

   /**
   * @brief Adds an entity to the system.
   * @param entity The entity to add.
   */
 void AddEntityToSystem(Entity entity);
   /**
   * @brief Removes an entity from the system.
   * @param entity The entity to remove.
   */
 void RemoveEntityFromSystem(Entity entity);
   /**
   * @brief Returns a list of all entities managed by this system.
   * @return Vector of entities.
   */
 std::vector<Entity> GetSystemEntities() const;
   /**
   * @brief Gets the signature of required components.
   * @return The component signature.
   */
 const Signature& GetComponentSignature() const;

   /**
   * @brief Declares a component as required by the system.
   */
 template <typename TComponent>
 void RequireComponent();

   /**
   * @brief Removes all entities from the system.
   */
 void ClearAllEntities() {
        entities.clear();
        OnClearAll();
    }
    
  /**
   * @brief Virtual method for custom cleanup in systems.
   */
    virtual void OnClearAll() {
    }
 
};

/**
 * @brief Manages all entities, components, and systems in the ECS.
 */
class Registry {
 private:
  int numEntity = 0;

  std::vector<std::shared_ptr<IPool>> componentsPools;
  std::vector<Signature> entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;

  std::deque<int> freeIds;

  public:
   Registry();
   ~Registry();
  /**
   * @brief Updates systems with pending entities.
   */
   void Update();

   //Entity Managment

     /**
   * @brief Creates a new entity.
   * @return The newly created entity.
   */
   Entity CreateEntity();
  /**
   * @brief Marks an entity to be removed.
   * @param entity The entity to kill.
   */
   void KillEntity(Entity entity);

   //Component Managment
     /**
   * @brief Adds a component to an entity.
   */
   template <typename TComponent, typename... TArgs>
   void AddComponent(Entity entity, TArgs&&... args);

    /**
   * @brief Removes a component from an entity.
   */
   template <typename TComponent>
   void RemoveComponent(Entity entity);

     /**
   * @brief Checks if an entity has a component.
   */
   template <typename TComponent>
   bool HasComponent(Entity entity) const;

    /**
   * @brief Gets a reference to a component of an entity.
   */
   template <typename TComponent>
   TComponent& GetComponent(Entity entity) const;

    //System Managment
    /**
   * @brief Adds a new system to the registry.
   */
   template <typename TSystem, typename... TArgs>
   void AddSystem(TArgs&&... args);
  /**
   * @brief Removes a system from the registry.
   */
   template <typename TSystem>
   void RemoveSystem();
  /**
   * @brief Checks if a system exists in the registry.
   */
   template <typename TSystem>
   bool HasSystem() const;
  /**
   * @brief Gets a reference to a system.
   */   
   template <typename TSystem>
   TSystem& GetSystem() const;

   // Add and remove entities to systems
  /**
   * @brief Updates all systems by adding newly created entities.
   */
   void AddEntityToSystems(Entity entity);
  /**
   * @brief Removes an entity from all systems.
   */
   void RemoveEntityFromSystems(Entity entity);

   //Reset registry
   /**
   * @brief Clears all entities and resets systems and components.
   */
   void ClearAllEntities();


};


template <typename TComponent>
void System::RequireComponent(){
  const auto componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args){
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if(static_cast<long unsigned int>(componentId) >= componentsPools.size()){
        componentsPools.resize(componentId + 10, nullptr);
    }

    if(!componentsPools[componentId]){
        std::shared_ptr<Pool<TComponent>> newComponentPool 
        = std::make_shared<Pool<TComponent>>();
        componentsPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool 
      = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    
    if(entityId >= componentPool->GetSize()){
        componentPool->Resize(numEntity + 100);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);

}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity){
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();
    
    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    auto componentPool 
     = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);

    return componentPool->Get(entityId);
}

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args){
    std::shared_ptr<TSystem>  newSystem 
     = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem(){
    auto system = system.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const{
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();

}
   
template <typename TSystem>
TSystem& Registry::GetSystem() const{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));

}

template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs&&... args){
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent(){
    registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const{
    return registry->HasComponent<TComponent>(*this);
}
   
template <typename TComponent>
TComponent& Entity::GetComponent() const{
    return registry->GetComponent<TComponent>(*this);
}


#endif