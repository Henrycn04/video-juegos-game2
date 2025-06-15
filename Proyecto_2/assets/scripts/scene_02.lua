scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "terrain", filePath = "./assets/images/Terrain.png"},
        {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png"},
        {assetId = "frog_jump", filePath = "./assets/images/frog_jump.png"},
        {assetId = "frog_fall", filePath = "./assets/images/frog_fall.png"},
        {assetId = "frog_run", filePath = "./assets/images/frog_run.png"},
    },
   -- Tabla con info de animaciones
    animations = {
        [0] = 
        { animation_id = "player_frog_idle", texture_id = "frog_idle", w = 32, h = 32, num_frames = 11,speed_rate = 15, is_loop = true,},
        { animation_id = "player_frog_jump", texture_id = "frog_jump", w = 32, h = 32, num_frames = 01,speed_rate = 01, is_loop = true,},
        { animation_id = "player_frog_fall", texture_id = "frog_fall", w = 32, h = 32, num_frames = 01,speed_rate = 01, is_loop = true,},
        { animation_id = "player_frog_run", texture_id = "frog_run", w = 32, h = 32, num_frames = 12,speed_rate = 15, is_loop = true,},
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
       {name = "jump", key = 32}, -- Espacio para saltar
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
            animation = {
                num_frames = 11,
                speed_rate = 15,
                is_loop = true,
            },
            camera_follow = {},
            box_collider = {
              width = 32,
              height = 32,
              offset= { x= 0, y = 0},

            },
            rigidbody ={
                is_dynamic = true,
                is_solid = true;
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
            tag = {
                tag = "player",
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

