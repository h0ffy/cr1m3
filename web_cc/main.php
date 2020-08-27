<?php
// pantalla principal
	require_once("mod_login.php");
	require_once("test.php");
	require_once("info.php");
	

        function __get_status($status) {
                switch($status) {
                        case "OK":
                        case "YES":
                                return("<a class=\"text_ok\"><b>OK</b></a>");
                                break;
                        case "PARTIAL":
                                return("<a class=\"text_partial\"><b>PARTIAL</b></a>");
                                break;
                        case "FALSE":
                        case "NO":
                                return("<a class=\"text_no\"><b>NO</b></a>");
                                break;
                        default:
                                break;
                }

                return 0;
        }



//main()

	if(__login_status()==false) {
		header("Location: login.php");
		return 0;	
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
		<li><a href="./main.php">Main</a></li>
		<li><a href="./list.php">Bots</a></li>
		<li><a href="./massive.php">Massive</a></li>
		<li><a href="./update.php">Update</a></li>
		<li><a href="./panic.php">Panic</a></li>
		<li><a href="./logout.php">Logout</a></li>
	</ul>
</nav>
<section>
	<article>
		<table>
			<tr>
				<th>Name</th>
				<th>Description</th>
				<th>Status</th>
			</tr>
			<tr>
				<td><b>Socket</b></td>
				<td>Open socket TCP connection</td>
				<td><?php echo(__get_status(__test_socket())); ?></td>
			</tr>
	
			<tr>
				<td><b>Write</b></td>
				<td>File write ./data/tmp.txt</td>
				<td><?php echo(__get_status(__test_file_write("data/tmp.txt"))); ?></td>
			</tr>
			<tr>
				<td><b>Read</b></td>
				<td>File read ./data/read_test</td>
				<td><?php echo(__get_status(__test_file_read("data/read_test"))); ?></td>
			</tr>

			<tr>
				<td><b>Unlink</b></td>
				<td>File remove ./data/tmp.txt</td>
				<td><?php echo(__get_status(__test_unlink("data/tmp.txt"))); ?></td>
			</tr>

			<tr>
				<td><b>MySQL</b></td>
				<td>Test Mysql Connect</td>
				<td><?php echo(__get_status(__test_mysql())); ?></td>
			</tr>
			<tr>
				<td><b>Mcrypt</b></td>
				<td>Test if mcrypt module loaded</td>
				<td><?php echo(__get_status("OK")); ?></td>
			</tr>
		</table>
	</article>
	<article>
		<table>
			<tr>
				<th>Name</th>
				<th>Value</th>
			</tr>
			<tr>
				<td>Server IP</td>
				<td><?php echo(__get_server_ip()); ?></td>
			</tr>
			<tr>
				<td>Client IP</td>
				<td><?php echo(__get_client_ip()); ?></td>
			</tr>
		</table>
	</article>
	

</section>

<footer>
	@cr1m3 // by h0ffy (JennyLab)
</footer>


</body>
</html>
