<?php
	function __security_input($str, $show) {
		$valid_chars = "abcdefghijkmlnopqrstuvwxyz=^;:@-%/\\&?.,_<>\"()\x20\xa4\n\r";
		$a = 0;
		$sec=0;
		$i=0;

		if(empty($str))
			return($str);
		
		$str_tmp = strtolower($str);

		for($a=0;$a<=strlen($str);$a++) { // main for through all input str
			$i=0;
			for($i=0;$i<=strlen($valid_chars);$i++) { // loop compare chars (loop through all valid chars)
				if(substr($str_tmp, $a, 1)==substr($valid_chars,$i,1)) {
					$sec=1;
					continue;
	
				}
				else if(is_numeric(substr($str_tmp, $a, 1))==true) {
					$sec=1;
					continue;
				}
			}

			
			if($sec==0 && $show==1) // display blocking web
				__security_error($str[$a]);

			else if($sec==0) { // hide blocking web ( for bots functions )
				$str[$a]="";
				$sec=0;
			}

			else
				$sec=0;


		} //end main for


		return($str);
	}



	function __security_output($str) {
		return(htmlspecialchars($str, ENT_QUOTES, 'UTF-8')); 
	}


	//Security error message ;)	
	function __security_error($invalid) {
		if(!empty($invalid)) 
			if(strlen($invalid)==1)
				$invalid = "Invalid char (" . $invalid . ")";

		echo('<html><body style="text-align:center;background-color:red;color:white;"><h1 style="font-size:120px;">Who\'re you trying to fuck m0th3rfuck3r?</h1><br /><h2>Security error: ' . $invalid . '</h2></body></html>');
		exit(0);
	}

?>
