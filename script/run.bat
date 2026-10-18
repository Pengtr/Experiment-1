@echo off
setlocal
pushd "%~dp0.."

if not exist build\tests\training_main.exe (
    echo training_main.exe not exists!
    popd
    exit /b 1
)

pushd build\tests
.\training_main.exe
set "RC=%errorlevel%"
popd

popd
exit /b %RC%
