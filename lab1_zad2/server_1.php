#!/usr/bin/php

<?php
	#===================================================================
	# Wersja z wywolaniami zblizonymi do C
	#===================================================================
	
	# zmienne predefiniowane -------------------------------------------
	$host = "127.0.0.1";
	$port = 12345;
	
	# tworzymy gniazdo -------------------------------------------------
	if( ! ( $server = socket_create( AF_INET, SOCK_STREAM, SOL_TCP ) ) ){
		print "socket_create(): " 		. socket_strerror( socket_last_error( $server ) ) . "\n";
		exit( 1 );
	}
	
	# ustawiamy opcje gniazda (REUSEADDR) ------------------------------
	if( ! socket_set_option($server, SOL_SOCKET, SO_REUSEADDR, 1) ) {
		print "socket_set_option(): " 	. socket_strerror(socket_last_error( $server ) ) . "\n";
		exit( 1 );
	}
	
	# mapujemy gniazdo (na port) ---------------------------------------
	if( ! socket_bind( $server, $host, $port ) ){
		print "socket_bind(): " 		. socket_strerror( socket_last_error( $server ) ) . "\n";
		exit( 1 );
	}
	
	# ustawiamy gniazdo w tryb nasluchiwania ---------------------------
	if( ! socket_listen( $server, 5 ) ){
		print "socket_listen(): " 		. socket_strerror( socket_last_error( $server ) ) . "\n";
		exit( 1 );
	}
	
	while( 1 ){

		$pid = pcntl_fork();
        if ($pid == -1) {
            die('could not fork');
        } else if ($pid) {
            # parent
            pcntl_wait($status);
        } else {
            # child
            $client = socket_accept( $server );
            $pidch = getmypid();
            $nazwa = $pidch . ".txt";
            print "Podproces o PID: $pidch\n";
            socket_getpeername( $client, $addr, $port );
		print "Addres: $addr Port: $port\n";
            $msg = ""; 
        while( $rcv = socket_read( $client, 2) ){ 
            $msg .= $rcv;
        }
        $hex = '';
        $hex = bin2hex($msg);
        file_put_contents($nazwa, $hex);
		print "$hex\n";
		socket_close( $client );
        }
		
		
	}
	#-------------------------------------------------------------------
	socket_close( $server );
	#===================================================================
?>
