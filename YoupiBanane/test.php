<?php
    $resSTDIN=fopen("php://stdin","r");
	$strChar = stream_get_contents($resSTDIN);
	echo("Content-Type: text/html; charset=utf-8\r\n\r\n");
	echo(strlen($strChar));
//    echo($strChar);
    fclose($resSTDIN);
?>