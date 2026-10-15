#include<sys/types.h>
#include<stdio.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sockfd, status, sair = 1;
    char ipstr[INET6_ADDRSTRLEN];

    if(argc != 2){
        fprintf(stderr, "Uso: sockcreate port\n");
        return -1;
    }

    memset(&hints, 0, sizeof hints);

    //critérios que serao utilizados posteriormente na funcao getaddrinfo()
    hints.ai_family = AF_UNSPEC; // qualquer tipo de endereço
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    /**
    * buscar por endereços de socket, que sejam compatíveis com os critérios
    * especificados em hints e com os argumentos da linha de comando,
    * guardando-os na variável result
    */
    status = getaddrinfo(NULL, argv[1], &hints, &result);
    if(status != 0){
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(status));
        return -1;
    }

    //para cada endereço encontrado pelo gai
    for(rp = result; rp != NULL; rp = rp->ai_next){
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        //verifica se é ipv4 ou ipv6
        if(rp->ai_family == AF_INET){
            ipv4 = (struct sockaddr_in*)rp->ai_addr;
            ipver = "IPv4";
            addr = &ipv4->sin_addr;
        }else{
            ipv6 = (struct sockaddr_in6*)rp->ai_addr;
            ipver = "IPv6";
            addr = &ipv6->sin6_addr;
        }

        inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);

        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(sockfd == -1){
            continue; //falha ao criar a socket, tentar com o proximo endereço
        }

        // tenta vincular a socket ao endereço
        if(bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0){
            printf("%-5s %-10s %-15s\n", "FD", "PROTOCOLO", "ENDERECO IP");
            printf("%-5d %-10s %-15s\n", sockfd, ipver, ipstr);
            printf("\nDIGITE 0 PARA SAIR\n");
            while(sair){
                scanf("%d", &sair);
            }
            break; //bind foi um sucesso, pular para fora do loop
        }
    }

    if(rp==NULL){
        printf("Falha ao conectar\n");
        return -1;
    }

    close(sockfd);
    freeaddrinfo(result);
    return 0;
}
