#pragma once
#include <cstddef>
#include "Executor.hpp"
namespace adas
{
struct VehicleSpec
{
    int moveSteps;    // M 指令一次前进的格数
    int lrMoveSteps;  // L/R 指令附带的移动格数
    bool turnFirst;   // L/R 指令是否先转向再移动
};

inline const VehicleSpec& GetVehicleSpec(const CarType& carType) noexcept
{
    // 下标与 CarType 的枚举值一一对应
    static const VehicleSpec kSpecs[] = {
        {1, 0, true},   // Normal：M 走 1 格，L/R 只转向
        {2, 1, true},   // SportsCar：M 走 2 格，L/R 先转向再走 1 格
        {1, 1, false},  // Bus：M 走 1 格，L/R 先走 1 格再转向
    };
    const auto index = static_cast<std::size_t>(carType);
    return index < sizeof(kSpecs) / sizeof(kSpecs[0]) ? kSpecs[index] : kSpecs[0];
}
}  // namespace adas
