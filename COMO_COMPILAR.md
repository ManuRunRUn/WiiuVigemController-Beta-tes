# 🔨 Cómo Compilar WiiUViGEmBusController

## ¿Qué es un archivo WUHB?

**WUHB** (Wii U Homebrew Bundle) es el formato de aplicación que la Wii U puede ejecutar desde el Homebrew Launcher. Es como un `.exe` en Windows o `.app` en macOS.

El archivo `.wuhb` contiene:
- El código ejecutable (`.rpx`)
- Los iconos de la aplicación
- Las imágenes de splash screen
- Los metadatos (nombre, autor, versión)

---

## 🎯 Proceso de Compilación

### El archivo `COMPILAR_WINDOWS.bat` hace TODO automáticamente:

```
Código C++ (.cpp)
       ↓
   [Compilador]
       ↓
Código Objeto (.o)
       ↓
    [Linker]
       ↓
Ejecutable (.elf)
       ↓
  [Conversión]
       ↓
Formato Wii U (.rpx)
       ↓
[Empaquetado con iconos]
       ↓
Aplicación Final (.wuhb) ✅
```

---

## 🚀 Compilación Rápida (Windows)

### Opción 1: Usar el Script Automático (RECOMENDADO)

```cmd
COMPILAR_WINDOWS.bat
```

¡Eso es todo! El script hace:
1. ✅ Crea la carpeta de iconos
2. ✅ Copia los iconos necesarios
3. ✅ Configura CMake
4. ✅ Descarga dependencias (rapidjson, inih)
5. ✅ Compila el código C++
6. ✅ Genera el archivo `.rpx`
7. ✅ Empaqueta todo en `.wuhb`

**Resultado:** `build_custom\WiiUViGEmBusController.wuhb`

---

### Opción 2: Compilación Manual

Si prefieres hacerlo paso a paso:

```cmd
# 1. Crear iconos
mkdir wuhb_custom
copy wuhb\*.png wuhb_custom\

# 2. Configurar CMake
move CMakeLists.txt CMakeLists_original.txt
copy CMakeLists_WiiUViGEmBus.txt CMakeLists.txt

# 3. Configurar proyecto
C:\devkitPro\portlibs\wiiu\bin\powerpc-eabi-cmake.exe -B build_custom

# 4. Compilar
cmake --build build_custom

# 5. El archivo WUHB estará en:
# build_custom\WiiUViGEmBusController.wuhb
```

---

## 🐧 Compilación en Linux/macOS

```bash
# 1. Crear iconos
mkdir wuhb_custom
cp wuhb/*.png wuhb_custom/

# 2. Configurar CMake
mv CMakeLists.txt CMakeLists_original.txt
cp CMakeLists_WiiUViGEmBus.txt CMakeLists.txt

# 3. Configurar proyecto
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom

# 4. Compilar
cmake --build build_custom

# 5. El archivo WUHB estará en:
# build_custom/WiiUViGEmBusController.wuhb
```

---

## 📋 Requisitos Previos

### Windows

1. **devkitPro** instalado en `C:\devkitPro`
   - Descarga: https://github.com/devkitPro/installer/releases

2. **Paquetes necesarios** (instalar con pacman):
   ```cmd
   pacman -S wiiu-dev ppc-jansson
   ```

3. **Conexión a internet** (para descargar dependencias)

### Linux/macOS

1. **devkitPro** instalado en `/opt/devkitpro`
   - Guía: https://devkitpro.org/wiki/Getting_Started

2. **Paquetes necesarios**:
   ```bash
   sudo dkp-pacman -S wiiu-dev ppc-jansson
   ```

3. **Conexión a internet** (para descargar dependencias)

---

## 🔍 Verificar la Instalación

### Verificar devkitPro (Windows):
```cmd
C:\devkitPro\portlibs\wiiu\bin\powerpc-eabi-cmake.exe --version
```

### Verificar devkitPro (Linux/macOS):
```bash
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake --version
```

Si ves la versión de CMake, ¡está instalado correctamente!

---

## 📦 Estructura del Archivo WUHB

Cuando compilas, CMake crea esta estructura:

```
WiiUViGEmBusController.wuhb
├── code/
│   └── WiiUViGEmBusController.rpx  (ejecutable)
├── meta/
│   ├── meta.xml                     (metadatos)
│   ├── iconTex.tga                  (icono convertido)
│   ├── bootTvTex.tga                (splash TV)
│   └── bootDrcTex.tga               (splash GamePad)
└── content/
    └── (archivos adicionales si los hay)
```

---

## 🎨 Personalizar Iconos

### Antes de compilar, puedes crear tus propios iconos:

**Requisitos:**
- `wuhb_custom/icon.png` - 128x128 píxeles, PNG
- `wuhb_custom/tv-image.png` - 1280x720 píxeles, PNG
- `wuhb_custom/drc-image.png` - 854x480 píxeles, PNG

**Herramientas recomendadas:**
- GIMP (gratis)
- Photoshop
- Paint.NET
- Cualquier editor de imágenes

---

## ⚙️ Configuración Avanzada

### Cambiar el Nombre de la App

Edita `CMakeLists_WiiUViGEmBus.txt`:

```cmake
wut_create_wuhb(WiiUViGEmBusController
  CONTENT
  NAME "Tu Nombre Aquí"          # ← Cambia esto
  SHORTNAME "TuNombre"            # ← Y esto
  AUTHOR "Tu Nombre"              # ← Y esto
  ICON "wuhb_custom/icon.png"
  TVSPLASH "wuhb_custom/tv-image.png"
  DRCSPLASH "wuhb_custom/drc-image.png"
)
```

### Cambiar la Versión

Edita `source_custom/main.cpp`, busca:

```cpp
OSScreenPutFontEx(bufferNum, 0, 4, "                                                    v1.0.0");
```

Cambia `v1.0.0` por tu versión.

---

## 🐛 Solución de Problemas

### Error: "powerpc-eabi-cmake not found"

**Solución:**
```cmd
# Verifica la ruta de instalación
dir C:\devkitPro\portlibs\wiiu\bin\

# Si está en otra ubicación, edita COMPILAR_WINDOWS.bat
# y cambia la ruta en la línea del cmake
```

### Error: "Cannot find rapidjson"

**Solución:**
- Asegúrate de tener conexión a internet
- CMake descarga automáticamente las dependencias
- Si falla, intenta de nuevo

### Error: "wiiu-dev not found"

**Solución:**
```cmd
# Instala los paquetes necesarios
pacman -S wiiu-dev ppc-jansson
```

### Error: "No such file or directory: wuhb_custom/icon.png"

**Solución:**
```cmd
# Crea la carpeta y copia los iconos
mkdir wuhb_custom
copy wuhb\*.png wuhb_custom\
```

### Compilación muy lenta

**Causas comunes:**
- Primera compilación (descarga dependencias)
- Antivirus escaneando archivos
- Disco duro lento

**Solución:**
- Espera pacientemente en la primera compilación
- Agrega excepción en el antivirus para la carpeta del proyecto
- Las siguientes compilaciones serán más rápidas

---

## 📊 Tiempos de Compilación

| Etapa | Primera Vez | Siguientes |
|-------|-------------|------------|
| Configuración CMake | 1-2 min | 5-10 seg |
| Descarga dependencias | 1-3 min | 0 seg |
| Compilación | 2-5 min | 30-60 seg |
| **TOTAL** | **4-10 min** | **1-2 min** |

---

## ✅ Verificar el Archivo WUHB

### Tamaño esperado:
- Aproximadamente 200-500 KB

### Verificar que existe:
```cmd
dir build_custom\WiiUViGEmBusController.wuhb
```

### Probar en Wii U:
1. Copia a `sd:\wiiu\apps\WiiUViGEmBusController.wuhb`
2. Inserta la SD en tu Wii U
3. Ejecuta Homebrew Launcher
4. Busca "WiiU ViGEmBus Controller"
5. ¡Ejecuta y disfruta!

---

## 🔄 Recompilar Después de Cambios

Si modificas el código:

```cmd
# Solo necesitas recompilar
cmake --build build_custom

# No necesitas volver a configurar CMake
```

Si modificas CMakeLists.txt:

```cmd
# Necesitas reconfigurar
C:\devkitPro\portlibs\wiiu\bin\powerpc-eabi-cmake.exe -B build_custom
cmake --build build_custom
```

---

## 📝 Notas Importantes

1. **Primera compilación**: Tarda más porque descarga dependencias
2. **Conexión a internet**: Necesaria solo la primera vez
3. **Espacio en disco**: Necesitas ~500 MB libres
4. **Iconos**: Deben estar en `wuhb_custom/` antes de compilar
5. **Cambios**: Después de modificar código, solo recompila

---

## 🎉 ¡Listo!

Ahora tienes tu archivo `.wuhb` listo para instalar en tu Wii U.

**Siguiente paso:** Lee `SUBIR_A_GITHUB.md` para publicar tu proyecto.

---

## 📞 Ayuda Adicional

- **devkitPro Wiki**: https://devkitpro.org/wiki/Getting_Started
- **WiiUBrew**: https://wiiubrew.org/
- **Proyecto Original**: https://github.com/Crayon2000/MiisendU-Wii-U

---

**¡Feliz compilación!** 🔨✨
