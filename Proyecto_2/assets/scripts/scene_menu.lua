scene = {
   
    sprites = {
        [0]={assetId = "background", filePath = "./assets/images/Background.png"},
        {assetId = "hud", filePath = "./assets/images/HUD.png"},
    },
   
 
    fonts = {
       [0] = 
       {fontId = "press_start_24", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 24},
       {fontId = "press_start_50", filePath="./assets/fonts/press_start_2p.ttf", fontSize = 50},
    },

    music = {
        [0] =  { musicId = "menu", filePath = "./assets/audio/menu.mp3" }
    },
   
    
    keys ={
       [0]=
       {name = "up", key = 119},
       {name = "left", key = 97},
       {name = "down", key = 115},
       {name = "right", key = 100},
    },
   
 
   buttons = {
       [0] =
       {name = "mouse_left_button", button = 1}
   
   },
   

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
                   a = 255
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
                a = 255
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
                a = 255
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
                a = 255
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