# Acta de Reunión — Seguimiento consultoría La Jobiteka

**Fecha:** 24 de julio de 2026
**Duración:** ~43 minutos
**Modalidad:** Videollamada
**Asistentes:** Sergio Monsalve · Juan Guillermo Ballesteros Montoya (cliente, La Jobiteka)

---

## Contexto

Reunión de seguimiento a la del [1 de julio](2026-07-01-reunion-cliente.md). Se revisó el checklist de adecuación de infraestructura enviado tras esa reunión, se hizo una demo en vivo de `bichongos.store` y de los avances de la cápsula IoT propia, y surgió una línea de negocio nueva: acopio de pequeños productores.

---

## Avances de infraestructura (sede de Guarne)

> Nota de contexto: la obra que se describe a continuación es la **sede física de Bichongos en Guarne** (el invernadero 7×14 m, Épica 1 de `BACKLOG.md`), no un sitio aparte de La Jobiteka. Juan (La Jobiteka, socio de Songo Sorhongo) está ejecutando la construcción como parte del acuerdo de consultoría.

Juan arrancó ~1 semana atrasado frente al cronograma inicial, pero aceleró mucho:

- Mapa eléctrico completo de todos los cuartos ya hecho; cielos falsos definidos (no se dejan los techos originales)
- Se demolieron los perfiles internos de los cuartos que no servían, además de todo lo que había que quitar antes de tirar tubería
- Tubería eléctrica **y de agua** se está corriendo por piso
- Al momento de la llamada: se están levantando muros laterales y los muros de las ventanas grandes; se espera que mañana quede la primera habitación revocada
- **Meta acordada: semana del 3 de agosto de 2026** con al menos **dos habitaciones terminadas** para empezar a trabajar in-house (no la adecuación completa del invernadero, pero sí dos cuartos operativos)

Sergio repasó el checklist de adecuación punto por punto (techos, pisos, paredes, puertas, ventanas, agua, energía) — todo calificado como "en proceso, casi listo" para esos días. Mesas de trabajo y báscula ya los tiene el cliente; recipientes y estantería quedan pendientes de conseguir. La chipeadora ya está en el sitio.

---

## Decisiones técnicas tomadas en la llamada

- **Fogón: se mantiene leña** (se descartó gas y el de aceite que podía prestar Alejo). Razón del cliente: quemar leña ayuda a vaciar el cuarto grande que necesitan liberar — la transición a otra fuente de energía se hará más adelante, no ahora.
- **Pasteurización/esterilización por vapor, no por inmersión** — más eficiente (el sustrato sumergido pesa mucho más y necesita zona de escurrido; en vapor el tubular ya sale con la humedad correcta). Se necesita:
  - Una parrilla tipo "parrilla de arepas" elevada ~40 cm dentro de las canecas
  - Un atril metálico/de hierro para sostener las canecas sobre el fuego
- **Tanques de 200 L** tipo barril industrial con tapa y cierre hermético metálico — se consiguen en el centro de Medellín (zona San Juan / Alpujarra / Guayabal). Bichongos ofreció compartir el contacto del proveedor y comprarlos si hace falta por logística.
- **Termómetro con sonda**: comprar uno que se pueda integrar al sistema de automatización (no uno genérico de pistola), para poder controlar temperatura de pasteurización desde el sistema IoT más adelante.
- **Compra de electrónica (~$1.000.000 COP)** quedó pausada por decisión de Juan hasta que la infraestructura esté más avanzada, para retomarla con foco.

---

## Semilla / spawn (lado Bichongos)

- Se está pidiendo semilla con **dos proveedores** (uno nuevo, de respaldo, para no depender de una sola fuente)
- Tiempo de entrega ≈ 20 días (se hace sobre pedido)
- El pedido se está agrupando para La Jobiteka y para el proyecto propio de Bichongos (Zongo/Songo), que también necesita reposición
- Hay ~1 kg de semilla actual sin destapar, pero insuficiente para las pruebas planeadas y ya con tiempo de estar guardada (sigue siendo viable pero no es la óptima recién salida de laboratorio) — las pruebas se van a dimensionar según esa cantidad mientras llega el nuevo pedido

---

## Demo en vivo — bichongos.store y cápsula IoT

- **bichongos.store**: landing pública ya levantada, conectada a un WhatsApp de contacto; explica el problema/solución de la cápsula y las 4 líneas de negocio (restaurantes, tiendas, etc.). Tendrá panel administrativo con login para Juan, Daniela, Lore y Freddy con documentación y videos de capacitación.
- **Cápsula IoT (avance propio de Bichongos, mostrado como referencia)**: control de luces ya funcionando desde el celular vía el controlador de la cápsula. Falta conseguir humidificadores (por pedir).
- **Hito de la semana**: se conectó un **agente de IA a una línea de WhatsApp** que toma pedidos de forma autónoma — pide los datos, la dirección, cotiza y registra el pedido en base de datos. Sergio lo propone como diferenciador de marketing frente a clientes y distribuidores ("tecnología de punta, agentes de IA").
- Se está considerando comprar una **impresora 3D** para mejorar la estética de la cápsula.

---

## Estrategia de contenido y marca

- Propuesta: crear el Instagram de la marca (con Daniela) y contar el proceso de construcción, incluyendo los momentos difíciles — genera más conexión que solo mostrar lo que sale bien. Ya existe material grabado desde el inicio de la obra.
- Material de referencia para generar contenido:
  - *Growing Gourmet and Medicinal Mushrooms* — Paul Stamets (referencia técnica principal)
  - Libro de hongos curativos, con recetas, propiedades, beneficios e historia — fuente directa para posts
  - Libro de agricultura restaurativa — conecta con el ángulo social/ambiental del proyecto
- Se acordó mantener una carpeta compartida de material audiovisual de construcción/desarrollo entre ambas partes.

---

## Certificación en micología

Se decidió esperar antes de buscar un curso formal: primero Bichongos transmite su conocimiento y recursos de forma orgánica; en paralelo se investiga una posible alianza con un programa universitario que le dé más credibilidad de cara a clientes.

---

## Idea estratégica nueva: modelo de acopio

Juan tiene una reunión próxima con un **gran distribuidor de Medellín** (sector hotelero/restaurantero) y necesita poder responder sobre capacidad de producción disponible.

- Hoy ese dato no existe calculado con precisión. Estimado cualitativo de Sergio: capacidad **pequeña** de orellana es estable; **mediana** puede tener fallos ocasionales; **grande** es riesgoso todavía — recomienda no comprometerse con un cliente grande de entrada y escalar gradualmente.
- De esa conversación surgió una idea que ambos validaron con fuerza: que Bichongos/La Jobiteka opere como **acopiador de pequeños productores de hongos**, similar al modelo de "Casa Orellana" o al de la Federación de Fungicultores de Café — comprar producción a pequeños cultivadores a un precio fijo garantizado, agregar volumen, y negociar con distribuidores grandes desde ahí. No depende de que Bichongos cultive todo el volumen, y genera ingreso y relación comercial mientras se escala producción propia.
- Conecta con la visión de largo plazo de "educar comunidades" para que cualquier persona tenga un cultivo en casa.
- Sergio ya tiene contacto con la Federación de cultivadores de Antioquia y datos de mercado de orellana rastreados desde hace ~3 años; contacto reciente también con cultivadores de Agaricus (Setas de Cuivá), donde hay una brecha de escala frente a Bichongos.
- Se define como una línea de negocio a desarrollar, no solo una respuesta puntual para la reunión de Juan.

---

## Acuerdos y compromisos

| # | Acuerdo | Responsable |
|---|---------|------------|
| 1 | Compartir fotos y contacto del proveedor de barriles de 200 L en el centro de Medellín | Sergio |
| 2 | Revisar el checklist de adecuación y marcar qué se tiene, qué falta y qué se necesita ayuda de Bichongos para comprar | Juan |
| 3 | Conseguir/mandar hacer la parrilla de vapor (40 cm) y el atril de hierro para las canecas | Juan (con apoyo de diseño de Bichongos) |
| 4 | Calcular un estimado real de capacidad de producción por especie (llamadas a productores aliados), para la reunión de Juan con el distribuidor de Medellín | Sergio |
| 5 | Retomar la compra de electrónica (~$1M COP) una vez la infraestructura esté más avanzada | Juan decide el momento |
| 6 | Avanzar compras del checklist antes de la próxima reunión | Juan |
| 7 | Escribir antes de ir a la finca para coordinar qué llevar/repetir de pedidos anteriores | Sergio → Juan |

---

## Pendientes de definir

- [ ] Estimado real de capacidad de producción actual por especie (orellana como prioridad)
- [ ] Definir el modelo de acopio como línea de negocio formal (precio garantizado a pequeños productores, criterios de entrada, logística)
- [ ] Confirmar si la meta del 3 de agosto (dos habitaciones terminadas) se cumplió
- [ ] Fecha para retomar la compra de electrónica pausada
- [ ] Sigue sin resolverse el Modelo A/B de la relación comercial (ver [acta del 1-jul](2026-07-01-reunion-cliente.md))

---

## Próximos pasos inmediatos

1. **Próxima reunión: miércoles 29 de julio de 2026**, con avances de compras del checklist ya hechos
2. Sergio envía contacto de proveedor de barriles
3. Juan avanza construcción de las dos primeras habitaciones (meta: semana del 3 de agosto)
4. Sergio arma el estimado de capacidad de producción antes de la reunión de Juan con el distribuidor

---

*Acta generada a partir de transcripción automática de la reunión · Bichongos / La Jobiteka · 2026-07-24*
