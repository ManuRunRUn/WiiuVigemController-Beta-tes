@echo off
echo Normalizando line endings...
echo.

REM Guardar cambios actuales
git add .gitattributes
git add .github/workflows/ci.yml
git add CMakeLists.txt
git add CAMBIOS_BUILD.md

echo Archivos principales agregados al staging
echo.

REM Mostrar estado
git status

echo.
echo Listo para hacer commit.
echo Ejecuta: git commit -m "Fix build configuration and normalize line endings"
echo Luego: git push
pause
