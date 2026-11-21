#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
// Bus 规则：坐标取车头，M 每次移动 1 格；L/R 先前进 1 格再转向。
// 加速时移动步数翻倍；倒车时移动取反、转向互换。
TEST(ExecutorBusTest, should_return_x_plus_1_given_normal_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("M");
    // then
    const Pose target{1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_plus_1_and_facing_N_given_normal_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("L");
    // then
    const Pose target{1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_plus_1_and_facing_S_given_normal_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("R");
    // then
    const Pose target{1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_1_given_reverse_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BM");
    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_1_and_facing_S_given_reverse_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BL");
    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_1_and_facing_N_given_reverse_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BR");
    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_plus_2_given_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("FM");
    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_plus_2_and_facing_N_given_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("FL");
    // then
    const Pose target{2, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_plus_2_and_facing_S_given_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("FR");
    // then
    const Pose target{2, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_2_given_reverse_and_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BFM");
    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_2_and_facing_S_given_reverse_and_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BFL");
    // then
    const Pose target{-2, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_return_x_minus_2_and_facing_N_given_reverse_and_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, CarType::Bus));
    // when
    executor->Execute("BFR");
    // then
    const Pose target{-2, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
