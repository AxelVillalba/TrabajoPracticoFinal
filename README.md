# TrabajoPracticoFinal
Repositorio dedicado al Trabajo Práctico Final de Programación de Bajo Nivel

# Sistema de Gestión de Estudiantes y Materias

## Integrantes
- Danel Alexis Villalba Villasboa
- Axel Villalba Villasboa
- Alexander Chavez

## Descripción
Sistema de gestión de estudiantes y materias desarrollado en lenguaje C. Permite administrar estudiantes, materias, inscripciones y exámenes mediante una interfaz de texto en consola.

## Consignas Implementadas

### ✅ CRUD de Estudiantes (ABM - Alta, Baja, Modificación)
- **Alta**: Crear nuevos estudiantes con nombre y edad
- **Baja**: Eliminar estudiantes del sistema
- **Modificación**: Actualizar datos de estudiantes existentes
- **Listado**: Visualizar todos los estudiantes registrados

### ✅ Búsquedas de Estudiantes
- **Búsqueda por nombre**: Búsqueda parcial que encuentra coincidencias en cualquier parte del nombre
- **Búsqueda por rango de edad**: Filtrar estudiantes dentro de un rango de edad especificado

### ✅ CRUD de Materias
- **Alta**: Crear nuevas materias con nombre y créditos
- **Baja**: Eliminar materias del sistema
- **Modificación**: Actualizar datos de materias existentes
- **Listado**: Visualizar todas las materias registradas

### ✅ Inscripciones
- Cada estudiante puede inscribirse en N materias (hasta 50)
- Validación para evitar inscripciones duplicadas
- Vista detallada de todas las materias de cada estudiante

### ✅ Exámenes
- Registrar calificaciones de exámenes para materias inscritas
- Validación de que el estudiante esté inscrito antes de rendir
- Escala de notas de 1 a 10
- Aprobación con nota >= 4

## Estructura de Datos

### Estructura de Datos Personalizada
El sistema utiliza **arreglos dinámicos** (dynamic arrays) como estructura de datos principal:

```c
typedef struct {
    Student *data;      // Arreglo dinámico de estudiantes
    int size;           // Cantidad actual de elementos
    int capacity;       // Capacidad total del arreglo
} StudentList;
```

#### Ventajas de esta implementación:
- **Acceso O(1)**: Acceso directo por índice
- **Búsqueda O(n)**: Recorrido lineal para búsquedas
- **Inserción O(1) amortizado**: Redimensionamiento automático cuando se llena
- **Memoria contigua**: Mejor rendimiento de caché

#### Escalabilidad:
- Capacidad inicial: 10 elementos
- Duplicación automática de capacidad cuando se llena
- Liberación automática de memoria

### Modelos de Datos

**Estudiante:**
```c
typedef struct {
    int id;                           // Identificador único
    char name[100];                   // Nombre del estudiante
    int age;                          // Edad
    Enrollment enrollments[50];       // Materias inscritas
    int enrollment_count;             // Cantidad de inscripciones
} Student;
```

**Materia:**
```c
typedef struct {
    int id;             // Identificador único
    char name[100];     // Nombre de la materia
    int credits;        // Créditos
} Course;
```

**Inscripción:**
```c
typedef struct {
    int course_id;          // ID de la materia
    float grade;            // Nota del examen
    int has_taken_exam;     // Si rindió el examen
} Enrollment;
```

## Funcionalidades del Sistema

### Menú Principal
El sistema presenta un menú interactivo con las siguientes opciones:

1. **Dar de alta estudiante**
2. **Modificar estudiante**
3. **Eliminar estudiante**
4. **Listar estudiantes**
5. **Buscar estudiante por nombre**
6. **Buscar estudiantes por rango de edad**
7. **Ver detalle de estudiante**
8. **Dar de alta materia**
9. **Modificar materia**
10. **Eliminar materia**
11. **Listar materias**
12. **Inscribir estudiante en materia**
13. **Rendir examen**
0. **Salir**

## Compilación y Ejecución

### Requisitos
- Compilador GCC
- Make

### Compilar
```bash
make
```

### Ejecutar
```bash
make run
```

### Limpiar archivos compilados
```bash
make clean
```

## Limitaciones y Consideraciones

### Almacenamiento
- **Limitación**: Los datos se almacenan en memoria durante la ejecución. Al cerrar el programa, todos los datos se pierden.
- **Impacto**: No hay persistencia de datos entre sesiones.
- **Solución futura**: Implementar guardado/carga desde archivos.

### Escalabilidad para Grandes Volúmenes

#### Rendimiento con muchos estudiantes:
- **Búsquedas lineales O(n)**: Con 10,000+ estudiantes, las búsquedas pueden volverse lentas
- **Solución propuesta**: Implementar índices con hash tables o árboles de búsqueda

#### Memoria:
- **Tamaño estimado por estudiante**: ~600 bytes (incluyendo inscripciones)
- **10,000 estudiantes**: ~6 MB
- **100,000 estudiantes**: ~60 MB
- **Conclusión**: El sistema puede manejar decenas de miles de registros sin problemas de memoria

#### Inscripciones:
- **Límite por estudiante**: 50 materias
- **Justificación**: Límite razonable para un estudiante universitario
- **Alternativa**: Usar lista enlazada para inscripciones ilimitadas

### Interfaz de Usuario
- **Limitación**: Interfaz de texto simple sin validaciones avanzadas
- **Experiencia**: Puede ser menos intuitiva para usuarios no técnicos
- **Mejora futura**: Implementar interfaz gráfica o web

## Puntos Extras Implementados

### ✅ Vista Detallada de Estudiante
- Muestra todas las materias inscritas
- Visualiza notas y estado de cada materia (Aprobado/Desaprobado/Sin rendir)

### ⚠️ Puntos NO Implementados (Opcionales)
Los siguientes puntos extras **no fueron implementados** en esta versión:
- **Paginado**: Para listas muy grandes
- **Selección de listado reducido**: Elegir de una lista filtrada
- **Validación de correlatividades**: Verificar materias previas aprobadas
- **Cálculo de promedios**: Promedio general de notas
- **Tests unitarios**: Suite de pruebas automatizadas

Estos puntos quedan como mejoras futuras para expandir la funcionalidad del sistema.

## Arquitectura del Código

### Archivos
- `main.c`: Programa principal y menú de usuario
- `student.h/c`: Implementación de estudiantes y operaciones
- `course.h/c`: Implementación de materias y operaciones
- `Makefile`: Configuración de compilación

### Principios de Diseño
- **Modularidad**: Separación de responsabilidades por archivos
- **Encapsulamiento**: Funciones específicas para cada operación
- **Gestión de memoria**: Liberación correcta de memoria dinámica
- **Validaciones**: Verificación de entradas del usuario

## Ejemplo de Uso

```
1. Crear algunas materias (opción 8)
2. Crear estudiantes (opción 1)
3. Inscribir estudiantes en materias (opción 12)
4. Registrar exámenes (opción 13)
5. Ver detalle de estudiante (opción 7)
6. Buscar por nombre o edad (opciones 5 y 6)
```

## Conclusión

El sistema cumple con todos los requisitos obligatorios del ejercicio:
- ✅ CRUD completo de estudiantes
- ✅ CRUD completo de materias
- ✅ Búsquedas por nombre y edad
- ✅ Inscripciones múltiples
- ✅ Sistema de exámenes
- ✅ Estructura de datos personalizada (arreglos dinámicos)
- ✅ Documentación de limitaciones

El sistema es funcional para casos de uso educativos y puede escalar a miles de registros. Las limitaciones identificadas están documentadas y se proponen soluciones para futuras mejoras.
