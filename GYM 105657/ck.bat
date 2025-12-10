@echo off
:loop
gen>r
l<r>w
lb<r>w2
fc w w2
if not errorlevel 1 goto loop
pause