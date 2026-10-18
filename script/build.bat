@echo off
setlocal
pushd "%~dp0.."

if not exist build (
    md build
)

cmake -S . -B build -G Ninja
if errorlevel 1 (
    popd
    exit /b 1
)

cmake --build build
if errorlevel 1 (
    popd
    exit /b 1
)

popd
exit /b 0
