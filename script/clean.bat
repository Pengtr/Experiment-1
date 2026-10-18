@echo off
setlocal
pushd "%~dp0.."

if exist build (
    cmake --build build --target clean
)

popd
exit /b 0
