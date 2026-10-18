@echo off
setlocal
pushd "%~dp0.."

call script\build.bat
if errorlevel 1 (
    echo There was an error during the build process.
    popd
    exit /b 1
)

call script\run.bat
if errorlevel 1 (
    echo There was an error running the application.
    popd
    exit /b 1
)

popd
exit /b 0
