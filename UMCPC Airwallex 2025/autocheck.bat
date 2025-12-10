@echo off
:loop
datamaker > r
g < r > w1
gb < r > w2
fc w1 w2
if not errorlevel 1 goto loop
pause