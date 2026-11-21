#pragma once 
#include <string> 
namespace adas
{
    enum class CarType {
        Normal = 0,
        SportsCar,
        Bus,
    };
    struct Pose {
        int x;
        int y;
        char heading;
    };
    class Executor
    {
    public:
        //Caller should delete *executor when it is no longer needed.
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}, const CarType& carType = CarType::Normal) noexcept;

    public:
        Executor(void) = default;
        virtual ~Executor(void) = default;
        Executor(const Executor&) = delete;
        Executor& operator=(const Executor&) = delete;

    public:
        virtual void Execute(const std::string& command) noexcept = 0;
        virtual Pose Query(void) const noexcept = 0;
    };
}
// namespace adas