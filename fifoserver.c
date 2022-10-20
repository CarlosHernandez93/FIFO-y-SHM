/* Filename: fifoserver.c */
/* Servidor named pipe (FIFO) */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "SERV_CLI"

#define FIFO_FILE2 "CLI_SERV"

int main() {
	
   //descriptor de acrhivo del named pipe:	
   int fd;
   
   //buffer del lectura:
   char readbuf[100];
   
   //cadena de fin de comunicación:
   char end[10];
   
   //terminar lectura?
   int to_end;
   
   //bytes leídos
   int read_bytes;

   //longitd de la cadena
   int stringlen;
   
   /* crear el named pipe (FIFO) si no existe */
   mknod(FIFO_FILE, S_IFIFO|0640, 0);
   
   strcpy(end, "end");
   
   while(1) {
      //Cambio al modo de solo lectura
      fd = open(FIFO_FILE, O_RDONLY);
   
      read_bytes = read(fd, readbuf, sizeof(readbuf));
   
      readbuf[read_bytes] = '\0';
   
      printf("\nCadena recibidas: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf),sizeof(readbuf));
   
      to_end = strcmp(readbuf, end);
   
      if (to_end == 0) {
         close(fd);
         break;
      }

      close(fd);

      //Cambio al modo de solo escritura
      fd = open(FIFO_FILE, O_WRONLY);

      printf("\nIngrese cadena: ");
   
      fgets(readbuf, sizeof(readbuf), stdin);
   
      stringlen = strlen(readbuf);
   
      readbuf[stringlen - 1] = '\0';
   
      to_end = strcmp(readbuf, end);
      
      //printf("end_process is %d\n", end_process);
      if (to_end != 0) {
         write(fd, readbuf, strlen(readbuf));
         printf("\nCadena enviada: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf), sizeof(readbuf));
      } else {
         write(fd, readbuf, strlen(readbuf));
         printf("\nCadena enviada: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf), sizeof(readbuf));
         close(fd);
         break;
      }

      close(fd);
   }
   
   return 0;
}