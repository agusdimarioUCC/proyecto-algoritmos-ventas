# Proyecto: Sistema de Análisis de Ventas para Empresa de Envíos en Sudamérica

---

## Objetivo

El alumno debe aplicar estructuras de datos y algoritmos aprendidos en la asignatura para desarrollar un sistema de
análisis de ventas de una empresa de envíos que opera en Sudamérica. El sistema procesará datos a partir de un archivo
CSV, permitiendo consultar, modificar y analizar ventas, priorizando la eficiencia y claridad del código.

---

## Modalidad

- Proyecto grupal. Cantidad de integrantes según lo anunciado en clase.
- Codificación en C++ utilizando estructuras propias o librerías brindadas por el docente.
- Presentación y defensa oral de 15 minutos.
- Entrega por GitHub con código completamente funcional y comentado.

---

## Enunciado General

Crear un programa en C++ que procese el archivo CSV `ventas_sudamerica.csv`. Este archivo contiene registros de ventas
realizadas por una empresa de logística. El programa deberá ofrecer, mediante un menú interactivo, funcionalidades que
permitan consultar y analizar los datos de manera dinámica.

---

## Requerimientos del Cliente

### 1. Eficiencia

- Se debe contabilizar el tiempo de ejecución y cantidad de condicionales (`if`) utilizados por cada proceso principal.
- Mostrar al usuario el nombre del proceso, el algoritmo y/o la estructura utilizada.

### 2. Librerías

- Se permite el uso de las librerías propias de la empresa o cualquier librería estándar.
- Si se usan librerías externas, deben ser explicadas y defendidas durante la presentación.

### 3. Menú

- Debe guiar al usuario con texto contextual y mostrar resultados claros.  
  **Ejemplo correcto:**  
  *La ciudad con mayor monto total de ventas en Perú es Lima, con $35000.*

### 4. Carga de datos desde archivo CSV

El archivo contiene las siguientes columnas:

`ID_Venta, Fecha, País, Ciudad, Cliente, Producto, Categoría, Cantidad, Precio_Unitario, Monto_Total, Medio_Envio, Estado_Envio`

### 5. Procesamiento de datos durante lectura del archivo CSV

Durante la lectura deben calcularse los siguientes resultados principales:

- El top 5 de ciudades con mayor monto de ventas por país.
- Monto total vendido por producto, discriminado por país.
- Promedio de ventas por categoría en cada país.
- Medio de envío más utilizado por país.
- Medio de envío más utilizado por categoría.
- Día con mayor cantidad de ventas (por monto de dinero) en toda la base de datos.
- Estado de envío más frecuente por país.
- Producto más vendido en cantidad total (unidades).
- Producto menos vendido en cantidad total.

### 6. Modificación de datos y reprocesamiento automático

El programa debe permitir:

- **Agregar una venta** (guiando al usuario paso a paso para ingresar todos los campos).
- **Eliminar una venta** (el usuario ingresará un país o una ciudad y el programa filtrará mostrando lo seleccionado).
- **Modificar una venta** (selección por ID de venta; permitir modificar cualquier campo).

Cada vez que se haga una modificación (agregar, eliminar o modificar), se deben volver a procesar automáticamente los
puntos del apartado 5.

### 7. Consultas dinámicas solicitadas por el usuario

- Listado de ventas realizadas en una ciudad específica.
- Listado de ventas realizadas en un rango de fechas por país.
- Comparación entre dos países:  
  a. Monto total de ventas  
  b. Productos más vendidos  
  c. Medio de envío más usado
- Comparación entre dos productos discriminado por todos los países:  
  a. Cantidad total vendida  
  b. Monto total
- Buscar productos vendidos en promedio por debajo de un monto total especificado por el usuario (umbral) y por país.  
  **Ejemplo:**  
  *Productos con monto promedio mayor a $500 por unidad vendidos en Brasil: Laptop, Celular.*
- Buscar productos vendidos en promedio por encima de un monto total especificado por el usuario (umbral).  
  **Ejemplo:**  
  *Productos con monto promedio menor a $250 por unidad vendidos en Brasil: mouse, teclado.*

---

## Notas Finales

- Mostrar los resultados con claridad y texto explicativo.
- Documentar el código y utilizar buenas prácticas.
- La evaluación contempla: funcionamiento, eficiencia, documentación, defensa oral, código y comprensión de algoritmos y
  estructuras (ventajas y desventajas), incluso si no fueron utilizadas.

