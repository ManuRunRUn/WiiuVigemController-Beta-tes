@echo off
chcp 65001 >nul
echo ╔══════════════════════════════════════════════════════════════╗
echo ║           Verificar Imágenes para Wii U                      ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

echo Verificando imágenes en wuhb_custom/...
echo.

set ERROR=0

REM Verificar que exista la carpeta
if not exist wuhb_custom (
    echo ✗ ERROR: La carpeta wuhb_custom/ no existe
    echo   Creando carpeta...
    mkdir wuhb_custom
    set ERROR=1
)

REM Verificar icon.png
if exist wuhb_custom\icon.png (
    echo ✓ icon.png encontrado
    for %%A in (wuhb_custom\icon.png) do (
        echo   Tamaño: %%~zA bytes
    )
    echo   Requerido: 128x128 píxeles, formato PNG
) else (
    echo ✗ ERROR: wuhb_custom\icon.png no encontrado
    set ERROR=1
)

echo.

REM Verificar tv-image.png
if exist wuhb_custom\tv-image.png (
    echo ✓ tv-image.png encontrado
    for %%A in (wuhb_custom\tv-image.png) do (
        echo   Tamaño: %%~zA bytes
    )
    echo   Requerido: 1280x720 píxeles, formato PNG
) else (
    echo ✗ ERROR: wuhb_custom\tv-image.png no encontrado
    set ERROR=1
)

echo.

REM Verificar drc-image.png
if exist wuhb_custom\drc-image.png (
    echo ✓ drc-image.png encontrado
    for %%A in (wuhb_custom\drc-image.png) do (
        echo   Tamaño: %%~zA bytes
    )
    echo   Requerido: 854x480 píxeles, formato PNG
) else (
    echo ✗ ERROR: wuhb_custom\drc-image.png no encontrado
    set ERROR=1
)

echo.
echo ════════════════════════════════════════════════════════════════

if %ERROR%==0 (
    echo.
    echo ✓ TODAS LAS IMÁGENES ESTÁN LISTAS
    echo.
    echo Las imágenes se usarán automáticamente al compilar.
    echo.
    echo Próximo paso:
    echo   1. Ejecuta: COMPILAR_WINDOWS.bat
    echo   2. El archivo .wuhb usará tus imágenes personalizadas
    echo.
) else (
    echo.
    echo ✗ FALTAN IMÁGENES
    echo.
    echo Asegúrate de tener estos 3 archivos en wuhb_custom/:
    echo   • icon.png (128x128 px)
    echo   • tv-image.png (1280x720 px)
    echo   • drc-image.png (854x480 px)
    echo.
)

echo ════════════════════════════════════════════════════════════════
echo.
echo INFORMACIÓN SOBRE LAS IMÁGENES:
echo.
echo icon.png:
echo   • Icono que aparece en el menú HOME de Wii U
echo   • Tamaño: 128x128 píxeles
echo   • Formato: PNG con transparencia (opcional)
echo.
echo tv-image.png:
echo   • Splash screen que aparece en la TV al iniciar
echo   • Tamaño: 1280x720 píxeles (720p)
echo   • Formato: PNG
echo.
echo drc-image.png:
echo   • Splash screen que aparece en el GamePad al iniciar
echo   • Tamaño: 854x480 píxeles
echo   • Formato: PNG
echo.
echo NOTA: CMake convierte automáticamente los PNG a formato TGA
echo       durante la compilación. No necesitas hacer nada más.
echo.
echo Presiona cualquier tecla para salir...
pause >nul
