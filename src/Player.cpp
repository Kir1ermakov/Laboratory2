#include "Player.h"

Player::Player(const std::string& name, int health) 
    : name(name), level(1), experience(0), maxHealth(health) {
    setHealth(health);
}

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

int Player::getLevel() const {
    return level;
}

int Player::getExperience() const {
    return experience;
}

void Player::addExperience(int exp) {
    if (exp > 0) {
        experience += exp;
        // Простая система уровней: каждые 100 опыта = новый уровень
        int newLevel = 1 + (experience / 100);
        if (newLevel != level) {
            level = newLevel;
            // Увеличиваем максимальное здоровье при повышении уровня
            maxHealth = 100 + (level - 1) * 20;
            setHealth(maxHealth); // Восстанавливаем здоровье при повышении уровня
        }
    }
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::setHealth(int newHealth) {
    // Ограничиваем здоровье до максимального значения
    if (newHealth > maxHealth) {
        newHealth = maxHealth;
    }
    Creation::setHealth(newHealth);
} 