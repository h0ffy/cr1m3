<?php

define('DB_HOST', '127.0.0.1');
define('DB_PORT', '3306');
define('DB_USER', 'root');
define('DB_PASS', 'jennylab');
define('DB_NAME', 'cr1m3');	
define('DB_TABLE_BOTS', 'bots');		//id: tabla con la informacion de los bots
define('DB_TABLE_TASK', 'task');
define('DB_TABLE_FILES', 'files_upload');	//id: tabla con archivos subidos
define('DB_TABLE_KEYLOGGER', 'keylogger');	//id: tabla con keylogger
define('DB_TABLE_SCREENSHOT', 'screenshot'); 	//id: tabla con token y nombre de archivo de la captura
define('DB_TABLE_SHELL', 'shell'); 	

define('LOGIN_USER', 'cr1m3_admin');			
define('LOGIN_PASS', '070edec4f5af4a9338743963435009af'); 	// md5('cr1m3');
define('LOGIN_RANDOM_SEED', '1337');				//semilla aleatoria para el token del login


define('UPLOAD_PATH', '/var/www/cr1m3/data/upload');
define('SCREEN_PATH', '/var/www/cr1m3/data/screenshot');
define('KEYLOG_PATH', '/var/www/cr1m3/data/keylog');

define('COMMAND_PREFIX', '!');					//perfijo del comando


define('MAIN_FILE', 'main.php');
define('LOGIN_FILE', 'login.php');

define('TEST_SOCKET_HOST', 'www.google.com');
define('TEST_SOCKET_PORT', '80');



?>

