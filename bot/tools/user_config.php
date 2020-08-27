<?php


	var_dump($argv);

	if(empty($argv[1]) || empty($argv[2])) {
		echo("php " . $argv[0] . " <user> <pass>");
		exit(0);
	}
	
	$text = $argv[1];
	$pass = $argv[2];

	$user = base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $pass, $text, MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND)));
       //mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $pass, base64_decode($text), MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND)));




	$str1 = "define('LOGIN_USER', '" . $user  .  "');";			
	$str2 = "define('LOGIN_PASS', '" . md5($pass)  .  "');";


	echo($str1 . "\n");
	echo($str2 . "\n");

?>
