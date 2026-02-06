# Instrucciones de Compilación - WiiU ViGEmBus Controller

## Pasos para compilar tu versión personalizada

### 1. Preparar el entorno

Asegúrate de tener instalado devkitPro con las herramientas para Wii U:
```bash
# En Linux/macOS
sudo dkp-pacman -S wiiu-dev ppc-jansson

# En Windows (desde MSYS2)
pacman -S wiiu-dev ppc-jansson
```

### 2. Renombrar el CMakeLists.txt

Primero, respalda el CMakeLists.txt original y usa el personalizado:
```bash
# Respaldar el original
mv CMakeLists.txt CMakeLists_original.txt

# Usar el personalizado
mv CMakeLists_WiiUViGEmBus.txt CMakeLists.txt
```

### 3. Crear los iconos personalizados

Necesitas crear tus propios iconos en la carpeta `wuhb_custom/`:
```bash
mkdir -p wuhb_custom
```

Crea o copia estos archivos:
- `wuhb_custom/icon.png` (128x128 píxeles)
- `wuhb_custom/tv-image.png` (1280x720 píxeles)
- `wuhb_custom/drc-image.png` (854x480 píxeles)

**Nota:** Por ahora puedes copiar los originales y modificarlos después:
```bash
cp wuhb/icon.png wuhb_custom/
cp wuhb/tv-image.png wuhb_custom/
cp wuhb/drc-image.png wuhb_custom/
```

### 4. Compilar el proyecto

```bash
# Configurar el proyecto
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom

# Compilar
cmake --build build_custom
```

### 5. Encontrar tu archivo compilado

El archivo `.wuhb` estará en:
```
build_custom/WiiUViGEmBusController.wuhb
```

### 6. Instalar en tu Wii U

Copia el archivo a tu tarjeta SD:
```
sd:/wiiu/apps/WiiUViGEmBusController.wuhb
```

## Solución de problemas

### Error: "Cannot find rapidjson"
Asegúrate de tener conexión a internet durante la compilación, CMake descargará las dependencias automáticamente.

### Error: "powerpc-eabi-cmake not found"
Verifica que devkitPro esté instalado correctamente y que la variable de entorno `DEVKITPRO` esté configurada:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
```

### Los iconos no aparecen
Asegúrate de que los archivos PNG en `wuhb_custom/` tengan las dimensiones correctas y estén en formato PNG válido.

## Personalización adicional

### Cambiar el puerto UDP
Edita `source_custom/main.cpp` y busca:
```cpp
uint16_t port{4242};
```

### Cambiar la IP por defecto
Edita `source_custom/main.cpp` y busca:
```cpp
uint8_t IP[4] = {192, 168, 1, 100};
```

### Modificar los textos
Todos los textos están en `source_custom/main.cpp` en las funciones `PrintHeader()` y `PrintCredits()`.

## Estructura del proyecto

```
.
├── source_custom/          # Código fuente personalizado
│   ├── main.cpp           # Archivo principal con mejoras
│   ├── console.c/h        # Manejo de consola
│   ├── udp.cpp/h          # Comunicación UDP
│   ├── vpad_to_json.cpp/h # Conversión de datos a JSON
│   └── screen_utils.c/h   # Utilidades de pantalla
├── wuhb_custom/           # Recursos gráficos personalizados
│   ├── icon.png
│   ├── tv-image.png
│   └── drc-image.png
├── CMakeLists.txt         # Configuración de compilación
└── README_WiiUViGEmBus.md # Documentación
```

## Próximos pasos

1. Crea tus propios iconos personalizados
2. Prueba la aplicación en tu Wii U
3. Ajusta los textos y colores según tus preferencias
4. Comparte tu versión con la comunidad (dando crédito al autor original)

---

¡Disfruta tu versión personalizada de WiiU ViGEmBus Controller!
