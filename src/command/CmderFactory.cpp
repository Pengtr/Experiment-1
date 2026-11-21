#include "CmderFactory.hpp"
namespace adas
{
CmderFactory::CmderFactory() noexcept
    : cmderMaps{
          BuildCmderMap(GetVehicleSpec(CarType::Normal)),
          BuildCmderMap(GetVehicleSpec(CarType::SportsCar)),
          BuildCmderMap(GetVehicleSpec(CarType::Bus)),
      }
{
}

CmderMap CmderFactory::BuildCmderMap(const VehicleSpec& spec) noexcept
{
    return {
        {'M', MoveCommand(spec)},
        {'L', TurnLeftCommand(spec)},
        {'R', TurnRightCommand(spec)},
        {'Z', TurnRoundCommand()},
        {'F', FastCommand()},
        {'B', ReverseCommand()},
    };
}

CmderList CmderFactory::GetCmders(const std::string& commands, const CarType& carType) const noexcept
{
    const auto index = static_cast<std::size_t>(carType);
    const auto& cmderMap = cmderMaps[index < cmderMaps.size() ? index : 0];
    CmderList cmders;
    for (const auto cmd : ParseCommandString(commands)) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            cmders.push_back(it->second);
        }
    }
    return cmders;
}

std::string CmderFactory::ParseCommandString(std::string_view commands) const noexcept
{
    // TR 是唯一的多字符指令，先统一替换为单字符 Z，使映射表只需以 char 为键
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}

void CmderFactory::ReplaceAll(
    std::string& inout, std::string_view what, std::string_view with) const noexcept
{
    for (std::string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length()) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}
}  // namespace adas
