<?php
	require_once("config.php");

        function __login_new_session($token) {
                session_start();
		$_SESSION['token'] = $token;

		header("Location: main.php");

        }

        function __login_status() {
		session_start();
		$ip = $_SERVER['REMOTE_ADDR'];
		$sum = md5(LOGIN_USER . LOGIN_PASS . $ip);

                if(!isset($_SESSION['token'])) {
	                   return false;
                }
		else {
			if($_SESSION['token']==$sum) {
		                return true;
			}
		}
	
		return false;
        }


	function __login_logged() {
	        session_start();
                $ip = $_SERVER['REMOTE_ADDR'];
                $sum = md5(LOGIN_USER . LOGIN_PASS . $ip);
        	if(!session_is_registered($sum)) {
                	$location = "Location: login.php";
                	header($location);
                	return false;
                }
                else {
			return true;
                }

           return false;
        }

        function __login_close() {
		session_start();
		$_SESSION['token']="";
		unset($_SESSION['token']);
                session_destroy();
        }
?>
