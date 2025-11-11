#include <gtest/gtest.h>

#include "game_objects.h"

TEST(PlayerTest, DamageUsesArmor) {
    Player player(0, 0, Direction::kRight, 10, 0, 0);
    player.equip_armor(2);
    player.take_damage(5);
    EXPECT_EQ(player.get_health_points(), 7);
}

TEST(PlayerTest, KeyIncreasesCounter) {
    Player player(1, 1, Direction::kRight, 5, 0, 0);
    Key key(1, 1);
    ASSERT_TRUE(player.key_check(key));
    player.take_key();
    EXPECT_TRUE(player.has_key());
}

TEST(PlayerTest, NoDamageIfArmorExceedsHit) {
    Player player(0, 0, Direction::kRight, 10, 0, 0);
    player.equip_armor(10);
    player.take_damage(3);
    EXPECT_EQ(player.get_health_points(), 10);
}

TEST(BulletTest, HitMonsterWhenSameCell) {
    Monster monster(2, 2, 1, 1);
    Bullet bullet(2, 2, Direction::kRight);
    EXPECT_TRUE(bullet.hit_monster(monster));
}

TEST(BulletTest, MissMonsterWhenDifferentCell) {
    Monster monster(2, 3, 1, 1);
    Bullet bullet(2, 2, Direction::kRight);
    EXPECT_FALSE(bullet.hit_monster(monster));
}

TEST(BulletTest, HitBarrierWhenSameCell) {
    Barrier barrier(5, 5, 2);
    Bullet bullet(5, 5, Direction::kLeft);
    EXPECT_TRUE(bullet.hit_barrier(barrier));
}





TEST(EnvTest, DoorAndTrapChecksByCoordinates) {
    Player player(3, 4, Direction::kDown, 5, 0, 0);
    Door door(3, 4);
    Trap trap(3, 4, 1);
    EXPECT_TRUE(player.door_check(door));
    EXPECT_TRUE(trap.player_check(player));
    EXPECT_FALSE(trap.is_activated());
    trap.activate();
    EXPECT_TRUE(trap.is_activated());
}

