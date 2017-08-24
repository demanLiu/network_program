#include "stdio.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "string.h"
#include <arpa/inet.h>
#include <unistd.h>

#define MSG_SIZE 100
#define BUFF_SIZE 100
int main()
{
  char sendMsg[MSG_SIZE];
  printf("please input msg what you want:\n");
  scanf("%s",sendMsg);
  int socket_fd = socket(PF_INET,SOCK_STREAM,0);
  if(socket_fd <0){
    printf("create socket failed \n");
  }
  //客户端不需要绑定
  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = PF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //服务器端口号
  server_addr.sin_port = htons(13);
  if(connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
      printf("connect failed\n");
  }
  int send_flag = send(socket_fd,sendMsg,strlen(sendMsg),0);
  if(send_flag <0 ){
      printf("send failed\n");
  }
  char buff[BUFF_SIZE];
  bzero(&buff,sizeof(BUFF_SIZE));
  //接受服务器返回
  if(recv(socket_fd,buff,BUFF_SIZE,0)){
    printf("server response:%s",buff);
  }
  close(socket_fd);

}
