@echo off

fc data.json right.json > nul

if errorlevel 1 (
    echo Files are different.
) else (
    echo Files are the same.
)