# 🎨 Guía de Imágenes para WiiUViGEmBusController

## 📁 Ubicación de las Imágenes

Todas las imágenes deben estar en la carpeta `wuhb_custom/`:

```
wuhb_custom/
├── icon.png         (128x128 px)
├── tv-image.png     (1280x720 px)
└── drc-image.png    (854x480 px)
```

---

## 🖼️ Especificaciones de Cada Imagen

### 1. icon.png - Icono del Menú HOME

**Dónde aparece:**
- En el menú HOME de la Wii U
- En el Homebrew Launcher

**Especificaciones:**
- **Tamaño:** 128x128 píxeles
- **Formato:** PNG
- **Transparencia:** Opcional (recomendado)
- **Colores:** RGB o RGBA

**Recomendaciones:**
- Usa colores vibrantes para que destaque
- Evita detalles muy pequeños (se verá pequeño en el menú)
- Puedes usar transparencia para bordes redondeados

---

### 2. tv-image.png - Splash Screen de TV

**Dónde aparece:**
- En la pantalla de TV cuando inicias la aplicación
- Se muestra durante 2-3 segundos

**Especificaciones:**
- **Tamaño:** 1280x720 píxeles (720p)
- **Formato:** PNG
- **Aspecto:** 16:9
- **Colores:** RGB

**Recomendaciones:**
- Usa el logo de tu aplicación
- Agrega el nombre "WiiU ViGEmBus Controller"
- Puedes incluir créditos o versión
- Fondo negro recomendado (consistente con la app)

---

### 3. drc-image.png - Splash Screen del GamePad

**Dónde aparece:**
- En la pantalla del GamePad cuando inicias la aplicación
- Se muestra durante 2-3 segundos

**Especificaciones:**
- **Tamaño:** 854x480 píxeles
- **Formato:** PNG
- **Aspecto:** 16:9 (aproximado)
- **Colores:** RGB

**Recomendaciones:**
- Similar al splash de TV pero adaptado al tamaño
- Texto más grande (pantalla más pequeña)
- Fondo negro recomendado

---

## ✅ Verificar tus Imágenes

Ejecuta este comando para verificar que tus imágenes están correctas:

```cmd
VERIFICAR_IMAGENES.bat
```

El script verificará:
- ✓ Que existan los 3 archivos
- ✓ Que estén en la carpeta correcta
- ✓ El tamaño de cada archivo

---

## 🔄 Proceso de Conversión Automática

Cuando compiles con `COMPILAR_WINDOWS.bat`, CMake automáticamente:

1. **Lee** los archivos PNG de `wuhb_custom/`
2. **Convierte** los PNG a formato TGA (formato que usa Wii U)
3. **Empaqueta** las imágenes en el archivo `.wuhb`

**No necesitas hacer nada manualmente.** Todo es automático.

---

## 🎨 Herramientas Recomendadas para Editar

### Gratis:
- **GIMP** - https://www.gimp.org/
- **Paint.NET** - https://www.getpaint.net/
- **Photopea** (online) - https://www.photopea.com/

### De Pago:
- **Photoshop**
- **Affinity Photo**

---

## 📐 Plantillas de Ejemplo

### Crear icon.png (128x128):

```
1. Abre tu editor de imágenes
2. Crea una nueva imagen: 128x128 píxeles
3. Diseña tu icono (logo, símbolo, etc.)
4. Guarda como PNG: wuhb_custom/icon.png
```

### Crear tv-image.png (1280x720):

```
1. Abre tu editor de imágenes
2. Crea una nueva imagen: 1280x720 píxeles
3. Fondo negro recomendado
4. Agrega tu logo centrado
5. Agrega texto: "WiiU ViGEmBus Controller v1.0.0"
6. Opcional: Agrega "Based on MiisendU by Crayon"
7. Guarda como PNG: wuhb_custom/tv-image.png
```

### Crear drc-image.png (854x480):

```
1. Abre tu editor de imágenes
2. Crea una nueva imagen: 854x480 píxeles
3. Usa el mismo diseño que tv-image.png
4. Ajusta el tamaño del texto (más grande)
5. Guarda como PNG: wuhb_custom/drc-image.png
```

---

## 🖼️ Ejemplo de Diseño Simple

### Para icon.png:
```
┌────────────────┐
│                │
│   [LOGO/       │
│    SÍMBOLO]    │
│                │
│   ViGEmBus     │
│                │
└────────────────┘
```

### Para tv-image.png y drc-image.png:
```
┌─────────────────────────────────────────┐
│                                         │
│                                         │
│           [LOGO GRANDE]                 │
│                                         │
│     WiiU ViGEmBus Controller            │
│              v1.0.0                     │
│                                         │
│    Based on MiisendU by Crayon          │
│                                         │
└─────────────────────────────────────────┘
```

---

## ⚠️ Errores Comunes

### Error: "Cannot find icon.png"
**Solución:**
- Verifica que el archivo esté en `wuhb_custom/icon.png`
- Verifica que el nombre sea exactamente `icon.png` (minúsculas)

### Error: "Invalid PNG format"
**Solución:**
- Asegúrate de guardar como PNG (no JPG, BMP, etc.)
- Usa formato RGB o RGBA
- Evita formatos PNG exóticos

### Las imágenes se ven pixeladas
**Solución:**
- Verifica que las dimensiones sean exactas
- No uses imágenes más pequeñas y las escales
- Usa imágenes de alta calidad

---

## 🔍 Verificar Resultados

Después de compilar:

1. El archivo `.wuhb` contendrá tus imágenes
2. Instala en tu Wii U
3. Verifica:
   - ✓ El icono en el menú HOME
   - ✓ El splash screen en TV al iniciar
   - ✓ El splash screen en GamePad al iniciar

---

## 💡 Consejos de Diseño

### Para el Icono (128x128):
- ✓ Usa colores contrastantes
- ✓ Diseño simple y reconocible
- ✓ Evita texto pequeño
- ✓ Prueba cómo se ve pequeño

### Para los Splash Screens:
- ✓ Fondo negro (consistente con la app)
- ✓ Logo centrado y grande
- ✓ Texto legible desde lejos (TV)
- ✓ Incluye versión y créditos
- ✓ Mantén el diseño limpio

---

## 📝 Checklist

Antes de compilar, verifica:

- [ ] `wuhb_custom/icon.png` existe (128x128 px)
- [ ] `wuhb_custom/tv-image.png` existe (1280x720 px)
- [ ] `wuhb_custom/drc-image.png` existe (854x480 px)
- [ ] Todas las imágenes son formato PNG
- [ ] Las dimensiones son exactas
- [ ] El diseño se ve bien

---

## 🚀 Compilar con tus Imágenes

Una vez que tengas las 3 imágenes listas:

```cmd
# Verificar imágenes
VERIFICAR_IMAGENES.bat

# Compilar (usa automáticamente tus imágenes)
COMPILAR_WINDOWS.bat
```

El archivo `.wuhb` generado incluirá tus imágenes personalizadas.

---

## 🎨 Recursos Adicionales

### Inspiración:
- Mira otros homebrews de Wii U para ideas
- Busca "wii u homebrew icons" en Google Images

### Colores Recomendados:
- Fondo: Negro (#000000)
- Texto: Blanco (#FFFFFF)
- Acento: Azul (#0078D7) o Verde (#00FF00)

### Fuentes Recomendadas:
- Roboto
- Open Sans
- Montserrat
- Arial Bold

---

## ✅ Resultado Final

Después de compilar con tus imágenes personalizadas:

```
build_custom/WiiUViGEmBusController.wuhb
├── Contiene tu icon.png
├── Contiene tu tv-image.png
└── Contiene tu drc-image.png
```

¡Listo para instalar en tu Wii U con tus imágenes personalizadas! 🎉

---

**Siguiente paso:** Ejecuta `COMPILAR_WINDOWS.bat` para generar el `.wuhb` con tus imágenes.
