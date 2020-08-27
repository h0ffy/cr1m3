<?php
	require_once("config.php");

	function __test_geoip() {
		if(extension_loaded('geoip')==1)
			return "OK";

		return "NO";

	}

	function __test_mcrypt() {
		$salt = "test";
		$text = $salt;

		if(extension_loaded('mcrypt')==1) {
			return "OK";
		}
		else {
			$a = base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $text, MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND)));

			if(strlen($a)==0) {
				return "NO";
			}
			else {
				return "OK";
			}
		}
					

		return "NO";
	}

	function __test_socket() {
		$fsock = fsockopen(gethostbyname(TEST_SOCKET_HOST),80);
		$http = "GET / HTTP/1.1\r\nHost: " . TEST_SOCKET_HOST . "\r\nConnection: Close\r\n\r\n";
		if(!$fsock) {
			return "NO";
		}

		if(fwrite($fsock, $http)===FALSE) {
			fclose($fsock);
			return "NO";
		}

		if(!feof($fsock)) {
			if(fread($fsock, 2048)===FALSE) {
				fclose($sock);
				return "PARTIAL";
			}

			else {
				fclose($sock);
				return "OK";
			}

		}

		return "PARTIAL";
	}


        function __test_file_write($file_path) {
                $file = fopen($file_path,"w");
                $stat = 0;
                if($file==0) {
                        return "NO";
                }
                else {
                        $stat = fwrite($file, "test it", 7);
                        if($stat==0) {
				fclose($file);
                                return "NO";
                        }
                        else {
                                fclose($file);
				return "OK";
                        }

                }

		fclose($file);
                return "NO";
        }


	function __test_unlink($file_path) {
		if(unlink($file_path)==true)
			return "OK";
		else
			return "NO";		
	}
	
        function __test_file_read($file_path) {
                $file = fopen($file_path, "r");

                if($file==0) {
                        return "NO";
                }

                else {
                        $ret = fread($file, 10);
                        if(strlen($ret)!=0) {
				fclose($file);
                                return "OK";
                        }
                        else {
				fclose($file);
                                return "PARTIAL";
                        }

                }

		fclose($file);
                return "NO";
        }

        function __test_mysql() {
                $mysql = mysql_connect(DB_HOST, DB_USER, DB_PASS);
                if($mysql==FALSE) {
                        return "NO";
                }

                mysql_close($mysql);
                return "OK";
        }


?>
