#include <gtest/gtest.h>
#include "../src/сreation.h"

class CreationTest : public ::testing::Test {
protected:
    Creation creation;
};

/**
 * @brief Тест установки и получения здоровья
 */
TEST_F(CreationTest, HealthGetSet) {
    // Проверяем установку положительного значения
    creation.setHealth(100);
    EXPECT_EQ(creation.getHealth(), 100);

    // Проверяем установку нулевого значения
    creation.setHealth(0);
    EXPECT_EQ(creation.getHealth(), 0);

    // Проверяем установку отрицательного значения
    creation.setHealth(-50);
    EXPECT_EQ(creation.getHealth(), 0);
}

/**
 * @brief Тест изменения здоровья
 */
TEST_F(CreationTest, HealthModification) {
    // Начальное значение
    creation.setHealth(100);
    
    // Уменьшаем здоровье
    creation.setHealth(creation.getHealth() - 30);
    EXPECT_EQ(creation.getHealth(), 70);
    
    // Увеличиваем здоровье
    creation.setHealth(creation.getHealth() + 20);
    EXPECT_EQ(creation.getHealth(), 90);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 