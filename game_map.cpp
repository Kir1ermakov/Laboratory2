#include "game_map.h"

Map::Map(int width, int height, int x, int y, Direction view, int hp, int bul, int gren) : width(width), height(height), walls(), enemies(),
		towers(), monsters(), bosses(), bullets(), grenades(), chests(), med_kits(), traps(), keys(), doors(), barriers(), armors(), player(Player(x, y, view, hp, bul, gren))
{
	game_map = std::vector<std::vector<char>>(height, std::vector<char>(width, '.'));
}

void Map::add_wall(int x, int y) {
    walls.push_back(Wall(x, y));
}

void Map::add_tower(int x, int y) {
    towers.push_back(Tower(x, y, 1, 1));
}

void Map::add_monster(int x, int y) {
    monsters.push_back(Monster(x, y, 1, 1));
}

void Map::add_bullet(int x, int y, Direction direction) {
    Bullet bullet(x, y, direction);
    bullets.push_back(bullet);
}

void Map::add_grenade(int x, int y, Direction direction, int timer) {
    Grenade grenade(x, y, direction, timer);
    grenades.push_back(grenade);
}

void Map::add_chest(int x, int y, int coins, int bullets, int grenades) {
    chests.push_back(Chest(x, y, coins, bullets, grenades));
}

void Map::add_med_kit(int x, int y, int health_points) {
    med_kits.push_back(MedKit(x, y, health_points));
}

void Map::add_boss(int x, int y, int health_points, int affected_area) {
    bosses.push_back(Boss(x, y, health_points, affected_area));
}

void Map::add_trap(int x, int y, int damage) {
    traps.push_back(Trap(x, y, damage));
}

void Map::add_key(int x, int y) {
    keys.push_back(Key(x, y));
}

void Map::add_door(int x, int y) {
    doors.push_back(Door(x, y));
}

void Map::add_barrier(int x, int y, int health_points) {
    barriers.push_back(Barrier(x, y, health_points));
}

void Map::add_light_armor(int x, int y) {
    armors.push_back(LightArmor(x, y));
}

void Map::add_medium_armor(int x, int y) {
    armors.push_back(MediumArmor(x, y));
}

void Map::add_heavy_armor(int x, int y) {
    armors.push_back(HeavyArmor(x, y));
}

void Map::get_enemies() {
    enemies.clear();
    enemies.insert(enemies.end(), towers.begin(), towers.end());
    enemies.insert(enemies.end(), monsters.begin(), monsters.end());
    enemies.insert(enemies.end(), bosses.begin(), bosses.end());
}

void Map::update_bullets() 
{
	bool Destroyed = false;

	for (auto bullet = bullets.begin(); bullet != bullets.end();) 
	{
		Destroyed = false;
		bullet->move();	
        for (auto monster = monsters.begin(); monster != monsters.end();)
		{
	    	if (bullet->hit_monster(*monster))
			{
				monster->damage();
				Destroyed = true;
				if (monster->get_health_points() == 0) 
                    monster = monsters.erase(monster);
				break;
			}
			else monster++;
		}
		
		for (auto boss = bosses.begin(); boss != bosses.end();)
		{
			if (bullet->hit_boss(*boss))
			{
				boss->damage();
				Destroyed = true;
				if (boss->get_health_points() == 0) 
                    boss = bosses.erase(boss);
				break;
			}
			else boss++;
		}
		
		for (auto barrier = barriers.begin(); barrier != barriers.end();)
		{
			if (bullet->hit_barrier(*barrier))
			{
				barrier->take_damage(1);
				Destroyed = true;
				if (barrier->is_destroyed()) 
                    barrier = barriers.erase(barrier);
				break;
			}
			else barrier++;
		}
	
		// Check boundaries
		if(bullet->get_x() < 0 || bullet->get_x() >= width || bullet->get_y() < 0 || bullet->get_y() >= height)
		{
			Destroyed = true;
		}
		else if (!Destroyed)
		{
			// Check walls
			for (const auto& wall : walls)
			{
				if (wall.get_x() == bullet->get_x() && wall.get_y() == bullet->get_y())
				{
					Destroyed = true;
					break;
				}
			}
		}
			
		if(Destroyed) bullet = bullets.erase(bullet);
			else bullet++;
	}	
}

void Map::update_grenades()
{
    bool Destroyed = false;

	for (auto grenade = grenades.begin(); grenade != grenades.end();)
	{
		Destroyed = false;
		grenade->move();

		if (grenade->explosion())
		{
			Destroyed = true;
		    for (auto monster = monsters.begin(); monster != monsters.end();)
			{
				if (grenade->hit_enemy(*monster))
				{
					monster->damage();
					if (monster->get_health_points() == 0) 
                        monster = monsters.erase(monster);
				}
				else monster++;
			}
			for (auto tower = towers.begin(); tower != towers.end();)
			{
				if (grenade->hit_enemy(*tower))
				{
					tower->damage();
					if (tower->get_health_points() == 0) tower = towers.erase(tower);
				}
				else tower++;
			}
			for (auto boss = bosses.begin(); boss != bosses.end();)
			{
				if (grenade->hit_enemy(*boss))
				{
					boss->damage();
					if (boss->get_health_points() == 0) 
                        boss = bosses.erase(boss);
				}
				else boss++;
			}
			for (auto barrier = barriers.begin(); barrier != barriers.end();)
			{
				if (grenade->hit_barrier(*barrier))
				{
					barrier->take_damage(2);
					if (barrier->is_destroyed()) 
                        barrier = barriers.erase(barrier);
				}
				else barrier++;
			}
			for(int i = grenade->get_x() - 1; i <= grenade->get_x() + 1; i++)
			{
				for(int j = grenade->get_y() - 1; j <= grenade->get_y() + 1; j++)
				{
					if(i>=0 && i < width && j >= 0 && j < height)
						game_map[j][i] = '@';
				}
			}
		}
		
		// Check boundaries
		if(grenade->get_x() < 0 || grenade->get_x() >= width || grenade->get_y() < 0 || grenade->get_y() >= height)
		{
			Destroyed = true;
		}
		else if (!Destroyed && !grenade->explosion())
		{
			// Check walls
			for (const auto& wall : walls)
			{
				if (wall.get_x() == grenade->get_x() && wall.get_y() == grenade->get_y())
				{
					Destroyed = true;
					break;
				}
			}
		}
		if(Destroyed) 
            grenade = grenades.erase(grenade);
		else grenade++;
	}		
}

void Map::update_chest()
{
	for (auto chest = chests.begin(); chest != chests.end(); chest++)
	{
		if (player.chest_check(*chest))
		{
			player.take_bullets(chest->get_bullets());
			player.take_coins(chest->get_coins());
			player.take_grenades(chest->get_grenades());
			chest = chests.erase(chest);
			break;
		}
	}
}

void Map::update_med_kits()
{
	for (auto med_kit = med_kits.begin(); med_kit != med_kits.end(); med_kit++)
	{
		if (player.med_kit_check(*med_kit))
		{
			player.take_health_points(med_kit->get_health_points());
			med_kit = med_kits.erase(med_kit);
			break;
		}
	}
}

void Map::update_monsters()
{
    int x = 0, y = 0;
    for (auto& monster : monsters) {
        y = monster.get_y();
        x = monster.get_x();
        monster.move_random();
        if (monster.get_x() < 0 || monster.get_x() >= width || monster.get_y() < 0 || monster.get_y() >= height)
        {
            monster.set_x(x);
            monster.set_y(y);
        }
        else
        {
            char cell = game_map[monster.get_y()][monster.get_x()];
            if(cell != '.' && cell != 'B' && cell != 'G' && cell != 'M' && cell != 'T')
            {
                monster.set_x(x);
                monster.set_y(y);
            }
        }
    }
}

void Map::update_traps()
{
	for (auto trap = traps.begin(); trap != traps.end(); trap++)
	{
		if (trap->player_check(player))
		{
			if (!trap->is_activated())
			{
				player.take_damage(trap->get_damage());
				trap->activate();
			}
		}
	}
}

void Map::update_keys()
{
	for (auto key = keys.begin(); key != keys.end();)
	{
		if (player.key_check(*key))
		{
			player.take_key();
			key = keys.erase(key);
			break;
		}
		else
		{
			key++;
		}
	}
}

void Map::update_doors()
{
	for (auto door = doors.begin(); door != doors.end();)
	{
		if (player.door_check(*door))
		{
			if (!door->get_is_open() && player.has_key())
			{
				door->open();
				player.use_key();
				door = doors.erase(door);
				break;
			}
			else
			{
				door++;
			}
		}
		else
		{
			door++;
		}
	}
}

void Map::update_barriers()
{
	// Barriers are updated in update_bullets() and update_grenades()
	// This method can be used for other barrier-related updates if needed
}

void Map::update_armors()
{
	for (auto armor = armors.begin(); armor != armors.end();)
	{
		if (player.armor_check(*armor))
		{
			player.equip_armor(armor->get_defense_points());
			armor = armors.erase(armor);
			break;
		}
		else
		{
			armor++;
		}
	}
}

void Map::move_check(int xOffset, int yOffset, void (Player::*moveFunction)()) 
{
    int next_y = player.get_y() + yOffset;
    int next_x = player.get_x() + xOffset;
    
    if(next_y < height && next_y >= 0 && next_x < width && next_x >= 0)
    {
        // Check walls
        bool wall_blocking = false;
        for (const auto& wall : walls)
        {
            if (wall.get_x() == next_x && wall.get_y() == next_y)
            {
                wall_blocking = true;
                break;
            }
        }
        if (wall_blocking) return;
        
        // Check barriers
        bool barrier_blocking = false;
        for (const auto& barrier : barriers)
        {
            if (barrier.get_x() == next_x && barrier.get_y() == next_y && !barrier.is_destroyed())
            {
                barrier_blocking = true;
                break;
            }
        }
        if (barrier_blocking) return;
        
        // Check closed doors - allow movement if player has key
        bool door_blocking = false;
        for (const auto& door : doors)
        {
            if (door.get_x() == next_x && door.get_y() == next_y && !door.get_is_open())
            {
                // Allow movement if player has key (door will open in update_doors)
                if (!player.has_key())
                {
                    door_blocking = true;
                }
                break;
            }
        }
        if (door_blocking) return;
        
        (player.*moveFunction)();
    }
}


void Map::player_input() 
{
    int ch = 0;
    initscr();
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    noecho();
    curs_set(0);
    ch = getch();

    switch (ch) {
        case 'w':
        case 'W':
            move_check(0, -1, &Player::move_up);
            break;

        case 's':
        case 'S':
            move_check(0, 1, &Player::move_down);
            break;

        case 'a':
        case 'A':
            move_check(-1, 0, &Player::move_left);
            break;

        case 'd':
        case 'D':
            move_check(1, 0, &Player::move_right);
            break;

        case 'f':
        case 'F':
            this->add_bullet(player.get_x(), player.get_y(), player.get_view());
            player.take_bullets(-1);
            break;

        case 'g':
        case 'G':
            this->add_grenade(player.get_x(), player.get_y(), player.get_view(), 4);
            player.take_grenades(-1);
            break;

        case 'i':
        case 'I':
            player.view_up();
            break;

        case 'k':
        case 'K':
            player.view_down();
            break;

        case 'j':
        case 'J':
            player.view_left();
            break;

        case 'l':
        case 'L':
            player.view_right();
            break;
    }
    endwin();
}

void Map::render_map() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            game_map[y][x] = '.';
        }
    }
    for (const auto& wall : walls) {
        game_map[wall.get_y()][wall.get_x()] = wall.get_texture();
    }
    for (const auto& barrier : barriers) {
        game_map[barrier.get_y()][barrier.get_x()] = barrier.get_texture();
    }
    for (const auto& door : doors) {
        if (!door.get_is_open()) {
            game_map[door.get_y()][door.get_x()] = door.get_texture();
        }
    }
    for (const auto& trap : traps) {
        game_map[trap.get_y()][trap.get_x()] = trap.get_texture();
    }
    for (const auto& key : keys) {
        game_map[key.get_y()][key.get_x()] = key.get_texture();
    }
    for (const auto& armor : armors) {
        game_map[armor.get_y()][armor.get_x()] = armor.get_texture();
    }
    for (const auto& enemy : enemies) 
		game_map[enemy.get_y()][enemy.get_x()] = enemy.get_texture();
    for (const auto& bullet : bullets) {
        game_map[bullet.get_y()][bullet.get_x()] = bullet.get_texture();
    }
    for (const auto& grenade : grenades) {
        game_map[grenade.get_y()][grenade.get_x()] = grenade.get_texture();
    }
    for (const auto& chest : chests) {
        game_map[chest.get_y()][chest.get_x()] = chest.get_texture();
    }
    for (const auto& mk : med_kits) {
        game_map[mk.get_y()][mk.get_x()] = mk.get_texture();
    }
    game_map[player.get_y()][player.get_x()] = player.get_texture();
}


bool Map::render_game() {
    clear();
    //refresh();

    player_input();
    // Update collectibles and interactions immediately after player input
    update_keys();
    update_armors();
    update_chest();
    update_med_kits();
    update_doors();
    update_traps();
    render_map();
    get_enemies();
    for (Enemy enemy : enemies) {
        if (enemy.player_check(player)) {
            player.take_damage(enemy.get_damage_points());
            if (player.get_health_points() <= 0) {
                mvaddch(player.get_y(), player.get_x(), 'X');
                printw("Game Over!");
                refresh();
                return false;
            }
        }
    }
    update_bullets();
    update_grenades();
    update_monsters();
    update_barriers();
    
    if (player.get_health_points() <= 0) {
        mvaddch(player.get_y(), player.get_x(), 'X');
        printw("Game Over!");
        refresh();
        return false;
    }

    printw("\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printw("%c", game_map[y][x]);
        }
        printw("\n");
    }
    printw("Bullets: %d\n", player.get_bullets());
    printw("Grenades: %d\n", player.get_grenades());
    printw("Health Points: %d\n", player.get_health_points());
    printw("Coins: %d\n", player.get_coins());
    printw("Keys: %d\n", player.get_keys_count());
    printw("Armor Defense: %d\n", player.get_armor_defense());
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    return true;
}

void Map::start() {
    srand(time(0));
    initscr();
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    noecho();
    curs_set(0);
    bool game = true;
    while (game) {
        game = render_game();
    }
    getch();
    endwin();
}
