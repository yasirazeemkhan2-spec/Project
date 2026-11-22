@echo off
title Cyber Bot Launcher
cd /d "%~dp0\frontend"
echo ====================================================
echo             STARTING CYBER BOT GUI...
echo ====================================================
echo.
echo Launching server at http://localhost:3000
start http://localhost:3000
node server.js
pause
