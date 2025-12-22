#include "funciones.h"

// ===== MENU PRINCIPAL =====
void mostrar_menu_principal() {
    printf("\n");
    printf("========================================================\n");
    printf("  SISTEMA DE GESTION DE INVENTARIO Y CLIENTES\n");
    printf("         CONCESIONARIA RUEDAS DE ORO            \n");
    printf("========================================================\n");
    printf("\n[1] Gestionar Vehiculos\n");
    printf("[2] Gestionar Clientes\n");
    printf("[3] Registrar Venta\n");
    printf("[4] Ver Transacciones\n");
    printf("[5] Busqueda Avanzada\n");
    printf("[6] Estadisticas\n");
    printf("[0] Salir\n");
    printf("\nSeleccione una opción: ");
}

void mostrar_menu_vehiculos() {
    printf("\n===== GESTION DE VEHICULOS =====\n");
    printf("[1] Agregar nuevo vehiculo\n");
    printf("[2] Listar vehiculos disponibles\n");
    printf("[3] Listar todos los vehiculos\n");
    printf("[4] Buscar por precio\n");
    printf("[5] Buscar por marca\n");
    printf("[6] Actualizar precio\n");
    printf("[7] Actualizar estado\n");
    printf("[8] Eliminar vehiculo\n");
    printf("[0] Volver al menú principal\n");
    printf("\nSeleccione una opción: ");
}

void mostrar_menu_clientes() {
    printf("\n===== GESTION DE CLIENTES =====\n");
    printf("[1] Agregar nuevo cliente\n");
    printf("[2] Listar todos los clientes\n");
    printf("[3] Buscar cliente por nombre\n");
    printf("[4] Actualizar cliente\n");
    printf("[5] Eliminar cliente\n");
    printf("[0] Volver al menú principal\n");
    printf("\nSeleccione una opción: ");
}

// ===== FUNCIONES DE ENTRADA =====
void menu_agregar_vehiculo(Inventario *inv) {
    char marca[MAX_STRING], modelo[MAX_STRING], tipo[MAX_STRING], color[MAX_STRING];
    int anio;
    float precio, kilometraje;
    
    printf("\n===== AGREGAR NUEVO VEHICULO =====\n");
    printf("Marca: ");
    scanf("%s", marca);
    printf("Modelo: ");
    scanf("%s", modelo);
    printf("Anio: ");
    scanf("%d", &anio);
    printf("Precio: $");
    scanf("%f", &precio);
    printf("Tipo (Nuevo/Usado): ");
    scanf("%s", tipo);
    printf("Kilometraje: ");
    scanf("%f", &kilometraje);
    printf("Color: ");
    scanf("%s", color);
    
    agregar_vehiculo(inv, marca, modelo, anio, precio, tipo, kilometraje, color);
}

void menu_agregar_cliente(BaseDatos_Clientes *bd) {
    char nombre[MAX_STRING], apellido[MAX_STRING], telefono[MAX_STRING];
    char email[MAX_STRING], direccion[MAX_STRING];
    float presupuesto;
    
    printf("\n===== AGREGAR NUEVO CLIENTE =====\n");
    printf("Nombre: ");
    scanf("%s", nombre);
    printf("Apellido: ");
    scanf("%s", apellido);
    printf("Teléfono: ");
    scanf("%s", telefono);
    printf("Email: ");
    scanf("%s", email);
    printf("Dirección: ");
    scanf("%s", direccion);
    printf("Presupuesto: $");
    scanf("%f", &presupuesto);
    
    agregar_cliente(bd, nombre, apellido, telefono, email, direccion, presupuesto);
}

void menu_buscar_por_precio(Inventario *inv) {
    float precio_min, precio_max;
    
    printf("\n===== BUSCAR POR RANGO DE PRECIO =====\n");
    printf("Precio mínimo: $");
    scanf("%f", &precio_min);
    printf("Precio máximo: $");
    scanf("%f", &precio_max);
    
    buscar_vehiculos_por_precio(inv, precio_min, precio_max);
}

void menu_buscar_por_marca(Inventario *inv) {
    char marca[MAX_STRING];
    
    printf("\n===== BUSCAR POR MARCA =====\n");
    printf("Marca a buscar: ");
    scanf("%s", marca);
    
    buscar_vehiculos_por_marca(inv, marca);
}

void menu_actualizar_precio(Inventario *inv) {
    int id;
    float nuevo_precio;
    
    printf("\n===== ACTUALIZAR PRECIO =====\n");
    printf("ID del vehículo: ");
    scanf("%d", &id);
    printf("Nuevo precio: $");
    scanf("%f", &nuevo_precio);
    
    actualizar_precio_vehiculo(inv, id, nuevo_precio);
}

void menu_actualizar_estado(Inventario *inv) {
    int id;
    char nuevo_estado[MAX_STRING];
    
    printf("\n===== ACTUALIZAR ESTADO =====\n");
    printf("ID del vehículo: ");
    scanf("%d", &id);
    printf("Nuevo estado (Disponible/Vendido): ");
    scanf("%s", nuevo_estado);
    
    actualizar_estado_vehiculo(inv, id, nuevo_estado);
}

void menu_eliminar_vehiculo(Inventario *inv) {
    int id;
    
    printf("\n===== ELIMINAR VEHICULO =====\n");
    printf("ID del vehiculo a eliminar: ");
    scanf("%d", &id);
    
    eliminar_vehiculo(inv, id);
}

void menu_actualizar_cliente(BaseDatos_Clientes *bd) {
    int id;
    char nombre[MAX_STRING], apellido[MAX_STRING], telefono[MAX_STRING];
    char email[MAX_STRING], direccion[MAX_STRING];
    float presupuesto;
    
    printf("\n===== ACTUALIZAR CLIENTE =====\n");
    printf("ID del cliente: ");
    scanf("%d", &id);
    printf("Nombre: ");
    scanf("%s", nombre);
    printf("Apellido: ");
    scanf("%s", apellido);
    printf("Teléfono: ");
    scanf("%s", telefono);
    printf("Email: ");
    scanf("%s", email);
    printf("Dirección: ");
    scanf("%s", direccion);
    printf("Presupuesto: $");
    scanf("%f", &presupuesto);
    
    actualizar_cliente(bd, id, nombre, apellido, telefono, email, direccion, presupuesto);
}

void menu_eliminar_cliente(BaseDatos_Clientes *bd) {
    int id;
    
    printf("\n===== ELIMINAR CLIENTE =====\n");
    printf("ID del cliente a eliminar: ");
    scanf("%d", &id);
    
    eliminar_cliente(bd, id);
}

void menu_registrar_venta(Registro_Transacciones *reg, Inventario *inv, BaseDatos_Clientes *bd) {
    int id_cliente, id_vehiculo;
    float descuento;
    
    printf("\n===== REGISTRAR VENTA =====\n");
    printf("ID del cliente: ");
    scanf("%d", &id_cliente);
    printf("ID del vehículo: ");
    scanf("%d", &id_vehiculo);
    printf("Descuento (%%): ");
    scanf("%f", &descuento);
    
    registrar_venta(reg, inv, bd, id_cliente, id_vehiculo, descuento);
}

void menu_buscar_cliente_por_nombre(BaseDatos_Clientes *bd) {
    char nombre[MAX_STRING];
    
    printf("\n===== BUSCAR CLIENTE POR NOMBRE =====\n");
    printf("Nombre a buscar: ");
    scanf("%s", nombre);
    
    buscar_clientes_por_nombre(bd, nombre);
}

void menu_busca_avanzada(Inventario *inv, BaseDatos_Clientes *bd) {
    int id_cliente;
    char marca[MAX_STRING], tipo[MAX_STRING];
    
    printf("\n===== BÚSQUEDA AVANZADA =====\n");
    printf("ID del cliente: ");
    scanf("%d", &id_cliente);
    printf("Marca preferida: ");
    scanf("%s", marca);
    printf("Tipo de vehiculo (Nuevo/Usado): ");
    scanf("%s", tipo);
    
    Cliente *c = buscar_cliente_por_id(bd, id_cliente);
    if (c != NULL) {
        buscar_vehiculos_para_cliente(inv, c, marca, tipo);
    } else {
        printf("\n[ERROR] Cliente no encontrado.\n");
    }
}

// ===== FUNCIÓN PRINCIPAL =====
int main() {
    // Inicializar estructuras
    Inventario inventario;
    BaseDatos_Clientes base_clientes;
    Registro_Transacciones registro_ventas;
    
    inicializar_inventario(&inventario);
    inicializar_clientes(&base_clientes);
    inicializar_transacciones(&registro_ventas);
    
    // Agregar datos de prueba
    printf("\n[*] Inicializando sistema con datos de prueba...\n");
    
    // Vehículos de prueba
    agregar_vehiculo(&inventario, "Toyota", "Corolla", 2023, 25000, "Nuevo", 0, "Blanco");
    agregar_vehiculo(&inventario, "Honda", "Civic", 2022, 22000, "Nuevo", 500, "Gris");
    agregar_vehiculo(&inventario, "Ford", "Focus", 2020, 18000, "Usado", 45000, "Negro");
    agregar_vehiculo(&inventario, "Chevrolet", "Cruze", 2021, 20000, "Usado", 35000, "Rojo");
    agregar_vehiculo(&inventario, "Toyota", "RAV4", 2023, 35000, "Nuevo", 0, "Plata");
    
    // Clientes de prueba
    agregar_cliente(&base_clientes, "Juan", "Perez", "+34612345678", "juan@email.com", 
                   "Calle Principal 123", 30000);
    agregar_cliente(&base_clientes, "Maria", "Garcia", "+34687654321", "maria@email.com", 
                   "Avenida Central 456", 25000);
    agregar_cliente(&base_clientes, "Carlos", "Lopez", "+34645123789", "carlos@email.com", 
                   "Plaza Mayor 789", 40000);
    
    printf("[✓] Sistema inicializado correctamente.\n");
    
    // Menú principal
    int opcion;
    int opcion_sub;
    
    while (1) {
        mostrar_menu_principal();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1: {
                // Gestión de vehículos
                while (1) {
                    mostrar_menu_vehiculos();
                    scanf("%d", &opcion_sub);
                    
                    switch (opcion_sub) {
                        case 1:
                            menu_agregar_vehiculo(&inventario);
                            break;
                        case 2:
                            listar_vehiculos_disponibles(&inventario);
                            break;
                        case 3:
                            listar_todos_vehiculos(&inventario);
                            break;
                        case 4:
                            menu_buscar_por_precio(&inventario);
                            break;
                        case 5:
                            menu_buscar_por_marca(&inventario);
                            break;
                        case 6:
                            menu_actualizar_precio(&inventario);
                            break;
                        case 7:
                            menu_actualizar_estado(&inventario);
                            break;
                        case 8:
                            menu_eliminar_vehiculo(&inventario);
                            break;
                        case 0:
                            goto salir_vehiculos;
                        default:
                            printf("[ERROR] Opción inválida.\n");
                    }
                }
                salir_vehiculos:
                break;
            }
            
            case 2: {
                // Gestión de clientes
                while (1) {
                    mostrar_menu_clientes();
                    scanf("%d", &opcion_sub);
                    
                    switch (opcion_sub) {
                        case 1:
                            menu_agregar_cliente(&base_clientes);
                            break;
                        case 2:
                            listar_clientes(&base_clientes);
                            break;
                        case 3:
                            menu_buscar_cliente_por_nombre(&base_clientes);
                            break;
                        case 4:
                            menu_actualizar_cliente(&base_clientes);
                            break;
                        case 5:
                            menu_eliminar_cliente(&base_clientes);
                            break;
                        case 0:
                            goto salir_clientes;
                        default:
                            printf("[ERROR] Opción inválida.\n");
                    }
                }
                salir_clientes:
                break;
            }
            
            case 3:
                menu_registrar_venta(&registro_ventas, &inventario, &base_clientes);
                break;
            
            case 4:
                listar_transacciones(&registro_ventas);
                printf("\nIngresos totales: $%.2f\n", calcular_ingresos_totales(&registro_ventas));
                break;
            
            case 5:
                menu_busca_avanzada(&inventario, &base_clientes);
                break;
            
            case 6:
                mostrar_estadisticas_inventario(&inventario);
                break;
            
            case 0:
                printf("\n[*] Gracias por usar el Sistema de Gestion de Inventario.\n");
                printf("[*] Hasta luego!\n\n");
                return 0;
            
            default:
                printf("[ERROR] Opción inválida. Intente de nuevo.\n");
        }
    }
    
    return 0;
}
