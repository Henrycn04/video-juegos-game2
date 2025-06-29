scene = {
    --Tabla de imagenes y sprites
    sprites = {
        [0]=
        {assetId = "terrain", filePath = "./assets/images/Terrain.png"},
        {assetId = "islands_1", filePath = "./assets/images/islands_1.png"},
        {assetId = "background", filePath = "./assets/images/background_.png"},
        {assetId = "ground", filePath = "./assets/images/midground_.png"},
        {assetId = "objects", filePath = "./assets/images/objects_.png"},
        {assetId = "objects1", filePath = "./assets/images/objects1_.png"},
        {assetId = "sky", filePath = "./assets/images/sky_.png"},
        {assetId = "player01_dino_idle", filePath = "./assets/images/player01_dino_idle.png"},
        {assetId = "player01_dino_run", filePath = "./assets/images/player01_dino_run.png"},
        {assetId = "enemy01_idle", filePath = "./assets/images/enemy01_idle.png"},
        {assetId = "arrow01", filePath = "./assets/images/arrow01.png"},

    },
   -- Tabla con info de animaciones
    animations = {
        [0] = 
        { animation_id = "player01_dino_idle", texture_id = "player01_dino_idle", w = 30, h = 36, num_frames = 4,speed_rate = 10, is_loop = true,},
        { animation_id = "player01_dino_run", texture_id = "player01_dino_run", w = 30, h = 36, num_frames = 6,speed_rate = 10, is_loop = true,},
        { animation_id = "arrow01", texture_id = "arrow01", w = 28, h = 12, num_frames = 30,speed_rate = 10, is_loop = true,},
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
    map_path = "./assets/maps/level_3.tmx",
    tilesets = {
      [1] = { tile_path = "assets/maps/islands_1.tsx", tile_name = "islands_1", firstgid = 1 },
      [2] = { tile_path = "assets/maps/sky.tsx", tile_name = "sky", firstgid = 101 },
      [3] = { tile_path = "assets/maps/background.tsx", tile_name = "background", firstgid = 165 },
      [4] = { tile_path = "assets/maps/ground.tsx", tile_name = "ground", firstgid = 245 },
      [5] = { tile_path = "assets/maps/objects1.tsx", tile_name = "objects1", firstgid = 315 },
      [6] = { tile_path = "assets/maps/objects.tsx", tile_name = "objects", firstgid = 403 },
      [7] = { tile_path = "assets/maps/terrain.tsx", tile_name = "terrain", firstgid = 463 },
    }
},

    --Tabla de entidades
    entities = {
       [0] = 


       { -- PLAYER
        components = {
            animation = {
                num_frames = 4,
                speed_rate = 15,
                is_loop = true,
            },
            camera_follow = {},
            box_collider = {
              width = 30,
              height = 36,
              offset= { x= 0, y = 0},

            },
            rigidbody ={
                is_dynamic = true,
                is_solid = true,
                is_enemy = false,
                is_player = true,
                mass = 10,

            },
            script = {
                path = "./assets/scripts/player01_dino.lua",
            },
            sprite = {
                assetId = "player01_dino_idle",
                width = 30,
                height = 36,
                src_rect = { x = 0, y = 0},

            },
            tag = {
                tag = "player",
            },
            transform = {
                position = { x = 50.0, y = 100.0},
                scale = { x = 1.0, y = 1.0},
                rotation = 0.0

            },
            health = {
                is_enemy = false,
                is_player = true,
                max_health = 3,
                current_health = 3,
                invincibility_time = 2.0,
            },
        }
    },


     }
   }

  