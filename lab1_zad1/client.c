#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
//======================================================================
int error( int ern, const char *err ){
	perror( err );
	return ern;
}
//======================================================================
int main( void )
{
	/* zmienne predefiniowane *****************************************/
	int  	port   = 12345;
	char 	host[] = "127.0.0.1";
	/* zmienne niezainicjowane ****************************************/
    int 	fd, n;
    struct 	sockaddr_in serv_addr;
    struct 	hostent *server;
    char 	buffer[256];
    
    /* tworzymy gniazdo ***********************************************/
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (fd < 0) 
        return error( 1, "socket()");
  
	/* pobieramy informacje o serwerze ********************************/
    server = gethostbyname( host );
  
    if( server == NULL )
		return error( 2, "gethostbyname()" );
    
    /* zapelniamy strukture zerami (inicjujemy) ***********************/
    bzero((char *) &serv_addr, sizeof(serv_addr));
    bzero( buffer, 256 );
    
    
    /* przypisujemy parametry *****************************************/
    serv_addr.sin_family = AF_INET;			// typ gniazda 
    serv_addr.sin_port = htons(port);		// port
    
    bcopy( (char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length );
    
    /* nawiazujemy polaczenie *****************************************/
    
    if( connect( fd, (struct sockaddr *) &serv_addr, sizeof( serv_addr ) ) < 0 ) 
        return error( 3, "connect()" );
    
    
        scanf("%s", &buffer);
    buffer[strlen(buffer)] = '\0';
        n = write( fd, buffer, sizeof( buffer ) );
                if( n < 0 ) 	// sprawdzamy, czy wystapil blad ....
                    perror( "write()" );
    
	/* zerujemy bufor *************************************************/
        bzero( buffer, 256 );
    
    /* odczytujemy wiadomosc ******************************************/
    /*n = read( fd, buffer, 255 );
    if (n < 0) 
         return error( 4, "read()" );*/
    
	/* wypisujemy wiadomosc *******************************************/
    //printf( "%s\n", buffer );
    
    /* konczymy polaczenie ********************************************/
    close(fd);
    
    //------------------------------------------------------------------
    return 0;
}
//======================================================================
