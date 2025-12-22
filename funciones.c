#include "funciones.h"

// ===== FUNCIONES DE GESTIÓN DE VEHÍCULOS =====

void inicializar_inventario(Inventario *inv) {
    inv->cantidad_vehiculos = 0;
}

void agregar_vehiculo(Inventario *inv, char marca[], char modelo[], int anio, 
                     float precio, char tipo[], float kilometraje, char color[]) {
    if (inv->cantidad_vehiculos >= MAX_VEHICULOS) {
        printf("\n[ERROR] El inventario esta lleno. No se puede agregar mas vehiculos.\n");
        return;
    }
    
    Vehiculo v;
    v.id = inv->cantidad_vehiculos + 1;
    strcpy(v.marca, marca);
    strcpy(v.modelo, modelo);
    v.anio = anio;
    v.precio = precio;
    strcpy(v.tipo, tipo);
    strcpy(v.estado, "Disponible");
    v.kilometraje = kilometraje;
    strcpy(v.color, color);
    
    inv->vehiculos[inv->cantidad_vehiculos] = v;
    inv->cantidad_vehiculos++;
    
    printf("\n[EXITO] Vehiculo agregado correctamente. ID: %d\n", v.id);
}

Vehiculo* buscar_vehiculo_por_id(Inventario *inv, int id) {
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (inv->vehiculos[i].id == id) {
            return &inv->vehiculos[i];
        }
    }
    return NULL;
}

void buscar_vehiculos_por_precio(Inventario *inv, float precio_min, float precio_max) {
    printf("\n===== VEHICULOS POR RANGO DE PRECIO =====\n");
    printf("Rango: $%.2f - $%.2f\n", precio_min, precio_max);
    printf("================================\n");
    
    int encontrados = 0;
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (inv->vehiculos[i].estado[0] == 'D' && 
            inv->vehiculos[i].precio >= precio_min && 
            inv->vehiculos[i].precio <= precio_max) {
            printf("ID: %d | %s %s (%d) | $%.2f | %s km | Color: %s\n",
                   inv->vehiculos[i].id,
                   inv->vehiculos[i].marca,
                   inv->vehiculos[i].modelo,
                   inv->vehiculos[i].anio,
                   inv->vehiculos[i].precio,
                   (int)inv->vehiculos[i].kilometraje,
                   inv->vehiculos[i].color);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No hay vehiculos disponibles en este rango de precios.\n");
    } else {
        printf("Total encontrado: %d vehiculos\n", encontrados);
    }
}

void buscar_vehiculos_por_marca(Inventario *inv, char marca[]) {
    printf("\n===== VEHICULOS DE LA MARCA: %s =====\n", marca);
    printf("================================\n");
    
    int encontrados = 0;
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (strcmp(inv->vehiculos[i].marca, marca) == 0 && 
            inv->vehiculos[i].estado[0] == 'D') {
            printf("ID: %d | %s (%d) | $%.2f | %s | %d km\n",
                   inv->vehiculos[i].id,
                   inv->vehiculos[i].modelo,
                   inv->vehiculos[i].anio,
                   inv->vehiculos[i].precio,
                   inv->vehiculos[i].tipo,
                   (int)inv->vehiculos[i].kilometraje);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No hay vehiculos disponibles de esta marca.\n");
    } else {
        printf("Total encontrado: %d vehiculos\n", encontrados);
    }
}

void listar_vehiculos_disponibles(Inventario *inv) {
    printf("\n===== INVENTARIO DE VEHICULOS DISPONIBLES =====\n");
    printf("================================================\n");
    
    int disponibles = 0;
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (strcmp(inv->vehiculos[i].estado, "Disponible") == 0) {
            printf("ID: %d\n", inv->vehiculos[i].id);
            printf("  Marca: %s\n", inv->vehiculos[i].marca);
            printf("  Modelo: %s\n", inv->vehiculos[i].modelo);
            printf("  Año: %d\n", inv->vehiculos[i].anio);
            printf("  Precio: $%.2f\n", inv->vehiculos[i].precio);
            printf("  Tipo: %s\n", inv->vehiculos[i].tipo);
            printf("  Color: %s\n", inv->vehiculos[i].color);
            printf("  Kilometraje: %.0f km\n", inv->vehiculos[i].kilometraje);
            printf("------------------------------------------------\n");
            disponibles++;
        }
    }
    
    if (disponibles == 0) {
        printf("No hay vehiculos disponibles en el inventario.\n");
    } else {
        printf("Total de vehiculos disponibles: %d\n", disponibles);
    }
}

void listar_todos_vehiculos(Inventario *inv) {
    printf("\n===== TODOS LOS VEHICULOS (DISPONIBLES Y VENDIDOS) =====\n");
    printf("========================================================\n");
    
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        printf("ID: %d\n", inv->vehiculos[i].id);
        printf("  %s %s (%d) - %s\n", 
               inv->vehiculos[i].marca,
               inv->vehiculos[i].modelo,
               inv->vehiculos[i].anio,
               inv->vehiculos[i].estado);
        printf("  Precio: $%.2f | %s | %d km\n",
               inv->vehiculos[i].precio,
               inv->vehiculos[i].tipo,
               (int)inv->vehiculos[i].kilometraje);
        printf("----------------------------------------\n");
    }
    
    printf("Total de vehículos: %d\n", inv->cantidad_vehiculos);
}

void actualizar_estado_vehiculo(Inventario *inv, int id, char nuevo_estado[]) {
    Vehiculo *v = buscar_vehiculo_por_id(inv, id);
    if (v == NULL) {
        printf("\n[ERROR] Vehiculo con ID %d no encontrado.\n", id);
        return;
    }
    
    strcpy(v->estado, nuevo_estado);
    printf("\n[EXITO] Estado del vehiculo %d actualizado a: %s\n", id, nuevo_estado);
}

void eliminar_vehiculo(Inventario *inv, int id) {
    int index = -1;
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (inv->vehiculos[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("\n[ERROR] Vehículo con ID %d no encontrado.\n", id);
        return;
    }
    
    if (strcmp(inv->vehiculos[index].estado, "Disponible") != 0) {
        printf("\n[ERROR] No se puede eliminar vehiculos que ya han sido vendidos.\n");
        return;
    }
    
    // Desplazar los vehículos posteriores
    for (int i = index; i < inv->cantidad_vehiculos - 1; i++) {
        inv->vehiculos[i] = inv->vehiculos[i + 1];
    }
    inv->cantidad_vehiculos--;
    
    printf("\n[EXITO] Vehiculo eliminado correctamente.\n");
}

void actualizar_precio_vehiculo(Inventario *inv, int id, float nuevo_precio) {
    Vehiculo *v = buscar_vehiculo_por_id(inv, id);
    if (v == NULL) {
        printf("\n[ERROR] Vehículo con ID %d no encontrado.\n", id);
        return;
    }
    
    printf("\nPrecio anterior: $%.2f\n", v->precio);
    v->precio = nuevo_precio;
    printf("Nuevo precio: $%.2f\n", nuevo_precio);
    printf("[EXITO] Precio actualizado correctamente.\n");
}

// ===== FUNCIONES DE GESTIÓN DE CLIENTES =====

void inicializar_clientes(BaseDatos_Clientes *bd_clientes) {
    bd_clientes->cantidad_clientes = 0;
}

void agregar_cliente(BaseDatos_Clientes *bd, char nombre[], char apellido[], 
                    char telefono[], char email[], char direccion[], float presupuesto) {
    if (bd->cantidad_clientes >= MAX_CLIENTES) {
        printf("\n[ERROR] Base de datos de clientes llena.\n");
        return;
    }
    
    if (!validar_email(email)) {
        printf("\n[ERROR] Email invalido.\n");
        return;
    }
    
    if (!validar_telefono(telefono)) {
        printf("\n[ERROR] Telefono invalido.\n");
        return;
    }
    
    Cliente c;
    c.id = bd->cantidad_clientes + 1;
    strcpy(c.nombre, nombre);
    strcpy(c.apellido, apellido);
    strcpy(c.telefono, telefono);
    strcpy(c.email, email);
    strcpy(c.direccion, direccion);
    c.presupuesto = presupuesto;
    
    bd->clientes[bd->cantidad_clientes] = c;
    bd->cantidad_clientes++;
    
    printf("\n[EXITO] Cliente agregado correctamente. ID: %d\n", c.id);
}

Cliente* buscar_cliente_por_id(BaseDatos_Clientes *bd, int id) {
    for (int i = 0; i < bd->cantidad_clientes; i++) {
        if (bd->clientes[i].id == id) {
            return &bd->clientes[i];
        }
    }
    return NULL;
}

void buscar_clientes_por_nombre(BaseDatos_Clientes *bd, char nombre[]) {
    printf("\n===== BUSQUEDA DE CLIENTES POR NOMBRE: %s =====\n", nombre);
    printf("================================================\n");
    
    int encontrados = 0;
    for (int i = 0; i < bd->cantidad_clientes; i++) {
        if (strstr(bd->clientes[i].nombre, nombre) != NULL) {
            printf("ID: %d | %s %s | Tel: %s | Presupuesto: $%.2f\n",
                   bd->clientes[i].id,
                   bd->clientes[i].nombre,
                   bd->clientes[i].apellido,
                   bd->clientes[i].telefono,
                   bd->clientes[i].presupuesto);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron clientes con ese nombre.\n");
    }
}

void listar_clientes(BaseDatos_Clientes *bd) {
    printf("\n===== LISTA DE CLIENTES =====\n");
    printf("==============================\n");
    
    for (int i = 0; i < bd->cantidad_clientes; i++) {
        printf("ID: %d\n", bd->clientes[i].id);
        printf("  Nombre: %s %s\n", bd->clientes[i].nombre, bd->clientes[i].apellido);
        printf("  Teléfono: %s\n", bd->clientes[i].telefono);
        printf("  Email: %s\n", bd->clientes[i].email);
        printf("  Dirección: %s\n", bd->clientes[i].direccion);
        printf("  Presupuesto: $%.2f\n", bd->clientes[i].presupuesto);
        printf("------------------------------\n");
    }
    
    printf("Total de clientes: %d\n", bd->cantidad_clientes);
}

void actualizar_cliente(BaseDatos_Clientes *bd, int id, char nombre[], char apellido[], 
                       char telefono[], char email[], char direccion[], float presupuesto) {
    Cliente *c = buscar_cliente_por_id(bd, id);
    if (c == NULL) {
        printf("\n[ERROR] Cliente con ID %d no encontrado.\n", id);
        return;
    }
    
    strcpy(c->nombre, nombre);
    strcpy(c->apellido, apellido);
    strcpy(c->telefono, telefono);
    strcpy(c->email, email);
    strcpy(c->direccion, direccion);
    c->presupuesto = presupuesto;
    
    printf("\n[EXITO] Datos del cliente actualizados correctamente.\n");
}

void eliminar_cliente(BaseDatos_Clientes *bd, int id) {
    int index = -1;
    for (int i = 0; i < bd->cantidad_clientes; i++) {
        if (bd->clientes[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("\n[ERROR] Cliente con ID %d no encontrado.\n", id);
        return;
    }
    
    for (int i = index; i < bd->cantidad_clientes - 1; i++) {
        bd->clientes[i] = bd->clientes[i + 1];
    }
    bd->cantidad_clientes--;
    
    printf("\n[EXITO] Cliente eliminado correctamente.\n");
}

// ===== FUNCIONES DE TRANSACCIONES =====

void inicializar_transacciones(Registro_Transacciones *reg) {
    reg->cantidad_transacciones = 0;
}

void registrar_venta(Registro_Transacciones *reg, Inventario *inv, 
                    BaseDatos_Clientes *bd, int id_cliente, int id_vehiculo, float descuento) {
    if (reg->cantidad_transacciones >= MAX_TRANSACCIONES) {
        printf("\n[ERROR] Límite de transacciones alcanzado.\n");
        return;
    }
    
    Cliente *c = buscar_cliente_por_id(bd, id_cliente);
    if (c == NULL) {
        printf("\n[ERROR] Cliente no encontrado.\n");
        return;
    }
    
    Vehiculo *v = buscar_vehiculo_por_id(inv, id_vehiculo);
    if (v == NULL) {
        printf("\n[ERROR] Vehículo no encontrado.\n");
        return;
    }
    
    if (strcmp(v->estado, "Disponible") != 0) {
        printf("\n[ERROR] Vehículo no está disponible para venta.\n");
        return;
    }
    
    float monto_final = v->precio * (1 - descuento / 100.0);
    
    if (monto_final > c->presupuesto) {
        printf("\n[ADVERTENCIA] El cliente no tiene presupuesto suficiente.\n");
        printf("Presupuesto: $%.2f | Monto final: $%.2f\n", c->presupuesto, monto_final);
        return;
    }
    
    Transaccion t;
    t.id = reg->cantidad_transacciones + 1;
    t.id_cliente = id_cliente;
    t.id_vehiculo = id_vehiculo;
    t.monto_final = monto_final;
    obtener_fecha_actual(t.fecha);
    
    reg->transacciones[reg->cantidad_transacciones] = t;
    reg->cantidad_transacciones++;
    
    // Actualizar estado del vehículo
    strcpy(v->estado, "Vendido");
    
    // Actualizar presupuesto del cliente
    c->presupuesto -= monto_final;
    
    printf("\n===== VENTA REGISTRADA EXITOSAMENTE =====\n");
    printf("ID Transaccion: %d\n", t.id);
    printf("Cliente: %s %s\n", c->nombre, c->apellido);
    printf("Vehiculo: %s %s (%d)\n", v->marca, v->modelo, v->anio);
    printf("Precio original: $%.2f\n", v->precio);
    printf("Descuento: %.1f%%\n", descuento);
    printf("Monto final: $%.2f\n", monto_final);
    printf("Fecha: %s\n", t.fecha);
    printf("==========================================\n");
}

void listar_transacciones(Registro_Transacciones *reg) {
    printf("\n===== REGISTRO DE TRANSACCIONES =====\n");
    printf("=====================================\n");
    
    for (int i = 0; i < reg->cantidad_transacciones; i++) {
        printf("Transacción ID: %d\n", reg->transacciones[i].id);
        printf("  Cliente ID: %d | Vehículo ID: %d\n", 
               reg->transacciones[i].id_cliente,
               reg->transacciones[i].id_vehiculo);
        printf("  Monto: $%.2f\n", reg->transacciones[i].monto_final);
        printf("  Fecha: %s\n", reg->transacciones[i].fecha);
        printf("-------------------------------------\n");
    }
    
    printf("Total de transacciones: %d\n", reg->cantidad_transacciones);
}

float calcular_ingresos_totales(Registro_Transacciones *reg) {
    float total = 0;
    for (int i = 0; i < reg->cantidad_transacciones; i++) {
        total += reg->transacciones[i].monto_final;
    }
    return total;
}

// ===== FUNCIONES DE BÚSQUEDA AVANZADA =====

void buscar_vehiculos_para_cliente(Inventario *inv, Cliente *cliente, 
                                   char marca_preferida[], char tipo[]) {
    printf("\n===== VEHICULOS RECOMENDADOS PARA %s %s =====\n", cliente->nombre, cliente->apellido);
    printf("Presupuesto: $%.2f\n", cliente->presupuesto);
    printf("=================================================\n");
    
    int encontrados = 0;
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        Vehiculo *v = &inv->vehiculos[i];
        if (strcmp(v->estado, "Disponible") == 0 && 
            v->precio <= cliente->presupuesto &&
            strcmp(v->marca, marca_preferida) == 0 &&
            strcmp(v->tipo, tipo) == 0) {
            printf("ID: %d | %s %s (%d) | $%.2f | %d km\n",
                   v->id, v->marca, v->modelo, v->anio, v->precio, (int)v->kilometraje);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No hay vehiculos disponibles que coincidan con los criterios.\n");
    } else {
        printf("Total recomendado: %d vehiculos\n", encontrados);
    }
}

void mostrar_estadisticas_inventario(Inventario *inv) {
    printf("\n===== ESTADISTICAS DEL INVENTARIO =====\n");
    printf("=======================================\n");
    
    int disponibles = 0, vendidos = 0;
    float valor_total = 0, promedio_precio = 0;
    
    for (int i = 0; i < inv->cantidad_vehiculos; i++) {
        if (strcmp(inv->vehiculos[i].estado, "Disponible") == 0) {
            disponibles++;
        } else {
            vendidos++;
        }
        valor_total += inv->vehiculos[i].precio;
    }
    
    if (inv->cantidad_vehiculos > 0) {
        promedio_precio = valor_total / inv->cantidad_vehiculos;
    }
    
    printf("Total de vehículos: %d\n", inv->cantidad_vehiculos);
    printf("  - Disponibles: %d\n", disponibles);
    printf("  - Vendidos: %d\n", vendidos);
    printf("\nValor total del inventario: $%.2f\n", valor_total);
    printf("Precio promedio: $%.2f\n", promedio_precio);
    printf("=======================================\n");
}

// ===== FUNCIONES AUXILIARES =====

void obtener_fecha_actual(char fecha[]) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, MAX_STRING, "%d/%m/%Y %H:%M:%S", tm_info);
}

int validar_email(char email[]) {
    int tiene_arroba = 0;
    int tiene_punto = 0;
    
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') tiene_arroba++;
        if (email[i] == '.') tiene_punto++;
    }
    
    return (tiene_arroba == 1 && tiene_punto >= 1);
}

int validar_telefono(char telefono[]) {
    if (strlen(telefono) < 7) return 0;
    
    for (int i = 0; telefono[i] != '\0'; i++) {
        if ((telefono[i] < '0' || telefono[i] > '9') && telefono[i] != '+' && telefono[i] != '-') {
            return 0;
        }
    }
    return 1;
}
