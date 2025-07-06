#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>
#include "Event.hpp"

/**
 * @brief Interface for generic event callbacks.
 *
 * All specific event callbacks must inherit from this interface.
 */
class IEventCallback {
  private:
    /**
     * @brief Pure virtual function to be implemented by derived event callback classes.
     * @param e Reference to the Event being dispatched.
     */
   virtual void Call(Event& e) = 0;
  
  public:
    /**
     * @brief Virtual destructor.
     */
   virtual ~IEventCallback() = default;
    /**
     * @brief Executes the stored callback using the provided Event.
     * @param e Reference to the Event to handle.
     */
   void Execute(Event& e){
    Call(e);
   }
};

/**
 * @brief Templated class for binding specific events to class member functions.
 *
 * @tparam TOwner Type of the class that owns the callback method.
 * @tparam TEvent Type of the Event this callback handles.
 */
template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
 private:
  typedef void (TOwner::*CallbackFunction)(TEvent&);

  TOwner* ownerInstance;
  CallbackFunction callbackFunction;
    /**
     * @brief Calls the bound member function with the event.
     * @param e Reference to the event (casted to TEvent).
     */
  virtual void Call(Event& e) override {
    std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
  }

  public:
    /**
     * @brief Constructs an EventCallback with an owner and a callback function.
     * @param ownerInstance Pointer to the class instance owning the callback.
     * @param callbackFunction Pointer to the member function that handles the event.
     */
  EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction){
    this->callbackFunction = callbackFunction;
    this->ownerInstance = ownerInstance;
  }
};

/**
 * @brief Type alias for a list of event handler callbacks.
 */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @brief Event manager class responsible for subscribing and emitting events.
 */
class EventManager {
 private:
     /**
     * @brief Maps each event type to a list of event handlers.
     */
  std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

 public:
     /**
     * @brief Constructor for EventManager.
     */
  EventManager(){
    std::cout<< "[EventManager] Se ejecuta constructor" << std::endl;
  }
    /**
     * @brief Destructor for EventManager.
     */
 ~EventManager(){
    std::cout<< "[EventManager] Se ejecuta destructor" << std::endl;
  }
    /**
     * @brief Clears all current subscribers from the event system.
     */
  void Reset(){
    subscribers.clear();
  }
    /**
     * @brief Subscribes a class method to a specific event type.
     * @tparam TEvent Type of the event.
     * @tparam TOwner Type of the subscriber class.
     * @param ownerInstance Pointer to the subscriber object.
     * @param callbackFunction Member function to be called when the event is emitted.
     */
  template <typename TEvent, typename TOwner>
  void SubscribeToEvent(TOwner* ownerInstance,
  void (TOwner::*callbackFunction)(TEvent&)) {
    if(!subscribers[typeid(TEvent)].get()){
        subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
  }
    /**
     * @brief Emits an event of the specified type to all subscribed handlers.
     * @tparam TEvent Type of the event to emit.
     * @tparam TArgs Variadic arguments to construct the event.
     * @param args Arguments to forward to the event constructor.
     */
  template <typename TEvent, typename... TArgs>
  void EmitEvent(TArgs&&... args) {
    auto handlers = subscribers[typeid(TEvent)].get();
    if(handlers){
        for (auto it = handlers->begin(); it != handlers->end(); it++){
            auto handler = it->get();
            TEvent event (std::forward<TArgs>(args)...);
            handler->Execute(event);
        }
    }
  }
};
#endif