#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <memory>

#include "stb_image.h"
#include "model_file_parser.h"
#include "obj_model_parser.h"
#include "shader.h"
#include "transform.h"
#include "component.h"

class Object {
public:
    // Delete copying 
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    // Define moving
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    // Constructors
    Object();
    Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "Object must derive from Component");

        auto typeID = std::type_index(typeid(T));
        if (components.count(typeID)) {
            return static_cast<T*>(components[typeID].get());
        }

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPointer = component.get();
        components[typeID] = std::move(component);

        return rawPointer;
    }

    template<typename T>
    T* getComponent() {
        auto typeID = std::type_index(typeid(T));
        if (components.count(typeID)) {
            return static_cast<T*>(components[typeID].get());
        }
        return nullptr;
    }

    template<typename T>
    bool hasComponent() {
        auto typeID = std::type_index(typeid(T));
        return components.count(typeID);
    }

    template<typename T>
    void deleteComponent() {
        auto typeID = std::type_index(typeid(T));
        components.erase(typeID);
    }

protected:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#endif