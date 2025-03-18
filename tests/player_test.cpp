#include <gtest/gtest.h>
#include "../src/Player.h"

class PlayerTest : public ::testing::Test {
protected:
    Player* player;

    void SetUp() override {
        player = new Player("TestPlayer", 100);
    }

    void TearDown() override {
        delete player;
    }
};

// Тесты конструктора
TEST_F(PlayerTest, ConstructorTest) {
    Player defaultPlayer;
    EXPECT_EQ(defaultPlayer.getName(), "Player");
    EXPECT_EQ(defaultPlayer.getHealth(), 100);
    EXPECT_EQ(defaultPlayer.getLevel(), 1);
    EXPECT_EQ(defaultPlayer.getExperience(), 0);
    EXPECT_EQ(defaultPlayer.getMaxHealth(), 100);

    Player customPlayer("Custom", 150);
    EXPECT_EQ(customPlayer.getName(), "Custom");
    EXPECT_EQ(customPlayer.getHealth(), 150);
    EXPECT_EQ(customPlayer.getMaxHealth(), 150);
}

// Тесты имени
TEST_F(PlayerTest, NameTest) {
    EXPECT_EQ(player->getName(), "TestPlayer");
    
    player->setName("NewName");
    EXPECT_EQ(player->getName(), "NewName");
}

// Тесты здоровья
TEST_F(PlayerTest, HealthTest) {
    // Проверка начального здоровья
    EXPECT_EQ(player->getHealth(), 100);
    EXPECT_EQ(player->getMaxHealth(), 100);

    // Проверка урона
    player->setHealth(50);
    EXPECT_EQ(player->getHealth(), 50);

    // Проверка лечения
    player->setHealth(80);
    EXPECT_EQ(player->getHealth(), 80);

    // Проверка превышения максимального здоровья
    player->setHealth(150);
    EXPECT_EQ(player->getHealth(), 100);

    // Проверка отрицательного здоровья
    player->setHealth(-50);
    EXPECT_EQ(player->getHealth(), 0);
}

// Тесты опыта и уровней
TEST_F(PlayerTest, ExperienceAndLevelTest) {
    // Начальные значения
    EXPECT_EQ(player->getLevel(), 1);
    EXPECT_EQ(player->getExperience(), 0);

    // Добавление малого количества опыта (без повышения уровня)
    player->addExperience(50);
    EXPECT_EQ(player->getLevel(), 1);
    EXPECT_EQ(player->getExperience(), 50);

    // Добавление опыта для повышения уровня
    player->addExperience(50);  // Всего 100 опыта
    EXPECT_EQ(player->getLevel(), 2);
    EXPECT_EQ(player->getExperience(), 100);
    EXPECT_EQ(player->getMaxHealth(), 120);  // 100 + (2-1)*20
    EXPECT_EQ(player->getHealth(), 120);     // Здоровье восстанавливается при повышении уровня

    // Проверка отрицательного опыта
    player->addExperience(-50);
    EXPECT_EQ(player->getExperience(), 100);  // Опыт не должен уменьшаться
}

// Тест повышения уровня и увеличения максимального здоровья
TEST_F(PlayerTest, LevelUpHealthIncrease) {
    // Повышаем до 3 уровня
    player->addExperience(250);
    EXPECT_EQ(player->getLevel(), 3);
    EXPECT_EQ(player->getMaxHealth(), 140);  // 100 + (3-1)*20
    EXPECT_EQ(player->getHealth(), 140);     // Полное здоровье после повышения уровня

    // Наносим урон
    player->setHealth(100);
    EXPECT_EQ(player->getHealth(), 100);

    // Повышаем уровень и проверяем восстановление здоровья
    player->addExperience(50);  // До 4 уровня
    EXPECT_EQ(player->getLevel(), 4);
    EXPECT_EQ(player->getMaxHealth(), 160);  // 100 + (4-1)*20
    EXPECT_EQ(player->getHealth(), 160);     // Здоровье должно восстановиться
}