#include "stdio.h"       //printf
#include "sys/socket.h"  //socket
#include "sys/types.h"  //socket
#include "netinet/in.h" // sockaddr_in
#include "string.h"     //bzero
#include <unistd.h>     //close socket
#define SERVER_PORT 13
#define BUFFER_SIZE 1024
#define MSG_SIZE 100
int main()
{
  struct sockaddr_in service_address;
  bzero(&service_address,sizeof(service_address));
  service_address.sin_family = PF_INET;
  service_address.sin_addr.s_addr = INADDR_ANY;
  service_address.sin_port = htons(13);
  //create socket server  address
  int socket_fd = socket(PF_INET,SOCK_STREAM,0);
  if(socket_fd <0){
    printf("%s","create socket fail");
  }
  int opt = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
       printf("%s","无法设置套接字的“重新使用端口”选项");
  }
  // bind
  if( bind(socket_fd,(struct sockaddr*)&service_address,sizeof(service_address))) {
        printf("Server Bind Port : %d Failed!", SERVER_PORT);
  }
  //listen
  if(listen(socket_fd,5) == -1 ){
     printf("%s","listen fail\n");  
  }
  while(1){
      struct sockaddr_in client_addr;
      socklen_t length = sizeof(client_addr);
      int new_socket_fd = accept(socket_fd,(struct sockaddr*)&client_addr,&length);
      if ( new_socket_fd < 0)
      {
          printf("Server Accept Failed!\n");
         break;
      }
      char client_msg[BUFFER_SIZE];
      bzero(client_msg, BUFFER_SIZE);
      length = recv(new_socket_fd,client_msg,BUFFER_SIZE,0);
      if (length < 0)
      {
          printf("Server Recieve Data Failed!\n");
          break;
      }
      char responseMsg[MSG_SIZE];
      bzero(responseMsg,MSG_SIZE);
      strcpy(responseMsg ,"had received:");
      strcat(responseMsg,client_msg);
      printf("%s",responseMsg);
      //发送buffer中的字符串到new_server_socket,实际是给客户端
      if(send(new_socket_fd,responseMsg,strlen(responseMsg),0)<0)
      {
          printf("Send msg Failed\n");
          break;
      }
      //关闭与客户端的连接
      close(new_socket_fd);
   }
   close(socket_fd);
   return 0;
}
