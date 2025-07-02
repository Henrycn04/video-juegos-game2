scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "background", filePath = "./assets/images/background.jpeg"},
       {assetId = "hud", filePath = "./assets/images/HUD.png"}
      },
   -- Tabla con info de animaciones
   animations = {},
    -- Tabla de fuentes
    fonts = {
             [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 20},
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
                 width = 1024,
                 height = 1024,
                 src_rect = { x = 0, y = 0},
 
             },
             transform = {
                 position = { x = 0.0, y = 0.0},
                 scale = { x = 0.8, y = 0.6},
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
                position = { x =220.0, y = 490.0},
                scale = { x = 0.125, y = 0.09},
                rotation = 0.0

            },
        }
    },
    { -- PLAYER
    components = {
        camera_follow = {},
        tag = {
            tag = "player",
        },
        transform = {
            position = { x = 0.0, y = 0.0},
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0

        },
    }
},
--  level 1
{ components = {
    transform = {
        position = { x = 330.0, y = 500.0},
        scale = { x = 1, y = 1},
        rotation = 0.0

    },
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
            isStatic = false
    }
}
},
--  level 2
    { components = {
        transform = {
            position = { x = 330.0, y = 525.0},
            scale = { x = 1, y = 1},
            rotation = 0.0

        },
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
                isStatic = false
        }
    }
},
--  level 3
{ components = {
    transform = {
        position = { x = 330.0, y = 550.0},
        scale = { x = 1, y = 1},
        rotation = 0.0

    },
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
            isStatic = false
    }
}
},
    
    }
}
