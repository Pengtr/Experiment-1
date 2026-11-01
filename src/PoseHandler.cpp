#include "PoseHandler.hpp"
namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept
    : pose(pose)
{
}
void PoseHandler::Move() noexcept
{
    const int step = reverse ? -1 : 1;
    if (pose.heading == 'E') {
        pose.x += step;
    } else if (pose.heading == 'W') {
        pose.x -= step;
    } else if (pose.heading == 'N') {
        pose.y += step;
    } else if (pose.heading == 'S') {
        pose.y -= step;
    }
}
void PoseHandler::TurnLeft() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = reverse ? 'S' : 'N';
    } else if (pose.heading == 'N') {
        pose.heading = reverse ? 'E' : 'W';
    } else if (pose.heading == 'W') {
        pose.heading = reverse ? 'N' : 'S';
    } else if (pose.heading == 'S') {
        pose.heading = reverse ? 'W' : 'E';
    }
}
void PoseHandler::TurnRight() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = reverse ? 'N' : 'S';
    } else if (pose.heading == 'S') {
        pose.heading = reverse ? 'E' : 'W';
    } else if (pose.heading == 'W') {
        pose.heading = reverse ? 'S' : 'N';
    } else if (pose.heading == 'N') {
        pose.heading = reverse ? 'W' : 'E';
    }
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
    return pose;
}
}  // namespace adas
