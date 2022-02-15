[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6870065&assignment_repo_type=AssignmentRepo)
# fsm_bump_go

## 0.Introducción
En esta primera práctica se nos ha pedido realizar un **bump and go** en distintas versiones. Para ello hemos optado por crear una clase base abstracta llamada "BumpGo_Base.h" y de la que heredan "BumpGo.h", "BumpGo_Advanced.h" y "NearGo.h". 

## 1.Versión 0: BumpGo 

### 1.1. Descripción
En esta versión se nos ha pedido hacer un programa básico de **bump and go** cuya máquina de estados está formada por 3  estados:

- 1º: Ir hacia delante y detecta un objeto
- 2º: Hacia atrás 
- 3º: Gira a la izquierda

### 1.2. Problemas surgidos durante la práctica
Los problemas que nos han surgido en esta práctica 0 son los siguientes:
  - Nos costó mucho entender la lógica del programa base que aparecía de ejemplo. De todo el código base nos costó entender en bumpgo_node.cpp las siguientes líneas: 
 
```c++
ros::init(argc, argv, "fsm_bump_go");

fsm_bump_go::BumpGo fsm_bump_go;
```


  
### 1.3. Vídeo de la versión 0
[Aquí]() podrás ver el funcionamiento de la práctica.

## 2.Versión 1: BumpGo_Advanced

### 2.1. Descripción 
En esta versión se nos ha pedido hacer un programa **bump and go** que sepa por donde detecta un objeto cuando se choca con él usando su bumper. Su máquina de estados está formada por los siguientes estados:

_Detecta un objeto por la derecha:_
- 1º: Va hacia delante 
- 2º: Detecta un objeto
- 3º: Hacia atrás
- 4º: Gira a la izquierda

_Detecta un objeto por la izquierda:_
- 1º: Va hacia delante 
- 2º: Detecta un objeto
- 3º: Hacia atrás
- 4º: Gira a la derecha

_Detecta un objeto de frente:_
- 1º: Va hacia delante 
- 2º: Detecta un objeto 
- 3º: Hacia atrás
- 4º: Gira a la izquierda

### 2.2. Problemas surgidos durante la práctica 

### 2.3. Video de la versión 1
[Aquí]() podrás ver el funcionamiento de la práctica.

## 3.Versión 2: NearGo

### 2.1. Descripción 

En esta versión se nos ha pedido hacer un programa **bump and go** usando el láser.


### 2.2. Problemas surgidos durante la práctica 

### 2.3. Video de la versión 2
[Aquí]() podrás ver el funcionamiento de la práctica.



