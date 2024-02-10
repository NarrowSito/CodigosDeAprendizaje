#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// Declarar estructura de las tareas y funciones que se utilizan
// -------------------------
struct tarea {
  char estado;
  char eliminado;
  char entregaDia[10];
  char materia[10];
  char descripcion[300];
};
void filtroTar();
void imprimirFiltro(int);
void mostrarMenu();
void clearS(); // funcion para limpiar la pantalla :3
void procesoMenu(int);
void agregarTar();
void imprimiTar();
void eliminarTar();
void editarTar();
void imprimirETar();
void casoEditar(char, struct tarea[10], int);

int main() {
  int seleccion;
  do {
    clearS();
    mostrarMenu();
    scanf("%i", &seleccion);
    getchar();
    procesoMenu(seleccion);
    printf("presiona enter para continuar\n");
    getchar();
  } while (seleccion != 6);
  clearS();
  return 0;
}
// Mostrar y procesar la opcion del menu
// -----------------------------------------
void mostrarMenu() {
  printf("\n\t== Organiza tus pendientes :D ==\n");
  printf("Presiona lo que se indica entre [] y luego enter para seleccionar\n");
  printf("\n[1] Agregar tarea nueva.\n");
  printf("[2] Mostrar todas las tareas.\n");
  printf("[3] Filtrar tareas.\n");
  printf("[4] Eliminar tarea\n");
  printf("[5] Editar tarea\n");
  printf("[6] Salir.\n");
  printf("---> ");
}
// impiar pantalla
// ----------------------------------------------------------------
void clearS() {
  int boolean;
  boolean = system("cls");
  if (boolean != 0) {
    boolean = system("clear");
    if (boolean != 0) {
      printf("Error por falta de acceso\n");
    }
  }
}
// limpiar pantalla
// --------------------------------------------------------------- Mostrar y
// procesar menu --------------------------------------------------------
void procesoMenu(int seleccion) {
  switch (seleccion) {
  case 1:
    printf("Seleccion 1\n");
    agregarTar();
    break;
  case 2:
    printf("Seleccion 2\n");
    imprimiTar();
    break;
  case 3:
    printf("Seleccion 3\n");
    filtroTar();
    break;
  case 4:
    printf("Holis es el 4\n");
    eliminarTar();
    break;
  case 5:
    printf("Seleccion 5\n");
    editarTar();
    break;
  case 6:
    printf("saliendo ...\n");
    break;
  default:
    printf("Seleccion invalida intentelo de nuevo\n");
  }
}
// Agregar tareas al archivo
// -----------------------------------------------------
void agregarTar() {
  clearS();
  FILE *writer = fopen("tareas.txt", "a");
  if (writer == NULL) {
    printf("Error falta de permisos...\n");
    exit(0);
  } else {
    int i, longitud;
    struct tarea nuevaTar;
    // llenado de datos del struct
    nuevaTar.eliminado = '0';
    printf("\nTarea a hacer: ");
    fgets(nuevaTar.descripcion, 298, stdin);

    printf("\nTeclee su estado [U]rgente | [P]endiente: ");
    scanf("%c", &nuevaTar.estado);
    getchar();
    printf("\nTeclee la materia (maximo 6 caracteres): ");
    fgets(nuevaTar.materia, 8, stdin);
    getchar();
    printf("\nTeclee un dia de entrega (maximo 6 caracteres): ");
    fgets(nuevaTar.entregaDia, 8, stdin);
    getchar();
    // agregar salto de linea al final de la descripcion
    longitud = sizeof(nuevaTar.descripcion) / sizeof(nuevaTar.descripcion[0]);
    for (i = longitud - 1; i >= 0; i--) {
      if (nuevaTar.descripcion[i] == '\n') {
        nuevaTar.descripcion[i] = '\0';
      }
    }
    if (nuevaTar.descripcion[longitud - 1] == '\0') {
      nuevaTar.descripcion[longitud - 1] = '\n';
    }
    // longitud de entregaDia
    longitud = sizeof(nuevaTar.entregaDia) / sizeof(nuevaTar.entregaDia[0]);
    // for para limpiar los \n
    for (i = longitud - 1; i >= 0; i--) {
      if ('\n' == nuevaTar.entregaDia[i]) {
        nuevaTar.entregaDia[i] = '\0';
        break;
      }
    }
    // longitud de materia
    longitud = sizeof(nuevaTar.materia) / sizeof(nuevaTar.materia[0]);
    // for para limpiar \n
    for (i = longitud - 1; i >= 0; i--) {
      if ('\n' == nuevaTar.materia[i]) {
        nuevaTar.materia[i] = '\0';
      }
    }
    // Hacer siempre Mayuscula el estado
    nuevaTar.estado = toupper(nuevaTar.estado);
    // Hacer siempre minuscula la Materia
    for (i = 0; nuevaTar.materia[i] != '\0'; i++) {
      nuevaTar.materia[i] = tolower(nuevaTar.materia[i]);
    }
    // hacer mayuscula el dia de entrega
    for (i = 0; nuevaTar.entregaDia[i] != '\0'; i++) {
      nuevaTar.entregaDia[i] = toupper(nuevaTar.entregaDia[i]);
    }
    i = fwrite(&nuevaTar, sizeof(struct tarea), 1, writer);
    if (i == 1) {
      printf("Tarea agregada correctamente\n");
    }
  }
  fclose(writer);
}
// Mostrar tareas guardadas
// ------------------------------------------------------
void imprimiTar() {
  clearS();
  FILE *reader = fopen("tareas.txt", "r");
  if (reader == NULL) {
    printf("Error falta de permisos\n");
  } else {
    struct tarea lector;
    int i, counter;
    // while para imprimir esta wea xd
    printf("Formato de las tareas:\nDescripcion | Estado | Dia de entrega | "
           "Materia |\n\n");
    while (feof(reader) == 0) {
      counter = fread(&lector, sizeof(struct tarea), 1, reader);
      // quitamos el ultimo enter que se gaurdaba en el txt
      for (i = 299; i <= 0; i--) {
        if (lector.descripcion[i] == '\n') {
          lector.descripcion[i] = '\0';
          break;
        }
      }
      if (lector.eliminado == '0' && counter == 1) {
        printf("%s | %c | %s | %s \n\n", lector.descripcion, lector.estado,
               lector.entregaDia, lector.materia);
      }
    }
  }
  fclose(reader);
}
// Filtrar tareas
// ----------------------------------------------------------------
void imprimirFiltro(int request) {
  FILE *reader = fopen("tareas.txt", "r");
  if (reader == NULL) {
    printf("Falta de permisos o archivo inexistente...\n");
  } else {
    struct tarea lector;
    int imprimir;
    char estadoB, matDiaB[10];
    switch (request) {
    case 1:
      printf("Dame el estado a filtrar: ");
      scanf("%c", &estadoB);
      getchar();
      estadoB = toupper(estadoB);
      while (!(feof(reader))) {
        imprimir = fread(&lector, sizeof(struct tarea), 1, reader);
        if (estadoB == lector.estado && imprimir == 1) {
          printf("%s | %c | %s | %s \n\n", lector.descripcion, lector.estado,
                 lector.entregaDia, lector.materia);
        }
      }
      break;
    case 2:
      printf("Escribe minimo 3 letras en la materia que asignaste: ");
      fgets(matDiaB, 10, stdin);
      getchar();
      for (int i = 0; i < 10; i++) {
        if (matDiaB[i] == '\n') {
          matDiaB[i] = '\0';
        }
        matDiaB[i] = tolower(matDiaB[i]);
      }
      while (!(feof(reader))) {
        imprimir = fread(&lector, sizeof(struct tarea), 1, reader);
        if ((matDiaB[0] == lector.materia[0] &&
                 matDiaB[1] == lector.materia[1] &&
                 matDiaB[2] == lector.materia[2] ||
             matDiaB[3] == lector.materia[3]) &&
            (lector.eliminado == '0') && (imprimir == 1)) {
          printf("%s | %c | %s | %s \n\n", lector.descripcion, lector.estado,
                 lector.entregaDia, lector.materia);
        }
      }

      break;
    case 3:
      printf("Escribe por lo menos 3 letras que se puso en el dia: ");
      fgets(matDiaB, 10, stdin);
      getchar();
      for (int i = 0; i < 10; i++) {
        if (matDiaB[i] == '\n') {
          matDiaB[i] = '\0';
        }
        matDiaB[i] = toupper(matDiaB[i]);
      }
      while (!(feof(reader))) {
        imprimir = fread(&lector, sizeof(struct tarea), 1, reader);
        if ((matDiaB[0] == lector.entregaDia[0] &&
                 matDiaB[1] == lector.entregaDia[1] &&
                 matDiaB[2] == lector.entregaDia[2] ||
             matDiaB[3] == lector.entregaDia[3]) &&
            (lector.eliminado == '0') && (imprimir == 1))
          printf("%s | %c | %s | %s \n\n", lector.descripcion, lector.estado,
                 lector.entregaDia, lector.materia);
      }
      break;
    default:
      printf("Opcion no valida...\n");
      break;
    }
  }
  fclose(reader);
}

void filtroTar() {
  clearS();
  int seleccion;
  printf("\nSeleccione como desea filtrar:\n");
  printf("[1] Estado\n");
  printf("[2] Materia\n");
  printf("[3] Dia de entrega\n");
  scanf("%i", &seleccion);
  getchar();
  imprimirFiltro(seleccion);
}

// eliminar tarea
// ----------------------------------------------------------------

void eliminarTar() {
  clearS();
  FILE *readwr = fopen("tareas.txt", "r+");
  int lectura, i, eliminar, limite, numTar;
  char confirmar;
  if (readwr == NULL) {
    printf("Archivo no encontrado error....");
  } else {
    struct tarea
        guardado[10]; // arreglo para guardar los posibles datos a eliminar
    while (feof(readwr) == 0) {

      for (i = 0; i < 10; i++) {
        lectura = fread(&guardado[i], sizeof(struct tarea), 1, readwr);
        if (lectura == 0) {
          limite = i;
          break;
        }
      }
      for (i = 0; i < limite; i++) {
        if (guardado[i].eliminado == '0') {
          printf("[%i] %s | %c\n\n", i + 1, guardado[i].descripcion,
                 guardado[i].estado);
        }
      }
      if (feof(readwr)) {
        printf("\nTeclee el numero entre [] para eliminar o [0] para cancelar "
               "no hay mas tareas: ");
      } else {
        printf("\nTeclee el numero entre [] para eliminar o [0] para cancelar "
               "o [11] para continuar: ");
      }
      scanf("%i", &eliminar);
      getchar();
      if ((eliminar - 1) > -1 &&
          (eliminar - 1) < 10) { // confirmar la eliminacion
        printf("\npresiona [S] para confirmar o [N] para cancelar\n");
        scanf("%c", &confirmar);
        getchar();
        confirmar = toupper(confirmar);
      }
      if ((eliminar - 1) >= -1 && (eliminar - 1) <= 10 && confirmar == 'S') {
        guardado[eliminar - 1].eliminado = '1';
        break;
      } else if (eliminar - 1 == -1) { // cancelar operacion
        printf("\n\nCancelando operacion...\n");
        break;
      }
    }
    // sobre escribir el dato actualizado
    if ((eliminar - 1) > -1 && (eliminar - 1) < 10) {
      numTar = eliminar - limite - 1; // tener cuantas veces mover el cursor
      fseek(readwr, (sizeof(struct tarea) * (numTar)), SEEK_CUR);
      fwrite(&guardado[eliminar - 1], sizeof(struct tarea), 1, readwr);
      printf("\n\nCambios realizados correctamente :3");
    }
  }
  fclose(readwr); // cerrar el puntero o pasan cositas :OOO
}
// -------------------------------------------------------------------------

// editar -------------------------------------------------------------------

void editarTar() {
  clearS();
  FILE *readwr = fopen("tareas.txt", "r+");
  if (readwr == NULL) {
    printf("Error falta de permisos\n");
  } else {
    struct tarea guardado[10];
    int i, limite, eliminar, posicion, leido;
    char eleccion;
    while (!(feof(readwr))) {
      for (i = 0; i < 10;
           i++) { // for para leer informacion en el struct y guardalo
        leido = fread(&guardado[i], sizeof(struct tarea), 1, readwr);
        if (leido == 0) {
          limite = i;
          break;
        }
      }
      for (i = 0; i < limite; i++) { // for para imprimir el arrego si es valido
        if (guardado[i].eliminado == '0') {
          printf("[%i] -> %s | %c | %s |\n", i + 1, guardado[i].descripcion,
                 guardado[i].estado, guardado[i].materia);
        }
      }
      if (!(feof(readwr))) {
        printf("Teclee el numnero entre [] o [0] para cancelar o [11] para "
               "continuar: ");
      } else {
        printf("Teclee el numero entre [] o [0] para cancelar no existen mas "
               "tareas:  ");
      }
      scanf("%i", &eliminar);
      getchar();
      if (eliminar > 0 && eliminar < 11) {
        break;
      }
    }
    imprimirETar();
    scanf("%c", &eleccion);
    getchar();
    casoEditar(eleccion, guardado,
               eliminar - 1); // modifica el eliminar elemento de guardado
    if ((eliminar - 1) >= -1 && (eliminar - 1) <= 10) {
      posicion = eliminar - limite - 1; // tener cuantas veces mover el cursor
      fseek(readwr, (sizeof(struct tarea) * (posicion)), SEEK_CUR);
      i = fwrite(&guardado[eliminar - 1], sizeof(struct tarea), 1, readwr);
      if (i == 1) {
        printf("\n\nCambios realizados correctamente :3\n");
      } else {
        printf("No se pudieron realizar los cambios intentelo de nuevo :c\n");
      }
    }
  }
  fclose(readwr);
}

void imprimirETar() {
  printf("\n=== Seleccione lo que desea EDITAR :O ===\n");
  printf("[D]ia de entrega\n");
  printf("[M]ateria asignada\n");
  printf("[E]stado de la tarea\n");
  printf("[T]area a realizar\n");
  printf("[C]ancelar\n");
  printf("--->");
}

void casoEditar(char eleccion, struct tarea guardado[10], int editar) {
  int i;
  switch (eleccion) {
  case 'd':
  case 'D':
    printf("Actual: %s\n", guardado[editar].entregaDia);
    printf("Ingresa el nuevo dia de entrega (maximo 6 caracteres): ");
    fgets(guardado[editar].entregaDia, 9, stdin);
    for (i = 8; i >= 0; i--) {
      if (guardado[editar].entregaDia[i] == '\n') {
        guardado[editar].entregaDia[i] = '\0'; // quitar el enter
        break;
      }
    }
    for (i = 0; i < 10; i++) {
      guardado[editar].entregaDia[i] = toupper(guardado[editar].entregaDia[i]);
    }
    break;
  case 'm':
  case 'M':
    printf("Actual: %s\n", guardado[editar].materia);
    printf("Ingresa la nueva materia (maximo 6 caracteres): ");
    fgets(guardado[editar].materia, 10, stdin);
    for (i = 9; i >= 0; i--) {
      if (guardado[editar].materia[i] == '\n') {
        guardado[editar].materia[i] = '\0'; // quitar el enter
        break;
      }
    }
    for (i = 0; i < 10; i++) {
      guardado[editar].materia[i] = tolower(guardado[editar].materia[i]);
    }
    break;
  case 'e':
  case 'E':
    printf("Actual: %c\n", guardado[editar].estado);
    printf("Ingresa el nuevo valor ([P]endiente | [U]rgente | [C]ompletado): ");
    scanf("%c", &guardado[editar].estado);
    getchar();
    guardado[editar].estado = toupper(guardado[editar].estado);
    break;
  case 't':
  case 'T':
    printf("Actual: %s\n", guardado[editar].descripcion);
    printf("Ingresa la nueva tarea: ");
    fgets(guardado[editar].descripcion, 297, stdin);
    for (i = 298; i >= 0; i--) {
      if (guardado[editar].descripcion[i] == '\n') {
        guardado[editar].descripcion[i] = '\0'; // quitar el enter
        
      }
      //i= sizeof(guardado[0].descripcion) / sizeof(guardado[0].descripcion[0]);
      //guardado[editar].descripcion[i-2] = '\n';
    }
    break;
  case 'c':
  case 'C':
    printf("Cancelando...\n");
    break;
  default:
    printf("Seleccion invalida\n");
    break;
  }
}
