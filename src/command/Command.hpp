#pragma once
#include "VehicleSpec.hpp"
#include "action/ActionGroup.hpp"
namespace adas
{
namespace
{
// L/R 指令的公共编排：按车型规则决定先转向还是先移动，以及移动的格数
inline void ComposeTurnActions(
    ActionGroup& actionGroup, const VehicleSpec& spec, const ActionType moveAction, const ActionType turnAction) noexcept
{
    if (spec.turnFirst) {
        actionGroup.PushAction(turnAction);
        for (int i = 0; i < spec.lrMoveSteps; ++i) {
            actionGroup.PushAction(moveAction);
        }
    } else {
        for (int i = 0; i < spec.lrMoveSteps; ++i) {
            actionGroup.PushAction(moveAction);
        }
        actionGroup.PushAction(turnAction);
    }
}
}  // namespace

class MoveCommand final
{
public:
    explicit MoveCommand(const VehicleSpec& spec) noexcept
        : spec(spec)
    {
    }
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto action =
            poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        const int times = spec.moveSteps * (poseHandler.IsFast() ? 2 : 1);
        for (int i = 0; i < times; ++i) {
            actionGroup.PushAction(action);
        }
        return actionGroup;
    }

private:
    VehicleSpec spec;
};

class TurnLeftCommand final
{
public:
    explicit TurnLeftCommand(const VehicleSpec& spec) noexcept
        : spec(spec)
    {
    }
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const bool reverse = poseHandler.IsReverse();
        const auto moveAction =
            reverse ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(moveAction);
        }
        ComposeTurnActions(
            actionGroup, spec, moveAction,
            reverse ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION);
        return actionGroup;
    }

private:
    VehicleSpec spec;
};

class TurnRightCommand final
{
public:
    explicit TurnRightCommand(const VehicleSpec& spec) noexcept
        : spec(spec)
    {
    }
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const bool reverse = poseHandler.IsReverse();
        const auto moveAction =
            reverse ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(moveAction);
        }
        ComposeTurnActions(
            actionGroup, spec, moveAction,
            reverse ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION);
        return actionGroup;
    }

private:
    VehicleSpec spec;
};

class FastCommand final
{
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_FAST_ACTION);
        return actionGroup;
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
        return actionGroup;
    }
};

class TurnRoundCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsReverse()) {
            return ActionGroup();
        }
        if (poseHandler.IsFast()) {
            return ActionGroup({
                ActionType::FORWARD_1_STEP_ACTION,
                ActionType::TURNLEFT_ACTION,
                ActionType::FORWARD_1_STEP_ACTION,
                ActionType::TURNLEFT_ACTION,
            });
        }
        return ActionGroup({
            ActionType::TURNLEFT_ACTION,
            ActionType::FORWARD_1_STEP_ACTION,
            ActionType::TURNLEFT_ACTION,
        });
    }
};
}  // namespace adas
