<?php

        function __get_client_ip() {
                $ip = $_SERVER['REMOTE_ADDR'];
                return($ip);
        }

        function __get_server_ip() {
                $ip = $_SERVER['SERVER_ADDR'];
                return($ip);
        }

?>
