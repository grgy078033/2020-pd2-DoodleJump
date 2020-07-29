How to play:  
  
    A = move left  
    D = move right  
    P = pause  
    R = resume 
    U = speed up  
    L = speed down  
    Space = shooting bullet  
  
Requirements:  
  
    Player can jump and can move across the boundary.  
    Two kinds of platforms(normal and crush).  
    Twu konds of game props(rocket and spring).  
    Hazard(monster and black hole).  
        player can shoot bullet to blast the monster.  
        monster will be remove from the scene if it is dead.  
        you can avoid monster and black hole through getting rocket.  
    The game can be played infinitely until the player died.  
    Can pause the game.  
    The score will be show above.  
    GAME OVER and final score will be show if player died.  
    Platforms classes is written by using polymorphism.  
  
Polymorphism:  
  
    In platform.h, I wrote a pure virtual function name appear().Then I creat two classes (platform_normal and platform_crush) which are inheritint from dplatform.h,both classes have the appear() function which is for creating platforms and setint their position.Then I creat a class name gen_platform to define which kind of platform will be created when I declare a platform pointer by using random number and switch case function.  
  
Bonus:  
  
    1.You can adjust game speed through pressing U or L.  
    2.The highiest score will be recorded above.  
    3.You can restart the game after player died through pressing R.  
  
  
