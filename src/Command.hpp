#pragma once
#include "ActionGroup.hpp"
namespace adas
{
class MoveCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto action =
            poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(action);
        }
        actionGroup.PushAction(action);
        return actionGroup;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const bool reverse = poseHandler.IsReverse();
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(reverse ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION);
        }
        actionGroup.PushAction(reverse ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION);
        return actionGroup;
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const bool reverse = poseHandler.IsReverse();
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(reverse ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION);
        }
        actionGroup.PushAction(reverse ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION);
        return actionGroup;
    }
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
}  // namespace adas
