# Cambios y Mejoras - WiiU ViGEmBus Controller

## 🎨 Cambios Visuales

### Fondo Negro
- **Antes:** Fondo azul por defecto
- **Ahora:** Fondo negro (0x000000FF) para reducir fatiga visual y consumo de energía
- **Ubicación:** `source_custom/console.c` - variable `consoleColor`

### Nuevo Header ASCII
```
 __      _____ _  _   _   _  __   ___  ___       ___          
 \ \    / /_ _(_)| | | | | | \ \ / (_)/ __|___ _|   \ _  _ ___
  \ \/\/ / | || || |_| | | |  \ V / | | (_ / -_)| |) | || (_-<
   \_/\\_/ |___|_| \___/  |_|   \_/  |_|\\___|___|___/ \\_,_/__/
                                                    v1.0.0
```

### Créditos Integrados
Se agregó la función `PrintCredits()` que muestra:
- "Based on MiisendU by Crayon"
- Link a GitHub: https://github.com/Crayon2000/MiisendU-Wii-U
- Link a Wiki: https://wiiubrew.org/wiki/UsendMii

## ⚡ Mejoras de Usabilidad

### Sistema de Entrada de IP Mejorado

#### Antes (MiisendU):
- Solo D-Pad LEFT/RIGHT para cambiar dígito
- Solo D-Pad UP/DOWN para cambiar valor
- Velocidad de repetición: 14 frames
- Cambio de valor: ±1 únicamente

#### Ahora (WiiUViGEmBus):
- **L/R**: Saltar entre octetos completos (más rápido)
- **ZL/ZR**: Cambiar valor ±10 (para ajustes rápidos)
- **D-Pad UP/DOWN**: Cambiar valor ±1 (para ajustes finos)
- Velocidad de repetición: 8 frames (casi el doble de rápido)
- Navegación por octetos en lugar de dígitos individuales

**Ejemplo de uso:**
```
IP: 192.168.1.100
     ^^^
     Presiona R para saltar al siguiente octeto
     Presiona ZR para +10, ZL para -10
     Presiona UP/DOWN para ajustes finos
```

### Función de Ahorro de Energía

**Nueva característica:** Apagar/encender pantalla del GamePad

```cpp
// Detecta toque en pantalla táctil
if(vpad_data.tpNormal.touched && !last_touch_state) {
    screen_enabled = !screen_enabled;
    if(!screen_enabled) {
        OSScreenClearBufferEx(SCREEN_DRC, 0x00000000);
        OSScreenFlipBuffersEx(SCREEN_DRC);
    }
}
```

**Beneficios:**
- Ahorra batería del GamePad
- Reduce fatiga visual en sesiones largas
- Pantalla se apaga completamente (negro puro)
- Se reactiva con un simple toque

## 📝 Cambios en Textos

### Textos Eliminados
Se removieron todas las referencias a UsendMii:
- ❌ "Remember the program will not work without UsendMii running on your computer"
- ❌ "You can get UsendMii from http://wiiubrew.org/wiki/UsendMii"

### Textos Nuevos
- ✅ "Enter your PC IP address:"
- ✅ "L/R: Switch octet | ZL/ZR: +/-10 | UP/DOWN: +/-1"
- ✅ "Streaming controller data to PC..."
- ✅ "Touch GamePad screen to toggle display"
- ✅ "Touch screen to turn off display"
- ✅ Créditos al autor original integrados

## 🔧 Cambios Técnicos

### Estructura de Archivos
```
source/          → source_custom/
wuhb/            → wuhb_custom/
MiisendU-Wii-U   → WiiUViGEmBusController
```

### Configuración
```
Antes: sd:/wiiu/apps/MiisendU-Wii-U/settings.ini
Ahora: sd:/wiiu/apps/WiiUViGEmBusController/settings.ini
```

### Variables Nuevas
```cpp
static std::atomic<bool> screen_enabled{true};  // Control de pantalla
int8_t selected_octet = 0;                      // Navegación por octeto
bool last_touch_state = false;                  // Estado táctil anterior
```

### Optimizaciones
- Tiempo de espera reducido de 14 a 8 frames
- Navegación por octetos completos (4x más rápido)
- Incrementos de ±10 para ajustes rápidos

## 📊 Comparación de Velocidad

### Cambiar IP de 192.168.1.1 a 192.168.1.100

**MiisendU Original:**
1. Navegar al último dígito: ~20 pulsaciones
2. Incrementar de 1 a 100: ~99 pulsaciones
3. **Total: ~119 pulsaciones**

**WiiUViGEmBus:**
1. Presionar R 3 veces para llegar al último octeto: 3 pulsaciones
2. Presionar ZR 9 veces (+90): 9 pulsaciones
3. Presionar UP 9 veces (+9): 9 pulsaciones
4. **Total: ~21 pulsaciones** (5.6x más rápido)

## 🎮 Funcionalidad Mantenida

Todas las características originales se mantienen intactas:
- ✅ Soporte para Wii U GamePad
- ✅ Soporte para Wii Remotes (con extensiones)
- ✅ Soporte para Wii U Pro Controllers
- ✅ Soporte para adaptador de GameCube
- ✅ Transmisión UDP en formato JSON
- ✅ Guardado automático de configuración
- ✅ Detección automática de IP local
- ✅ Giroscopio y acelerómetro
- ✅ Pantalla táctil del GamePad
- ✅ Todos los botones y sticks analógicos

## 🔄 Compatibilidad

**100% compatible con el protocolo original de MiisendU**

Los datos JSON enviados son idénticos, por lo que cualquier software que funcione con MiisendU funcionará con WiiUViGEmBus Controller sin modificaciones.

## 📦 Archivos Modificados

1. **source_custom/main.cpp** - Lógica principal mejorada
2. **source_custom/console.c** - Fondo negro por defecto
3. **CMakeLists_WiiUViGEmBus.txt** - Nueva configuración de compilación
4. **README_WiiUViGEmBus.md** - Documentación actualizada

## 🎯 Archivos Sin Cambios

Estos archivos se mantienen idénticos al original:
- `vpad_to_json.cpp/h` - Conversión a JSON
- `udp.cpp/h` - Comunicación UDP
- `screen_utils.c/h` - Utilidades de dibujo

---

**Resumen:** Esta versión mantiene toda la funcionalidad original mientras mejora significativamente la experiencia de usuario con una interfaz más rápida, eficiente y cómoda para los ojos.
