#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>

int PORT;char path[30];

char webpage[15000] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-length: 800\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n";

void configparser(){
    char conf[100];
    PORT = 0;
    FILE *f = fopen("conf.txt","r");
    fseek(f,5,SEEK_SET);
    fscanf(f,"%d",&PORT);
    fseek(f,18,SEEK_SET);
    char c;int l =0;
    do {
        c = fgetc(f);
        path[l] = c;
        l++;
    } while(c!=EOF);
    path[l-2]='\0';
    fclose(f);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    struct stat stat_buf;
    int fd_server, fd_client;
    char buf[2048];
    char param[11];
    char ch;
    int fdimg;
    int on = 1;
    configparser();
    printf("port : %d\n",PORT);
    printf("path to webpages: %s\n",path);
    fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server < 0)
    {
        perror("socket");
        exit(1);
    }
    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr =  INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(fd_server);
        exit(1);
    }
    if (listen(fd_server, 10) == -1)
    {
        perror("listen");
        close(fd_server);
        exit(1);
    }

    while(1)
    {
        fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);
        if (fd_client == -1)
        {
            perror("Connection failed......\n");
            continue;
        }
        printf("Got client connection.......\n");

        if (!fork())
        {
            close(fd_server);
            memset(buf, 0, 2048);
            read(fd_client, buf, 2047);
            printf("%s\n",buf);    
            int z = 85;
            if(strstr(buf,"homepage")){
                printf("request for homepage\n");
                char newpath[] = "";
                strcpy(newpath,path);
                strcat(newpath,"/homepage.html");
                FILE *f = fopen(newpath,"r");
                do {
                    ch = fgetc(f);
                    webpage[z] = ch;
                    z++;
                } while (ch != EOF);
                fclose(f);
            } else if(strstr(buf,"rakshitimage")){
                printf("request for image\n");
                char newpath[] = "";
                strcpy(newpath,path);
                strcat(newpath,"/secondarypage.html");
                FILE *f = fopen(newpath,"r");
                do {
                    ch = fgetc(f);
                    webpage[z] = ch;
                    z++;
                } while (ch != EOF);
                fclose(f);
            } else {
                char newpath[] = "";
                strcpy(newpath,path);
                strcat(newpath,"/index.html");
                FILE *f = fopen(newpath,"r");
                printf("request for index page\n");
                do {
                    ch = fgetc(f);
                    webpage[z] = ch;
                    z++;
                } while (ch != EOF);
                fclose(f);
            }
            webpage[z-1] = '\0';
            write(fd_client, webpage, sizeof(webpage) - 1);
            close(fd_client);
            printf("closing....\n");
            exit(0);
        }
        close(fd_client);
    }
    return 0;
}