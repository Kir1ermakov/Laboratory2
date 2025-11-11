
#include "game_map.h"

int main()
{

	Map GAME(15, 15, 7, 2, Direction::kRight, 3, 10, 0);

	GAME.add_wall(3,1);
	GAME.add_wall(3,2);
	GAME.add_wall(3,3);
	GAME.add_wall(4,3);
	GAME.add_wall(5,3);
	GAME.add_wall(9,3);
	GAME.add_wall(10,3);
	GAME.add_wall(11,3);
	GAME.add_wall(11,2);
	GAME.add_wall(11,1);
	GAME.add_wall(6,5);

	GAME.add_wall(12, 10);
	GAME.add_wall(14, 10);
	GAME.add_wall(14, 11);
	GAME.add_wall(14, 12);
	GAME.add_wall(14, 13);
	GAME.add_wall(14, 14);
	GAME.add_wall(13, 14);
	GAME.add_wall(12, 14);
	GAME.add_wall(12, 13);
	GAME.add_wall(12, 12);
	GAME.add_wall(12, 11);

	GAME.add_monster(7,7);
   	GAME.add_monster(9, 7);
    GAME.add_tower(7, 12);
    GAME.add_boss(10, 12, 3, 2); 
    
    GAME.add_chest(5, 2, 10, 10, 10);
    GAME.add_med_kit(4, 2, 3);
	
    GAME.add_trap(8, 8, 1);          
    GAME.add_key(6, 6);              
    GAME.add_door(13, 10);           
    GAME.add_barrier(8, 5, 2);       
    GAME.add_light_armor(1, 1);      
    GAME.add_medium_armor(2, 2);     
    GAME.add_heavy_armor(13, 12);    
    
    GAME.start();
	

    return 0;
}