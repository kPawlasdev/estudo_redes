# CÓDIGOS DISPONÍVEIS
Uma breve descrição de cada programa e como rodá-los.<br>(códigos compatíveis apenas com sistemas UNIX)
## sockcreate.c
### DESCRIÇÃO
Ao executar o programa no terminal, passando como argumento uma porta de rede _(ex: 8080)_, o sistema busca por endereços compatíveis com os critérios especificados em _hints_ e com a porta informada. Em seguida, cria uma socket (_L. 58_) e tenta vincular ela a um dos endereços encontrados (_L. 64_).  

Caso tenha sido possível vincular a socket a um endereço, imprime o _File Descriptor_ , o protocolo (IPv4 ou IPv6) e o endereço da socket.    
### USO
_Compilar:_  
`gcc sockcreate.c -o sockcreate`  
_Executar:_  
`./sockcreate port`  
### REFERÊNCIAS UTILIZADAS:
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/index.html)  
- _The Linux Programming Interface_ (Livro)
