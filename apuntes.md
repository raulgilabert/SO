# SO

[Web asignatura](http://docencia.ac.upc.edu/FIB/grau/SO)

## Profesora

Julita Corbalan
C6-203
julita.corbalan@upc.edu

## Exámenes

### Nota

max(.4 * Evaluación continua + .6 * EF, EF)

Evaluación continua = .5 * Parcial + .35 * Examen lab + .15 * Seguimiento lab

Seguimiento lab = 10% cuestionarios + 5% simulacros examen

Examen final = .5 * teoria + .5 * lab

---

## Introducción

La programación es como una cebolla, tiene capas.

(De más alto a más bajo nivel)

Framework -> (más capas) -> librería de C -> sistema operativo -> hardware

## Llamadas a sistema

Las llamadas a sistema permiten la comunicación entre la libreria de C y el
sistema operativo (aunque en EC se estudian las llamdas de sistema operativo a
hardware).

El sistema operativo enternamente define estructiras de datos para gestionar el
hardware y algoritmos para utilizarlo. En cambio, externamente, ofrece un
conjunto de funciones para acceder a su funcionalidad (o servicios) de gestión
de recursos.

El sistema operativo es clave para el funcionamiento del ordenador ya que es el
único programa que tiene los privilegios de acceso al hardware.

### Qué ofrece el sistema operativo?

- Nos ofrece un entorno usable, abstrayendo a los usuarios de las diferencias
entre los diferentes sistemas físicos.
- Un entorno seguro, proteje al hardware de accesos incorrectos y proteje a
  unos usuarios de intentos de acceso de otros a sus datos.
- Un entorno eficiente, el sistema operativo gestiona la compartición de
  recursos entre varios programas y usuarios, logrando que se aproveche bien
  los recuersos del comuputador.

El sistema operativo tiene un orden de funcionamiento:

1. Arranque (boot)
  - Carga el SO en memoria
  - Captura las interrupciones (Coloca en memoria las funciones a ejecutar en
  caso de interrupción y les da los privilegios necesarios)
  - Incializa el acceso al sistema
  - Ofrece el acceso al sistema
2. Uso
  - El SO tiene el entorno de ejecución que permite la ejecución de programas
    ya existente
  - También tiene el entorno de desarrollo que permite la generación de nuevos
    programas
3. Apagado (shutdown)
  - Se termina de forma controlada todos los procesos
  - Se apagan y/o sincronizan los dispositivos

### Llamadas al kernel

Solo en tres situaciones se ejecutan las llamadas al SO

1. Cuando una aplicación ejecuta una llamada a sistema
2. Cuando una aplicación provoca una excepción
3. Cuando un dispositivo provoca una interrupción

 El SO configura periódicamente la unterrupción del reloj para evitar perder el
 control y que un usuario pueda acaparar todos los recursos.

### Librería de sistema

(Ver apuntes)

### Requerimientos de llamadas a sistema

#### Desde el punto de vista del programador

- Tiene que ser como una llamada a función
- No se puede modificar el contexto
- Se tiene que guardar y restaurar los registros modificados

#### Desde el punto de vista del kernel

- Se ejecuta en modo privilegiado
- Se pasan los parámetros y se devuelven lso resultados entre modos de
  ejecución diferentes
- Las direcciones de memoria ocupadas por las llamdas a sistema tienen que
  poder ser variables para soportar diferentes versiones de kernel y diferentes
  SO

## Proceso

Un proceso es la representación en el SO de un programa en ejecución. Al
ponerlo en ejecución se le asigna memoria para el código, los datos y la pila
de este programa. Se inicializan los registros de la CPU, ofrece el acceso a
los dispositivos.

Para gestionar la información del proceso el sistema usa una estructura de
datos que se llama PCB (Process Control Block). Hay un PCB reservado para cada
proceso.

### PCB

Contiene la información necesaria para la gestión del proceso que depende del
sistema y de la máquina. Se puede clasificar en:

1. Espacio de direcciones
    Descripción de las regiones del proceso: código, datos, pila, etc.

    - Rangos resercados
    - Permisos
    - Información de las optimizaciones seguras o especulativas
    - Qué hacer si hay accesos de memoria incorrectos
2. Contexto de ejecución
    - Software
	
	PID, información para la planificación, información del uso de
	dispositivos, estadísticas, etc.
    - Hardware
        
	Tabla de páginas, program counter, etc.

### Concurrencia

La concurrencia es la capacidad de ejecutar varios procesos de forma
simultánea.

Si realmente hay varios procesos a la vez es paralelismo (arquitectura
multiprocesador o milti-core). En cambio, si se trata de un paralelismo virtual
creado por el SO a través de la compartición de recursos se tratará realmente
de concurrencia.

Varios procesos son secuenciales si independientemente de la arquitectura que
tiene el ordenador se ejecuta uno detrás de otro.

### Hilos de ejecución

Cuando se crea un proceso este tiene por defecto un thread de la CPU asignado.
Este se trata de la instancia/flujo de ejecución del proceso y es la mínima
unidad de planificaciñon del SO. Cada parte que se puede ejecutar de forma
independiente se asigna a un thread distinto.

Distintos thread no pueden tener la misma pila por lo que consume un poco más
de memoria. Lo que comparten entre ellos si son del mismo proceso es únicamente
el PCB.

---

### Estados de un proceso

- run
  
    El proceso tiene una CPU asignada y se encuentra en ejecución
- ready
    
    El proceso está preparado para ejecutarse pero está a la espera de CPU



