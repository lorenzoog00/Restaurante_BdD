# Sistema de Pedidos y Entrega de Comida

## Descripción
Este sistema permite a los usuarios registrarse y acceder a sus cuentas como cliente, gerente o repartidor. Cada tipo de cuenta tiene funcionalidades específicas, facilitando la gestión de pedidos y entregas de comida.

## Tipos de Cuentas
- **Cliente:** Puede modificar sus ajustes personales, realizar pedidos de comida y verificar el estado de sus pedidos.
- **Gerente:** Tiene la capacidad de revisar pedidos usando el ID del pedido o por estado, y modificar el estado de los pedidos.
- **Repartidor:** Puede ver los detalles de entrega como la dirección y el nombre del cliente, y actualizar el estado del pedido de 'en camino' a 'entregado'.

## Funcionalidades
### Cliente
- Cambiar ajustes (contraseña, dirección, etc.).
- Realizar pedidos de comida especificando platos y cantidades.
- Ver el precio total después de realizar el pedido.
- Verificar el estado de los pedidos.

### Gerente
- Buscar pedidos por ID o estado.
- Cambiar el estado de cualquier pedido.

### Repartidor
- Ver detalles de la entrega (dirección y nombre del cliente).
- Cambiar el estado del pedido de 'en camino' a 'entregado'.

## Tecnologías Utilizadas
- **Lenguaje de Programación:** C
- **Base de Datos:** SQL
