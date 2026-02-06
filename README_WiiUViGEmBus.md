# WiiU ViGEmBus Controller

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Un cliente homebrew personalizado para Wii U que transmite los estados de los controles (GamePad, Wii U Pro Controllers, Wii Remotes y adaptador de GameCube) a tu PC vía UDP en formato JSON.

## 🎮 Características

- **Interfaz mejorada** con fondo negro para reducir fatiga visual
- **Entrada rápida de IP** con controles optimizados:
  - L/R: Cambiar entre octetos
  - ZL/ZR: Incrementar/decrementar por 10
  - UP/DOWN: Incrementar/decrementar por 1
- **Ahorro de energía**: Toca la pantalla del GamePad para apagar/encender el display
- **Soporte completo** para todos los controles de Wii U
- **Transmisión en tiempo real** de datos de controles

## 🎯 Controles

### Durante la configuración de IP:
- **L/R**: Cambiar octeto seleccionado
- **ZL/ZR**: Ajustar valor ±10
- **D-Pad UP/DOWN**: Ajustar valor ±1
- **A**: Confirmar y conectar
- **HOME (mantener)**: Salir

### Durante la transmisión:
- **Pantalla táctil**: Apagar/encender display del GamePad
- **HOME (mantener)**: Salir de la aplicación

## 📦 Compilación

### Prerequisitos:
- Paquetes del grupo wiiu-dev de devkitpro
- ppc-jansson de devkitpro

### Para compilar:
```bash
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build_custom
```

## 📝 Configuración

La aplicación guarda automáticamente la última IP utilizada en:
```
sd:/wiiu/apps/WiiUViGEmBusController/settings.ini
```

## 🙏 Créditos

Esta aplicación está basada en el excelente trabajo de **Crayon** con MiisendU Wii U.

**Proyecto original:**
- GitHub: [https://github.com/Crayon2000/MiisendU-Wii-U](https://github.com/Crayon2000/MiisendU-Wii-U)
- Wiki: [https://wiiubrew.org/wiki/UsendMii](https://wiiubrew.org/wiki/UsendMii)

Todos los agradecimientos y créditos van para el creador original. Esta es una versión personalizada con mejoras en la interfaz y usabilidad.

## 📄 Licencia

Este proyecto mantiene la misma licencia que el proyecto original.

## 🔧 Diferencias con MiisendU

- Interfaz con fondo negro
- Sistema de entrada de IP más rápido y eficiente
- Función de apagado de pantalla táctil para ahorro de energía
- Textos e interfaz personalizados
- Nombre y branding actualizados

## 🚀 Uso

1. Instala la aplicación en tu Wii U
2. Asegúrate de tener un servidor UDP escuchando en tu PC (puerto 4242 por defecto)
3. Ejecuta la aplicación desde el Homebrew Launcher
4. Ingresa la IP de tu PC usando los controles mejorados
5. ¡Disfruta del streaming de tus controles!

---

**Versión:** 1.0.0  
**Basado en:** MiisendU Wii U por Crayon
