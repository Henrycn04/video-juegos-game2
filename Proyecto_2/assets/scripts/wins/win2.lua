scene = {
    --Tabla de imagenes y sprites
    sprites = {
       [0]=
       {assetId = "win", filePath = "./assets/images/win.png"},
      },
   -- Tabla con info de animaciones
   animations = {},
    -- Tabla de fuentes
    fonts = {
             [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 20},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},

    },

    music = {
        [0] =  { musicId = "win", filePath = "./assets/audio/win.mp3" }
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
                 assetId = "win",
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
--  Menu
{ components = {
    transform = {
        position = { x = 240.0, y = 520.0},
        scale = { x = 1, y = 1},
        rotation = 0.0

    },
    clickable = {

    },
    script = {
        path = "./assets/scripts/buttons/menu_button.lua",
    },
    text = {
        text = "Menu",
            fontId = "press_start_24",
            r = 255,
            g = 255,
            b = 255,
            a = 255,
            isStatic = false
    }
}
},
--  Next Level
    { components = {
        transform = {
            position = { x = 510.0, y = 520.0},
            scale = { x = 1, y = 1},
            rotation = 0.0

        },
        clickable = {

        },
        script = {
            path = "./assets/scripts/buttons/menu_button_03.lua",
        },
        text = {
            text = "Next",
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
