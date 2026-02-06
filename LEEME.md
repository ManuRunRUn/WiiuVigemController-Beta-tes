# WiiU ViGEmBus Controller 🎮

> Versión personalizada y mejorada de MiisendU Wii U con interfaz optimizada y controles más rápidos

[![Basado en MiisendU](https://img.shields.io/badge/Basado%20en-MiisendU-blue)](https://github.com/Crayon2000/MiisendU-Wii-U)
[![Versión](https://img.shields.io/badge/Versión-1.0.0-green)]()
[![Licencia](https://img.shields.io/badge/Licencia-MIT-yellow)]()

---

## 📖 ¿Qué es esto?

**WiiUViGEmBusController** es una versión personalizada del excelente proyecto **MiisendU** creado por **Crayon**. Esta aplicación homebrew para Wii U transmite los estados de todos tus controles (GamePad, Pro Controllers, Wii Remotes, adaptador de GameCube) a tu PC mediante UDP en formato JSON.

### 🆕 ¿Qué tiene de nuevo?

Esta versión incluye mejoras significativas en la experiencia de usuario:

- 🎨 **Fondo negro** para reducir fatiga visual
- ⚡ **Entrada de IP 5.6x más rápida** con controles optimizados
- 🔋 **Ahorro de energía** - Apaga la pantalla del GamePad tocándola
- 📝 **Interfaz mejorada** con textos más claros
- 🙏 **Créditos integrados** al autor original

---

## 🎯 Características Principales

### Controles Soportados
- ✅ Wii U GamePad (con giroscopio, acelerómetro y pantalla táctil)
- ✅ Wii U Pro Controllers
- ✅ Wii Remotes (con o sin extensiones)
- ✅ Nunchuk
- ✅ Classic Controller
- ✅ Adaptador USB de GameCube (hasta 4 controles)

### Datos Transmitidos
- Todos los botones
- Sticks analógicos
- Gatillos analógicos
- Giroscopio y acelerómetro
- Pantalla táctil del GamePad
- Posición del Wii Remote

---

## 🚀 Inicio Rápido

### Instalación
1. Descarga `WiiUViGEmBusController.wuhb`
2. Copia a `sd:/wiiu/apps/`
3. Ejecuta desde Homebrew Launcher

### Primer Uso
1. La app te pedirá la IP de tu PC
2. Usa los **controles mejorados** para ingresarla rápidamente:
   - **L/R**: Cambiar entre octetos (192 → 168 → 1 → 100)
   - **ZL/ZR**: Ajustar ±10 (para cambios rápidos)
   - **D-Pad UP/DOWN**: Ajustar ±1 (para ajustes finos)
3. Presiona **A** para conectar
4. ¡Listo! Tus controles se transmiten a tu PC

### Durante el Uso
- **Toca la pantalla** del GamePad para apagarla/encenderla (ahorra batería)
- **Mantén HOME** para salir de la aplicación

---

## ⚡ Comparación de Velocidad

### Ejemplo: Cambiar IP de 192.168.1.1 a 192.168.1.100

**MiisendU Original:**
- Navegar dígito por dígito: ~20 pulsaciones
- Incrementar de 1 a 100: ~99 pulsaciones
- **Total: ~119 pulsaciones** ⏱️

**WiiUViGEmBus (Esta versión):**
- Presionar R 3 veces (llegar al último octeto): 3 pulsaciones
- Presionar ZR 9 veces (+90): 9 pulsaciones
- Presionar UP 9 veces (+9): 9 pulsaciones
- **Total: ~21 pulsaciones** ⚡ **(5.6x más rápido!)**

---

## 🎮 Guía de Controles Completa

### Pantalla de Configuración de IP

| Botón | Acción |
|-------|--------|
| **L** | Ir al octeto anterior (← 192.168.1.100) |
| **R** | Ir al octeto siguiente (192.168.1.100 →) |
| **ZL** | Restar 10 al octeto actual |
| **ZR** | Sumar 10 al octeto actual |
| **D-Pad UP** | Sumar 1 al octeto actual |
| **D-Pad DOWN** | Restar 1 al octeto actual |
| **A** | Confirmar y conectar |
| **HOME** (mantener) | Salir de la aplicación |

### Durante la Transmisión

| Acción | Resultado |
|--------|-----------|
| **Tocar pantalla** | Apagar/encender display del GamePad |
| **HOME** (mantener) | Salir de la aplicación |

---

## 🔧 Compilación

### Requisitos
- devkitPro con soporte para Wii U
- Paquetes: `wiiu-dev`, `ppc-jansson`

### Pasos

```bash
# 1. Crear carpeta de iconos
mkdir wuhb_custom
cp wuhb/*.png wuhb_custom/

# 2. Configurar CMake
mv CMakeLists.txt CMakeLists_original.txt
mv CMakeLists_WiiUViGEmBus.txt CMakeLists.txt

# 3. Compilar
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom
cmake --build build_custom

# 4. El archivo .wuhb estará en:
# build_custom/WiiUViGEmBusController.wuhb
```

Para más detalles, consulta `BUILD_INSTRUCTIONS.md`

---

## 📝 Configuración

La aplicación guarda automáticamente tu configuración en:
```
sd:/wiiu/apps/WiiUViGEmBusController/settings.ini
```

Formato del archivo:
```ini
[server]
ipaddress=192.168.1.100
port=4242
```

Puedes editar este archivo manualmente si lo prefieres.

---

## 🎨 Capturas de Pantalla

### Pantalla de Configuración
```
┌──────────────────────────────────────────────────────┐
│  __      _____ _  _   _   _  __   ___  ___       ___ │
│  \ \    / /_ _(_)| | | | | | \ \ / (_)/ __|___ _|   \│
│   \ \/\/ / | || || |_| | | |  \ V / | | (_ / -_)| |) │
│    \_/\_/ |___|_| \___/  |_|   \_/  |_|\\___|___|___/│
│                                              v1.0.0   │
│                                                       │
│  Enter your PC IP address:                           │
│  L/R: Switch octet | ZL/ZR: +/-10 | UP/DOWN: +/-1    │
│      vvv                                              │
│  192.168.001.100                                      │
│                                                       │
│  Press 'A' to connect                                │
│  Hold HOME to exit                                   │
│                                                       │
│  Based on MiisendU by Crayon                         │
│  https://github.com/Crayon2000/MiisendU-Wii-U        │
└──────────────────────────────────────────────────────┘
```

### Pantalla de Transmisión
```
┌──────────────────────────────────────────────────────┐
│  WiiU ViGEmBus Controller v1.0.0                     │
│                                                       │
│  Connected to 192.168.1.100:4242                     │
│                                                       │
│  Streaming controller data to PC...                  │
│                                                       │
│  Touch screen to turn off display                    │
│                                                       │
│  Hold HOME to exit                                   │
│                                                       │
│  Based on MiisendU by Crayon                         │
└──────────────────────────────────────────────────────┘
```

---

## 🔌 Formato de Datos (JSON)

La aplicación envía datos en formato JSON compatible con MiisendU:

```json
{
  "wiiUGamePad": {
    "hold": 0,
    "tpTouch": 0,
    "lStickX": 0.0,
    "lStickY": 0.0,
    "gyroX": 0.0,
    "gyroY": 0.0,
    ...
  },
  "wiiRemotes": [...],
  "wiiUProControllers": [...],
  "gameCubeControllers": [...]
}
```

**100% compatible** con cualquier software que funcione con MiisendU.

---

## 🙏 Créditos y Agradecimientos

### Autor Original
Este proyecto está basado en **MiisendU Wii U** creado por **Crayon**.

- **GitHub:** https://github.com/Crayon2000/MiisendU-Wii-U
- **Wiki:** https://wiiubrew.org/wiki/UsendMii

**Todos los créditos y agradecimientos van para Crayon** por crear el proyecto original y hacerlo open source.

### Esta Versión
**WiiUViGEmBusController** es una versión personalizada que mantiene toda la funcionalidad original mientras agrega mejoras en la interfaz y usabilidad.

Cambios realizados:
- Interfaz con fondo negro
- Sistema de entrada de IP optimizado
- Función de ahorro de energía
- Textos personalizados
- Documentación en español

---

## 📄 Licencia

Este proyecto mantiene la misma licencia que el proyecto original (MiisendU).

---

## 📚 Documentación Adicional

- **INICIO_RAPIDO.md** - Guía rápida para empezar
- **README_WiiUViGEmBus.md** - README en inglés
- **BUILD_INSTRUCTIONS.md** - Instrucciones detalladas de compilación
- **CHANGES.md** - Lista completa de cambios y mejoras
- **RESUMEN_PROYECTO.md** - Vista general del proyecto

---

## ❓ Preguntas Frecuentes

### ¿Es compatible con el servidor original de MiisendU?
**Sí**, 100% compatible. El formato de datos JSON es idéntico.

### ¿Puedo usar mis iconos personalizados?
**Sí**, coloca tus PNG en la carpeta `wuhb_custom/` antes de compilar.

### ¿Funciona con todos los controles?
**Sí**, soporta GamePad, Pro Controllers, Wii Remotes (con extensiones) y adaptador de GameCube.

### ¿Cómo ahorro batería del GamePad?
Toca la pantalla táctil para apagar el display. Toca de nuevo para encenderlo.

### ¿Puedo cambiar el puerto UDP?
Sí, edita `source_custom/main.cpp` y busca `uint16_t port{4242};`

### ¿Dónde se guarda la configuración?
En `sd:/wiiu/apps/WiiUViGEmBusController/settings.ini`

---

## 🐛 Reporte de Problemas

Si encuentras algún problema:
1. Revisa `BUILD_INSTRUCTIONS.md`
2. Verifica que devkitPro esté instalado correctamente
3. Asegúrate de tener los iconos en `wuhb_custom/`
4. Consulta el proyecto original para problemas de compilación base

---

## 🌟 Características Destacadas

| Característica | MiisendU | WiiUViGEmBus |
|----------------|----------|--------------|
| Fondo de pantalla | Azul | **Negro** ⭐ |
| Velocidad entrada IP | Normal | **5.6x más rápido** ⭐ |
| Ahorro de energía | No | **Sí** ⭐ |
| Navegación IP | Por dígito | **Por octeto** ⭐ |
| Incrementos | ±1 | **±1, ±10** ⭐ |
| Créditos | En README | **Integrados** ⭐ |
| Compatibilidad | 100% | **100%** ✅ |
| Soporte controles | Completo | **Completo** ✅ |

---

## 💡 Consejos y Trucos

1. **Entrada rápida de IP:**
   - Usa L/R para saltar entre octetos
   - Usa ZL/ZR para cambios grandes (±10)
   - Usa D-Pad para ajustes finos (±1)

2. **Ahorro de batería:**
   - Apaga la pantalla del GamePad cuando no la necesites
   - El fondo negro consume menos energía que colores brillantes

3. **Configuración persistente:**
   - Tu IP se guarda automáticamente
   - No necesitas ingresarla cada vez

4. **Compatibilidad:**
   - Funciona con cualquier servidor que acepte el formato MiisendU
   - No necesitas software especial en la PC

---

## 🎯 Roadmap Futuro (Ideas)

- [ ] Selector de puerto UDP desde la interfaz
- [ ] Múltiples perfiles de IP guardados
- [ ] Indicador visual de conexión
- [ ] Estadísticas de paquetes enviados
- [ ] Modo de bajo consumo configurable
- [ ] Temas de color personalizables

---

## 🤝 Contribuciones

Este es un proyecto personalizado basado en MiisendU. Si quieres contribuir:
1. Respeta siempre los créditos al autor original (Crayon)
2. Mantén la compatibilidad con el formato JSON original
3. Documenta tus cambios claramente

---

## 📞 Contacto y Soporte

Para problemas con la funcionalidad base, consulta el proyecto original:
- https://github.com/Crayon2000/MiisendU-Wii-U

Para problemas específicos de esta versión personalizada, revisa la documentación incluida.

---

## ✨ Agradecimientos Especiales

- **Crayon** - Por crear MiisendU y hacerlo open source
- **Comunidad de WiiUBrew** - Por mantener vivo el homebrew de Wii U
- **devkitPro** - Por las herramientas de desarrollo

---

**¡Disfruta tu WiiUViGEmBusController!** 🎮✨

*Versión 1.0.0 - Basado en MiisendU v1.4.0*
