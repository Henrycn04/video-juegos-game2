scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "terrain", filePath = "./assets/images/Terrain.png"},
       {assetId = "player_ship", filePath = "./assets/images/player_ship.png"},
    },
   
    -- Tabla de fuentes
    fonts = {
    },
   
    --Tabla de acciones y teclas
    keys ={
       [0]=
       {name = "up", key = 119},
       {name = "left", key = 97},
       {name = "down", key = 115},
       {name = "right", key = 100},
    },
   
    --Tabla de acciones y botones del raton
   buttons = {},
   
    --Tabla de mapa
    maps = {
        map_path = "./assets/maps/level_01.tmx",
        tile_path = "./assets/maps/terrain.tsx",
        tile_name = "terrain"
    },
   
    --Tabla de entidades
    entities = {
       [0] = 


       -- Player
       {
           components = {
               camera_follow = {},
               circle_collider = {
                 radius = 8,
                 width = 16,
                 height = 16,
   
   
               },
               rigidbody ={
                   velocity = { x = 0, y = 0 },
   
               },
               script = {
                   path = "./assets/scripts/player.lua",
               },
               sprite = {
                   assetId = "player_ship",
                   width = 16,
                   height = 16,
                   src_rect = { x = 16, y = 0},
   
               },
               transform = {
                   position = { x = 400.0, y = 300.0},
                   scale = { x = 2.0, y = 2.0},
                   rotation = 0.0
   
               }
           }
       },


     }
   }