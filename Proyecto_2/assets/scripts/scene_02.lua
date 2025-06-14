scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "terrain", filePath = "./assets/images/Terrain.png"},
        {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png"},
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


       {
        components = {
            camera_follow = {},
            box_collider = {
              width = 32,
              height = 32,
              offset= { x= 0, y = 0},

            },
            rigidbody ={
                is_dynamic = true,
                mass = 10;

            },
            script = {
                path = "./assets/scripts/player_frog.lua",
            },
            sprite = {
                assetId = "frog_idle",
                width = 32,
                height = 32,
                src_rect = { x = 0, y = 0},

            },
            transform = {
                position = { x = 400.0, y = 300.0},
                scale = { x = 1.0, y = 1.0},
                rotation = 0.0

            }
        }
    },


     }
   }

