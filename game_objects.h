#pragma once

#include <cstdlib>

enum class Direction {
    kUP,
    kDown,
    kRight,
    kLeft
};

class Key;
class Armor;
class Door;
class Trap;
class Boss;
class Barrier;
class Monster;

class GameObject {
private:
    int x;
    int y;
    char texture; 
protected:
    void set_texture(char texture);
public:
    GameObject(int x, int y, char texture);
    int get_x() const;
    int get_y() const;
    char get_texture() const;
    void set_x(int x);
    void set_y(int y);
};



class Wall : public GameObject {
public:
    Wall(int x, int y) : GameObject(x, y, '#') {};
};



class Chest : public GameObject {
private:
    int coins;
    int bullets;
    int grenades;
protected:
    void set_coins(int new_coins);
    void set_bullets(int new_bullets);
    void set_grenades(int new_grenades);
public:
    Chest(int x, int y, int coins, int bullets, int grenades, char texture = '$' );
    int get_coins() const;
    int get_bullets() const;
    int get_grenades() const;
};



class MedKit : public GameObject {
private:
    int health_points;
public:
    MedKit(int x, int y, int health_points);
    int get_health_points() const;
};



class Player : public Chest {
private:
    int health_points;
    Direction view;
    int armor_defense;
    int keys_count;

public:
    Player(int x, int y, Direction view, int health_points, int bullets, int grenades);
    int get_health_points() const;
    void move_up();
    void move_down();
    void move_right();
    void move_left();
    Direction get_view() const;
    void view_up();
    void view_down();
    void view_left();
    void view_right();
    void take_coins(int given_coins);
    void take_bullets(int given_bullets);
    void take_grenades(int given_grenades);
    void take_health_points(int given_health_points);
    bool chest_check(Chest& chest);
    bool med_kit_check(MedKit& med_kit);
    int get_armor_defense() const;
    void equip_armor(int defense);
    void take_damage(int damage);
    int get_keys_count() const;
    void take_key();
    bool has_key() const;
    void use_key();
    bool key_check(Key& key);
    bool armor_check(Armor& armor);
    bool door_check(Door& door);
    bool trap_check(Trap& trap);
};



class Enemy : public GameObject {
private:
	int health_points;
	int affected_area;
	int damage_points;

public:
    Enemy(int x, int y, char texture, int health_points, int affected_area, int damage_points);
	void damage();
	int get_health_points() const;
	int get_damage_points() const;
    bool player_check(Player& player);
};



class Tower : public Enemy {
public:
    Tower(int x, int y, int health_points, int affected_area);
};



class Monster : public Enemy {
public:
    Monster(int x, int y, int health_points, int affected_area);
    void move_up();
    void move_down();
    void move_random();
};



class Projectile : public GameObject {
private:
    Direction direction;

public:
    Projectile(int x, int y, char texture, Direction direction);
    void move();
    Direction get_direction() const;
};

class Monster;

class Bullet : public Projectile {
public:
    Bullet(int x, int y, Direction direction);
    bool hit_monster(Monster& monster);
    bool hit_boss(Boss& boss);
    bool hit_barrier(Barrier& barrier);
};



class Grenade : public Projectile {
private:
    int timer;

public:
    Grenade(int x, int y, Direction direction, int timer);
    bool explosion();
    bool hit_enemy(Enemy& enemy);
    bool hit_barrier(Barrier& barrier);
};



class Boss : public Enemy {
public:
    Boss(int x, int y, int health_points, int affected_area);
};



class Trap : public GameObject {
private:
    int damage;
    bool activated;

public:
    Trap(int x, int y, int damage);
    int get_damage() const;
    bool is_activated() const;
    void activate();
    bool player_check(Player& player);
};



class Key : public GameObject {
public:
    Key(int x, int y);
};



class Door : public GameObject {
private:
    bool is_open;

public:
    Door(int x, int y);
    bool get_is_open() const;
    void open();
    bool player_check(Player& player);
};



class Barrier : public GameObject {
private:
    int health_points;

public:
    Barrier(int x, int y, int health_points);
    void take_damage(int damage);
    int get_health_points() const;
    bool is_destroyed() const;
};



class Armor : public GameObject {
protected:
    int defense_points;

public:
    Armor(int x, int y, int defense_points, char texture);
    int get_defense_points() const;
};



class LightArmor : public Armor {
public:
    LightArmor(int x, int y);
};



class MediumArmor : public Armor {
public:
    MediumArmor(int x, int y);
};



class HeavyArmor : public Armor {
public:
    HeavyArmor(int x, int y);
};