#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== DEFINICIONES DE CONSTANTES =====
#define MAX_VEHICULOS 100
#define MAX_CLIENTES 50
#define MAX_STRING 100
#define MAX_TRANSACCIONES 200

// ===== ESTRUCTURAS DE DATOS =====

// Estructura para representar un vehiculo
typedef struct {
    int id;
    char marca[MAX_STRING];
    char modelo[MAX_STRING];
    int anio;
    float precio;
    char tipo[MAX_STRING]; // "Nuevo" o "Usado"
    char estado[MAX_STRING]; // "Disponible" o "Vendido"
    float kilometraje;
    char color[MAX_STRING];
} Vehiculo;

// Estructura para representar un cliente
typedef struct {
    int id;
    char nombre[MAX_STRING];
    char apellido[MAX_STRING];
    char telefono[MAX_STRING];
    char email[MAX_STRING];
    char direccion[MAX_STRING];
    float presupuesto;
} Cliente;

// Estructura para representar una transacción
typedef struct {
    int id;
    int id_cliente;
    int id_vehiculo;
    float monto_final;
    char fecha[MAX_STRING];
} Transaccion;

// Estructura para el inventario
typedef struct {
    Vehiculo vehiculos[MAX_VEHICULOS];
    int cantidad_vehiculos;
} Inventario;

// Estructura para la base de clientes
typedef struct {
    Cliente clientes[MAX_CLIENTES];
    int cantidad_clientes;
} BaseDatos_Clientes;

// Estructura para el registro de transacciones
typedef struct {
    Transaccion transacciones[MAX_TRANSACCIONES];
    int cantidad_transacciones;
} Registro_Transacciones;

// ===== FUNCIONES DE GESTIÓN DE VEHÍCULOS =====

// Inicializa el inventario vacio
void inicializar_inventario(Inventario *inv);

// Agrega un nuevo vehiculo al inventario
void agregar_vehiculo(Inventario *inv, char marca[], char modelo[], int anio, 
                     float precio, char tipo[], float kilometraje, char color[]);

// Busca un vehiculo por ID
Vehiculo* buscar_vehiculo_por_id(Inventario *inv, int id);

// Busca vehiculos disponibles dentro de un rango de precio
void buscar_vehiculos_por_precio(Inventario *inv, float precio_min, float precio_max);

// Busca vehiculos por marca
void buscar_vehiculos_por_marca(Inventario *inv, char marca[]);

// Lista todos los vehiculos disponibles
void listar_vehiculos_disponibles(Inventario *inv);

// Lista todos los vehiculos (incluyendo vendidos)
void listar_todos_vehiculos(Inventario *inv);

// Actualiza el estado de un vehiculo
void actualizar_estado_vehiculo(Inventario *inv, int id, char nuevo_estado[]);

// Elimina un vehiculo del inventario (solo si esta disponible)
void eliminar_vehiculo(Inventario *inv, int id);

// Actualiza el precio de un vehiculo
void actualizar_precio_vehiculo(Inventario *inv, int id, float nuevo_precio);

// ===== FUNCIONES DE GESTIÓN DE CLIENTES =====

// Inicializa la base de datos de clientes
void inicializar_clientes(BaseDatos_Clientes *bd_clientes);

// Agrega un nuevo cliente
void agregar_cliente(BaseDatos_Clientes *bd, char nombre[], char apellido[], 
                    char telefono[], char email[], char direccion[], float presupuesto);

// Busca un cliente por ID
Cliente* buscar_cliente_por_id(BaseDatos_Clientes *bd, int id);

// Busca clientes por nombre
void buscar_clientes_por_nombre(BaseDatos_Clientes *bd, char nombre[]);

// Lista todos los clientes
void listar_clientes(BaseDatos_Clientes *bd);

// Actualiza la informacion de un cliente
void actualizar_cliente(BaseDatos_Clientes *bd, int id, char nombre[], char apellido[], 
                       char telefono[], char email[], char direccion[], float presupuesto);

// Elimina un cliente
void eliminar_cliente(BaseDatos_Clientes *bd, int id);

// ===== FUNCIONES DE TRANSACCIONES =====

// Inicializa el registro de transacciones
void inicializar_transacciones(Registro_Transacciones *reg);

// Registra una venta
void registrar_venta(Registro_Transacciones *reg, Inventario *inv, 
                    BaseDatos_Clientes *bd, int id_cliente, int id_vehiculo, float descuento);

// Lista todas las transacciones
void listar_transacciones(Registro_Transacciones *reg);

// Calcula ingresos totales
float calcular_ingresos_totales(Registro_Transacciones *reg);

// ===== FUNCIONES DE BÚSQUEDA AVANZADA =====

// Busca vehiculos que coincidan con los requerimientos del cliente
void buscar_vehiculos_para_cliente(Inventario *inv, Cliente *cliente, 
                                   char marca_preferida[], char tipo[]);

// Calcula estadisticas del inventario
void mostrar_estadisticas_inventario(Inventario *inv);

// ===== FUNCIONES AUXILIARES =====

// Obtiene la fecha actual como string
void obtener_fecha_actual(char fecha[]);

// Valida si un email es valido (basico)
int validar_email(char email[]);

// Valida si un telefono es valido
int validar_telefono(char telefono[]);

#endif
