#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
// 状态 B：倒车
TEST(ExecutorReverseTest, should_return_x_minus_1_given_status_is_reverse_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BM");
    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_minus_1_given_status_is_reverse_command_is_M_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    // when
    executor->Execute("BM");
    // then
    const Pose target{0, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_S_given_status_is_reverse_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BL");
    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_N_given_status_is_reverse_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BR");
    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

// 状态 B + F：倒车与加速叠加
TEST(ExecutorReverseTest, should_return_x_minus_2_given_status_is_reverse_and_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BFM");
    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_minus_2_given_status_is_reverse_and_fast_command_is_M_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    // when
    executor->Execute("BFM");
    // then
    const Pose target{0, -2, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_plus_2_given_status_is_reverse_and_fast_command_is_M_and_facing_is_S)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));
    // when
    executor->Execute("BFM");
    // then
    const Pose target{0, 2, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest,
     should_return_x_minus_1_and_facing_S_given_status_is_reverse_and_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BFL");
    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest,
     should_return_x_minus_1_and_facing_N_given_status_is_reverse_and_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BFR");
    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

// 状态取消：再次收到 B 或 F 取消对应状态
TEST(ExecutorReverseTest, should_return_y_plus_1_given_status_is_reverse_cancelled_command_is_M_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    // when
    executor->Execute("BBM");
    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_N_given_status_is_reverse_cancelled_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BBL");
    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_S_given_status_is_reverse_cancelled_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BBR");
    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_x_minus_1_given_command_is_BMB_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BMB");
    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_init_pose_given_command_is_BMBM_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BMBM");
    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest,
     should_return_x_plus_2_given_status_is_reverse_cancelled_but_still_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("BFBM");
    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
