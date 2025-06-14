scene = {
    --Tabla de imagenes y sprites
    sprites = {},
   
    -- Tabla de fuentes
    fonts = {
       [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
       {fontId = "press_start_32", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 32},
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
   buttons = {
       [0] =
       {name = "mouse_left_button", button = 1}
   
   },
   
    --Tabla de entidades
    entities = {
       [0] = 
       -- TEXT
       {
           components = {
               clickable = {
   
               },
               text = {
                   text = "Galaxian",
                   fontId = "press_start_32",
                   r = 150,
                   g = 0,
                   b = 150,
                   a = 255
               },
               transform = {
                   position = { x = 50.0, y = 50.0},
                   scale = { x = 1.0, y = 1.0},
                   rotation = 0.0
   
               }
           }
       },
       {
        components = {
            clickable = {

            },
            script = {
                path = "./assets/scripts/menu_button_01.lua",
            },
            text = {
                text = "Level 01",
                fontId = "press_start_24",
                r = 150,
                g = 150,
                b = 0,
                a = 255
            },
            transform = {
                position = { x = 50.0, y = 150.0},
                scale = { x = 1.0, y = 1.0},
                rotation = 0.0

            }
        }
    }
     }
   }