#include "ExecutorImpl.hpp"
#include "command/CmderFactory.hpp"
#include "command/Singleton.hpp"
#include <algorithm>
#include <memory>
namespace adas
{
    Executor* Executor::NewExecutor(const Pose& pose, const CarType& carType) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose, carType);
    }
    ExecutorImpl::ExecutorImpl(const Pose& pose, const CarType& carType) noexcept
        : poseHandler(pose), carType(carType)
    {
    }
    void ExecutorImpl::Execute(const std::string& commands) noexcept
    {
        const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands, carType);
        std::for_each(cmders.begin(), cmders.end(), [this](const Cmder& cmder) noexcept {
            cmder(poseHandler).DoOperate(poseHandler);
        });
    }
    Pose ExecutorImpl::Query() const noexcept
    {
        return poseHandler.Query();
    }
}
   // namespace adas
