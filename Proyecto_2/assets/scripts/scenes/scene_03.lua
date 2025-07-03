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
        {assetId = "enemy01", filePath = "./assets/images/enemy01.png"},
        {assetId = "enemy02", filePath = "./assets/images/enemy02.png"},
        {assetId = "enemy03", filePath = "./assets/images/enemy03.png"},
        {assetId = "enemy04", filePath = "./assets/images/enemy04.png"},
        {assetId = "arrow01", filePath = "./assets/images/arrow01.png"},
        {assetId = "powerup", filePath = "./assets/images/powerup.png"}, 
         {assetId = "player01_dino_idle_powerup", filePath = "./assets/images/player01_dino_idle_powerup.png"},
        {assetId = "player01_dino_run_powerup", filePath = "./assets/images/player01_dino_run_powerup.png"},
        {assetId = "player01_dino_run_damage_taken", filePath = "./assets/images/player01_dino_run_damage_taken.png"},


    },
   -- Tabla con info de animaciones
    animations = {
        [0] = 
        { animation_id = "player01_dino_idle", texture_id = "player01_dino_idle", w = 30, h = 36, num_frames = 4,speed_rate = 10, is_loop = true,},
        { animation_id = "player01_dino_run", texture_id = "player01_dino_run", w = 30, h = 36, num_frames = 6,speed_rate = 10, is_loop = true,},
        { animation_id = "arrow01", texture_id = "arrow01", w = 28, h = 12, num_frames = 30,speed_rate = 10, is_loop = true,},
        { animation_id = "powerup", texture_id = "powerup", w = 16, h = 16, num_frames = 3,speed_rate = 3, is_loop = true,},
        { animation_id = "player01_dino_idle_powerup", texture_id = "player01_dino_idle_powerup", w = 30, h = 36, num_frames = 4,speed_rate = 10, is_loop = true,},
        { animation_id = "player01_dino_run_powerup", texture_id = "player01_dino_run_powerup", w = 30, h = 36, num_frames = 6,speed_rate = 10, is_loop = true,},
        { animation_id = "player01_dino_run_damage_taken", texture_id = "player01_dino_run_damage_taken", w = 30, h = 36, num_frames = 3, speed_rate = 15, is_loop = true,},

    },
   -- Tabla de fuentes
   fonts = {
           [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
       {fontId = "press_start_32", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 32},

},

music = {
    [0] =  { musicId = "main", filePath = "./assets/audio/level3.mp3" }
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

-- Timer
{
  components = {
      script={
          path = "./assets/scripts/timer.lua",
      },
      text = {
          text = "0",
          fontId = "press_start_24",
          r = 0,
          g = 0,
          b = 0,
          a = 0,
          isStatic = true
      },
      transform = {
          position = { x = 125.0, y = 5.0},
          scale = { x = 1.0, y = 1.0},
          rotation = 0.0

      }
  }
}, 
 -- Time Text
 {
  components = {
      text = {
          text = "TIME:  ",
          fontId = "press_start_24",
          r = 0,
          g = 0,
          b = 0,
          a = 0,
          isStatic = true
      },
      transform = {
          position = { x = 5.0, y = 5.0},
          scale = { x = 1.0, y = 1.0},
          rotation = 0.0

      }
  }
}, 

 -- Points Text
 {
    components = {
        text = {
            text = "POINTS:  ",
            fontId = "press_start_24",
            r = 0,
            g = 0,
            b = 0,
            a = 0,
            isStatic = true
        },
        transform = {
            position = { x = 250.0, y = 5.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0
  
        }
    }
  }, 

       { -- PLAYER
        components = {
            text = {
                text = "00000000",
                fontId = "press_start_24",
                r = 0,
                g = 0,
                b = 0,
                a = 0,
                isStatic = true
            },
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
                path = "./assets/scripts/player01_dino_level_3.lua",
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
                max_health = 5,
                current_health = 5,
                invincibility_time = 2.0,
            },
        }
    },
-- Life
{
    components = {
        script={
            path = "./assets/scripts/lives.lua",
        },
        text = {
            text = "5",
            fontId = "press_start_24",
            r = 0,
            g = 0,
            b = 0,
            a = 0,
            isStatic = true
        },
        transform = {
            position = { x = 145.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0
  
        }
    }
  }, 
   -- Live Text
   {
    components = {
        text = {
            text = "LIVES:  ",
            fontId = "press_start_24",
            r = 0,
            g = 0,
            b = 0,
            a = 0,
            isStatic = true
        },
        transform = {
            position = { x = 5.0, y = 50.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0
  
        }
    }
  }

     }
   }

  