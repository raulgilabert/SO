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

El sistema operativo internamente define estructuras de datos para gestionar el
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

### Requerimientos de llamadas a sistema

#### Desde el punto de vista del programador

- Tiene que ser como una llamada a función
- No se puede modificar el contexto
- Se tiene que guardar y restaurar los registros modificados

#### Desde el punto de vista del kernel

- Se ejecuta en modo privilegiado
- Se pasan los parámetros y se devuelven los resultados entre modos de
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

    - Rangos reservados
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

- blocked
    
    Está a la espera de un evento que reciba por signal o con un acción de E/S

- zombie
    El proceso ha terminado pero está a la espera de que el padre lo compruebe
    por si este requiere usar algo de la información que genera el fin de
    ejecución

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

Crea un nuevo proceso que es un clon del padre que se ejecuta de forma
concurrente a este.

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

### Mutación de ejecutable

Al hacer fork el espacio de direcciones es el mismo, por lo que si se quiere
ejecutar otro código el proceso debe mutar a ese otro. Esto se hace con las
llamadas a sistema de tipo exec.

En esta asignatura se usará principalmente la llamada execlp que muta el
ejecutable por otro manteniendo el proceso. De esta forma todo el contenido del
espacio de direcciones cambia, reiniciando el contador de programa a la primera
instrucción de este. Se matiene todo lo relacionado con la indentidad del
proceso, incluyendo los signals pendientes pero se define por defecto la tabla
de programación de signals.

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

## Comunicación entre procesos

Los procesos pueden ser independientes o cooperar entre sí. Esta cooperación
puede ser útil por ejemplo para compartir información entre ellos, acelerar la
computación que realizan o por simple modularidad. Para permitir esta
cooperación obviamente lo necesario es que puedan comunicarse. Esto se hace de
dos formas principalmente:

- Memoria compartida
- Paso de mensajes

### Signals

Los signals son un método de comunicación entre procesos a través de mensajes a
través de notificaciones que pueden ser mandadas tanto por el kernel como por
el mismo u otro proceso del usuario.

### Tipo de signals

Cada posible evento tiene un signal asociado que está predefinido por el
kernel a excepción de dos que están a la disposición del programador para
usarlos como quiera: `SIGUSR1`  y `SIGUSR2`. Cada proceso puede tratar cada
signal de manera diferente, teniendo cada uno un tratamiento pot defecto pero
que el programador puede cambiarlos a excepción de `SIGKILL` y `SIGSTOP`.

EL tratamiento de los signals se basa en como si fueran interrupciones
provocadas por software. Cuando el proceso recibe un signal se interrumpe la
ejecución de lo que fuera que se estuviera ejecutando y se ejecuta el
tratamiento del signal y al acabar (en caso de que no se haga ningún exit)
continúa por el mismo sitio del código por el que iba.

Además los procesos pueden bloquear o desbloquear los signals para decidir
cuáles tratar y cuáles no a excepción de `SIGKILL` y `SIGSTOP` en cualquier
caso y `SIGFPE`, `SIGILL` y `SIGSEGV` si son causados por una excepción. En
caso de que el proceso reciba un signal que haya sigo bloqueado el proceso no
lo recibe y lo marca como pendiente de tratar, de forma que si en algún momento
lo desbloquea se ejecuta la rutina de tratamiento de inmediato.

### Interfaz relacionada con los signals

- Enviar evento (kill)
- Para capturar o reprogramar un signal en concreto se usa la función de C
`sigaction`.
- El bloqueo o desbloqueo de signals se hace usando `sigprocmask`.
- La espera hasta que llegue un evento bloqueado el programa se hace con
  `sigsuspend`.
- Para programa el envío automático del signal `SIGALRM` se hace usando la
  función `alarm`.

Esperar evento:
- Espera activa (no tiene llamada a sistema)
- Espera bloqueante

También se pueden programar signals de forma que se envía SIGALRM después de un
tiempo x en segundos.

#### Struct sigaction

Este struct tiene diversos campos pero solo vamos a fijarnos en 3 importantes:

- `sa_handler`

    Este puede tomar 3 valores:

    - `SIG_IGN`: ignora el signal al recibirlo
    - `SIG_DFL`: usa el tratamiento por defecto del signal
    - función de usuario con una cabecera predefinida: `void nombre_funcion(int
      s)`

- `sa_mask`

    Sirve para determinar los signals que serán añadidos a la máscara de
    signals que el proceso tiene bloqueados. Si esta máscara está vacía solo se
    añade el signal que se está capturando. Al salir del tratamiento de la
    función se restaura la máscara que había antes de entrar.

- `sa_flags`

    Sirve para configurar el comportamiento:

    - Si se mantiene como 0 usa la configuración por defecto del signal
    - `SA_RESETHAND` después de tratar se restaura el tratamiento por defecto
    - `SA_RESTART` reinicia la llamada que ha bloqueado el programa

### Estructuras de datos del kernel

La gestión de los signals es única para cada proceso, por lo que esta
información está guardad en el PCB de este. De forma que cada proceso tiene una
tabla de programación de signals en donde se indica la acción a realizar cuando
se recibe el evento, un bitmap de eventos pendientes que funciona como booleano
y no contador, un único temporizador para la alarma y una máscara de bits que
indica los signals que hay que tratar.

#### Modificar signals

```C
sigset_t m; // Declaración de m como signal
sigemptyset(&m) // Pone la máscara de signals a 0
sigaddset(&m, SIGALRM) // En este caso pone el bit de SIGALRM a 1
sigdelset(&m, SIGALRM) // Pone el bit de SIGALRM a 0
int sig_alrm = sigismember(&m, SIGALRM) // Devuelve 1 si el signal está en la
máscara
sigprocmask(SIG_BLOCK, &m, NULL) // Bloquea únicamente el signal tratado por la
máscara
sigprocmask(SIG_SETMASK, &m, NULL) // Bloquea todos los signals excepto el
tratado por la máscara
sigprocmask(SIG_UNBLOCK, &m, NULL) // desbloquear el signal de la máscara
```
 Para operar con más de un signal a la vez con las operaciones se puede usar
 `sigaddset()` con la misma máscara de signals.

De esta manera un programa para capturar un signal en específico podría ser
así:

```C
void main() {
    char buffer[128];
    struct sigaction sa;
    sigset_t mask;
    sigemptyset(&mask);
    sa.sa_mask = mask;
    sa.sa_flags = 0;
    sa.sa_handler = f_sigint;

    sigaction(SIGINT, &trat, NULL); // Cuando llegue SIGINT se ejecutará f_sigint

    while (1) {
    sprintf(buffer, "Haciendo cositas \n");
    write(1, buffer, strlen(buffer));
    }
}

void f_sigint(int s) {
    char buffer[128];
    sprintf(buffer, "SIGINT RECIBIDO! \n");
    exit(0);
}
```

#### Espera (sincronización)

#### Opción 1

Espera activa: se consulta en bucle el valor de una varuable que se modifica al
recibir un evento, siendo la variable gloabl y el evento una función
`sigaction()`.

##### Opción 2

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

En el caso del programa de ejemplo que se ha puesto primero se configura para
que SIGALRM tenga lla configuración del sigaction `trat`. Se realizan las
operaciones que estén entre los ... y después de eso se bloquean todos los
signals excepto SIGALRM y se configura la alarma de 2 segundos y bloqueando el
proceso.

## Gestión interna

Para gestionar los procesos se usan ciertas estructuras de datos para
representar sus propiedades y recursos (PCB) y para representar y gestionar los
threads (esto depende del SO).

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

### Estructuras de organización

El SO organiza los PCB de los procesos en estructuras de gestión: vectores,
listas, colas, tablas de hash, árboles, etc. en función de las necesidades del
SO.

Los procesos que van en un mismo orden suelen estar organizados en colas o
listas que permiten mantener un orden:

- Cola de procesos: Todos los procesos creados en el sistema
- Cola de procesos listos para ejecutarse (ready): procesos a la espera de CPU.
  En muchos SO esto puede no ser solo 1 única cola sino varias ya que los
  procesos pueden estar agrupadas por clases, prioridades, etc.
- Colas de dispositivos: Procesos a la espera de datos de algún dispositivo de
  E/S

El SO mueve los procesos de una estructura a otra dependiendo de lo que sea
necesario, por ejemplo: cuando temina una operación de E/S el proceso se mueve
de la cola del dispositivo a la cola de ready.

### Planificación

La planificación del SO es llevada por la Política de planificación que se
ejecuta cada poco tiempo (cada 10ms por ejemplo), por lo que debe de ejecutarse
de forma muy rápida. Esto tiene el criterio que evalua si hay que cambiar el
proceso que esté en la CPU, qué proceso se pone, etc.

Hay determinadas situación que provocan la ejecución de la planificación del
sistema:

- Programas en RUN que no pueden continuar la ejecución como puede ser la
  terminación del programa o el bloqueo de este.
- Forzado de la sustitución del programa en CPU por criterio del SO
  dependiendo de la política.

Hay dos tipos de políticas de planificación: las peemptibas (la política le
quita la CPU al proceso) y no preemptivas (la política no le quita la CPU al
proceso).

Además de esto hay dos tipos distintos de procesos: procesos de cálculo
(consumen más tiempo haciendo cálculo que E/S) y procesos de E/S (comsumen más
tiempo con E/S que con cálculo).

#### Mecanismos usados por el planificados

Cuando un proceso deja la CPU y se pone otro proceso en su lugar se produce un
cambio de contexto. En este el sistema tiene que salvar el estado del proceso
que deja la CPU y restaurar el estado del proceso que pasa a ejecutarse. Este
contexto que se guarda suele hacerse en el PCB en un espacio que hay dedicado a
guardar esta información.

Ya que el cambio de contexto no es tiempo útil de la aplicación este debe de
ser rápido con normalmente soporte de hardware para hacerlo permitiendo guardar
todos los registros o restaurarlos de golpe, además que hay difernecias entre
cambio de contexto entre thread del mismo proceso o de distintos.

#### Tipos de planificación

##### Round Robin (RR)

El sistema tiene organizados los procesos en función del estado y encolados por
orden de llegada. Cada proceso tiene la CPU durante un tuepo (time quantum)
típicamente de 10 o 100 ms. El planificados usa una interrupción de reloj para
ir cambiando el proceso en ejecución.

De esta manera tenemos tres tipos de eventos que activan la política RR:

- Bloqueo de proceso
- Terminación de proceso
- Terminación del quantum

Por tanto esta política es peemptiva o apropiativa.

Cuando el proceso está RUN y deja la CPU puede pasar a varios casos:

- En caso de que sea el bloqueo de proceso este se añade a la cola de
  bloqueados hasta que termine el acceso al dispositivo
- Si es la terminación el proceso pasa al estado de zombie en Linux
- Si es por terminación del quantum el proceso se añade al final de la cola de
  READY

Esta política se comporta diferente dependiendo del quantum, ya que si este es
muy grande prácticamente sería una ejecución seuencial hasta el bloqueo o
terminación del proceso por tener el quantum grande. En cambio, si es muy
pequeño habría demasiado tiempo perdido en los cambios de contexto respecto al
poco tiempo de ejecución que se tendría.

##### Completely Fair Scheduling

Este es el algoritmo que se usa en las versiones actuales de Linux con un
máximo de tiempo de uso consecutivo de CPU variable en base a los procesos que
compiten por la CPU, sacando el cálculo del tiempo consumido de CPU entre el
número de procesos en competición con una prioridad del proceso en base a la
distancia respecto al tiempo teórico de CPU (cuando más lejos mayor prioridad).
Además crea grupos de procesos permitiendo contabilizar el uso de CPU de cada
grupo de forma que se evita que un usuario monopolice la máquina.

## Memoria

La CPU solo puede acceder directamente a la memoria y los registros, por tanto
las instrucciones y los datos deben cargarse en memoria para poder
referenciarse, es decir, reservar memoria, escribir en ella el programa/los
datos y pasar el programa al punto de entrada en caso de ser de instrucciones
la memoria.

Hay dos tipos de direcciones: la referencia emitida por la CPU que es la
dirección lógica y la ocupada en memoria que es la dirección física. No tienen
por qué coincidir si el sistema operativo y el hardware ofrecen soporte para la
traducción entre estas.

Los sistemas multiprogramados son esos en los que hay varios programas cargados
en memoria física a la vez. Esto facilita la ejecución concurrente de los
programas y simplifica el cambio de contexto de ejecución. En esta clase de
sistemas el sistema operativo deve de garantizar la protección de la memoria
física para evitar el acceso de programas que no deben a la memoria. El kernel
de esta manera debe modificar la MMU para reflejar cualquier cambio de contexto
o si se aumenta el espacio de direcciones entre otras cosas.

El MMU es un componente de hardware que s eencarga de la traducción de
direcciones y la protección del acceso a memoria. El sistema operativo es el
responsable de configurarlo con los valores de la traducción de direcciones. El
sistema operativo se encarga de gestionar la excepción en función del caso que
sea, pudiendo eliminar el proceso con el error que personalmente más odio:
`SIGSEGV` también conocido como `segmentation fault`.

El sistema operativo tiene que modificar la traducción de direcciones del MMU
cuando se asigna memoria al inicializar o cuando se produce un cambio en el
espacio de direcciones al aumentar o disminuir al pedir o liberar memoria
dinámica. Además también se modifica en el cambio de contexto cuando un proceso
pasa a abandonar la CPU y otro toma ese lugar.

El sistema operativo se encarga de la carga de los programas en memoria,
reserma y libera memoria dinámicamente a través de llamadas a sistema, ofrece
la compartición de memoria entre procesos.

### Carga de programas

El ejectuable debe de estar en la memoria para poder ejecutarse pero este enm
un primer momento se encuentra en el disco. De esta manera el sistema operativo
debe de leer e interpretar el ejecutable, preparar el esquema del proceso en la
memoria lógica y asignar la memoria física, leer las secciones del programa del
disco y escribir en la memoria y cargar el registro del program counter con la
dirección de la instrucción definida en el ejecutable como puunto de entrada,
además de realizar las optimizaciones aplicadas a la carga de programas como es
la carga bajo demanda y las librería compartidas y de enlace dinámico. Todo
esto se realiza en Linux al mutar un proceso.

### Formato del ejecutable

Primero se interpreta el formato del ejecutable en disco, teniendo en la
cabecera definidas las secciones del programa. El formato más extendido en
sistemas POSIX es ELF que tiene diferentes secciones entre ellas `.text` con el
código, `.data` con los datos globales inicializados, `.bss` con datos globales
sin valor inicial, `.debug` con información de debug, `.comment` con
información de control, `.dynamic` ocn información para el enlace dinámico e
`.init` que contiene la dirección de la primera instrucción.

Después prepara el esquema del proceso en la memoria lógica. Reservando la
memoria en las distintas partes de la memoria para las distintas clases de
datos.

### Carga bajo demanda

Las rutinas no se cargan hasta que son llamadas de forma que se aprovecha mucho
mejor la memoria al no ocupar espacio de esta con funciones que puede que no se
llamen en ningún momento, además acelera el proceso de carga. Se debe de tener
un mecanismo que detecte si las rutinas están cargadas o no.

### Optimización de librerías compartidas

Los binarios en el disco no contienen el código de las librerías dinámicas,
únicamente un enlace a estas, de forma que s eahorra mucho espacio en el disco.
Además se facilita la actualización de los programas a las nuevas versiones de
la librerías.

### Reserva o liberación de memoria dinámica

Hay variables cuyo tamaño depende de parámetros de la ejecución. Fijar el
tamaño de estas en tiempo de compilación no es adecuado ya que se puede
desaprovechar memoria o tener errores de ejecución si falta memoria reservada.
De esta manera los sistemas operativos ofrecen un espacio de la memoria llamado
heap.

Para reservar la memoria se usará la interfaz tradicional de Unis con la
función `sbrk`. En la que si el número que se le pasa es mayor a 0 aumenta el
heap, si es menor lo reduce y si es 0 lo mantiene igual.

```C
int main(int argc, char *argv[]) {
    int num_procs = atoi(argv[1]);
    int *pids;
    pids = sbrk(num_procs*sizeof(int));

    for (int i = 0; i < 10; ++i) {
	pids[i] = fork();

	if (pids[i] == 0) {
	    ...
    	}
    }

    sbrk(-1*num_procs*sizeof(int));
}
```

La librería de C añade la gestión que vincula las direcciones con las variables
que pide memoria usando la función `malloc`, de forma que si hay tamaño
consecutivo disponible lo marca como reservado y devuelve la dirección de
inicio y en caso contrario aumenta el heap y devuelve la dirección de inicio.
Para libersar memoria se usa la función `free`.

```C
int main(int argc, char *argv[]) {
    int num_procs = atoi(argv[1]);
    int *pids;
    pids = malloc(num_procs*sizeof(int));

    for (int i = 0; i < 10; ++i) {
	pids[i] = fork();

	if (pids[i] == 0) {
	    ...
    	}
    }
    
    free(pids);
}
```

En cambio se producen problemas de fragmentación cuando se quiere asignar una
cantidad de memoria en una zona más grande al quedar espacios libres que no s
epueden usar (también se produce a nivel de disco). Hay dos tipos de
fragmentación: la fragmentación interna que es cuando se asigna memoria a un
proceso pero no la necesita y la fragmentación externa que es cuando hay
memoria libre pero no se puede asignar por no estar contigua.

De esta manera se tiene la asignación contínua que puede dar estos errores de
fragmentación al ocupar todo el espacio asignado direcciones contiguas y la
asignación no contigua que evita los problemas de fragmentación pero añade
cmplejidad al sistema operativo y el MMU.

#### Paginación

Un esquema basado en la paginación es un espacio de direcciones lógicas
dividido en particiones de tamaño fijo llamados páginas y la memoria física se
divide también en particiones del mismo tamaño llamadas marcos.Para cada página
del proceso se busca un marco libre y cuando acaba la ejecución devuelve los
amrcos libres. El sistema de paginación facilita la carga bajo demanda y
permite especificar la protección a nivel de página, además de facilitar la
compartición de memoria entre procesos. Por tema d epermisos una página
pertenece a una única región de memoria. D eeta forma el MMU tiene la tabla de
páginas para mantener la información a nivel de página con una entrada pro cada
página y una tabla para cada proceso. Esta suele guardarse en memoria y el
sistema operativo debe conocer la dirección de memoria en la que se guard ala
tbala de cada proceso. Los procesadores actuales disponen también de TLB, una
clase de memoria cache para el MMU.

Se suelen usar páginas de 4KB y la tabla va creciendo a medida que se van
añadiendo secciones para evitar que empiece con un tamaño excesivamente grande.



