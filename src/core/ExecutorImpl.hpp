#pragma once
#include "PoseHandler.hpp"
#include "Executor.hpp"
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
     explicit ExecutorImpl(const Pose& pose, const CarType& carType) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;
    const CarType carType;
};
}  // namespace adas
