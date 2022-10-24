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

### Propiedades de un proceso

Toda la información de un proceso se guarda en el PCB. Estas se agrupan en
tres:

- Identidad

    Define quién es el proceso y a qué recursos puede acceder
- Entorno

    Parámetros que se le dan al ejecutbale y sus variables de entorno
- Contexto
    
    Toda la información que define el estado del proceso y los recursos que usa
    y ha usado durante la ejecución

#### Identidad

La identidad se define por el PID que es un identificador único para el proceso
y que se usa como identificador dentro del sistema. Además de eso hay varias
credenciales, como puden ser el identificador del usuario que lo ha ejecutado y
el de los grupos a los que pertenece, determinando los derechos del proceso a
acceder a los recursos del sistena y los ficheros.

## Servicios básicos para gestionar los procesos

Los servicios ofrecen a los usuarios un conjunto de funciones para gestionar
los procesos:

- Crear/planificar/eliminar procesos
- Bloquear/desbloquear procesos
- Proporcionar mecanismos de sincronización
- Proporcionar mecanismos de comunicación

    Por ej.: Memoria compartida, dispositivos especiales, gestión de signals,
    etc.

### Creación de procesos

Cuando un proceso crea a otro este se considera su hijo. A su vez, el hijo
puede seguir creando procesos, de forma que se crea un árbol de procesos.

El SO debe decidir a la hora de crear los hijos lo referente a los recursos, la
planificación y el espacio de direcciones.

En Linux el padre y el hijo se ejecutan de forma concurrente, el hijo es un
duplicado del padre pero cada uno tiene su propia memoria física, además tiene
el mismo contexto de ejecución al momento de la creación (los registros valen
lo mismo).

Las llamadas a sistema son funciones que se peude ejecutar en C al llamar a
algunas librerías.

#### fork

Crea un nuevo proceso que es un clon del padre.

#### exec (execlp)

Reemplaza el espacio de direcciones del actual proceso con un nuevo programa
pero manteniendo los identificadores del primero.

Esta llamada a sistema en C tiene diversos parámetros:

El primero es el programa a ejecutar, el segundo es argv[0], y los siguientes
el resto de argv terminando con `NULL` para marcar que se han acabado los
argumentos.

#### exit

Termina el proceso que lo llama.

La llamada tiene como único parámetro un número que por convención es 0 si no
hay errores o cualquier número amyor si lo hay, siendo definido el significado
por el programador en la documentación.

#### wait/waitpid

Espera a que el proceso hijo acabe, de forma que el proceso actual se bloquea
hasta ese momento.

La llamada `waitpid` tiene varios parámetros, siendo el primero el PID del
programa que se está esperando, el segundo un puntero en el que se va a
guardar el valor que se ha devuelto en la llamada exit del programa y el
tercero opciones.

#### getpid

Devuelve el PID del proceso.

#### getppid

Devuelve el PID del padre.

### Creación de procesos usando fork

Se mantiene la información escrita en el apartado de creación de procesos pero
el valor de retorno de la llamada a `fork` es distinto:

- El padre recibe el PID del hijo
- El hijo recibe un 0

El hijo hereda del proceso padre su espacio de direcciones lógico (la memoria
física es nueva y contiene una copia de la del padre), la tabla de programación
de signals, los dispositivos virtuales, las credenciales del usuario y el
grupo y las variables de entorno. En cambio, no hereda el PID y PPID, los
contadores internos de utilización y las alarmas y signals pendientes al ser
estas propias del proceso.

### Teminación de la ejecución/espera a la terminación

EL proceso puede acabar su ejecución de forma voluntaria (llamada a sistema
`exit`) o involuntariamente (signals). Cuando este quiere acabar su
finalización de forma voluntaria se liberan sus recursos y se liberan las
estructuras del kernel reservadas para él con llamada `exit`.

Si quieremos sincronizar el padre con la finalización del proceso hijo se puede
usar la llamada a sistema `waitpid`, de forma que se bloquea el proceso hasta
que el hijo termina:

- `waitpid(-1, NULL, 0)` -> Espera a un hijo cualquiera
- `waitpid(pid_hijo, NULL, 0)` -> Espera al hijo que tiene el PID pid_hijo

En un posible programa como este:

```C
pid_t h1 = -1, h2 = -1;

h1 = fork();

if (h1 > 0) {
    h2 = fork();
}

if (h2 == 0)
    execlp("sleep", "sleep", "1000", NULL);

waitpid(h2, NULL, 0);
if (h2)
    exit(0);
else
    exit(1);
```

De esta manera, en caso de que sea el padre, se hará un nuevo fork y después de
este si se está en el hijo se ejecutará el `execlp`. El padre de este estará
esperando hasta el final de su ejecución, ya que en el hijo no esperará al ser
el PID 0. Al final de esto, si se trata del padre tras la espera executará
`exit` con un 0 y si es el hijo con un 1.

### Comunicación entre procesos

#### Signals

Enviar evento (kill)

Esperar evento:
- Espera activa (no tiene llamada a sistema)
- Espera bloqueante

Se pueden además bloquear eventos, de forma que se quedan pendientes; ignorar
eventos, "similar" a no recibirlos y configurar la recepción de los eventos.

También se pueden programar signals de forma que se envía SIGALRM después de un
tiempo x en segundos.

##### Modificar signals


```C
sigset_t m; // Declaración de m como signal
sigemptyset(&m) // -> 0 todo
sigaddset(&m, SIGALRM) // 1 en sigalrm
sigprocmask(SIG_BLOCK, &m, NULL) // bloquear SIGALRM
sigprocmask(SIG_SET, &m, NULL) // Todos los signals bloqueados menos SIGALRM
sigprocmask(SIG_UNBLOCK, &m, NULL) // desbloquear SIGALRM
```
 Para operar con más de un signal a la vez con las operaciones se puede usar
 `sigaddset()` con la misma máscara de signals.

##### Espera (sincronización)

###### Opción 1

Espera activa: se consulta en bucle el valor de una varuable que se modifica al
recibir un evento, siendo la variable gloabl y el evento una función
`sigaction()`.

###### Opción 2

En caso de saber el tiempo de necesidad de espera se usa `sigsuspend`

```C
sigmeptyset(&mask);
sigaddset(&mask, SIGALRM); // Se asigna SIGALRM
sigprocmask(SIG_SETMASK, &mask, NULL);
sigaction(SIGALRM, &trat, NULL);

...

sigfillset(&mask); // Se ponen todos a 1
sigdelset(&mask, SIGALRM); // SIGALRM se pone a 0
alarm(2); // 2 segundos de espera

sigsuspend(&mask);

```
Los signals con bit en 1 no se considera temporalmente bloqueados. Los que
están con un 0 son los que pueden desbloquear.

En caso de hacer un cambio de espera blocante a activa además de meter el while
en el lugar del sigsuspend hay que hacer un sigprocmask para colocar los
signals que pueden reactivar el programa.

### Gestión interna

Para gestionar los procesos se usan ciertas estructuras de datos para
representar sus propiedad es y recursos (PCB) y para representat y gestionar
thread (esto depende del SO).

Además de eso hay diversas estructuras de gestión que organizan los PCB en
función de su estado o necesidades de organización del sistema. Generalmente
son listas o colas pero pueden incluir estructuras más complejas como tablas de
hash, árboles, etc.

Hay que tener en cuenta la eficiencia de estas estructuras, de forma que hay
que ver si son rápidas las inserciones o eliminaciones, las búsquedas, los
índices de búsqueda, PID, usuario, etc.

Además se tiene que tener en cuenta la escalabilidad de las estructuras, es
decir, saber cuántos procesos se pueden tener activos en el sistema y la
memoria necesaria para estas estructuras.

También se necesitarán algoritmos de planificación que indiquen como gestionar
las estructuras y también mecanismo que apliquen las decisiones que toma el
planificador.

#### Estructuras de organización

El SO organiza los PCB de los procesos en estructuras de gestión: vectores,
listas, colas, tablas de hash, árboles, etc. en función de las necesidades del
SO.

Los procesos que van en un mismo orden suelen estar organizados en colas o
listas que permiten mantener un orden:

- Cola de procesos: Todos los procesos creados en el sistema
- Cola de procesos: Listos para ejecutarse (ready): procesos a la espera de CPU
- Colas de dispositivos: Procesos a la espera de datos de algún dispositivo de
  E/S

El SO mueve los procesos de una estructura a otra dependiendo de lo que sea
necesario, por ejemplo: cuando temina una operación de E/S el proceso se mueve
de la cola del dispositivo a la cola de ready.

