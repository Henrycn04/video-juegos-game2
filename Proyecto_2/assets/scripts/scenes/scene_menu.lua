scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "background", filePath = "./assets/images/background.jpg"},
       {assetId = "hud", filePath = "./assets/images/HUD.png"},
       {assetId = "terrain", filePath = "./assets/images/Terrain.png"},
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

      },
   -- Tabla con info de animaciones
   animations = {},
    -- Tabla de fuentes
    fonts = {
             [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},

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
   


    entities = {
        [0] = 
        --BackGround
        {
         components = {
             sprite = {
                 assetId = "background",
                 width = 2300,
                 height = 885,
                 src_rect = { x = 0, y = 0},
 
             },
             transform = {
                 position = { x = 0.0, y = 0.0},
                 scale = { x = 1, y = 1},
                 rotation = 0.0
 
             },
         }
     },
         --HUD
         {
             components = {
                 sprite = {
                     assetId = "hud",
                     width = 3072,
                     height = 1024,
                     src_rect = { x = 0, y = 0},
     
                 },
                 transform = {
                     position = { x = 500.0, y = 265.0},
                     scale = { x = 0.2, y = 0.2},
                     rotation = 0.0
     
                 },
             }
         },
        -- TITLE
        {
            components = {
                clickable = {
    
                },
                text = {
                    text = "Obelisk Defender",
                    fontId = "press_start_50",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255,
                    isStatic = true
                },
                transform = {
                    position = { x = 450.0, y = 50.0},
                    scale = { x = 1.0, y = 1.0},
                    rotation = 0.0
    
                }
            }
        },
        --Level 1
        {
         components = {
             clickable = {
 
             },
             script = {
                 path = "./assets/scripts/buttons/menu_button_01.lua",
             },
             text = {
                 text = "Level 01",
                 fontId = "press_start_24",
                 r = 255,
                 g = 255,
                 b = 255,
                 a = 255,
                 isStatic = true
             },
             transform = {
                 position = { x = 720.0, y = 300.0},
                 scale = { x = 1.0, y = 1.0},
                 rotation = 0.0
 
             }
         }
     },
     --Level 2
     {
         components = {
             clickable = {
 
             },
             script = {
                 path = "./assets/scripts/buttons/menu_button_02.lua",
             },
             text = {
                 text = "Level 02",
                 fontId = "press_start_24",
                 r = 255,
                 g = 255,
                 b = 255,
                 a = 255,
                 isStatic = true
             },
             transform = {
                 position = { x = 720.0, y = 350.0},
                 scale = { x = 1.0, y = 1.0},
                 rotation = 0.0
 
             }
         }
     },
     --Level 3
     {
         components = {
             clickable = {
 
             },
             script = {
                 path = "./assets/scripts/buttons/menu_button_03.lua",
             },
             text = {
                 text = "Level 03",
                 fontId = "press_start_24",
                 r = 255,
                 g = 255,
                 b = 255,
                 a = 255,
                 isStatic = true
             },
             transform = {
                 position = { x = 720.0, y = 400.0},
                 scale = { x = 1.0, y = 1.0},
                 rotation = 0.0
 
             }
         }
     }
      }
    }
