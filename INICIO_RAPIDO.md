# 🚀 Inicio Rápido - WiiUViGEmBusController

## ⚡ Compilar en 5 Pasos

### 1️⃣ Crear carpeta de iconos
```bash
mkdir wuhb_custom
cp wuhb/icon.png wuhb_custom/
cp wuhb/tv-image.png wuhb_custom/
cp wuhb/drc-image.png wuhb_custom/
```

### 2️⃣ Usar el CMakeLists personalizado
```bash
mv CMakeLists.txt CMakeLists_original.txt
mv CMakeLists_WiiUViGEmBus.txt CMakeLists.txt
```

### 3️⃣ Compilar
```bash
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom
cmake --build build_custom
```

### 4️⃣ Copiar a SD
```bash
cp build_custom/WiiUViGEmBusController.wuhb /ruta/a/tu/sd/wiiu/apps/
```

### 5️⃣ ¡Ejecutar en tu Wii U!

---

## 🎮 Controles Mejorados

### Configuración de IP (¡5.6x más rápido!)
```
L/R     → Cambiar octeto (192 → 168 → 1 → 100)
ZL/ZR   → Ajustar ±10 (rápido)
UP/DOWN → Ajustar ±1 (fino)
A       → Conectar
HOME    → Salir (mantener)
```

### Durante uso
```
TOUCH   → Apagar/encender pantalla (ahorra batería)
HOME    → Salir (mantener)
```

---

## 📝 Ejemplo de Uso

**Cambiar IP de 192.168.1.1 a 192.168.1.100:**

1. Presiona **R** 3 veces → Llegas al último octeto (100)
2. Presiona **ZR** 9 veces → Sumas 90 (de 1 a 91)
3. Presiona **UP** 9 veces → Sumas 9 (de 91 a 100)
4. Presiona **A** → ¡Conectado!

**Total: ~21 pulsaciones** vs 119 del original 🚀

---

## ✨ Características Nuevas

- ✅ **Fondo negro** - No quema los ojos
- ✅ **Entrada IP ultra rápida** - 5.6x más rápido
- ✅ **Apagar pantalla táctil** - Ahorra batería
- ✅ **Créditos integrados** - Respeto al autor original
- ✅ **100% compatible** - Funciona con cualquier servidor MiisendU

---

## 🔧 Solución Rápida de Problemas

### ❌ Error: "powerpc-eabi-cmake not found"
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
```

### ❌ Error: "Cannot find rapidjson"
- Asegúrate de tener internet, CMake lo descarga automáticamente

### ❌ Los iconos no aparecen
```bash
# Verifica que existan
ls -la wuhb_custom/
# Deben ser PNG válidos de 128x128, 1280x720, 854x480
```

### ❌ No compila
```bash
# Instala dependencias
sudo dkp-pacman -S wiiu-dev ppc-jansson
```

---

## 📦 Archivos Importantes

```
source_custom/main.cpp          ← Código principal mejorado
CMakeLists_WiiUViGEmBus.txt    ← Configuración de compilación
wuhb_custom/                    ← Iconos (crear esta carpeta)
README_WiiUViGEmBus.md         ← Documentación completa
BUILD_INSTRUCTIONS.md          ← Guía detallada
CHANGES.md                     ← Lista de cambios
```

---

## 🎯 Checklist Antes de Compilar

- [ ] devkitPro instalado
- [ ] Carpeta `wuhb_custom/` creada
- [ ] 3 iconos PNG copiados a `wuhb_custom/`
- [ ] CMakeLists.txt renombrado
- [ ] Internet disponible (para descargar dependencias)

---

## 🌟 Diferencias Visuales

### Pantalla de Configuración IP
```
Antes (MiisendU):
┌─────────────────────────────────────┐
│ MiisendU Wii U                      │ (Fondo azul)
│                                     │
│ Please insert your computer's IP    │
│ (use the DPAD to edit)              │
│     vvv                             │
│ 192.168.001.100                     │
│                                     │
│ Press 'A' to confirm                │
└─────────────────────────────────────┘

Ahora (WiiUViGEmBus):
┌─────────────────────────────────────┐
│ WiiU ViGEmBus Controller v1.0.0     │ (Fondo NEGRO)
│                                     │
│ Enter your PC IP address:           │
│ L/R: Switch | ZL/ZR: ±10 | UP/DOWN: ±1
│ vvv                                 │
│ 192.168.001.100                     │
│                                     │
│ Press 'A' to connect                │
│ Based on MiisendU by Crayon         │
└─────────────────────────────────────┘
```

---

## 💾 Configuración Guardada

La app guarda automáticamente tu IP en:
```
sd:/wiiu/apps/WiiUViGEmBusController/settings.ini
```

Contenido:
```ini
[server]
ipaddress=192.168.1.100
port=4242
```

---

## 🔗 Enlaces Útiles

**Proyecto Original:**
- GitHub: https://github.com/Crayon2000/MiisendU-Wii-U
- Wiki: https://wiiubrew.org/wiki/UsendMii

**Documentación Completa:**
- `README_WiiUViGEmBus.md` - Información general
- `BUILD_INSTRUCTIONS.md` - Guía detallada de compilación
- `CHANGES.md` - Lista completa de cambios
- `RESUMEN_PROYECTO.md` - Vista general del proyecto

---

## 🎉 ¡Listo!

Tu versión personalizada está lista para:
1. ✅ Compilar
2. ✅ Instalar en Wii U
3. ✅ Usar con fondo negro
4. ✅ Configurar IP rápidamente
5. ✅ Ahorrar batería con pantalla táctil

**¡Disfruta tu WiiUViGEmBusController!** 🎮

---

**Tip Pro:** Mantén presionado ZL o ZR para cambiar valores rápidamente. ¡Es mucho más rápido que el original!
