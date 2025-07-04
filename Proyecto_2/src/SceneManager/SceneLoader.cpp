#include "SceneLoader.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Game/Game.hpp"

SceneLoader::SceneLoader(){
     std::cout<< "[SceneLoader] Se ejecuta constructor" << std::endl;
}

SceneLoader:: ~SceneLoader(){
     std::cout<< "[SceneLoader] Se ejecuta destructor" << std::endl;
}

void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua
    , std::unique_ptr<AnimationManager>& animationsManager
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer){
  
  sol::load_result script_result = lua.load_file(scenePath);
  if(!script_result.valid()){
    sol::error err = script_result;
    std::string errMessage = err.what();
    std::cerr<< "[SceneLoader]"<< errMessage << std::endl;
    return;

  }

  lua.script_file(scenePath);
  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  LoadSprites(renderer, sprites, assetManager);

  sol::table animations = scene["animations"];
  LoadAnimations(animations, animationsManager);

  sol::table fonts = scene["fonts"];
  LoadFonts(fonts, assetManager);

  sol::optional<sol::table> maybe_music = scene["music"];
   if (maybe_music) {
        LoadMusic(maybe_music.value(), assetManager);
  }

  sol::table keys = scene["keys"];
  LoadKeys(keys, controllerManager);

  sol::table buttons = scene["buttons"];
  LoadButtons(buttons, controllerManager);

 sol::optional<sol::table> maybe_maps = scene["maps"];
    if (maybe_maps) {
        LoadMap(lua, maybe_maps.value(), registry);
    }

  sol::table entities = scene["entities"];
  LoadEntities(lua, entities, registry);

}

void  SceneLoader::LoadSprites(SDL_Renderer* renderer, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager){
    int index = 0;
    while (true){
        sol::optional<sol::table> hasSprite = sprites [index];
        if(hasSprite == sol::nullopt){
            break;
        }

        sol::table sprite = sprites[index];

        std::string assetId = sprite["assetId"];
        std::string filePath = sprite["filePath"];

        assetManager->AddTexture(renderer, assetId, filePath);

        index++;
    }

}
void SceneLoader::LoadAnimations(const sol::table& animations
  , std::unique_ptr<AnimationManager>& animationManager) {
    int index = 0;
    while (true){
        sol::optional<sol::table> hasAnimation = animations[index];
        if(hasAnimation == sol::nullopt){
            break;
        }

        sol::table animation = animations[index];

        std::string animationId = animation["animation_id"];
        std::string textureId = animation["texture_id"];
        int width = animation["w"];
        int height = animation["h"];
        int numFrames = animation["num_frames"];
        int frameSpeedRate = animation["speed_rate"];
        bool isLoop = animation["is_loop"];

        animationManager->AddAnimation(animationId, textureId, width, height, numFrames, frameSpeedRate, isLoop);

        index++;
    }
}

void SceneLoader::LoadMusic(const sol::table& musicTable, std::unique_ptr<AssetManager>& assetManager) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasMusic = musicTable[index];
        if (hasMusic == sol::nullopt) {
            break;
        }

        sol::table music = musicTable[index];
        std::string musicId = music["musicId"];
        std::string filePath = music["filePath"];

        assetManager->LoadMusic(musicId, filePath);

        index++;
    }
    if(index > 0){
        std::cout<<"[SceneLoader] Se activa la musica de fondo"<<std::endl;
        assetManager->PlayMusic(musicTable[0]["musicId"],-1);
    }
}

void SceneLoader::LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager){
  int index = 0;
  while(true){
    sol::optional<sol::table> hasFont = fonts[index];
    if(hasFont == sol::nullopt){
        break;
    }

    sol::table font = fonts[index];
    std::string fontId = font["fontId"];
    std::string filePath = font["filePath"];
    int size = font["fontSize"];

    assetManager->AddFont(fontId, filePath, size);

    index++;
  }
}

void  SceneLoader::LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& 
  controllerManager){
     int index = 0;
    while (true){
        sol::optional<sol::table> hasKey = keys[index];
        if(hasKey == sol::nullopt){
            break;
        }

        sol::table key = keys[index];

        std::string name = key ["name"];
        int keyCode = key["key"];

        controllerManager->AddActionKey(name, keyCode);

        index++;

    }
  }

void SceneLoader::LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& 
  controllerManager){
        int index = 0;
    while (true){
        sol::optional<sol::table> hasButtons = buttons[index];
        if(hasButtons == sol::nullopt){
            break;
        }

        sol::table button = buttons[index];

        std::string name = button ["name"];
        int buttonCode = button["button"];

        controllerManager->AddMouseButton(name, buttonCode);

        index++;

    }

  }
 void SceneLoader::LoadMap(sol::state& lua, const sol::table map, std::unique_ptr<Registry>& registry){
    sol::optional<int> hasWidth = map["width"];
    if(hasWidth != sol::nullopt){
        Game::GetInstance().mapWidth = map["width"];
    }

    sol::optional<int> hasHeight = map["height"];
    if(hasHeight != sol::nullopt){
        Game::GetInstance().mapHeight = map["height"];
    }



    sol::optional<std::string> hasPath = map["map_path"];
    if(hasPath != sol::nullopt){
        std::string mappath = map["map_path"];

        //Se carga el documento xml que contiene la informacion del mapa
        tinyxml2::XMLDocument xmlmap;
        xmlmap.LoadFile(mappath.c_str());

        //Extraer la raiz del documento xml
        tinyxml2::XMLElement* xmlRoot = xmlmap.RootElement();

        //Extaer el ancho y alto de los tiles y map
        int tWidth, tHeight, mWidth, mHeight;
        xmlRoot->QueryIntAttribute("tilewidth", &tWidth);
        xmlRoot->QueryIntAttribute("tileheight", &tHeight);
        xmlRoot->QueryIntAttribute("width", &mWidth);
        xmlRoot->QueryIntAttribute("height", &mHeight);

        //Calcular width y height del mapa
        Game::GetInstance().mapWidth = tWidth * mWidth;
        Game::GetInstance().mapHeight = tHeight * mHeight;

         // Recorrer todos los tilesets definidos en Lua
        sol::optional<sol::table> hasTilesets = map["tilesets"];
        // Cargar tilesets
        if (hasTilesets) {
            sol::table luaTilesets = map["tilesets"];
            for (auto& pair : luaTilesets) {
                sol::table ts = pair.second.as<sol::table>();

                std::string tilepath = ts["tile_path"];
                std::string tileName = ts["tile_name"];
                int firstgid = ts["firstgid"];  // Necesitas pasar esto desde Lua

                tinyxml2::XMLDocument xmltileset;
                xmltileset.LoadFile(tilepath.c_str());
                tinyxml2::XMLElement* xmlTileSetRoot = xmltileset.RootElement();

                int columns = 0, tileW = 0, tileH = 0;
                xmlTileSetRoot->QueryIntAttribute("columns", &columns);
                xmlTileSetRoot->QueryIntAttribute("tilewidth", &tileW);
                xmlTileSetRoot->QueryIntAttribute("tileheight", &tileH);

                tilesets.push_back(TileSetInfo {
                    firstgid,
                    columns,
                    tileW,
                    tileH,
                    tileName
                });
            }
        }

        // Cargar capas SOLO una vez
        tinyxml2::XMLElement* xmlLayer = xmlRoot->FirstChildElement("layer");
        while (xmlLayer != nullptr) {
            LoadLayer(registry, xmlLayer, mWidth);
            xmlLayer = xmlLayer->NextSiblingElement("layer");
        }

        //Se obtiene el primer elemento de tipo objectgroup
        tinyxml2::XMLElement* xmlObjectGroup = xmlRoot->FirstChildElement("objectgroup");
        while(xmlObjectGroup != nullptr){
          const char* objectGroupName;
          std::string name;
          xmlObjectGroup->QueryStringAttribute("name", &objectGroupName);
          name = objectGroupName;
          if(name.compare("colliders")==0){
            LoadColliders(lua, registry, xmlObjectGroup);  }
            xmlObjectGroup = xmlObjectGroup->NextSiblingElement("objectgroup");
        }
        

    }
 }

#include <sstream>
#include <stdexcept>

void SceneLoader::LoadLayer(std::unique_ptr<Registry>& registry,
    tinyxml2::XMLElement* layer, int mWidth) {

    // Validar la existencia del elemento 'data'
    tinyxml2::XMLElement* xmldata = layer->FirstChildElement("data");
    if (!xmldata) {
        throw std::runtime_error("No se encontró el elemento 'data' en la capa");
    }
    const char* data = xmldata->GetText();
    if (!data) {
        throw std::runtime_error("No se encontraron datos en el elemento 'data'");
    }

    // Validar que haya tilesets definidos
    if (tilesets.empty()) {
        throw std::runtime_error("No hay tilesets definidos");
    }

    // Procesar la cadena de datos de manera eficiente
    std::stringstream dataStream(data);
    std::string token;
    int tileNumber = 0;

   while (std::getline(dataStream, token, ',')) {
    // Eliminar espacios en blanco
    std::stringstream tokenStream(token);
    tokenStream >> std::ws;
    if (tokenStream.eof()) continue; // Saltar tokens vacíos

    try {
        unsigned long gid = std::stoul(token);

        if (gid > 0) {
            const unsigned GID_MASK = 0x1FFFFFFF;
            unsigned long cleanGid = gid & GID_MASK;

            const TileSetInfo* selectedTileset = nullptr;
            for (int i = tilesets.size() - 1; i >= 0; --i) {
                if (cleanGid >= static_cast<unsigned long>(tilesets[i].firstgid)) {
                    selectedTileset = &tilesets[i];
                    break;
                }
            }

            if (!selectedTileset) {
                throw std::runtime_error("No se encontró tileset para GID: " + std::to_string(cleanGid));
            }

            auto localId = cleanGid - static_cast<unsigned long>(selectedTileset->firstgid);
            int srcX = static_cast<int>((localId % static_cast<unsigned long>(selectedTileset->columns)) * static_cast<unsigned long>(selectedTileset->tileWidth));
            int srcY = static_cast<int>((localId / static_cast<unsigned long>(selectedTileset->columns)) * static_cast<unsigned long>(selectedTileset->tileHeight));

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>(
                glm::vec2((tileNumber % mWidth) * selectedTileset->tileWidth,
                          (tileNumber / mWidth) * selectedTileset->tileHeight));
            tile.AddComponent<SpriteComponent>(
                selectedTileset->textureId,
                selectedTileset->tileWidth,
                selectedTileset->tileHeight,
                srcX,
                srcY
            );
        }
        tileNumber++;
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Error al convertir GID: " + token + " - " + e.what());
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("GID fuera de rango: " + token + " - " + e.what());
    }
}}

void SceneLoader::LoadColliders(sol::state& lua, std::unique_ptr<Registry>& registry,
 tinyxml2::XMLElement* objectGroup){
    
    tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");
    while(object != nullptr){
        const char* name = nullptr;
        std::string tag;
        int x, y, w, h;
        int gid = 0; // inicializamos

        // Obtener la tag del objeto
        object->QueryStringAttribute("name", &name);
        if (name != nullptr) {
            tag = name;
        } else {
            tag = "";  // precaución si name es nullptr
        }





        // Obtener la posicion
        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        // Obtener medidas
        object->QueryIntAttribute("width",&w);
        object->QueryIntAttribute("height",&h);

        // Obtener gid (si existe)
        object->QueryIntAttribute("gid", &gid);
        Entity collider = registry->CreateEntity();
        lua["this"] = collider;
        // Solo si tiene gid válido, agregar SpriteComponent
        if(gid > 0 && (tag == "trembling" || tag=="moveH" || tag=="moveV") ){
            lua["update"] = sol::nil;
            lua["on_collision"] = sol::nil;
            sol::load_result loaded_script;
            if(tag == "moveV"){
                loaded_script = lua.load_file("./assets/scripts/moveV.lua");
            }

             if(tag == "moveH"){
                loaded_script = lua.load_file("./assets/scripts/moveH.lua");
            }
            
             if (tag == "trembling") {
                loaded_script = lua.load_file("./assets/scripts/trembling.lua");
            }

            if (!loaded_script.valid()) {
                sol::error err = loaded_script;
                std::cerr << "Error al cargar el script para tag " << tag << ": " << err.what() << std::endl;
                return;
            }
            sol::protected_function_result result = loaded_script();
            if (!result.valid()) {
                sol::error err = result;
                std::cerr << "Error al ejecutar el script: " << err.what() << std::endl;
                return;
            }

          
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(false, true, false, false,  9999999999.0f);
               sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }
                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

            collider.AddComponent<ScriptComponent>(onCollision, update);
            // Buscar tileset correcto
            const TileSetInfo* selectedTileset = nullptr;
            for (int i = tilesets.size() - 1; i >= 0; --i) {
                if (gid >= tilesets[i].firstgid) {
                    selectedTileset = &tilesets[i];
                    break;
                }
            }
            if(selectedTileset) {
                int localId = gid - selectedTileset->firstgid;
                int srcX = (localId % selectedTileset->columns) * selectedTileset->tileWidth;
                int srcY = (localId / selectedTileset->columns) * selectedTileset->tileHeight;

                collider.AddComponent<SpriteComponent>(
                    selectedTileset->textureId,  // textura correcta
                    w, h,
                    srcX, srcY
                );
            }

        } else if (tag == "enemy01") {
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(true, true, true, false, 10.0f);
            collider.AddComponent<AnimationComponent>(8, 15, true);
            collider.AddComponent<SpriteComponent>(
                "enemy01",
                w, h,
                0, 0 // src rect (x, y) as 0, 0
            );
            collider.AddComponent<HealthComponent>(true, false, 1, 1, 0); 
            
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;

                lua.script_file("./assets/scripts/enemy01.lua");

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); // agregar funciones al binding de necesitarlas
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                collider.AddComponent<ScriptComponent>(onCollision, update, onClick);
        
        } else if (tag == "enemy02") {
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(true, true, true, false, 10.0f);
            collider.AddComponent<AnimationComponent>(15, 15, true); // 2 frames, 0.1s per frame, loop
            collider.AddComponent<SpriteComponent>(
                "enemy02", // Asumiendo que tienes un sprite llamado "enemy01"
                w, h,
                0, 0 // src rect (x, y) as 0, 0
            );

            collider.AddComponent<HealthComponent>(true, false, 1, 1, 0); 
            
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;
                lua.script_file("./assets/scripts/enemy02.lua");

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); // agregar funciones al binding de necesitarlas
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                collider.AddComponent<ScriptComponent>(onCollision, update, onClick);
        
        } else if (tag == "enemy03") {
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(true, true, true, false, 15.0f);
            collider.AddComponent<AnimationComponent>(4, 15, true); // 2 frames, 0.1s per frame, loop
            collider.AddComponent<SpriteComponent>(
                "enemy03", // Asumiendo que tienes un sprite llamado "enemy01"
                w, h,
                0, 0 // src rect (x, y) as 0, 0
            );
            collider.AddComponent<HealthComponent>(true, false, 1, 1, 0); 
            
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;

                
                lua.script_file("./assets/scripts/enemy03.lua");

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); // agregar funciones al binding de necesitarlas
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                collider.AddComponent<ScriptComponent>(onCollision, update, onClick);
        
        } else if (tag == "enemy04") {
            collider.AddComponent<TagComponent>(tag);
           collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(false, true, true, false, 10.0f);
            collider.AddComponent<AnimationComponent>(4, 15, true); // 2 frames, 0.1s per frame, loop
            collider.AddComponent<SpriteComponent>(
                "enemy04", // Asumiendo que tienes un sprite llamado "enemy01"
                w, h,
                0, 0 // src rect (x, y) as 0, 0
            );
            collider.AddComponent<HealthComponent>(true, false, 1, 1, 0); 
            
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;

                
                lua.script_file("./assets/scripts/enemy04.lua");

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); // agregar funciones al binding de necesitarlas
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                collider.AddComponent<ScriptComponent>(onCollision, update, onClick);
        
        }else if (tag == "powerup") {
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y - 45), glm::vec2(3.0, 3.0));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(false, true, false, false, 1.0f);
            collider.AddComponent<AnimationComponent>(3, 3, true); // 2 frames, 0.1s per frame, loop
            collider.AddComponent<SpriteComponent>(
                "powerup", 
                w, h,
                0, 0 // src rect (x, y) as 0, 0
            );
            collider.GetComponent<RigidBodyComponent>().isInvulnerable = true;
        }   else if (tag == "check" || tag == "win") {
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(false, true, false, false, 1.0f);
            collider.GetComponent<RigidBodyComponent>().isInvulnerable = true; // Hacerlo un trigger
        } else {
            
            collider.AddComponent<TagComponent>(tag);
            collider.AddComponent<TransformComponent>(glm::vec2(x,y));
            collider.AddComponent<BoxColliderComponent>(w,h);
            collider.AddComponent<RigidBodyComponent>(false, true, false, false, 9999999999.0f);
        }

        object = object->NextSiblingElement("object");
    }
}

void  SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities, 
  std::unique_ptr<Registry>& registry){
    
    int index = 0;
    while (true){
        sol::optional<sol::table> hasEntity = entities [index];
        if(hasEntity == sol::nullopt){
            break;
        }

        sol::table entity = entities[index];

        Entity newEntity = registry->CreateEntity();

        sol::optional<sol::table> hasComponents = entity["components"];
        if(hasComponents != sol::nullopt){
            sol::table components = entity["components"];

            //* TagComponent
            sol::optional<sol::table> hasTag = components["tag"];
            if(hasTag != sol::nullopt){
                std::string tag = components["tag"]["tag"];
                newEntity.AddComponent<TagComponent>(tag);
            }

            //* AnimationComponent
            sol::optional<sol::table>hasAnimation = 
            components["animation"];
            if(hasAnimation != sol::nullopt) {
                newEntity.AddComponent<AnimationComponent>(
                 components["animation"]["num_frames"],
                 components["animation"]["speed_rate"],
                 components["animation"]["is_loop"]
                );
            }

            //* BoxColliderComponent
            sol::optional<sol::table>hasBoxCollider = 
            components["box_collider"];
            if(hasBoxCollider != sol::nullopt) {
                newEntity.AddComponent<BoxColliderComponent>(
                    components["box_collider"]["width"],
                    components["box_collider"]["height"],
                    glm::vec2(
                        components["box_collider"]["offset"]["x"],
                        components["box_collider"]["offset"]["y"]
                    )
                );
            }

            //* CircleColiderComponent
            sol::optional<sol::table>hasCircleCollider = 
            components["circle_collider"];
            if(hasCircleCollider != sol::nullopt) {
                newEntity.AddComponent<CircleColliderComponent>(
                 components["circle_collider"]["radius"],
                 components["circle_collider"]["width"],
                 components["circle_collider"]["height"]
                );
            }
            //* CameraFollowComponent
            sol::optional<sol::table>hasCameraFollow = components["camera_follow"];
            if(hasCameraFollow != sol::nullopt){
                newEntity.AddComponent<CameraFollowComponent>();
            }

            //* ClickableComponent
            sol::optional<sol::table>hasClickable = 
            components["clickable"];
            if(hasClickable != sol::nullopt) {
                newEntity.AddComponent<ClickableComponent>();
            }

            //* HealthComponent
            sol::optional<sol::table>hasHealth = 
            components["health"];
            if(hasHealth != sol::nullopt) {
                newEntity.AddComponent<HealthComponent>(
                    components["health"]["is_enemy"],
                    components["health"]["is_player"],
                    components["health"]["max_health"],
                    components["health"]["current_health"],
                    components["health"]["invincibility_time"]
                 
                );
                if(actualLife > 0){
                    if(newEntity.HasComponent<TagComponent>()){
                    if(newEntity.GetComponent<TagComponent>().tag == "player"){
                        newEntity.GetComponent<HealthComponent>().health = actualLife;}}
                }
            }       

            //* RigidbodyComponent
            sol::optional<sol::table>hasRigidbody = 
            components["rigidbody"];
            if(hasRigidbody != sol::nullopt) {
                newEntity.AddComponent<RigidBodyComponent>(
                 
                    components["rigidbody"]["is_dynamic"],
                    components["rigidbody"]["is_solid"],
                    components["rigidbody"]["is_enemy"],
                    components["rigidbody"]["is_player"],
                    components["rigidbody"]["mass"]
                 
                );
            }
            

            

            //* Sprite Component
            sol::optional<sol::table>hasSprite = 
            components["sprite"];
            if(hasSprite != sol::nullopt) {
                newEntity.AddComponent<SpriteComponent>(
                 components["sprite"]["assetId"],
                 components["sprite"]["width"],
                 components["sprite"]["height"],
                 components["sprite"]["src_rect"]["x"],
                 components["sprite"]["src_rect"]["y"]
                );
            }
            //* Text Component
            sol::optional<sol::table>hasText = components["text"];
            if(hasText != sol::nullopt){
                newEntity.AddComponent<TextComponent>(
                    components["text"]["text"],
                    components["text"]["fontId"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"],
                    components["text"]["isStatic"]
                );
            }

            //* Transform Component
            sol::optional<sol::table>hasTransform = 
            components["transform"];
            if(hasTransform != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                glm::vec2(
                 components["transform"]["position"]["x"],
                 components["transform"]["position"]["y"]
                 ),
                glm::vec2(
                 components["transform"]["scale"]["x"],
                 components["transform"]["scale"]["y"]
                 ),
                 components["transform"]["rotation"]
                );
                 if(checkPosX != newEntity.GetComponent<TransformComponent>().position.x && newEntity.HasComponent<TagComponent>()){
                    if(newEntity.GetComponent<TagComponent>().tag == "player" && actualLife != 0){
                     newEntity.GetComponent<TransformComponent>().position.x = checkPosX;}
                }
                 if(checkPosY != newEntity.GetComponent<TransformComponent>().position.y && newEntity.HasComponent<TagComponent>()){
                    if(newEntity.GetComponent<TagComponent>().tag == "player" && actualLife != 0){
                        newEntity.GetComponent<TransformComponent>().position.y = checkPosY;}
                }
            }

            //* ScriptComponent
            sol::optional<sol::table> hasScript = components["script"];
            if(hasScript != sol::nullopt){
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;

                std::string path = components["script"]["path"];
                lua.script_file(path);

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); // agregar funciones al binding de necesitarlas
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                newEntity.AddComponent<ScriptComponent>(onCollision, update, onClick);
            }


        }

        index++;

    }
  }