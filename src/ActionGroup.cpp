#include "ActionGroup.hpp"
#include <algorithm>
#include <functional>
#include <vector>
namespace adas
{
namespace
{
using Action = std::function<void(PoseHandler&)>;

class ForwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Forward();
    }
};

class BackwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Backward();
    }
};

class TurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeft();
    }
};

class ReverseTurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRight();
    }
};

class TurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRight();
    }
};

class ReverseTurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeft();
    }
};

class BeFastAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};

class BeReverseAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};

// 原子操作向量与 ActionType 的枚举顺序一一对应，下标即操作类型的值
const std::vector<Action>& GetActionVec() noexcept
{
    static const std::vector<Action> actionVec{
        ForwardAction(),       BackwardAction(),        TurnLeftAction(),    ReverseTurnLeftAction(),
        TurnRightAction(),     ReverseTurnRightAction(), BeFastAction(),     BeReverseAction(),
    };
    return actionVec;
}
}  // namespace

ActionGroup::ActionGroup(const std::list<ActionType>& actions) noexcept
    : actions(actions)
{
}

void ActionGroup::PushAction(const ActionType actionType) noexcept
{
    actions.push_back(actionType);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    const auto& actionVec = GetActionVec();
    std::for_each(actions.begin(), actions.end(), [&actionVec, &poseHandler](const ActionType actionType) {
        actionVec[static_cast<std::size_t>(actionType)](poseHandler);
    });
}
}  // namespace adas
