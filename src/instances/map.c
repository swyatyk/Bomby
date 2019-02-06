//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include "headers/map.h"


int text_map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};




void initMap(){
     for(int y = 0; y < 10; y++)
     {
          for(int x = 0; x < 10; x++)
          {
               Cell tmpCell;
               tmpCell.showedId = 0;
               tmpCell.viewId = 0;
               putInstanceToCell(tmpCell,text_map[y][x]);
               Map.cells[y][x] = tmpCell;
          }
     }
}


Player newPlayerInstance(){
     Player player;
     player.viewId = 10;
     return player;
}

Wall newWallInstance(){
     Wall wall;
     wall.viewId = 9;
     return wall;
}

Bomb newBombInstance(){
     Bomb bomb;
     bomb.viewId = 10;
     return bomb;
}

Block newBlockInstance(){
     Block block;
     block.viewId = 1;
     return block;
}


