#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define ERR_VALUE "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define ERR_INDEX "Error en los índices. Rango soportado: [1,9]\n"
#define ERR_NOT_SUPPORTED \
"Modo no soportado, el primer parámetro debe ser server o client\n​"
#define ERR_SERVER "Uso: ./tp server <host> <puerto>\n"
#define ERR_CLIENT "Uso: ./tp client <host> <puerto>\n"
#define VERIFY_OK "OK\n\0"
#define VERIFY_ERR  "ERROR\n\0"
#define ERR_INIT_VAL "La celda indicada no es modificable\n\0"
#endif  // MESSAGE_H_
