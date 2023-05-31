<a name="readme-top"></a>

<div align="center">
  <a href="https://github.com/CS-DaviMagalhaes/Proyecto_Algoritmos_y_Estructuras">
    <img src="images/blockchain.jpg" alt="Blockchain" width="500" height="300">
  </a> 
  <h1>🔷 Aplicación de retiro de dinero con blockchain 🔶</h1>
  
  <p>
  
  </p>
</div>

<details open>
  <summary>Tabla de contenidos:</summary>
  <ol>
    <li><a href="#acerca-del-proyecto">
      Acerca del proyecto
      <ul>
        <li><a href="#introducción1">Introducción</a></li>
        <li><a href="#caso-de-estudio">Caso de estudio</a></li>
        <li><a href="#importancia-de-blockchain">Importancia de blockchain</a></li>
        <li><a href="#estructura-de-blockchain">Estructura de blockchain</a></li>
        <li><a href="#estrategia-usada-integridad">Estrategia usada para asegurar la integridad del contenido</a></li>
        <li><a href="#estructura-de-datos-usadas">Estructuras de datos usadas</a></li>
      </ul>
    </a></li>
    <li><a href="#autores">
      Autores
    </a></li>
    <li><a href="#referencias">
    Referencias bibliográficas
    </a></li>
    <li><a href="#anexos">
      Anexos
    </a></li>
  </ol>
</details>

---

## Acerca del proyecto

### Introducción
El Blockchain o cadena de bloques es un libro mayor digital o una lista de registros electrónicos de transacciones que son almacenadas en bloques secuenciales que se conectan entre sí en cadena. El blockchain utiliza un algoritmo para asignar una *huella digital* a cada bloque, conocido como *hash*, que es una cadena única criptografada de letras y números que cambia si es que se altera la información del bloque. Cada bloque almacena el hash propio y del bloque anterior de tal forma que si se hace una alteración en un bloque todos los bloques posteriores son afectados. El Blockchain también se caracteriza por la ausencia de un intermediario para autenticar las transacciones.

### Caso de estudio
El presente proyecto consiste en una aplicación basada en el uso de Blockchain, el cual nos permite realizar transacciones y almacenarlos de manera segura. En este caso, las transacciones monetarias entre individuos viene a ser **el retiro**, y se hacen mediante el uso del hashing SHA256.
Este hash nos permite encriptar esta informacion que viene a ser una combinación de números y letras. Además, este identificador puede ser actualizado de diversas formas, un ejemplo de ello es cuando se hace un cambio a un bloque. Asimismo, cada blockchain cuenta con un valor *nonce* que viene a ser un número único que comprende una combinación con una cadena de datos del bloque al que pertenece.
### Importancia del blockchain
El blockchain es una tecnología que nos permite llevar un registro seguro, sincronizado, descentralizado, el cual no necesita de la intervención de terceros. Por lo tanto, es ideal para hacer seguimiento de pedidos, pagos, cuentas y en este proyecto que trata de una simulación de retiro de dinero como en un banco.
Es una base de datos distribuida donde todos los nodos tienen un registro de la información todo el tiempo. Pasando de una lógica centralizada, dónde alguien controla toda la información, a una distribuida, dónde la información se divide entre todas las computadoras. Dónde nadie puede monopolizar los contenidos porque todas las computadoras se ponen de acuerdo en cuál es la base de datos única donde van a converger.
### Estructura del blockchain
La estructura de datos del blockchain tiene el siguiente esquema:

```cpp
class Blockchain {
   private:
    List<Block *> *chain = new DoubleList<Block *>();
    Heap<retiro>* heap_fechaMax = new Heap<retiro>(10, Heap<retiro>::MAX_HEAP);
    Heap<retiro>* heap_fechaMin = new Heap<retiro>(10, Heap<retiro>::MIN_HEAP);
    HeapMon<retiro>* heap_montoMin = new HeapMon<retiro>(10, HeapMon<retiro>::MIN_HEAP);
    HeapMon<retiro>* heap_montoMax = new HeapMon<retiro>(10, HeapMon<retiro>::MAX_HEAP);

    unsigned int size_chain = 0;
    
   public:
    // Constructor
    Blockchain() {}

    // Public Functions
    void addBlock(retiro *data);
    void show_blockchain();
    void import_blockchain(const string& archivo);
    void test_proof_work(int id);
    void fix_all();
    void max_value(string tipe);
    void min_value(string tipe);

};
```

**Explicación de los atributos**
`chain` : Se implementó una lista que almacena punteros a bloques. Cada bloque guarda la información de un retiro de dinero. El retiro de dinero tiene un cliente, un lugar, un monto y una fecha. Por otro lado, el bloque presenta un id, un nonce, un retiro de dinero (objeto que presenta las caracteristicas previamente descritas), un hash para mantener cifrada la identidad del usuario, el hash previo a este y un booleano que indica si el bloque es válido o no.

`heap_fechaMax` : Se crea una estructura max-heap donde se almacenará las fechas de los retiros hechos. Esto servirá para obtener la fecha más actual en la que se hizo un retiro de dinero.

`heap_fechaMin` : Se crea una estructura min-heap donde se almacenará las fechas de los retiros hechos. Esto servirá para obtener la fecha más antigua en la que se hizo un retiro de dinero.

`heap_montoMax` : Se crea una estructura max-heap donde se almacenará los montos de dinero de los retiros hechos. Esto servirá para obtener la el monto más alto.

`heap_montoMin` : Se crea una estructura min-heap donde se almacenará los montos de dinero de los retiros hechos. Esto servirá para obtener el monto más bajo.

`size_chain`: Cantidad de bloques o de transacciones, en términos del proyecto, cantidad de retiros de dinero de los clientes.

**Explicación del constructor**
El constructor es uno por defecto, ya que una cadena de bloques siempre empieza vacía. Entonces, simplemente cuando se quiere crear un objeto blockchain se llama a la clase sin necesidad de pasarle ningun argumento. Si se desea añadir información a este, entonces allí se empiezan a llamar a los métodos de la clase, como por ejemplo el método inicial sería el de añadir bloques (`addBlock(retiro *data)`).

**Explicación de los métodos**

`addBlock` : 

`show_blockchain` : 

`import_blockchain` : 

`test_proof_work` : 

`fix_all` : 

`max_value` : 

`min_value` : 


### Estrategia usada para asegurar la integridad del contenido


### Estructuras de datos usadas


### Análisis de complejidad algorítmica
>- **block.h**:



**Creación de un objeto Block:**


**Función "mine()":** 



**Función "reHash()":**


**Otras funciones:**


>- **blockchain.h**:



**Función "addBlock(retiro data)":**


**Función "show_blockchain()":**


**Función "import_blockchain(const string& archivo)":**

O(m * n) - La función importa una cadena de bloques a partir de un archivo CSV. El tiempo de ejecución depende del número de líneas en el archivo (m) y del número de bloques en la cadena existente (n).

**Función "test_proof_work(int id)":**




**Función "fix_all()":**



>- **SHA256.h** 



**Conversión del texto de entrada a binario:**




**Conversión de los valores hash 'h' a hexadecimal:**


### Conclusiones


### Autores

### Referencias bibliográficas

---

[Back To The Top](#readme-top)

