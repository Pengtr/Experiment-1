#pragma once
#include <array>
#include <cstddef>
#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>
#include "Command.hpp"
namespace adas
{
using Cmder = std::function<ActionGroup(PoseHandler&)>;
using CmderList = std::list<Cmder>;
using CmderMap = std::unordered_map<char, Cmder>;

class CmderFactory final
{
public:
    CmderFactory(void) noexcept;
    ~CmderFactory(void) noexcept = default;
    CmderFactory(const CmderFactory&) noexcept = delete;
    CmderFactory& operator=(const CmderFactory&) noexcept = delete;

public:
    CmderList GetCmders(const std::string& commands, const CarType& carType) const noexcept;

private:
    static CmderMap BuildCmderMap(const VehicleSpec& spec) noexcept;
    std::string ParseCommandString(std::string_view commands) const noexcept;
    void ReplaceAll(std::string& inout, std::string_view what, std::string_view with) const noexcept;

private:
    const std::array<CmderMap, 3> cmderMaps;
};
}  // namespace adas
