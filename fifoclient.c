/* fifoclient.c */
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

   //terminar lectura?
   int end_process;

   //longitd de la cadena
   int stringlen;

   //buffer del lectura:
   char readbuf[100];
   
   //cadena de fin de comunicación:
   char end_str[5];

   //bytes leídos
   int read_bytes;
 
   strcpy(end_str, "end");
   
   while (1) {
      //Cambio al modo de solo escritura
      fd = open(FIFO_FILE, O_WRONLY);

      printf("\nIngrese cadena: ");
   
      fgets(readbuf, sizeof(readbuf), stdin);
   
      stringlen = strlen(readbuf);
   
      readbuf[stringlen - 1] = '\0';
   
      end_process = strcmp(readbuf, end_str);
      
      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         write(fd, readbuf, strlen(readbuf));
         printf("\nCadena enviada: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf), sizeof(readbuf));
      } else {
         write(fd, readbuf, strlen(readbuf));
         printf("\nCadena enviada: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf), sizeof(readbuf));
         close(fd);
         break;
      }

      close(fd);

      //Cambio al modo de solo lectura
      fd = open(FIFO_FILE, O_RDONLY);
   
      read_bytes = read(fd, readbuf, sizeof(readbuf));
   
      readbuf[read_bytes] = '\0';
   
      printf("\nCadena recibidas: \"%s\" con longitud %d y tamaño de %zd bytes\n", readbuf, (int)strlen(readbuf), sizeof(readbuf));
   
      end_process = strcmp(readbuf, end_str);
   
      if (end_process == 0) {
         close(fd);
         break;
      }

      close(fd);
   }
   
   return 0;
}