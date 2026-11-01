#include "PoseHandler.hpp"
namespace adas
{
namespace
{
// 朝向编码：E=0、S=1、W=2、N=3，顺时针递增
constexpr char kHeadings[] = {'E', 'S', 'W', 'N'};
constexpr int kHeadingCount = sizeof(kHeadings) / sizeof(kHeadings[0]);

int ToHeadingIndex(const char heading) noexcept
{
    for (int i = 0; i < kHeadingCount; ++i) {
        if (kHeadings[i] == heading) {
            return i;
        }
    }
    return kHeadingCount - 1;
}
}  // namespace

PoseHandler::PoseHandler(const Pose& pose) noexcept
    : point(pose.x, pose.y), heading(ToHeadingIndex(pose.heading))
{
}
void PoseHandler::Move() noexcept
{
    // 各朝向前进一格的向量，索引与朝向编码一致
    static const Point kOffsets[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    if (reverse) {
        point -= kOffsets[heading];
    } else {
        point += kOffsets[heading];
    }
}
void PoseHandler::TurnLeft() noexcept
{
    // 左转 = 编码 -1，倒车时方向取反
    heading = (heading + (reverse ? 1 : 3)) % kHeadingCount;
}
void PoseHandler::TurnRight() noexcept
{
    // 右转 = 编码 +1，倒车时方向取反
    heading = (heading + (reverse ? 3 : 1)) % kHeadingCount;
}
void PoseHandler::Fast() noexcept
{
    fast = !fast;
}
bool PoseHandler::IsFast() const noexcept
{
    return fast;
}
void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}
bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}
Pose PoseHandler::Query() const noexcept
{
    return Pose{point.GetX(), point.GetY(), kHeadings[heading]};
}
}  // namespace adas
