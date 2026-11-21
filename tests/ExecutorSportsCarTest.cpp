#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
// 跑车规则：M 一次移动 2 格；L/R 先转向再前进 1 格。
// 加速时 M 变为移动 4 格，L/R 最前面额外插入 1 格移动；倒车时移动取反、转向互换。
TEST(ExecutorSportsCarTest, should_return_x_plus_2_given_normal_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("M");
    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_y_plus_1_and_facing_N_given_normal_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("L");
    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_y_minus_1_and_facing_S_given_normal_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("R");
    // then
    const Pose target{0, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_x_minus_2_given_reverse_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BM");
    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_y_plus_1_and_facing_S_given_reverse_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BL");
    // then
    const Pose target{0, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_y_minus_1_and_facing_N_given_reverse_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BR");
    // then
    const Pose target{0, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_x_plus_4_given_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("FM");
    // then
    const Pose target{4, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_x_plus_1_y_plus_1_and_facing_N_given_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("FL");
    // then
    const Pose target{1, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_x_plus_1_y_minus_1_and_facing_S_given_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("FR");
    // then
    const Pose target{1, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_return_x_minus_4_given_reverse_and_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BFM");
    // then
    const Pose target{-4, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest,
     should_return_x_minus_1_y_plus_1_and_facing_S_given_reverse_and_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BFL");
    // then
    const Pose target{-1, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest,
     should_return_x_minus_1_y_minus_1_and_facing_N_given_reverse_and_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::SportsCar));
    // when
    executor->Execute("BFR");
    // then
    const Pose target{-1, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
