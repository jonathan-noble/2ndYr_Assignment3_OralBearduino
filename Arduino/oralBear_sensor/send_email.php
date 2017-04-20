<?php

$motion = $_GET["motion"];


$text ="Toothbrush has been recently activated! Motion: {$motion}  ";

$admin_email 	= "thenoblelad@gmail.com";
$email 	= "c15487922@mydit.ie";
$subject ="Toothbrush Report";


//send email
mail($admin_email,"$subject",$text,"From:" .$email);

?>
