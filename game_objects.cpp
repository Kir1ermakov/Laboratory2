#include "game_objects.h"
#include <cmath>

GameObject::GameObject(int x, int y, char texture) : x(x), y(y), texture(texture) {}

int GameObject::get_x() const {
    return x;
}

int GameObject::get_y() const {
    return y;
}

char GameObject::get_texture() const {
    return texture;
}

void GameObject::set_x(int x) {
    this->x = x;
}

void GameObject::set_y(int y) {
    this->y = y;
}

void GameObject::set_texture(char texture) {
    this->texture = texture;
}




Chest::Chest(int x, int y, int coins, int bullets, int grenades, char texture) :
    GameObject(x, y, texture), coins(coins), bullets(bullets), grenades(grenades) {}

int Chest::get_coins() const {
    return coins;
}

int Chest::get_bullets() const {
    return bullets;
}

int Chest::get_grenades() const {
    return grenades;
}

void Chest::set_coins(int new_coins) {
    this->coins = new_coins;
}

void Chest::set_bullets(int new_bullets) {
    this->bullets = new_bullets;
}

void Chest::set_grenades(int new_grenades) {
    this->grenades = new_grenades;
}



MedKit::MedKit(int x, int y, int health_points) : 
    GameObject(x, y, '+'), health_points(health_points) {}

int MedKit::get_health_points() const { return health_points; }



Player::Player(int x, int y, Direction view, int health_points, int bullets, int grenades) 
    : Chest(x, y, 0, bullets, grenades), health_points(health_points), view(view), armor_defense(0), keys_count(0) {
    switch (view) {
        case Direction::kDown:
            set_texture('v');
            break;
        case Direction::kLeft:
            set_texture('<');
            break;
        case Direction::kUP:
            set_texture('^');
            break;
        case Direction::kRight:
            set_texture('>');
            break;
    }
}

int Player::get_health_points() const { 
    return health_points; 
}

void Player::move_up() {
    set_y(get_y() - 1);
}

void Player::move_down() {
    set_y(get_y() + 1);
}

void Player::move_right() {
    set_x(get_x() + 1);
}

void Player::move_left() {
    set_x(get_x() - 1);
}

Direction Player::get_view() const { 
    return view; 
}

void Player::view_up() {
    set_texture('^'); 
    view = Direction::kUP;
}

void Player::view_down() {
    set_texture('v'); 
    view = Direction::kDown;
}

void Player::view_left() {
    set_texture('<');
    view = Direction::kLeft;
}

void Player::view_right() {
    set_texture('>');
    view = Direction::kRight;
}

void Player::take_coins(int given_coins) {
    set_coins(get_coins() + given_coins);
}

void Player::take_bullets(int given_bullets) {
    set_bullets(get_bullets() + given_bullets);
}

void Player::take_grenades(int given_grenades) {
    set_grenades(get_grenades() + given_grenades);
}

void Player::take_health_points(int given_health_points) {
    health_points += given_health_points;
}

bool Player::chest_check(Chest& chest) {
    return (get_x() == chest.get_x() && get_y() == chest.get_y());
}

bool Player::med_kit_check(MedKit& med_kit) {
    return (get_x() == med_kit.get_x() && get_y() == med_kit.get_y());
}

int Player::get_armor_defense() const {
    return armor_defense;
}

void Player::equip_armor(int defense) {
    armor_defense = defense;
}

void Player::take_damage(int damage) {
    int actual_damage = damage - armor_defense;
    if (actual_damage < 0) actual_damage = 0;
    health_points -= actual_damage;
    if (health_points < 0) health_points = 0;
}

int Player::get_keys_count() const {
    return keys_count;
}

void Player::take_key() {
    keys_count++;
}

bool Player::has_key() const {
    return keys_count > 0;
}

void Player::use_key() {
    if (keys_count > 0) {
        keys_count--;
    }
}

bool Player::key_check(Key& key) {
    return (get_x() == key.get_x() && get_y() == key.get_y());
}

bool Player::armor_check(Armor& armor) {
    return (get_x() == armor.get_x() && get_y() == armor.get_y());
}

bool Player::door_check(Door& door) {
    return (get_x() == door.get_x() && get_y() == door.get_y());
}

bool Player::trap_check(Trap& trap) {
    return (get_x() == trap.get_x() && get_y() == trap.get_y());
}



Enemy::Enemy(int x, int y, char texture, int health_points, int affected_area, int damage_points) 
    : GameObject(x, y, texture), health_points(health_points), affected_area(affected_area), damage_points(damage_points) {}

void Enemy::damage() {
	health_points--;
}

int Enemy::get_health_points() const { 
	return health_points; 
}

int Enemy::get_damage_points() const {
	return damage_points;
}

bool Enemy::player_check(Player& player) {
	int EnemyX = get_x();
	int EnemyY = get_y();
	int PlayerX = player.get_x();
	int PlayerY = player.get_y();

    return (std::abs(EnemyX - PlayerX) + std::abs(EnemyY - PlayerY)) <= affected_area;
}



Tower::Tower(int x, int y, int health_points, int affected_area) : Enemy(x, y, 'T', health_points, affected_area, 1) {}



Monster::Monster(int x, int y, int health_points, int affected_area) 
    : Enemy(x, y, 'M', health_points, affected_area, 3) {}

void Monster::move_up() {
    set_y(get_y() - 1);
}

void Monster::move_down() {
    set_y(get_y() + 1);
}

void Monster::move_random() {
    int MoveSeed = rand() % 3;
    switch (MoveSeed) {
        case 0:
            move_up();
            break;
        case 1:
            move_down();
            break;
        case 2:
            // В случае необходимости добавьте здесь дополнительное действие
            break;
    }
}



Projectile::Projectile(int x, int y, char texture, Direction direction) 
    : GameObject(x, y, texture), direction(direction) {}

void Projectile::move() {
    int X = get_x();
    int Y = get_y();
    switch (direction) {
        case Direction::kDown:
            set_y(Y + 1);
            break;
        case Direction::kLeft:
            set_x(X - 1);
            break;
        case Direction::kRight:
            set_x(X + 1);
            break;
        case Direction::kUP:
            set_y(Y - 1);
            break;
    }
}

Direction Projectile::get_direction() const {
    return direction;
}



Bullet::Bullet(int x, int y, Direction direction) 
    : Projectile(x, y, 'B', direction) {}

bool Bullet::hit_monster(Monster& monster) {
    int BulletX = get_x();
    int BulletY = get_y();
    int MonsterX = monster.get_x();
    int MonsterY = monster.get_y();

    return (BulletX == MonsterX && BulletY == MonsterY);
}

bool Bullet::hit_boss(Boss& boss) {
    int BulletX = get_x();
    int BulletY = get_y();
    int BossX = boss.get_x();
    int BossY = boss.get_y();

    return (BulletX == BossX && BulletY == BossY);
}

bool Bullet::hit_barrier(Barrier& barrier) {
    int BulletX = get_x();
    int BulletY = get_y();
    int BarrierX = barrier.get_x();
    int BarrierY = barrier.get_y();

    return (BulletX == BarrierX && BulletY == BarrierY);
}



Grenade::Grenade(int x, int y, Direction direction, int timer) 
    : Projectile(x, y, 'G', direction), timer(timer) {}

bool Grenade::explosion() {
    if (timer == 0)
        return true;
    timer--;
    return false;
}

bool Grenade::hit_enemy(Enemy& enemy) {
    int GrenadeXl = get_x() - 1;
    int GrenadeXr = get_x() + 1;
    int GrenadeYd = get_y() - 1;
    int GrenadeYu = get_y() + 1;
    int EnemyX = enemy.get_x();
    int EnemyY = enemy.get_y();

    return (GrenadeXl <= EnemyX && EnemyX <= GrenadeXr && GrenadeYd <= EnemyY && EnemyY <= GrenadeYu);
}

bool Grenade::hit_barrier(Barrier& barrier) {
    int GrenadeXl = get_x() - 1;
    int GrenadeXr = get_x() + 1;
    int GrenadeYd = get_y() - 1;
    int GrenadeYu = get_y() + 1;
    int BarrierX = barrier.get_x();
    int BarrierY = barrier.get_y();

    return (GrenadeXl <= BarrierX && BarrierX <= GrenadeXr && GrenadeYd <= BarrierY && BarrierY <= GrenadeYu);
}



Boss::Boss(int x, int y, int health_points, int affected_area) 
    : Enemy(x, y, 'O', health_points, affected_area, 5) {}



Trap::Trap(int x, int y, int damage) 
    : GameObject(x, y, 'T'), damage(damage), activated(false) {}

int Trap::get_damage() const {
    return damage;
}

bool Trap::is_activated() const {
    return activated;
}

void Trap::activate() {
    activated = true;
}

bool Trap::player_check(Player& player) {
    return (get_x() == player.get_x() && get_y() == player.get_y());
}



Key::Key(int x, int y) : GameObject(x, y, 'K') {}



Door::Door(int x, int y) : GameObject(x, y, 'D'), is_open(false) {}

bool Door::get_is_open() const {
    return is_open;
}

void Door::open() {
    is_open = true;
}

bool Door::player_check(Player& player) {
    return (get_x() == player.get_x() && get_y() == player.get_y());
}



Barrier::Barrier(int x, int y, int health_points) 
    : GameObject(x, y, '|'), health_points(health_points) {}

void Barrier::take_damage(int damage) {
    health_points -= damage;
    if (health_points < 0) health_points = 0;
}

int Barrier::get_health_points() const {
    return health_points;
}

bool Barrier::is_destroyed() const {
    return health_points <= 0;
}



Armor::Armor(int x, int y, int defense_points, char texture) 
    : GameObject(x, y, texture), defense_points(defense_points) {}

int Armor::get_defense_points() const {
    return defense_points;
}



LightArmor::LightArmor(int x, int y) : Armor(x, y, 1, 'L') {}



MediumArmor::MediumArmor(int x, int y) : Armor(x, y, 2, 'S') {}



HeavyArmor::HeavyArmor(int x, int y) : Armor(x, y, 3, 'H') {}
