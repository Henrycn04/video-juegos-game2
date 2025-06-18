#include "ECS.hpp"

#include <algorithm>

int IComponent::nextId = 0;

int Entity::GetId() const {
    return id;
}

void Entity::Kill(){
    registry->KillEntity(*this);
}

void System::AddEntityToSystem(Entity entity){
  entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity){
    auto it = std::remove_if(entities.begin(), entities.end(),
     [&entity](Entity other){return entity == other;});
    entities.erase(it, entities.end());
}

std::vector<Entity> System::GetSystemEntities() const{
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

Registry::Registry() {
    std::cout<< "[Registry] Se ejecuta constructor" << std::endl;
};
Registry::~Registry() {
    std::cout<< "[Registry] Se ejecuta destructor" << std::endl;
};

Entity Registry::CreateEntity(){
    int entityId;

    if (freeIds.empty()){
        entityId = numEntity++;
         if(static_cast<long unsigned int>(entityId) >= entityComponentSignatures.size()){
            entityComponentSignatures.resize(entityId + 100);
        }
    } else {
        entityId = freeIds.front();
        freeIds.pop_front();
    }

    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    std::cout<< "[Registry] Se crea entidad " << entityId << std::endl;

    return entity;
}

void Registry::KillEntity(Entity entity){
    entitiesToBeKilled.insert(entity);
}

void Registry::AddEntityToSystems(Entity entity){
    const int entityId = entity.GetId();

    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    for(auto system : systems){
        const auto& systemComponentSignature 
          = system.second->GetComponentSignature();
        
        bool isInterested = (entityComponentSignature & systemComponentSignature)
         == systemComponentSignature;

        if (isInterested){
            system.second->AddEntityToSystem(entity);
        }

    }
}

void Registry::RemoveEntityFromSystems(Entity entity) {
    for (auto system : systems){
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::Update(){
    for(auto entity : entitiesToBeAdded){
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for(auto entity : entitiesToBeKilled){
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();

        freeIds.push_back(entity.GetId());
    }
    entitiesToBeKilled.clear();
}

void Registry::ClearAllEntities(){
    for(int i = 0; i < numEntity; i++){
        RemoveEntityFromSystems(Entity(i));
        entityComponentSignatures[i].reset();
    }
    numEntity = 0;
    freeIds.clear();
}




